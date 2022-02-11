#ifndef ANCE_SRC_LANG_TYPE_POINTERTYPE_H_
#define ANCE_SRC_LANG_TYPE_POINTERTYPE_H_

#include "TypeDefinition.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/utility/TypeRegistry.h"

class Application;

namespace lang
{
    /**
     * Represents a pointer type. A pointer type has an element type, which is the type of the value pointed too.
     */
    class PointerType : public lang::TypeDefinition
    {
      private:
        explicit PointerType(lang::ResolvingHandle<lang::Type> element_type);

      public:
        bool                              isPointerType() const override;
        lang::ResolvingHandle<lang::Type> getElementType() const override;
        lang::ResolvingHandle<lang::Type> getActualType() override;

        llvm::Constant*    getDefaultContent(llvm::LLVMContext& c) override;
        llvm::PointerType* getContentType(llvm::LLVMContext& c) override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) override;

        bool isSubscriptDefined() override;

        lang::ResolvingHandle<lang::Type> getSubscriptReturnType() override;

        bool                         validateSubscript(lang::Location                    indexed_location,
                                                       lang::ResolvingHandle<lang::Type> index_type,
                                                       lang::Location                    index_location,
                                                       ValidationLogger&                 validation_logger) override;
        std::shared_ptr<lang::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext*        context) override;

      private:
        static llvm::Value* buildGetElementPointer(const std::shared_ptr<lang::Value>& indexed,
                                                   const std::shared_ptr<lang::Value>& index,
                                                   CompileContext*                     context);

      public:
        ~PointerType() override = default;

      private:
        lang::ResolvingHandle<lang::Type> element_type_;
        lang::ResolvingHandle<lang::Type> element_reference_;

      protected:
        std::string   createMangledName() override;
        llvm::DIType* createDebugType(CompileContext* context) override;

      private:
        static lang::TypeRegistry<>& getPointerTypes();

      public:
        static lang::TypeDefinitionRegistry* getRegistry();

        /**
         * Get a pointer type instance.
         * @param element_type The element type.
         * @return The instance.
         */
        static lang::ResolvingHandle<lang::Type> get(lang::ResolvingHandle<lang::Type> element_type);
    };
}

#endif
