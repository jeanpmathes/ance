#ifndef ANCE_TST_UTILITIES_TEMPORARYDIRECTORY_H
#define ANCE_TST_UTILITIES_TEMPORARYDIRECTORY_H

#include <filesystem>
#include <string_view>

namespace ance::test
{
    /// Owns a temporary directory.
    class TemporaryDirectory
    {
      public:
        TemporaryDirectory();
        ~TemporaryDirectory();

        TemporaryDirectory(TemporaryDirectory const&)            = delete;
        TemporaryDirectory(TemporaryDirectory&&)                 = delete;
        TemporaryDirectory& operator=(TemporaryDirectory const&) = delete;
        TemporaryDirectory& operator=(TemporaryDirectory&&)      = delete;

        /// Get the temporary directory's root path.
        [[nodiscard]] std::filesystem::path const& root() const;

        /// Write a file below the temporary directory.
        /// @param relative_path The path relative to the temporary directory.
        /// @param content The file content.
        /// @return The absolute path of the written file.
        std::filesystem::path writeFile(std::filesystem::path const& relative_path, std::string_view content);

      private:
        std::filesystem::path root_;
        size_t                counter_ = 0;
    };
}

#endif
