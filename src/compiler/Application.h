#ifndef ANCE_SRC_COMPILER_APPLICATION_H_
#define ANCE_SRC_COMPILER_APPLICATION_H_

#include <filesystem>
#include <memory>

#include "lang/Element.h"

#include "ApplicationType.h"
#include "lang/scope/GlobalScope.h"

namespace lang
{
    class Function;
}

namespace data
{
    class File;
}

class Statement;
class CompileContext;
class ValidationLogger;
class Project;

/**
 * The application that is described by the source and will be compiled.
 */
class Application : public lang::Element<Application, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new application from a given project.
     * @param project The project.
     */
    explicit Application(Project& project);

  private:
    Application(Project& project, Owned<lang::GlobalScope>&& scope);

  public:
    Application(Application const&) = delete;
    Application(Application&&)      = delete;

  public:
    /**
     * Set the pointer size to use.
     * @param size The pointer size.
     */
    void setPointerSize(unsigned size);

    /**
     * Get the name of the application.
     * @return The name.
     */
    std::string const& getName() const;

    /**
     * Get the path to the project file.
     * @return The project file.
     */
    [[nodiscard]] std::filesystem::path getProjectFile() const;

    /**
     * Get the path to the project directory.
     * @return The project directory.
     */
    [[nodiscard]] std::filesystem::path getProjectDirectory() const;

    /**
     * Get the paths to all source files.
     * @return The source file paths, relative to the project directory.
     */
    [[nodiscard]] std::vector<std::filesystem::path> getSourceFiles() const;

    /**
     * Get the application type.
     * @return The application type.
     */
    [[nodiscard]] ApplicationType getType() const;

    /**
     * Get the bitness of the application.
     * @return The bitness.
     */
    [[nodiscard]] unsigned getBitness() const;

    /**
     * Prepare everything for the first validation step.
     */
    void preValidate();

    /**
     * Validate the application before compilation.
     * @param validation_logger A logger to log validation messages.
     */
    void validate(ValidationLogger& validation_logger) const;

    /**
     * Prepare everything for compilation.
     */
    void preBuild();

    /**
     * Emit the parsed and processed application as source.
     * @param out The file to emit to.
     */
    void emitAsSource(std::filesystem::path const& out);

    /**
     * Validate the application before compilation.
     * @param validation_logger The logger to log validation messages.
     */
    void validateFlow(ValidationLogger& validation_logger) const;

    /**
     * Get the top level scope of this application.
     * @return The global scope.
     */
    lang::GlobalScope& globalScope();

  private:
    Project& project_;

    Owned<lang::GlobalScope> global_scope_;

    unsigned pointer_size_ {0};

    mutable Optional<std::string> name_;
};

#endif
