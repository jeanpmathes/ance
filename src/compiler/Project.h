#ifndef ANCE_SRC_COMPILER_PROJECT_H_
#define ANCE_SRC_COMPILER_PROJECT_H_

#include <filesystem>
#include <memory>

#include "compiler/Application.h"

namespace data
{
    class File;
}

class Application;

/**
 * Describes the current project, which is a collection of physical files.
 */
class Project
{
  public:
    explicit Project(data::File& project);

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
     * Get the path to the source file.
     * @return The source file.
     */
    [[nodiscard]] std::filesystem::path getSourceFile() const;

    /**
     * Get the application that is described by this project.
     * @return The application.
     */
    Application& getApplication();

  private:
    data::File& project_;
    Application application_;
};

#endif

