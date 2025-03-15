#ifndef ANCE_RET_NODE_H
#define ANCE_RET_NODE_H

#include "ance/core/Identifier.h"
#include "ance/core/Reporter.h"
#include "ance/core/Variable.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

namespace ance::core
{
    struct Intrinsic;

    class Scope;
    class Variable;
}

/**
 * The resolved element tree (RET) namespace.
 */
namespace ance::ret
{
    class Visitor;

    /**
     * Base class for all nodes in the RET.
     */
    struct Node : virtual utility::AbstractNode<Visitor>
    {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    /**
     * Statement node in the RET.
     */
    struct Statement
        : virtual Node
        , virtual utility::AbstractNode<Visitor>
    {
    };

    /**
     * Error statement, mostly as pass-through from the AST.
     */
    struct ErrorStatement final
        : Statement
        , utility::ConcreteNode<ErrorStatement, Visitor>
    {
        explicit ErrorStatement(core::Location const& source_location);
    };

    /**
     * Block statement, containing multiple statements.
     */
    struct Block final
        : Statement
        , utility::ConcreteNode<Block, Visitor>
    {
        Block(utility::Owned<core::Scope> own_scope, utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location);

        utility::Owned<core::Scope> scope;
        utility::List<utility::Owned<Statement>> statements = {};
    };

    struct Expression;

    /**
     * Statement that simply wraps an expression.
     */
    struct Independent final
        : Statement
        , utility::ConcreteNode<Independent, Visitor>
    {
        Independent(utility::Owned<Expression> independent_expression, core::Location const& source_location);

        utility::Owned<Expression> expression;
    };

    /**
     * A let statement declares a variable and can also define its value.
     */
    struct Let final
        : Statement
        , utility::ConcreteNode<Let, Visitor>
    {
        Let(core::Variable const& identifier, utility::Optional<utility::Owned<Expression>> definition, core::Location const& source_location);

        core::Variable const& variable;
        utility::Optional<utility::Owned<Expression>> value;
    };

    /**
     * Expression node in the RET.
     */
    struct Expression
        : virtual Node
        , virtual utility::AbstractNode<Visitor>
    {
    };

    /**
     * Error expression, mostly as pass-through from the AST.
     */
    struct ErrorExpression final
        : Expression
        , utility::ConcreteNode<ErrorExpression, Visitor>
    {
        explicit ErrorExpression(core::Location const& source_location);
    };

    /**
     * Performs a compiler-provided operation like operators or functions.
     */
    struct Intrinsic final
        : Expression
        , utility::ConcreteNode<Intrinsic, Visitor>
    {
        Intrinsic(core::Intrinsic const& used, core::Location const& source_location);

        core::Intrinsic const& intrinsic;
    };

    /**
     * Access is an expression that reads the value of a variable.
     */
    struct Access final
        : Expression
        , utility::ConcreteNode<Access, Visitor>
    {
        Access(core::Variable const& accessed, core::Location const& source_location);

        core::Variable const& variable;
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

        virtual void visit(ErrorExpression const& error) = 0;
        virtual void visit(Intrinsic const& intrinsic)   = 0;
        virtual void visit(Access const& access)         = 0;
    };
}

#endif
