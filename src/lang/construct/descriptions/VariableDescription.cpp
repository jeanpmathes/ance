#include "VariableDescription.h"

#include "lang/ApplicationVisitor.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::VariableDescription::VariableDescription(lang::Identifier                            name,
                                               Optional<lang::ResolvingHandle<lang::Type>> type,
                                               lang::Location                              type_location,
                                               lang::AccessModifier                        access,
                                               Optional<Owned<Expression>>                 init,
                                               Assigner                                    assigner,
                                               bool                                        is_constant,
                                               lang::Location                              location)
    : name_(name)
    , type_(std::move(type))
    , type_location_(type_location)
    , access_(access)
    , assigner_(assigner)
    , is_constant_(is_constant)
    , location_(location)
    , type_handle_(type_.valueOr(init.hasValue() ? init.value()->type() : lang::Type::getUndefined()))
    , constant_init_(is_constant ? dynamic_cast<ConstantExpression*>(getPtr(init)) : nullptr)
    , init_expression_ptr_(getPtr(init))
    , init_expression_(std::move(init))
    , init_block_(std::nullopt)
{}

lang::VariableDescription::VariableDescription(lang::Identifier                            name,
                                               Optional<lang::ResolvingHandle<lang::Type>> type,
                                               lang::Location                              type_location,
                                               lang::AccessModifier                        access,
                                               Optional<Owned<Statement>>                  init_block,
                                               Optional<Owned<Expression>>                 init_expression,
                                               Expression*                                 init_expression_ptr,
                                               Assigner                                    assigner,
                                               bool                                        is_constant,
                                               lang::Location                              location)
    : name_(name)
    , type_(std::move(type))
    , type_location_(type_location)
    , access_(access)
    , assigner_(assigner)
    , is_constant_(is_constant)
    , location_(location)
    , type_handle_(
          type_.valueOr(init_expression_ptr != nullptr ? init_expression_ptr->type() : lang::Type::getUndefined()))
    , constant_init_(is_constant_ ? dynamic_cast<ConstantExpression*>(init_expression_ptr) : nullptr)
    , init_expression_ptr_(init_expression_ptr)
    , init_expression_(std::move(init_expression))
    , init_block_(std::move(init_block))
{}

lang::Identifier const& lang::VariableDescription::name() const
{
    return name_;
}

bool lang::VariableDescription::isOverloadAllowed() const
{
    return false;
}

void lang::VariableDescription::performInitialization()
{
    lang::OwningHandle<lang::Variable> variable =
        lang::OwningHandle<lang::Variable>::takeOwnership(lang::makeHandled<lang::Variable>(name_));

    lang::GlobalVariable::Initializer variable_init;

    lang::Scope* init_scope = nullptr;

    if (type_.hasValue()) { scope().addType(type_.value()); }
    else if (init_expression_ptr_ != nullptr) { type_handle_.reroute(init_expression_ptr_->type()); }

    if (constant_init_ != nullptr) { variable_init = std::ref(*constant_init_); }
    else
    {
        if (init_block_.hasValue())
        {
            auto init_function = lang::OwningHandle<lang::Function>::takeOwnership(
                lang::makeHandled<lang::Function>(lang::Identifier::like(name_ + "$init")));

            init_function->defineAsInit(**init_block_, scope());

            variable_init = std::ref(*init_function);
            init_scope    = &*init_function;

            scope().getGlobalScope()->addFunction(std::move(init_function));
        }
        else if (init_expression_.hasValue())
        {
            init_block_ = lang::InitializerFunction::makeInitializerBlock(variable->toUndefined(),
                                                                          assigner_,
                                                                          std::move(init_expression_.value()));

            init_block_.value()->setContainingScope(scope());
            init_block_.value()->walkDefinitions();

            init_scope = init_block_.value()->getBlockScope();

            init_expression_ = std::nullopt;
        }
    }

    variable->defineAsGlobal(type_handle_,
                             type_location_,
                             *scope().getGlobalScope(),
                             access_,
                             variable_init,
                             init_scope,
                             assigner_,
                             is_constant_,
                             location_);

    scope().getGlobalScope()->addVariable(std::move(variable));
}

