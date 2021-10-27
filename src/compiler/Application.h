#ifndef ANCE_SRC_COMPILER_APPLICATION_H_
#define ANCE_SRC_COMPILER_APPLICATION_H_

#include <filesystem>

#include "ance/scope/GlobalScope.h"

namespace ance
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

/**
 * The application that is described by the source and will be compiled.
 */
class Application
{
  public:
    /**
     * Create a new application from a given project file.
     * @param project The project file.
     */
    explicit Application(data::File& project);

    Application(const Application&) = delete;
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
    [[nodiscard]] std::string getName() const;

    /**
     * Get the path to the project file.
     * @return The project file.
     */
    [[nodiscard]] std::filesystem::path getProjectFile() const;
    /**
     * Get the path to the source file.
     * @return The source file.
     */
    [[nodiscard]] std::filesystem::path getSourceFile() const;

    /**
     * Get the bitness of the application.
     * @return The bitness.
     */
    [[nodiscard]] unsigned getBitness() const;

    /**
     * Validate the application before compilation.
     * @param validation_logger A logger to log validation messages.
     */
    void validate(ValidationLogger& validation_logger);

    /**
     * Get the top level scope of this application.
     * @return The global scope.
     */
    ance::GlobalScope& globalScope();

  private:
    data::File& project_;

    std::unique_ptr<ance::GlobalScope> global_scope_;

    unsigned pointer_size_ {0};
};

#endif