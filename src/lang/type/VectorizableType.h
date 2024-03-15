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

        using TypeDefinition::buildRequestedOverload;

        /**
         * Build a requested overload for a value of this type or a vector of values of this type.
         * @param parameter_element The element type of the parameter type of the overload.
         * @param return_type The return type.
         * @param function The function to build.
         * @param context The current compilation context.
         */
        virtual void buildRequestedOverload(lang::Type const& parameter_element,
                                            lang::Type const& return_type,
                                            lang::PredefinedFunction&         function,
                                            CompileContext&                   context) const;
    };
}

#endif
