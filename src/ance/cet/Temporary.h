#ifndef ANCE_CET_TEMPORARY_H
#define ANCE_CET_TEMPORARY_H

#include "ance/utility/Owners.h"

#include "ance/core/Location.h"

#include "ance/cet/Memory.h"

namespace ance::bbt
{
    class Value;
    struct Temporary;
}

namespace ance::cet
{
    /// A wrapper of BBT temporaries for active use during execution.
    class Temporary : public Memory
    {
    public:
        Temporary();

        [[nodiscard]] utility::Shared<bbt::Value> access() override;

        utility::Shared<bbt::Value> read(std::vector<size_t> const& indices = {}) override;
        void write(utility::Shared<bbt::Value> value, std::vector<size_t> const& indices = {}) override;

        [[nodiscard]] bool isDefined() const override;

    private:
        utility::Shared<bbt::Value> value_;
    };
}

#endif
