#include "IntrinsicsRunner.h"

#include "ValueExtensions.h"
#include "ance/bbt/IntrinsicSignature.h"

ance::cet::IntrinsicsRunner::IntrinsicsRunner(sources::SourceTree&                              source_tree,
                                              core::Reporter&                                   reporter,
                                              bbt::TypeContext&                                 type_context,
                                              std::function<void(std::filesystem::path const&)> include)
    : source_tree_(source_tree)
    , reporter_(reporter)
    , type_context_(type_context)
    , include_(std::move(include))
{}

bool ance::cet::IntrinsicsRunner::Result::isPending() const
{
    return pending_resolution.hasValue();
}

bool ance::cet::IntrinsicsRunner::Result::isFailed() const
{
    return !return_value_.hasValue() && !pending_resolution.hasValue();
}

ance::cet::PendingResolution const& ance::cet::IntrinsicsRunner::Result::getPending() const
{
    assert(isPending());
    return pending_resolution.value();
}

ance::utility::Shared<ance::bbt::Value> ance::cet::IntrinsicsRunner::Result::getResult()
{
    assert(!isPending() && return_value_.hasValue());
    return return_value_.value();
}

ance::cet::IntrinsicsRunner::Result ance::cet::IntrinsicsRunner::run(core::Intrinsic const&                      intrinsic,
                                                                     utility::List<utility::Shared<bbt::Value>>& arguments,
                                                                     core::Location const&                       location)
{
    auto [signature, return_type] = bbt::getIntrinsicSignature(intrinsic, type_context_);

    state_ = State {.location             = location,
                    .arguments            = &arguments,
                    .expected_return_type = return_type,
                    .return_value_        = std::nullopt,
                    .pending_resolution   = std::nullopt};

    if (signature.isVariadic())
    {
        assert(arguments.size() >= signature.parameters().size());
        for (size_t index = 0; index < signature.parameters().size(); index++) assert(*arguments[index]->type() == *signature.parameters()[index].type);
    }
    else
    {
        assert(arguments.size() == signature.parameters().size());
        for (size_t index = 0; index < arguments.size(); index++) assert(*arguments[index]->type() == *signature.parameters()[index].type);
    }

    switch (intrinsic.value())
    {
        case core::Intrinsic::NO_OPERATION:
            runNoOp();
            break;
        case core::Intrinsic::DECLARE:
            runDeclare();
            break;
        case core::Intrinsic::RESOLVE:
            runResolve();
            break;
        case core::Intrinsic::ERASE:
            runErase();
            break;
        case core::Intrinsic::GET_PARENT:
            runGetParent();
            break;
        case core::Intrinsic::LOG:
            runLog();
            break;
        case core::Intrinsic::B_2_STR:
            runB2Str();
            break;
        case core::Intrinsic::INCLUDE:
            runInclude();
            break;
        case core::Intrinsic::CALL_INTRINSIC:
            runCallIntrinsic();
            break;
    }

    assert(state_.return_value_.hasValue() || state_.pending_resolution.hasValue() || state_.aborted);

    Result result {.return_value_ = std::move(state_.return_value_), .pending_resolution = std::move(state_.pending_resolution)};

    state_ = State {};

    return result;
}

void ance::cet::IntrinsicsRunner::runNoOp()
{
    // Do nothing.
}

void ance::cet::IntrinsicsRunner::runDeclare()
{
    Scope&                     scope      = state_.arguments->at(0)->as<ScopeRef>().value();
    core::Identifier const&    identifier = state_.arguments->at(1)->as<bbt::Identifier>().value();
    bool const                 is_final   = state_.arguments->at(2)->as<bbt::Bool>().value();
    utility::Shared<bbt::Type> type       = state_.arguments->at(3).cast<bbt::Type>();

    auto variable = scope.declare(identifier, type, is_final, state_.location, reporter_);

    if (variable.hasValue())
    {
        setResult(std::move(*variable));
    }
    else
    {
        abort();
    }
}

void ance::cet::IntrinsicsRunner::runResolve()
{
    Scope&                  scope      = state_.arguments->at(0)->as<ScopeRef>().value();
    core::Identifier const& identifier = state_.arguments->at(1)->as<bbt::Identifier>().value();

    auto [variable, status, reason] = scope.find(identifier);

    if (status == FindResult::Status::FOUND)
    {
        setResult(std::move(variable.value()));
    }
    else
    {
        setPending(PendingResolution {identifier, reason});
    }
}

