#include "VariableDescription.h"

#include "lang/ApplicationVisitor.h"
#include "lang/utility/Storage.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::VariableDescription::VariableDescription(lang::Identifier                            name,
                                               Optional<lang::ResolvingHandle<lang::Type>> type,
                                               lang::Location                              type_location,
                                               lang::Accessibility                         accessibility,
                                               Optional<Owned<Expression>>                 init,
                                               Assigner                                    assigner,
                                               bool                                        is_cmp,
                                               lang::Location                              location)
    : Description(accessibility)
    , name_(name)
    , type_(std::move(type))
    , type_location_(type_location)
    , assigner_(assigner)
    , is_cmp_(is_cmp)
    , location_(location)
    , type_handle_(type_.valueOr(init.hasValue() ? init.value()->type() : lang::Type::getUndefined()))
    , cmp_init_(is_cmp ? dynamic_cast<CompileTimeExpression*>(getPtr(init)) : nullptr)
    , init_expression_ptr_(getPtr(init))
    , init_expression_(std::move(init))
    , init_block_(std::nullopt)
    , variable_handle_(lang::makeHandled<lang::Variable>(name_))
{}

lang::VariableDescription::VariableDescription(lang::Identifier                            name,
                                               Optional<lang::ResolvingHandle<lang::Type>> type,
                                               lang::Location                              type_location,
                                               lang::Accessibility                         accessibility,
                                               Optional<Owned<Statement>>                  init_block,
                                               Optional<Owned<Expression>>                 init_expression,
                                               Expression*                                 init_expression_ptr,
                                               Assigner                                    assigner,
                                               bool                                        is_cmp,
                                               lang::Location                              location)
    : Description(accessibility)
    , name_(name)
    , type_(std::move(type))
    , type_location_(type_location)
    , assigner_(assigner)
    , is_cmp_(is_cmp)
    , location_(location)
    , type_handle_(
          type_.valueOr(init_expression_ptr != nullptr ? init_expression_ptr->type() : lang::Type::getUndefined()))
    , cmp_init_(is_cmp_ ? dynamic_cast<CompileTimeExpression*>(init_expression_ptr) : nullptr)
    , init_expression_ptr_(init_expression_ptr)
    , init_expression_(std::move(init_expression))
    , init_block_(std::move(init_block))
    , variable_handle_(lang::makeHandled<lang::Variable>(name_))
{}

lang::VariableDescription::VariableDescription(bool from_public_import)
    : Description(lang::Accessibility::imported(from_public_import))
    , name_(lang::Identifier::empty())
    , type_(lang::Type::getUndefined())
    , type_location_(lang::Location::global())
    , assigner_(Assigner::UNSPECIFIED)
    , is_cmp_(false)
    , location_(lang::Location::global())
    , type_handle_(type_.value())
    , cmp_init_(nullptr)
    , init_expression_ptr_(nullptr)
    , init_expression_(std::nullopt)
    , init_block_(std::nullopt)
    , variable_handle_(lang::makeHandled<lang::Variable>(name_))
{}

lang::Identifier const& lang::VariableDescription::name() const
{
    return name_;
}

bool lang::VariableDescription::isOverloadAllowed() const
{
    return false;
}

lang::GlobalVariable const* lang::VariableDescription::variable() const
{
    return global_variable_;
}

Expression const* lang::VariableDescription::initializer() const
{
    return init_expression_ptr_;
}

lang::InitializerFunction const* lang::VariableDescription::initializerFunction() const
{
    return init_function_;
}

bool lang::VariableDescription::isCMP() const
{
    return is_cmp_;
}

std::vector<std::reference_wrapper<lang::Entity const>> lang::VariableDescription::getProvidedEntities() const
{
    return {std::cref(variable_handle_.base())};
}

std::vector<lang::Description::Dependency> lang::VariableDescription::getDeclarationDependencies() const
{
    std::vector<Dependency> dependencies;

    if (type_.hasValue()) { dependencies.emplace_back(type_.value()); }

    return dependencies;
}

std::vector<lang::Description::Dependency> lang::VariableDescription::getDefinitionDependencies() const
{
    if (init_block_.hasValue())
    {
        std::vector<Dependency> dependencies;

        for (auto& dependency : init_block_.value()->getBlockScope()->getDependenciesOnDeclaration())
        {
            dependencies.emplace_back(dependency, false);
        }

        for (auto& dependency : init_block_.value()->getBlockScope()->getDependenciesOnDefinition())
        {
            dependencies.emplace_back(dependency);
        }

        return dependencies;
    }

    return {};
}

