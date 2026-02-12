#ifndef ANCE_EST_NODE_H
#define ANCE_EST_NODE_H

#include "ance/core/Identifier.h"
#include "ance/core/Intrinsic.h"
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

    /// Describes a declaration statement, which is a top-level statement.
    struct DeclarationStatement
    {
        utility::Owned<Statement> statement;
        std::string               name;
    };

    /// Represents a source file creating an unordered scope.
    /// Note that actual source files may contain a top-level ordered scope,
    /// which would be represented as a statement node instead of a file node.
    struct File final
        : Node
        , utility::ConcreteNode<File, Visitor>
    {
        File(utility::List<DeclarationStatement> declaration_statement_list, core::Location const& source_location);

        utility::List<DeclarationStatement> declaration_statements = {};
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

    struct Expression;

    /// Statement that simply wraps an expression, discarding its result.
    struct Independent final
        : Statement
        , utility::ConcreteNode<Independent, Visitor>
    {
        Independent(utility::Owned<Expression> independent_expression, core::Location const& source_location);

        utility::Owned<Expression> expression;
    };

    /// A write statement writes a value to an assignable.
    struct Write final
        : Statement
        , utility::ConcreteNode<Write, Visitor>
    {
        Write(utility::Owned<Expression> variable, utility::Owned<Expression> expression, core::Location const& source_location);

        utility::Owned<Expression> target;
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

    /// Introduce a temporary variable, which works similar to any other local variable but does not have a name it is bound to.
    struct Temporary final
        : Statement
        , utility::ConcreteNode<Temporary, Visitor>
    {
        Temporary(utility::Optional<utility::Owned<Expression>> expression, std::string id, core::Location const& source_location);

        [[nodiscard]] std::string id() const;

        utility::Optional<utility::Owned<Expression>> definition;
        std::string                                   identifier;
    };

    /// Writes a value to a temporary variable.
    struct WriteTemporary final
        : Statement
        , utility::ConcreteNode<WriteTemporary, Visitor>
    {
        WriteTemporary(Temporary const& target, utility::Owned<Expression> expression, core::Location const& source_location);

        Temporary const&           temporary;
        utility::Owned<Expression> value;
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

    /// An intrinsic expression.
    struct Intrinsic final
        : Expression
        , utility::ConcreteNode<Intrinsic, Visitor>
    {
        Intrinsic(core::Intrinsic called, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location);

        core::Intrinsic                           intrinsic;
        utility::List<utility::Owned<Expression>> arguments;
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
    struct AnonymousFunctionConstructor final// todo: make this an actual constructor of function types
        : Expression
        , utility::ConcreteNode<AnonymousFunctionConstructor, Visitor>
    {
        AnonymousFunctionConstructor(utility::List<Parameter>   params,
                                     utility::Owned<Expression> type,
                                     utility::Owned<Statement>  statement,
                                     core::Location const&      source_location);

        utility::List<Parameter>   parameters;
        utility::Owned<Expression> return_type;
        utility::Owned<Statement>  body;
    };

    /// Reads the value of a variable.
    struct Read final
        : Expression
        , utility::ConcreteNode<Read, Visitor>
    {
        Read(utility::Owned<Expression> accessed, core::Location const& source_location);

        utility::Owned<Expression> target;
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

    /// Expression providing the current scope.
    struct CurrentScope final
        : Expression
        , utility::ConcreteNode<CurrentScope, Visitor>
    {
        explicit CurrentScope(core::Location const& source_location);
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

    /// Reads the value of a temporary variable.
    struct ReadTemporary final
        : Expression
        , utility::ConcreteNode<ReadTemporary, Visitor>
    {
        ReadTemporary(Temporary const& target, core::Location const& source_location);

        Temporary const& temporary;
    };

    /// Gives the type of the value produced by an expression - the expression WILL BE evaluated.
    struct TypeOf final
        : Expression
        , utility::ConcreteNode<TypeOf, Visitor>
    {
        TypeOf(utility::Owned<Expression> e, core::Location const& source_location);

        utility::Owned<Expression> expression;
    };

    /// Captures an identifier and allows it to be used in expressions.
    struct IdentifierCapture final
        : Expression
        , utility::ConcreteNode<IdentifierCapture, Visitor>
    {
        IdentifierCapture(core::Identifier const& ident, core::Location const& source_location);

        core::Identifier identifier;
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

        virtual void visit(ErrorStatement const& error)           = 0;
        virtual void visit(Pass const& pass_statement)            = 0;
        virtual void visit(Block const& block)                    = 0;
        virtual void visit(Independent const& independent)        = 0;
        virtual void visit(Write const& assignment)               = 0;
        virtual void visit(If const& if_statement)                = 0;
        virtual void visit(Loop const& loop)                      = 0;
        virtual void visit(Break const& break_statement)          = 0;
        virtual void visit(Continue const& continue_statement)    = 0;
        virtual void visit(Return const& return_statement)        = 0;
        virtual void visit(Temporary const& temporary)            = 0;
        virtual void visit(WriteTemporary const& write_temporary) = 0;

        virtual void visit(ErrorExpression const& error)                = 0;
        virtual void visit(Intrinsic const& intrinsic)                  = 0;
        virtual void visit(Call const& call)                            = 0;
        virtual void visit(AnonymousFunctionConstructor const& ctor)    = 0;
        virtual void visit(Read const& access)                          = 0;
        virtual void visit(UnitLiteral const& unit_literal)             = 0;
        virtual void visit(SizeLiteral const& size_literal)             = 0;
        virtual void visit(StringLiteral const& string_literal)         = 0;
        virtual void visit(BoolLiteral const& bool_literal)             = 0;
        virtual void visit(Default const& default_value)                = 0;
        virtual void visit(Here const& here)                            = 0;
        virtual void visit(CurrentScope const& current_scope)           = 0;
        virtual void visit(UnaryOperation const& unary_operation)       = 0;
        virtual void visit(ReadTemporary const& read_temporary)         = 0;
        virtual void visit(TypeOf const& type_of)                       = 0;
        virtual void visit(IdentifierCapture const& identifier_capture) = 0;
    };
}

#endif
