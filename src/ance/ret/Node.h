#ifndef ANCE_RET_NODE_H
#define ANCE_RET_NODE_H

#include "ance/core/Identifier.h"
#include "ance/core/Reporter.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

/**
 * The resolved element tree (RET) namespace.
 */
namespace ance::ret
{
    class Visitor;

    /**
     * Base class for all nodes in the RET.
     */
    struct Node : virtual utility::AbstractNode<Visitor> {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    /**
     * Statement node in the RET.
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
     * Expression node in the RET.
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
     * Performs a compiler-provided operation like operators or functions.
     */
    struct Intrinsic final
        : Expression
        , utility::ConcreteNode<Intrinsic, Visitor> {
        explicit Intrinsic(core::Identifier const& callable, core::Location const& source_location);

        core::Identifier identifier;

        // todo: when putting the actual intrinsics here, do not make them optional
        // todo: not found intrinsics should be reported in resolution, not later in analysis
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
        virtual void visit(Intrinsic const& intrinsic)   = 0;
    };
}

#endif
