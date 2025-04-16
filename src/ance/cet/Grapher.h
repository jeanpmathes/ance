#ifndef ANCE_CET_GRAPHER_H
#define ANCE_CET_GRAPHER_H

#include <ostream>

#include "ance/utility/Owners.h"

namespace ance::cet
{
    struct Unit;

    /// Graphs the CET to a stream.
    class Grapher
    {
    public:
        explicit Grapher(std::ostream& out);
        ~Grapher();

        void graph(Unit const& unit) const;

    private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
