#include "NativeBuild.h"
#include <llvm/Support/TargetSelect.h>

#include "compiler/CompileContext.h"
#include "lang/construct/Member.h"
#include "lang/construct/Constant.h"
#include "lang/construct/constant/UnitConstant.h"
#include "lang/expression/LiteralExpression.h"
#include "lang/construct/LocalVariable.h"
#include "lang/construct/Function.h"
#include "lang/construct/GlobalVariable.h"
#include "compiler/WrappedConstant.h"
#include "lang/construct/Variable.h"
#include "compiler/RoughlyCastedValue.h"
#include "compiler/WrappedContentValue.h"
#include "compiler/WrappedNativeValue.h"
#include "compiler/NativeBuilder.h"
#include "lang/scope/Scope.h"
#include "lang/type/ArrayType.h"
#include "lang/type/CharType.h"
#include "lang/type/FloatingPointType.h"
#include "lang/type/SizeType.h"
#include "lang/type/VectorType.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-macros"

#define LLVM_CONCAT_NAME(value, name) value->getName() + name
#define LLVM_DROP_NAME(value, name) ""

#pragma clang diagnostic pop

#define LLVM_BUILD_NAME(value, name) LLVM_DROP_NAME(value, name)
#define LLVM_NAME(value, name) LLVM_BUILD_NAME(value, name)
#define LLVM_NAME2(lhs, rhs, name) lhs->getName().empty() ? LLVM_BUILD_NAME(rhs, name) : LLVM_BUILD_NAME(lhs, name)

template<class>
inline constexpr bool False = false;

NativeBuild::NativeBuild(CompileContext&      context,
                         llvm::LLVMContext&   c,
                         llvm::Module&        m,
                         llvm::IRBuilder<>&   ir,
                         llvm::DIBuilder&     di,
                         llvm::DICompileUnit* di_unit)
    : context_(context)
    , llvm_context_(c)
    , llvm_module_(m)
    , llvm_di_unit_(di_unit)
    , ir_builder_(ir)
    , di_builder_(di)
{}

void NativeBuild::initialize()
{
    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();
}

void NativeBuild::terminate()
{
    llvm::llvm_shutdown();
}

void NativeBuild::setActiveVisitor(NativeBuilder* visitor)
{
    visitor_ = visitor;
}

llvm::GlobalValue::LinkageTypes NativeBuild::getLinkage(lang::AccessModifier access)
{
    llvm::GlobalValue::LinkageTypes linkage;

    switch (access)
    {
        case lang::AccessModifier::PRIVATE_ACCESS:
            linkage = llvm::GlobalValue::LinkageTypes::PrivateLinkage;
            break;

        case lang::AccessModifier::EXTERN_ACCESS:
        case lang::AccessModifier::PUBLIC_ACCESS:
            linkage = llvm::GlobalValue::LinkageTypes::ExternalLinkage;
            break;
    }

    return linkage;
}

llvm::DILocation* NativeBuild::getLocation(lang::Location location, llvm::DIScope* scope)
{
    return llvm::DILocation::get(llvm_context_,
                                 static_cast<unsigned>(location.line()),
                                 static_cast<unsigned>(location.column()),
                                 scope);
}

Shared<lang::Constant> NativeBuild::getDefault(lang::Type const& type)
{
    return makeShared<WrappedConstant>(type, llvmDefault(type), *this);
}

Shared<lang::Constant> NativeBuild::getCodepointString(std::u32string const& string)
{
    auto iterator = codepoint_strings_.find(string);
    if (iterator == codepoint_strings_.end())
    {
        auto const* ptr  = reinterpret_cast<char const*>(string.data());
        llvm::Type* type = llvmType(context_.ctx().getCharType());

        llvm::Constant* constant        = llvm::ConstantDataArray::getRaw(ptr, string.size(), type);
        std::tie(iterator, std::ignore) = codepoint_strings_.emplace(string, constant);
    }

    auto const& [_, constant] = *iterator;

    return makeShared<WrappedConstant>(context_.ctx().getArrayType(context_.ctx().getCharType(), string.size()), constant, *this);
}

Shared<lang::Constant> NativeBuild::getByteString(std::string const& string)
{
    auto iterator = byte_strings_.find(string);
    if (iterator == byte_strings_.end())
    {
        llvm::Constant* constant        = llvm::ConstantDataArray::getString(llvm_context_, string, false);
        std::tie(iterator, std::ignore) = byte_strings_.emplace(string, constant);
    }

    auto const& [_, constant] = *iterator;

    return makeShared<WrappedConstant>(
        context_.ctx().getArrayType(context_.ctx().getFixedWidthIntegerType(8, false), string.size()),
        constant, *this);
}

Shared<lang::Constant> NativeBuild::getCString(std::string const& string)
{
    auto iterator = c_strings_.find(string);
    if (iterator == c_strings_.end())
    {
        llvm::Constant* constant        = ir_builder_.CreateGlobalStringPtr(string);
        std::tie(iterator, std::ignore) = c_strings_.emplace(string, constant);
    }

    auto const& [_, constant] = *iterator;

    return makeShared<WrappedConstant>(
        context_.ctx().getPointerType(context_.ctx().getFixedWidthIntegerType(8, false)),
        constant, *this);
}

Shared<lang::Constant> NativeBuild::getSizeN(size_t size)
{
    assert(size < (1ull << lang::SizeType::MINIMUM_BIT_SIZE));

    lang::Type const& size_type     = context_.ctx().getSizeType();
    llvm::Constant*                   size_constant = llvm::ConstantInt::get(llvmType(size_type), size);

    return makeShared<WrappedConstant>(size_type, size_constant, *this);
}

Shared<lang::Constant> NativeBuild::getDiffN(std::ptrdiff_t diff)
{
    assert(static_cast<size_t>(std::abs(diff)) < (1ull << lang::SizeType::MINIMUM_BIT_SIZE));

    lang::Type const& diff_type = context_.ctx().getDiffType();
    llvm::Constant*                   diff_constant = llvm::ConstantInt::getSigned(llvmType(diff_type), diff);

    return makeShared<WrappedConstant>(diff_type, diff_constant, *this);
}

Shared<lang::Constant> NativeBuild::getSizeOf(lang::Type const& type)
{
    uint64_t const size = llvm_module_.getDataLayout().getTypeAllocSize(llvmType(type));

    lang::Type const& size_type = context_.ctx().getSizeType();
    llvm::Constant*                   size_constant = llvm::ConstantInt::get(llvmType(size_type), size, false);

    return makeShared<WrappedConstant>(size_type, size_constant, *this);
}

Shared<lang::Constant> NativeBuild::getN(std::variant<uint64_t, double> n, lang::Type const& type)
{
    assert(type.isXOrVectorOfX([](auto& t) { return t.isIntegerType() || t.isFloatingPointType(); }));

    llvm::Constant* n_constant = nullptr;

    if (type.isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }))
    {
        uint64_t const n_integer =
            std::holds_alternative<uint64_t>(n) ? std::get<uint64_t>(n) : static_cast<uint64_t>(std::get<double>(n));
        n_constant = llvm::ConstantInt::get(llvmType(type), n_integer, false);
    }
    else if (type.isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }))
    {
        double const n_floating =
            std::holds_alternative<uint64_t>(n) ? static_cast<double>(std::get<uint64_t>(n)) : std::get<double>(n);
        n_constant = llvm::ConstantFP::get(llvmType(type), n_floating);
    }
    else { assert(false); }

    return makeShared<WrappedConstant>(type, n_constant, *this);
}

Shared<lang::Constant> NativeBuild::getZero(lang::Type const& type)
{
    return getN(static_cast<uint64_t>(0), type);
}

Shared<lang::Constant> NativeBuild::getOne(lang::Type const& type)
{
    return getN(static_cast<uint64_t>(1), type);
}

Shared<lang::Constant> NativeBuild::getNull(lang::Type const& type)
{
    assert(type.isPointerType() || type.isBufferType() || type.isOpaquePointerType());

    llvm::Type* content_type = llvmType(type);
    auto*       pointer_type = llvm::dyn_cast<llvm::PointerType>(content_type);
    assert(pointer_type != nullptr);

    llvm::Constant* null_constant = llvm::ConstantPointerNull::get(pointer_type);

    return makeShared<WrappedConstant>(type, null_constant, *this);
}

