#include "Project.h"

#include "lang/ApplicationVisitor.h"
#include "management/File.h"
#include "management/elements/Element.h"

Project::Project(data::File& project) : project_(project), application_(*this) {}

std::string Project::getName() const
{
    auto name = project_.root()["name"];

    if (name.hasValue())
    {
        auto str = name->get().asString();

        if (str.hasValue()) { return str->get(); }
    }

    return "unnamed";
}
std::filesystem::path Project::getProjectFile() const
{
    return project_.path();
}

std::filesystem::path Project::getProjectDirectory() const
{
    return project_.path().parent_path();
}

std::vector<std::filesystem::path> Project::getSourceFiles() const
{
    std::filesystem::path const project_directory = getProjectDirectory();
    std::filesystem::path const src               = "src";
    std::filesystem::path const src_directory     = project_directory / src;

    std::vector<std::filesystem::path> files;

    for (auto& entry : std::filesystem::recursive_directory_iterator(src_directory))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".nc")
        {
            std::filesystem::path const relative_path = entry.path().lexically_relative(project_directory);
            files.push_back(relative_path);
        }
    }

    return files;
}

Application& Project::getApplication()
{
    return application_;
}
