#ifndef ANCE_SRC_ANCE_SCOPE_GLOBALSCOPE_H_
#define ANCE_SRC_ANCE_SCOPE_GLOBALSCOPE_H_

#include "Scope.h"

#include <vector>

#include "ance/Assigner.h"

class ConstantExpression;

namespace ance
{
    /**
     * The top level scope.
     */
    class GlobalScope : public Scope
    {
      public:
        ance::GlobalScope* getGlobalScope() override;
        llvm::DIScope*     getDebugScope(CompileContext* context) override;

        [[nodiscard]] ance::Location location() const override;

        void validate(ValidationLogger& validation_logger) override;

        bool        isTypeRegistered(const std::string& type_name) override;
        ance::Type* getType(const std::string& type_name) override;
        void        registerType(ance::Type* type) override;

        /**
         * Define a global variable.
         * @param access The access level.
         * @param is_constant Whether the variable is a constant.
         * @param identifier The identifier of the variable.
         * @param type The type of the variable.
         * @param assigner The assigner to use for the initial assignment.
         * @param initializer The constant initializer.
         * @param location The source location.
         */
        void defineGlobalVariable(AccessModifier      access,
                                  bool                is_constant,
                                  const std::string&  identifier,
                                  ance::Type*         type,
                                  Assigner            assigner,
                                  ConstantExpression* initializer,
                                  ance::Location      location);

        ance::Variable* getVariable(std::string identifier) override;

        /**
         * Get the number of functions in this scope.
         * @return The function count.
         */
        [[nodiscard]] size_t functionCount() const;

        /**
         * Add a function name to this scope.
         * @param name The name.
         */
        void addFunctionName(const std::string& name);
        /**
         * Add a defined function to this scope.
         * @param function The function.
         */
        void addFunction(ance::Function* function);

        /**
         * Check if this scope contains a function.
         * @param identifier The name of the function to search.
         * @return True if the function exists in this scope.
         */
        bool hasFunction(const std::string& identifier);

        /**
         * Check if a given function is defined.
         * @param identifier The name of the function.
         * @return True if it is defined.
         */
        bool isFunctionDefined(const std::string& identifier);

        /**
         * Check if this global scope has an entry point.
         * The default entry point is a main method returning ui32.
         * @return True if there is an entry point.
         */
        bool hasEntry();

        /**
         * Check if this global scope has an exit point
         * The default exit point is an exit method taking a ui32.
         * @return True if there is an exit point.
         */
        bool hasExit();

        /**
         * Get a function by its identifier.
         * @param identifier The identifier.
         * @return The function.
         */
        ance::Function* getFunction(const std::string& identifier);

        /**
         * Create the native content backing methods and functions. It is required for the actual build.
         * @param context The current compile context.
         */
        void createNativeBacking(CompileContext* context);

        /**
         * Build all functions in this scope.
         * @param context The current compile context.
         */
        void buildFunctions(CompileContext* context);

        bool accept(ance::ApplicationVisitor& visitor) override;

      private:
        std::vector<std::pair<std::string, ance::Location>> errors_;

        std::map<std::string, ance::Type*> types_;

        std::map<std::string, ance::GlobalVariable*> global_constants_;
        std::map<std::string, ance::GlobalVariable*> global_variables_;
        std::map<std::string, ance::GlobalVariable*> global_undefined_;

        std::map<std::string, ance::Function*> functions_;
    };
}
#endif
