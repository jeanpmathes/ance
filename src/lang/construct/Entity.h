#ifndef ANCE_SRC_LANG_CONSTRUCT_ENTITY_H_
#define ANCE_SRC_LANG_CONSTRUCT_ENTITY_H_

#include "lang/utility/Identifier.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Entity;

    class FunctionGroup;
    class Function;
    class Type;
    class Variable;

    template<>
    struct HandleConfig<FunctionGroup> {
        using BaseType = Entity;
    };

    template<>
    struct HandleConfig<Function> {
        using BaseType = Entity;
    };

    template<>
    struct HandleConfig<Type> {
        using BaseType = Entity;
    };

    template<>
    struct HandleConfig<Variable> {
        using BaseType = Entity;
    };

    class Scope;
    class Context;

    /**
     * Any named entity in the language.
     * Will be replaced by something like Value in the future, when types, variables and function (groups) are unified.
     */
    class Entity
    {
      public:
        virtual ~Entity() = default;

        /**
         * Whether this entity is defined.
         * @return True if this entity is defined.
         */
        [[nodiscard]] virtual bool isDefined() const = 0;

        /**
         * Get the name of this entity.
         * @return The name.
         */
        [[nodiscard]] virtual lang::Identifier const& name() const = 0;

        /**
         * Get the name of this entity with helpful annotations. Useful for validation messages.
         * @return The annotated name.
         */
        [[nodiscard]] virtual std::string getAnnotatedName() const;

        /**
         * Get the scope this entity is defined in.
         * @return The scope.
         */
        [[nodiscard]] virtual lang::Scope* scope() = 0;

        /**
         * Get the scope this entity is defined in.
         * @return The scope.
         */
        [[nodiscard]] virtual lang::Scope const* scope() const = 0;

        /**
         * Set the scope this entity is defined in.
         * If the scope is already set on creation, this method only performs a check.
         * Calling this method twice is not allowed.
         * @param scope The scope.
         */
        virtual void setContainingScope(lang::Scope* scope);

        /**
         * Get an undefined entity with the same name. Entities given by literals cannot be undefined.
         * Therefore, for these entities the returned entity will already defined - but in the new context.
         */
        virtual lang::ResolvingHandle<lang::Entity> getUndefinedClone(lang::Context& new_context) const = 0;

        template<typename Desired>
        lang::ResolvingHandle<Desired> getUndefinedClone(lang::Context& new_context) const
        {
            auto const* self = dynamic_cast<Desired const*>(this);

            if (self != nullptr) { return this->getUndefinedClone(new_context).as<Desired>().value(); }

            return lang::makeHandled<Desired>(name());
        }
    };
}

#endif
