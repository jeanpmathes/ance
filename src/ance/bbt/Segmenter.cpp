#include "Segmenter.h"

#include <expected>
#include <map>
#include <set>
#include <stack>
#include <string_view>
#include <vector>

#include "ance/est/Expander.h"
#include "ance/est/Node.h"

#include "ance/bbt/Node.h"

#include "Grapher.h"
#include "Printer.h"
#include "Type.h"
#include "Value.h"
#include "ance/ast/Node.h"

namespace
{
    auto prefix = "segmenter";
}

struct ance::bbt::Segmenter::Implementation
{
    class BaseBB
    {
      public:
        virtual ~BaseBB() = default;

        void enter(BaseBB& incoming)
        {
            incoming_.insert(&incoming);
        }

        void push(utility::Owned<Statement> statement)
        {
            statements_.emplace_back(std::move(statement));
        }

        utility::Owned<BasicBlock> createBlock(size_t id)
        {
            assert(id_ == 0);
            assert(id != 0);

            id_ = id;

            return utility::makeOwned<BasicBlock>(id, std::move(statements_), utility::makeOwned<ErrorLink>(core::Location::project()), location());
        }

        [[nodiscard]] virtual utility::Owned<Link> createLink(utility::List<utility::Owned<BasicBlock>> const& blocks) = 0;

        [[nodiscard]] bool isCreated() const
        {
            return id_ != 0;
        }

        [[nodiscard]] size_t index() const
        {
            return id_ - 1;
        }

        [[nodiscard]] bool hasCode() const
        {
            return !statements_.empty();
        }

        [[nodiscard]] bool isRelevantForReachability() const
        {
            for (auto const& statement : statements_)
            {
                if (statement->isRelevantForReachability())
                {
                    return true;
                }
            }

            return false;
        }

        [[nodiscard]] core::Location location() const
        {
            core::Location location = core::Location::project();

            if (!statements_.empty())
            {
                location = statements_[0]->location;

                for (auto const& statement : statements_)
                {
                    location.extend(statement->location);
                }
            }

            return location;
        }

        [[nodiscard]] virtual std::set<BaseBB*> next() const = 0;

        std::tuple<BaseBB*, std::set<BaseBB*>> simplify()
        {
            std::set<BaseBB*> outgoing = next();
            BaseBB*           result   = this;

            if (outgoing.size() == 1)
            {
                BaseBB& target = **outgoing.begin();

                // We can only simplify if this is the only block entering the next (real) block, or if this block is unnecessary.

                if (target.incoming_.size() == 1 || statements_.empty())
                {
                    result = &target;

                    for (auto& incoming : incoming_)
                    {
                        incoming->swap(std::ref(*this), std::ref(target));
                    }

                    target.statements_.insert(target.statements_.begin(),
                                              std::make_move_iterator(statements_.begin()),
                                              std::make_move_iterator(statements_.end()));
                    statements_.clear();

                    target.incoming_.erase(this);
                    target.incoming_.insert(incoming_.begin(), incoming_.end());
                    incoming_.clear();

                    // todo: use virtual method to see if BB has inner code (e.g. condition in branch, match, etc.)
                    // todo: if such a block is simplified out, warn that the condition is not evaluated
                    // todo: this can happen if a match has only a default case
                }
            }

            return {result, outgoing};
        }

        void prune()
        {
            if (statements_.empty() && incoming_.empty())
            {
                std::set<BaseBB*> const outgoing = next();

                for (auto& next : outgoing)
                {
                    next->incoming_.erase(this);
                }
            }
        }

        virtual void swap(std::reference_wrapper<BaseBB> original, std::reference_wrapper<BaseBB> replacement) = 0;

      private:
        std::set<BaseBB*>                        incoming_;
        utility::List<utility::Owned<Statement>> statements_;

        size_t id_ = 0;
    };

    class SimpleBB final : public BaseBB
    {
      public:
        SimpleBB()           = default;
        ~SimpleBB() override = default;

        explicit SimpleBB(utility::Owned<Statement> statement)
        {
            push(std::move(statement));
        }

        void link(BaseBB& next)
        {
            assert(next_ == nullptr);
            next_ = &next;

            next.enter(*this);
        }

        [[nodiscard]] utility::Owned<Link> createLink(utility::List<utility::Owned<BasicBlock>> const& blocks) override
        {
            if (next_ == nullptr)
            {
                return utility::makeOwned<Return>(core::Location::project());// todo: should not be here but in the correct block maybe?
            }

            return utility::makeOwned<Jump>(*blocks[next_->index()], core::Location::project());
        }

        [[nodiscard]] std::set<BaseBB*> next() const override
        {
            std::set<BaseBB*> links;

            if (next_ != nullptr) links.emplace(next_);

            return links;
        }

        void swap(std::reference_wrapper<BaseBB> const original, std::reference_wrapper<BaseBB> const replacement) override
        {
            if (next_ == &original.get())
            {
                next_ = &replacement.get();
            }
        }

      private:
        BaseBB* next_ = nullptr;
    };

    class BranchBB final : public BaseBB
    {
      public:
        BranchBB()           = delete;
        ~BranchBB() override = default;

        BranchBB(Temporary const& condition, BaseBB& true_bb, BaseBB& false_bb, core::Location const& source_location)
            : condition_(condition)
            , true_(true_bb)
            , false_(false_bb)
            , source_location_(source_location)
        {
            true_.get().enter(*this);
            false_.get().enter(*this);
        }

        [[nodiscard]] utility::Owned<Link> createLink(utility::List<utility::Owned<BasicBlock>> const& blocks) override
        {
            return utility::makeOwned<Branch>(condition_, *blocks[true_.get().index()], *blocks[false_.get().index()], source_location_);
        }

        [[nodiscard]] std::set<BaseBB*> next() const override
        {
            std::set<BaseBB*> links;

            links.emplace(&true_.get());
            links.emplace(&false_.get());

            return links;
        }

        void swap(std::reference_wrapper<BaseBB> const original, std::reference_wrapper<BaseBB> const replacement) override
        {
            if (&true_.get() == &original.get())
            {
                true_ = replacement;
            }

            if (&false_.get() == &original.get())
            {
                false_ = replacement;
            }
        }

      private:
        Temporary const&               condition_;
        std::reference_wrapper<BaseBB> true_;
        std::reference_wrapper<BaseBB> false_;

        core::Location source_location_;
    };

    class SwitchBB final : public BaseBB
    {
      public:
        SwitchBB()           = delete;
        ~SwitchBB() override = default;

