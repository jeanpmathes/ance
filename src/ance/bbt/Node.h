#ifndef ANCE_BBT_NODE_H
#define ANCE_BBT_NODE_H

#include "ance/core/BinaryOperator.h"
#include "ance/core/Intrinsic.h"
#include "ance/core/Location.h"
#include "ance/core/UnaryOperator.h"
#include "ance/core/Occurrence.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

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

    /// A set of flows, e.g. all flows of a file.
    struct Flows final : Node, utility::ConcreteNode<Flows, Visitor>
    {
        Flows(
            utility::List<utility::Owned<Flow>> flow_list,
            core::Location const&               source_location
        );

        utility::List<utility::Owned<Flow>> flows = {};
    };

    /// An unordered scope contains a set of parts which are evaluated in an unspecified order.
    /// An example of an unordered scope is the scope in which the flows of all files are placed, which is the project scope.
    struct UnorderedScope final : Node, utility::ConcreteNode<UnorderedScope, Visitor>
    {
        UnorderedScope(
            utility::List<utility::Owned<Flow>> flow_list,
            core::Location const&               source_location
        );

        utility::List<utility::Owned<Flow>> flows = {};
    };

    struct BasicBlock;

    /// The flow node represents a complete control flow build up by a set of basic blocks.
    struct Flow final : Node, utility::ConcreteNode<Flow, Visitor>
    {
        Flow(
            utility::List<utility::Owned<BasicBlock>> content,
            BasicBlock&                               start,
            std::string                               id,
            core::Location const&                     source_location
        );

        [[nodiscard]] std::string id() const;

        utility::List<utility::Owned<BasicBlock>> blocks;
        BasicBlock&                               entry;
        std::string                               identifier;

        struct Attributes
        {
            core::Occurrence explicit_return_value_occurrence =
                core::Occurrence::NOT_APPLICABLE;
        } attributes = {};
    };

    struct Statement;
    struct Temporary;
    struct Link;

    /// A basic block is a sequence of statements that are executed without interruption.
    /// Control flow can be set up between basic blocks.
    struct BasicBlock final : Node, utility::ConcreteNode<BasicBlock, Visitor>
    {
        BasicBlock(
            size_t                                   number,
            utility::List<utility::Owned<Statement>> content,
            utility::Owned<Link>                     connection,
            core::Location const&                    source_location
        );

        size_t                                   id;
        utility::List<utility::Owned<Statement>> statements;
        utility::Owned<Link>                     link;
    };

    /// Describes how control flow is passed between basic blocks.
    struct Link : virtual Node, virtual utility::AbstractNode<Visitor>
    {
    };

    /// The error link is used to represent an error in the control flow.
    struct ErrorLink final : Link, utility::ConcreteNode<ErrorLink, Visitor>
    {
        explicit ErrorLink(core::Location const& source_location);
    };

    /// The return link ends the current function, not linking to any other basic block.
    /// The link cannot set a return value, for this the SetReturnValue statement is used.
    struct Return final : Link, utility::ConcreteNode<Return, Visitor>
    {
        explicit Return(core::Location const& source_location);
    };

    /// Chooses between two branches based on a condition.
    struct Branch final : Link, utility::ConcreteNode<Branch, Visitor>
    {
        Branch(
            Temporary const&      temporary,
            BasicBlock const&     true_link,
            BasicBlock const&     false_link,
            core::Location const& source_location
        );

        Temporary const&  condition;
        BasicBlock const& true_branch;
        BasicBlock const& false_branch;
    };

    /// A simple and direct jump to a block.
    struct Jump final : Link, utility::ConcreteNode<Jump, Visitor>
    {
        Jump(BasicBlock const& link, core::Location const& source_location);

        BasicBlock const& target;
    };

    struct SwitchCase;

    /// Matches a value against a series of cases and jumps to the block corresponding to the first matching case.
    struct Switch final : Link, utility::ConcreteNode<Switch, Visitor>
    {
        Switch(
            Temporary const&                          temporary,
            utility::List<utility::Owned<SwitchCase>> case_list,
            core::Location const&                     source_location
        );

        Temporary const&                          condition;
        utility::List<utility::Owned<SwitchCase>> cases;
    };

    /// Statement node in the BBT.
    struct Statement : virtual Node, virtual utility::AbstractNode<Visitor>
    {
        /// Whether this statement is relevant for reachability analysis.
        [[nodiscard]] virtual bool isRelevantForReachability() const;
    };

    /// Error statement, mostly as pass-through from the AST.
    struct ErrorStatement final : Statement,
                                  utility::ConcreteNode<ErrorStatement, Visitor>
    {
        explicit ErrorStatement(core::Location const& source_location);
    };

    /// Pass statement, a no-op.
    struct Pass final : Statement, utility::ConcreteNode<Pass, Visitor>
    {
        explicit Pass(core::Location const& source_location);
    };

    /// Asserts that a condition is true. If not, execution is stopped.
    struct Assert final : Statement, utility::ConcreteNode<Assert, Visitor>
    {
        Assert(Temporary const& expression, core::Location const& source_location);

        Temporary const& condition;
    };

    /// Stores a value to a variable reference.
    struct Store final : Statement, utility::ConcreteNode<Store, Visitor>
    {
        Store(
            Temporary const&      l_ref,
            Temporary const&      stored,
            core::Location const& source_location
        );

        Temporary const& target;
        Temporary const& value;
    };

    /// Provides a reference to a variable.
    struct Access final : Statement, utility::ConcreteNode<Access, Visitor>
    {
        Access(
            Temporary const&      var,
            Temporary const&      result,
            core::Location const& source_location
        );

        Temporary const& variable;
        Temporary const& destination;
    };

    /// Introduce a temporary variable, which works similar to any other local variable but does not have a name it is bound to.
    /// Temporaries live within the local scope they are defined in.
    struct Temporary final : Statement, utility::ConcreteNode<Temporary, Visitor>
    {
        Temporary(std::string id, core::Location const& source_location);

        [[nodiscard]] std::string id() const;

        std::string identifier;
    };

    /// Dereferences a value, unwrapping every reference until a concrete value is reached.
    struct Dereference final : Statement, utility::ConcreteNode<Dereference, Visitor>
    {
        Dereference(
            Temporary const&      value,
            Temporary const&      result,
            core::Location const& source_location
        );

        Temporary const& target;
        Temporary const& destination;
    };

    /// Performs a compiler-provided operation like operators or functions.
    struct Intrinsic final : Statement, utility::ConcreteNode<Intrinsic, Visitor>
    {
        Intrinsic(
            core::Intrinsic                                        used,
            utility::List<std::reference_wrapper<Temporary const>> args,
            Temporary const&                                       result,
            core::Location const&                                  source_location
        );

        core::Intrinsic                                        intrinsic;
        utility::List<std::reference_wrapper<Temporary const>> arguments;
        Temporary const&                                       destination;
    };

    /// Calls a function.
    struct Call final : Statement, utility::ConcreteNode<Call, Visitor>
    {
        Call(
            Temporary const&                                       function,
            utility::List<std::reference_wrapper<Temporary const>> args,
            Temporary const&                                       result,
            core::Location const&                                  source_location
        );

        Temporary const&                                       called;
        utility::List<std::reference_wrapper<Temporary const>> arguments;
        Temporary const&                                       destination;
    };

    /// Accesses a value by a given index.
    struct Subscript final : Statement, utility::ConcreteNode<Subscript, Visitor>
    {
        Subscript(
            Temporary const&      indexed_value,
            Temporary const&      index_value,
            Temporary const&      result,
            core::Location const& source_location
        );

        Temporary const& indexed;
        Temporary const& index;
        Temporary const& destination;
    };

    struct Parameter;

    /// Creates a function.
    struct
        FunctionConstructor final // todo: remove when actual function constructors exist
        : Statement,
          utility::ConcreteNode<FunctionConstructor, Visitor>
    {
        FunctionConstructor(
            core::Identifier const&  identifier,
            utility::List<Parameter> params,
            Temporary const&         returned_type,
            utility::Owned<Flow>     flow,
            Temporary const&         result,
            core::Location const&    source_location
        );

        core::Identifier         name;
        utility::List<Parameter> parameters;
        Temporary const&         return_type;
        utility::Owned<Flow>     body;
        Temporary const&         destination;
    };

    /// A constant value.
    struct Constant final : Statement, utility::ConcreteNode<Constant, Visitor>
    {
        Constant(
            utility::Shared<Value> constant,
            Temporary const&       result,
            core::Location const&  source_location
        );

        utility::Shared<Value> value;
        Temporary const&       destination;
    };

    /// Provides the default value for a type.
    struct Default final : Statement, utility::ConcreteNode<Default, Visitor>
    {
        Default(
            Temporary const&      t,
            Temporary const&      result,
            core::Location const& source_location
        );

        Temporary const& type;
        Temporary const& destination;
    };

    /// Writes the current scope to the destination temporary.
    struct CurrentScope final : Statement, utility::ConcreteNode<CurrentScope, Visitor>
    {
        CurrentScope(Temporary const& result, core::Location const& source_location);

        Temporary const& destination;
    };

    /// Retrieves the operator function identifier for a unary operation from the operand type.
    struct GetUnaryOperatorFunctionIdentifier final
        : Statement,
          utility::ConcreteNode<GetUnaryOperatorFunctionIdentifier, Visitor>
    {
        // todo: ugly, see comments at GetBinaryOperatorFunctionIdentifier

        GetUnaryOperatorFunctionIdentifier(
            core::UnaryOperator   kind,
            Temporary const&      operand_type,
            Temporary const&      result,
            core::Location const& source_location
        );

        core::UnaryOperator op;
        Temporary const&    type;
        Temporary const&    destination;
    };

    /// Retrieves the operator function identifier for a binary operation from the left operand's type.
    struct GetBinaryOperatorFunctionIdentifier final
        : Statement,
          utility::ConcreteNode<GetBinaryOperatorFunctionIdentifier, Visitor>
    {
        // todo: unify this with member function access as soon as those are added, consider whether this should be an intrinsic instead or use a completely different approach
        // todo: I really feel that this is ugly, and should rather be an intrinsic
        // todo: maybe it should not be an intrinsic and instead be something along the lines of GEP just for members
        // todo: it would be reworked to a simple GetMember where just the operator would be passed in and then standard overload resolution, which would also mean there would be no separate GetUnaryOperatorFunctionIdentifier

        GetBinaryOperatorFunctionIdentifier(
            core::BinaryOperator  kind,
            Temporary const&      left_type,
            Temporary const&      right_type,
            Temporary const&      result,
            core::Location const& source_location
        );

        core::BinaryOperator op;
        Temporary const&     left_type;
        Temporary const&     right_type;
        Temporary const&     destination;
    };

    /// Finds the common type of all provided values.
    struct TypeOf final // todo: should no longer evaluate the expressions
        : Statement,
          utility::ConcreteNode<TypeOf, Visitor>
    {
        TypeOf(
            utility::List<std::reference_wrapper<Temporary const>> value_list,
            Temporary const&                                       result,
            core::Location const&                                  source_location
        );

        utility::List<std::reference_wrapper<Temporary const>> values;
        Temporary const&                                       destination;
    };

    /// An expression that constructs an array type.
    /// The array type has a fixed length and element type.
    struct ArrayTypeConstructor final
        : Statement,
          utility::ConcreteNode<ArrayTypeConstructor, Visitor>
    {
        ArrayTypeConstructor(
            Temporary const&      type,
            Temporary const&      length_value,
            Temporary const&      result,
            core::Location const& source_location
        );

        Temporary const& element_type;
        Temporary const& length;
        Temporary const& destination;
    };

    /// Creates an array value from an optional element type and elements.
    /// Could also be called an array literal.
    struct ArrayConstructor final : Statement,
                                    utility::ConcreteNode<ArrayConstructor, Visitor>
    {
        ArrayConstructor(
            Temporary const*                                       type,
            utility::List<std::reference_wrapper<Temporary const>> expression_list,
            Temporary const&                                       result,
            core::Location const&                                  source_location
        );

        Temporary const*                                       element_type;
        utility::List<std::reference_wrapper<Temporary const>> elements;
        Temporary const&                                       destination;
    };

    /// Enters an ordered scope, which is used to manage variable lifetimes and visibility.
    struct OrderedScopeEnter final : Statement,
                                     utility::ConcreteNode<OrderedScopeEnter, Visitor>
    {
        explicit OrderedScopeEnter(core::Location const& source_location);

        [[nodiscard]] bool isRelevantForReachability() const override;
    };

    /// Exits an ordered scope, which is used to manage variable lifetimes and visibility.
    struct OrderedScopeExit final : Statement,
                                    utility::ConcreteNode<OrderedScopeExit, Visitor>
    {
        OrderedScopeExit(
            OrderedScopeEnter const& entry,
            core::Location const&    source_location
        );

        [[nodiscard]] bool isRelevantForReachability() const override;

        OrderedScopeEnter const& enter;
    };

    /// Set the return value of the current function.
    /// This may only be called at most once per function execution.
    /// The statement is necessary to allow persisting the return value even after all scopes and their temporaries have been destroyed.
    struct SetReturnValue final : Statement,
                                  utility::ConcreteNode<SetReturnValue, Visitor>
    {
        SetReturnValue(
            Temporary const&      return_value,
            core::Location const& source_location
        );

        Temporary const& value;
    };

    /// Auxiliary nodes that are used as parts of links and statements.
    struct Auxiliary : virtual Node, virtual utility::AbstractNode<Visitor>
    {
    };

    /// A case of a switch link. Has either a single pattern or no patterns if it matches everything.
    struct SwitchCase final : Auxiliary, utility::ConcreteNode<SwitchCase, Visitor>
    {
        // todo: do not forget that the patterns should become compiletime-only at some point
        // todo: then we could have a pattern node type, and default would become an actual node, and we would not need the pattern location here and all the other nodes as a separate field

        SwitchCase(
            Temporary const&      temporary,
            BasicBlock const&     block,
            core::Location const& source_location
        );
        SwitchCase(
            core::Location const& loc,
            BasicBlock const&     block,
            core::Location const& source_location
        );

        core::Location    pattern_location;
        Temporary const*  pattern;
        BasicBlock const& target;
    };

    /// A parameter for a callable, e.g. a function or lambda.
    struct
        Parameter final // todo: make this a node, make it visitable, use that in visitors
    {
        Parameter(
            core::Identifier const& name,
            Temporary const&        t,
            core::Location const&   source_location
        );

        core::Identifier identifier;
        Temporary const& type;
        core::Location   location;
    };

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        virtual void visit(Flows const& flows)                    = 0;
        virtual void visit(UnorderedScope const& unordered_scope) = 0;

        virtual void visit(Flow const& flow) = 0;

        virtual void visit(BasicBlock const& basic_block) = 0;

        virtual void visit(ErrorLink const& error_link) = 0;
        virtual void visit(Return const& return_link)   = 0;
        virtual void visit(Branch const& branch_link)   = 0;
        virtual void visit(Jump const& jump_link)       = 0;
        virtual void visit(Switch const& switch_link)   = 0;

        virtual void visit(ErrorStatement const& error_statement)           = 0;
        virtual void visit(Pass const& pass_statement)                      = 0;
        virtual void visit(Assert const& assert_statement)                  = 0;
        virtual void visit(Store const& store)                              = 0;
        virtual void visit(Access const& access)                            = 0;
        virtual void visit(Temporary const& temporary)                      = 0;
        virtual void visit(Dereference const& dereference)                  = 0;
        virtual void visit(Intrinsic const& intrinsic)                      = 0;
        virtual void visit(Call const& call)                                = 0;
        virtual void visit(Subscript const& subscript)                      = 0;
        virtual void visit(FunctionConstructor const& function_constructor) = 0;
        virtual void visit(Constant const& constant)                        = 0;
        virtual void visit(Default const& default_value)                    = 0;
        virtual void visit(CurrentScope const& current_scope)               = 0;
        virtual void visit(
            GetUnaryOperatorFunctionIdentifier const&
                get_unary_operator_function_identifier
        ) = 0;
        virtual void visit(
            GetBinaryOperatorFunctionIdentifier const&
                get_binary_operator_function_identifier
        )                                                                 = 0;
        virtual void visit(TypeOf const& type_of)                         = 0;
        virtual void visit(ArrayTypeConstructor const& create_array_type) = 0;
        virtual void visit(ArrayConstructor const& array_constructor)     = 0;
        virtual void visit(OrderedScopeEnter const& scope_enter)          = 0;
        virtual void visit(OrderedScopeExit const& scope_exit)            = 0;
        virtual void visit(SetReturnValue const& set_return_value)        = 0;

        virtual void visit(SwitchCase const& switch_case) = 0;

        ~Visitor() override = default;
    };
}

#endif
