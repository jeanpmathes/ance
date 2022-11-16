#ifndef ANCE_SRC_MANAGEMENT_FILE_H_
#define ANCE_SRC_MANAGEMENT_FILE_H_

#include <filesystem>

#include "management/elements/Element.h"

namespace data
{
    /**
     * Represents a data file.
     */
    class File
    {
      public:
        /**
         * Create a new data file from a file in the filesystem. No actual reading occurs.
         * @param path The path to the file.
         */
        explicit File(std::filesystem::path const& path);

        /**
         * Get the path to the file.
         * @return The path.
         */
        std::filesystem::path const& path();

        /**
         * Read the element structure from the file.
         */
        void read();

        /**
         * Get the root element of the element structure stored in the file.
         * @return The root element.
         */
        data::Element const& root();

      private:
        std::filesystem::path const&   path_;
        std::unique_ptr<data::Element> element_;
    };
}

#endif
