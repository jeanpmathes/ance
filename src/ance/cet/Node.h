#ifndef ANCE_CET_NODE_H
#define ANCE_CET_NODE_H

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
    class Value;
}


/// The compile-able entity tree (CET) namespace.
namespace ance::cet
{
    class Visitor;

    /// Base class for all nodes in the CET.
    struct Node : virtual utility::AbstractNode<Visitor> {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    /// A unit of compilation.
    struct Unit final
        : Node
        , utility::ConcreteNode<Unit, Visitor> {
        Unit();

        utility::List<utility::Owned<Node>> children = {};
    };

    struct Statement;
    struct Link;

    /// A basic block is a sequence of statements that are executed without interruption.
    /// Control flow can be set up between basic blocks.
    struct BasicBlock final
        : Node
        , utility::ConcreteNode<BasicBlock, Visitor> {
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

    /// Statement node in the CET.
    struct Statement
        : virtual Node
        , virtual utility::AbstractNode<Visitor> {
    };

    /// Statement that simply wraps an expression.
    struct Independent final
        : Statement
        , utility::ConcreteNode<Independent, Visitor> {
        Independent(utility::Owned<Expression> independent_expression, core::Location const& source_location);

        utility::Owned<Expression> expression;
    };

    /// A let statement declares a variable and can also define its value.
    struct Let final
        : Statement
        , utility::ConcreteNode<Let, Visitor> {
        Let(core::Variable const& identifier, utility::Optional<utility::Owned<Expression>> definition, core::Location const& source_location);

        core::Variable const& variable;
        utility::Optional<utility::Owned<Expression>> value;
    };

    /// Assigns an expression result to a variable.
    struct Assignment final
        : Statement
        , utility::ConcreteNode<Assignment, Visitor> {
        Assignment(core::Variable const& assigned, utility::Owned<Expression> expression, core::Location const& source_location);

        core::Variable const& variable;
        utility::Owned<Expression> value;
    };

    /// Introduce a temporary variable, which works similar to any other local variable but does not have a name.
    struct Temporary final
        : Statement
        , utility::ConcreteNode<Temporary, Visitor>
    {
        Temporary(core::Type const& t, utility::Optional<utility::Owned<Expression>> expression, core::Location const& source_location);

        [[nodiscard]] std::string id() const;

        core::Type const& type;
        utility::Optional<utility::Owned<Expression>> definition;
    };

    /// Writes a value to a temporary variable.
    struct WriteTemporary final
        : Statement
        , utility::ConcreteNode<WriteTemporary, Visitor>
    {
        WriteTemporary(Temporary const& target, utility::Owned<Expression> expression, core::Location const& source_location);

        Temporary const& temporary;
        utility::Owned<Expression> value;
    };

    /// Expression node in the CET.
    struct Expression
        : virtual Node
        , virtual utility::AbstractNode<Visitor> {
    };

    /// Performs a compiler-provided operation like operators or functions.
    struct Intrinsic final
        : Expression
        , utility::ConcreteNode<Intrinsic, Visitor> {
        Intrinsic(core::Intrinsic const& used, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location);

        core::Intrinsic const& intrinsic;
        utility::List<utility::Owned<Expression>> arguments;
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

    /// Access is an expression that reads the value of a variable.
    struct Access final
        : Expression
        , utility::ConcreteNode<Access, Visitor> {
        Access(core::Variable const& accessed, core::Location const& source_location);

        core::Variable const& variable;
    };

    /// Holds a compile-time value.
    struct Constant final
        : Expression
        , utility::ConcreteNode<Constant, Visitor> {
        Constant(utility::Shared<core::Value> constant, core::Location const& source_location);

        utility::Shared<core::Value> value;
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

    /// Reads the value of a temporary variable.
    struct ReadTemporary final
        : Expression
        , utility::ConcreteNode<ReadTemporary, Visitor>
    {
        ReadTemporary(Temporary const& target, core::Location const& source_location);

        Temporary const& temporary;
    };

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        virtual void visit(Unit const& unit) = 0;

        virtual void visit(BasicBlock const& basic_block) = 0;

        virtual void visit(Return const& return_link) = 0;
        virtual void visit(Branch const& branch_link) = 0;
        virtual void visit(Jump const& jump_link) = 0;

        virtual void visit(Independent const& independent) = 0;
        virtual void visit(Let const& let) = 0;
        virtual void visit(Assignment const& assignment) = 0;
        virtual void visit(Temporary const& temporary) = 0;
        virtual void visit(WriteTemporary const& write_temporary) = 0;

        virtual void visit(Intrinsic const& intrinsic) = 0;
        virtual void visit(Call const& call) = 0;
        virtual void visit(Access const& access) = 0;
        virtual void visit(Constant const& constant) = 0;
        virtual void visit(UnaryOperation const& unary_operation) = 0;
        virtual void visit(ReadTemporary const& read_temporary) = 0;

        ~Visitor() override = default;
    };
}

#endif
