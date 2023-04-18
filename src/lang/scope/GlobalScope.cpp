#include "GlobalScope.h"

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/Assigner.h"
#include "lang/construct/GlobalVariable.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/StructType.h"
#include "lang/type/TypeAlias.h"
#include "lang/utility/Storage.h"
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
    for (auto const& [name, associated_descriptions] : incompatible_descriptions_)
    {
        bool              first_source = true;
        std::stringstream source_list;
        size_t            conflicting_imports = 0;

        std::vector<lang::Identifier> internal_conflicts;

        for (auto const& [source, description] : associated_descriptions)
        {
            if (source.has_value())
            {
                if (first_source) first_source = false;
                else source_list << ", ";

                source_list << "'";
                source_list << source.value();
                source_list << "'";

                conflicting_imports++;
            }
            else { internal_conflicts.emplace_back(description->name()); }
        }

        assert(conflicting_imports + internal_conflicts.size() > 1);

        if (conflicting_imports > 1)
        {
            validation_logger.logError("Multiple definitions with the name '" + name
                                           + "' are imported from: " + source_list.str(),
                                       lang::Location::global());
        }

        for (auto const& internal_conflict : internal_conflicts)
        {
            if (conflicting_imports == 0)
            {
                validation_logger.logError("Multiple definitions with the name '" + name
                                               + "' are defined in the same scope",
                                           internal_conflict.location());
            }
            else
            {
                validation_logger.logError("Multiple definitions with the name '" + name
                                               + "' are defined in the same scope and imported from: "
                                               + source_list.str(),
                                           internal_conflict.location());
            }
        }
    }

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions)
        {
            if (description.description->isImported()) continue;
            description.description->validate(validation_logger);
        }
    }

    for (auto& [key, function] : defined_function_groups_) { function->validate(validation_logger); }

    auto& global_defined_variables = const_cast<GlobalScope*>(this)->global_defined_variables_;

    std::vector<lang::ResolvingHandle<lang::Variable>> global_variables;
    global_variables.reserve(global_defined_variables.size());
    for (auto& [name, variable] : global_defined_variables) { global_variables.emplace_back(variable.handle()); }

    lang::GlobalVariable::determineOrder(global_variables, &validation_logger);
}

Owned<lang::GlobalScope> lang::GlobalScope::expand() const
{
    Owned<lang::GlobalScope> expanded_scope = makeOwned<lang::GlobalScope>((**context_).isContainingRuntime());

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions)
        {
            std::vector<Owned<lang::Description>> new_descriptions =
                description.description->expand(expanded_scope->context());

            for (auto& new_description : new_descriptions)
            {
                expanded_scope->addDescription(std::move(new_description));
            }
        }
    }

    return expanded_scope;
}

void lang::GlobalScope::determineFlow()
{
    for (auto& [key, function] : defined_function_groups_) { function->determineFlow(); }
}

void lang::GlobalScope::validateFlow(ValidationLogger& validation_logger) const
{
    for (auto& [key, function] : defined_function_groups_) { function->validateFlow(validation_logger); }
}

void lang::GlobalScope::setCurrentDescriptionSource(std::optional<std::string> source)
{
    current_description_source_ = std::move(source);
}

void lang::GlobalScope::addDescription(Owned<lang::Description> description)
{
    addChild(*description);

    if (incompatible_descriptions_.contains(description->name()))
    {
        incompatible_descriptions_[description->name()].emplace_back(current_description_source_,
                                                                     std::move(description));
        return;
    }

    auto conflict = compatible_descriptions_.find(description->name());

    if (conflict != compatible_descriptions_.end())
    {
        auto& [name, conflicting_description] = *conflict;

        assert(not conflicting_description.empty());

        bool const is_overload_allowed =
            description->isOverloadAllowed() && conflicting_description.front().description->isOverloadAllowed();

        if (not is_overload_allowed)
        {
            std::move(conflicting_description.begin(),
                      conflicting_description.end(),
                      std::back_inserter(incompatible_descriptions_[description->name()]));
            incompatible_descriptions_[description->name()].emplace_back(current_description_source_,
                                                                         std::move(description));

            compatible_descriptions_.erase(conflict);

            return;
        }
    }

    compatible_descriptions_[description->name()].emplace_back(current_description_source_, std::move(description));
}

void lang::GlobalScope::addFunction(lang::OwningHandle<lang::Function> function)
{
    assert(!defined_names_.contains(function->name()) || defined_function_groups_.contains(function->name()));

    defined_names_.emplace(function->name());

    lang::ResolvingHandle<lang::FunctionGroup> group = prepareDefinedFunctionGroup(function->name());
    group->addFunction(std::move(function));
}

void lang::GlobalScope::addVariable(lang::OwningHandle<lang::Variable> variable)
{
    assert(!defined_names_.contains(variable->name()) || global_undefined_variables_.contains(variable->name()));

    defined_names_.emplace(variable->name());

    if (global_undefined_variables_.contains(variable->name()))
    {
        global_undefined_variables_.at(variable->name()).handle().reroute(variable.handle());
        global_undefined_variables_.erase(variable->name());
    }

    global_defined_variables_.emplace(variable->name(), std::move(variable));
}

void lang::GlobalScope::addType(lang::OwningHandle<lang::Type> type)
{
    assert(!defined_names_.contains(type->name()) || undefined_types_.contains(type->name()));

    defined_names_.emplace(type->name());

    if (undefined_types_.contains(type->name()))
    {
        undefined_types_.at(type->name()).handle().reroute(type.handle());
        undefined_types_.erase(type->name());
    }

    type->setContainingScope(this);
    defined_types_.emplace(type->name(), std::move(type));
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
        for (auto& description : descriptions) { description.description->initialize(*this); }
    }

    for (auto& [key, group] : defined_function_groups_) { group->resolve(); }

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions) { description.description->resolve(); }
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
        for (auto& description : descriptions) { description.description->postResolve(); }
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
    global_variables.reserve(global_defined_variables_.size());
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

void lang::GlobalScope::synchronize(lang::GlobalScope* scope, Storage& storage)
{
    std::vector<lang::Description*> export_descriptions;

    if (storage.isWriting())
    {
        for (auto& [name, descriptions] : scope->compatible_descriptions_)
        {
            for (auto& description : descriptions)
            {
                if (description.description->access() != lang::AccessModifier::PUBLIC_ACCESS) continue;
                if (description.description->isImported()) continue;

                export_descriptions.emplace_back(&*description.description);
            }
        }
    }

    uint64_t export_count = export_descriptions.size();
    storage.sync(export_count);
    if (storage.isReading()) export_descriptions = std::vector<lang::Description*>(export_count);

    for (uint64_t i = 0; i < export_count; i++)
    {
        lang::Description** description = &export_descriptions[i];
        storage.sync(description);
    }

    if (storage.isReading())
    {
        for (auto& description : export_descriptions) { scope->addDescription(Owned<lang::Description>(*description)); }
    }
}
