#ifndef ANCE_SRC_ANCE_SCOPE_SCOPE_H_
#define ANCE_SRC_ANCE_SCOPE_SCOPE_H_

#include <map>
#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/AccessModifier.h"
#include "ance/construct/GlobalVariable.h"
#include "ance/type/Type.h"

class Statement;

class CompileContext;

namespace ance
{
    class Constant;

    class Function;

    class Value;

    class GlobalScope;

    class Scope
    {
      public:
        virtual ance::GlobalScope* getGlobalScope() = 0;
        virtual llvm::DIScope* getDebugScope(CompileContext* context) = 0;

        virtual bool validate() = 0;

        virtual ance::Variable* getVariable(std::string identifier) = 0;

        virtual bool        isTypeRegistered(const std::string& type_name) = 0;
        virtual ance::Type* getType(const std::string& type_name)          = 0;
        virtual void        registerType(ance::Type* type)                 = 0;

        virtual ~Scope() = default;
    };
}
#endif