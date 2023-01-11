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

lang::GlobalVariable::GlobalVariable(lang::ResolvingHandle<lang::Variable>       self,
                                     Optional<lang::ResolvingHandle<lang::Type>> type,
                                     lang::Location                              type_location,
                                     GlobalScope&                                containing_scope,
                                     lang::AccessModifier                        access,
                                     Optional<Owned<Expression>>                 init,
                                     bool                                        is_final,
                                     bool                                        is_constant,
                                     lang::Location                              location)
    : VariableDefinition(self,
                         type.valueOr(lang::Type::getUndefined()),
                         type_location,
                         containing_scope,
                         is_final,
                         location)
    , type_opt_(type)
    , access_(access)
    , is_constant_(is_constant)
    , constant_init_(is_constant_ ? dynamic_cast<ConstantExpression*>(getPtr(init)) : nullptr)
    , init_(getPtr(init))
    , init_owner_(std::move(init))
    , init_function_(init_ && not constant_init_ ? lang::OwningHandle<lang::Function>::takeOwnership(
                         lang::makeHandled<lang::Function>(lang::Identifier::like(self->name() + "$init")))
                                                 : Optional<lang::OwningHandle<lang::Function>>())
{
    if (type.hasValue()) containing_scope.addType(type.value());

    if (init_owner_.hasValue())
    {
        if (constant_init_) { constant_init_->setContainingScope(containing_scope); }
        else
        {
            init_function_.value()->defineAsInit(self->toUndefined(),
                                                 assigner(),
                                                 std::move(init_owner_.value()),
                                                 containing_scope);

            init_owner_ = {};
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
    if (access_ == lang::AccessModifier::EXTERN_ACCESS)
    {
        validation_logger.logError("Global variables cannot be extern", location());
    }

    if (type_opt_.hasValue())
    {
        if (lang::validation::isTypeUndefined(type(), typeLocation(), validation_logger)) return;

        if (!type().validate(validation_logger, typeLocation())) return;

        if (type().isVoidType())
        {
            validation_logger.logError("Global variable cannot have 'void' type", typeLocation());
            return;
        }

        if (type().isReferenceType())
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
                validation_logger.logError("Constant initializer must be of variable type " + type().getAnnotatedName(),
                                           constant_init_->location());
                return;
            }
        }
        else
        {
            if (!lang::Type::checkMismatch(type(), init_->type(), init_->location(), validation_logger)) return;
        }
    }
    else if (!type_opt_.hasValue())
    {
        validation_logger.logError("Default-initialized global variable must have explicit type", location());
        return;
    }
}

void lang::GlobalVariable::expand()
{
    if (type_opt_.hasValue())// Not necessary with full expansion.
    {
        type_opt_ = type_opt_.value()->createUndefinedClone();
        setType(type_opt_.value());
    }

    if (init_function_.hasValue())
    {
        clearChildren();
        init_       = nullptr;
        init_owner_ = {};

        init_function_.value()->expand();
    }
}

void lang::GlobalVariable::determineFlow()
{
    if (init_function_.hasValue()) { init_function_.value()->determineFlow(); }
}

void lang::GlobalVariable::validateFlow(ValidationLogger& validation_logger) const
{
    if (init_function_.hasValue()) { init_function_.value()->validateFlow(validation_logger); }
}

void lang::GlobalVariable::resolve()
{
    if (init_function_.hasValue()) { init_function_.value()->resolve(); }
}

void lang::GlobalVariable::postResolve()
{
    rerouteIfNeeded();

    if (init_function_.hasValue()) { init_function_.value()->postResolve(); }
}

void lang::GlobalVariable::createNativeBacking(CompileContext& context)
{
    if (init_function_.hasValue()) { init_function_.value()->createNativeBacking(context); }
}

void lang::GlobalVariable::build(CompileContext& context)
{
    if (init_function_.hasValue()) { init_function_.value()->build(context); }
}

