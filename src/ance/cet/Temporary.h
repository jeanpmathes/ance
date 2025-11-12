#ifndef ANCE_CET_TEMPORARY_H
#define ANCE_CET_TEMPORARY_H

#include "ance/utility/Owners.h"

#include "ance/core/Location.h"

namespace ance::bbt
{
    class Value;
    struct Temporary;
}

namespace ance::cet
{
    /// A wrapper of BBT temporaries for active use during execution.
    class Temporary
    {
    public:
        Temporary();

        void setValue(utility::Shared<bbt::Value> value);
        utility::Shared<bbt::Value> getValue();

        [[nodiscard]] bbt::Value const& getValue() const;

    private:
        utility::Shared<bbt::Value> value_;
    };
}

#endif
