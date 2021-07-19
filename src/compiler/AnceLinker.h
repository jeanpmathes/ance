#ifndef ANCE_SRC_COMPILER_ANCELINKER_H_
#define ANCE_SRC_COMPILER_ANCELINKER_H_

#include <filesystem>

#include "compiler/Application.h"
#include "management/elements/Element.h"

class AnceLinker
{
  public:
    explicit AnceLinker(std::optional<std::reference_wrapper<const data::Element>> link_config);

    void link(const std::filesystem::path& bc, const std::filesystem::path& exe);

  private:
    std::vector<std::string> lib_paths_;
    std::vector<std::string> libs_;
};

#endif
