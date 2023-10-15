#ifndef ANCE_SRC_LANG_TYPE_ADDRESSTYPE_H_
#define ANCE_SRC_LANG_TYPE_ADDRESSTYPE_H_

#include "TypeDefinition.h"

namespace lang
{
    /**
     * Abstract base class for types based on pointers.
     */
    class AddressType : public virtual TypeDefinition
    {
      public:
        AddressType const* isAddressType() const final;
        StateCount         getStateCount() const override;

        bool                isCastingPossibleTo(Type const& other) const override;
        bool                validateCast(Type const&       other,
                                         lang::Location    location,
                                         ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildCast(lang::ResolvingHandle<lang::Type> other,
                                      Shared<Value>                     value,
                                      CompileContext&                   context) override;

        bool isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const override;
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::BinaryOperator              op,
                                                                lang::ResolvingHandle<lang::Type> other) override;
        bool                              validateOperator(lang::BinaryOperator op,
                                                           lang::Type const&    other,
                                                           lang::Location       left_location,
                                                           lang::Location       right_location,
                                                           ValidationLogger&    validation_logger) const override;
        Shared<lang::Value>               buildOperator(lang::BinaryOperator op,
                                                        Shared<Value>        left,
                                                        Shared<Value>        right,
                                                        CompileContext&      context) override;

      protected:
        [[nodiscard]] virtual Optional<lang::ResolvingHandle<lang::Type>> getPointeeType()       = 0;
        [[nodiscard]] virtual lang::Type const*                           getPointeeType() const = 0;
    };
}

#endif
