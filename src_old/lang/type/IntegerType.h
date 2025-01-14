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
        Shared<lang::Value> execImplicitConversion(lang::Type const&   other,
                                                   Shared<lang::Value> value,
                                                    Execution&          exec) const override;

      public:
        bool                isCastingPossibleTo(Type const& other) const override;
        bool                validateCast(Type const&       other,
                                         lang::Location    location,
                                         ValidationLogger& validation_logger) const override;
        Shared<lang::Value> execCast(lang::Type const&   other,
                                     Shared<lang::Value> value,
                                      Execution&          exec) const override;

      protected:
        bool acceptOverloadRequest(std::vector<lang::ResolvingHandle<lang::Type>> parameters) override;
        void execRequestedOverload(std::vector<std::reference_wrapper<lang::Type const>> parameters,
                                   lang::PredefinedFunction&                             function,
                                    Execution&                                            exec) const override;
        void execRequestedOverload(lang::Type const&         cc,
                                   lang::Type const&         return_type,
                                    lang::PredefinedFunction& function,
                                    Execution&                exec) const override;

        using TypeDefinition::execOperator;

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

        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        void registerExecutionType(Execution& exec) const override;
    };
}

#endif
