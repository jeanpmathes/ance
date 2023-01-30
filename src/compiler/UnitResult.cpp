#include "UnitResult.h"

#include <stdexcept>

UnitResult::operator Value() const
{
    return value_;
}

void UnitResult::addLinkerArguments(std::vector<char const*>& args, std::string const& os)
{
    switch (value_)
    {
        case LIBRARY:

            args.emplace_back("/dll");
            args.push_back("/entry:lib_start$lang");

            break;

        case EXECUTABLE:

            // Executable is the default.
            args.push_back("/entry:start$lang");

            if (os == "windows") { args.push_back("/subsystem:console"); }

            break;
    }
}

std::string UnitResult::getExtension(llvm::Triple const& triple) const
{
    switch (triple.getOS())
    {
        case llvm::Triple::Win32:
        {
            switch (value_)
            {
                case LIBRARY:
                    return ".dll";
                case EXECUTABLE:
                    return ".exe";
            }
        }

        default:
            throw std::logic_error("Not supported.");
    }
}
