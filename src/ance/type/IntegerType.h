#ifndef ANCE_SRC_ANCE_TYPE_INTEGERTYPE_H_
#define ANCE_SRC_ANCE_TYPE_INTEGERTYPE_H_

#include "TypeDefinition.h"

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"
#include "ance/utility/TypeRegistry.h"

class Application;

namespace ance
{
    /**
     * Represents an integer type. Integers can have any precision and can be both signed or unsigned.
     */
    class IntegerType : public ance::TypeDefinition
    {
      private:
        IntegerType(uint64_t bit_size, bool is_signed);

      public:
        bool isIntegerType() const override;
        bool isIntegerType(uint64_t bit_size, bool is_signed) const override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) override;

      private:
        uint64_t    bit_size_;
        bool        is_signed_;
        llvm::Type* type_ {nullptr};

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

      private:
        static ance::TypeRegistry<std::pair<uint64_t, bool>>& getIntegerTypes();

      public:
        static ance::TypeDefinitionRegistry* getRegistry();

        /**
         * Get an integer type instance.
         * @param bit_size The size of the integer.
         * @param is_signed Whether the integer should be signed.
         * @return The instance.
         */
        static ance::ResolvingHandle<ance::Type> get(uint64_t bit_size, bool is_signed);
    };
}

#endif