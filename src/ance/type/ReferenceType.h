#ifndef ANCE_SRC_ANCE_TYPE_REFERENCETYPE_H_
#define ANCE_SRC_ANCE_TYPE_REFERENCETYPE_H_

#include "TypeDefinition.h"

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"
#include "ance/utility/TypeRegistry.h"

class Application;

namespace ance
{
    /**
     * A reference refers to another stored value.
     */
    class ReferenceType : public ance::TypeDefinition
    {
      private:
        explicit ReferenceType(ance::ResolvingHandle<ance::Type> element_type);

      public:
        bool                              isReferenceType() const override;
        ance::ResolvingHandle<ance::Type> getElementType() const override;

        llvm::Constant*    getDefaultContent(llvm::LLVMContext& c) override;
        llvm::PointerType* getContentType(llvm::LLVMContext& c) override;

        bool isSubscriptDefined() override;

        ance::ResolvingHandle<ance::Type> getSubscriptReturnType() override;

        bool validate(ValidationLogger& validation_logger, ance::Location location) override;

        bool                         validateSubscript(ance::Location                    indexed_location,
                                                       ance::ResolvingHandle<ance::Type> index_type,
                                                       ance::Location                    index_location,
                                                       ValidationLogger&                 validation_logger) override;
        std::shared_ptr<ance::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext*        context) override;

        ~ReferenceType() override = default;

      private:
        ance::ResolvingHandle<ance::Type> element_type_;

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

      private:
        static ance::TypeRegistry<>& getReferenceTypes();

      public:
        static ance::TypeDefinitionRegistry* getRegistry();

        /**
         * Get the referenced backing value.
         * @param value A native value for a reference-type variable.
         * @param context The current compile context.
         * @return A native value for the referenced value.
         */
        static llvm::Value* getReferenced(llvm::Value* value, CompileContext* context);

        /**
         * Get the referenced value.
         * @param value A value of reference type.
         * @param context The current compile context.
         * @return The referenced value.
         */
        std::shared_ptr<ance::Value> getReferenced(const std::shared_ptr<ance::Value>& value, CompileContext* context);

        /**
         * Get a reference type instance.
         * @param element_type The element type.
         * @return The instance.
         */
        static ance::ResolvingHandle<ance::Type> get(ance::ResolvingHandle<ance::Type> element_type);
    };
}

#endif
