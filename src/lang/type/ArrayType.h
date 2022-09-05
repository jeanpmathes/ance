#ifndef ANCE_SRC_LANG_TYPE_ARRAYTYPE_H_
#define ANCE_SRC_LANG_TYPE_ARRAYTYPE_H_

#include "SequenceType.h"

#include <llvm/IR/DerivedTypes.h>

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/utility/TypeRegistry.h"

namespace lang
{
    class Scope;
}

class Application;

namespace lang
{
    /**
     * Represents array types. Array types have an element type and a length.
     */
    class ArrayType : public lang::SequenceType
    {
      private:
        ArrayType(lang::ResolvingHandle<lang::Type> element_type, uint64_t size);

      public:
        static const uint64_t MAX_ARRAY_TYPE_SIZE = 1ll << 32;

        bool isArrayType() const override;

        [[nodiscard]] lang::ResolvingHandle<lang::Type> getActualType() const override;

        llvm::Constant*  getDefaultContent(llvm::Module& m) override;
        llvm::ArrayType* getContentType(llvm::LLVMContext& c) const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

      public:
        ~ArrayType() override = default;

      protected:
        std::string                                      createMangledName() const override;
        llvm::DIType*                                    createDebugType(CompileContext& context) override;

      private:
        static lang::TypeRegistry<uint64_t>& getArrayTypes();

      public:
        static lang::TypeDefinitionRegistry* getRegistry();

        /**
         * Get an array type instance.
         * @param element_type The element type of the array.
         * @param size The size of the array. Must be greater than zero.
         * @return The array type instance.
         */
        static lang::ResolvingHandle<lang::Type> get(lang::ResolvingHandle<lang::Type> element_type, uint64_t size);
    };
}

#endif
