#include "Packages.h"

Packages::Packages(std::filesystem::path base) : base_(std::move(base)) {}

Optional<Packages::Package> Packages::getPackage(std::string const& name) const
{
    std::filesystem::path const directory_path = base_ / name;
    if (!std::filesystem::is_directory(directory_path)) return {};

    std::string const           package_name = name + ".ance";
    std::filesystem::path const package_path = directory_path / package_name;

    if (!std::filesystem::exists(package_path)) return {};

    return Package {name, package_path};
}
