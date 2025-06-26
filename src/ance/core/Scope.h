#ifndef ANCE_CORE_SCOPE_H
#define ANCE_CORE_SCOPE_H

#include "ance/core/Identifier.h"
#include "ance/core/Location.h"

#include "ance/utility/Owners.h"

namespace ance::core
{
    class Variable;
    class Type;

    /// Represents a scope in a program.
    /// Scopes hold named entities.
    class Scope
    {
        // todo: when later doing the validation with checking which variables will be declared later and so on, do not hold the state of those checks in the scope, but locally when checking
        // todo: when checking for a part on which entities it depends, create a new EST visitor that just collects dependencies and do not use scope at that point
        // todo: generally, this should hold minimal state and be step-independent
    public:

        /// Create a new scope without a parent.
        Scope();
        ~Scope();

        /// Create a new child scope within this scope.
        /// \return The child scope
        utility::Owned<Scope> createChild();

        /// Add a variable to the scope.
        /// \param identifier The identifier of the variable.
        /// \param location The location where the variable was defined.
        Variable const& addVariable(Identifier const& identifier, Location const& location);

    private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
