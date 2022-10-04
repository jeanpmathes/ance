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
        bool       isAddressType() const override;
        StateCount getStateCount() const override;

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

        bool        acceptOverloadRequest(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters) override;
        void        buildRequestedOverload(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters,
                                           lang::PredefinedFunction&                             function,
                                           CompileContext&                                       context) override;
        static void buildRequestedOverload(lang::ResolvingHandle<lang::Type> parameter_element,
                                           lang::ResolvingHandle<lang::Type> return_type,
                                           lang::PredefinedFunction&         function,
                                           CompileContext&                   context);
    };
}

#endif