        struct Case
        {
            Temporary const*               pattern = nullptr;
            core::Location                 pattern_location;
            std::reference_wrapper<BaseBB> block;
            core::Location                 location;
        };

        SwitchBB(Temporary const& condition, utility::List<Case> cases, core::Location const& source_location)
            : condition_(condition)
            , cases_(std::move(cases))
            , source_location_(source_location)
        {
            for (auto& current_case : cases_)
            {
                current_case.block.get().enter(*this);
            }
        }

        [[nodiscard]] utility::Owned<Link> createLink(utility::List<utility::Owned<BasicBlock>> const& blocks) override
        {
            utility::List<utility::Owned<SwitchCase>> switch_cases;
            switch_cases.reserve(cases_.size());

            for (auto& [pattern, pattern_location, block, location] : cases_)
            {
                if (pattern != nullptr)
                {
                    switch_cases.emplace_back(utility::makeOwned<SwitchCase>(*pattern, *blocks[block.get().index()], location));
                }
                else
                {
                    switch_cases.emplace_back(utility::makeOwned<SwitchCase>(pattern_location, *blocks[block.get().index()], location));
                }
            }

            return utility::makeOwned<Switch>(condition_, std::move(switch_cases), source_location_);
        }

        [[nodiscard]] std::set<BaseBB*> next() const override
        {
            std::set<BaseBB*> links;

            for (auto& [pattern, pattern_location, block, location] : cases_)
            {
                links.emplace(&block.get());
            }

            return links;
        }

        void swap(std::reference_wrapper<BaseBB> const original, std::reference_wrapper<BaseBB> const replacement) override
        {
            for (auto& current_case : cases_)
            {
                if (&current_case.block.get() == &original.get())
                {
                    current_case.block = replacement;
                }
            }
        }

      private:
        Temporary const&    condition_;
        utility::List<Case> cases_;

        core::Location source_location_;
    };

    class ReturnBB final : public BaseBB
    {
      public:
        ReturnBB()           = delete;
        ~ReturnBB() override = default;

        explicit ReturnBB(core::Location const& source_location) : source_location_(source_location) {}

        [[nodiscard]] utility::Owned<Link> createLink(utility::List<utility::Owned<BasicBlock>> const&) override
        {
            return utility::makeOwned<Return>(core::Location::project());
        }

        [[nodiscard]] std::set<BaseBB*> next() const override
        {
            return {};
        }

        void swap(std::reference_wrapper<BaseBB> const, std::reference_wrapper<BaseBB> const) override
        {
            // Nothing to do.
        }

      private:
        core::Location source_location_;
    };

    class RET final : public est::Visitor
    {
      public:
        using Visitor::visit;

        RET(core::Reporter& reporter, TypeContext& type_context) : reporter_(reporter), type_context_(type_context) {}
        ~RET() override = default;

        struct BlockOutput
        {
            BaseBB const& block;

            friend std::ostream& operator<<(std::ostream& os, BlockOutput const& self)
            {
                os << "BB{";

                if (self.block.isCreated())
                {
                    os << "index=" << self.block.index();
                }
                else
                {
                    os << "index=uncreated";
                }

                os << ", has_code=" << self.block.hasCode() << "}";

                return os;
            }
        };

        [[nodiscard]] static BlockOutput block(BaseBB const& base_bb)
        {
            return {base_bb};
        }

        // ReSharper disable once CppMemberFunctionMayBeConst
        core::Reporter::MessageBuilder trace(std::string_view const declaration_name, est::Declaration const& declaration)
        {
            auto msg = reporter_.trace(prefix, core::Location::nowhere());
            msg << "visit declaration " << declaration_name << " " << declaration.location;
            return msg;
        }

        // ReSharper disable once CppMemberFunctionMayBeConst
        core::Reporter::MessageBuilder trace(std::string_view const statement_name, est::Statement const& statement)
        {
            auto msg = reporter_.trace(prefix, core::Location::nowhere());
            msg << "visit statement " << statement_name << " " << statement.location;
            return msg;
        }

        // ReSharper disable once CppMemberFunctionMayBeConst
        core::Reporter::MessageBuilder trace(std::string_view const expression_name, est::Expression const& expression)
        {
            auto msg = reporter_.trace(prefix, core::Location::nowhere());
            msg << "visit expression " << expression_name << " " << expression.location;
            return msg;
        }

        struct Result
        {
            utility::List<utility::Owned<BaseBB>> blocks = {};
            std::reference_wrapper<SimpleBB>      entry;
            std::reference_wrapper<SimpleBB>      exit;
        };

        class Builder final
        {
          public:
            explicit Builder(RET& ret) : ret_(ret)
            {
                utility::Owned<SimpleBB> block = utility::makeOwned<SimpleBB>();

                entry_ = std::ref(*block);
                exit_  = entry_;

                blocks_.emplace_back(std::move(block));
            }

            template<typename StatementType, typename... Args>
            StatementType& addStatement(Args&&... args)
            {
                utility::Owned<StatementType> inner     = utility::makeOwned<StatementType>(std::forward<Args>(args)...);
                StatementType&                inner_ref = *inner;

                utility::Owned<SimpleBB> block     = utility::makeOwned<SimpleBB>(std::move(inner));
                std::reference_wrapper   block_ref = *block;
                blocks_.emplace_back(std::move(block));

                link(exit_.value(), block_ref);
                exit_ = block_ref;

                return inner_ref;
            }

            Temporary& addTemporary(std::string id, core::Location const& location)
            {
                size_t&     counter      = ret_.state_.temporary_name_counters[id];
                std::string temporary_id = std::format("{}'{}", id, counter++);

                return addStatement<Temporary>(std::move(temporary_id), location);
            }

            void addSegmented(est::Statement const& statement)
            {
                auto [result_entry, result_exit] = ret_.segment(statement);

                link(exit_.value(), result_entry);
                exit_ = result_exit;
            }

            void addSegmented(est::Expression const& expression, Temporary const& destination)
            {
                auto [result_entry, result_exit] = ret_.segment(expression, destination);

                link(exit_.value(), result_entry);
                exit_ = result_exit;
            }

            template<typename BlockType, typename... Args>
            BlockType& addSpecialBlock(Args&&... args)
            {
                utility::Owned<BlockType> block = utility::makeOwned<BlockType>(std::forward<Args>(args)...);
                BlockType&                ref   = *block;
                blocks_.emplace_back(std::move(block));

                link(exit_.value(), ref);
                addDisconnectedBlock();

                return ref;
            }

            void addDisconnectedBlock()
            {
                addDisconnectedBlock(utility::makeOwned<SimpleBB>());
            }

