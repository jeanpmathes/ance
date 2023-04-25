#include "Description.h"

#include "lang/ApplicationVisitor.h"
#include "lang/utility/Storage.h"

#include "lang/construct/descriptions/AliasDescription.h"
#include "lang/construct/descriptions/FunctionDescription.h"
#include "lang/construct/descriptions/StructDescription.h"
#include "lang/construct/descriptions/VariableDescription.h"

lang::Description::Description(lang::Accessibility accessibility) : accessibility_(accessibility) {}

lang::Accessibility lang::Description::access() const
{
    return accessibility_;
}

void lang::Description::setScope(lang::Scope& scope)
{
    assert(scope_ == nullptr);
    scope_ = &scope;
}

void lang::Description::initialize(lang::Scope& scope)
{
    setScope(scope);
    performInitialization();
}

void lang::Description::resolve() {}
void lang::Description::postResolve() {}

lang::Scope& lang::Description::scope()
{
    assert(scope_ != nullptr);
    return *scope_;
}

lang::Scope const& lang::Description::scope() const
{
    assert(scope_ != nullptr);
    return *scope_;
}

bool lang::Description::isImported() const
{
    return accessibility_.isImported();
}

enum DescriptionType : uint8_t
{
    INVALID,
    FUNCTION,
    GLOBAL_VARIABLE,
    ALIAS,
    STRUCT
};

static DescriptionType getType(lang::Description* description)
{
    assert(description != nullptr);
    DescriptionType type = INVALID;

    if (dynamic_cast<lang::FunctionDescription*>(description) != nullptr) { type = FUNCTION; }
    else if (dynamic_cast<lang::VariableDescription*>(description) != nullptr) { type = GLOBAL_VARIABLE; }
    else if (dynamic_cast<lang::AliasDescription*>(description) != nullptr) { type = ALIAS; }
    else if (dynamic_cast<lang::StructDescription*>(description) != nullptr) { type = STRUCT; }
    else { assert(false); }

    return type;
}

static lang::Description* createDescription(DescriptionType type, lang::Context& context)
{
    lang::Description* description = nullptr;

    switch (type)
    {
        case FUNCTION:
            description = new lang::FunctionDescription(context.isCurrentDescriptionSourcePublic());
            break;
        case GLOBAL_VARIABLE:
            description = new lang::VariableDescription(context.isCurrentDescriptionSourcePublic());
            break;
        case ALIAS:
            description = new lang::AliasDescription(context.isCurrentDescriptionSourcePublic());
            break;
        case STRUCT:
            description = new lang::StructDescription(context.isCurrentDescriptionSourcePublic());
            break;
        default:
            assert(false);
    }

    return description;
}

void lang::synchronize(lang::Description** description, Storage& storage)
{
    uint8_t type;

    if (storage.isWriting()) { type = getType(*description); }

    storage.sync(type);

    if (storage.isReading())
    {
        lang::Context* context = std::any_cast<lang::Context*>(storage.data_);
        *description           = createDescription(static_cast<DescriptionType>(type), *context);
    }

    (*description)->sync(storage);
}
