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
        explicit File(const std::filesystem::path& path);

        /**
         * Get the path to the file.
         * @return The path.
         */
        const std::filesystem::path& path();

        /**
         * Read the element structure from the file.
         */
        void read();

        /**
         * Get the root element of the element structure stored in the file.
         * @return The root element.
         */
        const data::Element& root();

      private:
        const std::filesystem::path&   path_;
        std::unique_ptr<data::Element> element_;
    };
}

#endif
