#include "Segmenter.h"

#include <expected>
#include <map>
#include <set>
#include <stack>
#include <vector>

#include "ance/bbt/Node.h"
#include "ance/core/Intrinsic.h"
#include "ance/core/Value.h"
#include "ance/est/Expander.h"
#include "ance/est/Node.h"

#include "Printer.h"
#include "Grapher.h"

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

            return utility::makeOwned<BasicBlock>(id, std::move(statements_), utility::makeOwned<ErrorLink>(core::Location::global()), location());
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

        [[nodiscard]] core::Location location() const
        {
            core::Location location = core::Location::global();

            if (!statements_.empty())
            {
                location = statements_[0]->location;

                for (auto const& statement : statements_) { location.extend(statement->location); }
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

                    for (auto& incoming : incoming_) { incoming->swap(std::ref(*this), std::ref(target)); }

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

                for (auto& next : outgoing) { next->incoming_.erase(this); }
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
                return utility::makeOwned<Return>(core::Location::global());// todo: should not be here but in the correct block maybe?
            }

            return utility::makeOwned<Jump>(*blocks[next_->index()], core::Location::global());
        }

        [[nodiscard]] std::set<BaseBB*> next() const override
        {
            std::set<BaseBB*> links;

            if (next_ != nullptr) links.emplace(next_);

            return links;
        }

        void swap(std::reference_wrapper<BaseBB> const original, std::reference_wrapper<BaseBB> const replacement) override
        {
            if (next_ == &original.get()) { next_ = &replacement.get(); }
        }

      private:
        BaseBB* next_ = nullptr;
    };

    class BranchBB final : public BaseBB
    {
      public:
        BranchBB()           = delete;
        ~BranchBB() override = default;

        BranchBB(Temporary const& condition, BaseBB& true_bb, BaseBB& false_bb) : condition_(condition), true_(true_bb), false_(false_bb)
        {
            true_.get().enter(*this);
            false_.get().enter(*this);
        }

        [[nodiscard]] utility::Owned<Link> createLink(utility::List<utility::Owned<BasicBlock>> const& blocks) override
        {
            return utility::makeOwned<Branch>(condition_, *blocks[true_.get().index()], *blocks[false_.get().index()], core::Location::global());
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
            if (&true_.get() == &original.get()) { true_ = replacement; }

            if (&false_.get() == &original.get()) { false_ = replacement; }
        }

      private:
        Temporary const&               condition_;
        std::reference_wrapper<BaseBB> true_;
        std::reference_wrapper<BaseBB> false_;
    };

    class RET final : public est::Visitor
    {
      public:
        using Visitor::visit;

        explicit RET(core::Reporter& reporter)
            : reporter_(reporter)
        {}
        ~RET() override = default;

        utility::Owned<UnorderedScope> apply(est::File const& file)
        {
            visit(file);

            return utility::makeOwned<UnorderedScope>(file.location); // todo: think about how / if to incorporate visitor here, probably a vector of flows in the visitor class
        }

        utility::Owned<Flow> apply(est::Statement const& statement)
        {
            assert(bbs_.empty());

            utility::Owned<SimpleBB> entry_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper   entry       = *entry_block;

            current_entry_bb_ = entry_block.get();
            current_exit_bb_  = current_entry_bb_;
            bbs_.emplace_back(std::move(entry_block));

            auto [statement_entry, statement_exit] = segment(statement);

            utility::Owned<SimpleBB>     exit_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper const exit       = *exit_block;

            link(entry, statement_entry);
            link(statement_exit, exit);

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

                for (auto& next : current.next())
                {
                    if (!next->isCreated()) { unconverted.emplace(*next); }
                }
            }

            for (size_t index = 0; index < converted.size(); index++)
            {
                BaseBB& current = converted[index].get();

                utility::Owned<Link> link = current.createLink(basic_blocks);
                basic_blocks[index]->link = std::move(link);
            }

            BasicBlock& first_block = *basic_blocks[current_entry.get().index()];

            return utility::makeOwned<Flow>(std::move(basic_blocks), first_block, statement.location);
        }

        std::reference_wrapper<BaseBB> simplify(std::reference_wrapper<BaseBB> entry)
        {
            for (auto& block : bbs_) { block.get()->prune(); }

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

                if (&current == &current_entry.get()) { current_entry = *result; }

                for (auto& next_block : next)
                {
                    if (!simplified.contains(next_block)) { to_simplify.emplace(*next_block); }
                }
            }

            bool           has_unreachable_code       = false;
            core::Location first_unreachable_location = core::Location::global();

            for (auto& block : bbs_)
            {
                if (block.get()->hasCode() && !simplified.contains(block.get()))
                {
                    has_unreachable_code       = true;
                    first_unreachable_location = core::Location::getFirst(first_unreachable_location, block.get()->location());
                }
            }

            if (has_unreachable_code) { reporter_.warning("Unreachable code", first_unreachable_location); }

            return current_entry;
        }

        static void link(std::reference_wrapper<SimpleBB> const from, std::reference_wrapper<BaseBB> const to)
        {
            assert(&from.get() != &to.get());

            from.get().link(to.get());
        }

        std::pair<std::reference_wrapper<SimpleBB>, std::reference_wrapper<SimpleBB>> segment(est::Statement const& statement)
        {
            SimpleBB* previous_entry = current_entry_bb_;
            SimpleBB* previous_exit  = current_exit_bb_;

            current_entry_bb_ = nullptr;
            current_exit_bb_  = nullptr;

            visit(statement);

            assert(current_entry_bb_ != nullptr);
            assert(current_exit_bb_ != nullptr);

            std::pair<SimpleBB&, SimpleBB&> const result = {*current_entry_bb_, *current_exit_bb_};

            current_entry_bb_ = previous_entry;
            current_exit_bb_  = previous_exit;

            return result;
        }

        std::pair<std::reference_wrapper<SimpleBB>, std::reference_wrapper<SimpleBB>> segment(est::Expression const& expression, Temporary const& destination)
        {
            SimpleBB*        previous_entry       = current_entry_bb_;
            SimpleBB*        previous_exit        = current_exit_bb_;
            Temporary const* previous_destination = current_destination_;

            current_entry_bb_    = nullptr;
            current_exit_bb_     = nullptr;
            current_destination_ = &destination;

            assert(current_destination_ != nullptr);

            visit(expression);

            assert(current_entry_bb_ != nullptr);
            assert(current_exit_bb_ != nullptr);

            std::pair<SimpleBB&, SimpleBB&> const result = {*current_entry_bb_, *current_exit_bb_};

            current_entry_bb_    = previous_entry;
            current_exit_bb_     = previous_exit;
            current_destination_ = previous_destination;

            return result;
        }

        [[nodiscard]] Temporary const& destination() const
        {
            assert(current_destination_ != nullptr);
            return *current_destination_;
        }

        template<typename T, typename... Args>
        static std::reference_wrapper<SimpleBB> addBlock(utility::List<utility::Owned<BaseBB>>& blocks, Args&&... args)
        {
            utility::Owned<SimpleBB>     block = utility::makeOwned<SimpleBB>(utility::makeOwned<T>(std::forward<Args>(args)...));
            std::reference_wrapper const ref   = *block;
            blocks.emplace_back(std::move(block));
            return ref;
        }

        template<typename T, typename... Args>
        static std::tuple<std::reference_wrapper<SimpleBB>, std::reference_wrapper<T>> addBlockAndGetInner(utility::List<utility::Owned<BaseBB>>& blocks,
                                                                                                           Args&&... args)
        {
            utility::Owned<T>               inner_node = utility::makeOwned<T>(std::forward<Args>(args)...);
            std::reference_wrapper<T> const inner_ref  = *inner_node;

            utility::Owned<SimpleBB>     block = utility::makeOwned<SimpleBB>(std::move(inner_node));
            std::reference_wrapper const ref   = *block;

            blocks.emplace_back(std::move(block));

            return {ref, inner_ref};
        }

        static std::reference_wrapper<SimpleBB> addEmptyBlock(utility::List<utility::Owned<BaseBB>>& blocks)
        {
            utility::Owned<SimpleBB>     block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper const ref   = *block;
            blocks.emplace_back(std::move(block));
            return ref;
        }

        void setResult(utility::List<utility::Owned<BaseBB>>&& blocks, SimpleBB& entry, SimpleBB& exit)
        {
            bbs_.insert(bbs_.end(), std::make_move_iterator(blocks.begin()), std::make_move_iterator(blocks.end()));

            current_entry_bb_ = &entry;
            current_exit_bb_  = &exit;
        }

        void visit(est::File const&) override
        {
            // See the respective apply method.
        }

        void visit(est::ErrorStatement const& error_statement) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry = addEmptyBlock(blocks);

            std::reference_wrapper const error = addBlock<ErrorStatement>(blocks, error_statement.location);
            link(entry, error);

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(error, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::Pass const& pass_statement) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const pass = addBlock<Pass>(blocks, pass_statement.location);

            setResult(std::move(blocks), pass, pass);
        }

        void visit(est::Block const& block) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry = addEmptyBlock(blocks);

            auto [scope_enter, enter] = addBlockAndGetInner<OrderedScopeEnter>(blocks, block.location);
            scopes_.emplace_back(&enter.get());
            link(entry, scope_enter);
            std::reference_wrapper current = scope_enter;

            for (auto& statement : block.statements)
            {
                auto [statement_entry, statement_exit] = segment(*statement);

                link(current, statement_entry);
                current = statement_exit;
            }

            std::reference_wrapper const scope_exit = addBlock<OrderedScopeExit>(blocks, enter, block.location);
            scopes_.pop_back();
            link(current, scope_exit);

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(scope_exit, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::Independent const& independent) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;
            std::reference_wrapper const          entry = addEmptyBlock(blocks);

            auto [temporary, value] = addBlockAndGetInner<Temporary>(blocks, independent.location);
            link(entry, temporary);

            auto [expression_entry, expression_exit] = segment(*independent.expression, value.get());
            link(temporary, expression_entry);

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(expression_exit, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::Write const& assignment) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry = addEmptyBlock(blocks);

            // todo: think of something to make this code less convoluted, maybe some nice builder or whatever

            auto [temporary_target, target] = addBlockAndGetInner<Temporary>(blocks, assignment.target->location);
            link(entry, temporary_target);

            auto [target_expression_entry, target_expression_exit] = segment(*assignment.target, target.get());
            link(temporary_target, target_expression_entry);

            auto [temporary_value, value] = addBlockAndGetInner<Temporary>(blocks, assignment.value->location);
            link(target_expression_exit, temporary_value);

            auto [value_expression_entry, value_expression_exit] = segment(*assignment.value, value.get());
            link(temporary_value, value_expression_entry);

            std::reference_wrapper inner = addBlock<Store>(blocks, target.get(), value.get(), assignment.location);
            link(value_expression_exit, inner);

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(inner, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::If const& if_statement) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry = addEmptyBlock(blocks);

            auto [temporary, value] = addBlockAndGetInner<Temporary>(blocks, if_statement.condition->location);
            link(entry, temporary);

            auto [condition_entry, condition_exit] = segment(*if_statement.condition, value.get());
            link(temporary, condition_entry);

            auto [true_entry, true_exit]   = segment(*if_statement.true_block);
            auto [false_entry, false_exit] = segment(*if_statement.false_block);

            utility::Owned<BranchBB> branch_block = utility::makeOwned<BranchBB>(value.get(), true_entry, false_entry);
            std::reference_wrapper   branch       = *branch_block;
            blocks.emplace_back(std::move(branch_block));
            link(condition_exit, branch);

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(true_exit, exit);
            link(false_exit, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::Loop const& loop) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry = addEmptyBlock(blocks);
            std::reference_wrapper const exit  = addEmptyBlock(blocks);

            loops_.emplace_back(Loop {.entry = entry, .exit = exit, .scope_depth = scopes_.size()});

            auto [loop_entry, loop_exit] = segment(*loop.body);

            loops_.pop_back();

            link(entry, loop_entry);
            link(loop_exit, entry);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::Break const& break_statement) override
        {
            if (loops_.empty()) { reporter_.error("Break statement outside of loop", break_statement.location); }

            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry   = addEmptyBlock(blocks);
            std::reference_wrapper       current = entry;

            size_t const target_depth = loops_.back().scope_depth;
            for (size_t i = scopes_.size(); i > target_depth; i--)
            {
                std::reference_wrapper const scope_exit = addBlock<OrderedScopeExit>(blocks, *scopes_[i - 1], break_statement.location);
                link(current, scope_exit);
                current = scope_exit;
            }

            link(current, loops_.back().exit);

            std::reference_wrapper const exit = addEmptyBlock(blocks);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::Continue const& continue_statement) override
        {
            if (loops_.empty()) { reporter_.error("Continue statement outside of loop", continue_statement.location); }

            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry   = addEmptyBlock(blocks);
            std::reference_wrapper       current = entry;

            size_t const target_depth = loops_.back().scope_depth;
            for (size_t i = scopes_.size(); i > target_depth; i--)
            {
                std::reference_wrapper const scope_exit = addBlock<OrderedScopeExit>(blocks, *scopes_[i - 1], continue_statement.location);
                link(current, scope_exit);
                current = scope_exit;
            }

            link(current, loops_.back().entry);

            std::reference_wrapper const exit = addEmptyBlock(blocks);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::Temporary const& temporary) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry = addEmptyBlock(blocks);

            auto [t, value] = addBlockAndGetInner<Temporary>(blocks, temporary.location);
            temporaries_.emplace(&temporary, &value.get());
            link(entry, t);

            std::reference_wrapper incoming = t;
            if (temporary.definition.hasValue())
            {
                auto [definition_entry, definition_exit] = segment(**temporary.definition, value.get());
                link(incoming, definition_entry);
                incoming = definition_exit;
            }

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(incoming, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::WriteTemporary const& write) override
        {
            Temporary const& destination = *temporaries_.at(&write.temporary);

            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry = addEmptyBlock(blocks);

            auto [expression_entry, expression_exit] = segment(*write.value, destination);
            link(entry, expression_entry);

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(expression_exit, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::ErrorExpression const& error) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const inner = addBlock<ErrorStatement>(blocks, error.location);

            setResult(std::move(blocks), inner, inner);
        }

        void visit(est::Intrinsic const& intrinsic) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry    = addEmptyBlock(blocks);
            std::reference_wrapper       incoming = entry;

            utility::List<std::reference_wrapper<Temporary const>> arguments;
            for (auto const& index : intrinsic.arguments)
            {
                auto [argument, value] = addBlockAndGetInner<Temporary>(blocks, index->location);
                link(incoming, argument);
                incoming = argument;

                auto [expression_entry, expression_exit] = segment(*index, value.get());
                link(incoming, expression_entry);
                incoming = expression_exit;

                arguments.emplace_back(value.get());
            }

            std::reference_wrapper const inner = addBlock<Intrinsic>(blocks, intrinsic.intrinsic, std::move(arguments), destination(), intrinsic.location);
            link(incoming, inner);

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(inner, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::Call const& call) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry    = addEmptyBlock(blocks);

            auto [called_temporary, called] = addBlockAndGetInner<Temporary>(blocks, call.called->location);
            link(entry, called_temporary);

            auto [called_entry, called_exit] = segment(*call.called, called.get());
            link(called_temporary, called_entry);

            std::reference_wrapper incoming = called_exit;

            utility::List<std::reference_wrapper<Temporary const>> arguments;
            for (auto const& index : call.arguments)
            {
                auto [argument, value] = addBlockAndGetInner<Temporary>(blocks, index->location);
                link(incoming, argument);
                incoming = argument;

                auto [expression_entry, expression_exit] = segment(*index, value.get());
                link(incoming, expression_entry);
                incoming = expression_exit;

                arguments.emplace_back(value.get());
            }

            std::reference_wrapper inner = addBlock<Call>(blocks, called, std::move(arguments), destination(), call.location);
            link(incoming, inner);

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(inner, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::Read const& access) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry = addEmptyBlock(blocks);

            auto [temporary, target] = addBlockAndGetInner<Temporary>(blocks, access.target->location);
            link(entry, temporary);

            auto [expression_entry, expression_exit] = segment(*access.target, target.get());
            link(temporary, expression_entry);

            std::reference_wrapper inner = addBlock<Read>(blocks, target.get(), destination(), access.location);
            link(expression_exit, inner);

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(inner, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::Literal const& literal) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const inner = addBlock<Constant>(blocks, literal.value->clone(), destination(), literal.location);

            setResult(std::move(blocks), inner, inner);
        }

        void visit(est::Here const& here) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const inner = addBlock<Constant>(blocks, core::Value::makeLocation(here.location), destination(), here.location);

            setResult(std::move(blocks), inner, inner);
        }

        void visit(est::UnaryOperation const& unary_operation) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry = addEmptyBlock(blocks);

            auto [temporary, value] = addBlockAndGetInner<Temporary>(blocks, unary_operation.operand->location);
            link(entry, temporary);

            auto [expression_entry, expression_exit] = segment(*unary_operation.operand, value.get());
            link(temporary, expression_entry);

            std::reference_wrapper const inner = addBlock<UnaryOperation>(blocks, unary_operation.op, value.get(), destination(), unary_operation.location);
            link(expression_exit, inner);

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(inner, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::ReadTemporary const& read_temporary) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry = addEmptyBlock(blocks);

            std::reference_wrapper const inner =
                addBlock<CopyTemporary>(blocks, destination(), *temporaries_.at(&read_temporary.temporary), read_temporary.location);
            link(entry, inner);

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(inner, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::TypeOf const& type_of) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry = addEmptyBlock(blocks);

            auto [temporary, value] = addBlockAndGetInner<Temporary>(blocks, type_of.expression->location);
            link(entry, temporary);

            auto [expression_entry, expression_exit] = segment(*type_of.expression, value.get());
            link(temporary, expression_entry);

            std::reference_wrapper const inner = addBlock<TypeOf>(blocks, value.get(), destination(), type_of.location);
            link(expression_exit, inner);

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(inner, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::IdentifierCapture const& identifier_capture) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const inner = addBlock<Constant>(blocks, core::Value::makeIdentifier(identifier_capture.identifier), destination(), identifier_capture.location);

            setResult(std::move(blocks), inner, inner);
        }

        void visit(est::CurrentScope const& current_scope) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const inner = addBlock<CurrentScope>(blocks, destination(), current_scope.location);

            setResult(std::move(blocks), inner, inner);
        }

        struct Loop
        {
            std::reference_wrapper<SimpleBB> entry;
            std::reference_wrapper<SimpleBB> exit;
            size_t                           scope_depth = 0;
        };

      private:
        utility::List<utility::Owned<BaseBB>> bbs_;

        SimpleBB*        current_entry_bb_    = nullptr;
        SimpleBB*        current_exit_bb_     = nullptr;
        Temporary const* current_destination_ = nullptr;

        std::vector<Loop>   loops_  = {};
        std::vector<OrderedScopeEnter const*> scopes_ = {};

        core::Reporter& reporter_;

        std::map<est::Temporary const*, Temporary const*> temporaries_;
    };
    
    explicit Implementation(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
        : source_tree_(source_tree)
        , reporter_(reporter)
        , expander_(source_tree, reporter, context)
        , context_(context)
    {}

    utility::Optional<utility::Owned<Flow>> segmentOrderedFile(std::filesystem::path const& file, std::ostream& out)
    {
        utility::Optional<utility::Owned<est::Statement>> expanded = expander_.expandOrderedFile(file, out);
        if (!expanded.hasValue()) return std::nullopt;

        utility::Owned<RET> ret = utility::makeOwned<RET>(reporter_);

        utility::Owned<Flow> flow = ret->apply(**expanded);
        if (reporter_.checkForFail(source_tree_, out))
            return std::nullopt;

        context_.print<Printer>(*flow, "bbt");
        context_.graph<Grapher>(*flow, "bbt");

        return flow;
    }

    utility::Optional<utility::Owned<UnorderedScope>> segmentUnorderedFile(std::filesystem::path const& file, std::ostream& out)
    {
        utility::Optional<utility::Owned<est::File>> expanded = expander_.expandUnorderedFile(file, out);
        if (!expanded.hasValue()) return std::nullopt;

        utility::Owned<RET> ret = utility::makeOwned<RET>(reporter_);

        utility::Owned<UnorderedScope> scope = ret->apply(**expanded);
        if (reporter_.checkForFail(source_tree_, out))
            return std::nullopt;

        context_.print<Printer>(*scope, "bbt");
        context_.graph<Grapher>(*scope, "bbt");

        return scope;
    }

  private:
    sources::SourceTree& source_tree_;
    core::Reporter& reporter_;
    est::Expander   expander_;
    core::Context& context_;
};

ance::bbt::Segmenter::Segmenter(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
    : implementation_(utility::makeOwned<Implementation>(source_tree, reporter, context))
{}

ance::bbt::Segmenter::~Segmenter() = default;

ance::utility::Optional<ance::utility::Owned<ance::bbt::Flow>> ance::bbt::Segmenter::segmentOrderedFile(std::filesystem::path const& file,
    std::ostream& out)
{
    return implementation_->segmentOrderedFile(file, out);
}

ance::utility::Optional<ance::utility::Owned<ance::bbt::UnorderedScope>> ance::bbt::Segmenter::segmentUnorderedFile(std::filesystem::path const& file,
                                                                                                                    std::ostream&                out)
{
    return implementation_->segmentUnorderedFile(file, out);
}