Shared<lang::Constant> NativeBuild::getBoolean(bool boolean, lang::Type const& type)
{
    assert(type.isXOrVectorOfX([](auto& t) { return t.isBooleanType(); }));

    // Vectorization is already handled by llvm here.
    llvm::Constant* boolean_constant = llvm::ConstantInt::getBool(llvmType(type), boolean);

    return makeShared<WrappedConstant>(type, boolean_constant, *this);
}

Shared<lang::Constant> NativeBuild::getInteger(llvm::APInt int_value, lang::Type const& type)
{
    assert(type.isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));

    // Vectorization is already handled by llvm here.
    llvm::Constant* integer_constant = llvm::ConstantInt::get(llvmType(type), int_value);

    return makeShared<WrappedConstant>(type, integer_constant, *this);
}

Shared<lang::Constant> NativeBuild::getFloatingPoint(llvm::APFloat float_value, lang::Type const& type)
{
    assert(type.isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));

    // Vectorization is already handled by llvm here.
    llvm::Constant* float_constant = llvm::ConstantFP::get(llvmType(type), float_value);

    return makeShared<WrappedConstant>(type, float_constant, *this);
}

Shared<lang::Constant> NativeBuild::getCodepoint(char32_t codepoint)
{
    llvm::Constant* constant = llvm::ConstantInt::get(llvmType(context_.ctx().getCharType()), codepoint, false);

    return makeShared<WrappedConstant>(context_.ctx().getCharType(), constant, *this);
}

Shared<lang::Constant> NativeBuild::getByte(uint8_t byte)
{
    llvm::Constant* constant =
        llvm::ConstantInt::get(llvmType(context_.ctx().getFixedWidthIntegerType(8, false)), byte, false);

    return makeShared<WrappedConstant>(context_.ctx().getFixedWidthIntegerType(8, false), constant, *this);
}

void NativeBuild::createFunction(lang::Identifier const&               name,
                                    std::string const&                    linkage_name,
                                    Optional<lang::AccessModifier>        access,
                                    bool                                  is_imported,
                                    std::vector<Shared<lang::Parameter>> const& parameters,
                                    lang::Type const&     return_type,
                                    lang::Scope const*                          scope,
                                    bool                                  preserve_unit,
                                    lang::Location                        declaration_location,
                                    Optional<lang::Location>              definition_location,
                                    lang::Function const& function)
{
    std::vector<std::reference_wrapper<lang::Type const>> parameter_types;
    parameter_types.reserve(parameters.size());

    std::vector<llvm::Type*> native_parameter_types;
    native_parameter_types.reserve(parameters.size());

    std::vector<llvm::Metadata*> parameter_debug_types;
    parameter_debug_types.reserve(parameters.size() + 1);

    parameter_debug_types.push_back(llvmDiType(return_type));
    for (auto& parameter : parameters)
    {
        parameter_types.emplace_back(parameter->type());
        native_parameter_types.push_back(llvmType(parameter->type()));
        parameter_debug_types.push_back(llvmDiType(parameter->type()));
    }

    llvm::Type* native_return_type = llvmType(return_type);
    if (return_type.isUnitType() && not preserve_unit) { native_return_type = llvm::Type::getVoidTy(llvm_context_); }

    llvm::FunctionType* native_type = llvm::FunctionType::get(native_return_type, native_parameter_types, false);
    llvm::Function*     native_function =
        llvm::Function::Create(native_type,
                               getLinkage(access.valueOr(lang::AccessModifier::EXTERN_ACCESS)),
                               linkage_name,
                               llvm_module_);

    if (definition_location.hasValue())
    {
        assert(scope != nullptr);

        llvm::DISubroutineType* debug_type =
            di_builder_.createSubroutineType(di_builder_.getOrCreateTypeArray(parameter_debug_types));
        llvm::DISubprogram* subprogram =
            di_builder_.createFunction(llvmScope(*scope),
                                       name.text(),
                                       native_function->getName(),
                                       context_.getSourceFile(declaration_location),
                                       static_cast<unsigned>(declaration_location.line()),
                                       debug_type,
                                       static_cast<unsigned>(definition_location->line()),
                                       llvm::DINode::DIFlags::FlagPrototyped,
                                       llvm::DISubprogram::toSPFlags(false, true, false, 0U, name.text() == "main"));

        native_function->setSubprogram(subprogram);
    }

    if (access.hasValue() && getLinkage(access.value()) == llvm::GlobalValue::LinkageTypes::ExternalLinkage)
    {
        if (is_imported)
        {
            native_function->setDLLStorageClass(llvm::GlobalValue::DLLStorageClassTypes::DLLImportStorageClass);
        }
        else { native_function->setDLLStorageClass(llvm::GlobalValue::DLLStorageClassTypes::DLLExportStorageClass); }
    }

    functions_.emplace(&function, NativeFunction{native_function, preserve_unit, return_type, parameter_types});
}

Shared<lang::Value> NativeBuild::getParameterValue(lang::Function const& function, size_t index)
{
    auto& [native_function, preserve_unit_return, return_type, parameters] = functions_.at(&function);

    llvm::Value* arg = native_function->getArg(static_cast<unsigned int>(index));

    return makeShared<WrappedContentValue>(parameters.at(index).get(), arg, *this);
}

void NativeBuild::defineFunctionBody(lang::Function const& function)
{
    current_function_ = &functions_.at(&function);

    llvm::BasicBlock* block = llvm::BasicBlock::Create(llvmContext(), "entry_of_body", current_function_->llvm_function);
    ir().SetInsertPoint(block);
}

Shared<lang::Value> NativeBuild::performFunctionCall(lang::Function const& function, std::vector<Shared<lang::Value>> arguments)
{
    auto& [native_function, preserve_unit_return, return_type, parameters] = functions_.at(&function);

    std::vector<llvm::Value*> native_arguments;
    native_arguments.reserve(arguments.size());

    for (auto [parameter, arg] : llvm::zip(parameters, arguments))
    {
        Shared<lang::Value> matching_argument = lang::Type::makeMatching(parameter, arg, context_);
        native_arguments.push_back(llvmContentValue(matching_argument));
    }

    auto* return_value_content = ir().CreateCall(native_function, native_arguments);
    if (!native_function->getFunctionType()->getReturnType()->isVoidTy())
        return_value_content->setName(LLVM_NAME(native_function, ".call"));

    if (return_type.isUnitType())
        return getDefault(return_type);

    return makeShared<WrappedContentValue>(return_type, return_value_content, *this);
}

void NativeBuild::createStruct(lang::Type const&                                 type,
                               std::vector<std::reference_wrapper<lang::Member>> members,
                               lang::Location definition_location)
{
    llvm::DataLayout const& dl = llvm_module_.getDataLayout();

    llvm::StructType* struct_type = llvm::StructType::create(llvm_context_, type.getMangledName());

    current_recursive_type_                  = &type;
    current_recursive_native_type_.llvm_type = struct_type;

    std::vector<llvm::Type*> llvm_member_types;
    llvm_member_types.reserve(members.size());

    std::vector<llvm::Constant*> llvm_default_values;
    llvm_default_values.reserve(members.size());

    for (auto& member : members)
    {
        llvm::Type* member_type = llvmType(member.get().type());
        llvm_member_types.push_back(member_type);

        Shared<lang::Constant> initializer = member.get().getConstantInitializer(context_);
        llvm_default_values.push_back(llvmConstant(initializer));
    }

    struct_type->setBody(llvm_member_types);
    llvm::StructLayout const* struct_layout = dl.getStructLayout(struct_type);

    uint64_t const size      = dl.getTypeSizeInBits(struct_type);
    auto           alignment = static_cast<uint32_t>(dl.getABITypeAlignment(struct_type));

    llvm::DICompositeType* di_type = di().createStructType(llvmScope(type.scope()),
                                                           type.name().text(),
                                                           context_.getSourceFile(definition_location),
                                                           static_cast<unsigned>(definition_location.line()),
                                                           size,
                                                           alignment,
                                                           llvm::DINode::FlagZero,
                                                           nullptr,
                                                           llvm::DINodeArray());

    current_recursive_native_type_.llvm_di_type = di_type;

    std::vector<llvm::Metadata*> llvm_di_member_types;
    llvm_di_member_types.reserve(members.size());

    for (auto& member : members)
    {
        llvm::Type*   member_type    = llvmType(member.get().type());
        llvm::DIType* member_di_type = llvmDiType(member.get().type());

        llvm_di_member_types.push_back(di().createMemberType(
            di_type,
            member.get().name().text(),
            context_.getSourceFile(member.get().location()),
            static_cast<unsigned>(member.get().location().line()),
            dl.getTypeSizeInBits(member_type),
            static_cast<uint32_t>(dl.getABITypeAlignment(member_type)),
            struct_layout->getElementOffsetInBits(static_cast<unsigned int>(member.get().index())),
            llvm::DINode::FlagZero,
            member_di_type));
    }

    llvm::MDTuple* debug_type = llvm::MDNode::get(llvmContext(), llvm_di_member_types);
    di_type->replaceElements(debug_type);

    llvm::Constant* default_value               = llvm::ConstantStruct::get(struct_type, llvm_default_values);
    current_recursive_native_type_.llvm_default = default_value;

    current_recursive_type_      = nullptr;
    current_recursive_native_type_ = {nullptr, nullptr, nullptr};

    types_[&type] = {struct_type, di_type, default_value};
}

