#ifndef ANCE_CORE_PRINTER_H
#define ANCE_CORE_PRINTER_H

#include <ostream>

#include "ance/core/Identifier.h"

namespace ance::core
{
    /**
     * Utility to simplify implementing code printers for different trees.
     */
    class Printer
    {
      public:
        explicit Printer(std::ostream& out);
        virtual ~Printer();

      protected:
        /**
         * Print a string to the output stream.
         */
        void print(std::string const& text);

        /**
         * Print a string to the output stream.
         */
        void print(char const* text);

        /**
         * Print an identifier to the output stream.
         */
        void print(core::Identifier const& identifier);

        /**
         * Start a new line.
         */
        void line();

        /**
         * Enter an indented block.
         */
        void enter();

        /**
         * Exit an indented block.
         */
        void exit();

      private:
        void indent();

        std::ostream& out_;

        bool in_new_line_ = true;
        size_t indent_level_ = 0;
    };
}

#endif
