#ifndef ANCE_RET_NODE_H
#define ANCE_RET_NODE_H

#include "ance/core/Identifier.h"
#include "ance/core/Reporter.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Node.h"
#include "ance/utility/Owners.h"

/**
 * The resolved element tree (RET) namespace.
 */
namespace ance::ret
{
  class Visitor;

  /**
   * Base class for all nodes in the RET.
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
