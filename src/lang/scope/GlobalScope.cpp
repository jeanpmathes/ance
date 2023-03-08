#include "GlobalScope.h"

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/Assigner.h"
#include "lang/construct/GlobalVariable.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/StructType.h"
#include "lang/type/TypeAlias.h"
#include "validation/ValidationLogger.h"

lang::GlobalScope::GlobalScope(bool is_containing_runtime)
{
    context_ = makeOwned<lang::Context>(*this, is_containing_runtime);
}

lang::Scope* lang::GlobalScope::scope()
{
    return this;
}

lang::Context& lang::GlobalScope::context()
{
    return **context_;
}

lang::Context const& lang::GlobalScope::context() const
{
    return **context_;
}

lang::GlobalScope* lang::GlobalScope::getGlobalScope()
{
    return this;
}

lang::GlobalScope const* lang::GlobalScope::getGlobalScope() const
{
    return this;
}

llvm::DIScope* lang::GlobalScope::getDebugScope(CompileContext& context) const
{
    return &context.llvmUnit();
}

void lang::GlobalScope::validate(ValidationLogger& validation_logger) const
{
    for (auto const& name : duplicated_names_)
    {
        validation_logger.logError("Name '" + name + "' already defined in the current context", name.location());
    }

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions) { description->validate(validation_logger); }
    }

    for (auto& [key, function] : defined_function_groups_) { function->validate(validation_logger); }

    std::vector<lang::ResolvingHandle<lang::Variable>> global_variables;
    for (auto& [name, variable] : const_cast<GlobalScope*>(this)->global_defined_variables_)
    {
        global_variables.emplace_back(variable.handle());
    }

    lang::GlobalVariable::determineOrder(global_variables, &validation_logger);
}

void lang::GlobalScope::expand()
{
    // this is only required because no full expansion is done on the global scope:
    auto undefined_function_groups = std::move(undefined_function_groups_);
    auto defined_function_groups   = std::move(defined_function_groups_);
    auto invalid_functions         = std::move(invalid_functions_);

    auto undefined_variables = std::move(global_defined_variables_);
    auto defined_variables   = std::move(global_defined_variables_);
    auto invalid_variables   = std::move(invalid_variables_);

    auto undefined_types = std::move(undefined_types_);
    auto defined_types   = std::move(defined_types_);
    auto invalid_types   = std::move(invalid_types_);

    clearChildren();

    // this is actually required:

    context_ = makeOwned<lang::Context>(*this, (**context_).isContainingRuntime());

    std::map<lang::Identifier, std::vector<Owned<lang::Description>>> expanded_descriptions;

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions)
        {
            std::vector<Owned<lang::Description>> new_descriptions = description->expand(**context_);

            for (auto& new_description : new_descriptions)
            {
                expanded_descriptions[name].push_back(std::move(new_description));
            }
        }
    }

    compatible_descriptions_ = std::move(expanded_descriptions);

    expanded_ = true;
}

void lang::GlobalScope::determineFlow()
{
    for (auto& [key, function] : defined_function_groups_) { function->determineFlow(); }
}

void lang::GlobalScope::validateFlow(ValidationLogger& validation_logger) const
{
    for (auto& [key, function] : defined_function_groups_) { function->validateFlow(validation_logger); }
}

void lang::GlobalScope::addDescription(Owned<lang::Description> description)
{
    addChild(*description);

    if (conflicting_description_names_.contains(description->name()))
    {
        conflicting_descriptions_.push_back(std::move(description));
        return;
    }

    auto conflict = compatible_descriptions_.find(description->name());

    if (conflict != compatible_descriptions_.end())
    {
        auto& [name, conflicting_description] = *conflict;

        assert(not conflicting_description.empty());

        bool const is_overload_allowed =
            description->isOverloadAllowed() && conflicting_description.front()->isOverloadAllowed();

        if (not is_overload_allowed)
        {
            conflicting_description_names_.emplace(description->name());

            std::move(conflicting_description.begin(),
                      conflicting_description.end(),
                      std::back_inserter(conflicting_descriptions_));
            conflicting_descriptions_.push_back(std::move(description));

            compatible_descriptions_.erase(conflict);

            return;
        }
    }

    compatible_descriptions_[description->name()].push_back(std::move(description));
}

void lang::GlobalScope::addFunction(lang::OwningHandle<lang::Function> function)
{
    if (!expanded_ && defined_names_.contains(function->name()) && !defined_function_groups_.contains(function->name()))
    {
        duplicated_names_.emplace_back(function->name());
        invalid_functions_.push_back(std::move(function));
    }
    else
    {
        defined_names_.emplace(function->name());

        lang::ResolvingHandle<lang::FunctionGroup> group = prepareDefinedFunctionGroup(function->name());
        group->addFunction(std::move(function));
    }
}

