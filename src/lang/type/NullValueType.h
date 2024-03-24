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
        Shared<lang::Value> buildImplicitConversion(lang::Type const&   other,
                                                    Shared<lang::Value> value,
                                                    Execution&          exec) const override;

      protected:
        std::string createMangledName() const override;
        void        registerExecutionType(Execution& exec) const override;

        Optional<lang::ResolvingHandle<lang::Type>> getPointeeType() override;
        Type const*                                 getPointeeType() const override;

      public:
        bool isTriviallyDefaultConstructible() const override;
        bool isTriviallyCopyConstructible() const override;
        bool isTriviallyDestructible() const override;

        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;
    };
}

#endif
