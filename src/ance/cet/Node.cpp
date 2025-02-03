#include "Node.h"

ance::cet::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::cet::Unit::Unit() : Node(core::Location::global()) {}