            void addDisconnectedBlock(utility::Owned<SimpleBB> block)
            {
                std::reference_wrapper block_ref = *block;

                blocks_.emplace_back(std::move(block));
                exit_ = block_ref;
            }

            [[nodiscard]] std::reference_wrapper<SimpleBB> getEntry() const
            {
                assert(entry_.hasValue());
                return entry_.value();
            }

            [[nodiscard]] std::reference_wrapper<SimpleBB> getExit() const
            {
                assert(exit_.hasValue());
                return exit_.value();
            }

            Result take()
            {
                assert(entry_.hasValue());
                assert(exit_.hasValue());

                return Result {.blocks = std::move(blocks_), .entry = entry_.value(), .exit = exit_.value()};
            }

          private:
            RET& ret_;

            utility::List<utility::Owned<BaseBB>> blocks_ = {};

            utility::Optional<std::reference_wrapper<SimpleBB>> entry_ = {};
            utility::Optional<std::reference_wrapper<SimpleBB>> exit_  = {};
        };

        utility::Owned<Flows> apply(est::File const& file)
        {
            utility::List<utility::Owned<Flow>> flows;

            for (auto const& declaration : file.declarations)
            {
                flows.emplace_back(apply(*declaration));
            }

            return utility::makeOwned<Flows>(std::move(flows), file.location);
        }

        utility::Owned<Flow> apply(est::Declaration const& declaration)
        {
            return apply(declaration, false, declaration.displayName());
        }

        template<typename Segmentable>
        utility::Owned<Flow> apply(Segmentable const& segmentable, bool is_function, std::string id)
        {
            reporter_.trace(prefix, core::Location::nowhere()) << "apply enter {id=" << id << ", is_function=" << is_function << "}";

            FlowState previous_state = std::move(state_);

            state_ = {};

            utility::Owned<SimpleBB> entry_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper   entry       = *entry_block;

            state_.segment.entry_bb = entry_block.get();
            state_.segment.exit_bb  = state_.segment.entry_bb;
            state_.bbs.emplace_back(std::move(entry_block));

            state_.is_function = is_function;

            auto [segmentable_entry, segmentable_exit] = segment(segmentable);

            utility::Owned<SimpleBB>     exit_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper const exit       = *exit_block;

            link(entry, segmentable_entry);
            link(segmentable_exit, exit);

            std::reference_wrapper<BaseBB> const current_entry = simplify(entry);

            utility::List<utility::Owned<BasicBlock>>     basic_blocks;
            utility::List<std::reference_wrapper<BaseBB>> converted;

            std::stack<std::reference_wrapper<BaseBB>> unconverted;
            unconverted.emplace(current_entry);

            while (!unconverted.empty())
            {
                BaseBB& current = unconverted.top();
                unconverted.pop();

                if (current.isCreated()) continue;

                basic_blocks.emplace_back(current.createBlock(basic_blocks.size() + 1));
                converted.emplace_back(current);

                reporter_.trace(prefix, core::Location::nowhere()) << "apply create block " << block(current);

                for (auto& next : current.next())
                {
                    if (!next->isCreated())
                    {
                        unconverted.emplace(*next);
                    }
                }
            }

            for (size_t index = 0; index < converted.size(); index++)
            {
                BaseBB& current = converted[index].get();

                utility::Owned<Link> link = current.createLink(basic_blocks);
                basic_blocks[index]->link = std::move(link);

                reporter_.trace(prefix, core::Location::nowhere()) << "apply create link " << block(current);
            }

            BasicBlock& first_block = *basic_blocks[current_entry.get().index()];

            size_t&     counter = flow_name_counters_[id];
            std::string flow_id = std::format("{}'{}", id, counter++);

            state_ = std::move(previous_state);

            utility::Owned<Flow> flow = utility::makeOwned<Flow>(std::move(basic_blocks), first_block, std::move(flow_id), segmentable.location);

            reporter_.trace(prefix, core::Location::nowhere()) << "apply exit {flow_id=" << flow->id() << ", count(block)=" << flow->blocks.size() << "}";

            return flow;
        }

        std::reference_wrapper<BaseBB> simplify(std::reference_wrapper<BaseBB> entry)
        {
            reporter_.trace(prefix, core::Location::nowhere()) << "simplify enter {entry=" << block(entry) << "}";

            for (auto& block : state_.bbs)
            {
                block.get()->prune();
            }

            std::set<BaseBB*>                          simplified;
            std::stack<std::reference_wrapper<BaseBB>> to_simplify;
            to_simplify.emplace(entry);

            std::reference_wrapper<BaseBB> current_entry = entry;

            while (!to_simplify.empty())
            {
                BaseBB& current = to_simplify.top();
                to_simplify.pop();

                if (simplified.contains(&current)) continue;
                simplified.insert(&current);

                auto [result, next] = current.simplify();

                if (&current == &current_entry.get())
                {
                    current_entry = *result;
                }

                for (auto& next_block : next)
                {
                    if (!simplified.contains(next_block))
                    {
                        to_simplify.emplace(*next_block);
                    }
                }
            }

            bool           has_unreachable_code       = false;
            core::Location first_unreachable_location = core::Location::project();

            for (auto& block : state_.bbs)
            {
                if (block.get()->isRelevantForReachability() && !simplified.contains(block.get()))
                {
                    has_unreachable_code       = true;
                    first_unreachable_location = core::Location::getFirst(first_unreachable_location, block.get()->location());
                }
            }

            if (has_unreachable_code)
            {
                reporter_.warning(first_unreachable_location) << "Unreachable code";
            }

            reporter_.trace(prefix, core::Location::nowhere())
                << "simplify exit {entry=" << block(current_entry) << ", count(reachable_blocks)=" << simplified.size() << "}";

            return current_entry;
        }

        static void link(std::reference_wrapper<SimpleBB> const from, std::reference_wrapper<BaseBB> const to)
        {
            assert(&from.get() != &to.get());

            from.get().link(to.get());
        }

        std::pair<std::reference_wrapper<SimpleBB>, std::reference_wrapper<SimpleBB>> segment(est::Declaration const& declaration)
        {
            SegmentState const previous_segment = state_.segment;
            state_.segment                      = {};

            visit(declaration);

            assert(state_.segment.entry_bb != nullptr);
            assert(state_.segment.exit_bb != nullptr);

            std::pair<SimpleBB&, SimpleBB&> const result = {*state_.segment.entry_bb, *state_.segment.exit_bb};

            state_.segment = previous_segment;

            return result;
        }

