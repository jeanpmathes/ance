#ifndef ANCE_CET_PRINTER_H
#define ANCE_CET_PRINTER_H

#include <ostream>

#include "ance/utility/Owners.h"

namespace ance::cet
{
    struct Unit;
    struct BasicBlock;

    /// Prints the CET (Compile-able Element Tree) to a stream.
    class Printer
    {
      public:
        explicit Printer(std::ostream& out);
        ~Printer();

        void print(Unit const& unit) const;

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
