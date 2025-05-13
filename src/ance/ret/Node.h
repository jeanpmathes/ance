#ifndef ANCE_RET_NODE_H
#define ANCE_RET_NODE_H

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

    class Scope;
    class Variable;
    class Function;
}

/// The resolved element tree (RET) namespace.
namespace ance::ret
{
    class Visitor;

    /// Base class for all nodes in the RET.
    struct Node : virtual utility::AbstractNode<Visitor>
    {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    /// Statement node in the RET.
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

    /// Block statement, containing multiple statements.
    struct Block final
        : Statement
        , utility::ConcreteNode<Block, Visitor>
    {
        Block(utility::Owned<core::Scope> own_scope, utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location);

        utility::Owned<core::Scope> scope;
        utility::List<utility::Owned<Statement>> statements = {};
    };

    struct Expression;

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
        Let(core::Variable const& identifier, utility::Optional<utility::Owned<Expression>> definition, core::Location const& source_location);

        core::Variable const& variable;
        utility::Optional<utility::Owned<Expression>> value;
    };

    /// Assigns the result of an expression to a variable.
    struct Assignment final
        : Statement
        , utility::ConcreteNode<Assignment, Visitor>
    {
        Assignment(core::Variable const& assigned, utility::Owned<Expression> expression, core::Location const& source_location);

        core::Variable const& variable;
        utility::Owned<Expression> value;
    };

    /// An if-statement chooses one of two blocks to execute based on a condition.
    struct If final
        : Statement
        , utility::ConcreteNode<If, Visitor>
    {
        If(utility::Owned<Expression> expression,
           utility::Owned<Statement>      then_block,
           utility::Owned<Statement>      else_block,
           core::Location const&      source_location);

        utility::Owned<Expression> condition;
        utility::Owned<Statement>  true_block;
        utility::Owned<Statement>  false_block;
    };

    /// Unconditionally loops over a block of statements.
    struct Loop final
        : Statement
        , utility::ConcreteNode<Loop, Visitor>
    {
        Loop(utility::Owned<Statement>  statement,
             core::Location const&      source_location);
        
        utility::Owned<Statement>  body;
    };

    /// Breaks out of the current loop.
    struct Break final
        : Statement
        , utility::ConcreteNode<Break, Visitor>
    {
        explicit Break(core::Location const& source_location);
    };

    /// Continues to the next iteration of the current loop.
    struct Continue final
        : Statement
        , utility::ConcreteNode<Continue, Visitor>
    {
        explicit Continue(core::Location const& source_location);
    };

    /// Expression node in the RET.
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

    /// Performs a compiler-provided operation like operators.
    struct Intrinsic final
        : Expression
        , utility::ConcreteNode<Intrinsic, Visitor>
    {
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
        , utility::ConcreteNode<Access, Visitor>
    {
        Access(core::Variable const& accessed, core::Location const& source_location);

        core::Variable const& variable;
    };

    /// Holds a constant value, known at compile time.
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

        virtual void visit(ErrorExpression const& error) = 0;
        virtual void visit(Intrinsic const& intrinsic)   = 0;
        virtual void visit(Call const& call)             = 0;
        virtual void visit(Access const& access)         = 0;
        virtual void visit(Constant const& constant)     = 0;
        virtual void visit(UnaryOperation const& unary_operation) = 0;
    };
}

#endif
