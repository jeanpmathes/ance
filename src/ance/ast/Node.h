#ifndef ANCE_AST_NODE_H
#define ANCE_AST_NODE_H

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

#include <ance/core/Reporter.h>

namespace ance::ast
{
    class Visitor;

    /**
     * Base class for all nodes in the AST.
     */
    struct Node : virtual utility::AbstractNode<Visitor> {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    /**
     * A statement is an independent part of code.
     */
    struct Statement
        : virtual Node
        , virtual utility::AbstractNode<Visitor> {
    };

    /**
     * A statement that could not be parsed correctly.
     */
    struct ErrorStatement final
        : Statement
        , utility::ConcreteNode<ErrorStatement, Visitor> {
        ErrorStatement();
    };

    /**
     * A block statement combines multiple statements into a single statement.
     */
    struct Block final
        : Statement
        , utility::ConcreteNode<Block, Visitor> {
        Block(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location);

        utility::List<utility::Owned<Statement>> statements = {};
    };

    struct Expression;

    /**
     * An independent expression statement is a statement that consists of a single expression.
     */
    struct Independent final
        : Statement
        , utility::ConcreteNode<Independent, Visitor> {
        Independent(utility::Owned<Expression> independent_expression, core::Location const& source_location);

        utility::Owned<Expression> expression;
    };

    /**
     * An expression is a piece of code that produces a value.
     */
    struct Expression
        : virtual Node
        , virtual utility::AbstractNode<Visitor> {
    };

    /**
     * An expression that could not be parsed correctly.
     */
    struct ErrorExpression final
        : Expression
        , utility::ConcreteNode<ErrorExpression, Visitor> {
        ErrorExpression();
    };

    /**
     * A call is an expression that performs the call-operator on a callable entity.
     */
    struct Call final
        : Expression
        , utility::ConcreteNode<Call, Visitor> {
        explicit Call(core::Location const& source_location);
    };

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        ~Visitor() override = default;

        virtual void visit(Block const& block);
        virtual void visit(Independent const& independent);

        virtual void visit(Call const& call);
    };
}

#endif
