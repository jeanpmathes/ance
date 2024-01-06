#include "NativeBuild.h"

#include "compiler/CompileContext.h"
#include "compiler/Runtime.h"
#include "lang/construct/Member.h"
#include "lang/construct/constant/Constant.h"
#include "lang/construct/constant/UnitConstant.h"
#include "lang/construct/constant/WrappedConstant.h"
#include "lang/construct/value/RoughlyCastedValue.h"
#include "lang/construct/value/WrappedContentValue.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/expression/ConstantExpression.h"
#include "lang/scope/Scope.h"
#include "lang/type/ArrayType.h"
#include "lang/type/SizeType.h"
#include "lang/type/VectorType.h"

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

Shared<lang::Value> NativeBuild::getDefaultValue(lang::ResolvingHandle<lang::Type> type)
{
    llvm::Value* content_value = type->getDefaultContent(context_);

    return makeShared<lang::WrappedContentValue>(type, content_value, context_);
}

Shared<lang::Constant> NativeBuild::getCString(std::string const& string)
{
    return makeShared<lang::WrappedConstant>(
        context_.ctx().getPointerType(context_.ctx().getFixedWidthIntegerType(8, false)),
        getCStringConstant(string));
}

Shared<lang::Constant> NativeBuild::getSizeValue(size_t size)
{
    assert(size < (1ull << lang::SizeType::MINIMUM_BIT_SIZE));

    lang::ResolvingHandle<lang::Type> size_type     = context_.ctx().getSizeType();
    llvm::Constant*                   size_constant = llvm::ConstantInt::get(size_type->getContentType(context_), size);

    return makeShared<lang::WrappedConstant>(size_type, size_constant);
}

Shared<lang::Constant> NativeBuild::getDiffValue(std::ptrdiff_t diff)
{
    assert(static_cast<size_t>(std::abs(diff)) < (1ull << lang::SizeType::MINIMUM_BIT_SIZE));

    lang::ResolvingHandle<lang::Type> diff_type = context_.ctx().getDiffType();
    llvm::Constant* diff_constant = llvm::ConstantInt::getSigned(diff_type->getContentType(context_), diff);

    return makeShared<lang::WrappedConstant>(diff_type, diff_constant);
}

Shared<lang::Constant> NativeBuild::getSizeOf(lang::ResolvingHandle<lang::Type> type)
{
    lang::ResolvingHandle<lang::Type> size_type = context_.ctx().getSizeType();
    llvm::Constant*                   size_constant =
        llvm::ConstantInt::get(size_type->getContentType(context_), llvmSizeOf(type), false);

    return makeShared<lang::WrappedConstant>(size_type, size_constant);
}

Shared<lang::Constant> NativeBuild::getN(std::variant<uint64_t, double> n, lang::ResolvingHandle<lang::Type> type)
{
    assert(type->isXOrVectorOfX([](auto& t) { return t.isIntegerType() || t.isFloatingPointType(); }));

    llvm::Constant* n_constant = nullptr;

    if (type->isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }))
    {
        uint64_t const n_integer =
            std::holds_alternative<uint64_t>(n) ? std::get<uint64_t>(n) : static_cast<uint64_t>(std::get<double>(n));
        n_constant = llvm::ConstantInt::get(type->getContentType(context_), n_integer, false);
    }
    else if (type->isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }))
    {
        double const n_floating =
            std::holds_alternative<uint64_t>(n) ? static_cast<double>(std::get<uint64_t>(n)) : std::get<double>(n);
        n_constant = llvm::ConstantFP::get(type->getContentType(context_), n_floating);
    }
    else { assert(false); }

    return makeShared<lang::WrappedConstant>(type, n_constant);
}

Shared<lang::Constant> NativeBuild::getZero(lang::ResolvingHandle<lang::Type> type)
{
    return getN(static_cast<uint64_t>(0), type);
}

Shared<lang::Constant> NativeBuild::getOne(lang::ResolvingHandle<lang::Type> type)
{
    return getN(static_cast<uint64_t>(1), type);
}

Shared<lang::Constant> NativeBuild::getNull(lang::ResolvingHandle<lang::Type> type)
{
    assert(type->isPointerType() || type->isBufferType() || type->isOpaquePointerType());

    llvm::Type* content_type = type->getContentType(context_);
    auto*       pointer_type = llvm::dyn_cast<llvm::PointerType>(content_type);
    assert(pointer_type != nullptr);

    llvm::Constant* null_constant = llvm::ConstantPointerNull::get(pointer_type);

    return makeShared<lang::WrappedConstant>(type, null_constant);
}

Shared<lang::Constant> NativeBuild::getBoolean(bool boolean, lang::ResolvingHandle<lang::Type> type)
{
    assert(type->isXOrVectorOfX([](auto& t) { return t.isBooleanType(); }));

    // Vectorization is already handled by llvm here.
    llvm::Constant* boolean_constant = boolean ? llvm::ConstantInt::getTrue(type->getContentType(context_))
                                               : llvm::ConstantInt::getFalse(type->getContentType(context_));

    return makeShared<lang::WrappedConstant>(type, boolean_constant);
}

Shared<lang::Constant> NativeBuild::getInteger(llvm::APInt int_value, lang::ResolvingHandle<lang::Type> type)
{
    assert(type->isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));

    // Vectorization is already handled by llvm here.
    llvm::Constant* integer_constant = llvm::ConstantInt::get(type->getContentType(context_), int_value);

    return makeShared<lang::WrappedConstant>(type, integer_constant);
}

llvm::Constant* NativeBuild::getBooleanConstant(bool boolean)
{
    return boolean ? llvm::ConstantInt::getTrue(context_.ctx().getBooleanType()->getContentType(context_))
                   : llvm::ConstantInt::getFalse(context_.ctx().getBooleanType()->getContentType(context_));
}

llvm::Constant* NativeBuild::getCodepointConstant(char32_t codepoint)
{
    return llvm::ConstantInt::get(context_.ctx().getCharType()->getContentType(context_), codepoint, false);
}

llvm::Constant* NativeBuild::getByteConstant(uint8_t byte)
{
    return llvm::ConstantInt::get(context_.ctx().getFixedWidthIntegerType(8, false)->getContentType(context_),
                                  byte,
                                  false);
}

llvm::Constant* NativeBuild::getFloatConstant(llvm::APFloat float_value)
{
    llvm::Type* content_type;
    switch (llvm::APFloatBase::semanticsSizeInBits(float_value.getSemantics()))
    {
        case 16:
            content_type = context_.ctx().getHalfType()->getContentType(context_);
            break;
        case 32:
            content_type = context_.ctx().getSingleType()->getContentType(context_);
            break;
        case 64:
            content_type = context_.ctx().getDoubleType()->getContentType(context_);
            break;
        case 128:
            content_type = context_.ctx().getQuadType()->getContentType(context_);
            break;
        default:
            throw std::logic_error("Unsupported float size");
    }

    return llvm::ConstantFP::get(content_type, float_value);
}

llvm::Constant* NativeBuild::getIntegerConstant(llvm::APInt int_value)
{
    auto size      = int_value.getBitWidth();
    auto is_signed = int_value.isSignedIntN(size);

    return llvm::ConstantInt::get(context_.ctx().getFixedWidthIntegerType(size, is_signed)->getContentType(context_),
                                  int_value);
}

