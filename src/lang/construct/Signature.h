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
        explicit Signature(const Identifier& name, std::vector<lang::ResolvingHandle<lang::Type>>& types);

      public:
        [[nodiscard]] size_t getParameterCount() const;

        /**
         * Creates a new signature from given parameters.
         * @param name The name of the function.
         * @param parameters The parameters of the function.
         * @return The signature.
         */
        static Signature fromParameters(Identifier                                           name,
                                        const std::vector<std::shared_ptr<lang::Parameter>>& parameters);

        /**
         * Get whether the signature can be considered same as the given types.
         * @param arguments The argument types.
         * @return Whether the signature can be considered same as the given types.
         */
        [[nodiscard]] bool isSame(const std::vector<lang::ResolvingHandle<lang::Type>>& arguments) const;

        /**
         * Get whether the signature matches the given argument types.
         * @param arguments The argument types.
         * @return Whether the signature matches the given argument types.
         */
        [[nodiscard]] bool isMatching(const std::vector<lang::ResolvingHandle<lang::Type>>& arguments) const;

        /**
         * Get the mangled name. Will create the mangled name if it has not been created yet.
         * @return The mangled name.
         */
        [[nodiscard]] const std::string& getMangledName();

        /**
         * Get a string representation of the signature.
         * The format is shortened in comparison, e.g. no argument names are used.
         * @return The string representation.
         */
        [[nodiscard]] std::string toString() const;

        bool operator==(const Signature& other) const;
        bool operator!=(const Signature& other) const;

        /**
         * Check if two given signatures are the same.
         * @param a The first signature.
         * @param b The second signature.
         * @return True if the signatures are the same, false otherwise.
         */
        static bool areSame(const Signature& a, const Signature& b);

      private:
        lang::Identifier                               function_name_;
        std::vector<lang::ResolvingHandle<lang::Type>> types_;
        std::string                                    mangled_name_ {};
    };
}

#endif

