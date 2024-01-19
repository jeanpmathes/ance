#ifndef ANCE_SRC_LANG_TYPE_VECTORTYPE_H_
#define ANCE_SRC_LANG_TYPE_VECTORTYPE_H_

#include "SequenceType.h"

#include <llvm/IR/DerivedTypes.h>

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/utility/TypeRegistry.h"

namespace lang
{
    class Scope;
}

class Application;

namespace lang
{
    /**
     * Represents a vector type.
     */
    class VectorType : public lang::SequenceType
    {
      public:
        VectorType(lang::ResolvingHandle<lang::Type> element_type, uint64_t size);

        static const uint64_t MAX_VECTOR_TYPE_SIZE = 1ll << 32;

        VectorType const* isVectorType() const override;
        VectorType*       isVectorType() override;

        bool isSigned() const override;

        lang::ResolvingHandle<lang::Type> getActualType() override;
        [[nodiscard]] lang::Type const&   getActualType() const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

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

        bool                              isOperatorDefined(lang::UnaryOperator op) const override;
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::UnaryOperator op) override;
        bool                              validateOperator(lang::UnaryOperator op,
                                                           lang::Location      location,
                                                           ValidationLogger&   validation_logger) const override;
        Shared<lang::Value>               buildOperator(lang::UnaryOperator op,
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

        bool acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters) override;
        void buildRequestedOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters,
                                    lang::PredefinedFunction&                      function,
                                    CompileContext&                                context) override;

      public:
        ~VectorType() override = default;

      protected:
        std::string   createMangledName() const override;
        Execution::Type         createExecutionType(CompileContext& context) const override;
        Execution::IndexingMode getIndexingMode() const override;

      private:
        Optional<lang::ResolvingHandle<lang::Type>> actual_type_ {};

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}

#endif
