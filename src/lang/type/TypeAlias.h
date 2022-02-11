#ifndef ANCE_SRC_ANCE_TYPE_TYPEALIAS_H_
#define ANCE_SRC_ANCE_TYPE_TYPEALIAS_H_

#include "TypeDefinition.h"

#include <optional>

namespace lang
{
    /**
     * Defines a type that can be used as an alias for the actual type.
     */
    class TypeAlias : public lang::TypeDefinition
    {
      public:
        TypeAlias(const std::string&                identifier,
                  lang::ResolvingHandle<lang::Type> actual,
                  lang::Location                    definition_location,
                  lang::Location                    actual_type_location);

        [[nodiscard]] bool isIntegerType() const override;
        [[nodiscard]] bool isIntegerType(uint64_t bit_size, bool is_signed) const override;
        [[nodiscard]] bool isBooleanType() const override;
        [[nodiscard]] bool isFloatingPointType() const override;
        [[nodiscard]] bool isFloatingPointType(size_t precision) const override;
        [[nodiscard]] bool isSizeType() const override;
        [[nodiscard]] bool isDiffType() const override;
        [[nodiscard]] bool isVoidType() const override;
        [[nodiscard]] bool isPointerType() const override;
        [[nodiscard]] bool isReferenceType() const override;

        [[nodiscard]] lang::ResolvingHandle<lang::Type> getElementType() const override;

        lang::ResolvingHandle<lang::Type> getActualType() override;

        void onScope() override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

        bool                              isSubscriptDefined() override;
        lang::ResolvingHandle<lang::Type> getSubscriptReturnType() override;

        bool validateDefinition(ValidationLogger& validation_logger) override;
        bool validate(ValidationLogger& validation_logger, lang::Location location) override;

        bool validateSubscript(lang::Location                    indexed_location,
                               lang::ResolvingHandle<lang::Type> index_type,
                               lang::Location                    index_location,
                               ValidationLogger&                 validation_logger) override;

        std::shared_ptr<lang::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext*        context) override;

      protected:
        std::string   createMangledName() override;
        llvm::DIType* createDebugType(CompileContext* context) override;

        std::vector<lang::TypeDefinition*> getDependencies() override;

      private:
        lang::ResolvingHandle<lang::Type> actual_;
        lang::Location                    actual_type_location_;

        std::optional<lang::ResolvingHandle<lang::Type>> actually_actual_ {};
        std::optional<bool>                              is_valid_ {};
    };
}

#endif
