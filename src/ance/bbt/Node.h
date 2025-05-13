#ifndef ANCE_BBT_NODE_H
#define ANCE_BBT_NODE_H

#include "ance/core/Identifier.h"
#include "ance/core/Reporter.h"
#include "ance/core/Variable.h"
#include "ance/core/UnaryOperator.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

namespace ance::core
{
    struct Intrinsic;

    class Function;
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

    struct BasicBlock;

    /// The flow node represents a complete control flow build up by a set of basic blocks.
    struct Flow final
        : Node
        , utility::ConcreteNode<Flow, Visitor>
    {
        Flow(utility::List<utility::Owned<BasicBlock>> content, BasicBlock& start, core::Location const& source_location);

        utility::List<utility::Owned<BasicBlock>> blocks;
        BasicBlock& entry;
    };

    struct Statement;
    struct Link;

    /// A basic block is a sequence of statements that are executed without interruption.
    /// Control flow can be set up between basic blocks.
    struct BasicBlock final
        : Node
        , utility::ConcreteNode<BasicBlock, Visitor>
    {
        BasicBlock(size_t number, utility::List<utility::Owned<Statement>> content, utility::Owned<Link> connection, core::Location const& source_location);

        size_t id;
        utility::List<utility::Owned<Statement>> statements;
        utility::Owned<Link>                     link;
    };

    /// Describes how control flow is passed between basic blocks.
    struct Link
        : virtual Node
        , virtual utility::AbstractNode<Visitor>
    {

    };

    /// The error link is used to represent an error in the control flow.
    struct ErrorLink final
        : Link
        , utility::ConcreteNode<ErrorLink, Visitor>
    {
        explicit ErrorLink(core::Location const& source_location);
    };

    /// The return link ends the current function, not linking to any other basic block.
    struct Return final
        : Link
        , utility::ConcreteNode<Return, Visitor>
    {
        explicit Return(core::Location const& source_location);
    };

    struct Expression;

    /// Chooses between two branches based on a condition.
    struct Branch final
        : Link
        , utility::ConcreteNode<Branch, Visitor>
    {
        Branch(utility::Owned<Expression> expression, BasicBlock const& true_link, BasicBlock const& false_link, core::Location const& source_location);

        utility::Owned<Expression> condition;
        BasicBlock const& true_branch;
        BasicBlock const& false_branch;
    };

    /// A simple and direct jump to a block.
    struct Jump final
        : Link
        , utility::ConcreteNode<Jump, Visitor>
    {
        Jump(BasicBlock const& link, core::Location const& source_location);

        BasicBlock const& target;
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

    /// An assignment statement assigns a value to a variable.
    struct Assignment final
        : Statement
        , utility::ConcreteNode<Assignment, Visitor>
    {
        Assignment(core::Variable const& assigned, utility::Owned<Expression> expression, core::Location const& source_location);

        core::Variable const& variable;
        utility::Owned<Expression> value;
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
        Intrinsic(core::Intrinsic const& used, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location);

        core::Intrinsic const& intrinsic;
        utility::List<utility::Owned<Expression>> arguments;
    };

    /// Accesses a variable.
    struct Access final
        : Expression
        , utility::ConcreteNode<Access, Visitor>
    {
        Access(core::Variable const& accessed, core::Location const& source_location);

        core::Variable const& variable;
    };

    /// Calls a function.
    struct Call final
        : Expression
        , utility::ConcreteNode<Call, Visitor>
    {
        Call(core::Function const& function, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location);

        core::Function const& called;
        utility::List<utility::Owned<Expression>> arguments;
    };

    /// A constant value.
    struct Constant final
        : Expression
        , utility::ConcreteNode<Constant, Visitor>
    {
        Constant(bool constant, core::Location const& source_location);

        bool value;
    };

    /// Applies an operation to an operand.
    struct UnaryOperation final
        : Expression
        , utility::ConcreteNode<UnaryOperation, Visitor>
    {
        UnaryOperation(core::UnaryOperator const& kind, utility::Owned<Expression> expression, core::Location const& source_location);

        core::UnaryOperator op;
        utility::Owned<Expression> operand;
    };

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        virtual void visit(Flow const& flow) = 0;

        virtual void visit(BasicBlock const& basic_block) = 0;

        virtual void visit(ErrorLink const& error_link) = 0;
        virtual void visit(Return const& return_link) = 0;
        virtual void visit(Branch const& branch_link) = 0;
        virtual void visit(Jump const& jump_link) = 0;

        virtual void visit(ErrorStatement const& error_statement) = 0;
        virtual void visit(Independent const& independent)        = 0;
        virtual void visit(Let const& let)                        = 0;
        virtual void visit(Assignment const& assignment)          = 0;

        virtual void visit(ErrorExpression const& error_expression) = 0;
        virtual void visit(Intrinsic const& intrinsic)              = 0;
        virtual void visit(Call const& call)                        = 0;
        virtual void visit(Access const& access)                    = 0;
        virtual void visit(Constant const& constant)                = 0;
        virtual void visit(UnaryOperation const& unary_operation)   = 0;

        ~Visitor() override = default;
    };
}

#endif
