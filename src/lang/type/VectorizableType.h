#ifndef ANCE_SRC_LANG_TYPE_VECTORIZABLETYPE_H_
#define ANCE_SRC_LANG_TYPE_VECTORIZABLETYPE_H_

#include "TypeDefinition.h"

namespace lang
{
    class VectorizableType : public virtual TypeDefinition
    {
      public:
        ~VectorizableType() override = default;

        const VectorizableType* isVectorizable() const override;
        VectorizableType*       isVectorizable() override;

        using TypeDefinition::buildOperator;

        virtual std::shared_ptr<Value> buildOperator(lang::BinaryOperator              op,
                                                     std::shared_ptr<Value>            left,
                                                     std::shared_ptr<Value>            right,
                                                     lang::ResolvingHandle<lang::Type> return_type,
                                                     CompileContext&                   context) = 0;
    };
}

#endif
