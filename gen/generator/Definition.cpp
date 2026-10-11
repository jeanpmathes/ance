#include "Definition.h"
#include "DefinitionRegistry.h"

Definition::Definition()
{
    DefinitionRegistry::registerDefinition(this);
}
