#ifndef DEFINITION_REGISTRY_H
#define DEFINITION_REGISTRY_H

#include <span>
#include <vector>

class Definition;

/// Keeps track of all registered definitions.
class DefinitionRegistry
{
  public:
    DefinitionRegistry() = delete;

    static void registerDefinition(Definition const* definition);
    [[nodiscard]] static std::span<Definition const* const> getDefinitions();

  private:
    static std::vector<Definition const*> definitions_;
};

#endif