void lang::GlobalScope::addVariable(lang::OwningHandle<lang::Variable> variable)
{
    if (!expanded_ && defined_names_.contains(variable->name())
        && !global_undefined_variables_.contains(variable->name()))
    {
        duplicated_names_.emplace_back(variable->name());
        invalid_variables_.push_back(std::move(variable));
    }
    else
    {
        defined_names_.emplace(variable->name());

        if (global_undefined_variables_.contains(variable->name()))
        {
            global_undefined_variables_.at(variable->name()).handle().reroute(variable.handle());
            global_undefined_variables_.erase(variable->name());
        }

        addChild(*variable);
        global_defined_variables_.emplace(variable->name(), std::move(variable));
    }
}

void lang::GlobalScope::addType(lang::OwningHandle<lang::Type> type)
{
    if (!expanded_ && defined_names_.contains(type->name()) && !undefined_types_.contains(type->name()))
    {
        duplicated_names_.emplace_back(type->name());
        invalid_types_.push_back(std::move(type));
    }
    else
    {
        defined_names_.emplace(type->name());

        if (undefined_types_.contains(type->name()))
        {
            undefined_types_.at(type->name()).handle().reroute(type.handle());
            undefined_types_.erase(type->name());
        }

        type->setContainingScope(this);
        defined_types_.emplace(type->name(), std::move(type));
    }
}

Optional<lang::ResolvingHandle<lang::Type>> lang::GlobalScope::getType(Identifier string)
{
    auto it = defined_types_.find(string);

    if (it != defined_types_.end())
    {
        auto& [name, type] = *it;
        return type.handle();
    }
    else { return {}; }
}

void lang::GlobalScope::registerUsage(lang::ResolvingHandle<lang::Variable> variable)
{
    assert(!variable->isDefined());

    if (global_undefined_variables_.find(variable->name()) != global_undefined_variables_.end())
    {
        variable.reroute(global_undefined_variables_.at(variable->name()).handle());
        return;
    }

    if (global_defined_variables_.find(variable->name()) != global_defined_variables_.end())
    {
        variable.reroute(global_defined_variables_.at(variable->name()).handle());
        return;
    }

    global_undefined_variables_.at(variable->name()) = lang::OwningHandle<lang::Variable>::takeOwnership(variable);
}

void lang::GlobalScope::registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    assert(!function_group->isDefined());

    if (undefined_function_groups_.find(function_group->name()) != undefined_function_groups_.end())
    {
        function_group.reroute(undefined_function_groups_.at(function_group->name()).handle());
        return;
    }

    if (defined_function_groups_.find(function_group->name()) != defined_function_groups_.end())
    {
        function_group.reroute(defined_function_groups_.at(function_group->name()).handle());
        return;
    }

    undefined_function_groups_.at(function_group->name()) =
        lang::OwningHandle<lang::FunctionGroup>::takeOwnership(function_group);
}

void lang::GlobalScope::registerUsage(lang::ResolvingHandle<lang::Type> type)
{
    assert(!type->isDefined());

    if (undefined_types_.contains(type->name()))
    {
        type.reroute(undefined_types_.at(type->name()).handle());
        return;
    }

    if (defined_types_.contains(type->name()))
    {
        type.reroute(defined_types_.at(type->name()).handle());
        return;
    }

    undefined_types_.emplace(type->name(), lang::OwningHandle<lang::Type>::takeOwnership(type));
}

void lang::GlobalScope::registerDefinition(lang::ResolvingHandle<lang::Type> type)
{
    assert(type->isDefined());
    assert(not defined_types_.contains(type->name()));

    defined_types_.emplace(type->name(), lang::OwningHandle<lang::Type>::takeOwnership(type));
    type->setContainingScope(this);

    if (undefined_types_.contains(type->name()))
    {
        lang::OwningHandle<lang::Type> undefined = std::move(undefined_types_.at(type->name()));
        undefined_types_.erase(type->name());

        undefined.handle().reroute(type);
    }
}

void lang::GlobalScope::resolve()
{
    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions) { description->initialize(*this); }
    }

    for (auto& [key, group] : defined_function_groups_) { group->resolve(); }

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions) { description->resolve(); }
    }

    // Type registries are currently incorrect, as they resolve type dependencies in an incorrect scope.

    (**context_).resolve();
}

