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
      private:
        enum Kind
        {
            SIZE_KIND,
            DIFF_KIND
        };

        SizeType(std::string const& name, Kind kind);

        Kind kind_;

      public:
        /**
         * The minimum size of a size value.
         */
        static const size_t MINIMUM_BIT_SIZE = 16;

        /**
         * The minimum size of a diff value.
         */
        static const size_t MINIMUM_DIFF_BIT_SIZE = MINIMUM_BIT_SIZE * 2;

        [[nodiscard]] bool isSizeType() const override;
        [[nodiscard]] bool isDiffType() const override;

        /**
         * Build a value of the size type from a given type size.
         * @param size The type size to use as value.
         * @param context The current compile context.
         * @return The content value containing the given type size.
         */
        static llvm::Value* buildContentValue(llvm::TypeSize size, CompileContext& context);

      private:
        inline static unsigned int size_width_ = 0;
        inline static unsigned int diff_width_ = 0;

      protected:
        std::string createMangledName() const override;

        Optional<size_t>      getBitSize() const override;
        size_t                getNativeBitSize() const override;
        bool                  isSigned() const override;
        size_t                getMinimumBitSize() const override;
        std::string           getSuffix() const override;

      public:
        /**
         * Initialize the size type.
         * @param c The llvm context.
         * @param unit The current unit.
         */
        static void init(llvm::LLVMContext& c, Unit& unit);

        /**
         * Get the size type instance.
         * @return The instance.
         */
        static lang::ResolvingHandle<lang::Type> getSize();

        /**
         * Get the width of the size type.
         */
        static unsigned int getSizeWidth();

        /**
         * Get the diff type instance.
         * @return The instance.
         */
        static lang::ResolvingHandle<lang::Type> getDiff();

        /**
         * Get the width of the diff type.
         */
        static unsigned int getDiffWidth();

        ResolvingHandle<lang::Type> clone() const override;
    };
}
#endif
