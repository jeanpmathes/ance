#ifndef ANCE_SRC_ANCE_TYPE_ARRAYTYPE_H_
#define ANCE_SRC_ANCE_TYPE_ARRAYTYPE_H_

#include "TypeDefinition.h"

#include <llvm/IR/DerivedTypes.h>

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"
#include "ance/utility/TypeRegistry.h"

namespace ance
{
    class Scope;
}

class Application;

namespace ance
{
    /**
     * Represents array types. Array types have an element type and a length.
     */
    class ArrayType : public ance::TypeDefinition
    {
      private:
        ArrayType(ance::ResolvingHandle<ance::Type> element_type, uint64_t size);

      public:
        ance::ResolvingHandle<ance::Type> getElementType() const override;

        llvm::Constant*  getDefaultContent(llvm::LLVMContext& c) override;
        llvm::ArrayType* getContentType(llvm::LLVMContext& c) override;

        bool                              isSubscriptDefined() override;
        ance::ResolvingHandle<ance::Type> getSubscriptReturnType() override;

        bool validate(ValidationLogger& validation_logger, ance::Location location) override;

        bool                         validateSubscript(ance::Location                    indexed_location,
                                                       ance::ResolvingHandle<ance::Type> index_type,
                                                       ance::Location                    index_location,
                                                       ValidationLogger&                 validation_logger) override;
        std::shared_ptr<ance::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext*        context) override;

      private:
        llvm::Value* buildGetElementPointer(const std::shared_ptr<ance::Value>& indexed,
                                            const std::shared_ptr<ance::Value>& index,
                                            CompileContext*                     context) const;

      public:
        ~ArrayType() override = default;

      protected:
        std::string   createMangledName() override;
        llvm::DIType* createDebugType(CompileContext* context) override;

      private:
        uint64_t                          size_;
        ance::ResolvingHandle<ance::Type> element_type_;
        ance::ResolvingHandle<ance::Type> element_reference_;
        llvm::ArrayType*                  type_ {nullptr};

      private:
        static ance::TypeRegistry<uint64_t>& getArrayTypes();

      public:
        static ance::TypeDefinitionRegistry* getRegistry();

        /**
         * Get an array type instance.
         * @param element_type The element type of the array.
         * @param size The size of the array. Must be greater than zero.
         * @return The array type instance.
         */
        static ance::ResolvingHandle<ance::Type> get(ance::ResolvingHandle<ance::Type> element_type, uint64_t size);
    };
}

#endif
