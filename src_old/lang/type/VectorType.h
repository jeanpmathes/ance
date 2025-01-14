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

        static uint64_t const MAX_VECTOR_TYPE_SIZE = 1ll << 32;

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
        Shared<lang::Value> execImplicitConversion(lang::Type const&   other,
                                                   Shared<lang::Value> value,
                                                    Execution&          exec) const override;

        bool                isCastingPossibleTo(Type const& other) const override;
        bool                validateCast(Type const&       other,
                                         lang::Location    location,
                                         ValidationLogger& validation_logger) const override;
        Shared<lang::Value> execCast(lang::Type const&   other,
                                     Shared<lang::Value> value,
                                      Execution&          exec) const override;

        bool                isOperatorDefined(lang::UnaryOperator op) const override;
        lang::Type const&   getOperatorResultType(lang::UnaryOperator op) const override;
        bool                validateOperator(lang::UnaryOperator op,
                                             lang::Location      location,
                                             ValidationLogger&   validation_logger) const override;
        Shared<lang::Value> execOperator(lang::UnaryOperator op,
                                         Shared<lang::Value> value,
                                          Execution&          exec) const override;

        bool                isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const override;
        lang::Type const&   getOperatorResultType(lang::BinaryOperator op, lang::Type const& other) const override;
        bool                validateOperator(lang::BinaryOperator op,
                                             lang::Type const&    other,
                                             lang::Location       left_location,
                                             lang::Location       right_location,
                                             ValidationLogger&    validation_logger) const override;
        Shared<lang::Value> execOperator(lang::BinaryOperator op,
                                         Shared<lang::Value>  left,
                                          Shared<lang::Value>  right,
                                          Execution&           exec) const override;

        bool acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters) override;
        void execRequestedOverload(std::vector<std::reference_wrapper<lang::Type const>> cc,
                                   lang::PredefinedFunction&                             function,
                                    Execution&                                            exec) const override;

      public:
        ~VectorType() override = default;

      protected:
        std::string             createMangledName() const override;
        void                    registerExecutionType(Execution& exec) const override;
        Execution::IndexingMode getIndexingMode() const override;

      private:
        Optional<lang::ResolvingHandle<lang::Type>> actual_type_ {};

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}

#endif
