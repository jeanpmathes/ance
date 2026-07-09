#ifndef ANCE_AST_NODE_H
#define ANCE_AST_NODE_H

#include "ance/core/AccessModifier.h"
#include "ance/core/Assigner.h"
#include "ance/core/BinaryOperator.h"
#include "ance/core/ExecutionModifier.h"
#include "ance/core/Identifier.h"
#include "ance/core/Precision.h"
#include "ance/core/Reporter.h"
#include "ance/core/UnaryOperator.h"
#include "ance/core/VariabilityModifier.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

namespace ance::ast
{
    class Visitor;

    /// Base class for all nodes in the AST.
    struct Node : virtual utility::AbstractNode<Visitor>
    {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    struct Declaration;
    struct Statement;
    struct Expression;
    struct Parameter;

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

    /// Declarations are nodes that introduce named entities and are used in unordered scopes.
    struct Declaration
        : virtual Node
        , virtual utility::AbstractNode<Visitor>
    {
    };

    /// A declaration that could not be parsed correctly.
    struct ErrorDeclaration final
        : Declaration
        , utility::ConcreteNode<ErrorDeclaration, Visitor>
    {
        explicit ErrorDeclaration(core::Location const& source_location);
    };

    /// Declares a statement to be run in an unordered scope.
    struct RunnableDeclaration final
        : Declaration
        , utility::ConcreteNode<RunnableDeclaration, Visitor>
    {
        RunnableDeclaration(utility::Owned<Statement> statement, core::Location const& source_location);

        utility::Owned<Statement> body;
    };

    /// A variable declaration in an unordered scope.
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

        core::AccessModifier                          access_modifier;
        core::ExecutionModifier                       execution_modifier;
        core::Identifier                              identifier;
        utility::Owned<Expression>                    type;
        core::Assigner                                assigner;
        utility::Optional<utility::Owned<Expression>> value;
    };

    /// A function declaration in an unordered scope.
    struct FunctionDeclaration final
        : Declaration
        , utility::ConcreteNode<FunctionDeclaration, Visitor>
    {
        FunctionDeclaration(core::AccessModifier                          access,
                            core::ExecutionModifier                       execution,
                            core::Identifier const&                       name,
                            utility::List<Parameter>                      params,
                            utility::Optional<utility::Owned<Expression>> type,
                            utility::Owned<Statement>                     function_body,
                            core::Location const&                         source_location);

        core::AccessModifier                          access_modifier;
        core::ExecutionModifier                       execution_modifier;
        core::Identifier                              identifier;
        utility::List<Parameter>                      parameters;
        utility::Optional<utility::Owned<Expression>> return_type;
        utility::Owned<Statement>                     body;
    };

    /// A statement is an independent part of code.
    struct Statement
        : virtual Node
        , virtual utility::AbstractNode<Visitor>
    {
        /// Check if the statement is a compound statement, e.g. a block.
        [[nodiscard]] virtual bool isCompound() const;
    };

    /// A statement that could not be parsed correctly.
    struct ErrorStatement final
        : Statement
        , utility::ConcreteNode<ErrorStatement, Visitor>
    {
        explicit ErrorStatement(core::Location const& source_location);
    };

    /// A block statement combines multiple statements into a single statement, creating a new ordered scope.
    struct Block final
        : Statement
        , utility::ConcreteNode<Block, Visitor>
    {
        Block(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location);

        [[nodiscard]] bool isCompound() const override;

        utility::List<utility::Owned<Statement>> statements = {};
    };

    struct Expression;

    /// An independent expression statement is a statement that consists of a single expression.
    struct Independent final
        : Statement
        , utility::ConcreteNode<Independent, Visitor>
    {
        Independent(utility::Owned<Expression> independent_expression, core::Location const& source_location);

        utility::Owned<Expression> expression;
    };

