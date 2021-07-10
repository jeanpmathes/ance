#ifndef ANCE_SRC_COMPILER_APPLICATION_H_
#define ANCE_SRC_COMPILER_APPLICATION_H_

#include <filesystem>

#include "File.h"
#include "Scope.h"

class Statement;

class CompileContext;

namespace ance
{
    class Scope;

    class Function;
}

class Application
{
  public:
    explicit Application(data::File& project);

    Application(const Application&) = delete;

    Application(Application&&) = delete;

  public:
    void setPointerSize(unsigned size);

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] std::filesystem::path getProjectFile() const;

    [[nodiscard]] std::filesystem::path getSourceFile() const;

    [[nodiscard]] unsigned getBitness() const;

    bool validate();

    ance::GlobalScope* globalScope();

  private:
    data::File& project_;

    ance::GlobalScope* global_scope_;

    unsigned pointer_size_ {0};
};

#endif