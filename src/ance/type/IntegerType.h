#ifndef ANCE_SRC_ANCE_TYPE_INTEGERTYPE_H_
#define ANCE_SRC_ANCE_TYPE_INTEGERTYPE_H_

#include "TypeDefinition.h"

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"

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
        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

      private:
        uint64_t    bit_size_;
        bool        is_signed_;
        llvm::Type* type_ {nullptr};

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

      private:
        static std::vector<std::pair<std::pair<uint64_t, bool>, ance::ResolvingHandle<ance::Type>>>& getIntegerTypes();

      public:
        /**
         * Get an integer type instance.
         * @param bit_size The size of the integer.
         * @param is_signed Whether the integer should be signed.
         * @return The instance.
         */
        static ance::ResolvingHandle<ance::Type> get(uint64_t bit_size, bool is_signed);

        /**
         * Check if a given type is an integer type with the given attributes.
         * @param type The type to check.
         * @param bit_size The size attribute.
         * @param is_signed The sign attribute.
         * @return True if the given type is as specified.
         */
        static bool isIntegerType(ance::ResolvingHandle<ance::Type> type, uint64_t bit_size, bool is_signed);
    };
}

#endif