#ifndef ANCE_SRC_LANG_TYPE_INTEGERTYPE_H_
#define ANCE_SRC_LANG_TYPE_INTEGERTYPE_H_

#include "TypeDefinition.h"
#include "VectorizableType.h"

namespace lang
{
    /**
     * An abstract class for all integer types.
     */
    class IntegerType : public virtual lang::TypeDefinition
    {
      public:
        [[nodiscard]] StateCount getStateCount() const override;

        llvm::Constant* getDefaultContent(llvm::Module& m) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

      protected:
        /**
         * Get the bit size of the integer type, if a fixed size is defined.
         * @return The size or none.
         */
        virtual std::optional<size_t> getBitSize() const = 0;

        /**
         * Get the size of the integer in bits as it is represented on the machine.
         * @return The native size of the integer.
         */
        virtual size_t getNativeBitSize() const = 0;

        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        llvm::DIType* createDebugType(CompileContext& context) override;
    };
}

#endif
