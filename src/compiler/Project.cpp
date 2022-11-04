#include "Project.h"

#include "lang/ApplicationVisitor.h"
#include "management/File.h"
#include "management/elements/Element.h"

Project::Project(data::File& project) : project_(project), application_(*this) {}

std::string Project::getName() const
{
    auto name = project_.root()["name"];

    if (name)
    {
        auto str = name->get().asString();

        if (str) { return str->get(); }
    }

    return "unnamed";
}
std::filesystem::path Project::getProjectFile() const
{
    return project_.path();
}

std::vector<std::filesystem::path> Project::getSourceFiles() const
{
    std::filesystem::path src               = "src";
    std::filesystem::path project_directory = project_.path().parent_path();
    std::filesystem::path src_directory     = getProjectFile().parent_path() / src;

    std::vector<std::filesystem::path> files;

    for (auto& entry : std::filesystem::recursive_directory_iterator(src_directory))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".nc") { files.push_back(entry.path()); }
    }

    return files;
}

Application& Project::getApplication()
{
    return application_;
}
