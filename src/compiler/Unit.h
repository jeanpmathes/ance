#ifndef ANCE_SRC_COMPILER_UNIT_H_
#define ANCE_SRC_COMPILER_UNIT_H_

#include <filesystem>
#include <memory>

#include "anceParser.h"

#include "lang/Element.h"

#include "compiler/FileContext.h"
#include "compiler/OptLevel.h"
#include "compiler/SourceVisitor.h"
#include "compiler/UnitResult.h"
#include "lang/scope/GlobalScope.h"

namespace lang
{
    class Function;
}

class Statement;
class CompileContext;
class ValidationLogger;
class Project;
class Packages;

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
    void setTargetInfo(llvm::Triple const& triple, llvm::DataLayout const& data_layout);

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
     * Get the bitness of the application.
     * @return The bitness.
     */
    [[nodiscard]] unsigned getBitness() const;

    /**
     * Get the target triple.
     * @return The target triple.
     */
    [[nodiscard]] llvm::Triple const& getTargetTriple() const;

    using BuildFunction = Optional<int>(std::ostream&,
                                        std::filesystem::path const&,
                                        Optional<std::filesystem::path> const&,
                                        Packages const&);

    /**
     * Prepare all package dependencies.
     * @param packages The packages object.
     * @param build A function that builds a package into a given directory.
     * @param dir The directory to output build files and logs to. Subdirectories will be created.
     * @param bin_base Path to the binary directory, all package binaries will be copied to this directory.
     * @param bin_suffix Suffix that leads from the build directory of a package to the binary directory of the package.
     * @param out The output stream to log general information to, related to the overall build process.
     */
    bool preparePackageDependencies(Packages const&                     packages,
                                    std::function<BuildFunction> const& build,
                                    std::filesystem::path const&        dir,
                                    std::filesystem::path const&        bin_base,
                                    std::filesystem::path const&        bin_suffix,
                                    std::ostream&                       out);

    /**
     * Export this unit as a package.
     * @param dir The directory to export to.
     */
    void exportPackage(std::filesystem::path const& dir);

    /**
     * Import a package into this unit.
     * @param dir The directory in which the package is located.
     * @name The name of the package.
     */
    void importPackage(std::filesystem::path const& dir, std::string const& name);

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
     * Get the names of the functions that should be exported.
     * @return The names of the exported functions.
     */
    [[nodiscard]] virtual std::vector<std::string> getExportedFunctions() const;

    /**
     * Get the name of all required packages.
     * @return The names of the required packages.
     */
    [[nodiscard]] virtual std::vector<std::string> getDependencies() const = 0;

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

    ~Unit() override = default;

  private:
    Owned<lang::GlobalScope> global_scope_;

  protected:
    unsigned      pointer_size_ {0};
    llvm::Triple  target_triple_;
    SourceVisitor source_visitor_ {*this};
};

#endif
