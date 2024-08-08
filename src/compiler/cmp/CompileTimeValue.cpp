#include "CompileTimeValue.h"

#include <utility>

#include "lang/Context.h"
#include "lang/scope/Scope.h"
#include "lang/type/Type.h"

CompileTimeValue::CompileTimeValue(lang::Type const& type) : lang::Constant(type) {}

Optional<CompileTimeBuild::Address> CompileTimeValue::getHandle() const
{
    return std::nullopt;
}

Shared<CompileTimeValue> CompileTimeValue::access(size_t, Shared<CompileTimeValue>*, bool* ok, Execution& exec)
{
    *ok = false;
    return makeShared<cmp::UnitValue>(exec.ctx().getUnitType(), exec.ctx());
}

cmp::HandledValue::HandledValue(CompileTimeBuild::Address handle, lang::Type const& type, CompileTimeBuild& exec)
    : CompileTimeValue(type)
    , exec_(exec)
    , handle_(std::move(handle))
{}

Shared<lang::Constant> cmp::HandledValue::embed(Execution& exec) const
{
    return exec_.load(handle_)->embed(exec);
}

Shared<CompileTimeValue> cmp::HandledValue::withType(lang::Type const& type, lang::Context&) const
{
    return makeShared<HandledValue>(handle_, type, exec_);
}

Optional<CompileTimeBuild::Address> cmp::HandledValue::getHandle() const
{
    return handle_;
}

cmp::AddressValue::AddressValue(CompileTimeBuild::Address address, lang::Type const& type, lang::Context&)
    : CompileTimeValue(type)
    , address_(std::move(address))
{}

Shared<lang::Constant> cmp::AddressValue::embed(Execution& exec) const
{
    return exec.getNull(type());// todo: think about this
}

Shared<CompileTimeValue> cmp::AddressValue::withType(lang::Type const& type, lang::Context& new_context) const
{
    return makeShared<AddressValue>(address_, type, new_context);
}

CompileTimeBuild::Address const& cmp::AddressValue::address() const
{
    return address_;
}

cmp::ArrayValue::ArrayValue(lang::Type const&                       element_type,
                            std::vector<Shared<CompileTimeValue>>&& values,
                            lang::Context&                          context)
    : CompileTimeValue(context.getArrayType(element_type, values.size()))
    , values_(std::move(values))
{}

Shared<lang::Constant> cmp::ArrayValue::embed(Execution& exec) const
{
    std::vector<Shared<lang::Constant>> constants;
    constants.reserve(values_.size());

    for (auto const& value : values_) constants.push_back(value->embed(exec));

    return exec.getArray(std::move(constants), type());
}

Shared<CompileTimeValue> cmp::ArrayValue::withType(lang::Type const& type, lang::Context& new_context) const
{
    std::vector<Shared<CompileTimeValue>> values;
    values.reserve(values_.size());

    for (auto const& value : values_) values.push_back(value->withType(type.getElementType(), new_context));

    return makeShared<ArrayValue>(type.getElementType(), std::move(values), new_context);
}

cmp::BooleanValue::BooleanValue(bool value, lang::Context& context)
    : CompileTimeValue(context.getBooleanType())
    , value_(value)
{}

Shared<lang::Constant> cmp::BooleanValue::embed(Execution& exec) const
{
    return exec.getBoolean(value_, type());
}

Shared<CompileTimeValue> cmp::BooleanValue::withType(lang::Type const&, lang::Context& new_context) const
{
    return makeShared<BooleanValue>(value_, new_context);
}

bool cmp::BooleanValue::value() const
{
    return value_;
}

cmp::CharValue::CharValue(char32_t value, lang::Context& context)
    : CompileTimeValue(context.getCharType())
    , value_(value)
{}

Shared<lang::Constant> cmp::CharValue::embed(Execution& exec) const
{
    return exec.getCodepoint(value_);
}

