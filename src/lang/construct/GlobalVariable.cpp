#include "GlobalVariable.h"

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/constant/Constant.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/expression/ConstantExpression.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/VoidType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

namespace llvm
{
    class Constant;
}

lang::GlobalVariable::GlobalVariable(lang::ResolvingHandle<lang::Variable>            self,
                                     std::optional<lang::ResolvingHandle<lang::Type>> type,
                                     lang::Location                                   type_location,
                                     GlobalScope&                                     containing_scope,
                                     lang::AccessModifier                             access,
                                     std::unique_ptr<Expression>                      init,
                                     bool                                             is_final,
                                     bool                                             is_constant,
                                     lang::Location                                   location)
    : VariableDefinition(self,
                         type.value_or(lang::Type::getUndefined()),
                         type_location,
                         containing_scope,
                         is_final,
                         location)
    , type_opt_(type)
    , access_(access)
    , is_constant_(is_constant)
    , constant_init_(is_constant_ ? dynamic_cast<ConstantExpression*>(init.get()) : nullptr)
    , init_(init.get())
    , init_owner_(std::move(init))
    , init_function_(init_ && not constant_init_ ? lang::OwningHandle<lang::Function>::takeOwnership(
                         lang::makeHandled<lang::Function>(lang::Identifier::from(self->name() + "$init")))
                                                 : std::optional<lang::OwningHandle<lang::Function>>())
{
    if (type.has_value()) containing_scope.addType(type.value());

    if (init_)
    {
        if (constant_init_) { constant_init_->setContainingScope(containing_scope); }
        else
        {
            init_function_.value()->defineAsInit(self->toUndefined(),
                                                 assigner(),
                                                 std::move(init_owner_),
                                                 containing_scope);
        }

        addChild(*init_);
    }
}

lang::AccessModifier lang::GlobalVariable::access() const
{
    return access_;
}

bool lang::GlobalVariable::isConstant() const
{
    return is_constant_;
}

lang::Assigner lang::GlobalVariable::assigner() const
{
    if (isFinal()) { return lang::Assigner::FINAL_COPY_ASSIGNMENT; }
    else { return lang::Assigner::COPY_ASSIGNMENT; }
}

Expression* lang::GlobalVariable::init() const
{
    return init_;
}

void lang::GlobalVariable::validate(ValidationLogger& validation_logger) const
{
    if (type_opt_.has_value())
    {
        if (lang::validation::isTypeUndefined(type(), typeLocation(), validation_logger)) return;

        if (!type()->validate(validation_logger, typeLocation())) return;

        if (type()->isVoidType())
        {
            validation_logger.logError("Global variable cannot have 'void' type", typeLocation());
            return;
        }

        if (type()->isReferenceType())
        {
            validation_logger.logError("Global variable cannot have reference type", typeLocation());
            return;
        }
    }

    if (!init_ && is_constant_)
    {
        validation_logger.logError("Constants require an explicit constant initializer", location());
        return;
    }

    if (!constant_init_ && is_constant_)
    {
        validation_logger.logError("Initializer for constant variable must be constant", location());
        return;
    }

    if (is_constant_ && !isFinal())
    {
        validation_logger.logError("Assignment to constants must be final", location());
        return;
    }

    if (init_)
    {
        if (!init_->validate(validation_logger)) return;

        if (constant_init_)
        {
            if (!lang::Type::areSame(type(), constant_init_->type()))
            {
                validation_logger.logError("Constant initializer must be of variable type "
                                               + type()->getAnnotatedName(),
                                           constant_init_->location());
                return;
            }
        }
        else
        {
            if (!lang::Type::checkMismatch(type(), init_->type(), init_->location(), validation_logger)) return;
        }
    }
    else if (!type_opt_.has_value())
    {
        validation_logger.logError("Default-initialized global variable must have explicit type", location());
        return;
    }
}

void lang::GlobalVariable::expand()
{
    if (init_function_)
    {
        clearChildren();
        init_ = nullptr;
        init_owner_.reset();

        init_function_.value()->expand();
    }
}

void lang::GlobalVariable::determineFlow()
{
    if (init_function_) { init_function_.value()->determineFlow(); }
}

void lang::GlobalVariable::validateFlow(ValidationLogger& validation_logger) const
{
    if (init_function_) { init_function_.value()->validateFlow(validation_logger); }
}

void lang::GlobalVariable::resolve()
{
    if (init_function_) { init_function_.value()->resolve(); }
}

void lang::GlobalVariable::postResolve()
{
    rerouteIfNeeded();

    if (init_function_) { init_function_.value()->postResolve(); }
}

void lang::GlobalVariable::createNativeBacking(CompileContext& context)
{
    if (init_function_) { init_function_.value()->createNativeBacking(context); }
}

void lang::GlobalVariable::build(CompileContext& context)
{
    if (init_function_) { init_function_.value()->build(context); }
}

