#ifndef ANCE_EST_NODE_H
#define ANCE_EST_NODE_H

#include "ance/core/Identifier.h"
#include "ance/core/Reporter.h"
#include "ance/core/UnaryOperator.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

namespace ance::core
{
    class Type;
    class Value;
}

/// The expanded syntax tree (EST) namespace.
/// The EST is similar to the AST, but without syntactic sugar.
namespace ance::est
{
    class Visitor;

    /// Base class for all nodes in the EST.
    struct Node : virtual utility::AbstractNode<Visitor> {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    /// Statement node in the EST.
    struct Statement
        : virtual Node
        , virtual utility::AbstractNode<Visitor> {
        /// Check if the statement is a compound statement, e.g. a block.
        [[nodiscard]] virtual bool isCompound() const;
    };

    /// Error statement, mostly as pass-through from the AST.
    struct ErrorStatement final
        : Statement
        , utility::ConcreteNode<ErrorStatement, Visitor> {
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
        , utility::ConcreteNode<Block, Visitor> {
        Block(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location);

        [[nodiscard]] bool isCompound() const override;

        utility::List<utility::Owned<Statement>> statements = {};
    };

    struct Expression;

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
        Let(core::Identifier const& name, utility::Optional<utility::Owned<Expression>> definition, utility::Owned<Expression> t, core::Location const& source_location);

        core::Identifier identifier;
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
        utility::Owned<Statement>      true_block;
        utility::Owned<Statement>      false_block;
    };

    /// A loop statement executes a block of code repeatedly and unconditionally.
    struct Loop final
        : Statement
        , utility::ConcreteNode<Loop, Visitor>
    {
        Loop(utility::Owned<Statement>  statement,
             core::Location const&      source_location);
        
        utility::Owned<Statement>      body;
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

    /// Introduce a temporary variable, which works similar to any other local variable but does not have a name.
    struct Temporary final
        : Statement
        , utility::ConcreteNode<Temporary, Visitor>
    {
        Temporary(utility::Optional<utility::Owned<Expression>> expression, core::Location const& source_location);

        [[nodiscard]] std::string id() const;

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

    /// Expression node in the EST.
    struct Expression
        : virtual Node
        , virtual utility::AbstractNode<Visitor> {
    };

    /// Error expression, mostly as pass-through from the AST.
    struct ErrorExpression final
        : Expression
        , utility::ConcreteNode<ErrorExpression, Visitor> {
        explicit ErrorExpression(core::Location const& source_location);
    };

    /// A call expression.
    struct Call final
        : Expression
        , utility::ConcreteNode<Call, Visitor> {
        Call(core::Identifier const& callable, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location);

        core::Identifier identifier;
        utility::List<utility::Owned<Expression>> arguments;
    };

    /// Access is an expression that reads the value of a variable.
    struct Access final
        : Expression
        , utility::ConcreteNode<Access, Visitor> {
        Access(core::Identifier const& accessed, core::Location const& source_location);

        core::Identifier identifier;
    };

    /// A literal value.
    struct Literal final
        : Expression
        , utility::ConcreteNode<Literal, Visitor>
    {
        Literal(utility::Shared<core::Value> constant, core::Location const& source_location);

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

    /// Gives the type of the value produced by an expression - the expression WILL BE evaluated.
    struct TypeOf final
        : Expression
        , utility::ConcreteNode<TypeOf, Visitor>
    {
        TypeOf(utility::Owned<Expression> e, core::Location const& source_location);

        utility::Owned<Expression> expression;
    };

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        ~Visitor() override = default;

        virtual void visit(ErrorStatement const& error)    = 0;
        virtual void visit(Pass const& pass_statement)     = 0;
        virtual void visit(Block const& block)             = 0;
        virtual void visit(Independent const& independent) = 0;
        virtual void visit(Let const& let)                 = 0;
        virtual void visit(Assignment const& assignment)   = 0;
        virtual void visit(If const& if_statement)         = 0;
        virtual void visit(Loop const& loop)               = 0;
        virtual void visit(Break const& break_statement)   = 0;
        virtual void visit(Continue const& continue_statement) = 0;
        virtual void visit(Temporary const& temporary)     = 0;
        virtual void visit(WriteTemporary const& write_temporary) = 0;

        virtual void visit(ErrorExpression const& error) = 0;
        virtual void visit(Call const& call)             = 0;
        virtual void visit(Access const& access)         = 0;
        virtual void visit(Literal const& literal)       = 0;
        virtual void visit(UnaryOperation const& unary_operation) = 0;
        virtual void visit(ReadTemporary const& read_temporary) = 0;
        virtual void visit(TypeOf const& type_of)       = 0;
    };
}

#endif