        std::pair<std::reference_wrapper<SimpleBB>, std::reference_wrapper<SimpleBB>> segment(est::Statement const& statement)
        {
            SegmentState const previous_segment = state_.segment;
            state_.segment                      = {};

            visit(statement);

            assert(state_.segment.entry_bb != nullptr);
            assert(state_.segment.exit_bb != nullptr);

            std::pair<SimpleBB&, SimpleBB&> const result = {*state_.segment.entry_bb, *state_.segment.exit_bb};

            state_.segment = previous_segment;

            return result;
        }

        std::pair<std::reference_wrapper<SimpleBB>, std::reference_wrapper<SimpleBB>> segment(est::Expression const& expression, Temporary const& destination)
        {
            SegmentState const previous_segment = state_.segment;
            state_.segment                      = {};
            state_.segment.destination          = &destination;

            assert(state_.segment.destination != nullptr);

            visit(expression);

            assert(state_.segment.entry_bb != nullptr);
            assert(state_.segment.exit_bb != nullptr);

            std::pair<SimpleBB&, SimpleBB&> const result = {*state_.segment.entry_bb, *state_.segment.exit_bb};

            state_.segment = previous_segment;

            return result;
        }

        [[nodiscard]] Temporary const& destination() const
        {
            assert(state_.segment.destination != nullptr);
            return *state_.segment.destination;
        }

        void storeBlocks(utility::List<utility::Owned<BaseBB>>&& blocks)
        {
            state_.bbs.insert(state_.bbs.end(), std::make_move_iterator(blocks.begin()), std::make_move_iterator(blocks.end()));
        }

        void storeBlocks(Result&& result)
        {
            storeBlocks(std::move(result.blocks));
        }

        void setResult(utility::List<utility::Owned<BaseBB>>&& blocks, SimpleBB& entry, SimpleBB& exit)
        {
            storeBlocks(std::move(blocks));

            state_.segment.entry_bb = &entry;
            state_.segment.exit_bb  = &exit;
        }

        void setResult(Result&& result)
        {
            setResult(std::move(result.blocks), result.entry.get(), result.exit.get());
        }

        void setEmptyResult()
        {
            Builder builder(*this);

            setResult(builder.take());
        }

        void visit(est::File const&) override
        {
            // See the respective apply method.
        }

        void visit(est::RunnableDeclaration const& runnable) override
        {
            trace("RunnableDeclaration", runnable);

            Builder builder(*this);
            builder.addSegmented(*runnable.body);
            setResult(builder.take());
        }

        void visit(est::VariableDeclaration const& variable_declaration) override
        {
            trace("VariableDeclaration", variable_declaration)
                << ", access=" << variable_declaration.access_modifier << ", execution=" << variable_declaration.execution_modifier
                << ", identifier=" << variable_declaration.identifier << ", assigner=" << variable_declaration.assigner << ", has_value=" << std::boolalpha
                << variable_declaration.value.hasValue();

            Builder builder(*this);

            auto& type_tmp = builder.addTemporary("VariableDeclaration_Type", variable_declaration.type->location);
            builder.addSegmented(*variable_declaration.type, type_tmp);

            auto& value_tmp = builder.addTemporary("VariableDeclaration_Value", variable_declaration.location);
            if (variable_declaration.value.hasValue())
            {
                builder.addSegmented(**variable_declaration.value, value_tmp);
            }
            else
            {
                builder.addStatement<Default>(type_tmp, value_tmp, variable_declaration.location);
            }

            auto& scope_tmp = builder.addTemporary("VariableDeclaration_Scope", variable_declaration.location);
            builder.addStatement<CurrentScope>(scope_tmp, variable_declaration.location);

            auto& identifier_tmp = builder.addTemporary("VariableDeclaration_Identifier", variable_declaration.location);
            builder.addStatement<Constant>(Identifier::make(variable_declaration.identifier, type_context_), identifier_tmp, variable_declaration.location);

            auto& is_final_tmp = builder.addTemporary("VariableDeclaration_IsFinal", variable_declaration.location);
            builder.addStatement<Constant>(Bool::make(variable_declaration.assigner.isFinal(), type_context_), is_final_tmp, variable_declaration.location);

            auto& declared_tmp = builder.addTemporary("VariableDeclaration_Declared", variable_declaration.location);
            {
                utility::List<std::reference_wrapper<Temporary const>> args;
                args.emplace_back(scope_tmp);
                args.emplace_back(identifier_tmp);
                args.emplace_back(is_final_tmp);
                args.emplace_back(type_tmp);
                builder.addStatement<Intrinsic>(core::Intrinsic::DECLARE, std::move(args), declared_tmp, variable_declaration.location);
            }

            auto& ref_tmp = builder.addTemporary("VariableDeclaration_Ref", variable_declaration.location);
            builder.addStatement<Access>(declared_tmp, ref_tmp, variable_declaration.location);
            builder.addStatement<Store>(ref_tmp, value_tmp, variable_declaration.location);

            setResult(builder.take());
        }

        void visit(est::ErrorStatement const& error_statement) override
        {
            trace("ErrorStatement", error_statement);

            Builder builder(*this);

            builder.addStatement<ErrorStatement>(error_statement.location);

            setResult(builder.take());
        }

        void visit(est::Pass const& pass_statement) override
        {
            trace("Pass", pass_statement);

            Builder builder(*this);

            builder.addStatement<Pass>(pass_statement.location);

            setResult(builder.take());
        }

        template<typename Node, typename BuildInner>
        void setResultInOrderedScope(Node const& node, BuildInner build_inner)
        {
            Builder builder(*this);

            auto& scope_enter = builder.addStatement<OrderedScopeEnter>(node.location.first());
            state_.scopes.emplace_back(&scope_enter);

            build_inner(builder, node);

            state_.scopes.pop_back();
            builder.addStatement<OrderedScopeExit>(scope_enter, node.location.last());

            setResult(builder.take());
        }

        void visit(est::Block const& block) override
        {
            trace("Block", block) << ", count(statements)=" << block.statements.size();

            setResultInOrderedScope(block, [](Builder& builder, est::Block const& node) {
                for (auto& statement : node.statements)
                {
                    builder.addSegmented(*statement);
                }
            });
        }

        void visit(est::Independent const& independent) override
        {
            trace("Independent", independent);

            Builder builder(*this);

            auto& value_tmp = builder.addTemporary("Independent", independent.location);
            builder.addSegmented(*independent.expression, value_tmp);

            setResult(builder.take());
        }

