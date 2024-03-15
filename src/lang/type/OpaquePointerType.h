#ifndef ANCE_SRC_LANG_TYPE_OPAQUEPOINTERTYPE_H_
#define ANCE_SRC_LANG_TYPE_OPAQUEPOINTERTYPE_H_

#include "AddressType.h"

namespace lang
{
    /**
     * Represents special pointer types that have no element type and are limited in the operations they can perform.
     */
    class OpaquePointerType : public lang::AddressType
    {
      public:
        OpaquePointerType();
        ~OpaquePointerType() override = default;

        bool isOpaquePointerType() const override;

      protected:
        std::string   createMangledName() const override;
        void          registerExecutionType(CompileContext& context) const override;

        Optional<lang::ResolvingHandle<lang::Type>> getPointeeType() override;
        Type const*                                 getPointeeType() const override;

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}

#endif
