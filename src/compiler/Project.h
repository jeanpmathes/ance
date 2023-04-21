#ifndef ANCE_SRC_COMPILER_PROJECT_H_
#define ANCE_SRC_COMPILER_PROJECT_H_

#include <filesystem>
#include <memory>

#include "compiler/Application.h"
#include "compiler/ProjectDescription.h"

class Application;

/**
 * Describes the current project, which is a collection of physical files.
 */
class Project
{
  public:
    /**
     * Create a project from a given description.
     * @param description The project description.
     * @param info The build information.
     */
    explicit Project(ProjectDescription::Description&& description, Application::BuildInfo info);

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
     * Get the path to the project directory.
     * @return The project directory.
     */
    [[nodiscard]] std::filesystem::path getProjectDirectory() const;

    /**
     * Get the paths to all source files.
     * @return The source file paths, relative to the project directory.
     */
    [[nodiscard]] std::vector<std::filesystem::path> getSourceFiles() const;

    /**
     * Get the application that is described by this project.
     * @return The application.
     */
    Application& getApplication();

    [[nodiscard]] ProjectDescription::Description const& description() const;

  private:
    ProjectDescription::Description description_;
    Application                     application_;
};

#endif