        void visit(est::Assignment const& assignment) override
        {
            trace("Assignment", assignment) << ", assigner=" << assignment.assigner;

            Builder builder(*this);

            auto& target_tmp = builder.addTemporary("Assignment_Target", assignment.assignee->location);
            builder.addSegmented(*assignment.assignee, target_tmp);

            auto& value_tmp = builder.addTemporary("Assignment_Value", assignment.value->location);
            builder.addSegmented(*assignment.value, value_tmp);

            builder.addStatement<Store>(target_tmp, value_tmp, assignment.location);// todo: pass assigner to this and use

            setResult(builder.take());
        }

        void visit(est::If const& if_statement) override
        {
            trace("If", if_statement);

            Builder builder(*this);

            auto& condition_tmp = builder.addTemporary("If_Condition", if_statement.condition->location);
            builder.addSegmented(*if_statement.condition, condition_tmp);

            auto [true_entry, true_exit]   = segment(*if_statement.true_block);
            auto [false_entry, false_exit] = segment(*if_statement.false_block);

            builder.addSpecialBlock<BranchBB>(condition_tmp, true_entry.get(), false_entry.get(), if_statement.location);

            link(true_exit, builder.getExit());
            link(false_exit, builder.getExit());

            setResult(builder.take());
        }

        void visit(est::Loop const& loop) override
        {
            trace("Loop", loop);

            Builder builder(*this);

            builder.addDisconnectedBlock();

            std::reference_wrapper const entry = builder.getEntry();
            std::reference_wrapper const exit  = builder.getExit();

            state_.loops.emplace_back(Loop {.entry = entry, .exit = exit, .scope_depth = state_.scopes.size()});

            auto [loop_entry, loop_exit] = segment(*loop.body);

            state_.loops.pop_back();

            link(entry, loop_entry);
            link(loop_exit, entry);

            setResult(builder.take());
        }

        void visit(est::Break const& break_statement) override
        {
            trace("Break", break_statement);

            if (state_.loops.empty())
            {
                reporter_.error(break_statement.location) << "Break statement outside of loop";

                setEmptyResult();

                return;
            }

            Builder builder(*this);

            size_t const target_depth = state_.loops.back().scope_depth;
            for (size_t i = state_.scopes.size(); i > target_depth; i--)
            {
                builder.addStatement<OrderedScopeExit>(*state_.scopes[i - 1], break_statement.location);
            }

            link(builder.getExit(), state_.loops.back().exit);

            builder.addDisconnectedBlock();

            setResult(builder.take());
        }

        void visit(est::Continue const& continue_statement) override
        {
            trace("Continue", continue_statement);

            if (state_.loops.empty())
            {
                reporter_.error(continue_statement.location) << "Continue statement outside of loop";

                setEmptyResult();

                return;
            }

            Builder builder(*this);

            size_t const target_depth = state_.loops.back().scope_depth;
            for (size_t i = state_.scopes.size(); i > target_depth; i--)
            {
                builder.addStatement<OrderedScopeExit>(*state_.scopes[i - 1], continue_statement.location);
            }

            link(builder.getExit(), state_.loops.back().entry);

            builder.addDisconnectedBlock();

            setResult(builder.take());
        }

        void visit(est::Match const& match) override
        {
            trace("Match", match) << ", count(cases)=" << match.cases.size();

            Builder builder(*this);

            auto& value_tmp = builder.addTemporary("Match_Value", match.value->location);
            builder.addSegmented(*match.value, value_tmp);

            utility::Owned<SimpleBB> match_end = utility::makeOwned<SimpleBB>();

            utility::List<SwitchBB::Case> cases;
            for (auto& match_case : match.cases)
            {
                Builder case_builder(*this);
                case_builder.addSegmented(*match_case->body);
                link(case_builder.getExit(), *match_end);

                bool has_patterns = false;
                for (auto& pattern : match_case->patterns)
                {
                    auto& pattern_tmp = builder.addTemporary("Match_Pattern", pattern->location);
                    builder.addSegmented(*pattern, pattern_tmp);

                    cases.emplace_back(&pattern_tmp, pattern->location, case_builder.getEntry(), pattern->location);

                    has_patterns = true;
                }

                if (!has_patterns)
                {
                    cases.emplace_back(nullptr, match_case->default_pattern_location, case_builder.getEntry(), match_case->location);
                }

                storeBlocks(case_builder.take());
            }

            builder.addSpecialBlock<SwitchBB>(value_tmp, std::move(cases), match.location);
            builder.addDisconnectedBlock(std::move(match_end));

            setResult(builder.take());
        }

        void visit(est::Return const& return_statement) override
        {
            trace("Return", return_statement) << ", has_value=" << std::boolalpha << return_statement.value.hasValue();

            if (!state_.is_function)
            {
                reporter_.error(return_statement.location) << "Return statement outside of function";
            }

            Builder builder(*this);

            if (return_statement.value.hasValue())
            {
                auto& return_value_tmp = builder.addTemporary("Return_Value", return_statement.value->get()->location);
                builder.addSegmented(**return_statement.value, return_value_tmp);

                builder.addStatement<SetReturnValue>(return_value_tmp, return_statement.location);
            }

            for (size_t i = state_.scopes.size(); i > 0; i--)
            {
                builder.addStatement<OrderedScopeExit>(*state_.scopes[i - 1], return_statement.location);
            }

            builder.addSpecialBlock<ReturnBB>(return_statement.location);

            setResult(builder.take());
        }

        void visit(est::Let const& let) override
        {
            trace("Let", let) << ", identifier=" << let.identifier << ", assigner=" << let.assigner << ", has_value=" << std::boolalpha << let.value.hasValue();

            Builder builder(*this);

            auto& type_tmp = builder.addTemporary("Let_Type", let.type->location);
            builder.addSegmented(*let.type, type_tmp);

            auto& value_tmp = builder.addTemporary("Let_Value", let.location);
            if (let.value.hasValue())
            {
                builder.addSegmented(**let.value, value_tmp);
            }
            else
            {
                builder.addStatement<Default>(type_tmp, value_tmp, let.location);
            }

            auto& scope_tmp = builder.addTemporary("Let_Scope", let.location);
            builder.addStatement<CurrentScope>(scope_tmp, let.location);

            auto& identifier_tmp = builder.addTemporary("Let_Identifier", let.location);
            builder.addStatement<Constant>(Identifier::make(let.identifier, type_context_), identifier_tmp, let.location);

            auto& is_final_tmp = builder.addTemporary("Let_IsFinal", let.location);
            builder.addStatement<Constant>(Bool::make(let.assigner.isFinal(), type_context_), is_final_tmp, let.location);

            auto& declared_tmp = builder.addTemporary("Let_Declared", let.location);
            {
                utility::List<std::reference_wrapper<Temporary const>> args;
                args.emplace_back(scope_tmp);
                args.emplace_back(identifier_tmp);
                args.emplace_back(is_final_tmp);
                args.emplace_back(type_tmp);
                builder.addStatement<Intrinsic>(core::Intrinsic::DECLARE, std::move(args), declared_tmp, let.location);
            }

            auto& ref_tmp = builder.addTemporary("Let_Ref", let.location);
            builder.addStatement<Access>(declared_tmp, ref_tmp, let.location);
            builder.addStatement<Store>(ref_tmp, value_tmp, let.location);

            setResult(builder.take());
        }

