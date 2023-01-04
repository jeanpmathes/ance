#ifndef ANCE_SRC_COMPILER_APPLICATIONTYPE_H_
#define ANCE_SRC_COMPILER_APPLICATIONTYPE_H_

#include <string>
#include <vector>

/**
 * The resulting build artifact type of a project.
 */
class ApplicationType
{
  public:
    enum Value
    {
        /**
     * A shared library.
     */
        LIBRARY,

        /**
     * An executable.
     */
        EXECUTABLE
    };

    ApplicationType() = default;
    constexpr ApplicationType(Value val) : value_(val) {}// NOLINT(google-explicit-constructor)

             operator Value() const;// NOLINT(google-explicit-constructor)
    explicit operator bool() = delete;

    /**
     * Add the required linker arguments for this application type to the given vector.
     * @param args The vector to add the arguments to.
     */
    void addLinkerArguments(std::vector<char const*>& args);

    /**
     * Get the file extension for this application type.
     * @return The file extension.
     */
    [[nodiscard]] std::string getExtension() const;

  private:
    Value value_;
};

#endif
