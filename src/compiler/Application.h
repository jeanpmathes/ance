#ifndef ANCE_SRC_COMPILER_APPLICATION_H_
#define ANCE_SRC_COMPILER_APPLICATION_H_

#include <filesystem>
#include <memory>

#include "lang/scope/GlobalScope.h"
#include "lang/Element.h"

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
    Application(Project& project, std::unique_ptr<lang::GlobalScope>&& scope);

  public:
    Application(const Application&) = delete;
    Application(Application&&)      = delete;

  public:
    /**
     * Set the pointer size to use.
     * @param size The pointer size.
     */
    void setPointerSize(unsigned size);

    /**
     * Get the containing project.
     * @return The project.
     */
    Project& getProject() const;

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
    void validate(ValidationLogger& validation_logger);

    /**
     * Prepare everything for compilation.
     */
    void preBuild();

    /**
     * Validate the application before compilation.
     * @param validation_logger The logger to log validation messages.
     */
    void validateFlow(ValidationLogger& validation_logger);

    /**
     * Get the top level scope of this application.
     * @return The global scope.
     */
    lang::GlobalScope& globalScope();

  private:
    Project& project_;

    std::unique_ptr<lang::GlobalScope> global_scope_;

    unsigned pointer_size_ {0};
};

#endif