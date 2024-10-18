#include "CompileTimeBuild.h"

#include <variant>

#include <llvm/ADT/APSInt.h>

#include "compiler/Unit.h"
#include "compiler/cmp/CompileTimeBuilder.h"
#include "compiler/cmp/CompileTimeValue.h"
#include "compiler/native/NativeBuild.h"
#include "lang/construct/LocalVariable.h"
#include "lang/type/ArrayType.h"
#include "lang/type/SizeType.h"
#include "lang/type/StructType.h"
#include "lang/type/Type.h"
#include "lang/type/VectorType.h"
#include "lang/utility/Erased.h"

namespace
{
    llvm::fltSemantics const& getFloatSemantics(lang::Type const& type)
    {
        if (type.isFloatingPointType(16)) return llvm::APFloat::IEEEhalf();
        if (type.isFloatingPointType(32)) return llvm::APFloat::IEEEsingle();
        if (type.isFloatingPointType(64)) return llvm::APFloat::IEEEdouble();
        if (type.isFloatingPointType(128)) return llvm::APFloat::IEEEquad();

        throw std::logic_error("Invalid floating point type");
    }

    template<typename I, typename O>
    Shared<CompileTimeValue> apply(Shared<CompileTimeValue>                                      value,
                                   lang::Type const&                                             result_type,
                                   lang::Context&                                                context,
                                   std::function<Shared<O>(Shared<I>, lang::Type const&)> const& fn)
    {
        if (value->type().isVectorType())
        {
            Shared<cmp::VectorValue> vector = value.cast<cmp::VectorValue>();

            std::vector<Shared<CompileTimeValue>> elements;
            elements.reserve(vector->size());

            for (size_t index = 0; index < vector->size(); index++)
            {
                elements.emplace_back(fn(vector->get(index).cast<I>(), result_type.getElementType()));
            }

            return makeShared<cmp::VectorValue>(result_type.getElementType(), std::move(elements), context);
        }

        return fn(value.cast<I>(), result_type);
    }

    template<typename I1, typename I2, typename O>
    Shared<CompileTimeValue> apply(Shared<CompileTimeValue> value1,
                                   Shared<CompileTimeValue> value2,
                                   lang::Type const&        result_type,
                                   lang::Context&           context,
                                   std::function<Shared<O>(Shared<I1>, Shared<I2>, lang::Type const&)> const& fn)
    {
        if (value1->type().isVectorType() && value2->type().isVectorType())
        {
            Shared<cmp::VectorValue> vector1 = value1.cast<cmp::VectorValue>();
            Shared<cmp::VectorValue> vector2 = value2.cast<cmp::VectorValue>();

            size_t size = vector1->size();
            assert(size == vector2->size());

            std::vector<Shared<CompileTimeValue>> elements;
            elements.reserve(size);

            for (size_t index = 0; index < size; index++)
            {
                elements.emplace_back(
                    fn(vector1->get(index).cast<I1>(), vector2->get(index).cast<I2>(), result_type.getElementType()));
            }

            return makeShared<cmp::VectorValue>(result_type.getElementType(), std::move(elements), context);
        }

        return fn(value1.cast<I1>(), value2.cast<I2>(), result_type);
    }

    using INT  = cmp::IntegerValue;
    using FP   = cmp::FloatingPointValue;
    using BOOL = cmp::BooleanValue;

    CompileTimeBuild::Address allocate(CompileTimeBuild::Address::Location location,
                                       CompileTimeBuild::Memory&           memory,
                                       lang::Type const&                   type,
                                       size_t                              count,
                                       CompileTimeBuild&                   exec)
    {
        size_t memory_index = memory.size();
        memory.emplace_back();

        Shared<CompileTimeValue> default_value = exec.getDefault(type).cast<CompileTimeValue>();

        for (size_t i = 0; i < count; ++i) { memory[memory_index].emplace_back(default_value); }

        return {location, memory_index};
    }
}

CompileTimeBuild::CompileTimeBuild(Unit& unit, Runtime& runtime, NativeBuild& native)
    : Execution(unit, runtime)
    , context_(unit.globalScope().context())
    , native_(native)
{
    native_.setCMP(this);
}

void CompileTimeBuild::setActiveVisitor(CompileTimeBuilder* visitor)
{
    visitor_ = visitor;
}

Shared<lang::Constant> CompileTimeBuild::getDefault(lang::Type const& type)
{
    return getTypeInformation(type).default_value;
}

Shared<lang::Constant> CompileTimeBuild::getCodepointString(std::u32string const& string)
{
    auto iterator = codepoint_strings_.find(string);
    if (iterator == codepoint_strings_.end())
    {
        std::vector<Shared<CompileTimeValue>> codepoints;
        codepoints.reserve(string.size());

        for (char32_t codepoint : string) { codepoints.emplace_back(makeShared<cmp::CharValue>(codepoint, context_)); }

        Shared<CompileTimeValue> constant =
            makeShared<cmp::ArrayValue>(context_.getCharType(), std::move(codepoints), context_);
        std::tie(iterator, std::ignore) = codepoint_strings_.emplace(string, std::move(constant));
    }

    auto& [_, constant] = *iterator;
    return constant;
}

Shared<lang::Constant> CompileTimeBuild::getByteString(std::string const& string)
{
    auto iterator = byte_strings_.find(string);
    if (iterator == byte_strings_.end())
    {
        lang::ResolvingHandle<lang::Type> byte_type = context_.getFixedWidthIntegerType(8, false);

        std::vector<Shared<CompileTimeValue>> codepoints;
        codepoints.reserve(string.size());

        for (char byte : string)
        {
            llvm::APInt value(8, static_cast<uint64_t>(byte), false);
            codepoints.emplace_back(makeShared<cmp::IntegerValue>(value, byte_type, context_));
        }

        Shared<CompileTimeValue> constant = makeShared<cmp::ArrayValue>(byte_type, std::move(codepoints), context_);
        std::tie(iterator, std::ignore)   = byte_strings_.emplace(string, std::move(constant));
    }

    auto& [_, constant] = *iterator;
    return constant;
}

Shared<lang::Constant> CompileTimeBuild::getCString(std::string const& string)
{
    auto iterator = c_strings_.find(string);
    if (iterator == c_strings_.end())
    {
        lang::ResolvingHandle<lang::Type> byte_type   = context_.getFixedWidthIntegerType(8, false);
        lang::ResolvingHandle<lang::Type> string_type = context_.getPointerType(byte_type);

        Address buffer_address = allocateGlobal(byte_type, string.size() + 1);

        for (size_t i = 0; i < string.size(); ++i)
        {
            llvm::APInt value(8, static_cast<uint64_t>(string[i]), false);
            store(buffer_address + i, makeShared<cmp::IntegerValue>(value, byte_type, context_));
        }

        llvm::APInt zero(8, 0, false);
        store(buffer_address + string.size(), makeShared<cmp::IntegerValue>(zero, byte_type, context_));

        Shared<CompileTimeValue> pointer_value = makeShared<cmp::AddressValue>(buffer_address, string_type, context_);
        std::tie(iterator, std::ignore)        = c_strings_.emplace(string, std::move(pointer_value));
    }

    auto& [_, constant] = *iterator;
    return constant;
}

