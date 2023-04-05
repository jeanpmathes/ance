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
    {
      public:
        explicit FunctionGroup(Identifier name);

        [[nodiscard]] bool              isDefined() const override;
        [[nodiscard]] Identifier const& name() const override;

        [[nodiscard]] std::vector<std::string> getExportSymbols() const;

        bool requestOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters) override;

        void resolve();
        void postResolve();
        void validate(ValidationLogger& validation_logger) const;
        void determineFlow();
        void validateFlow(ValidationLogger& validation_logger) const;
        void createNativeBacking(CompileContext& compile_context);
        void build(CompileContext& compile_context);

        /**
         * Get an undefined function group with the same name.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::FunctionGroup> toUndefined() const;

      private:
        lang::Identifier name_;
    };
}

#endif
