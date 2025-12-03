#ifndef ANCE_BBT_SIGNATURE_H
#define ANCE_BBT_SIGNATURE_H

#include "ance/utility/Containers.h"
#include "ance/utility/Owners.h"

#include "ance/core/Identifier.h"

namespace ance::bbt
{
    class Type;

    /// The signature of a callable, which is determined by its name and the types of its arguments.
    /// Note that the return type is not part of the signature.
    class Signature
    {
      public:
        struct Parameter
        {
            core::Identifier      name;
            utility::Shared<Type> type;

            Parameter(core::Identifier const& parameter_name, utility::Shared<Type> parameter_type);
        };

        Signature(core::Identifier const& name, utility::List<Parameter> parameters);

        /// Get the name of the signature.
        [[nodiscard]] core::Identifier const& name() const;

        /// Get the arity of the signature, meaning the number of arguments.
        [[nodiscard]] size_t arity() const;

        /// Get a parameter by index.
        [[nodiscard]] Parameter& operator[](size_t index);

        /// Get the parameters of the signature.
        [[nodiscard]] utility::List<Parameter> const& parameters() const;

        template<typename... Args>
        static Signature like(std::string const& name, Args&&... args)
        {
            utility::List<Parameter> parameters;
            (parameters.emplace_back(std::forward<Args>(args)), ...);
            return {core::Identifier::like(name), std::move(parameters)};
        }

        template<typename... Args>
        static Signature like(core::Identifier const& name, Args&&... args)
        {
            utility::List<Parameter> parameters;
            (parameters.emplace_back(std::forward<Args>(args)), ...);
            return {name, std::move(parameters)};
        }

        template<typename... Args>
        static Signature likeUnnamed(std::string const& name, Args&&... args)
        {
            utility::List<Parameter> parameters;
            size_t index = 0;
            (parameters.emplace_back(Parameter {core::Identifier::like("arg" + std::to_string(index++)), std::forward<Args>(args)}), ...);
            return {core::Identifier::like(name), std::move(parameters)};
        }

        template<typename... Args>
        static Signature likeUnnamed(core::Identifier const& name, Args&&... args)
        {
            utility::List<Parameter> parameters;
            size_t index = 0;
            (parameters.emplace_back(Parameter {core::Identifier::like("arg" + std::to_string(index++)), std::forward<Args>(args)}), ...);
            return {name, std::move(parameters)};
        }

      private:
        core::Identifier         name_;
        utility::List<Parameter> parameters_;
    };
}

#endif
