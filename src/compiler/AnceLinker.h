#ifndef ANCE_SRC_COMPILER_ANCELINKER_H_
#define ANCE_SRC_COMPILER_ANCELINKER_H_

#include <filesystem>

#include "management/elements/Element.h"

/**
 * Represents the linking step which transforms object files into a finished executable.
 */
class AnceLinker
{
  public:
    /**
     * Create a new linker.
     * @param link_config The linker configuration from the project file.
     */
    explicit AnceLinker(std::optional<std::reference_wrapper<const data::Element>> link_config);

    /**
     * Link object files.
     * @param obj The object files to link.
     * @param exe The path of the finished executable.
     */
    void link(const std::filesystem::path& obj, const std::filesystem::path& exe);

  private:
    std::vector<std::string> lib_paths_;
    std::vector<std::string> libs_;
};

#endif
