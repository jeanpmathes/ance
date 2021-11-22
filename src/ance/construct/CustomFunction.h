#ifndef ANCE_SRC_ANCE_CONSTRUCT_CUSTOMFUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CUSTOMFUNCTION_H_

#include "FunctionDefinition.h"

#include <list>
#include <optional>
#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/AccessModifier.h"
#include "ance/utility/ResolvingHandle.h"

namespace ance
{
    class LocalScope;
    class Function;
    class Variable;
}

class Statement;
class CompileContext;

namespace ance
{
    /**
     * A function that is defined in code.
     */
    class CustomFunction : public ance::FunctionDefinition
    {
      public:
        CustomFunction(ance::Function*                               function,
                       AccessModifier                                access,
                       ance::ResolvingHandle<ance::Type>             return_type,
                       ance::Location                                return_type_location,
                       std::vector<std::shared_ptr<ance::Parameter>> parameters,
                       ance::Scope*                                  containing_scope,
                       ance::Location                                declaration_location,
                       ance::Location                                definition_location);

        void pushStatement(Statement* statement) override;
        void addReturn(const std::shared_ptr<ance::Value>& value) override;

        void validate(ValidationLogger& validation_logger) override;

        void                         createNativeBacking(CompileContext* context) override;
        void                         build(CompileContext* context) override;
        std::shared_ptr<ance::Value> buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
                                               CompileContext*                                  context) const override;

        /**
         * Get the debug subprogram.
         * @return The debug subprogram.
         */
        llvm::DISubprogram* debugSubprogram();

        llvm::DIScope*  getDebugScope(CompileContext* context) override;
        ance::LocalScope* getInsideScope() override;

      protected:
        using FunctionDefinition::buildCall;

      private:
        AccessModifier access_;
        ance::Location definition_location_;

        std::unique_ptr<ance::LocalScope> inside_scope_;

        std::vector<std::optional<ance::ResolvingHandle<ance::Variable>>> arguments_;
        std::list<Statement*>                                             statements_;

        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};

        std::shared_ptr<ance::Value> return_value_ {};
        bool                         has_return_ {false};
    };
}

#endif
