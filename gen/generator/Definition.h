#ifndef DEFINITION_H
#define DEFINITION_H

#include <filesystem>

/// Base class for all definitions that can generate files.
class Definition
{
  public:
    Definition();
    virtual ~Definition() = default;

    virtual void generate(std::filesystem::path const& output_root) const = 0;
};

#endif
