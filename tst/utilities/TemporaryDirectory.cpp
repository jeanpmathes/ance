#include "TemporaryDirectory.h"

#include <atomic>
#include <format>
#include <fstream>
#include <stdexcept>
#include <system_error>

#include <process.h>

namespace
{
    std::filesystem::path createTemporaryDirectory()
    {
        static std::atomic_uint64_t counter = 0;

        std::string const name = std::format("ance-tst-{}-{}", _getpid(), counter++);

        std::filesystem::path const root = std::filesystem::temp_directory_path() / name;

        std::filesystem::remove_all(root);

        if (!std::filesystem::create_directory(root)) throw std::runtime_error("Failed to create a temporary test directory");

        return root;
    }
}

ance::test::TemporaryDirectory::TemporaryDirectory() : root_(createTemporaryDirectory()) {}

ance::test::TemporaryDirectory::~TemporaryDirectory()
{
    std::error_code error;
    std::filesystem::remove_all(root_, error);
}

std::filesystem::path const& ance::test::TemporaryDirectory::root() const
{
    return root_;
}

std::filesystem::path ance::test::TemporaryDirectory::writeFile(std::filesystem::path const& relative_path, std::string_view const content)
{
    std::filesystem::path const normalized_path = relative_path.lexically_normal();

    if (normalized_path.empty() || normalized_path.is_absolute() || *normalized_path.begin() == "..")
        throw std::invalid_argument("Test file paths must stay inside the temporary directory");

    std::filesystem::path const absolute_path = root_ / normalized_path;
    std::filesystem::create_directories(absolute_path.parent_path());

    std::ofstream file(absolute_path, std::ios::binary);
    file.write(content.data(), static_cast<std::streamsize>(content.size()));

    if (!file) throw std::runtime_error("Failed to write test file: " + normalized_path.generic_string());

    counter_ += 1;

    return absolute_path;
}
