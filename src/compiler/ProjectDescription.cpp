#include "ProjectDescription.h"

#include "lang/ApplicationVisitor.h"

ProjectDescription::ProjectDescription(std::filesystem::path project_file)
    : project_file_(std::move(project_file))
    , name_(project_file_.stem().generic_string())
{}

std::string const& ProjectDescription::getName() const
{
    return name_;
}

std::filesystem::path ProjectDescription::getProjectFile() const
{
    return project_file_;
}

std::filesystem::path ProjectDescription::getProjectDirectory() const
{
    return project_file_.parent_path();
}

std::vector<std::filesystem::path> ProjectDescription::getSourceFiles() const
{
    return {project_file_};
}

ApplicationType ProjectDescription::getType() const
{
    return ApplicationType::LIBRARY;
}

void ProjectDescription::validate(ValidationLogger& validation_logger) const
{
    this->globalScope().validate(validation_logger);
}

antlr4::tree::ParseTree* ProjectDescription::selectTree(anceParser& parser)
{
    return parser.projectFile();
}

void ProjectDescription::addToAbstractSyntaxTree(antlr4::tree::ParseTree* tree, FileContext& context)
{
    source_visitor_.setFileContext(context);
    source_visitor_.visit(tree);
}