void lang::GlobalVariable::buildDeclaration(CompileContext& context)
{
    llvm::Constant* native_initializer;

    if (constant_init_)
    {
        Shared<lang::Constant> initial_value = constant_init_->getConstantValue();
        initial_value->buildContentConstant(context.llvmModule());
        native_initializer = initial_value->getContentConstant();
    }
    else if (init_function_.hasValue())
    {
        // Will be initialized at startup.
        native_initializer = llvm::Constant::getNullValue(type()->getContentType(context.llvmContext()));
    }
    else { native_initializer = type()->getDefaultContent(context.llvmModule()); }

    native_variable_ = new llvm::GlobalVariable(context.llvmModule(),
                                                type()->getContentType(context.llvmModule().getContext()),
                                                is_constant_,
                                                access_.linkage(),
                                                native_initializer,
                                                name().text());

    auto* debug_info = context.di().createGlobalVariableExpression(&context.llvmUnit(),
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

    if (init_function_.hasValue()) { init_function_.value()->buildCall({}, context); }
}

void lang::GlobalVariable::buildFinalization(CompileContext& context)
{
    assert(not finalized_);

    type()->buildFinalizer(native_variable_, context);

    finalized_ = true;
}

std::vector<lang::ResolvingHandle<lang::Function>> lang::GlobalVariable::getFunctionDependencies()
{
    if (init_function_.hasValue()) return init_function_.value()->getFunctionDependencies();
    else return {};
}

std::vector<lang::ResolvingHandle<lang::Variable>> lang::GlobalVariable::getVariableDependencies()
{
    if (init_function_.hasValue())
    {
        auto dependencies = init_function_.value()->getVariableDependencies();

        std::vector<lang::ResolvingHandle<lang::Variable>> result;

        for (auto& [variable, usage_count] : dependencies)
        {
            if (variable != self() || usage_count > 1) result.emplace_back(variable);
        }

        return result;
    }
    else return {};
}

Shared<lang::Value> lang::GlobalVariable::getValue(CompileContext&)
{
    assert(native_variable_);
    return makeShared<lang::WrappedNativeValue>(type(), native_variable_);
}

void lang::GlobalVariable::storeValue(Shared<lang::Value> value, CompileContext& context)
{
    assert(native_variable_);

    value = lang::Type::makeMatching(type(), value, context);
    value->buildNativeValue(context);

    type()->buildCopyInitializer(native_variable_, value->getNativeValue(), context);
}

std::vector<lang::ResolvingHandle<lang::Variable>> lang::GlobalVariable::getAllVariableDependencies(
    lang::ResolvingHandle<lang::Variable> variable)
{
    auto dependencies = variable->getVariableDependencies();

    std::vector<lang::ResolvingHandle<lang::Function>> functions_to_check;
    std::set<lang::ResolvingHandle<lang::Function>>    functions_checked;

    auto function_dependencies = variable->getFunctionDependencies();
    functions_to_check.insert(functions_to_check.end(), function_dependencies.begin(), function_dependencies.end());

    while (!functions_to_check.empty())
    {
        auto function = functions_to_check.back();
        functions_to_check.pop_back();

        if (functions_checked.contains(function)) continue;
        functions_checked.emplace(function);

        auto function_variable_dependencies = function->getVariableDependencies();
        for (auto& variable_dependency : function_variable_dependencies)
            dependencies.emplace_back(variable_dependency.variable);

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
    int const unvisited = 0;
    int const visited   = 1;
    int const finished = 2;

    std::stack<std::pair<lang::ResolvingHandle<lang::Variable>, bool>> to_check;
    std::map<lang::ResolvingHandle<lang::Variable>, int>               state;
    std::vector<lang::ResolvingHandle<lang::Variable>>                 ordered_variables;

    for (auto& variable : variables)
    {
        if (!state.contains(variable)) to_check.emplace(variable, false);

        while (!to_check.empty())
        {
            auto& [current_variable, visited_children] = to_check.top();

            if (visited_children)
            {
                ordered_variables.emplace_back(current_variable);

                if (!state.contains(current_variable)) state.emplace(current_variable, unvisited);
                state.at(current_variable) = finished;

                to_check.pop();
            }
            else
            {
                to_check.top() = std::make_pair(current_variable, true);

                if (!state.contains(current_variable)) state.emplace(current_variable, unvisited);

                if (state.at(current_variable) == visited)
                {
                    validation_logger.logError("Variable '" + current_variable->name()
                                                   + "' part of circular dependency",
                                               current_variable->name().location());
                    return {};
                }

                state.at(current_variable) = visited;

                for (auto& dependency : getAllVariableDependencies(current_variable))
                {
                    if (state.contains(dependency) && state.at(dependency) == finished) continue;
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
    if (init_ && not type_opt_.hasValue())
    {
        auto assigned_type = init_->type();
        if (assigned_type->isDefined() && assigned_type != type()) { type().reroute(assigned_type); }
    }
}
