#include "ProjectDescription.h"

#include "lang/ApplicationVisitor.h"

ProjectDescription::ProjectDescription(std::filesystem::path project_file)
    : Unit(true)
    , project_file_(std::move(project_file))
    , name_("__definition__")
{}

void ProjectDescription::setBinaryDescriptionPath(std::filesystem::path path)
{
    binary_description_path_ = std::move(path);
}

bool ProjectDescription::isProjectDefinition() const
{
    return true;
}

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

UnitResult ProjectDescription::getType() const
{
    return UnitResult::LIBRARY;
}

OptLevel ProjectDescription::getOptimizationLevel() const
{
    return OptLevel::O_3;
}

bool ProjectDescription::isWarningsAsErrors() const
{
    return true;
}

bool ProjectDescription::isAssertionsEnabled() const
{
    return false;
}

bool ProjectDescription::isEmittingExtras() const
{
    return false;
}

bool ProjectDescription::isUsingRuntime() const
{
    return true;
}

void ProjectDescription::validate(ValidationLogger& validation_logger) const
{
    this->globalScope().validate(validation_logger);
}

antlr4::tree::ParseTree* ProjectDescription::selectTree(anceParser& parser)
{
    std::string const name = project_file_.stem().generic_string();
    if (name == "std" || name == "project")
    {
        // The 'std' and 'project' packages cannot use the project file stub as it depends on them.
        return parser.file();
    }
    else { return parser.projectFile(); }
}

void ProjectDescription::addToAbstractSyntaxTree(antlr4::tree::ParseTree* tree, FileContext& context)
{
    source_visitor_.setFileContext(context);
    source_visitor_.visit(tree);
}

std::vector<std::pair<std::string, bool>> ProjectDescription::getDependencies() const
{
    std::vector<std::pair<std::string, bool>> dependencies;

    std::string const name = getProjectFile().stem().generic_string();

    if (name != "std" && name != "project")
    {
        dependencies.emplace_back("std", true);
        dependencies.emplace_back("project", true);
    }

    return dependencies;
}

std::vector<std::string> ProjectDescription::getLibraries() const
{
    return {};
}

std::vector<std::string> ProjectDescription::getArchives() const
{
    return {};
}

std::vector<std::string> ProjectDescription::getLibraryPaths() const
{
    return {};
}

std::vector<std::string> ProjectDescription::getBinaryDependencyPaths() const
{
    return {};
}

struct Project_ {
    uint8_t const*  name                     = nullptr;
    uint32_t        kind                     = 0;
    uint8_t const** public_dependencies      = nullptr;
    uint8_t const** private_dependencies     = nullptr;
    uint8_t const** libraries                = nullptr;
    uint8_t const** archives                 = nullptr;
    uint8_t const** library_paths            = nullptr;
    uint8_t const** binary_dependencies      = nullptr;
    uint32_t        opt_level                = 0;
    bool            warning_as_error_enabled = false;
    bool            ignoring_assert          = false;
    bool            extra_emission_enabled   = false;
    bool            runtime_excluded         = false;
    bool            std_excluded             = false;
};

using ProjectDescriptionFunction = void(__cdecl*)(Project_*);

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <Windows.h>
#elif defined(_POSIX_VERSION)
#include <dlfcn.h>
#endif

bool ProjectDescription::loadDescription()
{
    assert(!description_.hasValue());

    Project_ project;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define ANCE_TARGET_WINDOWS

    SetDllDirectoryA(binary_description_path_->parent_path().string().c_str());

    HMODULE handle = LoadLibraryA(binary_description_path_->string().c_str());
    if (!handle) return false;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcast-function-type"
    auto function =
        reinterpret_cast<ProjectDescriptionFunction>(GetProcAddress(handle, ANCE_PROJECT_DEFINITION_FUNCTION));
    if (!function) return false;
#pragma clang diagnostic pop

    function(&project);
#elif defined(_POSIX_VERSION)
#define ANCE_TARGET_POSIX

    void* handle = dlopen(binary_description_path_->string().c_str(), RTLD_NOW);
    if (!handle) return false;

    auto function = reinterpret_cast<ProjectDescriptionFunction>(dlsym(handle, ANCE_PROJECT_DEFINITION_FUNCTION));
    if (!function) return false;

    function(&project);
#endif

    auto read_string = [](uint8_t const* str) -> std::string {
        if (str == nullptr) return {};

        std::stringstream ss;
        while (*str != '\0')
        {
            uint8_t const c = *str;
            ss << c;
            str++;
        }
        return ss.str();
    };

    auto read_vector = [&](uint8_t const** array) -> std::vector<std::string> {
        if (array == nullptr) return {};

        std::vector<std::string> result;
        while (*array)
        {
            result.emplace_back(read_string(*array));
            array++;
        }
        return result;
    };

    UnitResult kind;
    switch (project.kind)
    {
        case 1:
            kind = UnitResult::EXECUTABLE;
            break;
        case 2:
            kind = UnitResult::PACKAGE;
            break;
        case 3:
            kind = UnitResult::LIBRARY;
            break;
        default:
            return false;
    }

    OptLevel opt_level;
    switch (project.opt_level)
    {
        case 0:
            opt_level = OptLevel::O_0;
            break;
        case 1:
            opt_level = OptLevel::O_1;
            break;
        case 2:
            opt_level = OptLevel::O_2;
            break;
        case 3:
            opt_level = OptLevel::O_3;
            break;
        default:
            return false;
    }

    description_ = {.name                     = read_string(project.name),
                    .kind                     = kind,
                    .project_file             = project_file_,
                    .public_dependencies      = read_vector(project.public_dependencies),
                    .private_dependencies     = read_vector(project.private_dependencies),
                    .linkage_libraries        = read_vector(project.libraries),
                    .linkage_archives         = read_vector(project.archives),
                    .linkage_library_paths    = read_vector(project.library_paths),
                    .binary_dependencies      = read_vector(project.binary_dependencies),
                    .opt_level                = opt_level,
                    .warning_as_error_enabled = project.warning_as_error_enabled,
                    .ignoring_assert          = project.ignoring_assert,
                    .extra_emission_enabled   = project.extra_emission_enabled,
                    .runtime_excluded         = project.runtime_excluded,
                    .std_excluded             = project.std_excluded};

#if defined(ANCE_TARGET_WINDOWS)
    FreeLibrary(handle);
#elif defined(ANCE_TARGET_POSIX)
    dlclose(handle);
#endif

    return true;
}

ProjectDescription::Description const& ProjectDescription::description() const
{
    assert(description_.hasValue());
    return description_.value();
}
