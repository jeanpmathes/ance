#ifndef ANCE_AST_PRINTER_H
#define ANCE_AST_PRINTER_H

#include <ostream>

#include "ance/utility/Owners.h"

namespace ance::ast
{
    struct Statement;

    /**
     * Prints the AST to a stream.
     */
    class Printer
    {
      public:
        explicit Printer(std::ostream& out);
        ~Printer();

        void print(Statement const& statement) const;

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
