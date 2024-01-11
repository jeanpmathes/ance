#ifndef ANCE_SRC_LANG_TYPE_TYPEALIAS_H_
#define ANCE_SRC_LANG_TYPE_TYPEALIAS_H_

#include "CustomType.h"

#include <optional>

#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/FloatingPointType.h"
#include "lang/utility/Identifier.h"

namespace lang
{
    /**
     * Defines a type that can be used as an alias for the actual type.
     */
    class TypeAlias : public lang::CustomType
    {
      public:
        TypeAlias(lang::Accessibility               accessibility,
                  lang::Identifier                  name,
                  lang::ResolvingHandle<lang::Type> actual,
                  lang::Location                    definition_location);

        StateCount     getStateCount() const override;

        [[nodiscard]] FixedWidthIntegerType const* isFixedWidthIntegerType() const override;
        [[nodiscard]] bool               isFixedWidthIntegerType(uint64_t bit_size, bool is_signed) const override;
        [[nodiscard]] bool               isSigned() const override;
        [[nodiscard]] IntegerType const* isIntegerType() const override;
        [[nodiscard]] bool               isBooleanType() const override;
        [[nodiscard]] bool               isCharType() const override;
        [[nodiscard]] bool               isUnsignedIntegerPointerType() const override;
        [[nodiscard]] FloatingPointType const*     isFloatingPointType() const override;
        [[nodiscard]] bool                         isFloatingPointType(size_t precision) const override;
        [[nodiscard]] bool                         isSizeType() const override;
        [[nodiscard]] bool                         isDiffType() const override;
        [[nodiscard]] bool                         isUnitType() const override;
        [[nodiscard]] bool                         isNullValueType() const override;
        [[nodiscard]] bool                         isPointerType() const override;
        [[nodiscard]] lang::AddressType const*     isAddressType() const override;
        [[nodiscard]] bool                         isBufferType() const override;
        [[nodiscard]] bool                         isOpaquePointerType() const override;
        [[nodiscard]] bool                         isReferenceType() const override;
        [[nodiscard]] bool                         isStructType() const override;
        [[nodiscard]] VectorizableType const*      isVectorizable() const override;
        [[nodiscard]] VectorizableType*            isVectorizable() override;
        [[nodiscard]] VectorType const*            isVectorType() const override;
        [[nodiscard]] VectorType*                  isVectorType() override;
        [[nodiscard]] ArrayType const*             isArrayType() const override;
        [[nodiscard]] ArrayType*                   isArrayType() override;

        lang::ResolvingHandle<lang::Type> getElementType() override;
        [[nodiscard]] lang::Type const&   getElementType() const override;

        lang::ResolvingHandle<lang::Type> getActualType() override;
        [[nodiscard]] lang::Type const&   getActualType() const override;

        llvm::Constant* getDefaultContent(CompileContext& context) const override;

        llvm::Type* getContentType(CompileContext& context) const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        bool                              isSubscriptDefined() const override;
        lang::ResolvingHandle<lang::Type> getSubscriptReturnType() override;
        bool                              validateSubscript(lang::Location    indexed_location,
                                                            lang::Type const& index_type,
                                                            lang::Location    index_location,
                                                            ValidationLogger& validation_logger) const override;
        Shared<lang::Value>               buildSubscript(Shared<lang::Value> indexed,
                                                         Shared<lang::Value> index,
                                                         CompileContext& context) override;

        bool                isImplicitlyConvertibleTo(lang::Type const& other) const override;
        bool                validateImplicitConversion(lang::Type const& other,
                                                       lang::Location    location,
                                                       ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                    Shared<lang::Value>               value,
                                                    CompileContext&                   context) override;

        bool                isCastingPossibleTo(Type const& other) const override;
        bool                validateCast(Type const&       other,
                                         lang::Location    location,
                                         ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildCast(lang::ResolvingHandle<lang::Type> other,
                                      Shared<lang::Value>               value,
                                      CompileContext&                   context) override;

        bool                        isOperatorDefined(lang::UnaryOperator op) const override;
        ResolvingHandle<lang::Type> getOperatorResultType(lang::UnaryOperator op) override;
        bool                        validateOperator(lang::UnaryOperator op,
                                                     lang::Location      location,
                                                     ValidationLogger&   validation_logger) const override;
        Shared<lang::Value>         buildOperator(lang::UnaryOperator op,
                                                  Shared<lang::Value> value,
                                                  CompileContext&     context) override;

        bool isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const override;
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::BinaryOperator              op,
                                                                lang::ResolvingHandle<lang::Type> other) override;
        bool                              validateOperator(lang::BinaryOperator op,
                                                           lang::Type const&    other,
                                                           lang::Location       left_location,
                                                           lang::Location       right_location,
                                                           ValidationLogger&    validation_logger) const override;
        Shared<lang::Value>               buildOperator(lang::BinaryOperator op,
                                                        Shared<lang::Value>  left,
                                                        Shared<lang::Value>  right,
                                                        CompileContext&      context) override;

        bool                              hasMember(lang::Identifier const& name) const override;
        Member& getMember(lang::Identifier const& name) override;
        bool validateMemberAccess(lang::Identifier const& name, ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildMemberAccess(Shared<lang::Value>     value,
                                              lang::Identifier const& name,
                                              CompileContext&         context) override;

        bool                              definesIndirection() const override;
        lang::ResolvingHandle<lang::Type> getIndirectionType() override;
        bool validateIndirection(lang::Location location, ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildIndirection(Shared<lang::Value> value, CompileContext& context) override;

        void performDefaultInitializer(Shared<lang::Value> ptr,
                                       Shared<lang::Value> count,
                                       CompileContext&     context) override;
        void performCopyInitializer(Shared<lang::Value> destination,
                                    Shared<lang::Value> source,
                                    CompileContext&     context) override;
        void performFinalizer(Shared<lang::Value> ptr, Shared<lang::Value> count, CompileContext& context) override;

        bool isTriviallyDefaultConstructible() const override;
        bool isTriviallyCopyConstructible() const override;
        bool isTriviallyDestructible() const override;

        void createConstructors() override;
        bool acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters) override;
        void buildRequestedOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters,
                                    lang::PredefinedFunction&                      function,
                                    CompileContext&                                context) override;
        void buildNativeDeclaration(CompileContext& context) override;
        void buildNativeDefinition(CompileContext& context) override;

      protected:
        std::string   createMangledName() const override;
        Execution::Type createDebugType(CompileContext& context) const override;

      public:
        std::vector<lang::ResolvingHandle<lang::Type>> getDeclarationDependencies() override;
        std::vector<lang::ResolvingHandle<lang::Type>> getDefinitionDependencies() override;

      private:
        lang::ResolvingHandle<lang::Type> actual_;

        mutable Optional<lang::ResolvingHandle<lang::Type>> actually_actual_ {};
        mutable Optional<bool>                              is_valid_ {};
    };
}

#endif
