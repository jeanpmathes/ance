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
    auto src = project_.root()["src"];

    if (!src) return {};

    for (auto src_file : src->get())
    {
        auto src_file_str = src_file.get().asString();

        if (!src_file_str) continue;

        std::filesystem::path path_to_src(src_file_str->get());
        std::filesystem::path path_to_project = getProjectFile();

        return path_to_project.replace_filename(path_to_src);
    }

    return {};
}

Application& Project::getApplication()
{
    return application_;
}