llvm::Constant* NativeBuild::getByteStringConstant(std::string const& string)
{
    auto iterator = byte_strings_.find(string);
    if (iterator == byte_strings_.end())
    {
        llvm::Constant* constant        = llvm::ConstantDataArray::getString(llvm_context_, string, false);
        std::tie(iterator, std::ignore) = byte_strings_.emplace(string, constant);
    }

    auto const& [_, constant] = *iterator;
    return constant;
}

llvm::Constant* NativeBuild::getCodepointStringConstant(std::u32string const& string)
{
    auto iterator = codepoint_strings_.find(string);
    if (iterator == codepoint_strings_.end())
    {
        auto const* ptr  = reinterpret_cast<char const*>(string.data());
        llvm::Type* type = context_.ctx().getCharType()->getContentType(context_);

        llvm::Constant* constant        = llvm::ConstantDataArray::getRaw(ptr, string.size(), type);
        std::tie(iterator, std::ignore) = codepoint_strings_.emplace(string, constant);
    }

    auto const& [_, constant] = *iterator;
    return constant;
}

llvm::Constant* NativeBuild::getCStringConstant(std::string const& string)
{
    auto iterator = c_strings_.find(string);
    if (iterator == c_strings_.end())
    {
        llvm::Constant* constant        = ir_builder_.CreateGlobalStringPtr(string);
        std::tie(iterator, std::ignore) = c_strings_.emplace(string, constant);
    }

    auto const& [_, constant] = *iterator;
    return constant;
}

