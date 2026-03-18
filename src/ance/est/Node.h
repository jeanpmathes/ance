#ifndef ANCE_EST_NODE_H
#define ANCE_EST_NODE_H

#include "ance/core/AccessModifier.h"
#include "ance/core/Assigner.h"
#include "ance/core/ExecutionModifier.h"
#include "ance/core/Identifier.h"
#include "ance/core/Reporter.h"
#include "ance/core/UnaryOperator.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

/// The expanded syntax tree (EST) namespace.
/// The EST is similar to the AST, but without syntactic sugar.
namespace ance::est
{
    class Visitor;

    /// Base class for all nodes in the EST.
    struct Node : virtual utility::AbstractNode<Visitor>
    {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    struct Statement;
    struct Expression;

    /// Base class for all declaration nodes in the EST.
    struct Declaration
        : virtual Node
        , virtual utility::AbstractNode<Visitor>
    {
        [[nodiscard]] virtual std::string displayName() const = 0;
    };

    /// Represents a source file creating an unordered scope.
    /// Note that actual source files may contain a top-level ordered scope,
    /// which would be represented as a statement node instead of a file node.
    struct File final
        : Node
        , utility::ConcreteNode<File, Visitor>
    {
        File(utility::List<utility::Owned<Declaration>> declaration_list, core::Location const& source_location);

        utility::List<utility::Owned<Declaration>> declarations = {};
    };

    /// A runnable declaration runs a statement in an unordered scope.
    struct RunnableDeclaration final
        : Declaration
        , utility::ConcreteNode<RunnableDeclaration, Visitor>
    {
        RunnableDeclaration(utility::Owned<Statement> body_statement, core::Location const& source_location);

        [[nodiscard]] std::string displayName() const override;

        utility::Owned<Statement> body;
    };

    /// Declares a variable in an unordered scope.
    struct VariableDeclaration final
        : Declaration
        , utility::ConcreteNode<VariableDeclaration, Visitor>
    {
        VariableDeclaration(core::AccessModifier                          access,
                            core::ExecutionModifier                       execution,
                            core::Identifier const&                       name,
                            utility::Owned<Expression>                    t,
                            core::Assigner                                assignment,
                            utility::Optional<utility::Owned<Expression>> definition,
                            core::Location const&                         source_location);

        [[nodiscard]] std::string displayName() const override;

        core::AccessModifier                          access_modifier;
        core::ExecutionModifier                       execution_modifier;
        core::Identifier                              identifier;
        utility::Owned<Expression>                    type;
        core::Assigner                                assigner;
        utility::Optional<utility::Owned<Expression>> value;
    };

