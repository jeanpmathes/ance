#ifndef ANCE_SRC_LANG_TYPE_VECTORTYPE_H_
#define ANCE_SRC_LANG_TYPE_VECTORTYPE_H_

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
     * Represents a vector type.
     */
    class VectorType : public lang::TypeDefinition
    {
      private:
        VectorType(lang::ResolvingHandle<lang::Type> element_type, uint64_t size);

      public:
        static const uint64_t MAX_VECTOR_TYPE_SIZE = 1ll << 32;

        bool isVectorType() const override;

        [[nodiscard]] StateCount getStateCount() const override;

        [[nodiscard]] lang::ResolvingHandle<lang::Type> getElementType() const override;
        [[nodiscard]] lang::ResolvingHandle<lang::Type> getActualType() const override;

        llvm::Constant* getDefaultContent(llvm::Module& m) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

        bool                              isSubscriptDefined() override;
        lang::ResolvingHandle<lang::Type> getSubscriptReturnType() override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        bool                         validateSubscript(lang::Location                    indexed_location,
                                                       lang::ResolvingHandle<lang::Type> index_type,
                                                       lang::Location                    index_location,
                                                       ValidationLogger&                 validation_logger) const override;
        std::shared_ptr<lang::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext&        context) override;

        bool isOperatorDefined(lang::BinaryOperator op, lang::ResolvingHandle<lang::Type> other) override;
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::BinaryOperator              op,
                                                                lang::ResolvingHandle<lang::Type> other) override;
        bool                              validateOperator(lang::BinaryOperator              op,
                                                           lang::ResolvingHandle<lang::Type> other,
                                                           lang::Location                    left_location,
                                                           lang::Location                    right_location,
                                                           ValidationLogger&                 validation_logger) const override;
        std::shared_ptr<lang::Value>      buildOperator(lang::BinaryOperator   op,
                                                        std::shared_ptr<Value> left,
                                                        std::shared_ptr<Value> right,
                                                        CompileContext&        context) override;

      private:
        llvm::Value* buildGetElementPointer(const std::shared_ptr<lang::Value>& indexed,
                                            const std::shared_ptr<lang::Value>& index,
                                            CompileContext&                     context) const;

        llvm::Value* buildGetElementPointer(llvm::Value* indexed, uint64_t index, CompileContext& context) const;

      public:
        ~VectorType() override = default;

      protected:
        void buildSingleDefaultInitializerDefinition(llvm::Value* ptr, CompileContext& context) override;
        void buildSingleCopyInitializerDefinition(llvm::Value*    dts_ptr,
                                                  llvm::Value*    src_ptr,
                                                  CompileContext& context) override;
        void buildSingleDefaultFinalizerDefinition(llvm::Value* ptr, CompileContext& context) override;

        std::string                                      createMangledName() const override;
        llvm::DIType*                                    createDebugType(CompileContext& context) override;
        [[nodiscard]] std::vector<lang::TypeDefinition*> getDependencies() const override;

      private:
        uint64_t                          size_;
        lang::ResolvingHandle<lang::Type> element_type_;
        lang::ResolvingHandle<lang::Type> element_reference_;

      private:
        static lang::TypeRegistry<uint64_t>& getVectorTypes();

      public:
        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        static lang::TypeDefinitionRegistry* getRegistry();

        /**
         * Get an vector type instance.
         * @param element_type The element type of the vector.
         * @param size The size of the vector. Must be greater than zero.
         * @return The vector type instance.
         */
        static lang::ResolvingHandle<lang::Type> get(lang::ResolvingHandle<lang::Type> element_type, uint64_t size);
    };
}

#endif
