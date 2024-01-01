#ifndef ANCE_SRC_LANG_CONSTRUCT_PARAMETER_H_
#define ANCE_SRC_LANG_CONSTRUCT_PARAMETER_H_

#include <string>

#include "lang/construct/value/Value.h"
#include "lang/utility/Location.h"

namespace lang
{
    class Type;
}

class Storage;

namespace lang
{
    /**
     * A function parameter value.
     */
    class Parameter : public lang::Value
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
         * This constructor requires less information.
         * @param type The type of the parameter.
         */
        explicit Parameter(lang::ResolvingHandle<lang::Type> type);

        [[nodiscard]] lang::ResolvingHandle<lang::Type> type() override;
        [[nodiscard]] lang::Type const&                 type() const override;

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
         * Wrap an llvm argument as content value.
         * @param argument The native argument of this parameter.
         */
        void wrap(llvm::Argument* argument);

        Shared<lang::Parameter> expand(lang::Context& new_context) const;

        void buildContentValue(CompileContext& context) override;

        /**
         * Perform storage synchronization.
         */
        static void synchronize(lang::Parameter* parameter, Storage& storage);

      private:
        lang::ResolvingHandle<lang::Type> type_;
        lang::Location                    type_location_;
        lang::Identifier                  name_;

        lang::Location location_;

        llvm::Argument* argument_ = nullptr;
    };
}
#endif
