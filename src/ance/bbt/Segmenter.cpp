#include "Segmenter.h"

#include <expected>
#include <map>
#include <set>
#include <stack>
#include <vector>

#include "ance/bbt/Node.h"
#include "ance/core/Function.h"
#include "ance/core/Intrinsic.h"
#include "ance/core/Scope.h"
#include "ance/est/Node.h"

struct ance::bbt::Segmenter::Implementation
{
    class Declarations final : public est::Visitor
    {
      public:
        using Visitor::visit;

        Declarations()           = default;
        ~Declarations() override = default;

        static std::set<core::Identifier> get(est::Block const& block)
        {
            Declarations declarations;
            declarations.visit(block);

            return declarations.declarations;
        }

      protected:
        void visit(est::ErrorStatement const&) override {}

        void visit(est::Pass const&) override {}

        void visit(est::Block const& block) override
        {
            depth++;

            if (depth <= MAX_DEPTH)
            {
                for (auto& statement : block.statements) { visit(*statement); }
            }

            depth--;
        }

        void visit(est::Independent const& independent) override
        {
            visit(*independent.expression);
        }

        void visit(est::Let const& let) override
        {
            declarations.insert(let.identifier);
        }

        void visit(est::Assignment const& assignment) override
        {
            visit(*assignment.value);
        }

        void visit(est::If const& if_statement) override
        {
            visit(*if_statement.condition);
            visit(*if_statement.true_block);
            visit(*if_statement.false_block);
        }

        void visit(est::Loop const& loop) override
        {
            visit(*loop.body);
        }

        void visit(est::Break const&) override {}
        void visit(est::Continue const&) override {}

        void visit(est::Temporary const& temporary) override
        {
            if (temporary.definition.hasValue()) { visit(**temporary.definition); }
        }

        void visit(est::WriteTemporary const& write_temporary) override
        {
            visit(*write_temporary.value);
        }

        void visit(est::ErrorExpression const&) override {}

        void visit(est::Intrinsic const& intrinsic) override
        {
            for (auto& argument : intrinsic.arguments) { visit(*argument); }
        }

        void visit(est::Call const& call) override
        {
            for (auto& argument : call.arguments) { visit(*argument); }
        }

        void visit(est::Access const&) override {}
        void visit(est::Literal const&) override {}

        void visit(est::UnaryOperation const& unary_operation) override
        {
            visit(*unary_operation.operand);
        }

        void visit(est::ReadTemporary const&) override {}

        void visit(est::TypeOf const&) override {}

      private:
        std::set<core::Identifier> declarations = {};
        size_t                     depth        = 0;

        constexpr static size_t MAX_DEPTH = 1;
    };

    class Scope
    {
      protected:
        Scope(Scope const* parent, ScopeEnter& enter) : parent_(parent), scope_enter_(enter)
        {
        }

      public:
        virtual ~Scope() = default;

        core::Scope& scope() const
        {
            return *scope_enter_.scope;
        }

        core::Variable const& declare(core::Identifier const& identifier, core::Location const& location)
        {
            core::Variable const& variable = scope().addVariable(identifier, location);

            onDeclare(variable);

            return variable;
        }

        enum class Error
        {
            Unknown,
            Blocked
        };

        [[nodiscard]] std::expected<std::reference_wrapper<core::Variable const>, Error> find(core::Identifier const& identifier) const
        {
            // todo: when using resolving for intrinsics/functions, instead of adding a global scope, the find method should take a list of providers to use when top of the scope chain is reached
            // todo: when adding the functions then also add a Value base class for function and variable and scopes should hold Values only
            // todo: essentially resolving of functions / values should use the same logic - a resolve intrinsic, and intrinsics are placed inside function when they should be part of resolution
            // todo: the nodes should hold the correct type - meaning that this type checking is done in the resolver

            return onFind(identifier).or_else([&](Error const error) -> std::expected<std::reference_wrapper<core::Variable const>, Error> {
                if (error == Error::Unknown && parent_ != nullptr) { return parent_->find(identifier); }

                return std::unexpected(error);
            });
        }