        void visit(est::Erase const& erase) override
        {
            trace("Erase", erase) << ", identifier=" << erase.identifier;

            Builder builder(*this);

            auto& identifier_tmp = builder.addTemporary("Erase_Identifier", erase.location);
            builder.addStatement<Constant>(Identifier::make(erase.identifier, type_context_), identifier_tmp, erase.location);

            auto& scope_tmp = builder.addTemporary("Erase_Scope", erase.location);
            builder.addStatement<CurrentScope>(scope_tmp, erase.location);

            {
                auto& discard_tmp = builder.addTemporary("Erase_Discard", erase.location);// todo: maybe there is a nicer way?

                utility::List<std::reference_wrapper<Temporary const>> args;
                args.emplace_back(scope_tmp);
                args.emplace_back(identifier_tmp);
                builder.addStatement<Intrinsic>(core::Intrinsic::ERASE, std::move(args), discard_tmp, erase.location);
            }

            setResult(builder.take());
        }

        void visit(est::Assert const& assert) override
        {
            trace("Assert", assert);

            Builder builder(*this);

            auto& condition_tmp = builder.addTemporary("Assert_Condition", assert.condition->location);
            builder.addSegmented(*assert.condition, condition_tmp);

            builder.addStatement<Assert>(condition_tmp, assert.condition->location);

            setResult(builder.take());
        }

        void visit(est::ErrorExpression const& error) override
        {
            trace("ErrorExpression", error);

            Builder builder(*this);

            builder.addStatement<ErrorStatement>(error.location);

            setResult(builder.take());
        }

        void visit(est::Intrinsic const& intrinsic) override
        {
            trace("Intrinsic", intrinsic) << ", count(arguments)=" << intrinsic.arguments.size();

            Builder builder(*this);

            auto& name_tmp = builder.addTemporary("Intrinsic_Name", intrinsic.name->location);
            builder.addSegmented(*intrinsic.name, name_tmp);

            utility::List<std::reference_wrapper<Temporary const>> arguments;
            arguments.emplace_back(name_tmp);

            for (size_t index = 0; index < intrinsic.arguments.size(); index++)
            {
                auto& argument_tmp = builder.addTemporary(std::format("Intrinsic_Argument{}", index), intrinsic.arguments[index]->location);
                builder.addSegmented(*intrinsic.arguments[index], argument_tmp);

                arguments.emplace_back(argument_tmp);
            }

            builder.addStatement<Intrinsic>(core::Intrinsic::CALL_INTRINSIC, std::move(arguments), destination(), intrinsic.location);

            setResult(builder.take());
        }

        void visit(est::BlockExpression const& block_expression) override
        {
            trace("BlockExpression", block_expression) << ", count(statements)=" << block_expression.statements.size();

            setResultInOrderedScope(block_expression, [this](Builder& builder, est::BlockExpression const& node) {
                for (auto& statement : node.statements)
                {
                    builder.addSegmented(*statement);
                }

                auto& result_tmp = builder.addTemporary("BlockExpression_Result", node.location);
                builder.addSegmented(*node.result, result_tmp);
                builder.addStatement<Dereference>(result_tmp, destination(), node.location);
            });
        }

        void visit(est::Access const& access) override
        {
            trace("Access", access) << ", identifier=" << access.identifier;

            Builder builder(*this);

            auto& scope_tmp = builder.addTemporary("Access_Scope", access.location);
            builder.addStatement<CurrentScope>(scope_tmp, access.location);

            auto& identifier_tmp = builder.addTemporary("Access_Identifier", access.location);
            builder.addStatement<Constant>(Identifier::make(access.identifier, type_context_), identifier_tmp, access.location);

            auto& resolved_tmp = builder.addTemporary("Access_Resolved", access.location);
            {
                utility::List<std::reference_wrapper<Temporary const>> args;
                args.emplace_back(scope_tmp);
                args.emplace_back(identifier_tmp);
                builder.addStatement<Intrinsic>(core::Intrinsic::RESOLVE, std::move(args), resolved_tmp, access.location);
            }

            builder.addStatement<Access>(resolved_tmp, destination(), access.location);

            setResult(builder.take());
        }

        void visit(est::Call const& call) override
        {
            trace("Call", call) << ", count(arguments)=" << call.arguments.size();

            Builder builder(*this);

            auto& callee_tmp = builder.addTemporary("Call_Callee", call.callee->location);
            builder.addSegmented(*call.callee, callee_tmp);

            utility::List<std::reference_wrapper<Temporary const>> arguments;
            for (size_t index = 0; index < call.arguments.size(); index++)
            {
                auto& argument_tmp = builder.addTemporary(std::format("Call_Argument{}", index), call.arguments[index]->location);
                builder.addSegmented(*call.arguments[index], argument_tmp);

                arguments.emplace_back(argument_tmp);
            }

            builder.addStatement<Call>(callee_tmp, std::move(arguments), destination(), call.location);

            setResult(builder.take());
        }

        void visit(est::FunctionConstructor const& function_constructor) override
        {
            trace("FunctionConstructor", function_constructor)
                << ", name=" << function_constructor.name << ", count(parameters)=" << function_constructor.parameters.size();

            Builder builder(*this);

            utility::List<Parameter> parameters;
            for (auto const& parameter : function_constructor.parameters)
            {
                auto& parameter_type_tmp = builder.addTemporary("FunctionConstructor_ParameterType", parameter.type->location);
                builder.addSegmented(*parameter.type, parameter_type_tmp);
                parameters.emplace_back(parameter.identifier, parameter_type_tmp, parameter.location);
            }

            auto& return_type_tmp = builder.addTemporary("FunctionConstructor_ReturnType", function_constructor.return_type->location);
            builder.addSegmented(*function_constructor.return_type, return_type_tmp);

            utility::Owned<Flow> flow = apply(*function_constructor.body, true, "Function");

            builder.addStatement<FunctionConstructor>(function_constructor.name,
                                                      std::move(parameters),
                                                      return_type_tmp,
                                                      std::move(flow),
                                                      destination(),
                                                      function_constructor.location);

            setResult(builder.take());
        }

