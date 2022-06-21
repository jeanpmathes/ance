#include "StructType.h"

#include <llvm/IR/Constant.h>

#include "compiler/CompileContext.h"
#include "lang/scope/Scope.h"
#include "validation/ValidationLogger.h"
#include "lang/type/VoidType.h"

lang::StructType::StructType(lang::AccessModifier                       access_modifier,
                             lang::Identifier                           name,
                             std::vector<std::unique_ptr<lang::Member>> members,
                             lang::Scope*                               scope,
                             lang::Location                             location)
    : TypeDefinition(name, location)
    , access_(access_modifier)
    , members_(std::move(members))
    , scope_(scope)
{}

StateCount lang::StructType::getStateCount() const
{
    // While some structs actually have a state count, they cannot currently be matched anyway.
    // Also, struct matching would work on a per-member basis which makes state count of structs irrelevant for now.

    return SpecialCount::ABSTRACT;
}

llvm::Constant* lang::StructType::getDefaultContent(llvm::LLVMContext& c)
{
    std::vector<llvm::Constant*> values;

    for (auto& member : members_) { values.push_back(member->type()->getDefaultContent(c)); }

    return llvm::ConstantStruct::get(getContentType(c), values);
}

llvm::StructType* lang::StructType::getContentType(llvm::LLVMContext& c)
{
    if (!native_type_)
    {
        std::vector<llvm::Type*> member_types;

        for (auto& member : members_) { member_types.push_back(member->type()->getContentType(c)); }

        native_type_ = llvm::StructType::create(c, member_types, createMangledName());
    }

    return native_type_;
}

void lang::StructType::onScope()
{
    for (auto& member : members_) { member->setScope(scope()); }
}

bool lang::StructType::validateDefinition(ValidationLogger& validation_logger)
{
    bool valid = true;

    for (auto& member : members_)
    {
        auto type = member->type();

        if (!type->isDefined())
        {
            validation_logger.logError("Cannot declare member of undefined type " + type->getAnnotatedName(),
                                       member->location());
            valid = false;
            continue;
        }

        if (type == self())
        {
            validation_logger.logError("Cannot declare recursive member", member->location());
            valid = false;
            continue;
        }

        if (type == lang::VoidType::get())
        {
            validation_logger.logError("Cannot declare member of 'void' type", member->location());
            valid = false;
            continue;
        }

        if (type->isReferenceType())
        {
            validation_logger.logError("Cannot declare member of reference type", member->location());
            valid = false;
            continue;
        }
    }

    valid = valid && checkDependencies(validation_logger);

    if (!valid) return false;// These checks depend on the definition being roughly valid.

    std::set<lang::Identifier> member_names;

    for (auto& member : members_)
    {
        if (!member->type()->validate(validation_logger, member->location())) { valid = false; }

        if (member_names.contains(member->name()))
        {
            validation_logger.logError("Member name '" + member->name() + "' already used", member->name().location());
            valid = false;
        }

        member_names.insert(member->name());
    }

    return valid;
}

std::string lang::StructType::createMangledName()
{
    std::string mangled_name;
    mangled_name += "struct";
    mangled_name += "(" + name() + ")";
    mangled_name += "(";

    for (auto& member : members_)
    {
        mangled_name += "(";
        mangled_name += member->type()->getMangledName();
        mangled_name += ")";
    }

    mangled_name += ")";
    return mangled_name;
}

llvm::DIType* lang::StructType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl         = context->module()->getDataLayout();
    llvm::Type*             array_type = getContentType(*context->llvmContext());

    uint64_t size      = dl.getTypeSizeInBits(array_type);
    uint32_t alignment = dl.getABITypeAlignment(array_type);

    std::vector<llvm::Metadata*> member_types;
    for (auto& member : members_) { member_types.push_back(member->type()->getDebugType(context)); }

    llvm::MDTuple* debug_type = llvm::MDNode::get(*context->llvmContext(), member_types);

    return context->di()->createStructType(scope_->getDebugScope(context),
                                           name().text(),
                                           context->sourceFile(),
                                           getDefinitionLocation().line(),
                                           size,
                                           alignment,
                                           llvm::DINode::FlagZero,
                                           nullptr,
                                           debug_type);
}

std::vector<lang::TypeDefinition*> lang::StructType::getDependencies()
{
    std::vector<lang::TypeDefinition*> dependencies;
    std::set<lang::TypeDefinition*>    added;

    for (auto& member : members_)
    {
        auto* definition = member->type()->getDefinition();

        if (definition && !added.contains(definition))
        {
            dependencies.push_back(definition);
            added.insert(definition);
        }
    }

    return dependencies;
}
