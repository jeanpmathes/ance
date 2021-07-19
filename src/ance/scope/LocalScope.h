#ifndef ANCE_SRC_ANCE_SCOPE_LOCALSCOPE_H_
#define ANCE_SRC_ANCE_SCOPE_LOCALSCOPE_H_

#include "Scope.h"

#include "ance/construct/LocalVariable.h"
#include "ance/Assigner.h"

class Expression;

namespace ance
{
    class LocalScope : public Scope
    {
      public:
        explicit LocalScope(ance::Scope* parent);

        ance::GlobalScope* getGlobalScope() override;

        bool validate() override;

        ance::LocalVariable* defineLocalVariable(
            const std::string& identifier,
            ance::Type*        type,
            Assigner           assigner,
            Expression*        expression);

        ance::LocalVariable* defineLocalVariable(
            const std::string& identifier,
            ance::Type*        type,
            Assigner           assigner,
            ance::Value*       value);

        ance::Variable* getVariable(std::string identifier) override;

      private:
        ance::Scope* parent_;

        std::map<std::string, ance::LocalVariable*> local_variables_;
    };
}
#endif
