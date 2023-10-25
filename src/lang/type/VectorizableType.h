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

        VectorizableType const* isVectorizable() const override;
        VectorizableType*       isVectorizable() override;

        using TypeDefinition::buildOperator;

        /**
         * Build an operation with values of this type or vectors of values of this type.
         */
        virtual Shared<Value> buildOperator(lang::BinaryOperator              op,
                                            Shared<Value>                     left,
                                            Shared<Value>                     right,
                                            lang::ResolvingHandle<lang::Type> return_type,
                                            CompileContext&                   context);

        /**
         * Build an operation with values of this type or vectors of values of this type.
         */
        virtual Shared<Value> buildOperator(lang::UnaryOperator               op,
                                            Shared<Value>                     value,
                                            lang::ResolvingHandle<lang::Type> return_type,
                                            CompileContext&                   context);

        using TypeDefinition::buildCast;

        /**
         * Build a cast from a value of this type or a vector of values of this type to another type.
         * @param other The type to cast to.
         * @param value The value to cast.
         * @param element_type The element type of the type to cast to, or the type itself.
         * @param context The current compilation context.
         * @return The cast value.
         */
        virtual Shared<Value> buildCast(lang::ResolvingHandle<lang::Type> other,
                                        Shared<Value>                     value,
                                        lang::ResolvingHandle<lang::Type> element_type,
                                        CompileContext&                   context);

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
                                            CompileContext&                   context);
    };
}

#endif
