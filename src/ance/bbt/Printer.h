#ifndef ANCE_BBT_PRINTER_H
#define ANCE_BBT_PRINTER_H

#include <ostream>

#include "ance/utility/Owners.h"

namespace ance::bbt
{
    struct Flow;

    /// Prints the BBT (Basic Block Tree) to a stream.
    class Printer
    {
      public:
        explicit Printer(std::ostream& out);
        ~Printer();

        void print(Flow const& flow) const;

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