void lang::GlobalVariable::buildDeclaration(CompileContext& context)
{
    llvm::Constant* native_initializer;

    if (constant_init_)
    {
        std::shared_ptr<lang::Constant> initial_value = constant_init_->getConstantValue();
        initial_value->buildContentConstant(context.module());
        native_initializer = initial_value->getContentConstant();
    }
    else if (init_function_)
    {
        // Will be initialized at startup.
        native_initializer = llvm::Constant::getNullValue(type()->getContentType(*context.llvmContext()));
    }
    else { native_initializer = type()->getDefaultContent(*context.module()); }

    native_variable_ = new llvm::GlobalVariable(*context.module(),
                                                type()->getContentType(context.module()->getContext()),
                                                is_constant_,
                                                access_.linkage(),
                                                native_initializer,
                                                name().text());

    auto* debug_info = context.di()->createGlobalVariableExpression(context.unit(),
                                                                    name().text(),
                                                                    name().text(),
                                                                    context.getSourceFile(location()),
                                                                    static_cast<unsigned>(location().line()),
                                                                    type()->getDebugType(context),
                                                                    true);

    native_variable_->addDebugInfo(debug_info);
}

void lang::GlobalVariable::buildDefinition(CompileContext& context)
{
    if (constant_init_) return;// Definition done in declaration.

    if (init_function_) { init_function_.value()->buildCall({}, context); }
}

void lang::GlobalVariable::buildFinalization(CompileContext& context)
{
    assert(not finalized_);

    type()->buildFinalizer(native_variable_, context);

    finalized_ = true;
}

std::set<lang::ResolvingHandle<lang::Function>> lang::GlobalVariable::getFunctionDependencies() const
{
    if (init_function_) return init_function_.value()->getFunctionDependencies();
    else return {};
}

std::set<lang::ResolvingHandle<lang::Variable>> lang::GlobalVariable::getVariableDependencies() const
{
    if (init_function_)
    {
        auto dependencies = init_function_.value()->getVariableDependencies();

        std::set<lang::ResolvingHandle<lang::Variable>> result;

        for (auto& [dependency, count] : dependencies)
        {
            if (dependency != self() || count > 1) result.insert(dependency);
        }

        return result;
    }
    else return {};
}

std::shared_ptr<lang::Value> lang::GlobalVariable::getValue(CompileContext&)
{
    assert(native_variable_);
    return std::make_shared<lang::WrappedNativeValue>(type(), native_variable_);
}

void lang::GlobalVariable::storeValue(std::shared_ptr<lang::Value> value, CompileContext& context)
{
    assert(native_variable_);

    value = lang::Type::makeMatching(type(), value, context);
    value->buildNativeValue(context);

    type()->buildCopyInitializer(native_variable_, value->getNativeValue(), context);
}

std::set<lang::ResolvingHandle<lang::Variable>> lang::GlobalVariable::getAllVariableDependencies(
    lang::ResolvingHandle<lang::Variable> variable)
{
    std::set<lang::ResolvingHandle<lang::Variable>> dependencies = variable->getVariableDependencies();

    std::vector<lang::ResolvingHandle<lang::Function>> functions_to_check;
    std::set<lang::ResolvingHandle<lang::Function>>    functions_checked;

    auto function_dependencies = variable->getFunctionDependencies();
    functions_to_check.insert(functions_to_check.end(), function_dependencies.begin(), function_dependencies.end());

    while (!functions_to_check.empty())
    {
        auto function = functions_to_check.back();
        functions_to_check.pop_back();

        if (functions_checked.contains(function)) continue;
        functions_checked.insert(function);

        auto function_variable_dependencies = function->getVariableDependencies();
        for (auto& [dependency, count] : function_variable_dependencies) dependencies.insert(dependency);

        auto function_function_dependencies = function->getFunctionDependencies();
        functions_to_check.insert(functions_to_check.end(),
                                  function_function_dependencies.begin(),
                                  function_function_dependencies.end());
    }

    return dependencies;
}

std::vector<lang::ResolvingHandle<lang::Variable>> lang::GlobalVariable::determineOrder(
    std::vector<lang::ResolvingHandle<lang::Variable>> variables,
    ValidationLogger&                                  validation_logger)
{
    int const visited  = 1;
    int const finished = 2;

    std::stack<std::pair<lang::ResolvingHandle<lang::Variable>, bool>> to_check;
    std::map<lang::ResolvingHandle<lang::Variable>, int>               state;
    std::vector<lang::ResolvingHandle<lang::Variable>>                 ordered_variables;

    for (auto const& variable : variables)
    {
        if (!state.contains(variable)) to_check.emplace(variable, false);

        while (!to_check.empty())
        {
            auto [current_variable, visited_children] = to_check.top();

            if (visited_children)
            {
                ordered_variables.push_back(current_variable);
                state[current_variable] = finished;
                to_check.pop();
            }
            else
            {
                to_check.top() = std::make_pair(current_variable, true);

                if (state[current_variable] == visited)
                {
                    validation_logger.logError("Variable '" + current_variable->name()
                                                   + "' part of circular dependency",
                                               current_variable->name().location());
                    return {};
                }

                state[current_variable] = visited;

                for (auto const& dependency : getAllVariableDependencies(current_variable))
                {
                    if (state[dependency] == finished) continue;
                    to_check.emplace(dependency, false);
                }
            }
        }
    }

    assert(variables.size() == ordered_variables.size());
    return ordered_variables;
}

void lang::GlobalVariable::rerouteIfNeeded()
{
    if (init_ && not type_opt_.has_value())
    {
        auto assigned_type = init_->tryGetType();
        if (assigned_type && assigned_type.value() != type()) { type().reroute(assigned_type.value()); }
    }
}
