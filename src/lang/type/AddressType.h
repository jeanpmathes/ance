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
    };
}

#endif
