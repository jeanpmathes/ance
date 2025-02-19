#ifndef ANCE_CET_NODE_H
#define ANCE_CET_NODE_H

#include "ance/core/Identifier.h"
#include "ance/core/Reporter.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

/**
 * The compile-able entity tree (CET) namespace.
 */
namespace ance::cet
{
    class Visitor;

    /**
     * Base class for all nodes in the CET.
     */
    struct Node : virtual utility::AbstractNode<Visitor> {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    /**
     * A unit of compilation.
     */
    struct Unit final
        : Node
        , utility::ConcreteNode<Unit, Visitor> {
        Unit();

        utility::List<utility::Owned<Node>> children = {};
    };

    struct Statement;

    /**
     * A basic block is a sequence of statements that are executed without interruption.
     * Control flow can be set up between basic blocks.
     */
    struct BasicBlock final
        : Node
        , utility::ConcreteNode<BasicBlock, Visitor> {
        BasicBlock(utility::List<utility::Owned<Statement>> content, core::Location const& source_location);

        utility::List<utility::Owned<Statement>> statements;
    };

    /**
   * Statement node in the CET.
   */
    struct Statement
        : virtual Node
        , virtual utility::AbstractNode<Visitor> {
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
     * Expression node in the CET.
     */
    struct Expression
        : virtual Node
        , virtual utility::AbstractNode<Visitor> {
    };

    /**
     * Performs a compiler-provided operation like operators or functions.
     */
    struct Intrinsic final
        : Expression
        , utility::ConcreteNode<Intrinsic, Visitor> {
        explicit Intrinsic(core::Identifier const& callable, core::Location const& source_location);

        core::Identifier identifier;
    };

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        virtual void visit(Unit const& unit) = 0;

        virtual void visit(BasicBlock const& basic_block) = 0;

        virtual void visit(Independent const& independent) = 0;

        virtual void visit(Intrinsic const& intrinsic) = 0;

        ~Visitor() override = default;
    };
}

#endif