    /// Statement node in the EST.
    struct Statement
        : virtual Node
        , virtual utility::AbstractNode<Visitor>
    {
        /// Check if the statement is a compound statement, e.g. a block.
        [[nodiscard]] virtual bool isCompound() const;
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

    /// Block statement, containing multiple statements.
    struct Block final
        : Statement
        , utility::ConcreteNode<Block, Visitor>
    {
        Block(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location);

        [[nodiscard]] bool isCompound() const override;

        utility::List<utility::Owned<Statement>> statements = {};
    };

    /// Statement that simply wraps an expression, discarding its result.
    struct Independent final
        : Statement
        , utility::ConcreteNode<Independent, Visitor>
    {
        Independent(utility::Owned<Expression> independent_expression, core::Location const& source_location);

        utility::Owned<Expression> expression;
    };

    /// An assignment statement assigns a value to an assignable.
    struct Assignment final
        : Statement
        , utility::ConcreteNode<Assignment, Visitor>
    {
        Assignment(utility::Owned<Expression> left, core::Assigner assignment, utility::Owned<Expression> right, core::Location const& source_location);

        utility::Owned<Expression> assignee;
        core::Assigner             assigner;
        utility::Owned<Expression> value;
    };

    /// An if-statement chooses one of two blocks to execute based on a condition.
    struct If final
        : Statement
        , utility::ConcreteNode<If, Visitor>
    {
        If(utility::Owned<Expression> expression,
           utility::Owned<Statement>  then_block,
           utility::Owned<Statement>  else_block,
           core::Location const&      source_location);

        utility::Owned<Expression> condition;
        utility::Owned<Statement>  true_block;
        utility::Owned<Statement>  false_block;
    };

    /// A loop statement executes a block of code repeatedly and unconditionally.
    struct Loop final
        : Statement
        , utility::ConcreteNode<Loop, Visitor>
    {
        Loop(utility::Owned<Statement> statement, core::Location const& source_location);

        utility::Owned<Statement> body;
    };

    /// Break statement exits the nearest enclosing loop.
    struct Break final
        : Statement
        , utility::ConcreteNode<Break, Visitor>
    {
        explicit Break(core::Location const& source_location);
    };

    /// Continue statement continues the nearest enclosing loop.
    struct Continue final
        : Statement
        , utility::ConcreteNode<Continue, Visitor>
    {
        explicit Continue(core::Location const& source_location);
    };

    /// Returns from the current runnable, optionally with a value.
    struct Return final
        : Statement
        , utility::ConcreteNode<Return, Visitor>
    {
        Return(utility::Optional<utility::Owned<Expression>> expression, core::Location const& source_location);

        utility::Optional<utility::Owned<Expression>> value;
    };

    /// Declares a local variable in an ordered scope.
    struct Let final
        : Statement
        , utility::ConcreteNode<Let, Visitor>
    {
        Let(core::Identifier const&                       name,
            utility::Owned<Expression>                    t,
            core::Assigner                                assignment,
            utility::Optional<utility::Owned<Expression>> definition,
            core::Location const&                         source_location);

        core::Identifier                              identifier;
        utility::Owned<Expression>                    type;
        core::Assigner                                assigner;
        utility::Optional<utility::Owned<Expression>> value;
    };

    /// Erases a variable from the current scope, making it inaccessible and causing destruction.
    struct Erase final
        : Statement
        , utility::ConcreteNode<Erase, Visitor>
    {
        Erase(core::Identifier const& name, core::Location const& source_location);

        core::Identifier identifier;
    };

    /// Asserts that a condition is true. If not, execution is stopped.
    struct Assert final
        : Statement
        , utility::ConcreteNode<Assert, Visitor>
    {
        Assert(utility::Owned<Expression> expression, core::Location const& source_location);

        utility::Owned<Expression> condition;
    };

    /// Expression node in the EST.
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

    /// An intrinsic expression, calling an intrinsic specified by a string.
    struct Intrinsic final
        : Expression
        , utility::ConcreteNode<Intrinsic, Visitor>
    {
        Intrinsic(utility::Owned<Expression> intrinsic_name, utility::List<utility::Owned<Expression>> argument_list, core::Location const& source_location);

        utility::Owned<Expression>                name;
        utility::List<utility::Owned<Expression>> arguments;
    };

    /// An expression that combines a sequence of statements with a final expression inside an ordered scope.
    struct BlockExpression final
        : Expression
        , utility::ConcreteNode<BlockExpression, Visitor>
    {
        BlockExpression(utility::List<utility::Owned<Statement>> statement_list, utility::Owned<Expression> expression, core::Location const& source_location);

        utility::List<utility::Owned<Statement>> statements;
        utility::Owned<Expression>               result;
    };

    /// A call expression.
    struct Call final
        : Expression
        , utility::ConcreteNode<Call, Visitor>
    {
        Call(utility::Owned<Expression> callable, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location);

        utility::Owned<Expression>                callee;
        utility::List<utility::Owned<Expression>> arguments;
    };

    struct Parameter;

    /// Creates a function.
    struct FunctionConstructor final// todo: make this an actual constructor of function types
        : Expression
        , utility::ConcreteNode<FunctionConstructor, Visitor>
    {
        FunctionConstructor(core::Identifier const&    identifier,
                            utility::List<Parameter>   params,
                            utility::Owned<Expression> type,
                            utility::Owned<Statement>  statement,
                            core::Location const&      source_location);

        core::Identifier           name;
        utility::List<Parameter>   parameters;
        utility::Owned<Expression> return_type;
        utility::Owned<Statement>  body;
    };

    /// Accesses a variable by identifier.
    struct Access final
        : Expression
        , utility::ConcreteNode<Access, Visitor>
    {
        Access(core::Identifier const& ident, core::Location const& source_location);

        core::Identifier identifier;
    };

    /// A literal for the unit value.
    struct UnitLiteral final
        : Expression
        , utility::ConcreteNode<UnitLiteral, Visitor>
    {
        explicit UnitLiteral(core::Location const& source_location);
    };

    /// A literal for a value of the size type.
    struct SizeLiteral final
        : Expression
        , utility::ConcreteNode<SizeLiteral, Visitor>
    {
        SizeLiteral(std::string text, core::Location const& source_location);

        std::string value;
    };

    /// A literal for a string value.
    struct StringLiteral final
        : Expression
        , utility::ConcreteNode<StringLiteral, Visitor>
    {
        StringLiteral(std::string text, core::Location const& source_location);

        std::string value;
    };

    /// A literal for a boolean value.
    struct BoolLiteral final
        : Expression
        , utility::ConcreteNode<BoolLiteral, Visitor>
    {
        BoolLiteral(bool v, core::Location const& source_location);

        bool value;
    };

    /// Provides the default value for a type.
    struct Default final
        : Expression
        , utility::ConcreteNode<Default, Visitor>
    {
        Default(utility::Owned<Expression> t, core::Location const& source_location);

        utility::Owned<Expression> type;
    };

    /// Expression providing the current source location.
    struct Here final
        : Expression
        , utility::ConcreteNode<Here, Visitor>
    {
        explicit Here(core::Location const& source_location);
    };

    /// Applies an operation to an operand.
    struct UnaryOperation final
        : Expression
        , utility::ConcreteNode<UnaryOperation, Visitor>
    {
        UnaryOperation(core::UnaryOperator const& kind, utility::Owned<Expression> expression, core::Location const& source_location);

        core::UnaryOperator        op;
        utility::Owned<Expression> operand;
    };

    /// Gives the type of the value produced by an expression - the expression WILL BE evaluated.
    struct TypeOf final
        : Expression
        , utility::ConcreteNode<TypeOf, Visitor>
    {
        TypeOf(utility::Owned<Expression> e, core::Location const& source_location);

        utility::Owned<Expression> expression;
    };

    /// A parameter for a callable, e.g. a function or lambda.
    struct Parameter final
    {
        Parameter(core::Identifier const& name, utility::Owned<Expression> t, core::Location const& source_location);

        core::Identifier           identifier;
        utility::Owned<Expression> type;
        core::Location             location;
    };

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        ~Visitor() override = default;

        virtual void visit(File const& file) = 0;

        virtual void visit(RunnableDeclaration const& runnable)             = 0;
        virtual void visit(VariableDeclaration const& variable_declaration) = 0;

        virtual void visit(ErrorStatement const& error)        = 0;
        virtual void visit(Pass const& pass_statement)         = 0;
        virtual void visit(Block const& block)                 = 0;
        virtual void visit(Independent const& independent)     = 0;
        virtual void visit(Assignment const& assignment)       = 0;
        virtual void visit(If const& if_statement)             = 0;
        virtual void visit(Loop const& loop)                   = 0;
        virtual void visit(Break const& break_statement)       = 0;
        virtual void visit(Continue const& continue_statement) = 0;
        virtual void visit(Return const& return_statement)     = 0;
        virtual void visit(Let const& let)                     = 0;
        virtual void visit(Erase const& erase)                 = 0;
        virtual void visit(Assert const& assert)               = 0;

        virtual void visit(ErrorExpression const& error)                    = 0;
        virtual void visit(Intrinsic const& intrinsic)                      = 0;
        virtual void visit(BlockExpression const& block_expression)         = 0;
        virtual void visit(Call const& call)                                = 0;
        virtual void visit(FunctionConstructor const& function_constructor) = 0;
        virtual void visit(Access const& access)                            = 0;
        virtual void visit(UnitLiteral const& unit_literal)                 = 0;
        virtual void visit(SizeLiteral const& size_literal)                 = 0;
        virtual void visit(StringLiteral const& string_literal)             = 0;
        virtual void visit(BoolLiteral const& bool_literal)                 = 0;
        virtual void visit(Default const& default_value)                    = 0;
        virtual void visit(Here const& here)                                = 0;
        virtual void visit(UnaryOperation const& unary_operation)           = 0;
        virtual void visit(TypeOf const& type_of)                           = 0;
    };
}

#endif
