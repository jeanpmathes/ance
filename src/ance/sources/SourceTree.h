#ifndef ANCE_SOURCES_SOURCETREE_H
#define ANCE_SOURCES_SOURCETREE_H

#include <filesystem>

#include "ance/utility/Containers.h"
#include "ance/utility/Owners.h"

#include "SourceFile.h"

namespace ance::sources
{
    /**
      * Stores all source files.
      */
    class SourceTree
    {
      public:
        /**
         * Create a new source tree.
         * @param base_directory The base directory of the source files.
         */
        explicit SourceTree(std::filesystem::path base_directory);

        /**
         * Add a source file to the tree.
         * @param file The path to the file.
         * @return The added source file.
         */
        SourceFile& addFile(std::filesystem::path const& file);

        /**
         * Get a source file by index.
         * @param index The index of the file.
         * @return The source file.
         */
        SourceFile& getFile(size_t index);

        /**
         * Get all source files.
         * @return The source files.
         */
        std::vector<std::reference_wrapper<SourceFile>> getSourceFiles();

      private:
        std::filesystem::path base_directory_;
        utility::List<utility::Owned<SourceFile>> source_files_;
    };
}

#endif
