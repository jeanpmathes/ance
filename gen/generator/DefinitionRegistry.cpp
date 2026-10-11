#include "DefinitionRegistry.h"

std::vector<Definition const*> DefinitionRegistry::definitions_;

void DefinitionRegistry::registerDefinition(Definition const* const definition)
{
    definitions_.push_back(definition);
}

std::span<Definition const* const> DefinitionRegistry::getDefinitions()
{
    return definitions_;
}