Shared<lang::Constant> CompileTimeBuild::getSizeN(std::size_t size)
{
    assert(size < (1ull << lang::SizeType::MINIMUM_BIT_SIZE));

    lang::ResolvingHandle<lang::Type> size_type = ctx().getSizeType();
    size_t                            bit_size  = size_type->isIntegerType()->getNativeBitSize();
    llvm::APInt                       size_constant(static_cast<unsigned>(bit_size), size, false);

    return makeShared<cmp::IntegerValue>(size_constant, size_type, context_);
}

Shared<lang::Constant> CompileTimeBuild::getDiffN(std::ptrdiff_t diff)
{
    assert(static_cast<size_t>(std::abs(diff)) < (1ull << lang::SizeType::MINIMUM_BIT_SIZE));

    lang::ResolvingHandle<lang::Type> diff_type = ctx().getDiffType();
    size_t                            bit_size  = diff_type->isIntegerType()->getNativeBitSize();
    llvm::APInt                       diff_constant(static_cast<unsigned>(bit_size), static_cast<uint64_t>(diff), true);

    return makeShared<cmp::IntegerValue>(diff_constant, diff_type, context_);
}

Shared<lang::Constant> CompileTimeBuild::getSizeOf(lang::Type const& type)
{
    uint64_t const size = native_.llvmModule().getDataLayout().getTypeAllocSize(native_.llvmType(type));
    return getSizeN(size);
}

Shared<lang::Constant> CompileTimeBuild::getN(std::variant<uint64_t, double> n, lang::Type const& type)
{
    assert(type.isXOrVectorOfX([](auto& t) { return t.isIntegerType() || t.isFloatingPointType(); }));

    Optional<Shared<lang::Constant>> n_constant;

    if (type.isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }))
    {
        uint64_t const n_integer =
            std::holds_alternative<uint64_t>(n) ? std::get<uint64_t>(n) : static_cast<uint64_t>(std::get<double>(n));

        llvm::APInt n_int(static_cast<unsigned>(type.isIntegerType()->getNativeBitSize()),
                          n_integer,
                          type.isIntegerType()->isSigned());
        return getInteger(n_int, type);
    }
    else if (type.isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }))
    {
        double const n_floating =
            std::holds_alternative<uint64_t>(n) ? static_cast<double>(std::get<uint64_t>(n)) : std::get<double>(n);

        llvm::APFloat               n_float(n_floating);
        llvm::APFloat::roundingMode rm = llvm::APFloat::rmNearestTiesToEven;
        bool                        loss;

        n_float.convert(getFloatSemantics(type), rm, &loss);

        return getFloatingPoint(n_float, type);
    }
    else throw std::logic_error("Invalid type");
}

Shared<lang::Constant> CompileTimeBuild::getNull(lang::Type const& type)
{
    assert(type.isPointerType() || type.isBufferType() || type.isOpaquePointerType());

    return makeShared<cmp::AddressValue>(Address::NULL_ADDRESS, type, context_);
}

Shared<lang::Constant> CompileTimeBuild::getBoolean(bool boolean, lang::Type const& type)
{
    assert(type.isXOrVectorOfX([](auto& t) { return t.isBooleanType(); }));

    Shared<CompileTimeValue> constant = makeShared<cmp::BooleanValue>(boolean, context_);

    if (type.isVectorType()) { return getSplatVector(constant, type); }

    return constant;
}

Shared<lang::Constant> CompileTimeBuild::getInteger(llvm::APInt integer, lang::Type const& type)
{
    assert(type.isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));

    Shared<CompileTimeValue> constant = makeShared<cmp::IntegerValue>(integer, type, context_);

    if (type.isVectorType()) { return getSplatVector(constant, type); }

    return constant;
}

Shared<lang::Constant> CompileTimeBuild::getFloatingPoint(llvm::APFloat floating_point, lang::Type const& type)
{
    assert(type.isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));

    Shared<CompileTimeValue> constant = makeShared<cmp::FloatingPointValue>(floating_point, type, context_);

    if (type.isVectorType()) { return getSplatVector(constant, type); }

    return constant;
}

Shared<lang::Constant> CompileTimeBuild::getCodepoint(char32_t codepoint)
{
    return makeShared<cmp::CharValue>(codepoint, context_);
}

Shared<lang::Constant> CompileTimeBuild::getArray(std::vector<Shared<lang::Constant>> values, lang::Type const& type)
{
    lang::ArrayType const* array_type = type.isArrayType();

    assert(array_type != nullptr);
    assert(values.size() == array_type->getSize().value());

    std::vector<Shared<CompileTimeValue>> elements;
    elements.reserve(values.size());

    for (Shared<lang::Constant>& value : values) { elements.emplace_back(cmpContentOf(value)); }

    return makeShared<cmp::ArrayValue>(array_type->getElementType(), std::move(elements), context_);
}

Shared<lang::Constant> CompileTimeBuild::getVector(std::vector<Shared<lang::Constant>> values, lang::Type const& type)
{
    lang::VectorType const* vector_type = type.isVectorType();

    assert(vector_type != nullptr);
    assert(values.size() == vector_type->getSize().value());

    std::vector<Shared<CompileTimeValue>> elements;
    elements.reserve(values.size());

    for (Shared<lang::Constant>& value : values) { elements.emplace_back(cmpContentOf(value)); }

    return makeShared<cmp::VectorValue>(vector_type->getElementType(), std::move(elements), context_);
}

Shared<lang::Constant> CompileTimeBuild::getStruct(std::vector<Shared<lang::Constant>> values, lang::Type const& type)
{
    lang::StructType const* struct_type = type.isStructType();

    assert(struct_type != nullptr);
    assert(values.size() == struct_type->getMemberCount());

    std::vector<Shared<CompileTimeValue>> elements;
    elements.reserve(values.size());

    for (Shared<lang::Constant>& value : values) { elements.emplace_back(cmpContentOf(value)); }

    return makeShared<cmp::StructValue>(type, std::move(elements), context_);
}

void CompileTimeBuild::registerFunction(lang::Function const&)
{
    // Nothing to do.
}

CompileTimeBuild::CmpFnCtx::CmpFnCtx(lang::Function const&            fn,
                                     CompileTimeBuild&                build,
                                     std::vector<Shared<lang::Value>> arguments)
    : function_(fn)
    , build_(build)
    , arguments_(std::move(arguments))
{}

Shared<lang::Value> CompileTimeBuild::CmpFnCtx::getParameterValue(size_t index)
{
    return arguments_[index];
}

Execution& CompileTimeBuild::CmpFnCtx::exec()
{
    return build_;
}

lang::Function const& CompileTimeBuild::CmpFnCtx::function()
{
    return function_;
}

void CompileTimeBuild::defineFunctionBody(lang::Function const& function, std::function<void(FnCtx&)> const& builder)
{
    function_information_.emplace(&function, FunctionInformation {builder});
}

Shared<lang::Value> CompileTimeBuild::performFunctionCall(lang::Function const&            function,
                                                          std::vector<Shared<lang::Value>> arguments)
{
    FunctionInformation& function_information = getFunctionInformation(function);

    std::vector<Shared<lang::Value>> arguments_content;
    arguments_content.reserve(arguments.size());

    for (Shared<lang::Value>& argument : arguments) { arguments_content.emplace_back(cmpContentOf(argument)); }

    CmpFnCtx&           fn_ctx       = fns_.emplace(function, *this, std::move(arguments_content));
    Shared<lang::Value> return_value = getDefault(context_.getUnitType());

    function_information.body(fn_ctx);

    if (fn_ctx.return_value.hasValue()) return_value = fn_ctx.return_value.value();

    fns_.pop();

    return return_value;
}

