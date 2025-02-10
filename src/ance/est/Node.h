#ifndef ANCE_EST_NODE_H
#define ANCE_EST_NODE_H

#include "ance/core/Identifier.h"
#include "ance/core/Reporter.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

/**
 * The expanded syntax tree (EST) namespace.
 * The EST is similar to the AST, but without syntactic sugar.
 */
namespace ance::est
{
    class Visitor;

    /**
     * Base class for all nodes in the EST.
     */
    struct Node : virtual utility::AbstractNode<Visitor> {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    /**
     * Statement node in the EST.
     */
    struct Statement
        : virtual Node
        , virtual utility::AbstractNode<Visitor> {
    };

    /**
     * Error statement, mostly as pass-through from the AST.
     */
    struct ErrorStatement final
        : Statement
        , utility::ConcreteNode<ErrorStatement, Visitor> {
        ErrorStatement();
    };

    /**
     * Block statement, containing multiple statements.
     */
    struct Block final
        : Statement
        , utility::ConcreteNode<Block, Visitor> {
        Block(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location);

        utility::List<utility::Owned<Statement>> statements = {};
    };

    struct Expression;

    /**
     * Statement that simply wraps an expression.
     */
    struct Independent final
        : Statement
        , utility::ConcreteNode<Independent, Visitor> {
        Independent(utility::Owned<Expression> independent_expression, core::Location const& source_location);

        utility::Owned<Expression> expression;
    };

    /**
     * Expression node in the EST.
     */
    struct Expression
        : virtual Node
        , virtual utility::AbstractNode<Visitor> {
    };

    /**
     * Error expression, mostly as pass-through from the AST.
     */
    struct ErrorExpression final
        : Expression
        , utility::ConcreteNode<ErrorExpression, Visitor> {
        ErrorExpression();
    };

    /**
     * A call expression.
     */
    struct Call final
        : Expression
        , utility::ConcreteNode<Call, Visitor> {
        explicit Call(core::Identifier const& callable, core::Location const& source_location);

        core::Identifier identifier;
    };

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        ~Visitor() override = default;

        virtual void visit(ErrorStatement const& error)    = 0;
        virtual void visit(Block const& block)             = 0;
        virtual void visit(Independent const& independent) = 0;

        virtual void visit(ErrorExpression const& error) = 0;
        virtual void visit(Call const& call)             = 0;
    };
}

#endif
