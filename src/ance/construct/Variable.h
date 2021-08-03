#ifndef ANCE_SRC_ANCE_CONSTRUCT_VARIABLE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VARIABLE_H_

#include <string>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

class CompileContext;

namespace llvm
{
    class DIBuilder;

    class LLVMContext;
}

namespace ance
{
    class Scope;

    class Type;

    class Value;

    class Variable
    {
      protected:
        Variable(ance::Scope* containing_scope, std::string identifier, ance::Type* type, bool is_final);

        explicit Variable(std::string identifier);

        void define(ance::Scope* containing_scope, ance::Type* type, bool is_final);

        bool isDefined();

      public:
        [[nodiscard]] std::string identifier() const;
        [[nodiscard]] ance::Scope* scope() const;
        [[nodiscard]] ance::Type* type() const;
        [[nodiscard]] bool isFinal() const;

        virtual ance::Value* getValue(CompileContext* context) = 0;

        virtual void setValue(ance::Value* value, CompileContext* context) = 0;

      private:
        std::string identifier_;
        bool        is_defined_;

        ance::Scope* scope_;
        ance::Type*  type_;
        bool         is_final_;
    };
}
#endif