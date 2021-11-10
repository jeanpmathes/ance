#ifndef ANCE_SRC_ANCE_CONSTRUCT_VARIABLEDEFINITION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VARIABLEDEFINITION_H_

#include "ance/construct/value/Value.h"
#include "ance/utility/Location.h"

namespace ance
{
    class Scope;
    class Type;
}

class ValidationLogger;
class CompileContext;

namespace ance
{
    /**
     * Defines the behaviour of a variable.
     */
    class VariableDefinition
    {
      public:
        VariableDefinition(const std::string&                identifier,
                           ance::ResolvingHandle<ance::Type> type,
                           ance::Scope*                      containing_scope,
                           bool                              is_final,
                           ance::Location                    location);

        [[nodiscard]] const std::string& identifier() const;

        /**
         * Get the scope in which this variable is defined.
         */
        [[nodiscard]] ance::Scope* scope() const;

        /**
         * Get the type of this variable.
         */
        [[nodiscard]] ance::ResolvingHandle<ance::Type> type() const;

        /**
         * Get the source location of the variable definition.
         */
        [[nodiscard]] ance::Location location() const;

        /**
         * Get whether this variable is defined as final.
         */
        [[nodiscard]] bool isFinal() const;

        /**
         * Validate this variable declaration.
         * @param validation_logger The logger to use for validation.
         */
        virtual void validate(ValidationLogger& validation_logger) = 0;

        virtual void buildDeclaration(CompileContext* context) = 0;
        virtual void buildDefinition(CompileContext* context)  = 0;

        virtual std::shared_ptr<ance::Value> getValue(CompileContext* context) = 0;
        virtual void setValue(const std::shared_ptr<ance::Value>& value, CompileContext* context);

        virtual ~VariableDefinition() = default;

      protected:
        virtual void storeValue(std::shared_ptr<ance::Value> value, CompileContext* context) = 0;

      private:
        const std::string& identifier_;

        ance::ResolvingHandle<ance::Type> type_;
        ance::Scope*                      scope_;
        bool                              is_final_;
        ance::Location                    location_;
    };
}

#endif