        [[nodiscard]] core::Variable const* expect(core::Identifier const& identifier, core::Reporter& reporter) const
        {
            std::expected<std::reference_wrapper<core::Variable const>, Error> const variable = find(identifier);

            if (variable.has_value()) { return &variable.value().get(); }

            switch (variable.error())
            {
                case Error::Unknown:
                    reporter.error("Cannot resolve name '" + identifier + "'", identifier.location());
                    break;

                case Error::Blocked:
                    reporter.error("Name '" + identifier + "' blocked by later declaration in scope", identifier.location());
                    break;
            }

            return nullptr;
        }

      protected:
        virtual void                                                                             onDeclare(core::Variable const& variable)        = 0;
        [[nodiscard]] virtual std::expected<std::reference_wrapper<core::Variable const>, Error> onFind(core::Identifier const& identifier) const = 0;

      private:
        Scope const*                parent_;
        ScopeEnter&                 scope_enter_;
    };

    class OrderedScope final : public Scope
    {
      public:
        OrderedScope(std::set<core::Identifier> declarations, Scope const* parent, ScopeEnter& scope_enter)
            : Scope(parent, scope_enter)
            , declarations_(std::move(declarations))
        {}

        ~OrderedScope() override = default;

      protected:
        void onDeclare(core::Variable const& variable) override
        {
            active_variables_.emplace(variable.identifier(), std::cref(variable));
        }

        [[nodiscard]] std::expected<std::reference_wrapper<core::Variable const>, Error> onFind(core::Identifier const& identifier) const override
        {
            if (active_variables_.contains(identifier)) { return active_variables_.at(identifier); }

            if (declarations_.contains(identifier)) { return std::unexpected(Error::Blocked); }

            return std::unexpected(Error::Unknown);
        }

      private:
        std::set<core::Identifier> const declarations_;

        std::map<core::Identifier, std::reference_wrapper<core::Variable const>> active_variables_ = {};
    };

    static utility::Owned<core::Scope> createScope(utility::Optional<utility::Owned<core::Scope>>& parent)
    {
        if (parent.hasValue()) { return (*parent)->createChild(); }

        return utility::makeOwned<core::Scope>();
    }

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

        explicit RET(core::Reporter& reporter, std::map<core::Identifier, std::reference_wrapper<core::Function const>> const& functions)
            : reporter_(reporter)
            , functions_(functions)
        {}
        ~RET() override = default;

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

