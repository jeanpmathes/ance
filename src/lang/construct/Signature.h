#ifndef ANCE_SRC_LANG_CONSTRUCT_SIGNATURE_H_
#define ANCE_SRC_LANG_CONSTRUCT_SIGNATURE_H_

#include "lang/construct/Parameter.h"
#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    /**
     * A class for function signatures.
     */
    class Signature
    {
      private:
        explicit Signature(Identifier const& name, std::vector<Shared<lang::Parameter>> parameters);

      public:
        [[nodiscard]] size_t getParameterCount() const;

        /**
         * Creates a new signature from given parameters.
         * @param name The name of the function.
         * @param parameters The parameters of the function.
         * @return The signature.
         */
        static Signature fromParameters(Identifier name, std::vector<Shared<lang::Parameter>> parameters);

        /**
         * Get whether the signature can be considered same as the given types.
         * @param arguments The argument types.
         * @return Whether the signature can be considered same as the given types.
         */
        [[nodiscard]] bool isSame(std::vector<std::reference_wrapper<lang::Type const>> const& arguments) const;

        /**
         * Get whether the signature matches the given argument types.
         * @param arguments The argument types.
         * @return Whether the signature matches the given argument types.
         */
        [[nodiscard]] bool isMatching(std::vector<std::reference_wrapper<lang::Type const>> const& arguments) const;

        /**
         * Get the mangled name. Will create the mangled name if it has not been created yet.
         * @return The mangled name.
         */
        [[nodiscard]] std::string const& getMangledName() const;

        /**
         * Get a string representation of the signature.
         * The format is shortened in comparison, e.g. no argument names are used.
         * @return The string representation.
         */
        [[nodiscard]] std::string toString() const;

        bool operator==(Signature const& other) const;
        bool operator!=(Signature const& other) const;

        /**
         * Check if two given signatures are the same.
         * @param a The first signature.
         * @param b The second signature.
         * @return True if the signatures are the same, false otherwise.
         */
        static bool areSame(Signature const& a, Signature const& b);

      private:
        lang::Identifier                     function_name_;
        std::vector<Shared<lang::Parameter>> parameters_;

        mutable std::string mangled_name_ {};
    };
}

#endif
