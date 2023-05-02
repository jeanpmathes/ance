#ifndef ANCE_SRC_LANG_CONSTRUCT_CALLABLE_H_
#define ANCE_SRC_LANG_CONSTRUCT_CALLABLE_H_

#include <vector>

#include "lang/utility/Location.h"
#include "lang/utility/OwningHandle.h"
#include "lang/utility/ResolvingHandle.h"

class ValidationLogger;

namespace lang
{
    class Type;
    class Identifier;
    class Function;

    /**
     * An abstract class that defines some operations required for overload resolution.
     */
    class Callable
    {
      public:
        virtual ~Callable() = default;

        /**
         * Get the name of this callable.
         * @return The name.
         */
        [[nodiscard]] virtual Identifier const& name() const      = 0;
        [[nodiscard]] virtual bool              isDefined() const = 0;

        /**
         * Get the name of this callable with helpful annotations. Useful for validation messages.
         * @param is_safe Whether the callable is currently safe to use. Set to false when endless loops could occur.
         * @return The annotated name.
         */
        [[nodiscard]] virtual std::string getAnnotatedName(bool is_safe) const;

        /**
         * Request a function overload from this callable. The callable can than offer this overload in later phases.
         * The callable must be defined when requesting an overload.
         * @returns True if the overload was accepted. An accepted overload will be available when resolving.
         */
        virtual bool requestOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters) = 0;

        /**
         * Add a function to this group.
         * @param function The function. Must be named like the group.
         */
        void addFunction(lang::OwningHandle<lang::Function> function);

        /**
         * Validate the resolution for given types.
         * This is only a rough check, and does not guarantee that an unambiguous resolution is possible.
         * @param types The types of the arguments.
         * @param validation_logger The validation logger.
         * @return True if the resolution is valid.
         */
        bool validateResolution(std::vector<std::reference_wrapper<lang::Type const>> const& types,
                                lang::Location                                               location,
                                ValidationLogger&                                            validation_logger) const;

        /**
         * Resolve a function overload.
         * @param arguments The argument types to use for overload resolution.
         * @return All functions that fit the given arguments.
         */
        [[nodiscard]] std::vector<lang::ResolvingHandle<lang::Function>> resolveOverload(
            std::vector<std::reference_wrapper<lang::Type const>> const& arguments);

        /**
         * Resolve a function overload.
         * @param arguments The argument types to use for overload resolution.
         * @return All functions that fit the given arguments.
         */
        [[nodiscard]] std::vector<std::reference_wrapper<lang::Function const>> resolveOverload(
            std::vector<std::reference_wrapper<lang::Type const>> const& arguments) const;

      protected:
        std::vector<lang::ResolvingHandle<lang::Function>>&                     functions();
        [[nodiscard]] std::vector<lang::ResolvingHandle<lang::Function>> const& functions() const;

        /**
         * Get whether implicit conversion should be considered for overload resolution.
         * If not, the passed arguments must match the function signature exactly.
         */
        [[nodiscard]] virtual bool enableImplicitConversionOnCall() const;

        virtual lang::Callable&       getFunctionSource();
        virtual lang::Callable const& getFunctionSource() const;

      private:
        std::vector<lang::OwningHandle<lang::Function>>    functions_;
        std::vector<lang::ResolvingHandle<lang::Function>> function_handles_;
    };
}

#endif
