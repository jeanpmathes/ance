#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_LITERALCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_LITERALCONSTANT_H_

#include "lang/construct/Constant.h"

#include "lang/utility/ResolvingHandle.h"
#include "validation/ValidationLogger.h"

namespace lang
{
    /**
     * A constant that represents a literal value.
     * It is not embedded in an execution context.
     */
    class LiteralConstant : public Constant
    {
      public:
        explicit LiteralConstant(lang::ResolvingHandle<lang::Type> type);
        ~LiteralConstant() override = default;

        lang::ResolvingHandle<lang::Type> type();
        [[nodiscard]] lang::Type const&   type() const override;

        /**
         * Get a string representation of the constant.
         * The string representation is only guaranteed to exist if no backing expression is used.
         * @return The string representation.
         */
        [[nodiscard]] virtual std::string toString() const = 0;

        /**
         * Validate the constant value.
         * @param location The location of the constant.
         * @param validation_logger The logger to log the validation result.
         * @return True if the constant value is valid.
         */
        virtual bool validate(ValidationLogger& validation_logger, lang::Location location) const;

        /**
         * Check if this constant equals another constant. Only valid constants can be compared.
         * @param other The other constant.
         * @return True if the constants are equal.
         */
        virtual bool equals(lang::Constant const* other) const = 0;

        /**
         * Clone this constant.
         * @return The cloned constant.
         */
        [[nodiscard]] virtual Shared<lang::LiteralConstant> clone(lang::Context& new_context) const = 0;

        /**
         * Embed the constant in an execution context.
         * @param exec The context to embed the constant in.
         * @return The embedded constant.
         */
        virtual Shared<lang::Constant> embed(Execution& exec) const = 0;

      private:
        lang::ResolvingHandle<lang::Type> type_;
    };
}

#endif
