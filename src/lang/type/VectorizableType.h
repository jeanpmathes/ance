#ifndef ANCE_SRC_LANG_TYPE_VECTORIZABLETYPE_H_
#define ANCE_SRC_LANG_TYPE_VECTORIZABLETYPE_H_

#include "TypeDefinition.h"

namespace lang
{
    /**
     * Represents a type that can be natively vectorized.
     * This means that native operations on values and vectors of values are the same.
     */
    class VectorizableType : public virtual TypeDefinition
    {
      public:
        ~VectorizableType() override = default;

        const VectorizableType* isVectorizable() const override;
        VectorizableType*       isVectorizable() override;

        using TypeDefinition::buildOperator;

        /**
         * Build an operation with values of this type or vectors of values of this type.
         */
        virtual std::shared_ptr<Value> buildOperator(lang::BinaryOperator              op,
                                                     std::shared_ptr<Value>            left,
                                                     std::shared_ptr<Value>            right,
                                                     lang::ResolvingHandle<lang::Type> return_type,
                                                     CompileContext&                   context) = 0;

        using TypeDefinition::buildImplicitConversion;

        /**
         * Build an implicit conversion for a value of this type or a vector of values of this type.
         * @param other The type to convert to. Can be a vector type.
         * @param other_element The element type of the type to convert to. Is the same as other if other is not a vector.
         * @param value The value to convert.
         * @param context The current compilation context.
         * @return The converted value.
         */
        virtual std::shared_ptr<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                     lang::ResolvingHandle<lang::Type> other_element,
                                                                     std::shared_ptr<Value>            value,
                                                                     CompileContext&                   context) = 0;

        using TypeDefinition::buildRequestedOverload;

        /**
         * Build a requested overload for a value of this type or a vector of values of this type.
         * @param parameter_element The element type of the parameter type of the overload.
         * @param return_type The return type.
         * @param function The function to build.
         * @param context The current compilation context.
         */
        virtual void buildRequestedOverload(lang::ResolvingHandle<lang::Type> parameter_element,
                                            lang::ResolvingHandle<lang::Type> return_type,
                                            lang::PredefinedFunction&         function,
                                            CompileContext&                   context) = 0;
    };
}

#endif