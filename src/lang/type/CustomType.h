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
        explicit CustomType(bool is_imported);

        bool isCustom() const final;
        bool isImported() const final;

      private:
        bool is_imported_ {false};
    };
}

#endif
