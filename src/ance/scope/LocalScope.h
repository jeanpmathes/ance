#ifndef ANCE_SRC_ANCE_SCOPE_LOCALSCOPE_H_
#define ANCE_SRC_ANCE_SCOPE_LOCALSCOPE_H_

#include "Scope.h"

#include "ance/Assigner.h"
#include "ance/construct/LocalVariable.h"

class Expression;

namespace ance
{
    class LocalScope : public Scope
    {
      public:
        explicit LocalScope(ance::Scope* parent);

        ance::GlobalScope* getGlobalScope() override;
        llvm::DIScope*     getDebugScope(CompileContext* context) override;

        bool validate() override;

      public:
        ance::Variable* getVariable(std::string identifier) override;

        bool        isTypeRegistered(const std::string& type_name) override;
        ance::Type* getType(const std::string& type_name) override;
        void        registerType(ance::Type* type) override;

        ance::LocalVariable* defineAutoVariable(const std::string& identifier,
                                                ance::Type*        type,
                                                Assigner           assigner,
                                                ance::Value*       value,
                                                unsigned           line);

        ance::LocalVariable* defineParameterVariable(const std::string& identifier,
                                                     ance::Type*        type,
                                                     Assigner           assigner,
                                                     ance::Value*       value,
                                                     unsigned           line);

      private:
        ance::LocalVariable* defineLocalVariable(const std::string& identifier,
                                                 ance::Type*        type,
                                                 Assigner           assigner,
                                                 ance::Value*       value,
                                                 unsigned           line,
                                                 bool               is_parameter);

      private:
        ance::Scope* parent_;

        std::map<std::string, ance::LocalVariable*> local_variables_;
    };
}
#endif
