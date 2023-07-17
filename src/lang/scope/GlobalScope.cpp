#include "GlobalScope.h"

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/Assigner.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/StructType.h"
#include "lang/type/TypeAlias.h"
#include "lang/utility/Storage.h"
#include "validation/ValidationLogger.h"

lang::GlobalScope::GlobalScope(bool is_containing_runtime) : Scope()
{
    context_ = makeOwned<lang::Context>(*this, is_containing_runtime);
}

lang::Scope* lang::GlobalScope::scope()
{
    return this;
}

lang::Scope const* lang::GlobalScope::scope() const
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

bool lang::GlobalScope::isPartOfFunction() const
{
    return false;
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

Owned<lang::GlobalScope> lang::GlobalScope::expand() const
{
    Owned<lang::GlobalScope> expanded_scope = makeOwned<lang::GlobalScope>((**context_).isContainingRuntime());

    for (auto& [name, descriptions] : getCompatibleDescriptions())
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
    for (auto& group : getFunctionGroups()) { group->determineFlow(); }
}

void lang::GlobalScope::validateFlow(ValidationLogger& validation_logger) const
{
    for (auto& group : getFunctionGroups()) { group.get().validateFlow(validation_logger); }
}

bool lang::GlobalScope::hasEntryPoint() const
{
    // The findEntry function is non-const because it returns a non-const handle, but it doesn't modify this object.
    return const_cast<GlobalScope*>(this)->findEntryPoint().hasValue();
}

lang::ResolvingHandle<lang::Function> lang::GlobalScope::getEntryPoint()
{
    Optional<lang::ResolvingHandle<lang::Function>> potential_function = findEntryPoint();
    assert(potential_function.hasValue());
    return potential_function.value();
}

void lang::GlobalScope::createNativeBacking(CompileContext& context)
{
    for (auto& function_group : getFunctionGroups()) { function_group->createNativeBacking(context); }

    for (auto& variable : getVariables()) { variable->buildDeclaration(context); }

    for (auto& type : getTypes()) { type->buildNativeDeclaration(context); }
    (**context_).buildNativeDeclarations(context);

    for (auto& type : getTypes()) { type->buildNativeDefinition(context); }
    (**context_).buildNativeDefinitions(context);
}

void lang::GlobalScope::buildFunctions(CompileContext& context)
{
    for (auto& function_group : getFunctionGroups()) { function_group->build(context); }
}

Optional<lang::ResolvingHandle<lang::Function>> lang::GlobalScope::findEntryPoint()
{
    std::vector<lang::ResolvingHandle<lang::Function>> potential_function;

    for (auto& group : getFunctionGroups())
    {
        if (group->name().text() == "main")
        {
            potential_function = group->resolveOverload({});
            break;
        }
    }

    if (potential_function.size() != 1) return {};

    lang::Function const& function = *(potential_function.front());

    if (function.returnType().isFixedWidthIntegerType(32, false)) return potential_function.front();
    else return {};
}

void lang::GlobalScope::onResolve()
{
    // Type registries are currently incorrect, as they resolve type dependencies in an incorrect scope.
    (**context_).resolve();
}

void lang::GlobalScope::onPostResolve()
{
    (**context_).postResolve();
}

void lang::GlobalScope::synchronize(lang::GlobalScope* scope, Storage& storage)
{
    std::vector<lang::Description*> export_descriptions;

    if (storage.isWriting())
    {
        for (auto& [name, descriptions] : scope->getCompatibleDescriptions())
        {
            for (auto& description : descriptions)
            {
                if (!description.description->access().isExported()) continue;

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
