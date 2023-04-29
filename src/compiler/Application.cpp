#include "Application.h"

#include "compiler/CodePrinter.h"
#include "compiler/Project.h"
#include "validation/ValidationLogger.h"

#include "lang/type/HalfType.h"
#include "lang/type/ArrayType.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/VectorType.h"
#include "lang/type/SizeType.h"

Application::Application(Project& project, BuildInfo build_info)
    : Unit(!project.description().runtime_excluded)
    , project_(project)
    , info_(std::move(build_info))
    , declared_dependencies_()
{
    if (!project_.description().std_excluded) { declared_dependencies_.emplace_back("std", true); }

    for (auto const& dependency : project_.description().public_dependencies)
    {
        declared_dependencies_.emplace_back(dependency, true);
    }

    for (auto const& dependency : project_.description().private_dependencies)
    {
        declared_dependencies_.emplace_back(dependency, false);
    }
}

std::string const& Application::getName() const
{
    if (!name_.hasValue()) { name_ = project_.getName(); }

    return name_.value();
}

static bool isNameValid(std::string const& name)
{
    static std::set<char> const alpha = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                         'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                                         'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                                         'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    static std::set<char> const num = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    bool is_first = true;

    for (char const c : name)
    {
        if (is_first)
        {
            if (!alpha.contains(c)) { return false; }
        }
        else
        {
            if (!alpha.contains(c) && !num.contains(c) && c != '_') { return false; }
        }

        is_first = false;
    }

    return true;
}

void Application::validate(ValidationLogger& validation_logger) const
{
    std::string const name_according_to_file = project_.getProjectFile().stem().generic_string();
    std::string const name_according_to_path = project_.getProjectDirectory().stem().generic_string();

    bool const names_match = name_according_to_file == name_according_to_path && name_according_to_file == getName();

    if (!names_match)
    {
        validation_logger.logError("Project name does not match project file name or project directory name",
                                   lang::Location::global());
    }

    if (!isNameValid(getName()))
    {
        validation_logger.logError("Project name is not a valid identifier", lang::Location::global());
    }

    if (project_.description().runtime_excluded && !project_.description().std_excluded)
    {
        validation_logger.logError("Project cannot exclude the runtime while including the standard library",
                                   lang::Location::global());
    }

    this->globalScope().validate(validation_logger);

    if (getType() == UnitResult::EXECUTABLE)
    {
        if (!this->globalScope().hasEntry())
        {
            validation_logger.logError("Entry point 'main() : u32' could not be found", lang::Location::global());
        }
    }
}

std::filesystem::path Application::getProjectFile() const
{
    return project_.getProjectFile();
}

std::filesystem::path Application::getProjectDirectory() const
{
    return project_.getProjectDirectory();
}

std::vector<std::filesystem::path> Application::getSourceFiles() const
{
    return project_.getSourceFiles();
}

UnitResult Application::getType() const
{
    return project_.description().kind;
}

OptLevel Application::getOptimizationLevel() const
{
    return project_.description().opt_level;
}

bool Application::isWarningsAsErrors() const
{
    return project_.description().warning_as_error_enabled;
}

bool Application::isAssertionsEnabled() const
{
    return not project_.description().ignoring_assert;
}

bool Application::isEmittingExtras() const
{
    return project_.description().extra_emission_enabled;
}

bool Application::isUsingRuntime() const
{
    return not project_.description().runtime_excluded;
}

antlr4::tree::ParseTree* Application::selectTree(anceParser& parser)
{
    return parser.file();
}

void Application::addToAbstractSyntaxTree(antlr4::tree::ParseTree* tree, FileContext& context)
{
    source_visitor_.setFileContext(context);
    source_visitor_.visit(tree);
}

std::vector<std::pair<std::string, bool>> Application::getDependencies() const
{
    return declared_dependencies_;
}

std::vector<std::string> Application::getLibraries() const
{
    return project_.description().linkage_libraries;
}

std::vector<std::string> Application::getArchives() const
{
    return project_.description().linkage_archives;
}

std::vector<std::string> Application::getLibraryPaths() const
{
    return project_.description().linkage_library_paths;
}

std::vector<std::string> Application::getBinaryDependencyPaths() const
{
    return project_.description().binary_dependencies;
}

Application::BuildInfo& Application::getBuildInfo()
{
    return info_;
}

std::vector<std::string> Application::getPublicDependencies() const
{
    return project_.description().public_dependencies;
}
