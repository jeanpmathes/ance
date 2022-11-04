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

std::filesystem::path Project::getSourceFile() const
{
    std::filesystem::path source_directory = "src";
    std::filesystem::path source_file      = source_directory / (getName() + ".nc");

    std::filesystem::path path_to_project = getProjectFile();
    return path_to_project.replace_filename(source_file);
}

Application& Project::getApplication()
{
    return application_;
}

