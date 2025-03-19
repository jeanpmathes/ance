#ifndef ANCE_RET_PRINTER_H
#define ANCE_RET_PRINTER_H

#include <ostream>

#include "ance/utility/Owners.h"

namespace ance::ret
{
    struct Statement;

    /// Prints the RET to a stream.
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
