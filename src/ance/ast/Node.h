#ifndef ANCE_AST_NODE_H
#define ANCE_AST_NODE_H

#include "ance/core/Identifier.h"
#include "ance/core/Reporter.h"
#include "ance/core/Value.h"
#include "ance/core/UnaryOperator.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

namespace ance::core
{
    class Type;
}

/// The abstract syntax tree (AST) namespace.
namespace ance::ast
{
    class Visitor;

    /// Base class for all nodes in the AST.
    struct Node : virtual utility::AbstractNode<Visitor>
    {
        explicit Node(core::Location const& source_location);

        core::Location location;
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

    /// A block statement combines multiple statements into a single statement.
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

    /// A let statement declares a variable and can also define its value.
    struct Let final
        : Statement
        , utility::ConcreteNode<Let, Visitor>
    {
        Let(core::Identifier const&                       name,
        utility::Owned<Expression> t,
            utility::Optional<utility::Owned<Expression>> definition,
            core::Location const&                         source_location);

        core::Identifier                              identifier;
        utility::Owned<Expression> type;
        utility::Optional<utility::Owned<Expression>> value;
    };

    /// An assignment statement assigns a value to a variable.
    struct Assignment final
        : Statement
        , utility::ConcreteNode<Assignment, Visitor>
    {
        Assignment(core::Identifier const&                        assigned,
                    utility::Owned<Expression>                    expression,
                    core::Location const&                         source_location);

        core::Identifier         identifier;
        utility::Owned<Expression> value;
    };

    /// An if-statement chooses one of two statements to execute based on a condition.
    /// The second statement is optional.
    struct If final
        : Statement
        , utility::ConcreteNode<If, Visitor>
    {
        If(utility::Owned<Expression> expression,
           utility::Owned<Statement>      then_part,
           utility::Optional<utility::Owned<Statement>>      else_part,
           core::Location const&      source_location);

        utility::Owned<Expression> condition;
        utility::Owned<Statement>      true_part;
        utility::Optional<utility::Owned<Statement>>      false_part;
    };

    /// Unconditionally repeats a statement.
    struct Loop final
        : Statement
        , utility::ConcreteNode<Loop, Visitor>
    {
        Loop(utility::Owned<Statement>  statement,
             core::Location const&      source_location);

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

    /// Loops as long as the condition is true.
    struct While final
        : Statement
        , utility::ConcreteNode<While, Visitor>
    {
        While(utility::Owned<Expression> expression,
              utility::Owned<Statement>  statement,
              core::Location const&      source_location);

        utility::Owned<Expression> condition;
        utility::Owned<Statement>  body;
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

    /// A call is an expression that performs the call-operator on a callable entity.

    struct Call final
        : Expression
        , utility::ConcreteNode<Call, Visitor>
    {
        Call(core::Identifier const& callable, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location);

        core::Identifier identifier;
        utility::List<utility::Owned<Expression>> arguments;
    };

    /// Access is an expression that reads the value of a named entity.
    struct Access final
        : Expression
        , utility::ConcreteNode<Access, Visitor>
    {
        Access(core::Identifier const& accessed, core::Location const& source_location);

        core::Identifier identifier;
    };

    /// A literal value.
    struct Literal final
        : Expression
        , utility::ConcreteNode<Literal, Visitor>
    {
        Literal(utility::Shared<core::Value> literal, core::Location const& source_location);

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

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        ~Visitor() override = default;

        virtual void visit(ErrorStatement const& error)    = 0;
        virtual void visit(Block const& block)             = 0;
        virtual void visit(Independent const& independent) = 0;
        virtual void visit(Let const& let)                 = 0;
        virtual void visit(Assignment const& assignment)   = 0;
        virtual void visit(If const& if_statement)         = 0;
        virtual void visit(Loop const& loop)               = 0;
        virtual void visit(Break const& break_statement)   = 0;
        virtual void visit(Continue const& continue_statement) = 0;
        virtual void visit(While const& while_statement)   = 0;

        virtual void visit(ErrorExpression const& error) = 0;
        virtual void visit(Call const& call)             = 0;
        virtual void visit(Access const& access)         = 0;
        virtual void visit(Literal const& literal)       = 0;
        virtual void visit(UnaryOperation const& unary_operation) = 0;
    };
}

#endif
