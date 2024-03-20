#ifndef ANCE_SRC_LANG_CONSTRUCT_PARAMETER_H_
#define ANCE_SRC_LANG_CONSTRUCT_PARAMETER_H_

#include <string>

#include "lang/utility/Location.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Type;
    class Value;
}

class Storage;

namespace lang
{
    /**
     * A function parameter.
     */
    class Parameter
    {
      public:
        /**
         * Create a new parameter.
         * @param type The type of the parameter.
         * @param type_location The location of the type.
         * @param name The name of the parameter.
         * @param location The source location.
         */
        Parameter(lang::ResolvingHandle<lang::Type> type,
                  lang::Location                    type_location,
                  Identifier                        name,
                  lang::Location                    location);

        /**
         * Create a new parameter for usage in internal functions.
         * This constructor requires less information but also does not allow all operations.
         * @param type The type of the parameter.
         */
        explicit Parameter(lang::ResolvingHandle<lang::Type> type);

        /**
         * Create a new parameter for usage in internal functions.
         * This constructor requires less information but also does not allow all operations.
         * @param type The type of the parameter.
         */
        explicit Parameter(lang::Type const& type);

        [[nodiscard]] lang::ResolvingHandle<lang::Type> type();
        [[nodiscard]] lang::Type const&                 type() const;

        /**
         * Get the parameter name.
         * @return The name.
         */
        [[nodiscard]] Identifier const& name() const;

        /**
         * Get the source location.
         * @return The source location.
         */
        [[nodiscard]] lang::Location location() const;

        /**
         * Get the type location.
         * @return The type location.
         */
        [[nodiscard]] lang::Location typeLocation() const;

        /**
         * Set the argument variable corresponding to this parameter.
         * @param variable The variable.
         */
        void argument(lang::ResolvingHandle<lang::Variable> variable);

        lang::ResolvingHandle<lang::Variable> argument();
        [[nodiscard]] lang::Variable const&   argument() const;

        Shared<lang::Parameter> expand(lang::Context& new_context) const;

        /**
         * Perform storage synchronization.
         */
        static void synchronize(lang::Parameter* parameter, Storage& storage);

      private:
        lang::Type const*                           type_;
        Optional<lang::ResolvingHandle<lang::Type>> type_opt_;

        lang::Location   type_location_;
        lang::Identifier name_;

        Optional<lang::ResolvingHandle<lang::Variable>> argument_;

        lang::Location location_;
    };
}
#endif