        void visit(est::UnitLiteral const& unit_literal) override
        {
            trace("UnitLiteral", unit_literal);

            Builder builder(*this);

            builder.addStatement<Constant>(Unit::make(type_context_), destination(), unit_literal.location);

            setResult(builder.take());
        }

        void visit(est::SizeLiteral const& size_literal) override
        {
            trace("SizeLiteral", size_literal) << ", value=" << size_literal.value;

            Builder builder(*this);

            builder.addStatement<Constant>(Size::make(size_literal.value, type_context_), destination(), size_literal.location);

            setResult(builder.take());
        }

        void visit(est::FloatingPointLiteral const& floating_point_literal) override
        {
            trace("FloatingPointLiteral", floating_point_literal)
                << ", precision=" << floating_point_literal.precision << ", value=" << floating_point_literal.value;

            Builder builder(*this);

            builder.addStatement<Constant>(Float::make(floating_point_literal.value, floating_point_literal.precision, type_context_),
                                           destination(),
                                           floating_point_literal.location);

            setResult(builder.take());
        }

        void visit(est::StringLiteral const& string_literal) override
        {
            trace("StringLiteral", string_literal) << ", value=" << string_literal.value;

            Builder builder(*this);

            builder.addStatement<Constant>(String::make(string_literal.value, type_context_), destination(), string_literal.location);

            setResult(builder.take());
        }

        void visit(est::BoolLiteral const& bool_literal) override
        {
            trace("BoolLiteral", bool_literal) << ", value=" << std::boolalpha << bool_literal.value;

            Builder builder(*this);

            builder.addStatement<Constant>(Bool::make(bool_literal.value, type_context_), destination(), bool_literal.location);

            setResult(builder.take());
        }

        void visit(est::Default const& default_value) override
        {
            trace("Default", default_value);

            Builder builder(*this);

            auto& type = builder.addTemporary("Default_Type", default_value.type->location);
            builder.addSegmented(*default_value.type, type);

            builder.addStatement<Default>(type, destination(), default_value.location);

            setResult(builder.take());
        }

        void visit(est::Here const& here) override
        {
            trace("Here", here);

            Builder builder(*this);

            builder.addStatement<Constant>(Location::make(here.location, type_context_), destination(), here.location);

            setResult(builder.take());
        }

        void visit(est::UnaryOperation const& unary_operation) override
        {
            trace("UnaryOperation", unary_operation) << ", op=" << unary_operation.op;

            Builder builder(*this);

            auto& operand_tmp = builder.addTemporary("UnaryOperation_Operand", unary_operation.operand->location);
            builder.addSegmented(*unary_operation.operand, operand_tmp);

            auto& operand_dereferenced_tmp = builder.addTemporary("UnaryOperation_Operand_Dereferenced", unary_operation.operand->location);
            builder.addStatement<Dereference>(operand_tmp, operand_dereferenced_tmp, unary_operation.operand->location);

            auto& operand_type_tmp = builder.addTemporary("UnaryOperation_Operand_Type", unary_operation.location);
            {
                utility::List<std::reference_wrapper<Temporary const>> type_args;
                type_args.emplace_back(operand_dereferenced_tmp);
                builder.addStatement<TypeOf>(std::move(type_args), operand_type_tmp, unary_operation.location);
            }

            auto& operator_function_tmp = builder.addTemporary("UnaryOperation_OperatorFunction", unary_operation.location);
            builder.addStatement<GetUnaryOperatorFunction>(unary_operation.op, operand_type_tmp, operator_function_tmp, unary_operation.location);

            {
                utility::List<std::reference_wrapper<Temporary const>> call_args;
                call_args.emplace_back(operand_dereferenced_tmp);
                builder.addStatement<Call>(operator_function_tmp, std::move(call_args), destination(), unary_operation.location);
            }

            setResult(builder.take());
        }

        void visit(est::BinaryOperation const& binary_operation) override
        {
            trace("BinaryOperation", binary_operation) << ", op=" << binary_operation.op;

            Builder builder(*this);

            auto& left_tmp = builder.addTemporary("BinaryOperation_Left", binary_operation.left->location);
            builder.addSegmented(*binary_operation.left, left_tmp);

            auto& left_dereferenced_tmp = builder.addTemporary("BinaryOperation_Left_Dereferenced", binary_operation.left->location);
            builder.addStatement<Dereference>(left_tmp, left_dereferenced_tmp, binary_operation.left->location);

            auto& right_tmp = builder.addTemporary("BinaryOperation_Right", binary_operation.right->location);
            builder.addSegmented(*binary_operation.right, right_tmp);

            auto& right_dereferenced_tmp = builder.addTemporary("BinaryOperation_Right_Dereferenced", binary_operation.right->location);
            builder.addStatement<Dereference>(right_tmp, right_dereferenced_tmp, binary_operation.right->location);

            auto& left_type_tmp = builder.addTemporary("BinaryOperation_Left_Type", binary_operation.location);
            {
                utility::List<std::reference_wrapper<Temporary const>> type_args;
                type_args.emplace_back(left_dereferenced_tmp);
                builder.addStatement<TypeOf>(std::move(type_args), left_type_tmp, binary_operation.location);
            }

            auto& right_type_tmp = builder.addTemporary("BinaryOperation_Right_Type", binary_operation.location);
            {
                utility::List<std::reference_wrapper<Temporary const>> type_args;
                type_args.emplace_back(right_dereferenced_tmp);
                builder.addStatement<TypeOf>(std::move(type_args), right_type_tmp, binary_operation.location);
            }

            auto& operator_function_tmp = builder.addTemporary("BinaryOperation_OperatorFunction", binary_operation.location);
            builder.addStatement<GetBinaryOperatorFunction>(binary_operation.op,
                                                            left_type_tmp,
                                                            right_type_tmp,
                                                            operator_function_tmp,
                                                            binary_operation.location);

            {
                utility::List<std::reference_wrapper<Temporary const>> call_args;
                call_args.emplace_back(left_dereferenced_tmp);
                call_args.emplace_back(right_dereferenced_tmp);
                builder.addStatement<Call>(operator_function_tmp, std::move(call_args), destination(), binary_operation.location);
            }

            setResult(builder.take());
        }

