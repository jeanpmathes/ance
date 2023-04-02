#ifndef ANCE_SRC_LANG_TYPE_CUSTOMTYPE_H_
#define ANCE_SRC_LANG_TYPE_CUSTOMTYPE_H_

#include "TypeDefinition.h"

namespace lang
{
    /**
     * A base class for types that can be defined using code, e.g. structs.
     */
    class CustomType : public virtual lang::TypeDefinition
    {
      public:
        bool isCustom() const final;
    };
}

#endif
