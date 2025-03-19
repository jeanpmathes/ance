#ifndef ANCE_BBT_NODE_H
#define ANCE_BBT_NODE_H

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

/// The basic-block tree (BBT) namespace.
namespace ance::bbt
{
    class Visitor;

    /// Base class for all nodes in the BBT.
    struct Node : virtual utility::AbstractNode<Visitor>
    {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    struct Statement;

    /// A basic block is a sequence of statements that are executed without interruption.
    /// Control flow can be set up between basic blocks.
    struct BasicBlock final
        : Node
        , utility::ConcreteNode<BasicBlock, Visitor>
    {
        BasicBlock(utility::List<utility::Owned<Statement>> content, core::Location const& source_location);

        utility::List<utility::Owned<Statement>> statements;
    };

    /// Statement node in the BBT.
    struct Statement
        : virtual Node
        , virtual utility::AbstractNode<Visitor>
    {
    };

    /// Error statement, mostly as pass-through from the AST.
    struct ErrorStatement final
        : Statement
        , utility::ConcreteNode<ErrorStatement, Visitor>
    {
        explicit ErrorStatement(core::Location const& source_location);
    };

    struct Expression;

    /// Statement that simply wraps an expression.
    struct Independent final
        : Statement
        , utility::ConcreteNode<Independent, Visitor>
    {
        Independent(utility::Owned<Expression> independent_expression, core::Location const& source_location);

        utility::Owned<Expression> expression;
    };

    /// A let statement declares a variable and can also define its value.
    struct Let final
        : Statement
        , utility::ConcreteNode<Let, Visitor>
    {
        Let(core::Variable const&                         identifier,
            utility::Optional<utility::Owned<Expression>> definition,
            core::Location const&                         source_location);

        core::Variable const&                         variable;
        utility::Optional<utility::Owned<Expression>> value;
    };

    /// Expression node in the BBT.
    struct Expression
        : virtual Node
        , virtual utility::AbstractNode<Visitor>
    {
    };

    /// Error expression, mostly as pass-through from the AST.
    struct ErrorExpression final
        : Expression
        , utility::ConcreteNode<ErrorExpression, Visitor>
    {
        explicit ErrorExpression(core::Location const& source_location);
    };

    /// Performs a compiler-provided operation like operators or functions.
    struct Intrinsic final
        : Expression
        , utility::ConcreteNode<Intrinsic, Visitor>
    {
        Intrinsic(core::Intrinsic const& used, core::Location const& source_location);

        core::Intrinsic const& intrinsic;
    };

    /// Accesses a variable.
    struct Access final
        : Expression
        , utility::ConcreteNode<Access, Visitor>
    {
        Access(core::Variable const& accessed, core::Location const& source_location);

        core::Variable const& variable;
    };

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        virtual void visit(BasicBlock const& basic_block) = 0;

        virtual void visit(ErrorStatement const& error_statement) = 0;
        virtual void visit(Independent const& independent)        = 0;
        virtual void visit(Let const& let)                        = 0;

        virtual void visit(ErrorExpression const& error_expression) = 0;
        virtual void visit(Intrinsic const& intrinsic)              = 0;
        virtual void visit(Access const& access)                    = 0;

        ~Visitor() override = default;
    };
}

#endif
