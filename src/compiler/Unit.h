#ifndef ANCE_SRC_COMPILER_UNIT_H_
#define ANCE_SRC_COMPILER_UNIT_H_

#include <filesystem>
#include <memory>

#include "anceParser.h"

#include "lang/Element.h"

#include "TargetDescriptor.h"
#include "compiler/FileContext.h"
#include "compiler/OptLevel.h"
#include "compiler/Packages.h"
#include "compiler/SourceVisitor.h"
#include "compiler/UnitResult.h"
#include "lang/scope/GlobalScope.h"

namespace lang
{
    class Function;
}

class Statement;
class Execution;
class ValidationLogger;
class Project;
class ProjectDescription;

/**
 * A unit of source that is compiled as a whole.
 */
class Unit : public lang::Element<Unit, ANCE_CONSTRUCTS>
{
  private:
    explicit Unit(Owned<lang::GlobalScope> global_scope);

  protected:
    explicit Unit(bool is_containing_runtime);

  public:
    /**
     * Set information about the compile target machine.
     */
    void setTargetInfo(TargetDescriptor const& target_descriptor);

    /**
     * Get the name of the unit.
     * @return The name.
     */
    [[nodiscard]] virtual std::string const& getName() const = 0;

    /**
     * Get the path to the project file.
     * @return The project file.
     */
    [[nodiscard]] virtual std::filesystem::path getProjectFile() const = 0;

    /**
     * Get the path to the project directory.
     * @return The project directory.
     */
    [[nodiscard]] virtual std::filesystem::path getProjectDirectory() const = 0;

    /**
     * Get the paths to all source files.
     * @return The source file paths, relative to the project directory.
     */
    [[nodiscard]] virtual std::vector<std::filesystem::path> getSourceFiles() const = 0;

    /**
     * Get the application type.
     * @return The application type.
     */
    [[nodiscard]] virtual UnitResult getType() const = 0;

    /**
     * Get the optimization level.
     * @return The optimization level.
     */
    [[nodiscard]] virtual OptLevel getOptimizationLevel() const = 0;

    /**
     * Whether to treat warnings as errors.
     * @return True if warnings should be treated as errors.
     */
    [[nodiscard]] virtual bool isWarningsAsErrors() const = 0;

    /**
     * Get whether assertions are enabled.
     * @return True if assertions are enabled.
     */
    [[nodiscard]] virtual bool isAssertionsEnabled() const = 0;

    /**
     * Whether extras like a CFG should be emitted.
     * @return True if extras should be emitted.
     */
    [[nodiscard]] virtual bool isEmittingExtras() const = 0;

    /**
     * Whether the runtime is used.
     * @return True if the runtime is used.
     */
    [[nodiscard]] virtual bool isUsingRuntime() const = 0;

    /**
     * Get the target triple.
     * @return The target triple.
     */
    [[nodiscard]] TargetDescriptor const& getTarget() const;

    using PrepareFunctionType = Optional<Owned<Project>>(std::filesystem::path const&,
                                                         Optional<std::filesystem::path> const&,
                                                         std::ostream&,
                                                         Packages const&);

    using PrepareFunction = std::function<PrepareFunctionType>;

    using BuildFunctionType = Optional<bool>(Project&        project,
                                             Packages const& packages,
                                             std::set<std::string>,
                                             std::optional<std::chrono::steady_clock::time_point> const&,
                                             std::ostream&);

    using BuildFunction = std::function<BuildFunctionType>;

    /**
     * Prepare all package dependencies.
     * @param packages The packages object.
     * @param prepare The function to prepare a package.
     * @param dir The directory to output build files and logs to. Subdirectories will be created.
     * @param out The output stream to log general information to, related to current build process.
     */
    bool preparePackageDependencies(Packages const&              packages,
                                    PrepareFunction const&       prepare,
                                    std::filesystem::path const& dir,
                                    std::ostream&                out);

