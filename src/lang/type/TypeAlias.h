#ifndef ANCE_SRC_LANG_TYPE_TYPEALIAS_H_
#define ANCE_SRC_LANG_TYPE_TYPEALIAS_H_

#include "TypeDefinition.h"
#include "lang/utility/Identifier.h"

#include <optional>

namespace lang
{
    /**
     * Defines a type that can be used as an alias for the actual type.
     */
    class TypeAlias : public lang::TypeDefinition
    {
      public:
        TypeAlias(lang::Identifier                  name,
                  lang::ResolvingHandle<lang::Type> actual,
                  lang::Location                    definition_location,
                  lang::Location                    actual_type_location);

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

        lang::ResolvingHandle<lang::Type> getActualType() const override;

        void onScope() override;

        llvm::Constant* getDefaultContent(llvm::Module& m) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) const override;

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
                                                         CompileContext&        context) override;

        bool                         isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other) override;
        bool                         validateImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                lang::Location                    location,
                                                                ValidationLogger&                 validation_logger) const override;
        std::shared_ptr<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                             std::shared_ptr<Value>            value,
                                                             CompileContext&                   context) override;

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

        bool                              hasMember(const lang::Identifier& name) override;
        lang::ResolvingHandle<lang::Type> getMemberType(const lang::Identifier& name) override;
        bool validateMemberAccess(const lang::Identifier& name, ValidationLogger& validation_logger) const override;
        std::shared_ptr<lang::Value> buildMemberAccess(std::shared_ptr<Value>  value,
                                                       const lang::Identifier& name,
                                                       CompileContext&         context) override;

        bool                              definesIndirection() override;
        lang::ResolvingHandle<lang::Type> getIndirectionType() override;
        bool validateIndirection(lang::Location location, ValidationLogger& validation_logger) const override;
        std::shared_ptr<lang::Value> buildIndirection(std::shared_ptr<Value> value, CompileContext& context) override;

        void buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext& context) override;
        void buildCopyInitializer(llvm::Value* ptr, llvm::Value* original, CompileContext& context) override;
        void buildFinalizer(llvm::Value* ptr, llvm::Value* count, CompileContext& context) override;

        void createConstructors() override;
        void buildNativeDeclaration(CompileContext& context) override;
        void buildNativeDefinition(CompileContext& context) override;

      protected:
        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext& context) override;

        std::vector<lang::TypeDefinition*> getDependencies() const override;

      private:
        lang::ResolvingHandle<lang::Type> actual_;
        lang::Location                    actual_type_location_;

        mutable std::optional<lang::ResolvingHandle<lang::Type>> actually_actual_ {};
        mutable std::optional<bool>                              is_valid_ {};
    };
}

#endif
