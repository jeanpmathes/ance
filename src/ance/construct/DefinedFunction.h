#ifndef ANCE_SRC_ANCE_CONSTRUCT_DEFINEDFUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_DEFINEDFUNCTION_H_

#include "Function.h"

#include <list>
#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/construct/Parameter.h"

#include "compiler/CompileContext.h"
#include "ance/expression/Expression.h"
#include "ance/statement/Statement.h"
#include "ance/AccessModifier.h"

class CompileContext;

namespace ance
{
    class DefinedFunction : public ance::Function
    {
      public:
        DefinedFunction(
            AccessModifier                access,
            std::string                   function_name,
            ance::Type*                   return_type,
            std::vector<ance::Parameter*> parameters,
            ance::Scope*                  scope,
            unsigned int                  line,
            unsigned int                  column);

        [[nodiscard]] ance::LocalScope* getScope() const;

        void pushStatement(Statement* statement);

        void buildName(CompileContext* context) override;

        void build(CompileContext* context) override;

        void addReturn(ance::Value* value = nullptr);

        ance::Value* buildCall(const std::vector<ance::Value*>& arguments, CompileContext* context) const override;

      protected:
        using Function::buildCall;

      private:
        AccessModifier access_;

        std::vector<ance::Parameter*> parameters_;
        ance::LocalScope*             local_scope_;

        std::vector<ance::LocalVariable*> arguments_;
        std::list<Statement*>             statements_;

        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};

        ance::Value* return_value_ {nullptr};
        bool         has_return_ {false};
    };
}

#endif
