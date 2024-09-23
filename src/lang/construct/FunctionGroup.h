#ifndef ANCE_SRC_LANG_CONSTRUCT_FUNCTIONGROUP_H_
#define ANCE_SRC_LANG_CONSTRUCT_FUNCTIONGROUP_H_

#include "Callable.h"

#include <string>
#include <vector>

#include "lang/construct/Entity.h"

#include "lang/construct/Function.h"
#include "lang/utility/OwningHandle.h"
#include "lang/utility/ResolvingHandle.h"

class ValidationLogger;
class Execution;

namespace lang
{
    class FunctionGroup
        : public HandleTarget<FunctionGroup>
        , public Callable
        , public Entity
    {
      public:
        explicit FunctionGroup(Identifier name);

        [[nodiscard]] bool              isDefined() const override;
        [[nodiscard]] Identifier const& name() const override;

        bool isCMP() const override;

        void setScope(lang::Scope& scope);

        lang::Scope&                     scope() override;
        [[nodiscard]] lang::Scope const& scope() const override;

        bool requestOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters) override;

        void validate(ValidationLogger& validation_logger) const;
        void determineFlow();
        void validateFlow(ValidationLogger& validation_logger) const;

        ResolvingHandle<lang::Entity> getUndefinedClone(Context& new_context) const override;

      private:
        lang::Identifier name_;
        lang::Scope*     scope_ = nullptr;
    };
}

#endif
