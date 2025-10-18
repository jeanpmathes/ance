#ifndef ANCE_CORE_PRINTER_H
#define ANCE_CORE_PRINTER_H

#include <ostream>

#include "ance/utility/Owners.h"
#include "ance/core/Identifier.h"
#include "ance/core/AccessModifier.h"
#include "ance/core/Assigner.h"

namespace ance::core
{
    struct Intrinsic;

    class Type;
    class Value;

    /// Utility to simplify implementing code printers for different trees.
    class Printer
    {
      public:
        explicit Printer(std::ostream& out);
        virtual ~Printer();

      protected:
        /// Print a string to the output stream.
        void print(std::string const& text);

        /// Print a string to the output stream.
        void print(char const* text);

        /// Print an identifier to the output stream.
        void print(Identifier const& identifier);

        /// Print an access modifier to the output stream.
        void print(AccessModifier access_modifier);

        /// Print an assigner to the output stream.
        void print(Assigner assigner);

        /// Print an intrinsic to the output stream.
        void print(Intrinsic const& intrinsic);

        /// Print a type to the output stream.
        void print(Type const& type);

        /// Print a value to the output stream.
        void print(utility::Shared<Value> const& value);

        /// Print a size_t value to the output stream.
        void print(size_t value);

        /// Start a new line.
        void line();

        /// Enter an indented block.
        void enter();

        /// Exit an indented block.
        void exit();

      private:
        void indent();

        std::ostream& out_;

        bool in_new_line_ = true;
        size_t indent_level_ = 0;
    };
}

#endif
