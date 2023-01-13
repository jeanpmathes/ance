#ifndef ANCE_SRC_COMPILER_PROJECTDESCRIPTION_H_
#define ANCE_SRC_COMPILER_PROJECTDESCRIPTION_H_

#include "Unit.h"

class ProjectDescription : public Unit
{
  public:
    explicit ProjectDescription(std::filesystem::path project_file);

    [[nodiscard]] std::string const&                 getName() const override;
    [[nodiscard]] std::filesystem::path              getProjectFile() const override;
    [[nodiscard]] std::filesystem::path              getProjectDirectory() const override;
    [[nodiscard]] std::vector<std::filesystem::path> getSourceFiles() const override;
    [[nodiscard]] UnitResult                         getType() const override;
    void                                             validate(ValidationLogger& validation_logger) const override;

    antlr4::tree::ParseTree* selectTree(anceParser& parser) override;
    void                     addToAbstractSyntaxTree(antlr4::tree::ParseTree* tree, FileContext& context) override;

    [[nodiscard]] std::vector<std::string> getLibraries() const override;
    [[nodiscard]] std::vector<std::string> getLibraryPaths() const override;

    void setResultPath(std::filesystem::path result) override;

  public:
    static constexpr char const* ANCE_PROJECT_DEFINITION_FUNCTION = "define_project";

    struct Description {
        std::string              name;
        std::filesystem::path    project_file;
        std::vector<std::string> linkage_libraries;
        std::vector<std::string> linkage_library_paths;
    };

    /**
     * Load all data from the project definition library.
     */
    bool loadDescription();

    /**
     * Get the description of the project.
     * @return The description.
     */
    [[nodiscard]] Description const& description() const;

  private:
    std::filesystem::path project_file_;
    std::string           name_;

    Optional<Description>           description_;
    Optional<std::filesystem::path> result_path_;
};

#endif
