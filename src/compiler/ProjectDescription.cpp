#include "ProjectDescription.h"

#include "lang/ApplicationVisitor.h"

ProjectDescription::ProjectDescription(std::filesystem::path project_file)
    : project_file_(std::move(project_file))
    , name_(project_file_.stem().generic_string())
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

struct Project_ {
    uint8_t const*  name;
    uint8_t const** libraries;
    uint8_t const** library_paths;
};

struct test {
    char x;
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
        std::vector<std::string> result;
        while (*array)
        {
            result.emplace_back(read_string(*array));
            array++;
        }
        return result;
    };

    description_ = {.name                  = read_string(project.name),
                    .project_file          = project_file_,
                    .linkage_libraries     = read_vector(project.libraries),
                    .linkage_library_paths = read_vector(project.library_paths)};

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
