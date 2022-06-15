#ifndef ANCE_SRC_LANG_UTILITY_STRINGSTORAGE_H_
#define ANCE_SRC_LANG_UTILITY_STRINGSTORAGE_H_

#include <set>
#include <string>
#include <string_view>

namespace lang
{
    /**
 * Stores strings and provides views of them. The views are valid as long as the storage exists.
 */
    class StringStorage
    {
      private:
        StringStorage() = default;

      public:
        StringStorage(const StringStorage& storage) = delete;
        StringStorage(StringStorage&& storage)      = delete;

        /**
     * Get the shared instance of the string storage.
     * @return The shared instance.
     */
        static StringStorage& shared();

      public:
        /**
     * Store a string in storage and get a view of it.
     * If there is already a string with the same content, a view of the existing string will be returned.
     * @param string The string of which a copy is stored.
     * @return A view to a string with same content.
     */
        std::string_view store(const std::string& string);

      private:
        std::set<std::string> storage_ {};
    };
}

#endif
