#ifndef ANCE_SRC_LANG_TYPE_NULLVALUETYPE_H_
#define ANCE_SRC_LANG_TYPE_NULLVALUETYPE_H_

#include "AddressType.h"

namespace lang
{
    /**
     * The type of the null value/pointer literal. Can be implicitly converted to any address type.
     */
    class NullValueType : public lang::AddressType
    {
      public:
        NullValueType();
        ~NullValueType() override = default;

        bool       isNullValueType() const override;
        StateCount getStateCount() const override;

        bool                isImplicitlyConvertibleTo(lang::Type const& other) const override;
        bool                validateImplicitConversion(lang::Type const& other,
                                                       lang::Location    location,
                                                       ValidationLogger& validation_logger) const override;
        Shared<lang::Value> buildImplicitConversion(lang::Type const& other,
                                                    Shared<lang::Value>               value,
                                                    CompileContext&                   context) const override;

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
