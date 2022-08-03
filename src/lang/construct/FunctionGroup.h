#ifndef ANCE_SRC_LANG_CONSTRUCT_FUNCTIONGROUP_H_
#define ANCE_SRC_LANG_CONSTRUCT_FUNCTIONGROUP_H_

#include "Callable.h"

#include <string>
#include <vector>

#include "lang/construct/Function.h"
#include "lang/utility/OwningHandle.h"
#include "lang/utility/ResolvingHandle.h"

class ValidationLogger;
class CompileContext;

namespace lang
{
    class FunctionGroup
        : public HandleTarget<FunctionGroup>
        , public Callable
        , public Element<FunctionGroup, ANCE_CONSTRUCTS>
    {
      public:
        explicit FunctionGroup(Identifier name);

        [[nodiscard]] bool              isDefined() const override;
        [[nodiscard]] const Identifier& name() const override;

        void resolve();
        void postResolve();
        void validate(ValidationLogger& validation_logger) const;
        void expand();
        void determineFlow();
        void validateFlow(ValidationLogger& validation_logger) const;
        void createNativeBacking(CompileContext* compile_context);
        void build(CompileContext* compile_context);

        /**
         * Get an undefined function group with the same name.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::FunctionGroup> toUndefined() const;

      protected:
        void onAddFunction(lang::Function& function) override;

      private:
        lang::Identifier name_;
    };
}

#endif
