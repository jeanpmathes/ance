#ifndef ANCE_SRC_LANG_UTILITY_TYPEREGISTRY_H_
#define ANCE_SRC_LANG_UTILITY_TYPEREGISTRY_H_

#include <optional>
#include <vector>

#include "lang/type/Type.h"
#include "lang/utility/Empty.h"
#include "lang/utility/ResolvingHandle.h"

using TypeHandle = lang::ResolvingHandle<lang::Type>;

namespace lang
{
    class TypeDefinitionRegistry
    {
      public:
        TypeDefinitionRegistry()                                             = default;
        TypeDefinitionRegistry(TypeDefinitionRegistry&&) noexcept            = default;
        TypeDefinitionRegistry& operator=(TypeDefinitionRegistry&&) noexcept = default;

        TypeDefinitionRegistry(TypeDefinitionRegistry&)            = default;
        TypeDefinitionRegistry& operator=(TypeDefinitionRegistry&) = default;

        /**
         * Set the scope that will contain the non-custom types. Call this method once.
         * @param scope The default containing scope.
         */
        virtual void setDefaultContainingScope(lang::Scope& scope) = 0;

        /**
         * Resolve the used types.
         */
        virtual void resolve() = 0;

        /**
         * Called after all entities have been resolved.
         */
        virtual void postResolve() = 0;

        /**
         * Build all native declarations.
         * @param context The compile context.
         */
        virtual void buildNativeDeclarations(CompileContext& context) = 0;

        /**
         * Build all native definitions.
         * @param context The compile context.
         */
        virtual void buildNativeDefinitions(CompileContext& context) = 0;

        /**
         * Clear all types in this registry.
         */
        virtual void clear() = 0;

        virtual ~TypeDefinitionRegistry() = default;
    };

    /**
     * A registry that manages type definitions.
     * @tparam OtherKey Another key type, can be empty.
     */
    template<typename OtherKey = lang::Empty>
    class TypeRegistry : public TypeDefinitionRegistry
    {
      public:
        using UsedTypes = std::vector<TypeHandle>;
        using Key       = std::pair<UsedTypes, OtherKey>;
        using Entry     = std::pair<Key, TypeHandle>;

        TypeRegistry()                                   = default;
        TypeRegistry(TypeRegistry&&) noexcept            = default;
        TypeRegistry& operator=(TypeRegistry&&) noexcept = default;

        TypeRegistry(TypeRegistry&)            = default;
        TypeRegistry& operator=(TypeRegistry&) = default;

        Optional<TypeHandle> get(UsedTypes type_keys, OtherKey other_keys);
        void                 add(UsedTypes&& type_keys, OtherKey other_key, TypeHandle type);

        void setDefaultContainingScope(lang::Scope& scope) override;
        void resolve() override;
        void postResolve() override;

        void buildNativeDeclarations(CompileContext& context) override;
        void buildNativeDefinitions(CompileContext& context) override;

        void clear() override;

        ~TypeRegistry() override = default;

      private:
        std::vector<Entry> types_;
        lang::Scope*       scope_ {nullptr};
    };
}

#include "TypeRegistry.tpp"

#endif
