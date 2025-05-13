#include "Segmenter.h"

#include <map>
#include <set>
#include <stack>

#include "ance/bbt/Node.h"
#include "ance/ret/Node.h"

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

                // We can only simplify if this is the only block entering the next (real) block, or if this block is unnecessary, we can simplify.

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

        BranchBB(utility::Owned<Expression> condition, BaseBB& true_bb, BaseBB& false_bb) : condition_(std::move(condition)), true_(true_bb), false_(false_bb)
        {
            true_.get().enter(*this);
            false_.get().enter(*this);
        }

        [[nodiscard]] utility::Owned<Link> createLink(utility::List<utility::Owned<BasicBlock>> const& blocks) override
        {
            return utility::makeOwned<Branch>(std::move(condition_), *blocks[true_.get().index()], *blocks[false_.get().index()], core::Location::global());
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
        utility::Owned<Expression> condition_;
        std::reference_wrapper<BaseBB>                    true_;
        std::reference_wrapper<BaseBB>                    false_;
    };

    class RET final : public ret::Visitor
    {
      public:
        using Visitor::visit;

        explicit RET(core::Reporter& reporter) : reporter_(reporter) {}
        ~RET() override = default;

        utility::Owned<Flow> apply(ret::Statement const& statement)
        {
            assert(bbs_.empty());

            utility::Owned<SimpleBB>     entry_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper       entry       = *entry_block;

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
            std::set<BaseBB*> simplified;
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

            bool has_unreachable_code = false;
            core::Location first_unreachable_location = core::Location::global();

            for (auto& block : bbs_)
            {
                if (block.get()->hasCode() && !simplified.contains(block.get()))
                {
                    has_unreachable_code = true;
                    first_unreachable_location = core::Location::getFirst(first_unreachable_location, block.get()->location());
                }
            }

            if (has_unreachable_code)
            {
                reporter_.warning("Unreachable code", first_unreachable_location);
            }

            return current_entry;
        }

        static void link(std::reference_wrapper<SimpleBB> const from, std::reference_wrapper<BaseBB> const to)
        {
            assert(&from.get() != &to.get());

            from.get().link(to.get());
        }

        std::pair<std::reference_wrapper<SimpleBB>, std::reference_wrapper<SimpleBB>> segment(ret::Statement const& statement)
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

        utility::Owned<Expression> segment(ret::Expression const& expression)
        {
            visit(expression);

            assert(segmented_expression_.hasValue());

            utility::Owned<Expression> result = std::move(*segmented_expression_);
            segmented_expression_                  = std::nullopt;

            return result;
        }

        void setResult(utility::Owned<Expression> expression)
        {
            assert(!segmented_expression_.hasValue());

            segmented_expression_ = std::move(expression);
        }

        void setResult(utility::List<utility::Owned<BaseBB>>&& blocks, SimpleBB& entry, SimpleBB& exit)
        {
            bbs_.insert(bbs_.end(), std::make_move_iterator(blocks.begin()), std::make_move_iterator(blocks.end()));

            current_entry_bb_ = &entry;
            current_exit_bb_  = &exit;
        }

        void setResult(utility::Owned<Statement>&& statement)
        {
            utility::Owned<SimpleBB> entry_block = utility::makeOwned<SimpleBB>(std::move(statement));
            SimpleBB&                entry       = *entry_block;

            utility::List<utility::Owned<BaseBB>> blocks;
            blocks.emplace_back(std::move(entry_block));

            setResult(std::move(blocks), entry, entry);
        }

        void visit(ret::ErrorStatement const& error_statement) override
        {
            setResult(utility::makeOwned<ErrorStatement>(error_statement.location));
        }

        void visit(ret::Block const& block) override
        {
            utility::Owned<SimpleBB>     entry_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper const entry       = *entry_block;

            std::reference_wrapper current = entry;

            for (auto& statement : block.statements)
            {
                auto [statement_entry, statement_exit] = segment(*statement);

                link(current, statement_entry);
                current = statement_exit;
            }

            utility::Owned<SimpleBB> exit_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper   exit       = *exit_block;

            link(current, exit);

            utility::List<utility::Owned<BaseBB>> blocks;
            blocks.emplace_back(std::move(entry_block));
            blocks.emplace_back(std::move(exit_block));
            setResult(std::move(blocks), entry, exit);
        }

        void visit(ret::Independent const& independent) override
        {
            utility::Owned<Expression> expression = segment(*independent.expression);

            setResult(utility::makeOwned<Independent>(std::move(expression), independent.location));
        }

        void visit(ret::Let const& let) override
        {
            utility::Optional<utility::Owned<Expression>> value;

            if (let.value.hasValue())
            {
                value = segment(**let.value);
            }

            setResult(utility::makeOwned<Let>(let.variable, std::move(value), let.location));
        }

        void visit(ret::Assignment const& assignment) override
        {
            utility::Owned<Expression> value = segment(*assignment.value);

            setResult(utility::makeOwned<Assignment>(assignment.variable, std::move(value), assignment.location));
        }

        void visit(ret::If const& if_statement) override
        {
            utility::Owned<SimpleBB>     entry_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper const entry       = *entry_block;

            utility::Owned<Expression> condition = segment(*if_statement.condition);

            auto [true_entry, true_exit]   = segment(*if_statement.true_block);
            auto [false_entry, false_exit] = segment(*if_statement.false_block);

            utility::Owned<BranchBB> branch_block = utility::makeOwned<BranchBB>(std::move(condition), true_entry, false_entry);
            std::reference_wrapper   branch       = *branch_block;

            utility::Owned<SimpleBB> exit_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper   exit       = *exit_block;

            link(entry, branch);
            link(true_exit, exit);
            link(false_exit, exit);

            utility::List<utility::Owned<BaseBB>> blocks;
            blocks.emplace_back(std::move(entry_block));
            blocks.emplace_back(std::move(branch_block));
            blocks.emplace_back(std::move(exit_block));
            setResult(std::move(blocks), entry, exit);
        }

        void visit(ret::Loop const& loop) override
        {
            utility::Owned<SimpleBB>     entry_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper const entry       = *entry_block;

            utility::Owned<SimpleBB>     exit_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper const exit       = *exit_block;

            loops_.emplace(Loop {.entry = entry, .exit = exit});

            auto [loop_entry, loop_exit] = segment(*loop.body);

            loops_.pop();

            link(entry, loop_entry);
            link(loop_exit, entry);

            utility::List<utility::Owned<BaseBB>> blocks;
            blocks.emplace_back(std::move(entry_block));
            blocks.emplace_back(std::move(exit_block));
            setResult(std::move(blocks), entry, exit);
        }

        void visit(ret::Break const& break_statement) override
        {
            if (loops_.empty()) { reporter_.error("Break statement outside of loop", break_statement.location); }

            utility::Owned<SimpleBB>     entry_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper const entry       = *entry_block;

            utility::Owned<SimpleBB>     exit_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper const exit       = *exit_block;

            link(entry, loops_.top().exit);

            utility::List<utility::Owned<BaseBB>> blocks;
            blocks.emplace_back(std::move(entry_block));
            blocks.emplace_back(std::move(exit_block));
            setResult(std::move(blocks), entry, exit);
        }

        void visit(ret::Continue const& continue_statement) override
        {
            if (loops_.empty()) { reporter_.error("Continue statement outside of loop", continue_statement.location); }

            utility::Owned<SimpleBB>     entry_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper const entry       = *entry_block;

            utility::Owned<SimpleBB>     exit_block = utility::makeOwned<SimpleBB>();
            std::reference_wrapper const exit       = *exit_block;

            link(entry, loops_.top().entry);

            utility::List<utility::Owned<BaseBB>> blocks;
            blocks.emplace_back(std::move(entry_block));
            blocks.emplace_back(std::move(exit_block));
            setResult(std::move(blocks), entry, exit);
        }

        void visit(ret::ErrorExpression const& error_expression) override
        {
            setResult(utility::makeOwned<ErrorExpression>(error_expression.location));
        }

        void visit(ret::Intrinsic const& intrinsic) override
        {
            utility::List<utility::Owned<Expression>> arguments;
            for (auto& argument : intrinsic.arguments)
            {
                arguments.emplace_back(segment(*argument));
            }

            setResult(utility::makeOwned<Intrinsic>(intrinsic.intrinsic, std::move(arguments), intrinsic.location));
        }

        void visit(ret::Call const& call) override
        {
            utility::List<utility::Owned<Expression>> arguments;
            for (auto& argument : call.arguments)
            {
                arguments.emplace_back(segment(*argument));
            }

            setResult(utility::makeOwned<Call>(call.called, std::move(arguments), call.location));
        }

        void visit(ret::Access const& access) override
        {
            setResult(utility::makeOwned<Access>(access.variable, access.location));
        }

        void visit(ret::Constant const& constant) override
        {
            setResult(utility::makeOwned<Constant>(constant.value, constant.location));
        }

        void visit(ret::UnaryOperation const& unary_operation) override
        {
            utility::Owned<Expression> operand = segment(*unary_operation.operand);

            setResult(utility::makeOwned<UnaryOperation>(unary_operation.op, std::move(operand), unary_operation.location));
        }

        struct Loop
        {
            std::reference_wrapper<SimpleBB> entry;
            std::reference_wrapper<SimpleBB> exit;
        };

      private:
        utility::List<utility::Owned<BaseBB>> bbs_;

        SimpleBB* current_entry_bb_ = nullptr;
        SimpleBB* current_exit_bb_  = nullptr;

        std::stack<Loop> loops_;

        utility::Optional<utility::Owned<Expression>> segmented_expression_;

        core::Reporter& reporter_;
    };

    explicit Implementation(core::Reporter& reporter) : reporter_(reporter) {}

    utility::Owned<Flow> segment(ret::Statement const& statement)
    {
        utility::Owned<RET> ret = utility::makeOwned<RET>(reporter_);

        return ret->apply(statement);
    }

  private:
    core::Reporter& reporter_;
};

ance::bbt::Segmenter::Segmenter(core::Reporter& reporter) : implementation_(utility::makeOwned<Implementation>(reporter)) {}

ance::bbt::Segmenter::~Segmenter() = default;

ance::utility::Owned<ance::bbt::Flow> ance::bbt::Segmenter::segment(ret::Statement const& statement)
{
    return implementation_->segment(statement);
}
