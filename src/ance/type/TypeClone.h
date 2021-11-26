#ifndef ANCE_SRC_ANCE_TYPE_TYPECLONE_H_
#define ANCE_SRC_ANCE_TYPE_TYPECLONE_H_

#include "TypeDefinition.h"

#include <optional>

namespace ance
{
    /**
     * Defines a type that behaves just like the cloned original type.
     */
    class TypeClone : public ance::TypeDefinition
    {
      public:
        TypeClone(const std::string&                identifier,
                  ance::ResolvingHandle<ance::Type> original,
                  ance::Location                    definition_location,
                  ance::Location                    original_type_location);

        ance::ResolvingHandle<ance::Type> getOriginalType() override;

        void onScope() override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

        bool isSubscriptDefined() override;

        ance::ResolvingHandle<ance::Type> getSubscriptReturnType() override;

        bool validateDefinition(ValidationLogger& validation_logger) override;
        bool validate(ValidationLogger& validation_logger, ance::Location location) override;

        bool validateSubscript(ance::Location                    indexed_location,
                               ance::ResolvingHandle<ance::Type> index_type,
                               ance::Location                    index_location,
                               ValidationLogger&                 validation_logger) override;

        std::shared_ptr<ance::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext*        context) override;

      protected:
        llvm::DIType*                      createDebugType(CompileContext* context) override;
        std::vector<ance::TypeDefinition*> getDependencies() override;

      private:
        ance::ResolvingHandle<ance::Type> original_;
        ance::Location                    original_type_location_;

        std::optional<bool> is_valid_ {};
    };
}

#endif