void CompileTimeBuild::registerStruct(lang::Type const&                                 type,
                                      std::vector<std::reference_wrapper<lang::Member>> members,
                                      lang::Location)
{
    std::vector<Shared<lang::Constant>> values;
    values.reserve(members.size());

    for (lang::Member& member : members) { values.push_back(getDefault(member.type())); }

    type_information_.emplace(&type, TypeInformation {getStruct(std::move(values), type)});
}

void CompileTimeBuild::registerAlias(lang::Type const& type, lang::Location)
{
    type_information_.emplace(&type, TypeInformation {getDefault(type.getActualType())});
}

void CompileTimeBuild::registerReferenceType(lang::Type const& reference_type)
{
    // A default value does not make sense for reference types.

    type_information_.emplace(&reference_type, TypeInformation {getDefault(context_.getUnitType())});
}

void CompileTimeBuild::registerAddressType(lang::Type const& address_type)
{
    type_information_.emplace(&address_type, TypeInformation {getNull(address_type)});
}

void CompileTimeBuild::registerOpaqueAddressType(lang::Type const& opaque_address_type)
{
    type_information_.emplace(&opaque_address_type, TypeInformation {getNull(opaque_address_type)});
}

void CompileTimeBuild::registerVectorType(lang::Type const& vector_type)
{
    type_information_.emplace(&vector_type,
                              TypeInformation {getSplatVector(getDefault(vector_type.getElementType()), vector_type)});
}

void CompileTimeBuild::registerIntegerType(lang::Type const& integer_type)
{
    type_information_.emplace(&integer_type, TypeInformation {getZero(integer_type)});
}

void CompileTimeBuild::registerFloatingPointType(lang::Type const& floating_point_type)
{
    type_information_.emplace(&floating_point_type, TypeInformation {getZero(floating_point_type)});
}

void CompileTimeBuild::registerBooleanType(lang::Type const& boolean_type)
{
    type_information_.emplace(&boolean_type, TypeInformation {getBoolean(false, boolean_type)});
}

void CompileTimeBuild::registerUnitType(lang::Type const& unit_type)
{
    type_information_.emplace(&unit_type, TypeInformation {makeShared<cmp::UnitValue>(unit_type, context_)});
}

void CompileTimeBuild::registerCodepointType(lang::Type const& codepoint_type)
{
    type_information_.emplace(&codepoint_type, TypeInformation {getCodepoint(0)});
}

void CompileTimeBuild::registerArrayType(lang::Type const& array_type)
{
    size_t const array_size = array_type.isArrayType()->getSize().value();

    std::vector<Shared<lang::Constant>> values;
    values.reserve(array_size);

    for (size_t i = 0; i < array_size; ++i)
    {
        values.push_back(getDefault(array_type.isArrayType()->getElementType()));
    }

    type_information_.emplace(&array_type, TypeInformation {getArray(std::move(values), array_type)});
}

void CompileTimeBuild::declareGlobalVariable(lang::GlobalVariable const& global_variable)
{
    Address address = allocateGlobal(global_variable.type());
    global_variables_.emplace(&global_variable.self(), address);

    if (global_variable.isImported())
    {
        // todo: store the serialized value of the exported variable in the .apkg file and store it as value here
    }
    else if (global_variable.initializer() == nullptr)
    {
        store(address, cmpContentOf(getDefault(global_variable.type())));
    }
}

void CompileTimeBuild::defineGlobalVariable(lang::GlobalVariable const& global_variable)
{
    if (global_variable.isImported()) return;
    if (global_variable.initializer() == nullptr) return;

    Address address = global_variables_.at(&global_variable.self());

    Shared<lang::Value> initial_value = performFunctionCall(*global_variable.initializer(), {});
    store(address, cmpContentOf(initial_value));
}

void CompileTimeBuild::declareLocalVariable(lang::LocalVariable const& local_variable)
{
    Address address = allocateLocal(local_variable.type());
    fns_.top().variables.emplace(&local_variable.self(), address);
}

void CompileTimeBuild::defineLocalVariable(lang::LocalVariable const&,
                                           lang::Scope const&,
                                           Optional<size_t>,
                                           lang::Location)
{
    // Nothing to do.
}

Shared<lang::Value> CompileTimeBuild::computeInitializerValue(lang::LocalInitializer const& initializer)
{
    assert(initializer.hasValue());

    if (auto* parameter = std::get_if<lang::LocalParameterInitializer>(&initializer.value()))
    {
        auto [function, parameter_index] = *parameter;

        return fns_.top().getParameterValue(parameter_index);
    }

    if (auto* expression = std::get_if<std::reference_wrapper<Expression>>(&initializer.value()))
    {
        return visitor_->getV(*expression);
    }

    throw std::logic_error("Invalid initializer");
}

Shared<lang::Value> CompileTimeBuild::computeAddressOfVariable(lang::Variable const& variable)
{
    Address address;

    if (global_variables_.contains(&variable)) address = global_variables_.at(&variable);

    if (!fns_.empty() && fns_.top().variables.contains(&variable)) address = fns_.top().variables.at(&variable);

    assert(address != Address::NULL_ADDRESS);

    return makeShared<cmp::AddressValue>(address, context_.getPointerType(variable.type()), context_);
}

Shared<lang::Value> CompileTimeBuild::computeAsActualType(Shared<lang::Value> value)
{
    Shared<CompileTimeValue> cmp_value = value.cast<CompileTimeValue>();

    return cmp_value->withType(value->type().getActualType(), context_);
}

Shared<lang::Value> CompileTimeBuild::computeElementPointer(Shared<lang::Value>     sequence,
                                                            Shared<lang::Value>     index,
                                                            Execution::IndexingMode mode,
                                                            Optional<size_t>        bounds)
{
    lang::Type const& pointer_type = sequence->type();
    assert(pointer_type.isPointerType() || pointer_type.isBufferType());

    lang::Type const& sequence_type = pointer_type.getElementType();
    assert(mode != IndexingMode::SEQUENCE || (sequence_type.isArrayType() || sequence_type.isVectorType()));

    assert(index->type().isDiffType());

    // The two modes are: POINTER and SEQUENCE.
    // In POINTER mode, we are passed a value *T on which we operate.
    // In SEQUENCE mode, we are passed a value *[N x T] on which we operate.
    // In both cases, the result is a value *T.

    Optional<std::reference_wrapper<lang::Type const>> element_type;

    switch (mode)
    {
        case IndexingMode::POINTER:
        {
            // We got passed a value *T on which we operate.
            element_type = pointer_type.getElementType();
            break;
        }
        case IndexingMode::SEQUENCE:
        {
            // We got passed a value *[N x T] on which we operate.
            element_type = sequence_type.getElementType();
            break;
        }
    }

    Shared<cmp::IntegerValue> cmp_index   = cmpContentOf(index).cast<cmp::IntegerValue>();
    ptrdiff_t                 index_value = cmp_index->value().getSExtValue();

    if (bounds.hasValue())
    {
        // todo: cause compile time error if index is out of bounds, stop compilation
        // todo: also have a test for that case
    }

    Shared<cmp::AddressValue> cmp_address  = cmpContentOf(sequence).cast<cmp::AddressValue>();
    Address                   base_address = cmp_address->address();

    lang::Type const& ptr_type = ctx().getPointerType(element_type.value());
    Address           result_address;

    switch (mode)
    {
        case IndexingMode::POINTER:
        {
            result_address = base_address + index_value;
            break;
        }
        case IndexingMode::SEQUENCE:
        {
            result_address = base_address.inner(index_value);
            break;
        }
    }

    return makeShared<cmp::AddressValue>(result_address, ptr_type, context_);
}

