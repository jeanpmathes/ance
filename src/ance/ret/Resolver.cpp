#include "Resolver.h"

#include <array>
#include <map>

#include "ance/core/Intrinsic.h"

#include "ance/est/Node.h"
#include "ance/ret/Node.h"

struct ance::ret::Resolver::Implementation
{
    class EST final : public est::Visitor
    {
      public:
        using Visitor::visit;

        EST(core::Reporter& reporter, std::map<core::Identifier, std::reference_wrapper<const core::Intrinsic>> const& intrinsics)
            : reporter_(reporter), intrinsics_(intrinsics) {}
        ~EST() override = default;

        void setResult(utility::Owned<Statement> statement)
        {
            assert(!resolved_statement_.hasValue() && !resolved_expression_.hasValue());

            resolved_statement_  = std::move(statement);
            resolved_expression_ = std::nullopt;
        }

        void setResult(utility::Owned<Expression> expression)
        {
            assert(!resolved_statement_.hasValue() && !resolved_expression_.hasValue());

            resolved_statement_  = std::nullopt;
            resolved_expression_ = std::move(expression);
        }

        utility::Owned<Statement> resolve(est::Statement const& statement)
        {
            visit(statement);

            assert(resolved_statement_.hasValue());

            utility::Owned<Statement> result = std::move(*resolved_statement_);
            resolved_statement_                   = std::nullopt;

            return result;
        }

        utility::Owned<Expression> resolve(est::Expression const& expression)
        {
            visit(expression);

            assert(resolved_expression_.hasValue());

            utility::Owned<Expression> result = std::move(*resolved_expression_);
            resolved_expression_                   = std::nullopt;

            return result;
        }

        void visit(est::ErrorStatement const&) override { setResult(utility::makeOwned<ErrorStatement>()); }

        void visit(est::Block const& block) override
        {
            utility::List<utility::Owned<Statement>> statements;

            for (auto& statement : block.statements)
            {
                auto resolved = resolve(*statement);
                statements.emplace_back(std::move(resolved));
            }

            setResult(utility::makeOwned<Block>(std::move(statements), block.location));
        }

        void visit(est::Independent const& independent) override
        {
            auto resolved = resolve(*independent.expression);

            setResult(utility::makeOwned<Independent>(std::move(resolved), independent.location));
        }

        void visit(est::ErrorExpression const&) override { setResult(utility::makeOwned<ErrorExpression>()); }

        void visit(est::Call const& call) override
        {
            if (intrinsics_.contains(call.identifier))
            {
                setResult(utility::makeOwned<Intrinsic>(intrinsics_.at(call.identifier).get(), call.location));
            }
            else
            {
                reporter_.error("Unknown intrinsic '" + call.identifier + "'", call.identifier.location());

                setResult(utility::makeOwned<ErrorExpression>());
            }
        }

      private:
        utility::Optional<utility::Owned<Statement>>  resolved_statement_;
        utility::Optional<utility::Owned<Expression>> resolved_expression_;

        core::Reporter& reporter_;
        std::map<core::Identifier, std::reference_wrapper<const core::Intrinsic>> const& intrinsics_;
    };

    explicit Implementation(core::Reporter& reporter) : reporter_(reporter) {}

    void add(core::Intrinsic const& intrinsic)
    {
        intrinsics_.emplace(intrinsic.identifier(), std::cref(intrinsic));
    }

    utility::Owned<Statement> resolve(est::Statement const& statement)
    {
        utility::Owned<EST> est = utility::makeOwned<EST>(reporter_, intrinsics_);

        return est->resolve(statement);
    }

private:
    core::Reporter& reporter_;

    std::map<core::Identifier, std::reference_wrapper<const core::Intrinsic>> intrinsics_ = {};
};

ance::ret::Resolver::Resolver(core::Reporter& reporter) : implementation_(utility::makeOwned<Implementation>(reporter)) {}

ance::ret::Resolver::~Resolver() = default;

void ance::ret::Resolver::add(core::Intrinsic const& intrinsic)
{
    implementation_->add(intrinsic);
}

ance::utility::Owned<ance::ret::Statement> ance::ret::Resolver::resolve(est::Statement const& statement)
{
    return implementation_->resolve(statement);
}
