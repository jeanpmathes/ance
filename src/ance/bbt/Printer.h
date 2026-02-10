#ifndef ANCE_BBT_PRINTER_H
#define ANCE_BBT_PRINTER_H

#include <ostream>

#include "ance/utility/Owners.h"

namespace ance::bbt
{
    struct Flows;
    struct Flow;
    struct BasicBlock;

    /// Prints the BBT (Basic Block Tree) to a stream.
    class Printer
    {
      public:
        explicit Printer(std::ostream& out);
        ~Printer();

        void print(Flows const& flows) const;
        void print(Flow const& flow) const;
        void print(BasicBlock const& block) const;

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