        void visit(est::TypeOf const& type_of) override
        {
            trace("TypeOf", type_of);

            Builder builder(*this);

            utility::List<std::reference_wrapper<Temporary const>> arguments;
            for (auto const& expression : type_of.expressions)
            {
                auto& value_tmp = builder.addTemporary("TypeOf_Value", expression->location);
                builder.addSegmented(*expression, value_tmp);
                arguments.emplace_back(value_tmp);
            }

            builder.addStatement<TypeOf>(std::move(arguments), destination(), type_of.location);

            setResult(builder.take());
        }

        void visit(est::MatchCase const&) override
        {
            // Cases are also handled in the match visit method; therefore, this method is intentionally empty.
        }

        struct Loop
        {
            std::reference_wrapper<SimpleBB> entry;
            std::reference_wrapper<SimpleBB> exit;
            size_t                           scope_depth = 0;
        };

      private:
        struct SegmentState
        {
            SimpleBB*        entry_bb    = nullptr;
            SimpleBB*        exit_bb     = nullptr;
            Temporary const* destination = nullptr;
        };

        struct FlowState
        {
            utility::List<utility::Owned<BaseBB>> bbs;

            SegmentState segment = {};

            std::vector<Loop>                     loops  = {};
            std::vector<OrderedScopeEnter const*> scopes = {};

            bool is_function = false;

            std::map<std::string, size_t> temporary_name_counters;
        };

        FlowState state_;

        core::Reporter& reporter_;
        TypeContext&    type_context_;

        std::map<std::string, size_t> flow_name_counters_;
    };

    explicit Implementation(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context, TypeContext& type_context)
        : source_tree_(source_tree)
        , reporter_(reporter)
        , expander_(source_tree, reporter, context)
        , context_(context)
        , type_context_(type_context)
    {}

    utility::Optional<utility::Owned<Flow>> segmentOrderedFile(std::filesystem::path const& file)// todo: reduce duplication with below (templates)
    {
        reporter_.trace(prefix, core::Location::project()) << "segment ordered file enter {file='" << file.string() << "'}";

        (void) source_tree_;// todo: use or remove

        utility::Optional<utility::Owned<est::Statement>> expanded = expander_.expandOrderedFile(file);
        if (!expanded.hasValue())
        {
            reporter_.trace(prefix, core::Location::project()) << "segment ordered file exit {file='" << file.string() << "', status=no-expand}";

            return std::nullopt;
        }

        utility::Owned<RET> ret = utility::makeOwned<RET>(reporter_, type_context_);

        utility::Owned<Flow> flow = ret->apply(**expanded, false, "Ordered");

        context_.print<Printer>(*flow, "bbt", file);
        context_.graph<Grapher>(*flow, "bbt", file);

        if (reporter_.isFailed())
        {
            reporter_.trace(prefix, core::Location::project()) << "segment ordered file exit {file='" << file.string() << "', status=fail}";

            return std::nullopt;
        }

        reporter_.trace(prefix, core::Location::project()) << "segment ordered file exit {file='" << file.string() << "', status=ok}";

        return flow;
    }

    utility::Optional<utility::Owned<Flows>> segmentUnorderedFile(std::filesystem::path const& file)
    {
        reporter_.trace(prefix, core::Location::project()) << "segment unordered file enter {file='" << file.string() << "'}";

        utility::Optional<utility::Owned<est::File>> expanded = expander_.expandUnorderedFile(file);
        if (!expanded.hasValue())
        {
            reporter_.trace(prefix, core::Location::project()) << "segment unordered file exit {file='" << file.string() << "', status=no-expand}";

            return std::nullopt;
        }

        utility::Owned<RET> ret = utility::makeOwned<RET>(reporter_, type_context_);

        utility::Owned<Flows> flows = ret->apply(**expanded);

        context_.print<Printer>(*flows, "bbt", file);
        context_.graph<Grapher>(*flows, "bbt", file);

        if (reporter_.isFailed())
        {
            reporter_.trace(prefix, core::Location::project()) << "segment unordered file exit {file='" << file.string() << "', status=fail}";

            return std::nullopt;
        }

        reporter_.trace(prefix, core::Location::project()) << "segment unordered file exit {file='" << file.string() << "', status=ok}";

        return flows;
    }

    utility::Optional<utility::Owned<Flow>> segmentDeclaration(std::string const& code, std::string const& id)
    {
        reporter_.trace(prefix, core::Location::project()) << "segment declaration enter {id=" << id << "}";

        utility::Optional<utility::Owned<est::Declaration>> expanded = expander_.expandDeclaration(code, id);
        if (!expanded.hasValue())
        {
            reporter_.trace(prefix, core::Location::project()) << "segment declaration exit {id=" << id << ", status=no-expand}";

            return std::nullopt;
        }

        utility::Owned<RET> ret = utility::makeOwned<RET>(reporter_, type_context_);

        utility::Owned<Flow> flow = ret->apply(**expanded);

        std::filesystem::path path = std::filesystem::path("core") / id;
        context_.print<Printer>(*flow, "bbt", path);
        context_.graph<Grapher>(*flow, "bbt", path);

        if (reporter_.isFailed())
        {
            reporter_.trace(prefix, core::Location::project()) << "segment declaration exit {id=" << id << ", status=fail}";

            return std::nullopt;
        }

        reporter_.trace(prefix, core::Location::project()) << "segment declaration exit {id=" << id << ", status=ok}";

        return flow;
    }

  private:
    sources::SourceTree& source_tree_;
    core::Reporter&      reporter_;
    est::Expander        expander_;
    core::Context&       context_;
    TypeContext&         type_context_;
};

ance::bbt::Segmenter::Segmenter(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context, TypeContext& type_context)
    : implementation_(utility::makeOwned<Implementation>(source_tree, reporter, context, type_context))
{}

ance::bbt::Segmenter::~Segmenter() = default;

ance::utility::Optional<ance::utility::Owned<ance::bbt::Flow>> ance::bbt::Segmenter::segmentOrderedFile(std::filesystem::path const& file)
{
    return implementation_->segmentOrderedFile(file);
}

ance::utility::Optional<ance::utility::Owned<ance::bbt::Flows>> ance::bbt::Segmenter::segmentUnorderedFile(std::filesystem::path const& file)
{
    return implementation_->segmentUnorderedFile(file);
}

ance::utility::Optional<ance::utility::Owned<ance::bbt::Flow>> ance::bbt::Segmenter::segmentDeclaration(std::string const& code, std::string const& id)
{
    return implementation_->segmentDeclaration(code, id);
}
