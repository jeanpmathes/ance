#ifndef ANCE_EST_PRINTER_H
#define ANCE_EST_PRINTER_H

#include <ostream>

#include "ance/utility/Owners.h"

namespace ance::est
{
    struct File;
    struct Statement;

    /// Prints the EST to a stream.
    class Printer
    {
      public:
        explicit Printer(std::ostream& out);
        ~Printer();

        void print(File const& file) const;
        void print(Statement const& statement) const;

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
