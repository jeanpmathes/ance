#ifndef ANCE_SRC_COMPILER_UNIT_H_
#define ANCE_SRC_COMPILER_UNIT_H_

#include <filesystem>
#include <memory>

#include "grammar/anceParser.h"

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

/**
 * A unit of source that is compiled as a whole.
 */
class Unit : public lang::Element<Unit, ANCE_CONSTRUCTS>
{
  private:
    explicit Unit(Owned<lang::GlobalScope> global_scope);

  protected:
    Unit();

  public:
    /**
     * Set the pointer size to use.
     * @param size The pointer size.
     */
    void setPointerSize(unsigned size);

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
     * Whether extras like a CFG should be emitted.
     * @return True if extras should be emitted.
     */
    [[nodiscard]] virtual bool emitExtras() const = 0;

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
     * Libraries that should be linked.
     * @return The libraries to link.
     */
    [[nodiscard]] virtual std::vector<std::string> getLibraries() const = 0;

    /**
     * Paths to the directories containing the libraries.
     * @return The paths.
     */
    [[nodiscard]] virtual std::vector<std::string> getLibraryPaths() const = 0;

    ~Unit() override = default;

  private:
    Owned<lang::GlobalScope> global_scope_;

  protected:
    unsigned      pointer_size_ {0};
    SourceVisitor source_visitor_ {*this};
};

#endif
