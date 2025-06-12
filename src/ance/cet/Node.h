#ifndef ANCE_CET_NODE_H
#define ANCE_CET_NODE_H

#include "Node.h"
#include "ance/core/Identifier.h"
#include "ance/core/Reporter.h"
#include "ance/core/UnaryOperator.h"
#include "ance/core/Variable.h"

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

    struct Temporary;

    /// Chooses between two branches based on a condition.
    struct Branch final
        : Link
        , utility::ConcreteNode<Branch, Visitor>
    {
        Branch(Temporary const& temporary, BasicBlock const& true_link, BasicBlock const& false_link, core::Location const& source_location);

        Temporary const&  condition;
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

    /// Declares a variable and can also define its value.
    struct Declare final
        : Statement
        , utility::ConcreteNode<Declare, Visitor>
    {
        Declare(core::Variable const& identifier, Temporary const* definition, core::Location const& source_location);

        core::Variable const& variable;
        Temporary const*      value;
    };

    /// Assigns an expression result to a variable.
    struct Store final
        : Statement
        , utility::ConcreteNode<Store, Visitor>
    {
        Store(core::Variable const& assigned, Temporary const& stored, core::Location const& source_location);

        core::Variable const& variable;
        Temporary const&      value;
    };

    /// Introduce a temporary variable, which works similar to any other local variable but does not have a name.
    struct Temporary final
        : Statement
        , utility::ConcreteNode<Temporary, Visitor>
    {
        Temporary(core::Type const& t, core::Location const& source_location);

        [[nodiscard]] std::string id() const;

        core::Type const& type;
    };

    /// Copies a temporary variable to another temporary variable.
    struct CopyTemporary final
        : Statement
        , utility::ConcreteNode<CopyTemporary, Visitor>
    {
        CopyTemporary(Temporary const& target, Temporary const& value, core::Location const& source_location);

        Temporary const& destination;
        Temporary const& source;
    };

    /// Performs a compiler-provided operation like operators or functions.
    struct Intrinsic final
        : Statement
        , utility::ConcreteNode<Intrinsic, Visitor>
    {
        Intrinsic(core::Intrinsic const& used, utility::List<Temporary const*> args, Temporary const& result, core::Location const& source_location);

        core::Intrinsic const&          intrinsic;
        utility::List<Temporary const*> arguments;
        Temporary const&                destination;
    };

    /// Calls a function.
    struct Call final
        : Statement
        , utility::ConcreteNode<Call, Visitor>
    {
        Call(core::Function const& function, utility::List<Temporary const*> args, Temporary const& result, core::Location const& source_location);

        core::Function const&           called;
        utility::List<Temporary const*> arguments;
        Temporary const&                destination;
    };

    /// Reads the value of a variable.
    struct Read final
        : Statement
        , utility::ConcreteNode<Read, Visitor>
    {
        Read(core::Variable const& accessed, Temporary const& result, core::Location const& source_location);

        core::Variable const& variable;
        Temporary const&      destination;
    };

    /// Holds a compile-time value.
    struct Constant final
        : Statement
        , utility::ConcreteNode<Constant, Visitor> {
        Constant(utility::Shared<core::Value> constant, Temporary const& result, core::Location const& source_location);

        utility::Shared<core::Value> value;
        Temporary const&             destination;
    };

    /// Applies an operation to an operand.
    struct UnaryOperation final
        : Statement
        , utility::ConcreteNode<UnaryOperation, Visitor>
    {
        UnaryOperation(core::UnaryOperator const& kind, Temporary const& value, Temporary const& result, core::Location const& source_location);

        core::UnaryOperator op;
        Temporary const&    operand;
        Temporary const&    destination;
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

        virtual void visit(Declare const& declare) = 0;
        virtual void visit(Store const& store) = 0;
        virtual void visit(Temporary const& temporary) = 0;
        virtual void visit(CopyTemporary const& write_temporary) = 0;

        virtual void visit(Intrinsic const& intrinsic)            = 0;
        virtual void visit(Call const& call)                      = 0;
        virtual void visit(Read const& read)                      = 0;
        virtual void visit(Constant const& constant) = 0;
        virtual void visit(UnaryOperation const& unary_operation) = 0;

        ~Visitor() override = default;
    };
}

#endif