void NativeBuild::createAlias(lang::Type const&  type,
                              lang::Location     definition_location)
{
    llvm::Type* llvm_type = llvmType(type.getActualType());

    llvm::DIType* di_type = di().createTypedef(llvmDiType(type.getActualType()),
                                               type.name().text(),
                                               context_.getSourceFile(definition_location),
                                               static_cast<unsigned>(definition_location.line()),
                                               llvmScope(type.scope()));

    llvm::Constant* default_value = llvmDefault(type.getActualType());

    types_[&type] = {llvm_type, di_type, default_value};
}

void NativeBuild::registerReferenceType(lang::Type const& reference_type)
{
    llvm::DataLayout const& dl = llvm_module_.getDataLayout();

    llvm::Type*        llvm_element_type   = llvmType(reference_type.getElementType());
    llvm::PointerType* llvm_reference_type = llvm::PointerType::get(llvm_element_type, 0);

    uint64_t const size_in_bits = dl.getTypeSizeInBits(llvm_reference_type);

    llvm::DIType* di_type = di().createReferenceType(llvm::dwarf::DW_TAG_reference_type,
                                                     llvmDiType(reference_type.getElementType()),
                                                     size_in_bits);

    llvm::Constant* default_value = nullptr;
    if (reference_type.getElementType().isUnitType())
        default_value = llvm::ConstantPointerNull::get(llvm_reference_type);

    types_[&reference_type] = {llvm_reference_type, di_type, default_value};
}

void NativeBuild::registerAddressType(lang::Type const& address_type)
{
    llvm::DataLayout const& dl = llvm_module_.getDataLayout();

    llvm::Type*        llvm_element_type = llvmType(address_type.getElementType());
    llvm::PointerType* llvm_address_type = llvm::PointerType::get(llvm_element_type, 0);

    uint64_t const size_in_bits    = dl.getTypeSizeInBits(llvm_address_type);
    llvm::DIType*  element_di_type = llvmDiType(address_type.getElementType());
    llvm::DIType* di_type         = di().createPointerType(element_di_type, size_in_bits);

    llvm::Constant* default_value = llvm::ConstantPointerNull::get(llvm_address_type);

    types_[&address_type] = {llvm_address_type, di_type, default_value};
}

void NativeBuild::registerOpaqueAddressType(lang::Type const& opaque_pointer_type)
{
    llvm::DataLayout const& dl = llvm_module_.getDataLayout();

    llvm::PointerType* llvm_opaque_pointer_type = llvm::PointerType::get(llvm::Type::getInt8Ty(llvm_context_), 0);

    uint64_t const    size_in_bits = dl.getTypeSizeInBits(llvm_opaque_pointer_type);
    std::string const name     = std::string(opaque_pointer_type.name().text());
    auto              encoding = llvm::dwarf::DW_ATE_address;

    llvm::DIType* di_type = di().createBasicType(name, size_in_bits, encoding);

    llvm::Constant* default_value = llvm::ConstantPointerNull::get(llvm_opaque_pointer_type);

    types_[&opaque_pointer_type] = {llvm_opaque_pointer_type, di_type, default_value};
}

void NativeBuild::registerVectorType(lang::Type const& vector_type)
{
    llvm::DataLayout const& dl = llvm_module_.getDataLayout();

    lang::VectorType const* type = vector_type.isVectorType();

    llvm::Type*     llvm_element_type     = llvmType(type->getElementType());
    auto            elements              = static_cast<unsigned>(type->getSize().value());
    llvm::Constant* element_default_value = llvmDefault(vector_type.getElementType());

    llvm::Type*     llvm_vector_type;
    llvm::Constant* default_value;

    if (type->getElementType().isVectorizable())
    {
        llvm::VectorType*        actual_llvm_vector_type = llvm::FixedVectorType::get(llvm_element_type, elements);
        llvm::ElementCount const element_count           = actual_llvm_vector_type->getElementCount();

        default_value    = llvm::ConstantVector::getSplat(element_count, element_default_value);
        llvm_vector_type = actual_llvm_vector_type;
    }
    else
    {
        llvm::ArrayType* actual_llvm_array_type = llvm::ArrayType::get(llvm_element_type, elements);

        std::vector<llvm::Constant*> content;
        content.resize(elements, element_default_value);

        default_value    = llvm::ConstantArray::get(actual_llvm_array_type, content);
        llvm_vector_type = actual_llvm_array_type;
    }

    uint64_t const size            = dl.getTypeSizeInBits(llvm_vector_type);
    auto           alignment       = static_cast<uint32_t>(dl.getABITypeAlignment(llvm_vector_type));
    llvm::DIType*  element_di_type = llvmDiType(vector_type.getElementType());

    llvm::SmallVector<llvm::Metadata*, 1> subscripts;
    subscripts.push_back(
        di().getOrCreateSubrange(0, static_cast<int64_t>(vector_type.isVectorType()->getSize().value())));

    llvm::DIType* di_type = di().createVectorType(size, alignment, element_di_type, di().getOrCreateArray(subscripts));

    types_[&vector_type] = {llvm_vector_type, di_type, default_value};
}

void NativeBuild::registerIntegerType(lang::Type const& integer_type)
{
    llvm::DataLayout const& dl = llvm_module_.getDataLayout();

    lang::IntegerType const* type = integer_type.isIntegerType();

    llvm::Type* llvm_integer_type =
        llvm::Type::getIntNTy(llvmContext(), static_cast<unsigned>(type->getNativeBitSize()));

    std::string const name         = std::string(integer_type.name().text());
    uint64_t const    size_in_bits = dl.getTypeSizeInBits(llvm_integer_type);
    auto              encoding = integer_type.isSigned() ? llvm::dwarf::DW_ATE_signed : llvm::dwarf::DW_ATE_unsigned;

    llvm::DIType* di_type = di().createBasicType(name, size_in_bits, encoding);

    llvm::Constant* default_value = llvm::ConstantInt::get(llvm_integer_type, 0);

    types_[&integer_type] = {llvm_integer_type, di_type, default_value};
}

void NativeBuild::registerFloatingPointType(lang::Type const& floating_point_type)
{
    llvm::DataLayout const& dl = llvm_module_.getDataLayout();

    lang::FloatingPointType const* type = floating_point_type.isFloatingPointType();

    llvm::Type* llvm_floating_point_type;
    switch (type->getPrecision())
    {
        case 16:
            llvm_floating_point_type = llvm::Type::getHalfTy(llvm_context_);
            break;

        case 32:
            llvm_floating_point_type = llvm::Type::getFloatTy(llvm_context_);
            break;

        case 64:
            llvm_floating_point_type = llvm::Type::getDoubleTy(llvm_context_);
            break;

        case 128:
            llvm_floating_point_type = llvm::Type::getFP128Ty(llvm_context_);
            break;

        default:
            throw std::logic_error("Unsupported floating point type");
    }

    std::string const name         = std::string(floating_point_type.name().text());
    uint64_t const    size_in_bits = dl.getTypeSizeInBits(llvm_floating_point_type);
    auto              encoding     = llvm::dwarf::DW_ATE_float;

    llvm::DIType* di_type = di().createBasicType(name, size_in_bits, encoding);

    llvm::Constant* default_value = llvm::ConstantFP::get(llvm_floating_point_type, 0.0);

    types_[&floating_point_type] = {llvm_floating_point_type, di_type, default_value};
}