Shared<lang::Value> CompileTimeBuild::computeMemberPointer(Shared<lang::Value>     struct_ptr,
                                                           lang::Identifier const& member_name)
{
    assert(struct_ptr->type().isPointerType());
    assert(struct_ptr->type().getElementType().isStructType());

    Shared<cmp::AddressValue> cmp_struct_ptr = cmpContentOf(struct_ptr).cast<cmp::AddressValue>();
    Address                   struct_address = cmp_struct_ptr->address();

    lang::StructType const* struct_type = struct_ptr->type().getElementType().isStructType();
    lang::Member const&     member      = struct_type->getMember(member_name);

    Address           member_address = struct_address.inner(member.index());
    lang::Type const& member_type    = member.type();

    return makeShared<cmp::AddressValue>(member_address, context_.getPointerType(member_type), context_);
}

Shared<lang::Value> CompileTimeBuild::computeAddressOf(Shared<lang::Value> value)
{
    if (value->type().isReferenceType()) { return computePointerFromReference(value); }

    return cmpAddressValueOf(value);
}

Shared<lang::Value> CompileTimeBuild::computePointerToInteger(Shared<lang::Value>)
{
    throw std::logic_error("Pointer-to-integer conversion is not supported in compile-time execution");

    // todo: forbid this at higher level, cause compile time error
}

Shared<lang::Value> CompileTimeBuild::computeIntegerToPointer(Shared<lang::Value>, lang::Type const&)
{
    throw std::logic_error("Integer-to-pointer conversion is not supported in compile-time execution");

    // todo: forbid this at higher level, cause compile time error
}

Shared<lang::Value> CompileTimeBuild::computeCastedAddress(Shared<lang::Value> address, lang::Type const& new_type)
{
    assert(address->type().isXOrVectorOfX(
        [](auto& t) { return t.isPointerType() || t.isBufferType() || t.isOpaquePointerType(); }));
    assert(new_type.isXOrVectorOfX(
        [](auto& t) { return t.isPointerType() || t.isBufferType() || t.isOpaquePointerType(); }));

    Shared<CompileTimeValue> cmp_value = cmpContentOf(address);
    return cmp_value->withType(new_type, context_);
}

Shared<lang::Value> CompileTimeBuild::computeConversionOnFP(Shared<lang::Value> value,
                                                            lang::Type const&   destination_type)
{
    assert(value->type().isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));
    assert(destination_type.isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));

    return apply<FP, FP>(cmpContentOf(value),
                         destination_type,
                         context_,
                         [this](Shared<FP> v, lang::Type const& t) -> Shared<FP> {
                             llvm::APFloat converted_value = v->value();

                             bool loss;
                             converted_value.convert(getFloatSemantics(t), llvm::APFloat::rmNearestTiesToEven, &loss);

                             return makeShared<cmp::FloatingPointValue>(converted_value, t, context_);
                         });
}

Shared<lang::Value> CompileTimeBuild::computeConversionOnI(Shared<lang::Value> value,
                                                           lang::Type const&   destination_type)
{
    assert(value->type().isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));
    assert(destination_type.isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));

    return apply<INT, INT>(cmpContentOf(value),
                           destination_type,
                           context_,
                           [this](Shared<INT> v, lang::Type const& t) -> Shared<INT> {
                               llvm::APInt converted_value = v->value();

                               auto bit_size = static_cast<unsigned>(t.isIntegerType()->getNativeBitSize());

                               if (v->type().isSigned()) { converted_value = converted_value.sextOrTrunc(bit_size); }
                               else { converted_value = converted_value.zextOrTrunc(bit_size); }

                               return makeShared<cmp::IntegerValue>(converted_value, t, context_);
                           });
}

Shared<lang::Value> CompileTimeBuild::computeConversionFP2I(Shared<lang::Value> value,
                                                            lang::Type const&   destination_type)
{
    assert(value->type().isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));
    assert(destination_type.isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));

    return apply<FP, INT>(cmpContentOf(value),
                          destination_type,
                          context_,
                          [this](Shared<FP> v, lang::Type const& t) -> Shared<INT> {
                              llvm::APFloat fp_value = v->value();

                              lang::IntegerType const* integer_type = t.isIntegerType();
                              auto bit_size  = static_cast<unsigned>(integer_type->getNativeBitSize());
                              bool is_signed = integer_type->isSigned();

                              llvm::APSInt integer_value(bit_size, !is_signed);
                              bool         is_exact;
                              fp_value.convertToInteger(integer_value, llvm::APFloat::rmTowardZero, &is_exact);

                              return makeShared<cmp::IntegerValue>(integer_value, t, context_);
                          });
}

Shared<lang::Value> CompileTimeBuild::computeConversionI2FP(Shared<lang::Value> value,
                                                            lang::Type const&   destination_type)
{
    assert(value->type().isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));
    assert(destination_type.isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));

    return apply<INT, FP>(
        cmpContentOf(value),
        destination_type,
        context_,
        [this](Shared<INT> v, lang::Type const& t) -> Shared<FP> {
            llvm::APInt              integer_value = v->value();
            lang::IntegerType const* integer_type  = t.isIntegerType();

            llvm::APFloat fp_value(getFloatSemantics(t));
            fp_value.convertFromAPInt(integer_value, integer_type->isSigned(), llvm::APFloat::rmNearestTiesToEven);

            return makeShared<cmp::FloatingPointValue>(fp_value, t, context_);
        });
}

Shared<lang::Value> CompileTimeBuild::computePointerFromReference(Shared<lang::Value> reference)
{
    assert(reference->type().isReferenceType());

    lang::Type const& pointer_type = context_.getPointerType(reference->type().getElementType());

    return reference.cast<cmp::AddressValue>()->withType(pointer_type, context_);
}

Shared<lang::Value> CompileTimeBuild::computeReferenceFromPointer(Shared<lang::Value> pointer)
{
    assert(pointer->type().isPointerType());

    lang::Type const& reference_type = context_.getReferenceType(pointer->type().getElementType());

    return pointer.cast<cmp::AddressValue>()->withType(reference_type, context_);
}

Shared<lang::Value> CompileTimeBuild::computeAddressIsNotNull(Shared<lang::Value> address)
{
    assert(address->type().isXOrVectorOfX([](auto& t) { return t.isPointerType() || t.isBufferType(); }));

    Shared<cmp::AddressValue> cmp_address = cmpContentOf(address).cast<cmp::AddressValue>();
    bool                      not_null    = cmp_address->address() != Address::NULL_ADDRESS;

    return makeShared<cmp::BooleanValue>(not_null, context_);
}

Shared<lang::Value> CompileTimeBuild::computeAddressDiff(Shared<lang::Value>, Shared<lang::Value>)
{
    throw std::logic_error("Address difference is not supported in compile-time execution");

    // todo: forbid this at higher level, cause compile time error
}

Shared<lang::Value> CompileTimeBuild::performLoadFromAddress(Shared<lang::Value> address)
{
    assert(address->type().isPointerType());
    lang::Type const& pointee_type = address->type().getElementType();

    Shared<cmp::AddressValue> cmp_address = cmpContentOf(address).cast<cmp::AddressValue>();

    return makeShared<cmp::HandledValue>(cmp_address->address(), pointee_type, *this);
}

