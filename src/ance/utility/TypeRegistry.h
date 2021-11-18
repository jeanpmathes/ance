#ifndef ANCE_SRC_ANCE_UTILITY_TYPEREGISTRY_H_
#define ANCE_SRC_ANCE_UTILITY_TYPEREGISTRY_H_

#include <optional>
#include <vector>

#include "ance/type/Type.h"
#include "ance/utility/Empty.h"
#include "ance/utility/ResolvingHandle.h"

typedef ance::ResolvingHandle<ance::Type> TypeHandle;

namespace ance
{
    /**
     * A registry that manages type definitions.
     * @tparam OTHER_KEY Another key type, can be empty.
     */
    template<typename OTHER_KEY = ance::Empty>
    class TypeRegistry
    {
      public:
        typedef std::vector<TypeHandle>         UsedTypes;
        typedef std::pair<UsedTypes, OTHER_KEY> Key;
        typedef std::pair<Key, TypeHandle>      Entry;

        std::optional<TypeHandle> get(const UsedTypes& type_keys, const OTHER_KEY& other_keys) const;
        void                      add(UsedTypes&& type_keys, OTHER_KEY other_key, TypeHandle type);

        /**
         * Resolve the used types.
         */
        void resolve();

      private:
        std::vector<Entry> types_;
    };
}

#include "TypeRegistry.tpp"

#endif