void NativeBuild::registerBooleanType(lang::Type const& boolean_type)
{
    llvm::DataLayout const& dl = llvm_module_.getDataLayout();

    llvm::Type* llvm_boolean_type = llvm::Type::getInt1Ty(llvm_context_);

    std::string const name         = std::string(boolean_type.name().text());
    uint64_t const    size_in_bits = dl.getTypeSizeInBits(llvm_boolean_type);

    llvm::DIType* di_type = di().createBasicType(name, size_in_bits, llvm::dwarf::DW_ATE_boolean);

    llvm::Constant* default_value = llvm::ConstantInt::get(llvm_boolean_type, 0);

    types_[&boolean_type] = {llvm_boolean_type, di_type, default_value};
}

void NativeBuild::registerUnitType(lang::Type const& unit_type)
{
    llvm::StructType* llvm_unit_type = llvm::StructType::create(llvm_context_, unit_type.name().text());

    std::vector<llvm::Type*> const elements;
    llvm_unit_type->setBody(elements, false);

    llvm::DIType* di_type = di().createUnspecifiedType(unit_type.name().text());

    llvm::Constant* default_value = llvm::ConstantStruct::get(llvm_unit_type, {});

    types_[&unit_type] = {llvm_unit_type, di_type, default_value};
}

void NativeBuild::registerCodepointType(lang::Type const& codepoint_type)
{
    llvm::DataLayout const& dl                  = llvm_module_.getDataLayout();
    llvm::Type*             llvm_codepoint_type = llvm::Type::getIntNTy(llvm_context_, lang::CharType::SIZE_IN_BITS);

    std::string const name         = std::string(codepoint_type.name().text());
    uint64_t const    size_in_bits = dl.getTypeSizeInBits(llvm_codepoint_type);

    llvm::DIType* di_type = di().createBasicType(name, size_in_bits, llvm::dwarf::DW_ATE_UCS);

    llvm::Constant* default_value = llvm::ConstantInt::get(llvm_codepoint_type, 0);

    types_[&codepoint_type] = {llvm_codepoint_type, di_type, default_value};
}

void NativeBuild::registerArrayType(lang::Type const& array_type)
{
    llvm::DataLayout const& dl = llvm_module_.getDataLayout();

    lang::ArrayType const* type = array_type.isArrayType();
    size_t const           size = type->getSize().value();

    llvm::ArrayType* llvm_array_type = llvm::ArrayType::get(llvmType(array_type.getElementType()), size);

    uint64_t const bits            = dl.getTypeSizeInBits(llvm_array_type);
    auto           alignment       = static_cast<uint32_t>(dl.getABITypeAlignment(llvm_array_type));
    llvm::DIType*  element_di_type = llvmDiType(array_type.getElementType());

    llvm::SmallVector<llvm::Metadata*, 1> subscripts;
    subscripts.push_back(di().getOrCreateSubrange(0, static_cast<int64_t>(size)));

    llvm::DIType* di_type = di().createArrayType(bits, alignment, element_di_type, di().getOrCreateArray(subscripts));

    std::vector<llvm::Constant*> const content(size, llvmDefault(array_type.getElementType()));
    llvm::Constant*                    default_value = llvm::ConstantArray::get(llvm_array_type, content);

    types_[&array_type] = {llvm_array_type, di_type, default_value};
}

void NativeBuild::createGlobalVariable(lang::GlobalVariable const& global_variable,
                                                            bool                              is_imported,
                                                            lang::GlobalInitializer     init)
{
    llvm::Constant* native_initializer = nullptr;

    if (init.hasValue())
    {
        if (auto* constant_init = std::get_if<std::reference_wrapper<LiteralExpression>>(&init.value()))
        {
            Shared<lang::Constant> initial_constant = constant_init->get().constant().embed(context_);
            native_initializer = llvmConstant(initial_constant);
        }
        else
        {
            // Will be initialized at startup.
            assert(std::holds_alternative<std::reference_wrapper<lang::Function>>(init.value()));
            native_initializer = llvm::Constant::getNullValue(llvmType(global_variable.type()));
        }
    }
    else if (!is_imported) { native_initializer = llvmDefault(global_variable.type()); }

    llvm::Type*       native_type  = llvmType(global_variable.type());
    std::string const linkage_name = std::string(global_variable.name().text());

    auto* native_variable = new llvm::GlobalVariable(llvm_module_,
                                                     native_type,
                                                     global_variable.isConstant(),
                                                     getLinkage(global_variable.access()),
                                                     native_initializer,
                                                     linkage_name,
                                                     nullptr,
                                                     llvm::GlobalValue::NotThreadLocal,
                                                     llvm::None,
                                                     is_imported);

    llvm::GlobalValue::DLLStorageClassTypes dll_storage_class = llvm::GlobalValue::DefaultStorageClass;
    if (global_variable.access() == lang::AccessModifier::PUBLIC_ACCESS)
    {
        dll_storage_class =
            is_imported ? llvm::GlobalValue::DLLImportStorageClass : llvm::GlobalValue::DLLExportStorageClass;
    }
    native_variable->setDLLStorageClass(dll_storage_class);
    native_variable->setDSOLocal(!is_imported);

    llvm::MaybeAlign const alignment = llvm_module_.getDataLayout().getABITypeAlign(native_type);
    native_variable->setAlignment(alignment);

    auto* debug_info = di().createGlobalVariableExpression(llvm_di_unit_,
                                                           global_variable.name().text(),
                                                           global_variable.name().text(),
                                                           context_.getSourceFile(global_variable.location()),
                                                           static_cast<unsigned>(global_variable.location().line()),
                                                           llvmDiType(global_variable.type()),
                                                           global_variable.access() == lang::AccessModifier::PRIVATE_ACCESS);

    native_variable->addDebugInfo(debug_info);

    global_variables_.emplace(&global_variable.self(), NativeGlobalVariable{native_variable, global_variable.type()});
}

void NativeBuild::declareLocalVariable(lang::LocalVariable const& local_variable)
{
    llvm::Value* native_value = ir().CreateAlloca(llvmType(local_variable.type()), nullptr, local_variable.name().text());

    local_variables_.emplace(&local_variable.self(), NativeLocalVariable{native_value, local_variable.type(), local_variable.name()});
}

void NativeBuild::defineLocalVariable(lang::LocalVariable const& local_variable,
                                      lang::Scope const&             scope,
                                      Optional<size_t>       parameter_index,
                                      lang::Location           location)
{
    auto& [native_variable, type, name] = local_variables_.at(&local_variable.self());

    llvm::DILocalVariable* native_di_variable;

    if (!parameter_index.hasValue())
    {
        native_di_variable = di().createAutoVariable(llvmScope(scope),
                                                     name.text(),
                                                     context_.getSourceFile(location),
                                                     static_cast<unsigned>(location.line()),
                                                     llvmDiType(type),
                                                     true);
    }
    else
    {
        native_di_variable = di().createParameterVariable(llvmScope(scope),
                                                          name.text(),
                                                          static_cast<unsigned int>(parameter_index.value() + 1),
                                                          context_.getSourceFile(location),
                                                          static_cast<unsigned>(location.line()),
                                                          llvmDiType(type),
                                                          true);
    }

    di().insertDeclare(native_variable,
                       native_di_variable,
                       di().createExpression(),
                       getLocation(location, llvmScope(scope)),
                       ir().GetInsertBlock());
}

Shared<lang::Value> NativeBuild::computeInitializerValue(lang::LocalInitializer const& initializer)
{
    assert(initializer.hasValue());

    if (auto* parameter = std::get_if<lang::LocalParameterInitializer>(&initializer.value()))
    {
        auto [function, parameter_index] = *parameter;

        return getParameterValue(function, parameter_index);
    }

    if (auto* expression = std::get_if<std::reference_wrapper<Expression>>(&initializer.value()))
    {
        return visitor_->getV(*expression);
    }

    throw std::logic_error("Invalid initializer");
}

Shared<lang::Value> NativeBuild::computeAddressOfVariable(lang::Variable const& variable)
{
    if (global_variables_.contains(&variable))
    {
        auto& [native_variable, type] = global_variables_.at(&variable);
        lang::Type const& type_ptr                 = context_.ctx().getPointerType(type);
        return makeShared<WrappedContentValue>(type_ptr, native_variable, *this);
    }

    if (local_variables_.contains(&variable))
    {
        auto& [native_value, type, name] = local_variables_.at(&variable);
        lang::Type const& type_ptr                    = context_.ctx().getPointerType(type);
        return makeShared<WrappedContentValue>(type_ptr, native_value, *this);
    }

    throw std::logic_error("Variable not found");
}

