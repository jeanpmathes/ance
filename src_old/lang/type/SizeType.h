#ifndef ANCE_SRC_LANG_TYPE_SIZETYPE_H_
#define ANCE_SRC_LANG_TYPE_SIZETYPE_H_

#include "IntegerType.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Unit;

namespace lang
{
    /**
     * Represents an unsigned integer capable of holding the size of the largest possible array as well as a type of holding all possible differences of such sizes.
     */
    class SizeType : public IntegerType
    {
      public:
        enum Kind
        {
            SIZE_KIND,
            DIFF_KIND
        };

        SizeType(std::string const& name, Kind kind);

      private:
        Kind kind_;

      public:
        /**
         * The minimum size of a size value.
         */
        static size_t const MINIMUM_BIT_SIZE = 16;

        /**
         * The minimum size of a diff value.
         */
        static size_t const MINIMUM_DIFF_BIT_SIZE = MINIMUM_BIT_SIZE * 2;

        [[nodiscard]] bool isSizeType() const override;
        [[nodiscard]] bool isDiffType() const override;

      private:
        inline static unsigned int size_width_ = 0;
        inline static unsigned int diff_width_ = 0;

      protected:
        std::string createMangledName() const override;

        Optional<size_t> getBitSize() const override;
        size_t           getNativeBitSize() const override;
        bool             isSigned() const override;
        size_t           getMinimumBitSize() const override;
        std::string      getSuffix() const override;

      public:
        /**
         * Initialize the size type.
         * @param unit The current unit.
         */
        static void init(Unit& unit);

        /**
         * Get the width of the size type.
         */
        static unsigned int getSizeWidth();

        /**
         * Get the width of the diff type.
         */
        static unsigned int getDiffWidth();

        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}
#endif