Shared<CompileTimeValue> cmp::CharValue::withType(lang::Type const&, lang::Context& new_context) const
{
    return makeShared<CharValue>(value_, new_context);
}

cmp::IntegerValue::IntegerValue(llvm::APInt value, lang::Type const& type, lang::Context&)
    : CompileTimeValue(type)
    , value_(std::move(value))
{}

Shared<lang::Constant> cmp::IntegerValue::embed(Execution& exec) const
{
    return exec.getInteger(value_, type());
}

Shared<CompileTimeValue> cmp::IntegerValue::withType(lang::Type const& type, lang::Context& new_context) const
{
    return makeShared<IntegerValue>(value_, type, new_context);
}

llvm::APInt const& cmp::IntegerValue::value() const
{
    return value_;
}

cmp::FloatingPointValue::FloatingPointValue(llvm::APFloat value, lang::Type const& type, lang::Context&)
    : CompileTimeValue(type)
    , value_(std::move(value))
{}

Shared<lang::Constant> cmp::FloatingPointValue::embed(Execution& exec) const
{
    return exec.getFloatingPoint(value_, type());
}

Shared<CompileTimeValue> cmp::FloatingPointValue::withType(lang::Type const& type, lang::Context& new_context) const
{
    return makeShared<FloatingPointValue>(value_, type, new_context);
}

llvm::APFloat const& cmp::FloatingPointValue::value() const
{
    return value_;
}

cmp::UnitValue::UnitValue(lang::Type const& type, lang::Context&) : CompileTimeValue(type) {}

Shared<lang::Constant> cmp::UnitValue::embed(Execution& exec) const
{
    return exec.getDefault(type());
}

Shared<CompileTimeValue> cmp::UnitValue::withType(lang::Type const& type, lang::Context& new_context) const
{
    return makeShared<UnitValue>(type, new_context);
}

cmp::StructValue::StructValue(lang::Type const& type, std::vector<Shared<CompileTimeValue>>&& values, lang::Context&)
    : CompileTimeValue(type)
    , values_(std::move(values))
{}

Shared<lang::Constant> cmp::StructValue::embed(Execution& exec) const
{
    std::vector<Shared<lang::Constant>> constants;
    constants.reserve(values_.size());

    for (auto const& value : values_) constants.push_back(value->embed(exec));

    return exec.getStruct(std::move(constants), type());
}

Shared<CompileTimeValue> cmp::StructValue::withType(lang::Type const& type, lang::Context& new_context) const
{
    std::vector<Shared<CompileTimeValue>> values;
    values.reserve(values_.size());

    for (auto const& value : values_) values.push_back(value->withType(type, new_context));

    return makeShared<StructValue>(type, std::move(values), new_context);
}

cmp::VectorValue::VectorValue(lang::Type const&                       element_type,
                              std::vector<Shared<CompileTimeValue>>&& values,
                              lang::Context&                          context)
    : CompileTimeValue(context.getVectorType(element_type, values.size()))
    , values_(std::move(values))
{}

Shared<lang::Constant> cmp::VectorValue::embed(Execution& exec) const
{
    std::vector<Shared<lang::Constant>> constants;
    constants.reserve(values_.size());

    for (auto const& value : values_) constants.push_back(value->embed(exec));

    return exec.getVector(std::move(constants), type());
}

Shared<CompileTimeValue> cmp::VectorValue::withType(lang::Type const& type, lang::Context& new_context) const
{
    std::vector<Shared<CompileTimeValue>> values;
    values.reserve(values_.size());

    for (auto const& value : values_) values.push_back(value->withType(type.getElementType(), new_context));

    return makeShared<VectorValue>(type.getElementType(), std::move(values), new_context);
}

Shared<CompileTimeValue> cmp::VectorValue::get(size_t index)
{
    return values_.at(index);
}

size_t cmp::VectorValue::size() const
{
    return values_.size();
}