Shared<lang::Value> NativeBuild::computeAsActualType(Shared<lang::Value> value)
{
    lang::Type const& actual_type = value->type().getActualType();
    if (lang::Type::areSame(value->type(), actual_type)) return value;

    return makeShared<RoughlyCastedValue>(actual_type, value, *this);
}

Shared<lang::Value> NativeBuild::computeAllocatedSize(lang::Type const& type,
                                                      Optional<Shared<lang::Value>>     count)
{
    lang::Type const& size_type = context_.ctx().getSizeType();

    Shared<lang::Constant> element_size = getSizeOf(type);

    llvm::Value* element_size_constant = llvmConstant(element_size);
    llvm::Value* allocated_size        = element_size_constant;

    if (count.hasValue())
    {
        assert(lang::Type::areSame(count.value()->type(), size_type));

        llvm::Value* count_content = llvmContentValue(count.value());

        allocated_size = ir().CreateMul(count_content, element_size_constant, LLVM_NAME(count_content, ".mul"));
    }

    return makeShared<WrappedContentValue>(size_type, allocated_size, *this);
}

Shared<lang::Value> NativeBuild::computeElementPointer(Shared<lang::Value> sequence,
                                                       Shared<lang::Value> index,
                                                       IndexingMode        mode,
                                                       Optional<size_t>    bounds)
{
    lang::Type const& pointer_type = sequence->type();
    assert(pointer_type.isPointerType() || pointer_type.isBufferType());

    lang::Type const& sequence_type = pointer_type.getElementType();
    assert(mode != IndexingMode::SEQUENCE || (sequence_type.isArrayType() || sequence_type.isVectorType()));

    Optional<std::reference_wrapper<lang::Type const>> element_type;

    llvm::Value*                    zero         = llvm::ConstantInt::get(llvm::Type::getInt64Ty(llvmContext()), 0);
    llvm::Value*                    native_index = llvmContentValue(index);
    llvm::SmallVector<llvm::Value*> indices;

    switch (mode)
    {
        case IndexingMode::POINTER:
        {
            // We got passed a value *T on which we operate.
            element_type = pointer_type.getElementType();
            indices      = {native_index};

            break;
        }
        case IndexingMode::SEQUENCE:
        {
            // We got passed a value *[N x T] on which we operate.
            element_type = sequence_type.getElementType();
            indices      = {zero, native_index};

            break;
        }
    }

    llvm::Value* sequence_ptr = llvmContentValue(sequence);
    llvm::Type*  base_type    = llvmType(pointer_type.getElementType());

    if (bounds.hasValue() && context_.ctx().isContainingRuntime())
    {
        Shared<lang::Value> bounds_size_value = getSizeN(bounds.value());
        Shared<lang::Value> bounds_diff_value = computeConversionOnI(bounds_size_value, context_.ctx().getDiffType());

        llvm::Value* native_bounds = llvmContentValue(bounds_diff_value);

        llvm::Value* in_bounds = ir().CreateICmpULT(native_index, native_bounds, LLVM_NAME(native_index, ".icmp"));

        Shared<lang::Value> truth =
            makeShared<WrappedContentValue>(context_.ctx().getBooleanType(), in_bounds, *this);

        context_.runtime().buildAssert(truth, "Index out of bounds at " + context_.getLocationString(), context_);
    }

    lang::Type const& ptr_type = context_.ctx().getPointerType(element_type.value());
    llvm::Value* element_ptr = ir().CreateGEP(base_type, sequence_ptr, indices, LLVM_NAME(sequence_ptr, ".gep"));

    return makeShared<WrappedContentValue>(ptr_type, element_ptr, *this);
}

Shared<lang::Value> NativeBuild::computeMemberPointer(Shared<lang::Value>     struct_ptr,
                                                      lang::Identifier const& member_name)
{
    assert(struct_ptr->type().isPointerType());
    assert(struct_ptr->type().getElementType().isStructType());

    lang::Type const& struct_type = struct_ptr->type().getElementType();

    lang::Member const&                     member          = struct_type.getMember(member_name);
    size_t const                      member_index    = member.index();
    lang::Type const& member_ptr_type = context_.ctx().getPointerType(member.type());

    llvm::Value* struct_ptr_content = llvmContentValue(struct_ptr);

    llvm::Value* member_ptr = ir().CreateStructGEP(llvmType(struct_type),
                                                   struct_ptr_content,
                                                   static_cast<unsigned int>(member_index),
                                                   LLVM_NAME(struct_ptr_content, ".gep"));

    return makeShared<WrappedContentValue>(member_ptr_type, member_ptr, *this);
}

Shared<lang::Value> NativeBuild::computeAddressOf(Shared<lang::Value> value)
{
    Optional<std::reference_wrapper<lang::Type const>> ptr_type;
    llvm::Value*                      ptr;

    if (value->type().isReferenceType())
    {
        ptr_type = context_.ctx().getPointerType(value->type().getElementType());
        ptr = llvmContentValue(value);
    }
    else
    {
        ptr_type = context_.ctx().getPointerType(value->type());
        ptr = llvmNativeValue(value);
    }

    return makeShared<WrappedContentValue>(ptr_type.value(), ptr, *this);
}

Shared<lang::Value> NativeBuild::computePointerToInteger(Shared<lang::Value> pointer)
{
    assert(pointer->type().isXOrVectorOfX([](auto& t) { return t.isAddressType(); }));

    lang::Type const& integer_type = context_.ctx().getUnsignedIntegerPointerType();

    llvm::Value* pointer_content = llvmContentValue(pointer);

    llvm::Value* integer_content = ir().CreatePtrToInt(pointer_content, llvmType(integer_type));

    return makeShared<WrappedContentValue>(integer_type, integer_content, *this);
}

Shared<lang::Value> NativeBuild::computeIntegerToPointer(Shared<lang::Value>               integer,
                                                         lang::Type const& pointer_type)
{
    assert(integer->type().isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));

    llvm::Value* integer_content = llvmContentValue(integer);

    llvm::Value* pointer_content = ir().CreateIntToPtr(integer_content, llvmType(pointer_type));

    return makeShared<WrappedContentValue>(pointer_type, pointer_content, *this);
}

Shared<lang::Value> NativeBuild::computeCastedAddress(Shared<lang::Value>               address,
                                                      lang::Type const& new_type)
{
    assert(address->type().isXOrVectorOfX(
        [](auto& t) { return t.isPointerType() || t.isBufferType() || t.isOpaquePointerType(); }));
    assert(new_type.isXOrVectorOfX(
        [](auto& t) { return t.isPointerType() || t.isBufferType() || t.isOpaquePointerType(); }));

    if (llvmType(address->type()) == llvmType(new_type))
        return makeShared<RoughlyCastedValue>(new_type, address, *this);

    llvm::Value* address_content = llvmContentValue(address);

    llvm::Value* casted_address_content = ir().CreateBitCast(address_content, llvmType(new_type), LLVM_NAME(address_content, ".bitcast"));

    return makeShared<WrappedContentValue>(new_type, casted_address_content, *this);
}

Shared<lang::Value> NativeBuild::computeConversionOnFP(Shared<lang::Value>               value,
                                                       lang::Type const& destination_type)
{
    assert(value->type().isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));
    assert(destination_type.isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));

    llvm::Value* content_value = llvmContentValue(value);

    llvm::Value* converted_value =
        ir().CreateFPCast(content_value, llvmType(destination_type), LLVM_NAME(content_value, ".f2f"));

    return makeShared<WrappedContentValue>(destination_type, converted_value, *this);
}

Shared<lang::Value> NativeBuild::computeConversionOnI(Shared<lang::Value>               value,
                                                      lang::Type const& destination_type)
{
    assert(value->type().isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));
    assert(destination_type.isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));

    llvm::Value* content_value = llvmContentValue(value);

    llvm::Value* converted_value = ir().CreateIntCast(content_value,
                                                      llvmType(destination_type),
                                                      value->type().isSigned(),
                                                      LLVM_NAME(content_value, ".i2i"));

    return makeShared<WrappedContentValue>(destination_type, converted_value, *this);
}

