#include "Member.h"

#include "compiler/CompileContext.h"
#include "lang/construct/constant/Constant.h"
#include "lang/construct/value/Value.h"
#include "lang/scope/Scope.h"
#include "lang/utility/Values.h"
#include "validation/ValidationLogger.h"

lang::Member::Member(lang::AccessModifier                access,
                     lang::Identifier                    name,
                     lang::ResolvingHandle<lang::Type>   type,
                     lang::Assigner                      assigner,
                     Optional<Owned<ConstantExpression>> constant_init,
                     lang::Location                      location,
                     lang::Location                      type_location)
    : access_(access)
    , name_(name)
    , type_(type)
    , assigner_(assigner)
    , constant_init_(std::move(constant_init))
    , location_(location)
    , type_location_(type_location)
{}

lang::AccessModifier lang::Member::access() const
{
    return access_;
}

lang::Identifier const& lang::Member::name() const
{
    return name_;
}

lang::ResolvingHandle<lang::Type> lang::Member::type()
{
    return type_;
}

lang::Type const& lang::Member::type() const
{
    return type_;
}

lang::Assigner lang::Member::assigner() const
{
    return assigner_;
}

lang::Location lang::Member::location() const
{
    return location_;
}

lang::Location lang::Member::typeLocation() const
{
    return type_location_;
}

void lang::Member::setScope(lang::Scope* scope)
{
    scope->addType(type());
    if (constant_init_.hasValue()) { constant_init_.value()->type(); }
}

bool lang::Member::validate(ValidationLogger& validation_logger) const
{
    if (!type_->validate(validation_logger, location())) return false;

    if (constant_init_.hasValue() && assigner_ != lang::Assigner::COPY_ASSIGNMENT)
    {
        validation_logger.logError("Only copy assignment currently supported for member initializers", location());
        return false;
    }

    if (constant_init_.hasValue())
    {
        if (!constant_init_.value()->validate(validation_logger)) return false;

        if (!lang::Type::areSame(type(), constant_init_.value()->type()))
        {
            validation_logger.logError("Member initializer with type "
                                           + constant_init_.value()->type().getAnnotatedName()
                                           + " must be of member type " + type().getAnnotatedName(),
                                       constant_init_.value()->location());
            return false;
        }
    }

    return true;
}

llvm::Constant* lang::Member::getConstantInitializer(llvm::Module& m) const
{
    if (constant_init_.hasValue()) { return getInitialValue(m); }
    else { return type().getDefaultContent(m); }
}

void lang::Member::buildInitialization(llvm::Value* ptr, CompileContext& context)
{
    if (constant_init_.hasValue())
    {
        llvm::Value* content   = getInitialValue(*context.module());
        llvm::Value* value_ptr = lang::values::contentToNative(type(), content, context);

        type()->buildCopyInitializer(ptr, value_ptr, context);
    }
    else { type()->buildDefaultInitializer(ptr, context); }
}

llvm::Constant* lang::Member::getInitialValue(llvm::Module& m) const
{
    if (!initial_value_)
    {
        // The llvm constant does not allow to change the ance constant.
        Shared<lang::Constant> constant = const_cast<Member*>(this)->constant_init_.value()->getConstantValue();
        constant->buildContentConstant(&m);
        initial_value_ = constant->getContentConstant();
    }

    return initial_value_;
}

void lang::Member::expand()
{
    type_ = type_->createUndefinedClone();
}
