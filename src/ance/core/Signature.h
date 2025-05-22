#ifndef ANCE_CORE_SIGNATURE_H
#define ANCE_CORE_SIGNATURE_H

#include "ance/utility/Containers.h"
#include "ance/core/Identifier.h"

namespace ance::core
{
    class Type;

    /// The signature of a callable, which is determined by its name and the types of its arguments.
    /// Note that the return type is not part of the signature.
    class Signature
    {
    public:
        Signature(Identifier const& name, utility::List<std::reference_wrapper<const Type>> types);

        /// Get the name of the signature.
        [[nodiscard]] Identifier const& name() const;

        /// Get the arity of the signature, meaning the number of arguments.
        [[nodiscard]] size_t arity() const;

        /// Get the parameter types of the signature.
        [[nodiscard]] utility::List<std::reference_wrapper<const Type>> const& types() const;

        template<typename... Args>
        static Signature like(std::string const& name, Args&&... args)
        {
            return { Identifier::like(name), utility::List<std::reference_wrapper<const Type>> { std::forward<Args>(args)... } };
        }

    private:
        Identifier name_;
        utility::List<std::reference_wrapper<const Type>> types_;
    };
}

#endif
