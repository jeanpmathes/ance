#include "Segmenter.h"

#include <array>

#include "ance/ret/Node.h"
#include "ance/bbt/Node.h"

namespace ance::bbt
{
    class RET final : public ret::Visitor
    {
      public:
        using Visitor::visit;

        explicit RET(core::Reporter& reporter) : reporter_(reporter) {}
        ~RET() override = default;

        utility::Owned<BasicBlock> segment(ret::Statement const& statement)
        {
            statements_.clear();

            visit(statement);

            return utility::makeOwned<BasicBlock>(std::move(statements_), statement.location);
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

        void visit(ret::ErrorStatement const&) override
        {
            statements_.emplace_back(utility::makeOwned<ErrorStatement>());
        }

        void visit(ret::Block const& block) override
        {
            for (auto& statement : block.statements)
            {
                visit(*statement);
            }
        }

        void visit(ret::Independent const& independent) override
        {
            utility::Owned<Expression> expression = segment(*independent.expression);

            statements_.emplace_back(utility::makeOwned<Independent>(std::move(expression), independent.location));
        }

        void visit(ret::ErrorExpression const&) override
        {
            utility::Owned<Expression> expression = utility::makeOwned<ErrorExpression>();

            setResult(std::move(expression));
        }

        void visit(ret::Intrinsic const& intrinsic) override
        {
            utility::Owned<Expression> expression = utility::makeOwned<Intrinsic>(intrinsic.identifier, intrinsic.location);

            setResult(std::move(expression));

            (void)reporter_; // todo: use it or remove it
        }

      private:
        utility::List<utility::Owned<Statement>> statements_;
        utility::Optional<utility::Owned<Expression>> segmented_expression_;

        core::Reporter& reporter_;
    };
}

struct ance::bbt::Segmenter::Implementation
{
    explicit Implementation(core::Reporter& reporter) : reporter_(reporter) {}

    utility::Owned<BasicBlock> segment(ret::Statement const& statement)
    {
        utility::Owned<RET> ret = utility::makeOwned<RET>(reporter_);

        return ret->segment(statement);
    }

private:
    core::Reporter& reporter_;
};

ance::bbt::Segmenter::Segmenter(core::Reporter& reporter) : implementation_(utility::makeOwned<Implementation>(reporter)) {}

ance::bbt::Segmenter::~Segmenter() = default;

ance::utility::Owned<ance::bbt::BasicBlock> ance::bbt::Segmenter::segment(ret::Statement const& statement)
{
    return implementation_->segment(statement);
}
