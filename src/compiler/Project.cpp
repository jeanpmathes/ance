#include "Project.h"

#include "lang/ApplicationVisitor.h"

Project::Project(ProjectDescription::Description&& description) : description_(description), application_(*this) {}

std::string Project::getName() const
{
    return description_.name;
}

std::filesystem::path Project::getProjectFile() const
{
    return description_.project_file;
}

std::filesystem::path Project::getProjectDirectory() const
{
    return description_.project_file.parent_path();
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

ProjectDescription::Description const& Project::description() const
{
    return description_;
}