Execution::Function NativeBuild::createFunction(lang::Identifier const&               name,
                                                std::string const&                    linkage_name,
                                                Optional<lang::AccessModifier>        access,
                                                bool                                  is_imported,
                                                std::vector<Shared<lang::Parameter>>& parameters,
                                                lang::ResolvingHandle<lang::Type>     return_type,
                                                lang::Scope*                          scope,
                                                bool                                  is_constructor,
                                                lang::Location                        declaration_location,
                                                Optional<lang::Location>              definition_location)
{
    std::vector<lang::ResolvingHandle<lang::Type>> parameter_types;
    parameter_types.reserve(parameters.size());

    std::vector<llvm::Type*> native_parameter_types;
    native_parameter_types.reserve(parameters.size());

    std::vector<llvm::Metadata*> parameter_debug_types;
    parameter_debug_types.reserve(parameters.size() + 1);

    parameter_debug_types.push_back(llvmType(return_type));
    for (auto& parameter : parameters)
    {
        parameter_types.push_back(parameter->type());
        native_parameter_types.push_back(parameter->type()->getContentType(context_));
        parameter_debug_types.push_back(llvmType(parameter->type()));
    }

    llvm::Type* native_return_type = return_type->getContentType(context_);
    if (return_type->isUnitType() && not is_constructor) { native_return_type = llvm::Type::getVoidTy(llvm_context_); }

    llvm::FunctionType* native_type = llvm::FunctionType::get(native_return_type, native_parameter_types, false);
    llvm::Function*     native_function =
        llvm::Function::Create(native_type,
                               access.valueOr(lang::AccessModifier::EXTERN_ACCESS).linkage(),
                               linkage_name,
                               llvm_module_);

    if (definition_location.hasValue())
    {
        assert(scope != nullptr);

        llvm::DISubroutineType* debug_type =
            di_builder_.createSubroutineType(di_builder_.getOrCreateTypeArray(parameter_debug_types));
        llvm::DISubprogram* subprogram =
            di_builder_.createFunction(llvmScope(scope->getDebugScope(context_)),
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

    if (access.hasValue() && access.value().linkage() == llvm::GlobalValue::LinkageTypes::ExternalLinkage)
    {
        if (is_imported)
        {
            native_function->setDLLStorageClass(llvm::GlobalValue::DLLStorageClassTypes::DLLImportStorageClass);
        }
        else { native_function->setDLLStorageClass(llvm::GlobalValue::DLLStorageClassTypes::DLLExportStorageClass); }
    }

    for (unsigned int i = 0; i < parameters.size(); ++i) { parameters[i]->wrap(native_function->getArg(i)); }

    functions_.emplace_back(native_function, return_type, parameter_types);
    return static_cast<Execution::Function>(functions_.size() - 1);
}

void NativeBuild::enterFunctionBody(Execution::Function function)
{
    current_function_ = functions_[static_cast<std::size_t>(function)].llvm_function;

    llvm::BasicBlock* block = llvm::BasicBlock::Create(llvmContext(), "entry_of_body", current_function_);
    ir().SetInsertPoint(block);
}

Shared<lang::Value> NativeBuild::performFunctionCall(Function function, std::vector<Shared<lang::Value>> arguments)
{
    auto& [native_function, return_type, parameters] = functions_[static_cast<std::size_t>(function)];

    std::vector<llvm::Value*> native_arguments;
    native_arguments.reserve(arguments.size());

    for (auto [parameter, arg] : llvm::zip(parameters, arguments))
    {
        Shared<lang::Value> matching_argument = lang::Type::makeMatching(parameter, arg, context_);

        matching_argument->buildContentValue(context_);
        native_arguments.push_back(matching_argument->getContentValue());
    }

    auto* return_value_content = ir().CreateCall(native_function, native_arguments);
    if (!native_function->getFunctionType()->getReturnType()->isVoidTy())
        return_value_content->setName(native_function->getName() + ".call");

    if (return_type->isUnitType()) { return lang::UnitConstant::create(context_.ctx()); }

    return {makeShared<lang::WrappedContentValue>(return_type, return_value_content, context_)};
}

Execution::Struct NativeBuild::createStruct(lang::Identifier name,
                                            lang::AccessModifier,
                                            lang::Type const&                                 type,
                                            std::vector<std::reference_wrapper<lang::Member>> members,
                                            lang::Scope const&                                scope,
                                            lang::Location                                    definition_location)
{
    llvm::DataLayout const&   dl            = llvmModule().getDataLayout();
    auto*                     struct_type   = llvm::dyn_cast<llvm::StructType>(type.getContentType(context_));
    llvm::StructLayout const* struct_layout = dl.getStructLayout(struct_type);

    uint64_t const size      = dl.getTypeSizeInBits(struct_type);
    auto           alignment = static_cast<uint32_t>(dl.getABITypeAlignment(struct_type));

    llvm::DICompositeType* di_type = di().createStructType(llvmScope(scope.getDebugScope(context_)),
                                                           name.text(),
                                                           context_.getSourceFile(definition_location),
                                                           static_cast<unsigned>(definition_location.line()),
                                                           size,
                                                           alignment,
                                                           llvm::DINode::FlagZero,
                                                           nullptr,
                                                           llvm::DINodeArray());

    current_recursive_type_      = &type;
    current_recursive_llvm_type_ = di_type;

    std::vector<llvm::Metadata*> member_types;
    member_types.reserve(members.size());
    for (auto& member : members)
    {
        llvm::Type*   member_type    = member.get().type()->getContentType(context_);
        llvm::DIType* member_di_type = llvmType(member.get().type());

        member_types.push_back(di().createMemberType(
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

    llvm::MDTuple* debug_type = llvm::MDNode::get(llvmContext(), member_types);
    di_type->replaceElements(debug_type);

    current_recursive_type_      = nullptr;
    current_recursive_llvm_type_ = nullptr;

    types_.emplace_back(di_type);
    return static_cast<Struct>(types_.size() - 1);
}

Execution::Alias NativeBuild::createAlias(lang::Identifier name,
                                          lang::AccessModifier,
                                          lang::Type const&  actual_type,
                                          lang::Scope const& scope,
                                          lang::Location     definition_location)
{
    llvm::DIType* di_type = di().createTypedef(llvmType(actual_type),
                                               name.text(),
                                               context_.getSourceFile(definition_location),
                                               static_cast<unsigned>(definition_location.line()),
                                               llvmScope(scope.getDebugScope(context_)));

    types_.emplace_back(di_type);
    return static_cast<Alias>(types_.size() - 1);
}

Execution::BasicType NativeBuild::registerReferenceType(lang::Type const& reference_type)
{
    llvm::DataLayout const& dl = llvmModule().getDataLayout();

    uint64_t const size_in_bits = dl.getTypeSizeInBits(reference_type.getContentType(context_));

    llvm::DIType* di_type = di().createReferenceType(llvm::dwarf::DW_TAG_reference_type,
                                                     llvmType(reference_type.getElementType()),
                                                     size_in_bits);

    types_.emplace_back(di_type);
    return static_cast<BasicType>(types_.size() - 1);
}

Execution::BasicType NativeBuild::registerAddressType(lang::Type const& address_type)
{
    llvm::DataLayout const& dl = llvmModule().getDataLayout();

    uint64_t const size_in_bits = dl.getTypeSizeInBits(address_type.getContentType(context_));

    llvm::DIType* element_di_type = llvmType(address_type.getElementType());
    llvm::DIType* di_type         = di().createPointerType(element_di_type, size_in_bits);

    types_.emplace_back(di_type);
    return static_cast<BasicType>(types_.size() - 1);
}

Execution::BasicType NativeBuild::registerOpaqueAddressType(lang::Type const& opaque_pointer_type)
{
    llvm::DataLayout const& dl = llvmModule().getDataLayout();

    uint64_t const size_in_bits = dl.getTypeSizeInBits(opaque_pointer_type.getContentType(context_));

    std::string const name     = std::string(opaque_pointer_type.name().text());
    auto              encoding = llvm::dwarf::DW_ATE_address;

    llvm::DIType* di_type = di().createBasicType(name, size_in_bits, encoding);

    types_.emplace_back(di_type);
    return static_cast<BasicType>(types_.size() - 1);
}

Execution::BasicType NativeBuild::registerVectorType(lang::Type const& vector_type)
{
    llvm::DataLayout const& dl               = llvmModule().getDataLayout();
    llvm::Type*             llvm_vector_type = vector_type.getContentType(context_);

    uint64_t const size            = dl.getTypeSizeInBits(llvm_vector_type);
    auto           alignment       = static_cast<uint32_t>(dl.getABITypeAlignment(llvm_vector_type));
    llvm::DIType*  element_di_type = llvmType(vector_type.getElementType());

    llvm::SmallVector<llvm::Metadata*, 1> subscripts;
    subscripts.push_back(
        di().getOrCreateSubrange(0, static_cast<int64_t>(vector_type.isVectorType()->getSize().value())));

    llvm::DIType* di_type = di().createVectorType(size, alignment, element_di_type, di().getOrCreateArray(subscripts));

    types_.emplace_back(di_type);
    return static_cast<BasicType>(types_.size() - 1);
}

Execution::BasicType NativeBuild::registerIntegerType(lang::Type const& integer_type)
{
    llvm::DataLayout const& dl = llvmModule().getDataLayout();

    std::string const name         = std::string(integer_type.name().text());
    uint64_t const    size_in_bits = dl.getTypeSizeInBits(integer_type.getContentType(context_));
    auto              encoding = integer_type.isSigned() ? llvm::dwarf::DW_ATE_signed : llvm::dwarf::DW_ATE_unsigned;

    llvm::DIType* di_type = di().createBasicType(name, size_in_bits, encoding);

    types_.emplace_back(di_type);
    return static_cast<BasicType>(types_.size() - 1);
}

Execution::BasicType NativeBuild::registerFloatingPointType(lang::Type const& floating_point_type)
{
    llvm::DataLayout const& dl = llvmModule().getDataLayout();

    std::string const name         = std::string(floating_point_type.name().text());
    uint64_t const    size_in_bits = dl.getTypeSizeInBits(floating_point_type.getContentType(context_));
    auto              encoding     = llvm::dwarf::DW_ATE_float;

    llvm::DIType* di_type = di().createBasicType(name, size_in_bits, encoding);

    types_.emplace_back(di_type);
    return static_cast<BasicType>(types_.size() - 1);
}

Execution::BasicType NativeBuild::registerBooleanType(lang::Type const& boolean_type)
{
    llvm::DataLayout const& dl = llvmModule().getDataLayout();

    std::string const name         = std::string(boolean_type.name().text());
    uint64_t const    size_in_bits = dl.getTypeSizeInBits(boolean_type.getContentType(context_));

    llvm::DIType* di_type = di().createBasicType(name, size_in_bits, llvm::dwarf::DW_ATE_boolean);

    types_.emplace_back(di_type);
    return static_cast<BasicType>(types_.size() - 1);
}

Execution::BasicType NativeBuild::registerUnitType(lang::Type const& unit_type)
{
    llvm::DIType* di_type = di().createUnspecifiedType(unit_type.name().text());

    types_.emplace_back(di_type);
    return static_cast<BasicType>(types_.size() - 1);
}

Execution::BasicType NativeBuild::registerCodepointType(lang::Type const& codepoint_type)
{
    llvm::DataLayout const& dl = llvmModule().getDataLayout();

    std::string const name         = std::string(codepoint_type.name().text());
    uint64_t const    size_in_bits = dl.getTypeSizeInBits(codepoint_type.getContentType(context_));

    llvm::DIType* di_type = di().createBasicType(name, size_in_bits, llvm::dwarf::DW_ATE_UCS);

    types_.emplace_back(di_type);
    return static_cast<BasicType>(types_.size() - 1);
}

Execution::BasicType NativeBuild::registerArrayType(lang::Type const& array_type)
{
    llvm::DataLayout const& dl              = llvmModule().getDataLayout();
    llvm::Type*             llvm_array_type = array_type.getContentType(context_);

    uint64_t const size            = dl.getTypeSizeInBits(llvm_array_type);
    auto           alignment       = static_cast<uint32_t>(dl.getABITypeAlignment(llvm_array_type));
    llvm::DIType*  element_di_type = llvmType(array_type.getElementType());

    llvm::SmallVector<llvm::Metadata*, 1> subscripts;
    subscripts.push_back(
        di().getOrCreateSubrange(0, static_cast<int64_t>(array_type.isArrayType()->getSize().value())));

    llvm::DIType* di_type = di().createArrayType(size, alignment, element_di_type, di().getOrCreateArray(subscripts));

    types_.emplace_back(di_type);
    return static_cast<BasicType>(types_.size() - 1);
}

Execution::GlobalVariable NativeBuild::createGlobalVariable(lang::Identifier                  name,
                                                            lang::AccessModifier              access,
                                                            bool                              is_imported,
                                                            lang::ResolvingHandle<lang::Type> type,
                                                            bool                              is_constant,
                                                            lang::Initializer                 init,
                                                            lang::Location                    location)
{
    llvm::Constant* native_initializer = nullptr;

    if (init.hasValue())
    {
        if (auto* constant_init = std::get_if<std::reference_wrapper<ConstantExpression>>(&init.value()))
        {
            Shared<lang::Constant> initial_value = constant_init->get().getConstantValue();
            initial_value->buildContentConstant(context_);
            native_initializer = initial_value->getContentConstant();
        }
        else
        {
            // Will be initialized at startup.
            assert(std::holds_alternative<std::reference_wrapper<lang::Function>>(init.value()));
            native_initializer = llvm::Constant::getNullValue(type->getContentType(context_));
        }
    }
    else if (!is_imported) { native_initializer = type->getDefaultContent(context_); }

    llvm::Type*       native_type  = type->getContentType(context_);
    std::string const linkage_name = std::string(name.text());

    auto* native_variable = new llvm::GlobalVariable(llvmModule(),
                                                     native_type,
                                                     is_constant,
                                                     access.linkage(),
                                                     native_initializer,
                                                     linkage_name,
                                                     nullptr,
                                                     llvm::GlobalValue::NotThreadLocal,
                                                     llvm::None,
                                                     is_imported);

    llvm::GlobalValue::DLLStorageClassTypes dll_storage_class = llvm::GlobalValue::DefaultStorageClass;
    if (access == lang::AccessModifier::PUBLIC_ACCESS)
    {
        dll_storage_class =
            is_imported ? llvm::GlobalValue::DLLImportStorageClass : llvm::GlobalValue::DLLExportStorageClass;
    }
    native_variable->setDLLStorageClass(dll_storage_class);
    native_variable->setDSOLocal(!is_imported);

    llvm::MaybeAlign const alignment = llvmModule().getDataLayout().getABITypeAlign(native_type);
    native_variable->setAlignment(alignment);

    auto* debug_info = di().createGlobalVariableExpression(&llvmUnit(),
                                                           name.text(),
                                                           name.text(),
                                                           context_.getSourceFile(location),
                                                           static_cast<unsigned>(location.line()),
                                                           llvmType(type),
                                                           access == lang::AccessModifier::PRIVATE_ACCESS);

    native_variable->addDebugInfo(debug_info);

    global_variables_.emplace_back(native_variable, type);
    return static_cast<Execution::GlobalVariable>(global_variables_.size() - 1);
}

Execution::LocalVariable NativeBuild::declareLocalVariable(lang::Identifier const&           name,
                                                           lang::ResolvingHandle<lang::Type> type)
{
    llvm::Value* native_value = ir().CreateAlloca(type->getContentType(context_), nullptr, name.text());

    local_variables_.emplace_back(native_value, type, name);
    return static_cast<Execution::LocalVariable>(local_variables_.size() - 1);
}

void NativeBuild::defineLocalVariable(Execution::LocalVariable variable,
                                      lang::Scope&             scope,
                                      Optional<unsigned>       parameter_index,
                                      lang::Location           location)
{
    auto& [native_variable, type, name] = local_variables_[static_cast<size_t>(variable)];

    llvm::DILocalVariable* native_di_variable;

    if (!parameter_index.hasValue())
    {
        native_di_variable = di().createAutoVariable(llvmScope(scope.getDebugScope(context_)),
                                                     name.text(),
                                                     context_.getSourceFile(location),
                                                     static_cast<unsigned>(location.line()),
                                                     llvmType(type),
                                                     true);
    }
    else
    {
        native_di_variable = di().createParameterVariable(llvmScope(scope.getDebugScope(context_)),
                                                          name.text(),
                                                          parameter_index.value() + 1,
                                                          context_.getSourceFile(location),
                                                          static_cast<unsigned>(location.line()),
                                                          llvmType(type),
                                                          true);
    }

    di().insertDeclare(native_variable,
                       native_di_variable,
                       di().createExpression(),
                       location.getDebugLoc(llvmContext(), llvmScope(scope.getDebugScope(context_))),
                       ir().GetInsertBlock());
}

Shared<lang::Value> NativeBuild::computeAddressOfVariable(Execution::Variable variable)
{
    return std::visit(
        [this](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;

            if constexpr (std::is_same_v<T, Execution::GlobalVariable>)
            {
                auto& [native_variable, type] = global_variables_[static_cast<size_t>(arg)];
                auto type_ptr                 = context_.ctx().getPointerType(type);
                return makeShared<lang::WrappedContentValue>(type_ptr, native_variable, context_);
            }
            else if constexpr (std::is_same_v<T, Execution::LocalVariable>)
            {
                auto& [native_value, type, name] = local_variables_[static_cast<size_t>(arg)];
                auto type_ptr                    = context_.ctx().getPointerType(type);
                return makeShared<lang::WrappedContentValue>(type_ptr, native_value, context_);
            }
            else static_assert(False<T>, "non-exhaustive visitor!");
        },
        variable);
}

Shared<lang::Value> NativeBuild::computeAllocatedSize(lang::ResolvingHandle<lang::Type> type,
                                                      Optional<Shared<lang::Value>>     count)
{
    lang::ResolvingHandle<lang::Type> size_type = context_.ctx().getSizeType();

    llvm::Value* element_size = llvm::ConstantInt::get(size_type->getContentType(context_), llvmSizeOf(type), false);

    llvm::Value* allocated_size = element_size;

    if (count.hasValue())
    {
        assert(lang::Type::areSame(count.value()->type(), size_type));

        count.value()->buildContentValue(context_);
        llvm::Value* count_content = count.value()->getContentValue();

        allocated_size = ir().CreateMul(count_content, element_size, count_content->getName() + ".mul");
    }

    return makeShared<lang::WrappedContentValue>(size_type, allocated_size, context_);
}

Shared<lang::Value> NativeBuild::computeElementPointer(Shared<lang::Value> sequence,
                                                       Shared<lang::Value> index,
                                                       IndexingMode        mode,
                                                       Optional<size_t>    bounds)
{
    auto pointer_type = sequence->type();
    assert(pointer_type->isPointerType() || pointer_type->isBufferType());

    auto sequence_type = pointer_type->getElementType();
    assert(mode != IndexingMode::SEQUENCE || (sequence_type->isArrayType() || sequence_type->isVectorType()));

    index->buildContentValue(context_);

    Optional<lang::ResolvingHandle<lang::Type>> element_type;

    llvm::Value*                    zero         = llvm::ConstantInt::get(llvm::Type::getInt64Ty(llvmContext()), 0);
    llvm::Value*                    native_index = index->getContentValue();
    llvm::SmallVector<llvm::Value*> indices;

    switch (mode)
    {
        case IndexingMode::POINTER:
        {
            // We got passed a value *T on which we operate.
            element_type = pointer_type->getElementType();
            indices      = {native_index};

            break;
        }
        case IndexingMode::SEQUENCE:
        {
            // We got passed a value *[N x T] on which we operate.
            element_type = sequence_type->getElementType();
            indices      = {zero, native_index};

            break;
        }
    }

    sequence->buildContentValue(context_);
    llvm::Value* sequence_ptr = sequence->getContentValue();
    llvm::Type*  base_type    = pointer_type->getElementType()->getContentType(context_);

    if (bounds.hasValue() && context_.ctx().isContainingRuntime())
    {
        Shared<lang::Value> bounds_size_value = getSizeValue(bounds.value());
        Shared<lang::Value> bounds_diff_value = computeConversionOnI(bounds_size_value, context_.ctx().getDiffType());

        bounds_diff_value->buildContentValue(context_);
        llvm::Value* native_bounds = bounds_diff_value->getContentValue();

        llvm::Value* in_bounds = ir().CreateICmpULT(native_index, native_bounds, native_index->getName() + ".icmp");

        Shared<lang::Value> truth =
            makeShared<lang::WrappedContentValue>(context_.ctx().getBooleanType(), in_bounds, context_);

        context_.runtime().buildAssert(truth, "Index out of bounds at " + context_.getLocationString(), context_);
    }

    lang::ResolvingHandle<lang::Type> ptr_type = context_.ctx().getPointerType(element_type.value());
    llvm::Value* element_ptr = ir().CreateGEP(base_type, sequence_ptr, indices, sequence_ptr->getName() + ".gep");

    return makeShared<lang::WrappedContentValue>(ptr_type, element_ptr, context_);
}

Shared<lang::Value> NativeBuild::computeMemberPointer(Shared<lang::Value>     struct_ptr,
                                                      lang::Identifier const& member_name)
{
    assert(struct_ptr->type()->isPointerType());
    assert(struct_ptr->type()->getElementType()->isStructType());

    lang::ResolvingHandle<lang::Type> struct_type = struct_ptr->type()->getElementType();

    lang::Member&                     member          = struct_type->getMember(member_name);
    size_t const                      member_index    = member.index();
    lang::ResolvingHandle<lang::Type> member_ptr_type = context_.ctx().getPointerType(member.type());

    struct_ptr->buildContentValue(context_);
    llvm::Value* struct_ptr_content = struct_ptr->getContentValue();

    llvm::Value* member_ptr = ir().CreateStructGEP(struct_type->getContentType(context_),
                                                   struct_ptr_content,
                                                   static_cast<unsigned int>(member_index),
                                                   struct_ptr_content->getName() + ".gep");

    return makeShared<lang::WrappedContentValue>(member_ptr_type, member_ptr, context_);
}

Shared<lang::Value> NativeBuild::computeAddressOf(Shared<lang::Value> value)
{
    lang::ResolvingHandle<lang::Type> ptr_type = lang::Type::getUndefined();
    llvm::Value*                      ptr;

    if (value->type()->isReferenceType())
    {
        ptr_type = context_.ctx().getPointerType(value->type()->getElementType());

        value->buildContentValue(context_);
        ptr = value->getContentValue();
    }
    else
    {
        ptr_type = context_.ctx().getPointerType(value->type());

        value->buildNativeValue(context_);
        ptr = value->getNativeValue();
    }

    return makeShared<lang::WrappedContentValue>(ptr_type, ptr, context_);
}

Shared<lang::Value> NativeBuild::computePointerToInteger(Shared<lang::Value> pointer)
{
    assert(pointer->type()->isXOrVectorOfX([](auto& t) { return t.isAddressType(); }));

    lang::ResolvingHandle<lang::Type> integer_type = context_.ctx().getUnsignedIntegerPointerType();

    pointer->buildContentValue(context_);
    llvm::Value* pointer_content = pointer->getContentValue();

    llvm::Value* integer_content = ir().CreatePtrToInt(pointer_content, integer_type->getContentType(context_));

    return makeShared<lang::WrappedContentValue>(integer_type, integer_content, context_);
}

Shared<lang::Value> NativeBuild::computeIntegerToPointer(Shared<lang::Value>               integer,
                                                         lang::ResolvingHandle<lang::Type> pointer_type)
{
    assert(integer->type()->isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));

    integer->buildContentValue(context_);
    llvm::Value* integer_content = integer->getContentValue();

    llvm::Value* pointer_content = ir().CreateIntToPtr(integer_content, pointer_type->getContentType(context_));

    return makeShared<lang::WrappedContentValue>(pointer_type, pointer_content, context_);
}

Shared<lang::Value> NativeBuild::computeCastedAddress(Shared<lang::Value>               address,
                                                      lang::ResolvingHandle<lang::Type> new_type)
{
    assert(address->type()->isXOrVectorOfX(
        [](auto& t) { return t.isPointerType() || t.isBufferType() || t.isOpaquePointerType(); }));
    assert(new_type->isXOrVectorOfX(
        [](auto& t) { return t.isPointerType() || t.isBufferType() || t.isOpaquePointerType(); }));

    address->buildContentValue(context_);
    llvm::Value* address_content = address->getContentValue();

    llvm::Value* casted_address_content = ir().CreateBitCast(address_content,
                                                             new_type->getContentType(context_),
                                                             address_content->getName() + ".bitcast");

    return makeShared<lang::WrappedContentValue>(new_type, casted_address_content, context_);
}

Shared<lang::Value> NativeBuild::computeConversionOnFP(Shared<lang::Value>               value,
                                                       lang::ResolvingHandle<lang::Type> destination_type)
{
    assert(value->type()->isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));
    assert(destination_type->isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));

    value->buildContentValue(context_);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* converted_value =
        ir().CreateFPCast(content_value, destination_type->getContentType(context_), content_value->getName() + ".f2f");

    return makeShared<lang::WrappedContentValue>(destination_type, converted_value, context_);
}

Shared<lang::Value> NativeBuild::computeConversionOnI(Shared<lang::Value>               value,
                                                      lang::ResolvingHandle<lang::Type> destination_type)
{
    assert(value->type()->isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));
    assert(destination_type->isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));

    value->buildContentValue(context_);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* converted_value = ir().CreateIntCast(content_value,
                                                      destination_type->getContentType(context_),
                                                      value->type()->isSigned(),
                                                      content_value->getName() + ".i2i");

    return makeShared<lang::WrappedContentValue>(destination_type, converted_value, context_);
}

