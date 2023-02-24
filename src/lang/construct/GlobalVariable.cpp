#include "GlobalVariable.h"

#include <utility>

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

lang::GlobalVariable::GlobalVariable(lang::ResolvingHandle<lang::Variable> self,
                                     lang::ResolvingHandle<lang::Type>     type,
                                     lang::Location                        type_location,
                                     GlobalScope&                          containing_scope,
                                     lang::AccessModifier                  access,
                                     Initializer                           init,
                                     lang::Scope*                          init_scope,
                                     Assigner                              assigner,
                                     bool                                  is_constant,
                                     lang::Location                        location)
    : VariableDefinition(self, type, type_location, containing_scope, assigner.isFinal(), location)
    , access_(access)
    , is_constant_(is_constant)
    , init_(std::move(init))
    , init_scope_(init_scope)
    , assigner_(assigner)
{
    if (init_.hasValue())
    {
        if (auto* constant_init = std::get_if<std::reference_wrapper<ConstantExpression>>(&init_.value()))
        {
            constant_init->get().setContainingScope(containing_scope);
        }
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
    return assigner_;
}

void lang::GlobalVariable::buildDeclaration(CompileContext& context)
{
    llvm::Constant* native_initializer;

    if (init_.hasValue())
    {
        if (auto* constant_init = std::get_if<std::reference_wrapper<ConstantExpression>>(&init_.value()))
        {
            Shared<lang::Constant> initial_value = constant_init->get().getConstantValue();
            initial_value->buildContentConstant(context.llvmModule());
            native_initializer = initial_value->getContentConstant();
        }
        else
        {
            // Will be initialized at startup.
            assert(std::holds_alternative<std::reference_wrapper<lang::Function>>(init_.value()));
            native_initializer = llvm::Constant::getNullValue(type()->getContentType(context.llvmContext()));
        }
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
    if (init_.hasValue())
    {
        if (auto* function_init = std::get_if<std::reference_wrapper<lang::Function>>(&init_.value()))
        {
            function_init->get().buildCall({}, context);
        }
    }
}

void lang::GlobalVariable::buildFinalization(CompileContext& context)
{
    assert(not finalized_);

    type()->buildFinalizer(native_variable_, context);

    finalized_ = true;
}

std::vector<lang::ResolvingHandle<lang::Function>> lang::GlobalVariable::getFunctionDependencies()
{
    if (init_scope_ != nullptr) { return init_scope_->getFunctionDependencies(); }

    return {};
}

std::vector<lang::ResolvingHandle<lang::Variable>> lang::GlobalVariable::getVariableDependencies()
{
    if (init_scope_ != nullptr)
    {
        auto dependencies = init_scope_->getVariableDependencies();

        std::vector<lang::ResolvingHandle<lang::Variable>> result;

        for (auto& [variable, usage_count] : dependencies)
        {
            if (variable != self() || usage_count > 1) result.emplace_back(variable);
        }

        return result;
    }

    return {};
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
    ValidationLogger*                                  validation_logger)
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
                    if (validation_logger)
                    {
                        validation_logger->logError("Variable '" + current_variable->name()
                                                        + "' part of circular dependency",
                                                    current_variable->name().location());
                    }

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