void CompileTimeBuild::performStoreToAddress(Shared<lang::Value> address, Shared<lang::Value> value)
{
    assert(address->type().isPointerType());
    assert(lang::Type::areSame(address->type().getElementType(), value->type()));

    Shared<cmp::AddressValue> cmp_address = cmpContentOf(address).cast<cmp::AddressValue>();

    store(cmp_address->address(), cmpContentOf(value));
}

void CompileTimeBuild::performPointerIteration(Shared<lang::Value>                      pointer,
                                               Shared<lang::Value>                      count,
                                               std::function<void(Shared<lang::Value>)> body)
{
    assert(pointer->type().isPointerType());
    assert(lang::Type::areSame(count->type(), ctx().getSizeType()));
    assert(!fns_.empty());

    Shared<cmp::AddressValue> cmp_pointer  = cmpContentOf(pointer).cast<cmp::AddressValue>();
    Address                   base_address = cmp_pointer->address();

    Shared<cmp::IntegerValue> cmp_count   = cmpContentOf(count).cast<cmp::IntegerValue>();
    llvm::APInt               count_value = cmp_count->value();

    for (llvm::APInt i(count_value.getBitWidth(), 0, false); i.slt(count_value); i = i + 1)
    {
        body(makeShared<cmp::AddressValue>(base_address + i.getZExtValue(), pointer->type(), context_));
    }
}

void CompileTimeBuild::performReturn(Optional<Shared<lang::Value>> value)
{
    if (value.hasValue()) { fns_.top().return_value = cmpContentOf(value.value()); }
    else { fns_.top().return_value = makeShared<cmp::UnitValue>(context_.getUnitType(), context_); }
}

void CompileTimeBuild::performMemoryClear(Shared<lang::Value> address, Shared<lang::Value> count)
{
    assert(address->type().isPointerType());
    assert(lang::Type::areSame(count->type(), ctx().getSizeType()));

    Shared<cmp::AddressValue> cmp_address  = cmpContentOf(address).cast<cmp::AddressValue>();
    Address                   base_address = cmp_address->address();

    Shared<cmp::IntegerValue> cmp_count   = cmpContentOf(count).cast<cmp::IntegerValue>();
    llvm::APInt               count_value = cmp_count->value();

    lang::Type const&        element_type  = address->type().getElementType();
    Shared<CompileTimeValue> default_value = getDefault(element_type).cast<CompileTimeValue>();

    // While the default_value is not necessarily zero, memory clear is only used for types where that is the case.

    for (llvm::APInt i(count_value.getBitWidth(), 0, false); i.slt(count_value); i = i + 1)
    {
        store(base_address + i.getZExtValue(), default_value);
    }
}

void CompileTimeBuild::performMemoryCopy(Shared<lang::Value> destination,
                                         Shared<lang::Value> source,
                                         Shared<lang::Value> count)
{
    assert(source->type().isPointerType());
    assert(destination->type().isPointerType());
    assert(lang::Type::areSame(source->type().getElementType(), destination->type().getElementType()));
    assert(lang::Type::areSame(count->type(), ctx().getSizeType()));

    Shared<cmp::AddressValue> cmp_source     = cmpContentOf(source).cast<cmp::AddressValue>();
    Address                   source_address = cmp_source->address();

    Shared<cmp::AddressValue> cmp_destination     = cmpContentOf(destination).cast<cmp::AddressValue>();
    Address                   destination_address = cmp_destination->address();

    Shared<cmp::IntegerValue> cmp_count   = cmpContentOf(count).cast<cmp::IntegerValue>();
    llvm::APInt               count_value = cmp_count->value();

    for (llvm::APInt i(count_value.getBitWidth(), 0, false); i.slt(count_value); i = i + 1)
    {
        Shared<CompileTimeValue> value = load(source_address + i.getZExtValue());
        store(destination_address + i.getZExtValue(), value);
    }
}

Shared<lang::Value> CompileTimeBuild::performStackAllocation(lang::Type const& type, Shared<lang::Value> count)
{
    assert(count->type().isSizeType());

    lang::Type const& ptr_type = ctx().getPointerType(type);

    Shared<cmp::IntegerValue> cmp_count   = cmpContentOf(count).cast<cmp::IntegerValue>();
    size_t                    count_value = cmp_count->value().getZExtValue();

    Address address = allocateLocal(type, count_value);

    return makeShared<cmp::AddressValue>(address, ptr_type, context_);
}

Shared<lang::Value> CompileTimeBuild::performOperator(lang::UnaryOperator op, Shared<lang::Value> value)
{
    assert(value->type().isXOrVectorOfX(
        [](auto& t) { return t.isIntegerType() || t.isFloatingPointType() || t.isBooleanType(); }));

    bool const is_integer_type = value->type().isXOrVectorOfX([](auto& t) { return t.isIntegerType(); });
    bool const is_float_type   = value->type().isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); });
    bool const is_boolean_type = value->type().isXOrVectorOfX([](auto& t) { return t.isBooleanType(); });

    lang::Type const& return_type = value->type().getOperatorResultType(op);

    switch (op)
    {
        case lang::UnaryOperator::NOT:
            if (is_integer_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type)
            {
                return apply<BOOL, BOOL>(cmpContentOf(value),
                                         return_type,
                                         context_,
                                         [this](Shared<BOOL> v, lang::Type const&) -> Shared<BOOL> {
                                             return makeShared<cmp::BooleanValue>(!v->value(), context_);
                                         });
            }
            break;
        case lang::UnaryOperator::BITWISE_NOT:
            if (is_integer_type)
            {
                return apply<INT, INT>(cmpContentOf(value),
                                       return_type,
                                       context_,
                                       [this](Shared<INT> v, lang::Type const& t) -> Shared<INT> {
                                           return makeShared<cmp::IntegerValue>(~v->value(), t, context_);
                                       });
            }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type)
            {
                return apply<BOOL, BOOL>(cmpContentOf(value),
                                         return_type,
                                         context_,
                                         [this](Shared<BOOL> v, lang::Type const&) -> Shared<BOOL> {
                                             return makeShared<cmp::BooleanValue>(!v->value(), context_);
                                         });
            }
            break;
        case lang::UnaryOperator::NEGATION:
            if (is_integer_type)
            {
                return apply<INT, INT>(cmpContentOf(value),
                                       return_type,
                                       context_,
                                       [this](Shared<INT> v, lang::Type const& t) -> Shared<INT> {
                                           return makeShared<cmp::IntegerValue>(-v->value(), t, context_);
                                       });
            }
            if (is_float_type)
            {
                return apply<FP, FP>(cmpContentOf(value),
                                     return_type,
                                     context_,
                                     [this](Shared<FP> v, lang::Type const& t) -> Shared<FP> {
                                         return makeShared<cmp::FloatingPointValue>(-v->value(), t, context_);
                                     });
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
    }

    throw std::logic_error("Invalid op");
}