Shared<lang::Value> NativeBuild::computeConversionFP2I(Shared<lang::Value>               value,
                                                       lang::Type const& destination_type)
{
    assert(value->type().isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));
    assert(destination_type.isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));

    llvm::Value* content_value = llvmContentValue(value);

    llvm::Value* converted_value;

    if (destination_type.isSigned())
    {
        converted_value = ir().CreateFPToSI(content_value, llvmType(destination_type), LLVM_NAME(content_value, ".f2i"));
    }
    else
    {
        converted_value = ir().CreateFPToUI(content_value, llvmType(destination_type), LLVM_NAME(content_value, ".f2i"));
    }

    return makeShared<WrappedContentValue>(destination_type, converted_value, *this);
}

Shared<lang::Value> NativeBuild::computeConversionI2FP(Shared<lang::Value>               value,
                                                       lang::Type const& destination_type)
{
    assert(value->type().isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));
    assert(destination_type.isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));

    llvm::Value* content_value = llvmContentValue(value);

    llvm::Value* converted_value;

    if (value->type().isSigned())
    {
        converted_value = ir().CreateSIToFP(content_value, llvmType(destination_type), LLVM_NAME(content_value, ".i2f"));
    }
    else
    {
        converted_value = ir().CreateUIToFP(content_value, llvmType(destination_type), LLVM_NAME(content_value, ".i2f"));
    }

    return makeShared<WrappedContentValue>(destination_type, converted_value, *this);
}

Shared<lang::Value> NativeBuild::computePointerFromReference(Shared<lang::Value> reference)
{
    assert(reference->type().isReferenceType());

    lang::Type const& ptr_type = context_.ctx().getPointerType(reference->type().getElementType());

    return makeShared<RoughlyCastedValue>(ptr_type, reference, *this);
}

Shared<lang::Value> NativeBuild::computeReferenceFromPointer(Shared<lang::Value> pointer)
{
    assert(pointer->type().isPointerType());

    lang::Type const& ref_type = context_.ctx().getReferenceType(pointer->type().getElementType());

    return makeShared<RoughlyCastedValue>(ref_type, pointer, *this);
}

Shared<lang::Value> NativeBuild::computeAddressIsNotNull(Shared<lang::Value> address)
{
    assert(address->type().isXOrVectorOfX([](auto& t) { return t.isPointerType() || t.isBufferType(); }));

    llvm::Value* content_value = llvmContentValue(address);

    llvm::Value* is_not_null = ir().CreateIsNotNull(content_value, LLVM_NAME(content_value, ".nnull"));

    return makeShared<WrappedContentValue>(context_.ctx().getBooleanType(), is_not_null, *this);
}

Shared<lang::Value> NativeBuild::computeAddressDiff(Shared<lang::Value> lhs, Shared<lang::Value> rhs)
{
    assert(lhs->type().isXOrVectorOfX([](auto& t) { return t.isPointerType() || t.isBufferType(); }));
    assert(rhs->type().isXOrVectorOfX([](auto& t) { return t.isPointerType() || t.isBufferType(); }));

    assert(lang::Type::areSame(lhs->type().getElementType(), rhs->type().getElementType()));
    lang::Type const& element_type = lhs->type().getElementType();

    if (element_type.getStateCount().isUnit()) return getDefault(context_.ctx().getDiffType());

    llvm::Value* left_value  = llvmContentValue(lhs);
    llvm::Value* right_value = llvmContentValue(rhs);

    llvm::Value* diff   = ir().CreatePtrDiff(llvmType(element_type),
                                           left_value,
                                           right_value,
                                           LLVM_NAME2(left_value, right_value, ".diff"));
    llvm::Value* result = ir().CreateIntCast(diff, llvmType(context_.ctx().getDiffType()), true,
                                             LLVM_NAME(diff, ".diff"));

    return makeShared<WrappedContentValue>(context_.ctx().getDiffType(), result, *this);
}

Shared<lang::Value> NativeBuild::performLoadFromAddress(Shared<lang::Value> address)
{
    assert(address->type().isPointerType());
    lang::Type const& pointee_type = address->type().getElementType();

    llvm::Value* ptr = llvmContentValue(address);

    return makeShared<WrappedNativeValue>(pointee_type, ptr, *this);
}

void NativeBuild::performStoreToAddress(Shared<lang::Value> address, Shared<lang::Value> value)
{
    assert(address->type().isPointerType());
    assert(lang::Type::areSame(address->type().getElementType(), value->type()));

    llvm::Value* address_content = llvmContentValue(address);
    llvm::Value* value_content = llvmContentValue(value);

    ir().CreateStore(value_content, address_content);
}

void NativeBuild::performPointerIteration(Shared<lang::Value>                      pointer,
                                          Shared<lang::Value>                      count,
                                          std::function<void(Shared<lang::Value>)> body)
{
    assert(pointer->type().isPointerType());
    assert(lang::Type::areSame(count->type(), context_.ctx().getSizeType()));
    assert(current_function_ != nullptr);

    lang::Type const& ptr_type     = pointer->type();
    lang::Type const& element_type = ptr_type.getElementType();

    llvm::Type* size_type = llvmType(context_.ctx().getSizeType());

    llvm::BasicBlock* iteration_start = ir().GetInsertBlock();
    llvm::BasicBlock* iteration_body  = llvm::BasicBlock::Create(llvmContext(), "iteration_body", current_function_->llvm_function);
    llvm::BasicBlock* iteration_end   = llvm::BasicBlock::Create(llvmContext(), "iteration_end", current_function_->llvm_function);

    ir().CreateBr(iteration_body);

    ir().SetInsertPoint(iteration_body);
    {
        llvm::PHINode* current_index = ir().CreatePHI(size_type, 2, "i");
        current_index->addIncoming(llvm::ConstantInt::get(size_type, 0), iteration_start);

        llvm::Value* element_ptr = llvmContentValue(pointer);
        if (!element_type.getStateCount().isUnit())
        {
            element_ptr = ir().CreateInBoundsGEP(llvmType(element_type), element_ptr,
                                                 current_index,
                                                 "element_ptr");
        }

        body(makeShared<WrappedContentValue>(ptr_type, element_ptr, *this));

        llvm::Value* next_index = ir().CreateAdd(current_index, llvm::ConstantInt::get(size_type, 1), "next");
        current_index->addIncoming(next_index, iteration_body);

        llvm::Value* condition = ir().CreateICmpULT(next_index, llvmContentValue(count), "condition");
        ir().CreateCondBr(condition, iteration_body, iteration_end);
    }

    ir().SetInsertPoint(iteration_end);
}

void NativeBuild::performReturn(Optional<Shared<lang::Value>> value)
{
    assert(current_function_ != nullptr);
    assert(lang::Type::areSame(current_function_->return_type, value.hasValue() ? value.value()->type() : context_.ctx().getUnitType()));

    if (value.hasValue())
    {
        if (current_function_->return_type.isUnitType() && !current_function_->preserve_unit_return)
        {
            ir().CreateRetVoid();
        }
        else
        {
            llvm::Value* content_value = llvmContentValue(value.value());
            ir().CreateRet(content_value);
        }
    }
    else
    {
        if (current_function_->preserve_unit_return)
        {
            Shared<lang::Value> unit_value = getDefault(context_.ctx().getUnitType());
            llvm::Value*        content_value = llvmContentValue(unit_value);

            ir().CreateRet(content_value);
        }
        else
        {
            ir().CreateRetVoid();
        }
    }
}

void NativeBuild::performMemoryClear(Shared<lang::Value> address, Shared<lang::Value> size)
{
    assert(address->type().isPointerType());
    assert(lang::Type::areSame(size->type(), context_.ctx().getSizeType()));

    llvm::Value* address_content = llvmContentValue(address);
    llvm::Value* size_content = llvmContentValue(size);

    ir().CreateMemSet(address_content,
                      llvm::ConstantInt::get(llvm::Type::getInt8Ty(llvmContext()), 0),
                      size_content,
                      llvm::Align(1));
}

void NativeBuild::performMemoryCopy(Shared<lang::Value> destination,
                                    Shared<lang::Value> source,
                                    Shared<lang::Value> size)
{
    assert(source->type().isPointerType());
    assert(destination->type().isPointerType());
    assert(lang::Type::areSame(source->type().getElementType(), destination->type().getElementType()));
    assert(lang::Type::areSame(size->type(), context_.ctx().getSizeType()));

    llvm::Value* source_content = llvmContentValue(source);
    llvm::Value* destination_content = llvmContentValue(destination);
    llvm::Value* size_content = llvmContentValue(size);

    ir().CreateMemCpy(destination_content, llvm::Align(1), source_content, llvm::Align(1), size_content);
}

