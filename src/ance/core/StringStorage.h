#ifndef ANCE_CORE_STRINGSTORAGE_H
#define ANCE_CORE_STRINGSTORAGE_H

#include <set>
#include <string>
#include <string_view>

namespace ance::core
{
    /// Stores strings and provides views of them. The views are valid as long as the storage exists.
    class StringStorage
    {
        StringStorage() = default;

      public:
        StringStorage(StringStorage const& storage) = delete;
        StringStorage(StringStorage&& storage)      = delete;

        /// Get the shared instance of the string storage.
        /// \return The shared instance.
        static StringStorage& shared();

        /// Store a string in storage and get a view of it.
        /// If there is already a string with the same content, a view of the existing string will be returned.
        /// \param string The string of which a copy is stored.
        /// \return A view to a string with same content.
        std::string_view store(std::string const& string);

      private:
        std::set<std::string> storage_ {};
    };
}

#endif
