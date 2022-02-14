#ifndef ANCE_SRC_LANG_TYPE_REFERENCETYPE_H_
#define ANCE_SRC_LANG_TYPE_REFERENCETYPE_H_

#include "TypeDefinition.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/utility/TypeRegistry.h"

class Application;

namespace lang
{
    /**
     * A reference refers to another stored value.
     */
    class ReferenceType : public lang::TypeDefinition
    {
      private:
        explicit ReferenceType(lang::ResolvingHandle<lang::Type> element_type);

      public:
        bool                              isReferenceType() const override;
        lang::ResolvingHandle<lang::Type> getElementType() const override;
        lang::ResolvingHandle<lang::Type> getActualType() override;

        llvm::Constant*    getDefaultContent(llvm::LLVMContext& c) override;
        llvm::PointerType* getContentType(llvm::LLVMContext& c) override;

        bool isSubscriptDefined() override;

        lang::ResolvingHandle<lang::Type> getSubscriptReturnType() override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) override;

        bool                         validateSubscript(lang::Location                    indexed_location,
                                                       lang::ResolvingHandle<lang::Type> index_type,
                                                       lang::Location                    index_location,
                                                       ValidationLogger&                 validation_logger) override;
        std::shared_ptr<lang::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext*        context) override;

        ~ReferenceType() override = default;

      private:
        lang::ResolvingHandle<lang::Type> element_type_;

      protected:
        std::string   createMangledName() override;
        llvm::DIType* createDebugType(CompileContext* context) override;

      private:
        static lang::TypeRegistry<>& getReferenceTypes();

      public:
        static lang::TypeDefinitionRegistry* getRegistry();

        /**
         * Get the referenced backing value.
         * @param value A native value for a reference-type variable.
         * @param context The current compile context.
         * @return A native value for the referenced value.
         */
        llvm::Value* getReferenced(llvm::Value* value, CompileContext* context);

        /**
         * Get the referenced value.
         * @param value A value of reference type.
         * @param context The current compile context.
         * @return The referenced value.
         */
        std::shared_ptr<lang::Value> getReferenced(const std::shared_ptr<lang::Value>& value, CompileContext* context);

        /**
         * Get a reference type instance.
         * @param element_type The element type.
         * @return The instance.
         */
        static lang::ResolvingHandle<lang::Type> get(lang::ResolvingHandle<lang::Type> element_type);
    };
}

#endif
