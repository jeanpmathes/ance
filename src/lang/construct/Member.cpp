#include "Member.h"

#include "lang/scope/Scope.h"
#include "validation/ValidationLogger.h"
#include "lang/construct/value/Value.h"
#include "lang/construct/constant/Constant.h"
#include "compiler/CompileContext.h"

lang::Member::Member(lang::AccessModifier                access,
                     lang::Identifier                    name,
                     lang::ResolvingHandle<lang::Type>   type,
                     lang::Assigner                      assigner,
                     std::unique_ptr<ConstantExpression> constant_init,
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

const lang::Identifier& lang::Member::name() const
{
    return name_;
}

lang::ResolvingHandle<lang::Type> lang::Member::type() const
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
}

bool lang::Member::validate(ValidationLogger& validation_logger) const
{
    if (!type_->validate(validation_logger, location())) return false;

    if (constant_init_ && assigner_ != lang::Assigner::COPY_ASSIGNMENT)
    {
        validation_logger.logError("Only copy assignment currently supported for member initializers", location());
        return false;
    }

    if (constant_init_)
    {
        if (!constant_init_->validate(validation_logger)) return false;

        if (!lang::Type::areSame(type(), constant_init_->type()))
        {
            validation_logger.logError("Member initializer with type " + constant_init_->type()->getAnnotatedName()
                                           + " must be of member type " + type()->getAnnotatedName(),
                                       constant_init_->location());
            return false;
        }
    }

    return true;
}

llvm::Constant* lang::Member::getConstantInitializer(llvm::Module& m) const
{
    if (constant_init_)
    {
        if (!initial_value_)
        {
            std::shared_ptr<lang::Constant> constant = constant_init_->getConstantValue();
            constant->buildContentConstant(&m);
            initial_value_ = constant->getContentConstant();
        }

        return initial_value_;
    }
    else {
        return type()->getDefaultContent(m);
    }
}