Shared<lang::Value> CompileTimeBuild::performOperator(lang::BinaryOperator op,
                                                      Shared<lang::Value>  lhs,
                                                      Shared<lang::Value>  rhs)
{
    assert(lhs->type().isXOrVectorOfX(
        [](auto& t) { return t.isIntegerType() || t.isFloatingPointType() || t.isBooleanType(); }));
    assert(rhs->type().isXOrVectorOfX(
        [](auto& t) { return t.isIntegerType() || t.isFloatingPointType() || t.isBooleanType(); }));
    assert(lang::Type::areSame(lhs->type(), rhs->type()));

    bool const is_integer_type = lhs->type().isXOrVectorOfX([](auto& t) { return t.isIntegerType(); });
    bool const is_float_type   = lhs->type().isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); });
    bool const is_boolean_type = lhs->type().isXOrVectorOfX([](auto& t) { return t.isBooleanType(); });

    Shared<CompileTimeValue> cmp_lhs = cmpContentOf(lhs);
    Shared<CompileTimeValue> cmp_rhs = cmpContentOf(rhs);

    lang::Type const& return_type = lhs->type().getOperatorResultType(op, rhs->type());
    bool              is_signed   = lhs->type().isSigned();

    switch (op)
    {
        case lang::BinaryOperator::ADDITION:
            if (is_integer_type)
            {
                return apply<INT, INT, INT>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<INT> left, Shared<INT> right, lang::Type const& t) -> Shared<INT> {
                        return makeShared<cmp::IntegerValue>(left->value() + right->value(), t, context_);
                    });
            }
            if (is_float_type)
            {
                return apply<FP, FP, FP>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<FP> left, Shared<FP> right, lang::Type const& t) -> Shared<FP> {
                        return makeShared<cmp::FloatingPointValue>(left->value() + right->value(), t, context_);
                    });
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::SUBTRACTION:
            if (is_integer_type)
            {
                return apply<INT, INT, INT>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<INT> left, Shared<INT> right, lang::Type const& t) -> Shared<INT> {
                        return makeShared<cmp::IntegerValue>(left->value() - right->value(), t, context_);
                    });
            }
            if (is_float_type)
            {
                return apply<FP, FP, FP>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<FP> left, Shared<FP> right, lang::Type const& t) -> Shared<FP> {
                        return makeShared<cmp::FloatingPointValue>(left->value() - right->value(), t, context_);
                    });
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::MULTIPLICATION:
            if (is_integer_type)
            {
                return apply<INT, INT, INT>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<INT> left, Shared<INT> right, lang::Type const& t) -> Shared<INT> {
                        return makeShared<cmp::IntegerValue>(left->value() * right->value(), t, context_);
                    });
            }
            if (is_float_type)
            {
                return apply<FP, FP, FP>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<FP> left, Shared<FP> right, lang::Type const& t) -> Shared<FP> {
                        return makeShared<cmp::FloatingPointValue>(left->value() * right->value(), t, context_);
                    });
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::DIVISION:
            if (is_integer_type)
            {
                return apply<INT, INT, INT>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this, is_signed](Shared<INT> left, Shared<INT> right, lang::Type const& t) -> Shared<INT> {
                        // todo: compile time error if division by zero, use new CompileTimeException
                        if (is_signed)
                            return makeShared<cmp::IntegerValue>(left->value().sdiv(right->value()), t, context_);
                        else return makeShared<cmp::IntegerValue>(left->value().udiv(right->value()), t, context_);
                    });
            }
            if (is_float_type)
            {
                return apply<FP, FP, FP>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<FP> left, Shared<FP> right, lang::Type const& t) -> Shared<FP> {
                        return makeShared<cmp::FloatingPointValue>(left->value() / right->value(), t, context_);
                    });
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::REMAINDER:
            if (is_integer_type)
            {
                return apply<INT, INT, INT>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this, is_signed](Shared<INT> left, Shared<INT> right, lang::Type const& t) -> Shared<INT> {
                        if (is_signed)
                            return makeShared<cmp::IntegerValue>(left->value().srem(right->value()), t, context_);
                        else return makeShared<cmp::IntegerValue>(left->value().urem(right->value()), t, context_);
                    });
            }
            if (is_float_type)
            {
                return apply<FP, FP, FP>(cmp_lhs,
                                         cmp_rhs,
                                         return_type,
                                         context_,
                                         [this](Shared<FP> left, Shared<FP> right, lang::Type const& t) -> Shared<FP> {
                                             llvm::APFloat intermediate = left->value();
                                             intermediate.remainder(right->value());
                                             return makeShared<cmp::FloatingPointValue>(intermediate, t, context_);
                                         });
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::LESS_THAN:
            if (is_integer_type)
            {
                return apply<INT, INT, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this, is_signed](Shared<INT> left, Shared<INT> right, lang::Type const&) -> Shared<BOOL> {
                        if (is_signed)
                            return makeShared<cmp::BooleanValue>(left->value().slt(right->value()), context_);
                        else return makeShared<cmp::BooleanValue>(left->value().ult(right->value()), context_);
                    });
            }
            if (is_float_type)
            {
                return apply<FP, FP, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<FP> left, Shared<FP> right, lang::Type const&) -> Shared<BOOL> {
                        return makeShared<cmp::BooleanValue>(left->value() < right->value(), context_);
                    });
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::LESS_THAN_OR_EQUAL:
            if (is_integer_type)
            {
                return apply<INT, INT, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this, is_signed](Shared<INT> left, Shared<INT> right, lang::Type const&) -> Shared<BOOL> {
                        if (is_signed)
                            return makeShared<cmp::BooleanValue>(left->value().sle(right->value()), context_);
                        else return makeShared<cmp::BooleanValue>(left->value().ule(right->value()), context_);
                    });
            }
            if (is_float_type)
            {
                return apply<FP, FP, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<FP> left, Shared<FP> right, lang::Type const&) -> Shared<BOOL> {
                        return makeShared<cmp::BooleanValue>(left->value() <= right->value(), context_);
                    });
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::GREATER_THAN:
            if (is_integer_type)
            {
                return apply<INT, INT, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this, is_signed](Shared<INT> left, Shared<INT> right, lang::Type const&) -> Shared<BOOL> {
                        if (is_signed)
                            return makeShared<cmp::BooleanValue>(left->value().sgt(right->value()), context_);
                        else return makeShared<cmp::BooleanValue>(left->value().ugt(right->value()), context_);
                    });
            }
            if (is_float_type)
            {
                return apply<FP, FP, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<FP> left, Shared<FP> right, lang::Type const&) -> Shared<BOOL> {
                        return makeShared<cmp::BooleanValue>(left->value() > right->value(), context_);
                    });
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::GREATER_THAN_OR_EQUAL:
            if (is_integer_type)
            {
                return apply<INT, INT, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this, is_signed](Shared<INT> left, Shared<INT> right, lang::Type const&) -> Shared<BOOL> {
                        if (is_signed)
                            return makeShared<cmp::BooleanValue>(left->value().sge(right->value()), context_);
                        else return makeShared<cmp::BooleanValue>(left->value().uge(right->value()), context_);
                    });
            }
            if (is_float_type)
            {
                return apply<FP, FP, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<FP> left, Shared<FP> right, lang::Type const&) -> Shared<BOOL> {
                        return makeShared<cmp::BooleanValue>(left->value() >= right->value(), context_);
                    });
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::EQUAL:
            if (is_integer_type)
            {
                return apply<INT, INT, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<INT> left, Shared<INT> right, lang::Type const&) -> Shared<BOOL> {
                        return makeShared<cmp::BooleanValue>(left->value() == right->value(), context_);
                    });
            }
            if (is_float_type)
            {
                return apply<FP, FP, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<FP> left, Shared<FP> right, lang::Type const&) -> Shared<BOOL> {
                        return makeShared<cmp::BooleanValue>(left->value() == right->value(), context_);
                    });
            }
            if (is_boolean_type)
            {
                return apply<BOOL, BOOL, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<BOOL> left, Shared<BOOL> right, lang::Type const&) -> Shared<BOOL> {
                        return makeShared<cmp::BooleanValue>(left->value() == right->value(), context_);
                    });
            }
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            if (is_integer_type)
            {
                return apply<INT, INT, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<INT> left, Shared<INT> right, lang::Type const&) -> Shared<BOOL> {
                        return makeShared<cmp::BooleanValue>(left->value() != right->value(), context_);
                    });
            }
            if (is_float_type)
            {
                return apply<FP, FP, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<FP> left, Shared<FP> right, lang::Type const&) -> Shared<BOOL> {
                        return makeShared<cmp::BooleanValue>(left->value() != right->value(), context_);
                    });
            }
            if (is_boolean_type)
            {
                return apply<BOOL, BOOL, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<BOOL> left, Shared<BOOL> right, lang::Type const&) -> Shared<BOOL> {
                        return makeShared<cmp::BooleanValue>(left->value() != right->value(), context_);
                    });
            }
            break;
        case lang::BinaryOperator::BITWISE_AND:
            if (is_integer_type)
            {
                return apply<INT, INT, INT>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<INT> left, Shared<INT> right, lang::Type const& t) -> Shared<INT> {
                        return makeShared<cmp::IntegerValue>(left->value() & right->value(), t, context_);
                    });
            }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type)
            {
                return apply<BOOL, BOOL, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<BOOL> left, Shared<BOOL> right, lang::Type const&) -> Shared<BOOL> {
                        return makeShared<cmp::BooleanValue>(left->value() && right->value(), context_);
                    });
            }
            break;
        case lang::BinaryOperator::BITWISE_OR:
            if (is_integer_type)
            {
                return apply<INT, INT, INT>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<INT> left, Shared<INT> right, lang::Type const& t) -> Shared<INT> {
                        return makeShared<cmp::IntegerValue>(left->value() | right->value(), t, context_);
                    });
            }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type)
            {
                return apply<BOOL, BOOL, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<BOOL> left, Shared<BOOL> right, lang::Type const&) -> Shared<BOOL> {
                        return makeShared<cmp::BooleanValue>(left->value() || right->value(), context_);
                    });
            }
            break;
        case lang::BinaryOperator::BITWISE_XOR:
            if (is_integer_type)
            {
                return apply<INT, INT, INT>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<INT> left, Shared<INT> right, lang::Type const& t) -> Shared<INT> {
                        return makeShared<cmp::IntegerValue>(left->value() ^ right->value(), t, context_);
                    });
            }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type)
            {
                return apply<BOOL, BOOL, BOOL>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<BOOL> left, Shared<BOOL> right, lang::Type const&) -> Shared<BOOL> {
                        return makeShared<cmp::BooleanValue>(left->value() != right->value(), context_);
                    });
            }
            break;
        case lang::BinaryOperator::SHIFT_LEFT:
            if (is_integer_type)
            {
                return apply<INT, INT, INT>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this](Shared<INT> left, Shared<INT> right, lang::Type const& t) -> Shared<INT> {
                        return makeShared<cmp::IntegerValue>(left->value().shl(right->value()), t, context_);
                    });
            }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::SHIFT_RIGHT:
            if (is_integer_type)
            {
                return apply<INT, INT, INT>(
                    cmp_lhs,
                    cmp_rhs,
                    return_type,
                    context_,
                    [this, is_signed](Shared<INT> left, Shared<INT> right, lang::Type const& t) -> Shared<INT> {
                        if (is_signed)
                            return makeShared<cmp::IntegerValue>(left->value().ashr(right->value()), t, context_);
                        else return makeShared<cmp::IntegerValue>(left->value().lshr(right->value()), t, context_);
                    });
            }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
    }

    throw std::logic_error("Invalid op");
}

