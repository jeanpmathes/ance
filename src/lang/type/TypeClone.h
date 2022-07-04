#ifndef ANCE_SRC_LANG_TYPE_TYPECLONE_H_
#define ANCE_SRC_LANG_TYPE_TYPECLONE_H_

#include "TypeDefinition.h"
#include "lang/utility/Identifier.h"

#include <optional>

namespace lang
{
    /**
     * Defines a type that behaves just like the cloned original type.
     */
    class TypeClone : public lang::TypeDefinition
    {
      public:
        TypeClone(lang::Identifier                  name,
                  lang::ResolvingHandle<lang::Type> original,
                  lang::Location                    definition_location,
                  lang::Location                    original_type_location);

        StateCount getStateCount() const override;

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

        lang::ResolvingHandle<lang::Type> getOriginalType() const override;

        void onScope() override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) override;

        bool validateDefinition(ValidationLogger& validation_logger) const override;
        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        bool                              isSubscriptDefined() override;
        lang::ResolvingHandle<lang::Type> getSubscriptReturnType() override;
        bool                              validateSubscript(lang::Location                    indexed_location,
                                                            lang::ResolvingHandle<lang::Type> index_type,
                                                            lang::Location                    index_location,
                                                            ValidationLogger&                 validation_logger) const override;
        std::shared_ptr<lang::Value>      buildSubscript(std::shared_ptr<Value> indexed,
                                                         std::shared_ptr<Value> index,
                                                         CompileContext*        context) override;

        bool                              hasMember(const lang::Identifier& name) override;
        lang::ResolvingHandle<lang::Type> getMemberType(const lang::Identifier& name) override;
        bool validateMemberAccess(const lang::Identifier& name, ValidationLogger& validation_logger) const override;
        std::shared_ptr<lang::Value> buildMemberAccess(std::shared_ptr<Value>  value,
                                                       const lang::Identifier& name,
                                                       CompileContext*         context) override;

        bool                              definesIndirection() override;
        lang::ResolvingHandle<lang::Type> getIndirectionType() override;
        bool validateIndirection(lang::Location location, ValidationLogger& validation_logger) const override;
        std::shared_ptr<lang::Value> buildIndirection(std::shared_ptr<Value> value, CompileContext* context) override;

      protected:
        std::string                        createMangledName() override;
        llvm::DIType*                      createDebugType(CompileContext* context) override;
        std::vector<lang::TypeDefinition*> getDependencies() const override;

      private:
        lang::ResolvingHandle<lang::Type> original_;
        lang::Location                    original_type_location_;

        mutable std::optional<bool> is_valid_ {};
    };
}

#endif
