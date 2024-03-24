#ifndef ANCE_SRC_LANG_TYPE_UNITTYPE_H_
#define ANCE_SRC_LANG_TYPE_UNITTYPE_H_

#include "TypeDefinition.h"

namespace lang
{
    /**
     * Represents the unit type. The unit type is a special type representing exactly one value.
     */
    class UnitType : public lang::TypeDefinition
    {
      public:
        UnitType();

        [[nodiscard]] StateCount getStateCount() const override;

        [[nodiscard]] bool isUnitType() const override;

        bool                isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const override;
        lang::Type const&   getOperatorResultType(lang::BinaryOperator op, lang::Type const& other) const override;
        bool                validateOperator(lang::BinaryOperator op,
                                             lang::Type const&    other,
                                             lang::Location       left_location,
                                             lang::Location       right_location,
                                             ValidationLogger&    validation_logger) const override;
        Shared<lang::Value> buildOperator(lang::BinaryOperator op,
                                          Shared<lang::Value>  left,
                                          Shared<lang::Value>  right,
                                          Execution&           exec) const override;

        void performDefaultInitializer(Shared<lang::Value> ptr,
                                       Shared<lang::Value> count,
                                       Execution&          exec) const override;
        void performCopyInitializer(Shared<lang::Value> ptr,
                                    Shared<lang::Value> original,
                                    Execution&          exec) const override;
        void performFinalizer(Shared<lang::Value> ptr,
                              Shared<lang::Value> count, Execution& exec) const override;

      protected:
        std::string createMangledName() const override;
        void        registerExecutionType(Execution& exec) const override;

      public:
        bool isTriviallyDefaultConstructible() const override;
        bool isTriviallyCopyConstructible() const override;
        bool isTriviallyDestructible() const override;

        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}
#endif