void lang::VariableDescription::resolve()
{
    if (init_expression_ptr_ != nullptr && init_block_.hasValue())
    {
        lang::Scope* block_scope = init_block_.value()->getBlockScope();
        if (block_scope != nullptr) { block_scope->resolve(); }
    }
}

void lang::VariableDescription::postResolve()
{
    if (init_expression_ptr_ != nullptr && init_block_.hasValue()) { init_block_.value()->postResolve(); }
}

void lang::VariableDescription::validate(ValidationLogger& validation_logger) const
{
    if (access_ == lang::AccessModifier::EXTERN_ACCESS)
    {
        validation_logger.logError("Global variables cannot be extern", location_);
    }

    if (type_.hasValue())
    {
        if (lang::validation::isTypeUndefined(type_handle_, type_location_, validation_logger)) return;

        if (!type_handle_->validate(validation_logger, type_location_)) return;

        if (type_handle_->isVoidType())
        {
            validation_logger.logError("Global variable cannot have 'void' type", type_location_);
            return;
        }

        if (type_handle_->isReferenceType())
        {
            validation_logger.logError("Global variable cannot have reference type", type_location_);
            return;
        }
    }

    if (!constant_init_ && is_constant_)
    {
        validation_logger.logError("Constants require an explicit constant initializer", type_location_);
        return;
    }

    if (is_constant_ && !assigner_.isFinal())
    {
        validation_logger.logError("Assignment to constants must be final", type_location_);
        return;
    }

    if (init_expression_ptr_ != nullptr)
    {
        if (!init_expression_ptr_->validate(validation_logger)) return;

        if (constant_init_ != nullptr)
        {
            if (!lang::Type::areSame(type_handle_, constant_init_->type()))
            {
                validation_logger.logError("Constant initializer must be of variable type "
                                               + type_handle_->getAnnotatedName(),
                                           constant_init_->location());
                return;
            }
        }
        else
        {
            if (!lang::Type::checkMismatch(type_handle_,
                                           init_expression_ptr_->type(),
                                           init_expression_ptr_->location(),
                                           validation_logger))
                return;
        }
    }
    else if (!type_.hasValue())
    {
        validation_logger.logError("Default-initialized global variable must have explicit type", location_);
        return;
    }
}

lang::Description::Descriptions lang::VariableDescription::expand() const
{
    Expression* expanded_init_expression_ptr = nullptr;

    Optional<Owned<Statement>> expanded_init_block;

    if (init_block_.hasValue())
    {
        Statements expanded = init_block_.value()->expand();
        assert(expanded.size() == 1);

        expanded_init_block = std::move(expanded[0]);
    }

    Optional<Owned<Expression>> expanded_init_expression;

    if (init_expression_.hasValue())
    {
        auto [leading_statements, new_expression, following_statements] = init_expression_.value()->expand();

        assert(leading_statements.empty());
        assert(following_statements.empty());

        expanded_init_expression_ptr = new_expression.get();
        expanded_init_expression     = std::move(new_expression);

        if (constant_init_ != nullptr) { assert(dynamic_cast<ConstantExpression*>(expanded_init_expression_ptr)); }
    }

    auto expanded = makeOwned<lang::VariableDescription>(name_,
                                                         type_handle_->createUndefinedClone(),
                                                         type_location_,
                                                         access_,
                                                         std::move(expanded_init_block),
                                                         std::move(expanded_init_expression),
                                                         expanded_init_expression_ptr,
                                                         assigner_,
                                                         is_constant_,
                                                         location_);

    Descriptions descriptions;
    descriptions.emplace_back(std::move(expanded));

    return descriptions;
}