Shared<lang::Value> NativeBuild::performStackAllocation(lang::Type const& type,
                                                        Shared<lang::Value>               count)
{
    lang::Type const& ptr_type = context_.ctx().getPointerType(type);

    llvm::Value* count_content = llvmContentValue(count);

    llvm::Value* ptr_to_allocated_content = ir().CreateAlloca(llvmType(type), count_content, "alloca");

    return makeShared<WrappedContentValue>(ptr_type, ptr_to_allocated_content, *this);
}

Shared<lang::Value> NativeBuild::performOperator(lang::UnaryOperator op, Shared<lang::Value> value)
{
    assert(value->type().isXOrVectorOfX(
        [](auto& t) { return t.isIntegerType() || t.isFloatingPointType() || t.isBooleanType(); }));

    bool const is_integer_type = value->type().isXOrVectorOfX([](auto& t) { return t.isIntegerType(); });
    bool const is_float_type   = value->type().isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); });
    bool const is_boolean_type = value->type().isXOrVectorOfX([](auto& t) { return t.isBooleanType(); });

    llvm::Value* content_value = llvmContentValue(value);

    llvm::Value*          result = nullptr;

    switch (op)
    {
        case lang::UnaryOperator::NOT:
            if (is_integer_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type) { result = ir().CreateNot(content_value, LLVM_NAME(content_value, ".not")); }
            break;
        case lang::UnaryOperator::BITWISE_NOT:
            if (is_integer_type) { result = ir().CreateNot(content_value, LLVM_NAME(content_value, ".not")); }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type) { result = ir().CreateNot(content_value, LLVM_NAME(content_value, ".not")); }
            break;
        case lang::UnaryOperator::NEGATION:
            if (is_integer_type) { result = ir().CreateNeg(content_value, LLVM_NAME(content_value, ".neg")); }
            if (is_float_type) { result = ir().CreateFNeg(content_value, LLVM_NAME(content_value, ".neg")); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
    }

    lang::Type const& return_type = value->type().getOperatorResultType(op);

    return makeShared<WrappedContentValue>(return_type, result, *this);
}