Shared<lang::Value> NativeBuild::computeConversionFP2I(Shared<lang::Value>               value,
                                                       lang::ResolvingHandle<lang::Type> destination_type)
{
    assert(value->type()->isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));
    assert(destination_type->isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));

    value->buildContentValue(context_);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* converted_value;

    if (destination_type->isSigned())
    {
        converted_value = ir().CreateFPToSI(content_value,
                                            destination_type->getContentType(context_),
                                            content_value->getName() + ".f2i");
    }
    else
    {
        converted_value = ir().CreateFPToUI(content_value,
                                            destination_type->getContentType(context_),
                                            content_value->getName() + ".f2i");
    }

    return makeShared<lang::WrappedContentValue>(destination_type, converted_value, context_);
}

Shared<lang::Value> NativeBuild::computeConversionI2FP(Shared<lang::Value>               value,
                                                       lang::ResolvingHandle<lang::Type> destination_type)
{
    assert(value->type()->isXOrVectorOfX([](auto& t) { return t.isIntegerType(); }));
    assert(destination_type->isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }));

    value->buildContentValue(context_);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value* converted_value;

    if (value->type()->isSigned())
    {
        converted_value = ir().CreateSIToFP(content_value,
                                            destination_type->getContentType(context_),
                                            content_value->getName() + ".i2f");
    }
    else
    {
        converted_value = ir().CreateUIToFP(content_value,
                                            destination_type->getContentType(context_),
                                            content_value->getName() + ".i2f");
    }

    return makeShared<lang::WrappedContentValue>(destination_type, converted_value, context_);
}

