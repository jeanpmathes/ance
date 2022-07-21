#include "StructType.h"

#include <llvm/IR/Constant.h>

#include "compiler/CompileContext.h"
#include "lang/scope/Scope.h"
#include "validation/ValidationLogger.h"
#include "lang/type/VoidType.h"
#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/utility/Values.h"
#include "lang/type/ReferenceType.h"

lang::StructType::StructType(lang::AccessModifier                       access_modifier,
                             lang::Identifier                           name,
                             std::vector<std::unique_ptr<lang::Member>> members,
                             lang::Scope*                               scope,
                             lang::Location                             location)
    : TypeDefinition(name, location)
    , access_(access_modifier)
    , members_(std::move(members))
    , scope_(scope)
{
    int32_t index = 0;

    for (auto& member : members_)
    {
        member_map_.emplace(member->name(), *member);
        member_indices_[member->name()] = index++;
    }
}

StateCount lang::StructType::getStateCount() const
{
    // While some structs actually have a state count, they cannot currently be matched anyway.
    // Also, struct matching would work on a per-member basis which makes state count of structs irrelevant for now.

    return SpecialCount::ABSTRACT;
}

llvm::Constant* lang::StructType::getDefaultContent(llvm::Module& m)
{
    std::vector<llvm::Constant*> values;

    for (auto& member : members_) { values.push_back(member->getConstantInitializer(m)); }

    return llvm::ConstantStruct::get(getContentType(m.getContext()), values);
}

llvm::StructType* lang::StructType::getContentType(llvm::LLVMContext& c)
{
    if (!native_type_)
    {
        native_type_ = llvm::StructType::create(c, getMangledName());

        std::vector<llvm::Type*> member_types;

        for (auto& member : members_) { member_types.push_back(member->type()->getContentType(c)); }

        native_type_->setBody(member_types);
    }

    return native_type_;
}

lang::AccessModifier lang::StructType::getAccessModifier() const
{
    return access_;
}

void lang::StructType::onScope()
{
    for (auto& member : members_) { member->setScope(scope()); }
}

bool lang::StructType::validateDefinition(ValidationLogger& validation_logger) const
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
        valid &= member->validate(validation_logger);

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
    return "struct(" + name() + ")";
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

std::vector<lang::TypeDefinition*> lang::StructType::getDependencies() const
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

bool lang::StructType::hasMember(const lang::Identifier& name)
{
    return member_map_.contains(name);
}

lang::ResolvingHandle<lang::Type> lang::StructType::getMemberType(const lang::Identifier& name)
{
    return member_map_.at(name).get().type();
}

bool lang::StructType::validateMemberAccess(const lang::Identifier& name, ValidationLogger& validation_logger) const
{
    if (member_map_.at(name).get().access() == AccessModifier::PRIVATE_ACCESS)
    {
        validation_logger.logError("Cannot access private member '" + name + "'", name.location());
        return false;
    }

    return true;
}

std::shared_ptr<lang::Value> lang::StructType::buildMemberAccess(std::shared_ptr<Value>  value,
                                                                 const lang::Identifier& name,
                                                                 CompileContext*         context)
{
    lang::ResolvingHandle<lang::Type> return_type = lang::ReferenceType::get(getMemberType(name));

    auto&                             member       = member_map_.at(name);
    int32_t                           member_index = member_indices_[name];
    lang::ResolvingHandle<lang::Type> member_type  = member.get().type();

    llvm::Value* struct_ptr;

    if (value->type()->isReferenceType())
    {
        value->buildContentValue(context);
        struct_ptr = value->getContentValue();
    }
    else
    {
        value->buildNativeValue(context);
        struct_ptr = value->getNativeValue();
    }

    llvm::Value* member_ptr   = buildGetElementPointer(struct_ptr, member_index, context);
    llvm::Value* native_value = lang::Values::contentToNative(return_type, member_ptr, context);

    return std::make_shared<lang::WrappedNativeValue>(return_type, native_value);
}

void lang::StructType::buildSingleDefaultInitializerDefinition(llvm::Value* ptr, CompileContext* context)
{
    auto size = static_cast<int32_t>(members_.size());

    for (int32_t index = 0; index < size; index++)
    {
        llvm::Value* member_ptr = buildGetElementPointer(ptr, index, context);
        members_[index]->buildInitialization(member_ptr, context);
    }
}

void lang::StructType::buildSingleCopyInitializerDefinition(llvm::Value*    dts_ptr,
                                                            llvm::Value*    src_ptr,
                                                            CompileContext* context)
{
    auto size = static_cast<int32_t>(members_.size());

    for (int32_t index = 0; index < size; index++)
    {
        llvm::Value* dst_member_ptr = buildGetElementPointer(dts_ptr, index, context);
        llvm::Value* src_member_ptr = buildGetElementPointer(src_ptr, index, context);
        members_[index]->type()->buildCopyInitializer(dst_member_ptr, src_member_ptr, context);
    }
}

llvm::Value* lang::StructType::buildGetElementPointer(llvm::Value*    struct_ptr,
                                                      int32_t         member_index,
                                                      CompileContext* context)
{
    return context->ir()->CreateStructGEP(getContentType(*context->llvmContext()),
                                          struct_ptr,
                                          member_index,
                                          struct_ptr->getName() + ".gep");
}
