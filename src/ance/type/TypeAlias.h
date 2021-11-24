#ifndef ANCE_SRC_ANCE_TYPE_TYPEALIAS_H_
#define ANCE_SRC_ANCE_TYPE_TYPEALIAS_H_

#include "TypeDefinition.h"

#include <optional>

namespace ance
{
    /**
     * Defines a type that can be used as an alias for the actual type.
     */
    class TypeAlias : public ance::TypeDefinition
    {
      public:
        TypeAlias(const std::string&                identifier,
                  ance::ResolvingHandle<ance::Type> actual,
                  ance::Location                    definition_location,
                  ance::Location                    actual_type_location);

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

        bool                         isImplicitlyConvertibleTo(ance::ResolvingHandle<ance::Type> target) override;
        std::shared_ptr<ance::Value> convertImplicitlyTo(ance::ResolvingHandle<ance::Type> target,
                                                         std::shared_ptr<Value>            value,
                                                         CompileContext*                   context) override;

        bool                         isImplicitlyConvertibleFrom(ance::ResolvingHandle<ance::Type> source) override;
        std::shared_ptr<ance::Value> convertImplicitlyFrom(std::shared_ptr<Value>            value,
                                                           ance::ResolvingHandle<ance::Type> self,
                                                           CompileContext*                   context) override;

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

        std::vector<ance::TypeDefinition*> getDependencies() override;

      private:
        ance::ResolvingHandle<ance::Type> actual_;
        ance::Location                    actual_type_location_;

        std::optional<bool> is_valid_ {};
    };
}

#endif
