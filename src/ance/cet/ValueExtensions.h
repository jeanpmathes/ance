#ifndef ANCE_CET_VALUEEXTENSIONS_H
#define ANCE_CET_VALUEEXTENSIONS_H

#include "ance/bbt/Value.h"
#include "ance/cet/Scope.h"

namespace ance::cet
{
    class ScopeValue final : public bbt::Value
    {
    public:
        explicit ScopeValue(Scope& scope);

        static utility::Shared<ScopeValue> make(Scope& scope);

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] Scope& value() const;

    private:
        Scope& scope_;
    };

}

#endif