Shared<lang::Value> NativeBuild::computePointerFromReference(Shared<lang::Value> reference)
{
    assert(reference->type()->isReferenceType());

    lang::ResolvingHandle<lang::Type> ptr_type = context_.ctx().getPointerType(reference->type()->getElementType());

    return makeShared<lang::RoughlyCastedValue>(ptr_type, reference, context_);
}

Shared<lang::Value> NativeBuild::computeReferenceFromPointer(Shared<lang::Value> pointer)
{
    assert(pointer->type()->isPointerType());

    lang::ResolvingHandle<lang::Type> ref_type = context_.ctx().getReferenceType(pointer->type()->getElementType());

    return makeShared<lang::RoughlyCastedValue>(ref_type, pointer, context_);
}

Shared<lang::Value> NativeBuild::computeAddressIsNotNull(Shared<lang::Value> address)
{
    assert(address->type()->isXOrVectorOfX([](auto& t) { return t.isPointerType() || t.isBufferType(); }));

    address->buildContentValue(context_);
    llvm::Value* content_value = address->getContentValue();

    llvm::Value* is_not_null = ir().CreateIsNotNull(content_value, content_value->getName() + ".nnull");

    return makeShared<lang::WrappedContentValue>(context_.ctx().getBooleanType(), is_not_null, context_);
}

