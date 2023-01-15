#include "UnitResult.h"

UnitResult::operator Value() const
{
    return value_;
}

void UnitResult::addLinkerArguments(std::vector<char const*>& args)
{
    switch (value_)
    {
        case LIBRARY:

            args.emplace_back("/dll");
            // No entry point needed for now.

            break;

        case EXECUTABLE:

            // Executable is the default.
            args.push_back("/entry:start$lang");

            break;
    }
}

std::string UnitResult::getExtension() const
{
    switch (value_)
    {
        case LIBRARY:
            return ".dll";
        case EXECUTABLE:
            return ".exe";
    }
}