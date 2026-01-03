#ifndef ANCE_UTILITY_EMPTY_H
#define ANCE_UTILITY_EMPTY_H

namespace ance::utility
{
    /**
     * An empty class. All instances are considered the same.
     */
    class Empty
    {
      public:
        bool operator==(Empty const&) const;
    };
}

#endif
