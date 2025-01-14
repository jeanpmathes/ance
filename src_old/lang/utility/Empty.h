#ifndef ANCE_SRC_LANG_UTILITY_EMPTY_H_
#define ANCE_SRC_LANG_UTILITY_EMPTY_H_

namespace lang
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
