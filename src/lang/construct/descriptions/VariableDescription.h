#ifndef ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_VARIABLEDESCRIPTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_VARIABLEDESCRIPTION_H_

#include "Description.h"

#include "lang/AccessModifier.h"
#include "lang/Assigner.h"
#include "lang/utility/Identifier.h"
#include "lang/utility/Location.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Type;
    class Parameter;
    class GlobalVariable;
    class InitializerFunction;
}

class ConstantExpression;

namespace lang
{
    /**
     * A description of a (global) variable.
     */
    class VariableDescription
        : public virtual Description
        , public Element<VariableDescription, ANCE_CONSTRUCTS>
    {
      public:
        VariableDescription(lang::Identifier                            name,
                            Optional<lang::ResolvingHandle<lang::Type>> type,
                            lang::Location                              type_location,
                            lang::AccessModifier                        access,
                            Optional<Owned<Expression>>                 init,
                            lang::Assigner                              assigner,
                            bool                                        is_constant,
                            lang::Location                              location);

        VariableDescription(lang::Identifier                            name,
                            Optional<lang::ResolvingHandle<lang::Type>> type,
                            lang::Location                              type_location,
                            lang::AccessModifier                        access,
                            Optional<Owned<Statement>>                  init_block,
                            Optional<Owned<Expression>>                 init_expression,
                            Expression*                                 init_expression_ptr,
                            lang::Assigner                              assigner,
                            bool                                        is_constant,
                            lang::Location                              location);

        ~VariableDescription() override = default;

        [[nodiscard]] Identifier const&           name() const override;
        [[nodiscard]] bool                        isOverloadAllowed() const override;
        [[nodiscard]] lang::GlobalVariable const* variable() const;
        [[nodiscard]] Expression const*           initializer() const;
        [[nodiscard]] InitializerFunction const*  initializerFunction() const;

        void resolve() override;
        void postResolve() override;
        void validate(ValidationLogger& validation_logger) const override;

        [[nodiscard]] Descriptions expand(lang::Context& new_context) const override;

      protected:
        void performInitialization() override;

      private:
        lang::Identifier                            name_;
        Optional<lang::ResolvingHandle<lang::Type>> type_;
        lang::Location                              type_location_;
        lang::AccessModifier                        access_;
        Assigner                                    assigner_;
        bool                                        is_constant_;
        lang::Location                              location_;

        lang::ResolvingHandle<lang::Type> type_handle_;
        ConstantExpression*               constant_init_;
        Expression*                       init_expression_ptr_;

        Optional<Owned<Expression>> init_expression_;
        Optional<Owned<Statement>>  init_block_;

        lang::GlobalVariable*      global_variable_ {nullptr};
        lang::InitializerFunction* init_function_ {nullptr};
    };
}

#endif