Shared<lang::Value> NativeBuild::computeAddressDiff(Shared<lang::Value> lhs, Shared<lang::Value> rhs)
{
    assert(lhs->type()->isXOrVectorOfX([](auto& t) { return t.isPointerType() || t.isBufferType(); }));
    assert(rhs->type()->isXOrVectorOfX([](auto& t) { return t.isPointerType() || t.isBufferType(); }));

    assert(lang::Type::areSame(lhs->type()->getElementType(), rhs->type()->getElementType()));
    lang::ResolvingHandle<lang::Type> element_type = lhs->type()->getElementType();

    if (element_type->getStateCount().isUnit()) return getDefaultValue(context_.ctx().getDiffType());

    lhs->buildContentValue(context_);
    rhs->buildContentValue(context_);

    llvm::Value* left_value  = lhs->getContentValue();
    llvm::Value* right_value = rhs->getContentValue();

    llvm::StringRef name = left_value->getName();
    if (name.empty()) name = right_value->getName();

    llvm::Value* diff =
        ir().CreatePtrDiff(element_type->getContentType(context_), left_value, right_value, name + ".ptrdiff");
    llvm::Value* result =
        ir().CreateIntCast(diff, context_.ctx().getDiffType()->getContentType(context_), true, name + ".icast");

    return makeShared<lang::WrappedContentValue>(context_.ctx().getDiffType(), result, context_);
}

Shared<lang::Value> NativeBuild::performLoadFromAddress(Shared<lang::Value> address)
{
    assert(address->type()->isPointerType());
    lang::ResolvingHandle<lang::Type> pointee_type = address->type()->getElementType();

    address->buildContentValue(context_);
    llvm::Value* ptr = address->getContentValue();

    return makeShared<lang::WrappedNativeValue>(pointee_type, ptr, context_);
}

void NativeBuild::performStoreToAddress(Shared<lang::Value> address, Shared<lang::Value> value)
{
    assert(address->type()->isPointerType());
    assert(lang::Type::areSame(address->type()->getElementType(), value->type()));

    address->buildContentValue(context_);
    llvm::Value* address_content = address->getContentValue();

    value->buildContentValue(context_);
    llvm::Value* value_content = value->getContentValue();

    ir().CreateStore(value_content, address_content);
}

void NativeBuild::performPointerIteration(Shared<lang::Value>                      pointer,
                                          Shared<lang::Value>                      count,
                                          std::function<void(Shared<lang::Value>)> body)
{
    assert(pointer->type()->isPointerType());
    assert(lang::Type::areSame(count->type(), context_.ctx().getSizeType()));
    assert(current_function_ != nullptr);

    lang::ResolvingHandle<lang::Type> ptr_type     = pointer->type();
    lang::ResolvingHandle<lang::Type> element_type = ptr_type->getElementType();

    llvm::Type* size_type = context_.ctx().getSizeType()->getContentType(context_);

    llvm::BasicBlock* iteration_start = ir().GetInsertBlock();
    llvm::BasicBlock* iteration_body  = llvm::BasicBlock::Create(llvmContext(), "iteration_body", current_function_);
    llvm::BasicBlock* iteration_end   = llvm::BasicBlock::Create(llvmContext(), "iteration_end", current_function_);

    pointer->buildContentValue(context_);
    count->buildContentValue(context_);

    ir().CreateBr(iteration_body);

    ir().SetInsertPoint(iteration_body);
    {
        llvm::PHINode* current_index = ir().CreatePHI(size_type, 2, "i");
        current_index->addIncoming(llvm::ConstantInt::get(size_type, 0), iteration_start);

        llvm::Value* element_ptr = pointer->getContentValue();
        if (!element_type->getStateCount().isUnit())
        {
            element_ptr = ir().CreateInBoundsGEP(element_type->getContentType(context_),
                                                 element_ptr,
                                                 current_index,
                                                 "element_ptr");
        }

        body(makeShared<lang::WrappedContentValue>(ptr_type, element_ptr, context_));

        llvm::Value* next_index = ir().CreateAdd(current_index, llvm::ConstantInt::get(size_type, 1), "next");
        current_index->addIncoming(next_index, iteration_body);

        llvm::Value* condition = ir().CreateICmpULT(next_index, count->getContentValue(), "condition");
        ir().CreateCondBr(condition, iteration_body, iteration_end);
    }

    ir().SetInsertPoint(iteration_end);
}

void NativeBuild::performReturn(Optional<Shared<lang::Value>> value)
{
    assert(current_function_ != nullptr);

    if (value.hasValue())
    {
        value.value()->buildContentValue(context_);
        ir().CreateRet(value.value()->getContentValue());
    }
    else { ir().CreateRetVoid(); }
}