Shared<lang::Value> CompileTimeBuild::performSelect(Shared<lang::Value> condition,
                                                    Shared<lang::Value> true_value,
                                                    Shared<lang::Value> false_value)
{
    assert(condition->type().isXOrVectorOfX([](auto& t) { return t.isBooleanType(); }));
    assert(lang::Type::areSame(true_value->type(), false_value->type()));

    Shared<CompileTimeValue> cmp_condition   = cmpContentOf(condition);
    Shared<CompileTimeValue> cmp_true_value  = cmpContentOf(true_value);
    Shared<CompileTimeValue> cmp_false_value = cmpContentOf(false_value);

    auto select = [](Shared<CompileTimeValue> c, Shared<CompileTimeValue> t, Shared<CompileTimeValue> f)
        -> Shared<CompileTimeValue> { return c.cast<cmp::BooleanValue>()->value() ? t : f; };

    if (condition->type().isVectorType())
    {
        Shared<cmp::VectorValue> cmp_condition_vector   = cmp_condition.cast<cmp::VectorValue>();
        Shared<cmp::VectorValue> cmp_true_value_vector  = cmp_true_value.cast<cmp::VectorValue>();
        Shared<cmp::VectorValue> cmp_false_value_vector = cmp_false_value.cast<cmp::VectorValue>();

        std::vector<Shared<CompileTimeValue>> result_values;
        result_values.reserve(cmp_condition_vector->size());

        for (size_t i = 0; i < cmp_condition_vector->size(); ++i)
        {
            result_values.push_back(
                select(cmp_condition_vector->get(i), cmp_true_value_vector->get(i), cmp_false_value_vector->get(i)));
        }

        return makeShared<cmp::VectorValue>(true_value->type().getElementType(), std::move(result_values), context_);
    }

    return select(cmp_condition, cmp_true_value, cmp_false_value);
}

Shared<lang::Value> CompileTimeBuild::performBooleanCollapse(Shared<lang::Value> value)
{
    assert(value->type().isXOrVectorOfX([](auto& t) { return t.isBooleanType(); }));

    if (value->type().isBooleanType()) return value;

    Shared<cmp::VectorValue> cmp_vector = cmpContentOf(value).cast<cmp::VectorValue>();

    bool result;

    for (size_t i = 0; i < cmp_vector->size(); ++i)
    {
        result = cmp_vector->get(i).cast<cmp::BooleanValue>()->value();

        if (!result) break;
    }

    return makeShared<cmp::BooleanValue>(result, context_);
}

Shared<lang::Value> CompileTimeBuild::performIntegerReinterpretation(Shared<lang::Value> value,
                                                                     lang::Type const&   target_type)
{
    return cmpContentOf(value)->withType(target_type, context_);
}

Shared<lang::Constant> CompileTimeBuild::getGlobalVariableValue(lang::GlobalVariable const& variable, Execution& exec)
{
    Address address = computeAddressOfVariable(variable.self()).cast<cmp::AddressValue>()->address();

    return load(address)->embed(exec);
}

CompileTimeBuild::TypeInformation& CompileTimeBuild::getTypeInformation(lang::Type const& type)
{
    if (!type_information_.contains(&type)) { type.registerExecutionType(*this); }

    return type_information_.at(&type);
}

CompileTimeBuild::FunctionInformation& CompileTimeBuild::getFunctionInformation(lang::Function const& function)
{
    return function_information_.at(&function);
}

CompileTimeBuild::Address const CompileTimeBuild::Address::NULL_ADDRESS {};

CompileTimeBuild::Address::Address(CompileTimeBuild::Address::Location location, size_t memory_index)
    : memory_index_(memory_index)
    , location_(location)
{
    assert(location != Location::Null);
}

