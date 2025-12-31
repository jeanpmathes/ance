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

    assert(arguments.size() == signature.parameters().size());
    for (size_t i = 0; i < arguments.size(); ++i) assert(arguments[i]->type()->isAssignableTo(*signature.parameters()[i].type));

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
    }

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

    utility::Optional<utility::Shared<bbt::Value>> variable = scope.find(identifier);

    if (variable.hasValue())
    {
        setResult(std::move(*variable));
    }
    else
    {
        setPending(identifier);
    }
}

void ance::cet::IntrinsicsRunner::runGetParent()
{
    Scope const& scope = state_.arguments->at(0)->as<ScopeRef>().value();

    if (scope.parent() == nullptr)
    {
        reporter_.error("Scope has no parent", state_.location);
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

void ance::cet::IntrinsicsRunner::setResult(utility::Shared<bbt::Value> value)
{
    assert(value->type()->isAssignableTo(**state_.expected_return_type));

    assert(!state_.return_value_.hasValue());
    assert(!state_.pending_resolution.hasValue());

    state_.return_value_ = std::move(value);
}

void ance::cet::IntrinsicsRunner::setPending(core::Identifier const& identifier)
{
    assert(!state_.return_value_.hasValue());
    assert(!state_.pending_resolution.hasValue());

    state_.pending_resolution = PendingResolution {identifier};
}

void ance::cet::IntrinsicsRunner::abort()
{
    assert(!state_.return_value_.hasValue());
    assert(!state_.pending_resolution.hasValue());

    state_.return_value_      = std::nullopt;
    state_.pending_resolution = std::nullopt;
}
