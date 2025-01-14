#ifndef ANCE_SRC_COMPILER_PACKAGES_H_
#define ANCE_SRC_COMPILER_PACKAGES_H_

#include <filesystem>

#include "lang/utility/Optional.h"

/**
 * A class giving access to a package repository.
 */
class Packages
{
  public:
    explicit Packages(std::filesystem::path base);

    struct Package {
        std::string           name;
        std::filesystem::path path;
    };

    /**
     * Get the path to a package.
     * @param name The name of the package.
     * @return The path to the package.
     */
    [[nodiscard]] Optional<Package> getPackage(std::string const& name) const;

    constexpr static char const* PACKAGE_EXTENSION = ".apkg";

  private:
    std::filesystem::path base_;
};

#endif