void NativeBuild::performMemoryClear(Shared<lang::Value> address, Shared<lang::Value> size)
{
    assert(address->type()->isPointerType());
    assert(lang::Type::areSame(size->type(), context_.ctx().getSizeType()));

    address->buildContentValue(context_);
    llvm::Value* address_content = address->getContentValue();

    size->buildContentValue(context_);
    llvm::Value* size_content = size->getContentValue();

    ir().CreateMemSet(address_content,
                      llvm::ConstantInt::get(llvm::Type::getInt8Ty(llvmContext()), 0),
                      size_content,
                      llvm::Align(1));
}

void NativeBuild::performMemoryCopy(Shared<lang::Value> destination,
                                    Shared<lang::Value> source,
                                    Shared<lang::Value> size)
{
    assert(source->type()->isPointerType());
    assert(destination->type()->isPointerType());
    assert(lang::Type::areSame(source->type()->getElementType(), destination->type()->getElementType()));
    assert(lang::Type::areSame(size->type(), context_.ctx().getSizeType()));

    source->buildContentValue(context_);
    llvm::Value* source_content = source->getContentValue();

    destination->buildContentValue(context_);
    llvm::Value* destination_content = destination->getContentValue();

    size->buildContentValue(context_);
    llvm::Value* size_content = size->getContentValue();

    ir().CreateMemCpy(destination_content, llvm::Align(1), source_content, llvm::Align(1), size_content);
}

Shared<lang::Value> NativeBuild::performStackAllocation(lang::ResolvingHandle<lang::Type> type,
                                                        Shared<lang::Value>               count)
{
    lang::ResolvingHandle<lang::Type> ptr_type = context_.ctx().getPointerType(type);

    count->buildContentValue(context_);
    llvm::Value* count_content = count->getContentValue();

    llvm::Value* ptr_to_allocated_content = ir().CreateAlloca(type->getContentType(context_), count_content, "alloca");

    return makeShared<lang::WrappedContentValue>(ptr_type, ptr_to_allocated_content, context_);
}

Shared<lang::Value> NativeBuild::performOperator(lang::UnaryOperator op, Shared<lang::Value> value)
{
    assert(value->type()->isXOrVectorOfX(
        [](auto& t) { return t.isIntegerType() || t.isFloatingPointType() || t.isBooleanType(); }));

    bool const is_integer_type = value->type()->isXOrVectorOfX([](auto& t) { return t.isIntegerType(); });
    bool const is_float_type   = value->type()->isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); });
    bool const is_boolean_type = value->type()->isXOrVectorOfX([](auto& t) { return t.isBooleanType(); });

    value->buildContentValue(context_);
    llvm::Value* content_value = value->getContentValue();

    llvm::Value*          result = nullptr;
    llvm::StringRef const name   = content_value->getName();

    switch (op)
    {
        case lang::UnaryOperator::NOT:
            if (is_integer_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type) { result = ir().CreateNot(content_value, name + ".not"); }
            break;
        case lang::UnaryOperator::BITWISE_NOT:
            if (is_integer_type) { result = ir().CreateNot(content_value, name + ".not"); }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type) { result = ir().CreateNot(content_value, name + ".not"); }
            break;
        case lang::UnaryOperator::NEGATION:
            if (is_integer_type) { result = ir().CreateNeg(content_value, name + ".neg"); }
            if (is_float_type) { result = ir().CreateFNeg(content_value, name + ".neg"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
    }

    lang::ResolvingHandle<lang::Type> return_type = value->type()->getOperatorResultType(op);

    return makeShared<lang::WrappedContentValue>(return_type, result, context_);
}

