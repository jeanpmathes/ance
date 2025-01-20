#ifndef ANCE_AST_NODE_H
#define ANCE_AST_NODE_H

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

namespace ance::ast
{
    class Visitor;

    /**
     * Base class for all nodes in the AST.
     */
    struct Node : virtual utility::AbstractNode<Visitor> {
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
    struct ErrorStatement
        : Statement
        , utility::ConcreteNode<ErrorStatement, Visitor> {
    };

    /**
     * A block statement combines multiple statements into a single statement.
     */
    struct Block
        : Statement
        , utility::ConcreteNode<Block, Visitor> {
        explicit Block(utility::List<utility::Owned<Statement>> statements);

        utility::List<utility::Owned<Statement>> statements = {};
    };

    struct Expression;

    /**
     * An independent expression statement is a statement that consists of a single expression.
     */
    struct Independent
        : Statement
        , utility::ConcreteNode<Independent, Visitor> {
        explicit Independent(utility::Owned<Expression> independent_expression);

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
    struct ErrorExpression
        : Expression
        , utility::ConcreteNode<ErrorExpression, Visitor> {
    };

    /**
     * A call is an expression that performs the call-operator on a callable entity.
     */
    struct Call
        : Expression
        , utility::ConcreteNode<Call, Visitor> {
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