void lang::GlobalScope::postResolve()
{
    for (auto& [name, type] : defined_types_) { type->postResolve(); }

    (**context_).postResolve();

    for (auto& [key, group] : defined_function_groups_) { group->postResolve(); }

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions) { description->postResolve(); }
    }
}

bool lang::GlobalScope::resolveDefinition(lang::ResolvingHandle<lang::Variable> variable)
{
    if (global_defined_variables_.find(variable->name()) != global_defined_variables_.end())
    {
        variable.reroute(global_defined_variables_.at(variable->name()).handle());
        return true;
    }

    return false;
}

bool lang::GlobalScope::resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    if (defined_function_groups_.find(function_group->name()) != defined_function_groups_.end())
    {
        function_group.reroute(defined_function_groups_.at(function_group->name()).handle());
        return true;
    }

    return false;
}

bool lang::GlobalScope::resolveDefinition(lang::ResolvingHandle<lang::Type> type)
{
    if (defined_types_.contains(type->name()))
    {
        type.reroute(defined_types_.at(type->name()).handle());
        return true;
    }

    return false;
}

Optional<lang::ResolvingHandle<lang::Function>> lang::GlobalScope::findEntry()
{
    auto c = defined_function_groups_.find(lang::Identifier::like("main"));
    if (c == defined_function_groups_.end()) return {};

    auto& [name, group] = *c;

    auto potential_function = group->resolveOverload({});
    if (potential_function.size() != 1) return {};

    lang::Function const& function = *(potential_function.front());

    if (function.returnType().isFixedWidthIntegerType(32, false)) return potential_function.front();
    else return {};
}

bool lang::GlobalScope::hasEntry() const
{
    // The findEntry function is non-const because it returns a non-const handle, but it doesn't modify this object.
    return const_cast<GlobalScope*>(this)->findEntry().hasValue();
}

lang::ResolvingHandle<lang::Function> lang::GlobalScope::getEntry()
{
    Optional<lang::ResolvingHandle<lang::Function>> potential_function = findEntry();
    assert(potential_function.hasValue());
    return potential_function.value();
}

std::vector<std::string> lang::GlobalScope::getExportFunctions() const
{
    std::vector<std::string> exports;

    for (auto& [name, group] : defined_function_groups_)
    {
        std::vector<std::string> group_exports = group->getExportFunctions();
        exports.insert(exports.end(), group_exports.begin(), group_exports.end());
    }

    return exports;
}

void lang::GlobalScope::createNativeBacking(CompileContext& context)
{
    for (auto& [key, val] : defined_function_groups_) { val->createNativeBacking(context); }

    for (auto& [name, variable] : global_defined_variables_) { variable->buildDeclaration(context); }

    for (auto& [name, type] : defined_types_) { type->buildNativeDeclaration(context); }
    (**context_).buildNativeDeclarations(context);

    for (auto& [name, type] : defined_types_) { type->buildNativeDefinition(context); }
    (**context_).buildNativeDefinitions(context);
}

void lang::GlobalScope::buildFunctions(CompileContext& context)
{
    for (auto& [key, group] : defined_function_groups_) { group->build(context); }
}

void lang::GlobalScope::buildInitialization(CompileContext& context)
{
    std::vector<lang::ResolvingHandle<lang::Variable>> global_variables;
    for (auto& [name, variable] : global_defined_variables_) { global_variables.emplace_back(variable.handle()); }

    global_variables = GlobalVariable::determineOrder(global_variables, nullptr);

    for (auto& variable : global_variables) { variable->buildDefinition(context); }
}

void lang::GlobalScope::buildFinalization(CompileContext& context)
{
    for (auto& [name, variable] : global_defined_variables_) { variable->buildFinalization(context); }
}

lang::ResolvingHandle<lang::FunctionGroup> lang::GlobalScope::prepareDefinedFunctionGroup(Identifier name)
{
    if (defined_function_groups_.find(name) != defined_function_groups_.end())
    {
        return defined_function_groups_.at(name).handle();
    }

    Optional<lang::OwningHandle<lang::FunctionGroup>> undefined;

    if (undefined_function_groups_.contains(name))
    {
        undefined = std::move(undefined_function_groups_.at(name));
        undefined_function_groups_.erase(name);
    }
    else
    {
        undefined =
            lang::OwningHandle<lang::FunctionGroup>::takeOwnership(lang::makeHandled<lang::FunctionGroup>(name));
    }

    lang::ResolvingHandle<lang::FunctionGroup> defined = undefined->handle();
    defined_function_groups_.emplace(name, std::move(undefined.value()));

    return defined;
}
