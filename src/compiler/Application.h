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
    std::string const&                               getName() const override;
    [[nodiscard]] std::filesystem::path              getProjectFile() const override;
    [[nodiscard]] std::filesystem::path              getProjectDirectory() const override;
    [[nodiscard]] std::vector<std::filesystem::path> getSourceFiles() const override;
    [[nodiscard]] UnitResult                         getType() const override;
    OptLevel                                         getOptimizationLevel() const override;
    bool                                             emitExtras() const override;
    void                                             validate(ValidationLogger& validation_logger) const override;

    antlr4::tree::ParseTree* selectTree(anceParser& parser) override;
    void                     addToAbstractSyntaxTree(antlr4::tree::ParseTree* tree, FileContext& context) override;

    std::vector<std::string> getLibraries() const override;
    std::vector<std::string> getLibraryPaths() const override;

  private:
    Project& project_;

    mutable Optional<std::string> name_;
};

#endif
