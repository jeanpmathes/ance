#ifndef ANCE_SRC_LANG_TYPE_FLOATINGPOINTTYPE_H_
#define ANCE_SRC_LANG_TYPE_FLOATINGPOINTTYPE_H_

#include "VectorizableType.h"

namespace lang
{
    /**
     * The base class of all floating point types.
     */
    class FloatingPointType : virtual public lang::VectorizableType
    {
      protected:
        std::string   createMangledName() const override;
        Execution::Type createExecutionType(CompileContext& context) const override;

      public:
        ~FloatingPointType() override = default;

        StateCount getStateCount() const override;

        [[nodiscard]] FloatingPointType const* isFloatingPointType() const override;
        [[nodiscard]] bool                     isFloatingPointType(size_t precision) const override;

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

        [[nodiscard]] virtual size_t getPrecision() const = 0;

      protected:
        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;
    };
}
#endif
