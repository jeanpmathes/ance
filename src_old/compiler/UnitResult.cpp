#include "UnitResult.h"

#include <stdexcept>

UnitResult::operator Value() const
{
    return value_;
}

void UnitResult::addLinkerArguments(std::vector<char const*>& args, TargetDescriptor const& target_descriptor)
{
    if (target_descriptor.getOS() == TargetDescriptor::WINDOWS)
    {
        switch (value_)
        {
            case LIBRARY:

                args.emplace_back("/dll");
                // The subsystem is only relevant for executables.

                break;

            case EXECUTABLE:

                // Executable is the default.
                args.push_back("/subsystem:console");

                break;

            case PACKAGE:

                args.emplace_back("/dll");
                // The subsystem is only relevant for executables.

                break;
        }
    }
    else { throw std::logic_error("Not supported"); }
}

std::string UnitResult::getExtension(TargetDescriptor const& target_descriptor) const
{
    switch (target_descriptor.getOS())
    {
        case TargetDescriptor::WINDOWS:
        {
            switch (value_)
            {
                case EXECUTABLE:
                    return ".exe";
                case PACKAGE:
                case LIBRARY:
                    return ".dll";
            }
        }
    }
}
