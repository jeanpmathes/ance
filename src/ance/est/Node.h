#ifndef ANCE_EST_NODE_H
#define ANCE_EST_NODE_H

#include "ance/core/Identifier.h"
#include "ance/core/Reporter.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

/**
 * The expanded syntax tree (EST) namespace.
 * The EST is similar to the AST, but without syntactic sugar.
 */
namespace ance::est
{
    class Visitor;

    /**
     * Base class for all nodes in the EST.
     */
    struct Node : virtual utility::AbstractNode<Visitor> {
        explicit Node(core::Location const& source_location);

        core::Location location;
    };

    class Visitor : public utility::AbstractVisitor<Visitor>
    {
      public:
        using AbstractVisitor::visit;

        ~Visitor() override = default;
    };
}

#endif
