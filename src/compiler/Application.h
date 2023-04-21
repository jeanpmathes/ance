#ifndef ANCE_SRC_COMPILER_APPLICATION_H_
#define ANCE_SRC_COMPILER_APPLICATION_H_

#include "Unit.h"

#include "validation/ValidationLogger.h"

/**
 * The application that is described by the source and will be compiled.
 */
class Application : public Unit
{
  public:
    struct BuildInfo {
        llvm::Triple triple;

        std::filesystem::path build_dir;
        std::filesystem::path triple_dir;
        std::filesystem::path bin_suffix;

        ValidationLogger validation_logger;
        std::ostream&    out;
    };

    /**
     * Create a new application from a given project.
     * @param project The project.
     * @param info The build information.
     */
    explicit Application(Project& project, BuildInfo info);

  public:
    Application(Application const&) = delete;
    Application(Application&&)      = delete;

  public:
    std::string const&                               getName() const override;
    [[nodiscard]] std::filesystem::path              getProjectFile() const override;
    [[nodiscard]] std::filesystem::path              getProjectDirectory() const override;
    [[nodiscard]] std::vector<std::filesystem::path> getSourceFiles() const override;
    [[nodiscard]] UnitResult                         getType() const override;
    [[nodiscard]] OptLevel                           getOptimizationLevel() const override;
    [[nodiscard]] bool                               isWarningsAsErrors() const override;
    [[nodiscard]] bool                               isAssertionsEnabled() const override;
    [[nodiscard]] bool                               isEmittingExtras() const override;
    [[nodiscard]] bool                               isUsingRuntime() const override;
    void                                             validate(ValidationLogger& validation_logger) const override;

    antlr4::tree::ParseTree* selectTree(anceParser& parser) override;
    void                     addToAbstractSyntaxTree(antlr4::tree::ParseTree* tree, FileContext& context) override;

    std::vector<std::string> getDependencies() const override;
    std::vector<std::string> getLibraries() const override;
    std::vector<std::string> getArchives() const override;
    std::vector<std::string> getLibraryPaths() const override;
    std::vector<std::string> getBinaryDependencyPaths() const override;

    BuildInfo& getBuildInfo();

  private:
    Project&  project_;
    BuildInfo info_;

    mutable Optional<std::string> name_;
};

#endif
