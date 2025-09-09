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
        struct Parameter
        {
            Identifier name;
            std::reference_wrapper<Type const> type;

            Parameter(Identifier const& parameter_name, std::reference_wrapper<Type const> parameter_type);
        };

        Signature(Identifier const& name, utility::List<Parameter> parameters);

        /// Get the name of the signature.
        [[nodiscard]] Identifier const& name() const;

        /// Get the arity of the signature, meaning the number of arguments.
        [[nodiscard]] size_t arity() const;

        /// Get the parameters of the signature.
        [[nodiscard]] utility::List<Parameter> const& parameters() const;

        template<typename... Args>
        static Signature like(std::string const& name, Args&&... args)
        {
            return { Identifier::like(name), utility::List<Parameter> { std::forward<Args>(args)... } };
        }

        template<typename... Args>
        static Signature likeUnnamed(std::string const& name, Args&&... args)
        {
            return { Identifier::like(name), utility::List<Parameter> { Parameter { Identifier::like("arg" + std::to_string(sizeof...(args))), std::forward<Args>(args) }... } };
        }

    private:
        Identifier name_;
        utility::List<Parameter> parameters_;
    };
}

#endif
