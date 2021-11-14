#ifndef ANCE_SRC_ANCE_TYPE_TYPECLONE_H_
#define ANCE_SRC_ANCE_TYPE_TYPECLONE_H_

#include "TypeDefinition.h"

namespace ance
{
    class TypeClone : public ance::TypeDefinition
    {
      public:
        TypeClone(const std::string& identifier, ance::ResolvingHandle<ance::Type> original);

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

        bool isSubscriptDefined() override;

        ance::ResolvingHandle<ance::Type> getSubscriptReturnType() override;

        bool validate(ValidationLogger& validation_logger, ance::Location location) override;

        bool validateSubscript(ance::Location                    indexed_location,
                               ance::ResolvingHandle<ance::Type> index_type,
                               ance::Location                    index_location,
                               ValidationLogger&                 validation_logger) override;

        std::shared_ptr<ance::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext*        context) override;

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

      private:
        ance::ResolvingHandle<ance::Type> original_;
    };
}

#endif