bool CompileTimeBuild::Address::operator==(CompileTimeBuild::Address const& other) const
{
    if (location_ != other.location_) return false;
    if (location_ == Location::Null) return true;

    return memory_index_ == other.memory_index_ && array_index_ == other.array_index_
        && inner_indices_ == other.inner_indices_;
}

bool CompileTimeBuild::Address::operator!=(CompileTimeBuild::Address const& other) const
{
    return !(*this == other);
}

CompileTimeBuild::Address CompileTimeBuild::Address::operator+(ptrdiff_t offset) const
{
    assert(location_ != Location::Null);

    Address result = *this;

    size_t* most_inner_index = &result.array_index_;
    if (!result.inner_indices_.empty()) { most_inner_index = &result.inner_indices_.back(); }

    auto index_as_ptrdiff = static_cast<ptrdiff_t>(*most_inner_index);
    assert(index_as_ptrdiff + offset >= 0);

    *most_inner_index = static_cast<size_t>(index_as_ptrdiff + offset);

    return result;
}

CompileTimeBuild::Address CompileTimeBuild::Address::operator+(size_t offset) const
{
    assert(location_ != Location::Null);

    Address result = *this;

    size_t* most_inner_index = &result.array_index_;
    if (!result.inner_indices_.empty()) { most_inner_index = &result.inner_indices_.back(); }

    *most_inner_index += offset;

    return result;
}

CompileTimeBuild::Address CompileTimeBuild::Address::inner(ptrdiff_t index) const
{
    assert(location_ != Location::Null);
    assert(index >= 0);

    Address result = *this;
    result.inner_indices_.push_back(static_cast<size_t>(index));
    return result;
}

CompileTimeBuild::Address CompileTimeBuild::Address::inner(size_t index) const
{
    assert(location_ != Location::Null);

    Address result = *this;
    result.inner_indices_.push_back(index);
    return result;
}

size_t CompileTimeBuild::Address::memory() const
{
    assert(location_ != Location::Null);
    return memory_index_;
}

size_t CompileTimeBuild::Address::array() const
{
    assert(location_ != Location::Null);
    return array_index_;
}

std::vector<size_t> CompileTimeBuild::Address::inners() const
{
    assert(location_ != Location::Null);
    return inner_indices_;
}

CompileTimeBuild::Address::Location CompileTimeBuild::Address::location() const
{
    return location_;
}

std::string CompileTimeBuild::Address::toString() const
{
    if (location_ == Location::Null) return "null";

    std::string result = location_ == Location::Global ? "global" : "local";
    result += "[" + std::to_string(memory_index_) + "][" + std::to_string(array_index_) + "]";

    for (size_t index : inner_indices_) { result += "[" + std::to_string(index) + "]"; }

    return result;
}

Shared<CompileTimeValue> CompileTimeBuild::cmpContentOf(Shared<lang::Value> value)
{
    Shared<CompileTimeValue> cmp_value = value.cast<CompileTimeValue>();
    Optional<Address>        handle    = cmp_value->getHandle();

    if (handle.hasValue()) { cmp_value = load(handle.value()); }

    return cmp_value;
}

CompileTimeBuild::Address CompileTimeBuild::cmpAddressOf(Shared<lang::Value> value)
{
    Shared<CompileTimeValue> cmp_value = value.cast<CompileTimeValue>();
    Optional<Address>        handle    = cmp_value->getHandle();

    if (!handle.hasValue())
    {
        handle = allocateLocal(value->type());
        store(handle.value(), cmp_value);
    }

    return handle.value();
}

Shared<CompileTimeValue> CompileTimeBuild::cmpAddressValueOf(Shared<lang::Value> value)
{
    Address address = cmpAddressOf(value);
    return makeShared<cmp::AddressValue>(address,
                                         context_.getPointerType(value.cast<CompileTimeValue>()->type()),
                                         context_);
}

Shared<CompileTimeValue> CompileTimeBuild::cmpHandledValueOf(Shared<lang::Value> value)
{
    Address address = cmpAddressOf(value);
    return cmpHandledValueOf(address, value.cast<CompileTimeValue>()->type());
}

Shared<CompileTimeValue> CompileTimeBuild::cmpHandledValueOf(Address address, lang::Type const& type)
{
    return makeShared<cmp::HandledValue>(address, type, *this);
}

CompileTimeBuild::Address CompileTimeBuild::allocateGlobal(lang::Type const& type, size_t count)
{
    return allocate(Address::Location::Global, global_memory_, type, count, *this);
}

CompileTimeBuild::Address CompileTimeBuild::allocateLocal(lang::Type const& type, size_t count)
{
    assert(!fns_.empty());

    return allocate(Address::Location::Local, fns_.top().memory, type, count, *this);
}

Shared<CompileTimeValue> CompileTimeBuild::load(CompileTimeBuild::Address const& address)
{
    assert(address.location() != Address::Location::Null);

    Memory& memory = address.location() == Address::Location::Global ? global_memory_ : fns_.top().memory;
    Shared<CompileTimeValue> value = memory.at(address.memory()).at(address.array());

    for (size_t index : address.inners())
    {
        bool ok = true;
        value   = value->access(index, nullptr, &ok, *this);
        assert(ok);// todo: use for compiler error
    }

    return value;
}

void CompileTimeBuild::store(CompileTimeBuild::Address address, Shared<CompileTimeValue> value)
{
    assert(address.location() != Address::Location::Null);

    Memory& memory = address.location() == Address::Location::Global ? global_memory_ : fns_.top().memory;
    Shared<CompileTimeValue>* slot = &memory.at(address.memory()).at(address.array());

    if (address.inners().empty())
    {
        *slot = value;
        return;
    }

    std::function<void(Shared<CompileTimeValue>&, size_t)> replace = [&](Shared<CompileTimeValue>& target,
                                                                         size_t                    index) -> void {
        bool ok;

        if (index == address.inners().size() - 1)
        {
            ok     = true;
            target = target->access(address.inners()[index], &value, &ok, *this);
            assert(ok);// todo: use for compiler error
        }
        else
        {
            ok                               = true;
            Shared<CompileTimeValue> current = target->access(address.inners()[index], nullptr, &ok, *this);
            assert(ok);// todo: use for compiler error

            replace(current, index + 1);

            ok     = true;
            target = target->access(address.inners()[index], &current, &ok, *this);
            assert(ok);// todo: use for compiler error
        }
    };

    replace(*slot, 0);
}

CompileTimeBuild::Memory& CompileTimeBuild::memory(CompileTimeBuild::Address::Location location)
{
    if (location == Address::Location::Global) return global_memory_;

    if (location == Address::Location::Local)
    {
        assert(!fns_.empty());
        return fns_.top().memory;
    }

    throw std::logic_error("Invalid location");
}

std::filesystem::path CompileTimeBuild::getSourceFilePath(lang::Location location)
{
    return native_.getSourceFilePath(location);
}

void CompileTimeBuild::setDebugLocation(lang::Location location, lang::Scope const& scope)
{
    native_.setDebugLocation(location, scope);
}

void CompileTimeBuild::resetDebugLocation()
{
    native_.resetDebugLocation();
}

bool CompileTimeBuild::allDebugLocationsPopped()
{
    return native_.allDebugLocationsPopped();
}

std::string CompileTimeBuild::getLocationString()
{
    return native_.getLocationString();
}
