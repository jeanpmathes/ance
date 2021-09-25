#ifndef ANCE_SRC_ANCE_CONSTRUCT_DEFINEDFUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_DEFINEDFUNCTION_H_

#include "Function.h"
#include "ance/scope/Scope.h"

#include <list>
#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/AccessModifier.h"

namespace ance
{
    class LocalVariable;
}

class Statement;
class CompileContext;

namespace ance
{
    /**
     * A function that is defined in code.
     */
    class DefinedFunction
        : public virtual ance::Function
        , public virtual ance::Scope
    {
      public:
        /**
         * Create a new defined function.
         * @param access The access level.
         * @param function_name The name of the function.
         * @param return_type The return type of the function.
         * @param parameters The parameters for this function.
         * @param scope The scope containing the function.
         * @param declaration_location The location of the function declaration.
         * @param definition_location The location of the function definition, meaning its code.
         */
        DefinedFunction(AccessModifier                access,
                        const std::string&            function_name,
                        ance::Type*                   return_type,
                        std::vector<ance::Parameter*> parameters,
                        ance::Scope*                  scope,
                        ance::Location                declaration_location,
                        ance::Location                definition_location);

        [[nodiscard]] ance::Scope* scope() const override;

        /**
         * Push a statement to the end of the statement list.
         * @param statement The statement to add.
         */
        void pushStatement(Statement* statement);

        void createNativeBacking(CompileContext* context) override;
        void build(CompileContext* context) override;

        /**
         * Add a return. Call this method in the build method of a statement.
         * @param value The value to return or nullptr if nothing is returned.
         */
        void addReturn(ance::Value* value = nullptr);

        ance::Value* buildCall(const std::vector<ance::Value*>& arguments, CompileContext* context) const override;

        /**
         * Get the debug subprogram.
         * @return The debug subprogram.
         */
        llvm::DISubprogram* debugSubprogram();

        ance::GlobalScope* getGlobalScope() override;
        /**
         * Get the function scope of this function, in which the statements live.
         * @return The scope of this function. It is the child scope of the function.
         */
        ance::LocalScope* getFunctionScope();
        llvm::DIScope*    getDebugScope(CompileContext* context) override;

        void validate(ValidationLogger& validation_logger) override;

        ance::Variable* getVariable(std::string identifier) override;

        bool        isTypeRegistered(const std::string& type_name) override;
        ance::Type* getType(const std::string& type_name) override;
        void        registerType(ance::Type* type) override;

        bool accept(ance::ApplicationVisitor& visitor) override;

      protected:
        using Function::buildCall;

      private:
        AccessModifier access_;
        ance::Location definition_location_;

        ance::Scope*      containing_scope_;
        ance::LocalScope* function_scope_;

        std::vector<ance::LocalVariable*> arguments_;
        std::list<Statement*>             statements_;

        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};

        ance::Value* return_value_ {nullptr};
        bool         has_return_ {false};
    };
}

#endif
