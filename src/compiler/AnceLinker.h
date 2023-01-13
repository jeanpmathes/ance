#ifndef ANCE_SRC_COMPILER_ANCELINKER_H_
#define ANCE_SRC_COMPILER_ANCELINKER_H_

#include <filesystem>

class Unit;

/**
 * Represents the linking step which transforms object files into a finished binary.
 */
class AnceLinker
{
  public:
    /**
     * Create a new linker.
     * @param unit The unit to link.
     */
    explicit AnceLinker(Unit& unit);

    /**
     * Link object files.
     * @param obj The object files to link.
     * @param app The path of the finished application.
     * @return True if the linking was successful, false otherwise.
     */
    bool link(std::filesystem::path const& obj, std::filesystem::path const& app);

  private:
    Unit& unit_;
};

#endif