void ance::cet::IntrinsicsRunner::runErase()
{
    Scope&                  scope      = state_.arguments->at(0)->as<ScopeRef>().value();
    core::Identifier const& identifier = state_.arguments->at(1)->as<bbt::Identifier>().value();

    EraseResult result = scope.erase(identifier);

    switch (result)
    {
        case EraseResult::OK:
            setResult(bbt::Unit::make(type_context_));
            break;

        case EraseResult::NOT_FOUND:
            setPending(PendingResolution {identifier, FindResult::NotFound {}});
            break;

        case EraseResult::IS_OUTER:
            reporter_.error(identifier.location()) << "Cannot erase " << identifier << " because it is declared in an outer scope";
            abort();
            break;
        case EraseResult::IS_NOT_ORDERED:
            reporter_.error(state_.location) << "Cannot erase in an un-ordered scope";
            abort();
            break;
    }
}

void ance::cet::IntrinsicsRunner::runGetParent()
{
    Scope const& scope = state_.arguments->at(0)->as<ScopeRef>().value();

    if (scope.parent() == nullptr)
    {
        reporter_.error(state_.location) << "Scope has no parent";
        abort();
        return;
    }

    setResult(ScopeRef::make(*scope.parent(), type_context_));
}

void ance::cet::IntrinsicsRunner::runLog()
{
    std::string const&    value = state_.arguments->at(0)->as<bbt::String>().value();
    core::Location const& loc   = state_.arguments->at(1)->as<bbt::Location>().value();

    reporter_.info(value, loc);

    setResult(bbt::Unit::make(type_context_));
}

void ance::cet::IntrinsicsRunner::runB2Str()
{
    bool const value = state_.arguments->at(0)->as<bbt::Bool>().value();

    setResult(bbt::String::make(value ? "true" : "false", type_context_));
}

void ance::cet::IntrinsicsRunner::runInclude()
{
    std::string const&    file     = state_.arguments->at(0)->as<bbt::String>().value();
    core::Location const& location = state_.arguments->at(1)->as<bbt::Location>().value();

    std::filesystem::path const path = source_tree_.getFile(location.fileIndex()).getDirectory() / file;

    include_(path);

    setResult(bbt::Unit::make(type_context_));
}

void ance::cet::IntrinsicsRunner::runCallIntrinsic()
{
    std::string const& name = state_.arguments->at(0)->as<bbt::String>().value();

    std::optional<core::Intrinsic> target = core::Intrinsic::fromString(name);
    if (!target.has_value())
    {
        reporter_.error(state_.location) << "Unknown intrinsic: '" << name << "'";
        abort();
        return;
    }

    utility::List<utility::Shared<bbt::Value>> arguments;
    for (size_t index = 1; index < state_.arguments->size(); index++)
        arguments.emplace_back(state_.arguments->at(index));

    State outer_state = std::move(state_);
    Result inner_result = run(target.value(), arguments, outer_state.location);
    state_ = std::move(outer_state);

    if (inner_result.isFailed())
    {
        abort();
    }
    else if (inner_result.isPending())
    {
        setPending(inner_result.getPending());
    }
    else
    {
        // todo: currently we cannot handle the any result type safely, which is why we do not use setResult here
        state_.return_value_ = inner_result.getResult();
    }
}

void ance::cet::IntrinsicsRunner::setResult(utility::Shared<bbt::Value> value)
{
    assert(*value->type() == **state_.expected_return_type);

    assert(!state_.return_value_.hasValue());
    assert(!state_.pending_resolution.hasValue());
    assert(!state_.aborted);

    state_.return_value_ = std::move(value);
}

void ance::cet::IntrinsicsRunner::setPending(PendingResolution pending)
{
    assert(!state_.return_value_.hasValue());
    assert(!state_.pending_resolution.hasValue());
    assert(!state_.aborted);

    state_.pending_resolution = std::move(pending);
}

void ance::cet::IntrinsicsRunner::abort()
{
    assert(!state_.return_value_.hasValue());
    assert(!state_.pending_resolution.hasValue());
    assert(!state_.aborted);

    state_.aborted = true;
}