void lang::VariableDescription::performInitialization()
{
    lang::GlobalInitializer variable_init;

    if (type_.hasValue()) { scope().registerUsage(type_.value()); }
    else if (init_expression_ptr_ != nullptr) { type_handle_.reroute(init_expression_ptr_->type()); }

    if (cmp_init_ != nullptr)
    {
        variable_init = std::ref(*cmp_init_);

        cmp_init_->setContainingScope(scope());
        cmp_init_->walkDefinitions();
    }
    else
    {
        if (init_block_.hasValue())
        {
            auto init_function = lang::OwningHandle<lang::Function>::takeOwnership(
                lang::makeHandled<lang::Function>(lang::Identifier::like(name_ + "$init")));

            init_function_ = &init_function->defineAsInit(**init_block_, scope());

            variable_init = std::ref(*init_function);

            scope().addEntity(std::move(init_function));
        }
        else if (init_expression_.hasValue())
        {
            init_block_ = lang::InitializerFunction::makeInitializerBlock(variable_handle_->toUndefined(),
                                                                          assigner_,
                                                                          std::move(init_expression_.value()));

            init_block_.value()->setContainingScope(scope());
            init_block_.value()->walkDefinitions();

            init_expression_ = std::nullopt;
        }
    }

    global_variable_ = variable_handle_->defineAsGlobal(type_handle_,
                                                        type_location_,
                                                        scope(),
                                                        access().modifier(),
                                                        access().isImported(),
                                                        variable_init,
                                                        assigner_,
                                                        is_cmp_,
                                                        location_);

    scope().addEntity(OwningHandle<lang::Variable>::takeOwnership(variable_handle_));
}

void lang::VariableDescription::resolveDeclaration() {}

void lang::VariableDescription::resolveDefinition()
{
    if (init_expression_ptr_ != nullptr && init_block_.hasValue())
    {
        lang::Scope* block_scope = init_block_.value()->getBlockScope();
        if (block_scope != nullptr) { block_scope->resolve(); }
    }

    if (init_function_ != nullptr) { init_function_->function().resolve(); }
}

void lang::VariableDescription::postResolve()
{
    if (init_expression_ptr_ != nullptr)
    {
        if (init_block_.hasValue()) { init_block_.value()->postResolve(); }
        else init_expression_ptr_->postResolve();
    }

    if (init_function_ != nullptr) { init_function_->function().postResolve(); }
}

void lang::VariableDescription::validate(ValidationLogger& validation_logger) const
{
    if (access().modifier() == lang::AccessModifier::EXTERN_ACCESS)
    {
        validation_logger.logError("Global variables cannot be extern", location_);
    }

    if (type_.hasValue())
    {
        if (!type_handle_->validate(validation_logger, type_location_)) return;

        if (access().modifier() == lang::AccessModifier::PUBLIC_ACCESS)
        {
            lang::validation::isTypeExportable(type_handle_, type_location_, validation_logger);
        }

        if (type_handle_->isReferenceType())
        {
            validation_logger.logError("Global variable cannot have reference type", type_location_);
            return;
        }
    }

    if (is_cmp_)
    {
        if (cmp_init_ == nullptr)
        {
            if (init_expression_ptr_ != nullptr)
            {
                validation_logger.logError("Compile-time variable initializer must be compile-time expression",
                                           init_expression_ptr_->location());
                return;
            }

            validation_logger.logError("Compile-time variables require an explicit initializer", location_);
            return;
        }

        if (!assigner_.isFinal())
        {
            validation_logger.logError("Assignment to compile-time variables must be final", location_);
            return;
        }
    }

    if (init_expression_ptr_ != nullptr)
    {
        if (!init_expression_ptr_->validate(validation_logger)) return;

        if (cmp_init_ != nullptr)
        {
            if (!cmp_init_->isCMP())
            {
                validation_logger.logError("Compile-time expression must contain only compile-time parts",
                                           cmp_init_->location());
                return;
            }

            if (!lang::Type::areSame(type_handle_, cmp_init_->type()))
            {
                validation_logger.logError("Compile-time initializer must be of variable type "
                                               + type_handle_->getAnnotatedName(),
                                           cmp_init_->location());
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

lang::Description::Descriptions lang::VariableDescription::expand(lang::Context& new_context) const
{
    Expression* expanded_init_expression_ptr = nullptr;

    Optional<Owned<Statement>> expanded_init_block;

    if (init_block_.hasValue())
    {
        Statements expanded = init_block_.value()->expand(new_context);
        assert(expanded.size() == 1);

        expanded_init_block = std::move(expanded[0]);
    }

    Optional<Owned<Expression>> expanded_init_expression;

    if (init_expression_.hasValue())
    {
        auto [leading_statements, new_expression, following_statements] = init_expression_.value()->expand(new_context);

        assert(leading_statements.empty());
        assert(following_statements.empty());

        expanded_init_expression_ptr = new_expression.get();
        expanded_init_expression     = std::move(new_expression);

        if (cmp_init_ != nullptr) { assert(dynamic_cast<CompileTimeExpression*>(expanded_init_expression_ptr)); }
    }

    auto expanded = makeOwned<lang::VariableDescription>(name_,
                                                         type_handle_->getUndefinedTypeClone(new_context),
                                                         type_location_,
                                                         access(),
                                                         std::move(expanded_init_block),
                                                         std::move(expanded_init_expression),
                                                         expanded_init_expression_ptr,
                                                         assigner_,
                                                         is_cmp_,
                                                         location_);

    Descriptions descriptions;
    descriptions.emplace_back(std::move(expanded));

    return descriptions;
}

void lang::VariableDescription::performInitialization(Execution& exec)
{
    variable_handle_->performInitialization(exec);
}

void lang::VariableDescription::performFinalization(Execution& exec)
{
    variable_handle_->performFinalization(exec);
}

void lang::VariableDescription::sync(Storage& storage)
{
    storage.sync(name_);
    storage.sync(type_handle_);
    storage.sync(is_cmp_);
    storage.sync(assigner_);

    if (storage.isReading()) { variable_handle_ = lang::makeHandled<lang::Variable>(name_); }
}
