#ifndef ANCE_SRC_LANG_UTILITY_TYPEREGISTRY_H_
#define ANCE_SRC_LANG_UTILITY_TYPEREGISTRY_H_

#include <optional>
#include <vector>

#include "lang/type/Type.h"
#include "lang/utility/Empty.h"
#include "lang/utility/ResolvingHandle.h"

typedef lang::ResolvingHandle<lang::Type> TypeHandle;

namespace lang
{
    class TypeDefinitionRegistry
    {
      public:
        /**
         * Set the scope that will contain the non-custom types. Call this method once.
         * @param scope The default containing scope.
         */
        virtual void setDefaultContainingScope(lang::Scope* scope) = 0;

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
    };

    /**
     * A registry that manages type definitions.
     * @tparam OTHER_KEY Another key type, can be empty.
     */
    template<typename OTHER_KEY = lang::Empty>
    class TypeRegistry : public TypeDefinitionRegistry
    {
      public:
        typedef std::vector<TypeHandle>         UsedTypes;
        typedef std::pair<UsedTypes, OTHER_KEY> Key;
        typedef std::pair<Key, TypeHandle>      Entry;

        std::optional<TypeHandle> get(const UsedTypes& type_keys, const OTHER_KEY& other_keys) const;
        void                      add(UsedTypes&& type_keys, OTHER_KEY other_key, TypeHandle type);

        void setDefaultContainingScope(lang::Scope* scope) override;
        void resolve() override;
        void postResolve() override;

        void buildNativeDeclarations(CompileContext& context) override;
        void buildNativeDefinitions(CompileContext& context) override;

      private:
        std::vector<Entry> types_;
    };
}

#include "TypeRegistry.tpp"

#endif