Shared<lang::Value> NativeBuild::performOperator(lang::BinaryOperator op,
                                                 Shared<lang::Value>  lhs,
                                                 Shared<lang::Value>  rhs)
{
    assert(lhs->type().isXOrVectorOfX(
        [](auto& t) { return t.isIntegerType() || t.isFloatingPointType() || t.isBooleanType(); }));
    assert(rhs->type().isXOrVectorOfX(
        [](auto& t) { return t.isIntegerType() || t.isFloatingPointType() || t.isBooleanType(); }));
    assert(lang::Type::areSame(lhs->type(), rhs->type()));

    llvm::Value* left_value  = llvmContentValue(lhs);
    llvm::Value* right_value = llvmContentValue(rhs);

    llvm::Value* result = nullptr;

    bool const is_integer_type = lhs->type().isXOrVectorOfX([](auto& t) { return t.isIntegerType(); });
    bool const is_float_type   = rhs->type().isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); });
    bool const is_boolean_type = rhs->type().isXOrVectorOfX([](auto& t) { return t.isBooleanType(); });

    bool const is_signed = lhs->type().isSigned();

    switch (op)
    {
        case lang::BinaryOperator::ADDITION:
            if (is_integer_type)
            {
                result = ir().CreateAdd(left_value, right_value, LLVM_NAME2(left_value, right_value, ".add"));
            }
            if (is_float_type)
            {
                result = ir().CreateFAdd(left_value, right_value, LLVM_NAME2(left_value, right_value, ".fadd"));
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::SUBTRACTION:
            if (is_integer_type)
            {
                result = ir().CreateSub(left_value, right_value, LLVM_NAME2(left_value, right_value, ".sub"));
            }
            if (is_float_type)
            {
                result = ir().CreateFSub(left_value, right_value, LLVM_NAME2(left_value, right_value, ".fsub"));
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::MULTIPLICATION:
            if (is_integer_type)
            {
                result = ir().CreateMul(left_value, right_value, LLVM_NAME2(left_value, right_value, ".mul"));
            }
            if (is_float_type)
            {
                result = ir().CreateFMul(left_value, right_value, LLVM_NAME2(left_value, right_value, ".fmul"));
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::DIVISION:
            if (is_integer_type)
            {
                if (is_signed)
                    result = ir().CreateSDiv(left_value, right_value, LLVM_NAME2(left_value, right_value, ".sdiv"));
                else result = ir().CreateUDiv(left_value, right_value, LLVM_NAME2(left_value, right_value, ".udiv"));
            }
            if (is_float_type)
            {
                result = ir().CreateFDiv(left_value, right_value, LLVM_NAME2(left_value, right_value, ".fdiv"));
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::REMAINDER:
            if (is_integer_type)
            {
                if (is_signed)
                    result = ir().CreateSRem(left_value, right_value, LLVM_NAME2(left_value, right_value, ".srem"));
                else result = ir().CreateURem(left_value, right_value, LLVM_NAME2(left_value, right_value, ".urem"));
            }
            if (is_float_type)
            {
                result = ir().CreateFRem(left_value, right_value, LLVM_NAME2(left_value, right_value, ".frem"));
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::LESS_THAN:
            if (is_integer_type)
            {
                if (is_signed)
                    result = ir().CreateICmpSLT(left_value, right_value, LLVM_NAME2(left_value, right_value, ".icmp"));
                else result = ir().CreateICmpULT(left_value, right_value, LLVM_NAME2(left_value, right_value, ".icmp"));
            }
            if (is_float_type)
            {
                result = ir().CreateFCmpULT(left_value, right_value, LLVM_NAME2(left_value, right_value, ".fcmp"));
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::LESS_THAN_OR_EQUAL:
            if (is_integer_type)
            {
                if (is_signed)
                    result = ir().CreateICmpSLE(left_value, right_value, LLVM_NAME2(left_value, right_value, ".icmp"));
                else result = ir().CreateICmpULE(left_value, right_value, LLVM_NAME2(left_value, right_value, ".icmp"));
            }
            if (is_float_type)
            {
                result = ir().CreateFCmpULE(left_value, right_value, LLVM_NAME2(left_value, right_value, ".fcmp"));
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::GREATER_THAN:
            if (is_integer_type)
            {
                if (is_signed)
                    result = ir().CreateICmpSGT(left_value, right_value, LLVM_NAME2(left_value, right_value, ".icmp"));
                else result = ir().CreateICmpUGT(left_value, right_value, LLVM_NAME2(left_value, right_value, ".icmp"));
            }
            if (is_float_type)
            {
                result = ir().CreateFCmpUGT(left_value, right_value, LLVM_NAME2(left_value, right_value, ".fcmp"));
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::GREATER_THAN_OR_EQUAL:
            if (is_integer_type)
            {
                if (is_signed)
                    result = ir().CreateICmpSGE(left_value, right_value, LLVM_NAME2(left_value, right_value, ".icmp"));
                else result = ir().CreateICmpUGE(left_value, right_value, LLVM_NAME2(left_value, right_value, ".icmp"));
            }
            if (is_float_type)
            {
                result = ir().CreateFCmpUGE(left_value, right_value, LLVM_NAME2(left_value, right_value, ".fcmp"));
            }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::EQUAL:
            if (is_integer_type)
            {
                result = ir().CreateICmpEQ(left_value, right_value, LLVM_NAME2(left_value, right_value, ".icmp"));
            }
            if (is_float_type)
            {
                result = ir().CreateFCmpUEQ(left_value, right_value, LLVM_NAME2(left_value, right_value, ".fcmp"));
            }
            if (is_boolean_type)
            {
                result = ir().CreateICmpEQ(left_value, right_value, LLVM_NAME2(left_value, right_value, ".icmp"));
            }
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            if (is_integer_type)
            {
                result = ir().CreateICmpNE(left_value, right_value, LLVM_NAME2(left_value, right_value, ".icmp"));
            }
            if (is_float_type)
            {
                result = ir().CreateFCmpUNE(left_value, right_value, LLVM_NAME2(left_value, right_value, ".fcmp"));
            }
            if (is_boolean_type)
            {
                result = ir().CreateICmpNE(left_value, right_value, LLVM_NAME2(left_value, right_value, ".icmp"));
            }
            break;
        case lang::BinaryOperator::BITWISE_AND:
            if (is_integer_type)
            {
                result = ir().CreateAnd(left_value, right_value, LLVM_NAME2(left_value, right_value, ".and"));
            }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type)
            {
                result = ir().CreateAnd(left_value, right_value, LLVM_NAME2(left_value, right_value, ".and"));
            }
            break;
        case lang::BinaryOperator::BITWISE_OR:
            if (is_integer_type)
            {
                result = ir().CreateOr(left_value, right_value, LLVM_NAME2(left_value, right_value, ".or"));
            }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type)
            {
                result = ir().CreateOr(left_value, right_value, LLVM_NAME2(left_value, right_value, ".or"));
            }
            break;
        case lang::BinaryOperator::BITWISE_XOR:
            if (is_integer_type)
            {
                result = ir().CreateXor(left_value, right_value, LLVM_NAME2(left_value, right_value, ".xor"));
            }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type)
            {
                result = ir().CreateXor(left_value, right_value, LLVM_NAME2(left_value, right_value, ".xor"));
            }
            break;
        case lang::BinaryOperator::SHIFT_LEFT:
            if (is_integer_type)
            {
                result = ir().CreateShl(left_value, right_value, LLVM_NAME2(left_value, right_value, ".shl"));
            }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::SHIFT_RIGHT:
            if (is_integer_type)
            {
                if (is_signed)
                    result = ir().CreateAShr(left_value, right_value, LLVM_NAME2(left_value, right_value, ".ashr"));
                else result = ir().CreateLShr(left_value, right_value, LLVM_NAME2(left_value, right_value, ".lshr"));
            }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
    }

    lang::Type const& return_type = lhs->type().getOperatorResultType(op, rhs->type());

    return makeShared<WrappedContentValue>(return_type, result, *this);
}

Shared<lang::Value> NativeBuild::performSelect(Shared<lang::Value> condition,
                                               Shared<lang::Value> true_value,
                                               Shared<lang::Value> false_value)
{
    assert(condition->type().isXOrVectorOfX([](auto& t) { return t.isBooleanType(); }));
    assert(lang::Type::areSame(true_value->type(), false_value->type()));

    llvm::Value* condition_content   = llvmContentValue(condition);
    llvm::Value* true_value_content  = llvmContentValue(true_value);
    llvm::Value* false_value_content = llvmContentValue(false_value);

    llvm::Value* result_content = ir().CreateSelect(condition_content,
                                                    true_value_content,
                                                    false_value_content,
                                                    LLVM_NAME(condition_content, ".select"));

    return makeShared<WrappedContentValue>(true_value->type(), result_content, *this);
}

Shared<lang::Value> NativeBuild::performBooleanCollapse(Shared<lang::Value> value)
{
    assert(value->type().isXOrVectorOfX([](auto& t) { return t.isBooleanType(); }));

    if (value->type().isBooleanType()) return value;

    lang::VectorType const* vector_type = value->type().isVectorType();
    assert(vector_type != nullptr);

    llvm::Value* vector = llvmContentValue(value);
    llvm::Value* result = llvm::ConstantInt::getTrue(llvm_context_);

    for (size_t index = 0; index < vector_type->getSize().value(); ++index)
    {
        llvm::Value* element = ir().CreateExtractElement(vector, index);
        result               = ir().CreateAnd(result, element);
    }

    return makeShared<WrappedContentValue>(context_.ctx().getBooleanType(), result, *this);
}

Shared<lang::Value> NativeBuild::performIntegerReinterpretation(Shared<lang::Value> value, lang::Type const& target_type)
{
    return makeShared<RoughlyCastedValue>(target_type, value, *this);
}

Execution::Handle<false> NativeBuild::allocateNativeValue(llvm::Value* value)
{
    values_.emplace_back(value, nullptr);

    return { this, std::prev(values_.end()) };
}

Execution::Handle<false> NativeBuild::allocateContentValue(llvm::Value* value)
{
    values_.emplace_back(nullptr, value);

    return { this, std::prev(values_.end()) };
}

Execution::Handle<true> NativeBuild::allocateConstant(llvm::Constant* constant)
{
    constants_.emplace_back(constant);

    return { this, std::prev(constants_.end()) };
}

void NativeBuild::releaseValue(std::any handle)
{
    auto iterator = std::any_cast<std::list<Value>::iterator>(handle);
    values_.erase(iterator);
}

void NativeBuild::releaseConstant(std::any handle)
{
    auto iterator = std::any_cast<std::list<llvm::Constant*>::iterator>(handle);
    constants_.erase(iterator);
}

CompileContext& NativeBuild::cc()
{
    return context_;
}

llvm::IRBuilder<>& NativeBuild::ir()
{
    return ir_builder_;
}

llvm::DIBuilder& NativeBuild::di()
{
    return di_builder_;
}

llvm::LLVMContext& NativeBuild::llvmContext()
{
    return llvm_context_;
}

llvm::Function* NativeBuild::llvmFunction(lang::Function const& function)
{
    return functions_.at(&function).llvm_function;
}

llvm::DIScope* NativeBuild::llvmScope(lang::Scope const& scope)
{
    if (scope.getGlobalScope() == &scope)
        return llvm_di_unit_;

    if (auto function_scope = dynamic_cast<lang::Function const*>(&scope))
        return functions_.at(function_scope).llvm_function->getSubprogram();

    if (auto type_scope = dynamic_cast<lang::Type const*>(&scope))
        return getNativeType(*type_scope).llvm_di_type;

    return llvmScope(scope.scope());
}

llvm::Type* NativeBuild::llvmType(lang::Type const& type)
{
    if (&type == current_recursive_type_) return current_recursive_native_type_.llvm_type;

    return getNativeType(type).llvm_type;
}

llvm::DIType* NativeBuild::llvmDiType(lang::Type const& type)
{
    if (&type == current_recursive_type_) return current_recursive_native_type_.llvm_di_type;

    return getNativeType(type).llvm_di_type;
}

llvm::Constant* NativeBuild::llvmDefault(lang::Type const& type)
{
    if (&type == current_recursive_type_) return current_recursive_native_type_.llvm_default;

    return getNativeType(type).llvm_default;
}

llvm::Value* NativeBuild::llvmNativeValue(Shared<lang::Value> value)
{
    Execution::Handle<false> execution_value = value->getExecutionValue();
    assert(execution_value.execution == this);

    auto iterator = std::any_cast<std::list<Value>::iterator>(execution_value.handle);
    Value const& entry = *iterator;

    llvm::Value* native_value = entry.native;

    if (native_value == nullptr)
    {
        native_value = ir().CreateAlloca(llvmType(value->type()), nullptr, "store");
        ir().CreateStore(entry.content, native_value);
    }

    return native_value;
}

llvm::Value* NativeBuild::llvmContentValue(Shared<lang::Value> value)
{
    Execution::Handle<false> execution_value = value->getExecutionValue();
    assert(execution_value.execution == this);

    auto iterator = std::any_cast<std::list<Value>::iterator>(execution_value.handle);
    Value const& entry = *iterator;

    llvm::Value* content_value = entry.content;

    if (entry.content == nullptr)
    {
        content_value = ir().CreateLoad(llvmType(value->type()), entry.native, entry.native->getName() + ".load");
    }

    return content_value;
}

llvm::Constant* NativeBuild::llvmConstant(Shared<lang::Constant> constant)
{
    Execution::Handle<true> execution_constant = constant->getExecutionConstant();
    assert(execution_constant.execution == this);

    auto iterator = std::any_cast<std::list<llvm::Constant*>::iterator>(execution_constant.handle);
    llvm::Constant* llvm_constant = *iterator;

    return llvm_constant;
}

llvm::Function* NativeBuild::getCurrentFunction()
{
    return current_function_ != nullptr ? current_function_->llvm_function : nullptr;
}

void NativeBuild::setCurrentFunction(lang::Function const* function)
{
    current_function_ = function != nullptr ? &functions_.at(function) : nullptr;
}

NativeBuild::NativeType& NativeBuild::getNativeType(lang::Type const& type)
{
    if (!types_.contains(&type))
    {
        type.registerExecutionType(context_);
    }

    return types_[&type];
}