Shared<lang::Value> NativeBuild::performOperator(lang::BinaryOperator op,
                                                 Shared<lang::Value>  lhs,
                                                 Shared<lang::Value>  rhs)
{
    assert(lhs->type()->isXOrVectorOfX(
        [](auto& t) { return t.isIntegerType() || t.isFloatingPointType() || t.isBooleanType(); }));
    assert(rhs->type()->isXOrVectorOfX(
        [](auto& t) { return t.isIntegerType() || t.isFloatingPointType() || t.isBooleanType(); }));
    assert(lang::Type::areSame(lhs->type(), rhs->type()));

    lhs->buildContentValue(context_);
    rhs->buildContentValue(context_);

    llvm::Value* left_value  = lhs->getContentValue();
    llvm::Value* right_value = rhs->getContentValue();

    llvm::Value* result = nullptr;

    llvm::StringRef name = left_value->getName();
    if (name.empty()) { name = right_value->getName(); }

    bool const is_integer_type = lhs->type()->isXOrVectorOfX([](auto& t) { return t.isIntegerType(); });
    bool const is_float_type   = rhs->type()->isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); });
    bool const is_boolean_type = rhs->type()->isXOrVectorOfX([](auto& t) { return t.isBooleanType(); });

    bool const is_signed = lhs->type()->isSigned();

    switch (op)
    {
        case lang::BinaryOperator::ADDITION:
            if (is_integer_type) { result = ir().CreateAdd(left_value, right_value, name + ".add"); }
            if (is_float_type) { result = ir().CreateFAdd(left_value, right_value, name + ".fadd"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::SUBTRACTION:
            if (is_integer_type) { result = ir().CreateSub(left_value, right_value, name + ".sub"); }
            if (is_float_type) { result = ir().CreateFSub(left_value, right_value, name + ".fsub"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::MULTIPLICATION:
            if (is_integer_type) { result = ir().CreateMul(left_value, right_value, name + ".mul"); }
            if (is_float_type) { result = ir().CreateFMul(left_value, right_value, name + ".fmul"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::DIVISION:
            if (is_integer_type)
            {
                if (is_signed) result = ir().CreateSDiv(left_value, right_value, name + ".sdiv");
                else result = ir().CreateUDiv(left_value, right_value, name + ".udiv");
            }
            if (is_float_type) { result = ir().CreateFDiv(left_value, right_value, name + ".fdiv"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::REMAINDER:
            if (is_integer_type)
            {
                if (is_signed) result = ir().CreateSRem(left_value, right_value, name + ".srem");
                else result = ir().CreateURem(left_value, right_value, name + ".urem");
            }
            if (is_float_type) { result = ir().CreateFRem(left_value, right_value, name + ".frem"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::LESS_THAN:
            if (is_integer_type)
            {
                if (is_signed) result = ir().CreateICmpSLT(left_value, right_value, name + ".icmp");
                else result = ir().CreateICmpULT(left_value, right_value, name + ".icmp");
            }
            if (is_float_type) { result = ir().CreateFCmpULT(left_value, right_value, name + ".fcmp"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::LESS_THAN_OR_EQUAL:
            if (is_integer_type)
            {
                if (is_signed) result = ir().CreateICmpSLE(left_value, right_value, name + ".icmp");
                else result = ir().CreateICmpULE(left_value, right_value, name + ".icmp");
            }
            if (is_float_type) { result = ir().CreateFCmpULE(left_value, right_value, name + ".fcmp"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::GREATER_THAN:
            if (is_integer_type)
            {
                if (is_signed) result = ir().CreateICmpSGT(left_value, right_value, name + ".icmp");
                else result = ir().CreateICmpUGT(left_value, right_value, name + ".icmp");
            }
            if (is_float_type) { result = ir().CreateFCmpUGT(left_value, right_value, name + ".fcmp"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::GREATER_THAN_OR_EQUAL:
            if (is_integer_type)
            {
                if (is_signed) result = ir().CreateICmpSGE(left_value, right_value, name + ".icmp");
                else result = ir().CreateICmpUGE(left_value, right_value, name + ".icmp");
            }
            if (is_float_type) { result = ir().CreateFCmpUGE(left_value, right_value, name + ".fcmp"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::EQUAL:
            if (is_integer_type) { result = ir().CreateICmpEQ(left_value, right_value, name + ".icmp"); }
            if (is_float_type) { result = ir().CreateFCmpUEQ(left_value, right_value, name + ".fcmp"); }
            if (is_boolean_type) { result = ir().CreateICmpEQ(left_value, right_value, name + ".icmp"); }
            break;
        case lang::BinaryOperator::NOT_EQUAL:
            if (is_integer_type) { result = ir().CreateICmpNE(left_value, right_value, name + ".icmp"); }
            if (is_float_type) { result = ir().CreateFCmpUNE(left_value, right_value, name + ".fcmp"); }
            if (is_boolean_type) { result = ir().CreateICmpNE(left_value, right_value, name + ".icmp"); }
            break;
        case lang::BinaryOperator::BITWISE_AND:
            if (is_integer_type) { result = ir().CreateAnd(left_value, right_value, name + ".and"); }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type) { result = ir().CreateAnd(left_value, right_value, name + ".and"); }
            break;
        case lang::BinaryOperator::BITWISE_OR:
            if (is_integer_type) { result = ir().CreateOr(left_value, right_value, name + ".or"); }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type) { result = ir().CreateOr(left_value, right_value, name + ".or"); }
            break;
        case lang::BinaryOperator::BITWISE_XOR:
            if (is_integer_type) { result = ir().CreateXor(left_value, right_value, name + ".xor"); }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type) { result = ir().CreateXor(left_value, right_value, name + ".xor"); }
            break;
        case lang::BinaryOperator::SHIFT_LEFT:
            if (is_integer_type) { result = ir().CreateShl(left_value, right_value, name + ".shl"); }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
        case lang::BinaryOperator::SHIFT_RIGHT:
            if (is_integer_type)
            {
                if (is_signed) result = ir().CreateAShr(left_value, right_value, name + ".ashr");
                else result = ir().CreateLShr(left_value, right_value, name + ".lshr");
            }
            if (is_float_type) { throw std::logic_error("Undefined behaviour"); }
            if (is_boolean_type) { throw std::logic_error("Undefined behaviour"); }
            break;
    }

    auto return_type = lhs->type()->getOperatorResultType(op, rhs->type());

    return makeShared<lang::WrappedContentValue>(return_type, result, context_);
}

Shared<lang::Value> NativeBuild::performSelect(Shared<lang::Value> condition,
                                               Shared<lang::Value> true_value,
                                               Shared<lang::Value> false_value)
{
    assert(condition->type()->isXOrVectorOfX([](auto& t) { return t.isBooleanType(); }));
    assert(lang::Type::areSame(true_value->type(), false_value->type()));

    condition->buildContentValue(context_);
    true_value->buildContentValue(context_);
    false_value->buildContentValue(context_);

    llvm::Value* condition_content   = condition->getContentValue();
    llvm::Value* true_value_content  = true_value->getContentValue();
    llvm::Value* false_value_content = false_value->getContentValue();

    llvm::Value* result_content = ir().CreateSelect(condition_content,
                                                    true_value_content,
                                                    false_value_content,
                                                    condition_content->getName() + ".select");

    return makeShared<lang::WrappedContentValue>(true_value->type(), result_content, context_);
}

Shared<lang::Value> NativeBuild::performBooleanCollapse(Shared<lang::Value> value)
{
    assert(value->type()->isXOrVectorOfX([](auto& t) { return t.isBooleanType(); }));

    if (value->type()->isBooleanType()) return value;

    lang::VectorType* vector_type = value->type()->isVectorType();
    assert(vector_type != nullptr);

    value->buildContentValue(context_);
    llvm::Value* vector = value->getContentValue();
    llvm::Value* result = llvm::ConstantInt::getTrue(llvm_context_);

    for (size_t index = 0; index < vector_type->getSize().value(); ++index)
    {
        llvm::Value* element = ir().CreateExtractElement(vector, index);
        result               = ir().CreateAnd(result, element);
    }

    return makeShared<lang::WrappedContentValue>(context_.ctx().getBooleanType(), result, context_);
}

llvm::IRBuilder<>& NativeBuild::ir()
{
    return ir_builder_;
}

llvm::DIBuilder& NativeBuild::di()
{
    return di_builder_;
}

llvm::Module& NativeBuild::llvmModule()
{
    return llvm_module_;
}

llvm::LLVMContext& NativeBuild::llvmContext()
{
    return llvm_context_;
}

llvm::DICompileUnit& NativeBuild::llvmUnit()
{
    return *llvm_di_unit_;
}

llvm::Function* NativeBuild::llvmFunction(Execution::Function function)
{
    return functions_[static_cast<std::size_t>(function)].llvm_function;
}

llvm::DIScope* NativeBuild::llvmScope(Execution::Scoped scoped)
{
    return std::visit(
        [this](auto&& arg) {
            using T              = std::decay_t<decltype(arg)>;
            llvm::DIScope* scope = nullptr;

            if constexpr (std::is_same_v<T, Execution::Application>)
            {
                switch (arg)
                {
                    case Execution::Application::GLOBAL_SCOPE:
                        scope = llvm_di_unit_;
                        break;
                }
            }
            else if constexpr (std::is_same_v<T, Execution::Function>)
            {
                auto index = static_cast<std::size_t>(arg);
                scope      = functions_[index].llvm_function->getSubprogram();
            }
            else if constexpr (std::is_same_v<T, Execution::Struct>)
            {
                auto index = static_cast<std::size_t>(arg);
                scope      = types_[index].llvm_type;
            }
            else { static_assert(False<T>, "non-exhaustive visitor!"); }
            return scope;
        },
        scoped);
}

llvm::DIType* NativeBuild::llvmType(Execution::Type type)
{
    return std::visit(
        [this](auto&& arg) {
            using T               = std::decay_t<decltype(arg)>;
            llvm::DIType* di_type = nullptr;
            auto          index   = static_cast<std::size_t>(arg);
            if constexpr (std::is_same_v<T, Execution::Struct>) { di_type = types_[index].llvm_type; }
            else if constexpr (std::is_same_v<T, Execution::Alias>) { di_type = types_[index].llvm_type; }
            else if constexpr (std::is_same_v<T, Execution::BasicType>) { di_type = types_[index].llvm_type; }
            else { static_assert(False<T>, "non-exhaustive visitor!"); }
            return di_type;
        },
        type);
}

llvm::TypeSize NativeBuild::llvmSizeOf(lang::ResolvingHandle<lang::Type> type)
{
    return llvmModule().getDataLayout().getTypeAllocSize(type->getContentType(context_));
}

llvm::DIType* NativeBuild::llvmType(lang::Type const& type)
{
    if (&type == current_recursive_type_) return current_recursive_llvm_type_;

    return llvmType(type.getDebugType(context_));
}
