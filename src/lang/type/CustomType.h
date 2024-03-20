#ifndef ANCE_SRC_LANG_TYPE_CUSTOMTYPE_H_
#define ANCE_SRC_LANG_TYPE_CUSTOMTYPE_H_

#include "TypeDefinition.h"

#include "lang/Accessibility.h"

namespace lang
{
    /**
     * A base class for types that can be defined using code, e.g. structs.
     */
    class CustomType : public virtual lang::TypeDefinition
    {
      public:
        explicit CustomType(lang::Accessibility accessibility);

        bool                       isCustom() const final;
        bool                       isImported() const final;
        lang::Accessibility const& getAccessibility() const final;

      private:
        lang::Accessibility accessibility_;
    };
}

#endif
