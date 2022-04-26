#ifndef ANCE_SRC_LANG_CONSTRUCT_FUNCTIONGROUP_H_
#define ANCE_SRC_LANG_CONSTRUCT_FUNCTIONGROUP_H_

#include "lang/utility/ResolvingHandle.h"

#include <string>
#include <vector>

#include "lang/construct/Function.h"
#include "lang/utility/OwningHandle.h"

class ValidationLogger;
class CompileContext;

namespace lang
{
    class FunctionGroup
        : public HandleTarget<FunctionGroup>
        , public Element<FunctionGroup, ANCE_CONSTRUCTS>
    {
      public:
        explicit FunctionGroup(std::string name);

        [[nodiscard]] bool               isDefined() const;
        [[nodiscard]] const std::string& name() const;

        void resolve();
        void validate(ValidationLogger& validation_logger);
        void expand();
        void determineFlow();
        void createNativeBacking(CompileContext* compile_context);
        void build(CompileContext* compile_context);

        /**
         * Add a function to this group.
         * @param function The function. Must be named like the group.
         */
        void addFunction(lang::OwningHandle<lang::Function> function);

        /**
         * Validate the resolution for given types.
         * This is only a rough check, and does not guarantee that an unambiguous resolution is possible.
         * @param types The types of the arguments.
         * @param location The source location at which the resolution was requested.
         * @param validation_logger The validation logger.
         * @return True if the resolution is valid.
         */
        bool validateResolution(const std::vector<lang::ResolvingHandle<lang::Type>>& types,
                                lang::Location                                        location,
                                ValidationLogger&                                     validation_logger);

        /**
         * Resolve a function overload.
         * @param arguments The argument types to use for overload resolution.
         * @return All functions that fit the given arguments.
         */
        std::vector<lang::ResolvingHandle<lang::Function>> resolveOverload(
            const std::vector<lang::ResolvingHandle<lang::Type>>& arguments);

        /**
         * Get an undefined function group with the same name.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::FunctionGroup> toUndefined() const;

      private:
        std::string                                     name_;
        std::vector<lang::OwningHandle<lang::Function>> functions_;
    };
}

#endif
