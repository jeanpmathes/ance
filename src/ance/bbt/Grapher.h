#ifndef ANCE_BBT_GRAPHER_H
#define ANCE_BBT_GRAPHER_H

#include <ostream>

#include "ance/utility/Owners.h"

namespace ance::bbt
{
    struct Flow;

    /// Graphs the BBT to a stream.
    class Grapher
    {
    public:
        explicit Grapher(std::ostream& out);
        ~Grapher();

        void graph(Flow const& flow) const;

    private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
