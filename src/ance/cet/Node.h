#ifndef ANCE_CET_NODE_H
#define ANCE_CET_NODE_H

#include "ance/core/Identifier.h"
#include "ance/core/Reporter.h"
#include "ance/core/Variable.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

namespace ance::core
{
    struct Intrinsic;
}

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
     * A let statement declares a variable and can also define its value.
     */
    struct Let final
        : Statement
        , utility::ConcreteNode<Let, Visitor> {
        Let(core::Variable const& identifier, utility::Optional<utility::Owned<Expression>> definition, core::Location const& source_location);

        core::Variable const& variable;
        utility::Optional<utility::Owned<Expression>> value;
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
        Intrinsic(core::Intrinsic const& used, core::Location const& source_location);

        core::Intrinsic const& intrinsic;
    };

    /**
     * Access is an expression that reads the value of a variable.
     */
    struct Access final
        : Expression
        , utility::ConcreteNode<Access, Visitor> {
        Access(core::Variable const& accessed, core::Location const& source_location);

        core::Variable const& variable;
    };

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        virtual void visit(Unit const& unit) = 0;

        virtual void visit(BasicBlock const& basic_block) = 0;

        virtual void visit(Independent const& independent) = 0;
        virtual void visit(Let const& let) = 0;

        virtual void visit(Intrinsic const& intrinsic) = 0;
        virtual void visit(Access const& access) = 0;

        ~Visitor() override = default;
    };
}

#endif
