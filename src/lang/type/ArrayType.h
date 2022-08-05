#ifndef ANCE_SRC_LANG_TYPE_ARRAYTYPE_H_
#define ANCE_SRC_LANG_TYPE_ARRAYTYPE_H_

#include "TypeDefinition.h"

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
    class ArrayType : public lang::TypeDefinition
    {
      private:
        ArrayType(lang::ResolvingHandle<lang::Type> element_type, uint64_t size);

      public:
        static const uint64_t MAX_ARRAY_TYPE_SIZE = 1ll << 32;

        [[nodiscard]] StateCount getStateCount() const override;

        [[nodiscard]] lang::ResolvingHandle<lang::Type> getElementType() const override;
        [[nodiscard]] lang::ResolvingHandle<lang::Type> getActualType() const override;

        llvm::Constant*  getDefaultContent(llvm::Module& m) override;
        llvm::ArrayType* getContentType(llvm::LLVMContext& c) const override;

        bool                              isSubscriptDefined() override;
        lang::ResolvingHandle<lang::Type> getSubscriptReturnType() override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        bool                         validateSubscript(lang::Location                    indexed_location,
                                                       lang::ResolvingHandle<lang::Type> index_type,
                                                       lang::Location                    index_location,
                                                       ValidationLogger&                 validation_logger) const override;
        std::shared_ptr<lang::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext*        context) override;

      private:
        llvm::Value* buildGetElementPointer(const std::shared_ptr<lang::Value>& indexed,
                                            const std::shared_ptr<lang::Value>& index,
                                            CompileContext*                     context);

        llvm::Value* buildGetElementPointer(llvm::Value* indexed, uint64_t index, CompileContext* context);

      public:
        ~ArrayType() override = default;

      protected:
        void buildSingleDefaultInitializerDefinition(llvm::Value* ptr, CompileContext* context) override;
        void buildSingleCopyInitializerDefinition(llvm::Value*    dts_ptr,
                                                  llvm::Value*    src_ptr,
                                                  CompileContext* context) override;
        void buildSingleDefaultFinalizerDefinition(llvm::Value* ptr, CompileContext* context) override;

        std::string                                      createMangledName() const override;
        llvm::DIType*                                    createDebugType(CompileContext* context) override;
        [[nodiscard]] std::vector<lang::TypeDefinition*> getDependencies() const override;

      private:
        uint64_t                          size_;
        lang::ResolvingHandle<lang::Type> element_type_;
        lang::ResolvingHandle<lang::Type> element_reference_;

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
