#ifndef ANCE_SRC_COMPILER_PROJECTDESCRIPTION_H_
#define ANCE_SRC_COMPILER_PROJECTDESCRIPTION_H_

#include "Unit.h"

class ProjectDescription : public Unit
{
  public:
    explicit ProjectDescription(std::filesystem::path project_file);

    /**
     * Set the path where the binary form of the project description will be stored.
     * @param path The path.
     */
    void setBinaryDescriptionPath(std::filesystem::path path);

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

    /*
     * Get whether a refresh build is required.
     * @return True if a refresh build is required, false if the binary description is up to date.
     */
    bool isRefreshRequired();

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

    Optional<std::filesystem::path> binary_description_path_;
    Optional<Description>           description_;
};

#endif