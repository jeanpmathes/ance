#ifndef ANCE_SRC_ANCE_CONSTRUCT_SIGNATURE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_SIGNATURE_H_

#include "ance/construct/Parameter.h"
#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"

namespace ance
{
    /**
     * A class for function signatures.
     */
    class Signature
    {
      private:
        explicit Signature(const std::string& name, std::vector<ance::ResolvingHandle<ance::Type>>& types);

      public:
        /**
         * Creates a new signature from given parameters.
         * @param name The name of the function.
         * @param parameters The parameters of the function.
         * @return The signature.
         */
        static Signature fromParameters(const std::string&                                   name,
                                        const std::vector<std::shared_ptr<ance::Parameter>>& parameters);

        /**
         * Get the mangled name. Will create the mangled name if it has not been created yet.
         * @return The mangled name.
         */
        [[nodiscard]] const std::string& getMangledName();

      private:
        std::string                                    function_name_;
        std::vector<ance::ResolvingHandle<ance::Type>> types_;
        std::string                                    mangled_name_ {};
    };
}

#endif
