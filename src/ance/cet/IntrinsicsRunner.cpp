#include "IntrinsicsRunner.h"

#include "ValueExtensions.h"

ance::cet::IntrinsicsRunner::IntrinsicsRunner(sources::SourceTree&                                                                    source_tree,
                                              core::Reporter&                                                                         reporter,
                                              std::function<utility::Optional<utility::Shared<bbt::Value>>(core::Identifier const&)> provide,
                                              std::function<void(std::filesystem::path const&)>                                       include)
    : source_tree_(source_tree)
    , reporter_(reporter)
    , provide_(std::move(provide))
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

ance::cet::IntrinsicsRunner::Result ance::cet::IntrinsicsRunner::run(core::Intrinsic const&                             intrinsic,
                                                                                                   utility::List<utility::Shared<bbt::Value>> const& arguments,
                                                                                                   core::Location const&                              location)
{
    state_ = State
    {
        .location = location,
        .arguments = &arguments,
        .expected_return_type = &intrinsic.returnType(),
        .return_value_ = std::nullopt,
        .pending_resolution = std::nullopt
    };

    this->visit(intrinsic);

    Result result
    {
        .return_value_ = std::move(state_.return_value_),
        .pending_resolution = std::move(state_.pending_resolution)
    };

    state_ = State{};

    return result;
}

void ance::cet::IntrinsicsRunner::visit(core::Dynamic const& dynamic)
{
    reporter_.error("Unsupported intrinsic '" + dynamic.identifier() + "'", state_.location);
}

void ance::cet::IntrinsicsRunner::visit(core::NoOp const&)
{
    // Do nothing.
}

void ance::cet::IntrinsicsRunner::visit(core::Declare const&)
{
    assert(state_.arguments->size() == 4);
    assert(state_.arguments->at(0)->type() == core::Type::Scope());
    assert(state_.arguments->at(1)->type() == core::Type::Ident());
    assert(state_.arguments->at(2)->type() == core::Type::Bool());
    assert(state_.arguments->at(3)->type() == core::Type::Self());

    Scope&                  scope      = state_.arguments->at(0)->as<ScopeValue>().value();
    core::Identifier const& identifier = state_.arguments->at(1)->as<bbt::IdentifierValue>().value();
    bool const              is_final   = state_.arguments->at(2)->as<bbt::BoolValue>().value();
    core::Type const&       type       = state_.arguments->at(3)->as<bbt::TypeValue>().value();

    auto variable = scope.declare(identifier, type, is_final, state_.location, reporter_);

    if (variable.hasValue()) { setResult(std::move(*variable)); }
    else { abort(); }
}

void ance::cet::IntrinsicsRunner::visit(core::Resolve const&)
{
    assert(state_.arguments->size() == 2);
    assert(state_.arguments->at(0)->type() == core::Type::Scope());
    assert(state_.arguments->at(1)->type() == core::Type::Ident());

    Scope&            scope            = state_.arguments->at(0)->as<ScopeValue>().value();
    core::Identifier const& identifier = state_.arguments->at(1)->as<bbt::IdentifierValue>().value();

    utility::Optional<utility::Shared<bbt::Value>> variable = scope.find(identifier, provide_);

    if (variable.hasValue()) { setResult(std::move(*variable)); }
    else { setPending(identifier); }
}

void ance::cet::IntrinsicsRunner::visit(core::GetParent const&)
{
    assert(state_.arguments->size() == 1);
    assert(state_.arguments->at(0)->type() == core::Type::Scope());

    Scope const& scope = state_.arguments->at(0)->as<ScopeValue>().value();

    if (scope.parent() == nullptr)
    {
        reporter_.error("Scope has no parent", state_.location);
        abort();
        return;
    }

    setResult(ScopeValue::make(*scope.parent()));
}

void ance::cet::IntrinsicsRunner::visit(core::Log const&)
{
    assert(state_.arguments->size() == 2);
    assert(state_.arguments->at(0)->type() == core::Type::String());
    assert(state_.arguments->at(1)->type() == core::Type::Location());

    std::string const&    value = state_.arguments->at(0)->as<bbt::StringValue>().value();
    core::Location const& loc   = state_.arguments->at(1)->as<bbt::LocationValue>().value();

    reporter_.info(value, loc);

    setResult(bbt::UnitValue::make());
}

void ance::cet::IntrinsicsRunner::visit(core::B2Str const&)
{
    assert(state_.arguments->size() == 1);
    assert(state_.arguments->at(0)->type() == core::Type::Bool());

    bool const value = state_.arguments->at(0)->as<bbt::BoolValue>().value();

    setResult(bbt::StringValue::make(value ? "true" : "false"));
}

void ance::cet::IntrinsicsRunner::visit(core::Include const&)
{
    assert(state_.arguments->size() == 2);
    assert(state_.arguments->at(0)->type() == core::Type::String());
    assert(state_.arguments->at(1)->type() == core::Type::Location());

    std::string const&    file     = state_.arguments->at(0)->as<bbt::StringValue>().value();
    core::Location const& location = state_.arguments->at(1)->as<bbt::LocationValue>().value();

    std::filesystem::path const path = source_tree_.getFile(location.fileIndex()).getDirectory() / file;

    include_(path);

    setResult(bbt::UnitValue::make());
}

void ance::cet::IntrinsicsRunner::setResult(utility::Shared<bbt::Value> value)
{
    assert(value->type().isAssignableTo(*state_.expected_return_type));

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

    state_.return_value_ = std::nullopt;
    state_.pending_resolution = std::nullopt;
}
