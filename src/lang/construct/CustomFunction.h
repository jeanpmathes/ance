#ifndef ANCE_SRC_ANCE_CONSTRUCT_CUSTOMFUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CUSTOMFUNCTION_H_

#include "FunctionDefinition.h"

#include <list>
#include <optional>
#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/AccessModifier.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/AccessModifier.h"

namespace lang
{
    class LocalScope;
    class Function;
    class Variable;
}

class Statement;
class CompileContext;

namespace lang
{
    /**
     * A function that is defined in code.
     */
    class CustomFunction : public lang::FunctionDefinition
    {
      public:
        CustomFunction(lang::Function*                               function,
                       lang::AccessModifier                          access,
                       lang::ResolvingHandle<lang::Type>             return_type,
                       lang::Location                                return_type_location,
                       std::vector<std::shared_ptr<lang::Parameter>> parameters,
                       lang::Scope*                                  containing_scope,
                       lang::Location                                declaration_location,
                       lang::Location                                definition_location);

        [[nodiscard]] bool isMangled() const override;

        void pushStatement(Statement* statement) override;
        void addReturn(const std::shared_ptr<lang::Value>& value) override;

        void validate(ValidationLogger& validation_logger) override;

        void                         createNativeBacking(CompileContext* context) override;
        void                         build(CompileContext* context) override;
        std::shared_ptr<lang::Value> buildCall(const std::vector<std::shared_ptr<lang::Value>>& arguments,
                                               CompileContext*                                  context) const override;

        /**
         * Get the debug subprogram.
         * @return The debug subprogram.
         */
        llvm::DISubprogram* debugSubprogram();

        llvm::DIScope*    getDebugScope(CompileContext* context) override;
        lang::LocalScope* getInsideScope() override;

      protected:
        using FunctionDefinition::buildCall;

      private:
        lang::AccessModifier access_;
        lang::Location       definition_location_;

        std::unique_ptr<lang::LocalScope> inside_scope_;

        std::vector<std::optional<lang::ResolvingHandle<lang::Variable>>> arguments_;
        std::list<Statement*>                                             statements_;

        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};

        std::shared_ptr<lang::Value> return_value_ {};
        bool                         has_return_ {false};
    };
}

#endif
