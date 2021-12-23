#ifndef ANCE_SRC_ANCE_CONSTRUCT_FUNCTIONGROUP_H_
#define ANCE_SRC_ANCE_CONSTRUCT_FUNCTIONGROUP_H_

#include "ance/utility/ResolvingHandle.h"

#include <string>
#include <vector>

#include "ance/construct/Function.h"
#include "ance/utility/OwningHandle.h"

class ValidationLogger;
class CompileContext;

namespace ance
{
    class FunctionGroup : public HandleTarget<FunctionGroup>
    {
      public:
        explicit FunctionGroup(std::string name);

        [[nodiscard]] bool               isDefined() const;
        [[nodiscard]] const std::string& name() const;

        void resolve();
        void validate(ValidationLogger& validation_logger);
        void createNativeBacking(CompileContext* compile_context);
        void build(CompileContext* compile_context);

        /**
         * Add a function to this group.
         * @param function The function. Must be named like the group.
         */
        void addFunction(ance::OwningHandle<ance::Function> function);

        /**
         * Resolve a function overload.
         * @param arguments The argument types to use for overload resolution.
         * @return A function, when defined.
         */
        std::optional<ance::ResolvingHandle<ance::Function>> resolveOverload(
            const std::vector<ance::ResolvingHandle<ance::Type>>& arguments);

      private:
        std::string                                     name_;
        std::vector<ance::OwningHandle<ance::Function>> functions_;
    };
}

#endif
