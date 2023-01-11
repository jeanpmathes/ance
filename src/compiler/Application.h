#ifndef ANCE_SRC_COMPILER_APPLICATION_H_
#define ANCE_SRC_COMPILER_APPLICATION_H_

#include "Unit.h"

/**
 * The application that is described by the source and will be compiled.
 */
class Application : public Unit
{
  public:
    /**
     * Create a new application from a given project.
     * @param project The project.
     */
    explicit Application(Project& project);

  public:
    Application(Application const&) = delete;
    Application(Application&&)      = delete;

  public:
    /**
     * Get the name of the application.
     * @return The name.
     */
    std::string const& getName() const override;

    /**
     * Get the path to the project file.
     * @return The project file.
     */
    [[nodiscard]] std::filesystem::path getProjectFile() const override;

    /**
     * Get the path to the project directory.
     * @return The project directory.
     */
    [[nodiscard]] std::filesystem::path getProjectDirectory() const override;

    /**
     * Get the paths to all source files.
     * @return The source file paths, relative to the project directory.
     */
    [[nodiscard]] std::vector<std::filesystem::path> getSourceFiles() const override;

    /**
     * Get the application type.
     * @return The application type.
     */
    [[nodiscard]] ApplicationType getType() const override;

    /**
     * Validate the application before compilation.
     * @param validation_logger A logger to log validation messages.
     */
    void validate(ValidationLogger& validation_logger) const override;

    antlr4::tree::ParseTree* selectTree(anceParser& parser) override;
    void                     addToAbstractSyntaxTree(antlr4::tree::ParseTree* tree, FileContext& context) override;

  private:
    Project& project_;

    mutable Optional<std::string> name_;
};

#endif