    /// A bind statement binds a value to a name in a local scope as a variable or constant, or simply prepares the binding of a name.
    struct Bind final
        : Statement
        , utility::ConcreteNode<Bind, Visitor>
    {
        Bind(core::Identifier const&                       name,
             core::VariabilityModifier                     variability_modifier,
             utility::Owned<Expression>                    type_expression,
             core::Assigner                                assignment,
             utility::Optional<utility::Owned<Expression>> definition,
             core::Location const&                         source_location);

        core::Identifier                              identifier;
        core::VariabilityModifier                     variability;
        utility::Owned<Expression>                    type;
        core::Assigner                                assigner;
        utility::Optional<utility::Owned<Expression>> value;
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

    /// An if-statement chooses one of two statements to execute based on a condition.
    /// The second statement is optional.
    struct If final
        : Statement
        , utility::ConcreteNode<If, Visitor>
    {
        If(utility::Owned<Expression>                   expression,
           utility::Owned<Statement>                    then_part,
           utility::Optional<utility::Owned<Statement>> else_part,
           core::Location const&                        source_location);

        utility::Owned<Expression>                   condition;
        utility::Owned<Statement>                    true_part;
        utility::Optional<utility::Owned<Statement>> false_part;
    };

    /// Unconditionally repeats a statement.
    struct Loop final
        : Statement
        , utility::ConcreteNode<Loop, Visitor>
    {
        Loop(utility::Owned<Statement> statement, core::Location const& source_location);

        utility::Owned<Statement> body;
    };

    /// Breaks out of the innermost containing loop.
    struct Break final
        : Statement
        , utility::ConcreteNode<Break, Visitor>
    {
        explicit Break(core::Location const& source_location);
    };

    /// Begins a new iteration of the innermost containing loop.
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

    /// Loops as long as the condition is true.
    struct While final
        : Statement
        , utility::ConcreteNode<While, Visitor>
    {
        While(utility::Owned<Expression> expression, utility::Owned<Statement> statement, core::Location const& source_location);

        utility::Owned<Expression> condition;
        utility::Owned<Statement>  body;
    };

    struct MatchCase;

    /// Matches an expression against a series of patterns and executes the code of the first matching pattern.
    struct Match final
        : Statement
        , utility::ConcreteNode<Match, Visitor>
    {
        Match(utility::Owned<Expression> expression, utility::List<utility::Owned<MatchCase>> case_list, core::Location const& source_location);

        utility::Owned<Expression>               condition;
        utility::List<utility::Owned<MatchCase>> cases;
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

    /// An expression is a piece of code that produces a value.
    struct Expression
        : virtual Node
        , virtual utility::AbstractNode<Visitor>
    {
    };

    /// An expression that could not be parsed correctly.
    struct ErrorExpression final
        : Expression
        , utility::ConcreteNode<ErrorExpression, Visitor>
    {
        explicit ErrorExpression(core::Location const& source_location);
    };

    /// Logical, short-circuiting and-expression. Can be negated to create a nand-expression.
    struct And final
        : Expression
        , utility::ConcreteNode<And, Visitor>
    {
        And(utility::Owned<Expression> lhs, bool neg, utility::Owned<Expression> rhs, core::Location const& source_location);

        utility::Owned<Expression> left;
        bool                       negated;
        utility::Owned<Expression> right;
    };

    /// Logical, short-circuiting or-expression. Can be negated to create a nor-expression.
    struct Or final
        : Expression
        , utility::ConcreteNode<Or, Visitor>
    {
        Or(utility::Owned<Expression> lhs, bool neg, utility::Owned<Expression> rhs, core::Location const& source_location);

        utility::Owned<Expression> left;
        bool                       negated;
        utility::Owned<Expression> right;
    };

    /// A call is an expression that performs the call-operator on a callable entity.
    struct Call final
        : Expression
        , utility::ConcreteNode<Call, Visitor>
    {
        Call(utility::Owned<Expression> called, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location);

        utility::Owned<Expression>                callee;
        utility::List<utility::Owned<Expression>> arguments;
    };

    /// A subscript expression accesses an element using an index.
    struct Subscript final
        : Expression
        , utility::ConcreteNode<Subscript, Visitor>
    {
        Subscript(utility::Owned<Expression> indexed_value, utility::Owned<Expression> index_value, core::Location const& source_location);

        utility::Owned<Expression> indexed;
        utility::Owned<Expression> index;
    };

    /// A lambda expression creates an anonymous function.
    struct Lambda final
        : Expression
        , utility::ConcreteNode<Lambda, Visitor>
    {
        Lambda(utility::List<Parameter>                      params,
               utility::Optional<utility::Owned<Expression>> type,
               utility::Optional<utility::Owned<Expression>> expression,
               utility::Optional<utility::Owned<Statement>>  statement,
               core::Location const&                         source_location);

        utility::List<Parameter>                      parameters;
        utility::Optional<utility::Owned<Expression>> return_type;
        utility::Optional<utility::Owned<Expression>> expression_body;
        utility::Optional<utility::Owned<Statement>>  statement_body;
    };

    /// Access is an expression that reads the value of a named entity.
    struct Access final
        : Expression
        , utility::ConcreteNode<Access, Visitor>
    {
        Access(core::Identifier const& accessed, core::Location const& source_location);

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

    /// A literal for a value of the floating point types.
    struct FloatingPointLiteral final
        : Expression
        , utility::ConcreteNode<FloatingPointLiteral, Visitor>
    {
        FloatingPointLiteral(core::Precision kind, std::string text, core::Location const& source_location);

        core::Precision precision;
        std::string     value;
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

    /// An expression that calls an intrinsic by name.
    struct Intrinsic final
        : Expression
        , utility::ConcreteNode<Intrinsic, Visitor>
    {
        Intrinsic(utility::Owned<Expression> intrinsic_name, utility::List<utility::Owned<Expression>> args, core::Location const& source_location);

        utility::Owned<Expression>                name;
        utility::List<utility::Owned<Expression>> arguments;
    };

    /// Gives the common type of the values produced by the expressions - the expressions WILL BE evaluated.
    struct TypeOf final// todo: should no longer evaluate the expressions
        : Expression
        , utility::ConcreteNode<TypeOf, Visitor>
    {
        TypeOf(utility::List<utility::Owned<Expression>> expression_list, core::Location const& source_location);

        utility::List<utility::Owned<Expression>> expressions;
    };

    /// An expression that constructs an array type.
    /// The array type has a fixed length and element type.
    struct ArrayTypeConstructor final
        : Expression
        , utility::ConcreteNode<ArrayTypeConstructor, Visitor>
    {
        ArrayTypeConstructor(utility::Owned<Expression> type, utility::Owned<Expression> length_expression, core::Location const& source_location);

        utility::Owned<Expression> element_type;
        utility::Owned<Expression> length;
    };

    /// An expression that creates an array value.
    /// Could also be called an array literal.
    struct ArrayConstructor final
        : Expression
        , utility::ConcreteNode<ArrayConstructor, Visitor>
    {
        ArrayConstructor(utility::Optional<utility::Owned<Expression>> type,
                         utility::List<utility::Owned<Expression>>     expression_list,
                         core::Location const&                         source_location);

        utility::Optional<utility::Owned<Expression>> element_type;
        utility::List<utility::Owned<Expression>>     elements;
    };

    /// An expression that combines a sequence of statements with a final expression inside an ordered scope.
    struct BlockExpression final
        : Expression
        , utility::ConcreteNode<BlockExpression, Visitor>
    {
        BlockExpression(utility::List<utility::Owned<Statement>>      statement_list,
                        utility::Optional<utility::Owned<Expression>> expression,
                        core::Location const&                         source_location);

        utility::List<utility::Owned<Statement>>      statements;
        utility::Optional<utility::Owned<Expression>> result;
    };

    /// An expression wrapped in parentheses.
    struct Parenthesis final
        : Expression
        , utility::ConcreteNode<Parenthesis, Visitor>
    {
        Parenthesis(utility::Owned<Expression> expression, core::Location const& source_location);

        utility::Owned<Expression> contained;
    };

    /// An expression that resolves to its own source location.
    struct Here final
        : Expression
        , utility::ConcreteNode<Here, Visitor>
    {
        explicit Here(core::Location const& source_location);
    };

    /// An expression that evaluates to one of two expressions based on a condition.
    struct IfExpression final
        : Expression
        , utility::ConcreteNode<IfExpression, Visitor>
    {
        IfExpression(utility::Owned<Expression>                    expression,
                     utility::Owned<Expression>                    then_part,
                     utility::Optional<utility::Owned<Expression>> else_part,
                     core::Location const&                         source_location);

        utility::Owned<Expression>                    condition;
        utility::Owned<Expression>                    then_expression;
        utility::Optional<utility::Owned<Expression>> else_expression;
    };

    struct MatchExpressionCase;

    /// An expression that evaluates to one of several expressions based on a condition.
    struct MatchExpression final
        : Expression
        , utility::ConcreteNode<MatchExpression, Visitor>
    {
        MatchExpression(utility::Owned<Expression>                         expression,
                        utility::List<utility::Owned<MatchExpressionCase>> case_list,
                        core::Location const&                              source_location);

        utility::Owned<Expression>                         condition;
        utility::List<utility::Owned<MatchExpressionCase>> cases;
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

    /// Applies a binary operation to two operands.
    struct BinaryOperation final
        : Expression
        , utility::ConcreteNode<BinaryOperation, Visitor>
    {
        BinaryOperation(utility::Owned<Expression> lhs, core::BinaryOperator kind, utility::Owned<Expression> rhs, core::Location const& source_location);

        utility::Owned<Expression> left;
        core::BinaryOperator       op;
        utility::Owned<Expression> right;
    };

    /// Auxiliary nodes that are used as parts of expressions and statements.
    struct Auxiliary
        : virtual Node
        , virtual utility::AbstractNode<Visitor>
    {
    };

    /// A case of a match statement. Has a set of patterns, or no patterns if it is the default case.
    struct MatchCase final
        : Auxiliary
        , utility::ConcreteNode<MatchCase, Visitor>
    {
        MatchCase(utility::List<utility::Owned<Expression>> pattern_list,
                  core::Location                            default_location,
                  utility::Owned<Statement>                 code,
                  core::Location const&                     source_location);

        utility::List<utility::Owned<Expression>> patterns;
        core::Location                            default_pattern_location;// todo: make default a pattern with an actual node, then no special field is needed
        utility::Owned<Statement>                 body;
    };

    /// A case of a match expression. Has a set of patterns, or no patterns if it is the default case.
    struct MatchExpressionCase final
        : Auxiliary
        , utility::ConcreteNode<MatchExpressionCase, Visitor>
    {
        MatchExpressionCase(utility::List<utility::Owned<Expression>> pattern_list,
                            core::Location const&                     default_location,
                            utility::Owned<Expression>                code,
                            core::Location const&                     source_location);

        utility::List<utility::Owned<Expression>> patterns;
        core::Location                            default_pattern_location;
        utility::Owned<Expression>                result;
    };

    /// A parameter for a callable, e.g. a function or lambda.
    struct Parameter final// todo: make this a node, make it visitable, use that in visitors
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

        virtual void visit(ErrorDeclaration const& error)       = 0;
        virtual void visit(RunnableDeclaration const& runnable) = 0;
        virtual void visit(VariableDeclaration const& global)   = 0;
        virtual void visit(FunctionDeclaration const& function) = 0;

        virtual void visit(ErrorStatement const& error)        = 0;
        virtual void visit(Block const& block)                 = 0;
        virtual void visit(Independent const& independent)     = 0;
        virtual void visit(Bind const& bind)                   = 0;
        virtual void visit(Assignment const& assignment)       = 0;
        virtual void visit(If const& if_statement)             = 0;
        virtual void visit(Loop const& loop)                   = 0;
        virtual void visit(Break const& break_statement)       = 0;
        virtual void visit(Continue const& continue_statement) = 0;
        virtual void visit(Return const& return_statement)     = 0;
        virtual void visit(While const& while_statement)       = 0;
        virtual void visit(Match const& match_statement)       = 0;
        virtual void visit(Erase const& erase)                 = 0;
        virtual void visit(Assert const& assert)               = 0;

        virtual void visit(ErrorExpression const& error)                       = 0;
        virtual void visit(And const& and_expression)                          = 0;
        virtual void visit(Or const& or_expression)                            = 0;
        virtual void visit(Call const& call)                                   = 0;
        virtual void visit(Subscript const& subscript)                         = 0;
        virtual void visit(Intrinsic const& intrinsic)                         = 0;
        virtual void visit(TypeOf const& type_of)                              = 0;
        virtual void visit(ArrayTypeConstructor const& array_type)                        = 0;
        virtual void visit(ArrayConstructor const& array_constructor)          = 0;
        virtual void visit(BlockExpression const& block_expression)            = 0;
        virtual void visit(Parenthesis const& parenthesis)                     = 0;
        virtual void visit(Lambda const& lambda)                               = 0;
        virtual void visit(Access const& access)                               = 0;
        virtual void visit(UnitLiteral const& unit_literal)                    = 0;
        virtual void visit(SizeLiteral const& size_literal)                    = 0;
        virtual void visit(FloatingPointLiteral const& floating_point_literal) = 0;
        virtual void visit(StringLiteral const& string_literal)                = 0;
        virtual void visit(BoolLiteral const& bool_literal)                    = 0;
        virtual void visit(IfExpression const& if_expression)                  = 0;
        virtual void visit(MatchExpression const& match_expression)            = 0;
        virtual void visit(Here const& here)                                   = 0;
        virtual void visit(UnaryOperation const& unary_operation)              = 0;
        virtual void visit(BinaryOperation const& binary_operation)            = 0;

        virtual void visit(MatchCase const& match_case)                      = 0;
        virtual void visit(MatchExpressionCase const& match_expression_case) = 0;
    };
}

#endif
