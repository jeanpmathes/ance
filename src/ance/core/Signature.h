#ifndef ANCE_CORE_SIGNATURE_H
#define ANCE_CORE_SIGNATURE_H

#include "ance/core/Identifier.h"

namespace ance::core
{
    /// The signature of a callable.
    class Signature
    {
    public:
        Signature(Identifier const& name, size_t arity);

        [[nodiscard]] Identifier const& name() const;
        [[nodiscard]] size_t arity() const;

        static Signature like(std::string const& name, size_t arity = 0);

    private:
        Identifier name_;
        size_t     arity_;
    };
}

#endif
