#include "Resolver.h"

#include <array>

#include "ance/est/Node.h"
#include "ance/ret/Node.h"

namespace ance
{
    class EST final : public est::Visitor
    {
      public:
        using Visitor::visit;

        void setResult(utility::Owned<ret::Statement> statement)
        {
            assert(!resolved_statement_.hasValue() && !resolved_expression_.hasValue());

            resolved_statement_  = std::move(statement);
            resolved_expression_ = std::nullopt;
        }

        void setResult(utility::Owned<ret::Expression> expression)
        {
            assert(!resolved_statement_.hasValue() && !resolved_expression_.hasValue());

            resolved_statement_  = std::nullopt;
            resolved_expression_ = std::move(expression);
        }

        utility::Owned<ret::Statement> resolve(est::Statement const& statement)
        {
            visit(statement);

            assert(resolved_statement_.hasValue());

            utility::Owned<ret::Statement> result = std::move(*resolved_statement_);
            resolved_statement_                   = std::nullopt;

            return result;
        }

        utility::Owned<ret::Expression> resolve(est::Expression const& expression)
        {
            visit(expression);

            assert(resolved_expression_.hasValue());

            utility::Owned<ret::Expression> result = std::move(*resolved_expression_);
            resolved_expression_                   = std::nullopt;

            return result;
        }

        void visit(est::ErrorStatement const&) override { setResult(utility::makeOwned<ret::ErrorStatement>()); }

        void visit(est::Block const& block) override
        {
            utility::List<utility::Owned<ret::Statement>> statements;

            for (auto& statement : block.statements)
            {
                auto resolved = resolve(*statement);
                statements.emplace_back(std::move(resolved));
            }

            setResult(utility::makeOwned<ret::Block>(std::move(statements), block.location));
        }

        void visit(est::Independent const& independent) override
        {
            auto resolved = resolve(*independent.expression);

            setResult(utility::makeOwned<ret::Independent>(std::move(resolved), independent.location));
        }

        void visit(est::ErrorExpression const&) override { setResult(utility::makeOwned<ret::ErrorExpression>()); }

        void visit(est::Call const& call) override
        {
            setResult(utility::makeOwned<ret::Intrinsic>(call.identifier, call.location));
        }

      private:
        utility::Optional<utility::Owned<ret::Statement>>  resolved_statement_;
        utility::Optional<utility::Owned<ret::Expression>> resolved_expression_;
    };
}

struct ance::ret::Resolver::Implementation
{
    utility::Owned<Statement> resolve(est::Statement const& statement)
    {
        EST est;

        return est.resolve(statement);
    }
};

ance::ret::Resolver::Resolver() : implementation_(utility::makeOwned<Implementation>()) {}

ance::ret::Resolver::~Resolver() = default;

ance::utility::Owned<ance::ret::Statement> ance::ret::Resolver::resolve(est::Statement const& statement)
{
    return implementation_->resolve(statement);
}
