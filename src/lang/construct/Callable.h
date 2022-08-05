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
        [[nodiscard]] virtual const Identifier& name() const = 0;

        [[nodiscard]] virtual bool isDefined() const = 0;

        /**
         * Request a function overload from this callable. The callable can than offer this overload in later phases.
         * The callable must be defined when requesting an overload.
         */
        virtual void requestOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters) = 0;

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
        bool validateResolution(const std::vector<lang::ResolvingHandle<lang::Type>>& types,
                                lang::Location                                        location,
                                ValidationLogger&                                     validation_logger) const;

        /**
         * Resolve a function overload.
         * @param arguments The argument types to use for overload resolution.
         * @return All functions that fit the given arguments.
         */
        [[nodiscard]] std::vector<lang::ResolvingHandle<lang::Function>> resolveOverload(
            const std::vector<lang::ResolvingHandle<lang::Type>>& arguments) const;

      protected:
        virtual void                                                            onAddFunction(lang::Function& function);
        std::vector<lang::ResolvingHandle<lang::Function>>&                     functions();
        [[nodiscard]] const std::vector<lang::ResolvingHandle<lang::Function>>& functions() const;

        /**
         * Get whether implicit conversion should be considered for overload resolution.
         * If not, the passed arguments must match the function signature exactly.
         */
        virtual bool enableImplicitConversionOnCall() const;

      private:
        std::vector<lang::OwningHandle<lang::Function>>    functions_;
        std::vector<lang::ResolvingHandle<lang::Function>> function_handles_;
    };
}

#endif
