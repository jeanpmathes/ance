#ifndef ANCE_BBT_NODE_H
#define ANCE_BBT_NODE_H

#include "ance/core/Intrinsic.h"
#include "ance/core/Location.h"
#include "ance/core/UnaryOperator.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

/// The basic-block tree (BBT) namespace.
namespace ance::bbt
{
    class Value;

    class Visitor;

    /// Base class for all nodes in the BBT.
    struct Node : virtual utility::AbstractNode<Visitor>
    {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    struct Flow;

    /// An unordered scope contains a set of parts which are evaluated in an unspecified order.
    /// An example of an unordered scope is the top-level of any file except for the primary file.
    struct UnorderedScope final
        : Node
        , utility::ConcreteNode<UnorderedScope, Visitor>
    {
        UnorderedScope(utility::List<utility::Owned<Flow>> flow_list, core::Location const& source_location);

        utility::List<utility::Owned<Flow>> flows = {};
    };

    struct BasicBlock;

    /// The flow node represents a complete control flow build up by a set of basic blocks.
    struct Flow final
        : Node
        , utility::ConcreteNode<Flow, Visitor>
    {
        Flow(utility::List<utility::Owned<BasicBlock>> content, BasicBlock& start, core::Location const& source_location);

        utility::List<utility::Owned<BasicBlock>> blocks;
        BasicBlock&                               entry;

        [[nodiscard]] std::string id() const;
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

        size_t                                   id;
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

    /// Pass statement, a no-op.
    struct Pass final
        : Statement
        , utility::ConcreteNode<Pass, Visitor>
    {
        explicit Pass(core::Location const& source_location);
    };

    /// Stores a value to a variable.
    struct Store final
        : Statement
        , utility::ConcreteNode<Store, Visitor>
    {
        Store(Temporary const& var, Temporary const& stored, core::Location const& source_location);

        Temporary const& target;
        Temporary const& value;
    };

    /// Introduce a temporary variable, which works similar to any other local variable but does not have a name.
    struct Temporary final
        : Statement
        , utility::ConcreteNode<Temporary, Visitor>
    {
        explicit Temporary(core::Location const& source_location);

        [[nodiscard]] std::string id() const;
    };

    /// Writes a value to a temporary variable.
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
        Intrinsic(core::Intrinsic                                        used,
                  utility::List<std::reference_wrapper<Temporary const>> args,
                  Temporary const&                                       result,
                  core::Location const&                                  source_location);

        core::Intrinsic                                        intrinsic;
        utility::List<std::reference_wrapper<Temporary const>> arguments;
        Temporary const&                                       destination;
    };

    /// Reads a variable.
    struct Read final
        : Statement
        , utility::ConcreteNode<Read, Visitor>
    {
        Read(Temporary const& var, Temporary const& result, core::Location const& source_location);

        Temporary const& target;
        Temporary const& destination;
    };

    /// Calls a function.
    struct Call final
        : Statement
        , utility::ConcreteNode<Call, Visitor>
    {
        Call(Temporary const&                                       function,
             utility::List<std::reference_wrapper<Temporary const>> args,
             Temporary const&                                       result,
             core::Location const&                                  source_location);

        Temporary const&                                       called;
        utility::List<std::reference_wrapper<Temporary const>> arguments;
        Temporary const&                                       destination;
    };

    /// A constant value.
    struct Constant final
        : Statement
        , utility::ConcreteNode<Constant, Visitor>
    {
        Constant(utility::Shared<Value> constant, Temporary const& result, core::Location const& source_location);

        utility::Shared<Value> value;
        Temporary const&       destination;
    };

    /// Provides the default value for a type.
    struct Default final
        : Statement
        , utility::ConcreteNode<Default, Visitor>
    {
        Default(Temporary const& t, Temporary const& result, core::Location const& source_location);

        Temporary const& type;
        Temporary const& destination;
    };

    /// Writes the current scope to the destination temporary.
    struct CurrentScope final
        : Statement
        , utility::ConcreteNode<CurrentScope, Visitor>
    {
        CurrentScope(Temporary const& result, core::Location const& source_location);

        Temporary const& destination;
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

    /// Stores the type of the value produced by an expression into the destination temporary variable.
    /// The expression WILL BE evaluated.
    struct TypeOf final
        : Statement
        , utility::ConcreteNode<TypeOf, Visitor>
    {
        TypeOf(Temporary const& expr, Temporary const& result, core::Location const& source_location);

        Temporary const& expression;
        Temporary const& destination;
    };

    /// Enters an ordered scope, which is used to manage variable lifetimes and visibility.
    struct OrderedScopeEnter final
        : Statement
        , utility::ConcreteNode<OrderedScopeEnter, Visitor>
    {
        explicit OrderedScopeEnter(core::Location const& source_location);
    };

    /// Exits an ordered scope, which is used to manage variable lifetimes and visibility.
    struct OrderedScopeExit final
        : Statement
        , utility::ConcreteNode<OrderedScopeExit, Visitor>
    {
        OrderedScopeExit(OrderedScopeEnter const& entry, core::Location const& source_location);

        OrderedScopeEnter const& enter;
    };

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        virtual void visit(UnorderedScope const& unordered_scope) = 0;

        virtual void visit(Flow const& flow) = 0;

        virtual void visit(BasicBlock const& basic_block) = 0;

        virtual void visit(ErrorLink const& error_link) = 0;
        virtual void visit(Return const& return_link)   = 0;
        virtual void visit(Branch const& branch_link)   = 0;
        virtual void visit(Jump const& jump_link)       = 0;

        virtual void visit(ErrorStatement const& error_statement) = 0;
        virtual void visit(Pass const& pass_statement)            = 0;
        virtual void visit(Store const& store)                    = 0;
        virtual void visit(Temporary const& temporary)            = 0;
        virtual void visit(CopyTemporary const& write_temporary)  = 0;

        virtual void visit(Intrinsic const& intrinsic)            = 0;
        virtual void visit(Call const& call)                      = 0;
        virtual void visit(Read const& read)                      = 0;
        virtual void visit(Constant const& constant)              = 0;
        virtual void visit(Default const& default_value)          = 0;
        virtual void visit(CurrentScope const& current_scope)     = 0;
        virtual void visit(UnaryOperation const& unary_operation) = 0;
        virtual void visit(TypeOf const& type_of)                 = 0;
        virtual void visit(OrderedScopeEnter const& scope_enter)  = 0;
        virtual void visit(OrderedScopeExit const& scope_exit)    = 0;

        ~Visitor() override = default;
    };
}

#endif
