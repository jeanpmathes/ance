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
        llvm::DIType* createDebugType(CompileContext& context) override;

      public:
        ~FloatingPointType() override = default;

        StateCount getStateCount() const override;

        [[nodiscard]] bool isFloatingPointType() const override;
        [[nodiscard]] bool isFloatingPointType(size_t precision) const override;

        bool                         isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other) override;
        bool                         validateImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                lang::Location                    location,
                                                                ValidationLogger&                 validation_logger) const override;
        std::shared_ptr<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                             std::shared_ptr<Value>            value,
                                                             CompileContext&                   context) override;
        std::shared_ptr<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                             lang::ResolvingHandle<lang::Type> other_element,
                                                             std::shared_ptr<Value>            value,
                                                             CompileContext&                   context) override;

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
        std::shared_ptr<Value>            buildOperator(lang::BinaryOperator              op,
                                                        std::shared_ptr<Value>            left,
                                                        std::shared_ptr<Value>            right,
                                                        lang::ResolvingHandle<lang::Type> return_type,
                                                        CompileContext&                   context) override;

        bool acceptOverloadRequest(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters) override;
        void buildRequestedOverload(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters,
                                    lang::PredefinedFunction&                             function,
                                    CompileContext&                                       context) override;
        void buildRequestedOverload(lang::ResolvingHandle<lang::Type> parameter_element,
                                    lang::ResolvingHandle<lang::Type> return_type,
                                    lang::PredefinedFunction&         function,
                                    CompileContext&                   context) override;

      protected:
        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

      private:
        [[nodiscard]] virtual size_t getPrecision() const = 0;
    };
}
#endif