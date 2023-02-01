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
    return parser.projectFile();
}

void ProjectDescription::addToAbstractSyntaxTree(antlr4::tree::ParseTree* tree, FileContext& context)
{
    source_visitor_.setFileContext(context);
    source_visitor_.visit(tree);
}

std::vector<std::string> ProjectDescription::getLibraries() const
{
    return {"kernel32", "ucrt", "msvcrt", "libcmt", "libvcruntime"};
}

std::vector<std::string> ProjectDescription::getLibraryPaths() const
{
    return {R"(C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64)",
            R"(C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\ucrt\x64)",
            R"(C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.30.30705\lib\x64)"};
}

std::vector<std::string> ProjectDescription::getBinaryDependencyPaths() const
{
    return {};
}

struct Project_ {
    uint8_t const*  name                        = nullptr;
    uint32_t        kind                        = 0;
    uint8_t const** libraries                   = nullptr;
    uint8_t const** library_paths               = nullptr;
    uint8_t const** binary_dependencies         = nullptr;
    uint32_t        opt_level                   = 0;
    bool            is_warning_as_error_enabled = false;
    bool            is_assert_ignored           = false;
    bool            is_extra_emission_enabled   = false;
    bool            is_runtime_excluded         = false;
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

    auto function =
        reinterpret_cast<ProjectDescriptionFunction>(GetProcAddress(handle, ANCE_PROJECT_DEFINITION_FUNCTION));
    if (!function) return false;

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

    description_ = {.name                        = read_string(project.name),
                    .kind                        = kind,
                    .project_file                = project_file_,
                    .linkage_libraries           = read_vector(project.libraries),
                    .linkage_library_paths       = read_vector(project.library_paths),
                    .binary_dependencies         = read_vector(project.binary_dependencies),
                    .opt_level                   = opt_level,
                    .is_warning_as_error_enabled = project.is_warning_as_error_enabled,
                    .is_assert_ignored           = project.is_assert_ignored,
                    .is_extra_emission_enabled   = project.is_extra_emission_enabled,
                    .is_runtime_excluded         = project.is_runtime_excluded};

#if defined(ANCE_TARGET_WINDOWS)
    FreeLibrary(handle);
#elif defined(ANCE_TARGET_POSIX)
    dlclose(handle);
#endif

    return true;
}

bool ProjectDescription::isRefreshRequired()
{
    if (std::filesystem::exists(binary_description_path_.value()))
    {
        auto binary_description_time = std::filesystem::last_write_time(binary_description_path_.value());
        auto project_file_time       = std::filesystem::last_write_time(project_file_);

        return binary_description_time < project_file_time;
    }

    return true;
}

ProjectDescription::Description const& ProjectDescription::description() const
{
    assert(description_.hasValue());
    return description_.value();
}
