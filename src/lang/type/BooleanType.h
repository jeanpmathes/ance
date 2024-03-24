#ifndef ANCE_SRC_LANG_TYPE_BOOLEANTYPE_H_
#define ANCE_SRC_LANG_TYPE_BOOLEANTYPE_H_

#include "TypeDefinition.h"

#include "lang/type/VectorizableType.h"

namespace lang
{
    /**
     * The boolean type.
     */
    class BooleanType : public lang::VectorizableType
    {
      public:
        BooleanType();
        ~BooleanType() override = default;

        [[nodiscard]] StateCount getStateCount() const override;
        [[nodiscard]] bool       isBooleanType() const override;

        using TypeDefinition::buildOperator;

        bool                isOperatorDefined(lang::UnaryOperator op) const override;
        lang::Type const&   getOperatorResultType(lang::UnaryOperator op) const override;
        bool                validateOperator(lang::UnaryOperator op,
                                             lang::Location      location,
                                             ValidationLogger&   validation_logger) const override;
        Shared<lang::Value> buildOperator(lang::UnaryOperator op,
                                          Shared<lang::Value> value,
                                          Execution&          exec) const override;

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

        bool acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters) override;
        void buildRequestedOverload(std::vector<std::reference_wrapper<lang::Type const>> parameters,
                                    lang::PredefinedFunction&                             function,
                                    Execution&                                            exec) const override;
        void buildRequestedOverload(lang::Type const&         cc,
                                    lang::Type const&         return_type,
                                    lang::PredefinedFunction& function,
                                    Execution&                exec) const override;

      protected:
        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        std::string createMangledName() const override;
        void        registerExecutionType(Execution& exec) const override;

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}

#endif