    /**
     * Prepare all package dependencies.
     * @param packages The packages object.
     * @param build The function to build a package.
     * @param dir The directory to output build files and logs to. Subdirectories will be created.
     * @param bin_base Path to the binary directory, all package binaries will be copied to this directory.
     * @param bin_suffix Suffix that leads from the build directory of a package to the binary directory of the package.
     * @param is_binary_dir_fresh Whether the binary directory is fresh, which means that all packages must be copied.
     * @param out The output stream to log general information to, related to the current build process.
     * @param included_packages Packages that are already included in a higher level package.
     * @param root_out The output stream to log general information to, related to the uppermost build process.
     * @return Whether the build was successful and the number of packages built.
     */
    std::pair<bool, size_t> buildPackageDependencies(Packages const&              packages,
                                                     BuildFunction const&         build,
                                                     std::filesystem::path const& dir,
                                                     std::filesystem::path const& bin_base,
                                                     std::filesystem::path const& bin_suffix,
                                                     bool                         is_binary_dir_fresh,
                                                     std::ostream&                out,
                                                     std::set<std::string>        included_packages,
                                                     std::ostream&                root_out);

    /**
     * Export this unit as a package.
     * @param dir The directory to export to.
     */
    void exportPackage(std::filesystem::path const& dir);

    /**
     * Import a package into this unit.
     * @param dir The directory in which the package is located.
     * @param name The name of the package.
     * @param is_public Whether the package is public.
     */
    void importPackage(std::filesystem::path const& dir, std::string const& name, bool is_public);

    /**
     * Prepare everything for the first validation step.
     */
    void preValidate();

    /**
     * Validate the application before compilation.
     * @param validation_logger A logger to log validation messages.
     */
    virtual void validate(ValidationLogger& validation_logger) const = 0;

    /**
     * Transform the internal representation to an executable form.
     * This means that the AST is expanded to remove syntactic sugar,
     * then references are resolved and basic blocks are created.
     */
    void transformToExecutableForm();

    /**
     * Emit the parsed and processed application as source.
     * @param out The file to emit to.
     */
    void emitAsSource(std::filesystem::path const& out);

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

    /**
     * Get the top level scope of this application.
     * @return The global scope.
     */
    [[nodiscard]] lang::GlobalScope const& globalScope() const;

    /**
     * Select the required parse tree.
     * @param parser The parser.
     * @return The required parse tree.
     */
    virtual antlr4::tree::ParseTree* selectTree(anceParser& parser) = 0;

    /**
     * Add the content of a parse tree to the AST.
     * @param tree The parse tree.
     * @param context The file context.
     */
    virtual void addToAbstractSyntaxTree(antlr4::tree::ParseTree* tree, FileContext& context) = 0;

    /**
     * Get the name of all required packages.
     * @return The names of the required packages.
     */
    [[nodiscard]] virtual std::vector<std::pair<std::string, bool>> getDependencies() const = 0;

    /**
     * Libraries that should be linked.
     * @return The libraries to link.
     */
    [[nodiscard]] virtual std::vector<std::string> getLibraries() const = 0;

    /**
     * Archives (static libraries) that should be included.
     * @return The archives to include.
     */
    [[nodiscard]] virtual std::vector<std::string> getArchives() const = 0;

    /**
     * Paths to the directories containing the libraries.
     * @return The paths.
     */
    [[nodiscard]] virtual std::vector<std::string> getLibraryPaths() const = 0;

    /**
     * Paths to binary dependencies hat must be copied to the binary output directory.
     * @return The paths.
     */
    [[nodiscard]] virtual std::vector<std::string> getBinaryDependencyPaths() const = 0;

    /**
     * Get the name of dependencies that must be linked.
     */
    [[nodiscard]] std::vector<std::string> const& getLinkDependencies() const;

    ~Unit() override;

  private:
    Owned<lang::GlobalScope> global_scope_;

  protected:
    SourceVisitor source_visitor_ {*this};

    TargetDescriptor target_descriptor_;

  private:
    std::vector<std::tuple<Optional<Owned<Project>>, Packages::Package, bool>> dependencies_ {};
    std::vector<std::string>                                                   dependencies_to_link_ {};
    std::list<std::ofstream>                                                   open_logs_ {};
};

#endif
