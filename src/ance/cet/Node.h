#ifndef ANCE_CET_NODE_H
#define ANCE_CET_NODE_H

#include "ance/core/Reporter.h"

#include "ance/utility/Node.h"


/// The compile-able entity tree (CET) namespace.
namespace ance::cet
{
    class Visitor;

    /// Base class for all nodes in the CET.
    struct Node : virtual utility::AbstractNode<Visitor>
    {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    /// A unit of compilation.
    struct Unit final
        : Node
        , utility::ConcreteNode<Unit, Visitor>
    {
        Unit();
    };

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        virtual void visit(Unit const& unit) = 0;

        ~Visitor() override = default;
    };
}

#endif
