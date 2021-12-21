#ifndef ANCE_SRC_ANCE_TYPE_POINTERTYPE_H_
#define ANCE_SRC_ANCE_TYPE_POINTERTYPE_H_

#include "TypeDefinition.h"

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"
#include "ance/utility/TypeRegistry.h"

class Application;

namespace ance
{
    /**
     * Represents a pointer type. A pointer type has an element type, which is the type of the value pointed too.
     */
    class PointerType : public ance::TypeDefinition
    {
      private:
        explicit PointerType(ance::ResolvingHandle<ance::Type> element_type);

      public:
        bool                              isPointerType() const override;
        ance::ResolvingHandle<ance::Type> getElementType() const override;
        ance::ResolvingHandle<ance::Type> getActualType() override;

        llvm::Constant*    getDefaultContent(llvm::LLVMContext& c) override;
        llvm::PointerType* getContentType(llvm::LLVMContext& c) override;

        bool validate(ValidationLogger& validation_logger, ance::Location location) override;

        bool isSubscriptDefined() override;

        ance::ResolvingHandle<ance::Type> getSubscriptReturnType() override;

        bool                         validateSubscript(ance::Location                    indexed_location,
                                                       ance::ResolvingHandle<ance::Type> index_type,
                                                       ance::Location                    index_location,
                                                       ValidationLogger&                 validation_logger) override;
        std::shared_ptr<ance::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext*        context) override;

      private:
        static llvm::Value* buildGetElementPointer(const std::shared_ptr<ance::Value>& indexed,
                                                   const std::shared_ptr<ance::Value>& index,
                                                   CompileContext*                     context);

      public:
        ~PointerType() override = default;

      private:
        ance::ResolvingHandle<ance::Type> element_type_;
        ance::ResolvingHandle<ance::Type> element_reference_;

      protected:
        std::string   createMangledName() override;
        llvm::DIType* createDebugType(CompileContext* context) override;

      private:
        static ance::TypeRegistry<>& getPointerTypes();

      public:
        static ance::TypeDefinitionRegistry* getRegistry();

        /**
         * Get a pointer type instance.
         * @param element_type The element type.
         * @return The instance.
         */
        static ance::ResolvingHandle<ance::Type> get(ance::ResolvingHandle<ance::Type> element_type);
    };
}

#endif
