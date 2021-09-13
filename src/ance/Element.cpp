#include "Element.h"

void ance::Element::addChild(ance::Element& child)
{
    children_.emplace_back(child);
}

size_t ance::Element::childCount()
{
    return children_.size();
}

ance::Element& ance::Element::getChild(size_t index)
{
    return children_[index];
}
