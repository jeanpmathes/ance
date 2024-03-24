#ifndef ANCE_SRC_LANG_TYPE_FIXEDWIDTHINTEGERTYPE_H_
#define ANCE_SRC_LANG_TYPE_FIXEDWIDTHINTEGERTYPE_H_

#include "IntegerType.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/utility/TypeRegistry.h"

class Application;

namespace lang
{
    /**
     * Represents a fixed width integer type. They can an arbitrary but fixed bit size and can be signed or unsigned.
     */
    class FixedWidthIntegerType : public IntegerType
    {
      public:
        FixedWidthIntegerType(uint64_t bit_size, bool is_signed);

        Optional<size_t> getBitSize() const override;
        size_t           getNativeBitSize() const override;
        bool             isSigned() const override;
        size_t           getMinimumBitSize() const override;
        std::string      getSuffix() const override;

        static int64_t const MAX_INTEGER_SIZE = 1ll << 16;

        [[nodiscard]] FixedWidthIntegerType const* isFixedWidthIntegerType() const override;
        [[nodiscard]] bool isFixedWidthIntegerType(uint64_t bit_size, bool is_signed) const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        bool                isCastingPossibleTo(Type const& other) const override;
        bool                validateCast(Type const&       other,
                                         lang::Location    location,
                                         ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildCast(lang::Type const&   other,
                                      Shared<lang::Value> value,
                                      Execution&          exec) const override;

      private:
        uint64_t bit_size_;
        bool     is_signed_;

      protected:
        std::string createMangledName() const override;

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}

#endif