        [[nodiscard]] Scope* scope() const
        {
            if (scopes_.empty()) return nullptr;

            return scopes_.back();
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

            utility::Optional<utility::Owned<core::Scope>> owned_scope;

            if (scopes_.empty()) { owned_scope = utility::makeOwned<core::Scope>(); }
            else { owned_scope = scopes_.back()->scope().createChild(); }

            core::Scope const& scope = **owned_scope;

            auto [scope_enter, enter] = addBlockAndGetInner<ScopeEnter>(blocks, std::move(owned_scope.value()), block.location);
            utility::Owned<Scope>        scope_representation =
                utility::makeOwned<OrderedScope>(Declarations::get(block), scopes_.empty() ? nullptr : scopes_.back(), enter.get());
            scopes_.emplace_back(scope_representation.get());
            link(entry, scope_enter);
            std::reference_wrapper current = scope_enter;

            for (auto& statement : block.statements)
            {
                auto [statement_entry, statement_exit] = segment(*statement);

                link(current, statement_entry);
                current = statement_exit;
            }

            std::reference_wrapper const scope_exit = addBlock<ScopeExit>(blocks, scope, block.location);
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

        void visit(est::Let const& let) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry    = addEmptyBlock(blocks);
            std::reference_wrapper       incoming = entry;

            Temporary const* type;
            {
                auto [temporary, temporary_node] = addBlockAndGetInner<Temporary>(blocks, let.type->location);
                link(incoming, temporary);
                incoming = temporary;
                type     = &temporary_node.get();

                auto [expression_entry, expression_exit] = segment(*let.type, *type);
                link(incoming, expression_entry);
                incoming = expression_exit;
            }

            Temporary const* value = nullptr;
            if (let.value.hasValue())
            {
                auto [temporary, temporary_node] = addBlockAndGetInner<Temporary>(blocks, (*let.value)->location);
                link(incoming, temporary);
                incoming = temporary;
                value    = &temporary_node.get();

                auto [expression_entry, expression_exit] = segment(**let.value, *value);
                link(incoming, expression_entry);
                incoming = expression_exit;
            }

            core::Variable const&        variable = scope()->declare(let.identifier, let.location);
            std::reference_wrapper const declare  = addBlock<Declare>(blocks, variable, *type, value, let.location);
            link(incoming, declare);

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(declare, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::Assignment const& assignment) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry = addEmptyBlock(blocks);

            auto [temporary, value] = addBlockAndGetInner<Temporary>(blocks, assignment.value->location);
            link(entry, temporary);

            auto [expression_entry, expression_exit] = segment(*assignment.value, value.get());
            link(temporary, expression_entry);

            std::reference_wrapper inner    = expression_exit;
            core::Variable const*  variable = scope()->expect(assignment.identifier, reporter_);
            if (variable != nullptr)
            {
                inner = addBlock<Store>(blocks, *variable, value.get(), assignment.location);
                link(expression_exit, inner);
            }
            else
            {
                inner = addBlock<ErrorStatement>(blocks, assignment.location);
                link(expression_exit, inner);
            }

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
                std::reference_wrapper const scope_exit = addBlock<ScopeExit>(blocks, scopes_[i - 1]->scope(), break_statement.location);
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
                std::reference_wrapper const scope_exit = addBlock<ScopeExit>(blocks, scopes_[i - 1]->scope(), continue_statement.location);
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
            std::reference_wrapper       incoming = entry;

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

            std::reference_wrapper inner = incoming;
            if (functions_.contains(call.identifier))
            {
                inner = addBlock<Call>(blocks, functions_.at(call.identifier).get(), std::move(arguments), destination(), call.location);
                link(incoming, inner);
            }
            else
            {
                reporter_.error("Unknown function '" + call.identifier + "'", call.identifier.location());

                inner = addBlock<ErrorStatement>(blocks, call.location);
                link(incoming, inner);
            }

            std::reference_wrapper const exit = addEmptyBlock(blocks);
            link(inner, exit);

            setResult(std::move(blocks), entry, exit);
        }

        void visit(est::Access const& access) override
        {
            utility::List<utility::Owned<BaseBB>> blocks;

            std::reference_wrapper const entry = addEmptyBlock(blocks);
            std::reference_wrapper inner = entry;

            core::Variable const* variable = scope()->expect(access.identifier, reporter_);
            if (variable != nullptr)
            {
                inner = addBlock<Read>(blocks, *variable, destination(), access.location);
                link(entry, inner);
            }
            else
            {
                inner = addBlock<ErrorStatement>(blocks, access.location);
                link(entry, inner);
            }

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
        std::vector<Scope*> scopes_ = {};

        core::Reporter& reporter_;

        std::map<est::Temporary const*, Temporary const*> temporaries_;

        std::map<core::Identifier, std::reference_wrapper<core::Function const>> const& functions_;
    };

    explicit Implementation(core::Reporter& reporter) : reporter_(reporter) {}

    void add(core::Function const& function)
    {
        functions_.emplace(function.name(), std::cref(function));
    }

    utility::Owned<Flow> segment(est::Statement const& statement)
    {
        utility::Owned<RET> ret = utility::makeOwned<RET>(reporter_, functions_);

        return ret->apply(statement);
    }

  private:
    core::Reporter& reporter_;

    std::map<core::Identifier, std::reference_wrapper<core::Function const>> functions_ = {};
};

ance::bbt::Segmenter::Segmenter(core::Reporter& reporter) : implementation_(utility::makeOwned<Implementation>(reporter)) {}

ance::bbt::Segmenter::~Segmenter() = default;

void ance::bbt::Segmenter::add(core::Function const& function)
{
    implementation_->add(function);
}

ance::utility::Owned<ance::bbt::Flow> ance::bbt::Segmenter::segment(est::Statement const& statement)
{
    return implementation_->segment(statement);
}
