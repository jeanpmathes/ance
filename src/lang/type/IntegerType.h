#ifndef ANCE_SRC_LANG_TYPE_INTEGERTYPE_H_
#define ANCE_SRC_LANG_TYPE_INTEGERTYPE_H_

#include "TypeDefinition.h"
#include "VectorizableType.h"

namespace lang
{
    /**
     * An abstract class for all integer types.
     */
    class IntegerType
        : public virtual lang::TypeDefinition
        , public virtual lang::VectorizableType
    {
      public:
        [[nodiscard]] StateCount getStateCount() const override;

        IntegerType const* isIntegerType() const override;

        /**
         * Get the bit size of the integer type, if a fixed size is defined.
         * @return The size or none.
         */
        virtual Optional<size_t> getBitSize() const = 0;

        /**
         * Get the size of the integer in bits as it is represented on the machine.
         * @return The native size of the integer.
         */
        virtual size_t getNativeBitSize() const = 0;

        /**
         * Get the minimum bit size of the type. No matter the target, the type will always be at least this big.
         * @return The minimum bit size.
         */
        virtual size_t getMinimumBitSize() const = 0;

        /**
         * Get the suffix used in literals.
         * @return The suffix.
         */
        virtual std::string getSuffix() const = 0;

      protected:
        bool                isImplicitlyConvertibleTo(lang::Type const& other) const override;
        bool                validateImplicitConversion(lang::Type const& other,
                                                       lang::Location    location,
                                                       ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildImplicitConversion(lang::Type const& other,
                                                    Shared<lang::Value>               value,
                                                    CompileContext&                   context) const override;

      public:
        bool                isCastingPossibleTo(Type const& other) const override;
        bool                validateCast(Type const&       other,
                                         lang::Location    location,
                                         ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildCast(lang::Type const& other,
                                      Shared<lang::Value>               value,
                                      CompileContext&                   context) const override;

      protected:
        bool acceptOverloadRequest(std::vector<lang::ResolvingHandle<lang::Type>> parameters) override;
        void buildRequestedOverload(std::vector<std::reference_wrapper<lang::Type const>> parameters,
                                    lang::PredefinedFunction&                      function,
                                    CompileContext&                                context) const override;
        void buildRequestedOverload(lang::Type const& parameter_element,
                                    lang::Type const& return_type,
                                    lang::PredefinedFunction&         function,
                                    CompileContext&                   context) const override;

        using TypeDefinition::buildOperator;

        bool                              isOperatorDefined(lang::UnaryOperator op) const override;
        lang::Type const& getOperatorResultType(lang::UnaryOperator op) const override;
        bool                              validateOperator(lang::UnaryOperator op,
                                                           lang::Location      location,
                                                           ValidationLogger&   validation_logger) const override;
        Shared<lang::Value>               buildOperator(lang::UnaryOperator op,
                                                        Shared<lang::Value> value,
                                                        CompileContext&     context) const override;

        bool isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const override;
        lang::Type const& getOperatorResultType(lang::BinaryOperator              op,
                                                                lang::Type const& other) const override;
        bool                              validateOperator(lang::BinaryOperator op,
                                                           lang::Type const&    other,
                                                           lang::Location       left_location,
                                                           lang::Location       right_location,
                                                           ValidationLogger&    validation_logger) const override;
        Shared<lang::Value>               buildOperator(lang::BinaryOperator op,
                                                        Shared<lang::Value>  left,
                                                        Shared<lang::Value>  right,
                                                        CompileContext&      context) const override;

        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        void registerExecutionType(CompileContext& context) const override;
    };
}

#endif
