#include "Application.h"

#include "compiler/CodePrinter.h"
#include "compiler/Project.h"
#include "validation/ValidationLogger.h"

#include "lang/type/HalfType.h"
#include "lang/type/ArrayType.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/VectorType.h"
#include "lang/type/SizeType.h"

Application::Application(Project& project) : project_(project) {}

std::string const& Application::getName() const
{
    if (!name_.hasValue()) { name_ = project_.getName(); }

    return name_.value();
}

void Application::validate(ValidationLogger& validation_logger) const
{
    this->globalScope().validate(validation_logger);

    if (!this->globalScope().hasEntry())
    {
        validation_logger.logError("Entry point 'main() : u32' could not be found", lang::Location::global());
    }

    if (!this->globalScope().hasExit())
    {
        validation_logger.logError("Exit point 'exit(u32)' could not be found", lang::Location::global());
    }
}

std::filesystem::path Application::getProjectFile() const
{
    return project_.getProjectFile();
}

std::filesystem::path Application::getProjectDirectory() const
{
    return project_.getProjectDirectory();
}

std::vector<std::filesystem::path> Application::getSourceFiles() const
{
    return project_.getSourceFiles();
}

UnitResult Application::getType() const
{
    return UnitResult::EXECUTABLE;
}

OptLevel Application::getOptimizationLevel() const
{
    return project_.description().opt_level;
}

bool Application::emitExtras() const
{
    return project_.description().emit_extras;
}

antlr4::tree::ParseTree* Application::selectTree(anceParser& parser)
{
    return parser.file();
}

void Application::addToAbstractSyntaxTree(antlr4::tree::ParseTree* tree, FileContext& context)
{
    source_visitor_.setFileContext(context);
    source_visitor_.visit(tree);
}

std::vector<std::string> Application::getLibraries() const
{
    return project_.description().linkage_libraries;
}

std::vector<std::string> Application::getLibraryPaths() const
{
    return project_.description().linkage_library_paths;
}
