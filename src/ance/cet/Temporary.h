#ifndef ANCE_CET_TEMPORARY_H
#define ANCE_CET_TEMPORARY_H

#include "ance/utility/Owners.h"

#include "ance/core/Location.h"

#include "ance/cet/Memory.h"

namespace ance::bbt
{
    class Value;
    struct Temporary;
    class TypeContext;
}

namespace ance::cet
{
    /// A wrapper of BBT temporaries for active use during execution.
    class Temporary : public Memory
    {
      public:
        explicit Temporary(bbt::TypeContext& type_context);
        ~Temporary() override = default;

        [[nodiscard]] utility::Shared<bbt::Value const> access() override;

        utility::Shared<bbt::Value const> read(std::span<size_t const> indices) override;
        void                              write(utility::Shared<bbt::Value const> value, std::span<size_t const> indices) override;

        utility::Shared<bbt::Value const> read();
        void                              write(utility::Shared<bbt::Value const> value);

        [[nodiscard]] bool isDefined() const override;
        [[nodiscard]] utility::Shared<bbt::Type const> type() const override;

      private:
        utility::Shared<bbt::Value const> value_;
        bbt::TypeContext&           type_context_;
    };
}

#endif
