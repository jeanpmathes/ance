#include "Expander.h"

struct ance::est::Expander::Implementation
{
};

ance::est::Expander::Expander() : implementation_(utility::makeOwned<Implementation>()) {}

ance::est::Expander::~Expander() = default;
