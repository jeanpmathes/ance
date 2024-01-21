#ifndef ANCE_SRC_COMPILER_NATIVEBUILD_H_
#define ANCE_SRC_COMPILER_NATIVEBUILD_H_

#include "Execution.h"

#include <map>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

class CompileContext;

/**
 * A class to build operations as native LLVM IR.
 */
class NativeBuild : public Execution
{
  public:
    NativeBuild(CompileContext&      context,
                llvm::LLVMContext&   c,
                llvm::Module&        m,
                llvm::IRBuilder<>&   ir,
                llvm::DIBuilder&     di,
                llvm::DICompileUnit* di_unit);
    ~NativeBuild() override = default;

    Shared<lang::Constant> getDefault(lang::ResolvingHandle<lang::Type> type) override;
    Shared<lang::Constant> getCodepointString(std::u32string const& string) override;
    Shared<lang::Constant> getByteString(std::string const& string) override;
    Shared<lang::Constant> getCString(std::string const& string) override;
    Shared<lang::Constant> getSizeN(std::size_t size) override;
    Shared<lang::Constant> getDiffN(std::ptrdiff_t diff) override;
    Shared<lang::Constant> getSizeOf(lang::ResolvingHandle<lang::Type> type) override;
    Shared<lang::Constant> getN(std::variant<uint64_t, double> n, lang::ResolvingHandle<lang::Type> type) override;
    Shared<lang::Constant> getZero(lang::ResolvingHandle<lang::Type> type) override;
    Shared<lang::Constant> getOne(lang::ResolvingHandle<lang::Type> type) override;
    Shared<lang::Constant> getNull(lang::ResolvingHandle<lang::Type> type) override;
    Shared<lang::Constant> getBoolean(bool boolean, lang::ResolvingHandle<lang::Type> type) override;
    Shared<lang::Constant> getInteger(llvm::APInt int_value, lang::ResolvingHandle<lang::Type> type) override;
    Shared<lang::Constant> getFloatingPoint(llvm::APFloat float_value, lang::ResolvingHandle<lang::Type> type) override;
    Shared<lang::Constant> getCodepoint(char32_t codepoint) override;
    Shared<lang::Constant> getByte(uint8_t byte) override;

    Function            createFunction(lang::Identifier const&               name,
                                       std::string const&                    linkage_name,
                                       Optional<lang::AccessModifier>        access,
                                       bool                                  is_imported,
                                       std::vector<Shared<lang::Parameter>>& parameters,
                                       lang::ResolvingHandle<lang::Type>     return_type,
                                       lang::Scope*                          scope,
                                       bool                                  is_constructor,
                                       lang::Location                        declaration_location,
                                       Optional<lang::Location>              definition_location) override;
    void                enterFunctionBody(Execution::Function function) override;
    Shared<lang::Value> performFunctionCall(Function function, std::vector<Shared<lang::Value>> arguments) override;

    Struct createStruct(lang::Identifier                                  name,
                        lang::AccessModifier                              access,
                        lang::Type const&                                 type,
                        std::vector<std::reference_wrapper<lang::Member>> members,
                        lang::Scope const&                                scope,
                        lang::Location                                    definition_location) override;

    Alias createAlias(lang::Identifier     name,
                      lang::AccessModifier access,
                      lang::Type const&    actual_type,
                      lang::Scope const&   scope,
                      lang::Location       definition_location) override;

    BasicType registerReferenceType(lang::Type const& reference_type) override;
    BasicType registerAddressType(lang::Type const& address_type) override;
    BasicType registerOpaqueAddressType(lang::Type const& opaque_pointer_type) override;
    BasicType registerVectorType(lang::Type const& vector_type) override;
    BasicType registerIntegerType(lang::Type const& integer_type) override;
    BasicType registerFloatingPointType(lang::Type const& floating_point_type) override;
    BasicType registerBooleanType(lang::Type const& boolean_type) override;
    BasicType registerUnitType(lang::Type const& unit_type) override;
    BasicType registerCodepointType(lang::Type const& codepoint_type) override;
    BasicType registerArrayType(lang::Type const& array_type) override;

    GlobalVariable createGlobalVariable(lang::Identifier                  name,
                                        lang::AccessModifier              access,
                                        bool                              is_imported,
                                        lang::ResolvingHandle<lang::Type> type,
                                        bool                              is_constant,
                                        lang::Initializer                 init,
                                        lang::Location                    location) override;
    LocalVariable  declareLocalVariable(lang::Identifier const& name, lang::ResolvingHandle<lang::Type> type) override;
    void           defineLocalVariable(Execution::LocalVariable variable,
                                       lang::Scope&             scope,
                                       Optional<unsigned>       parameter_index,
                                       lang::Location           location) override;
    Shared<lang::Value> computeAddressOfVariable(Variable variable) override;

    Shared<lang::Value> computeAllocatedSize(lang::ResolvingHandle<lang::Type> type,
                                             Optional<Shared<lang::Value>>     count) override;
    Shared<lang::Value> computeElementPointer(Shared<lang::Value> sequence,
                                              Shared<lang::Value> index,
                                              IndexingMode        mode,
                                              Optional<size_t>    bounds) override;
    Shared<lang::Value> computeMemberPointer(Shared<lang::Value>     struct_ptr,
                                             lang::Identifier const& member_name) override;
    Shared<lang::Value> computeAddressOf(Shared<lang::Value> value) override;
    Shared<lang::Value> computePointerToInteger(Shared<lang::Value> pointer) override;
    Shared<lang::Value> computeIntegerToPointer(Shared<lang::Value>               integer,
                                                lang::ResolvingHandle<lang::Type> pointer_type) override;
    Shared<lang::Value> computeCastedAddress(Shared<lang::Value>               address,
                                             lang::ResolvingHandle<lang::Type> new_type) override;
    Shared<lang::Value> computeConversionOnFP(Shared<lang::Value>               value,
                                              lang::ResolvingHandle<lang::Type> destination_type) override;
    Shared<lang::Value> computeConversionOnI(Shared<lang::Value>               value,
                                             lang::ResolvingHandle<lang::Type> destination_type) override;
    Shared<lang::Value> computeConversionFP2I(Shared<lang::Value>               value,
                                              lang::ResolvingHandle<lang::Type> destination_type) override;
    Shared<lang::Value> computeConversionI2FP(Shared<lang::Value>               value,
                                              lang::ResolvingHandle<lang::Type> destination_type) override;
    Shared<lang::Value> computePointerFromReference(Shared<lang::Value> reference) override;
    Shared<lang::Value> computeReferenceFromPointer(Shared<lang::Value> pointer) override;
    Shared<lang::Value> computeAddressIsNotNull(Shared<lang::Value> address) override;
    Shared<lang::Value> computeAddressDiff(Shared<lang::Value> lhs, Shared<lang::Value> rhs) override;

    Shared<lang::Value> performLoadFromAddress(Shared<lang::Value> address) override;
    void                performStoreToAddress(Shared<lang::Value> address, Shared<lang::Value> value) override;
    void                performPointerIteration(Shared<lang::Value>                      pointer,
                                                Shared<lang::Value>                      count,
                                                std::function<void(Shared<lang::Value>)> body) override;
    void                performReturn(Optional<Shared<lang::Value>> value) override;
    void                performMemoryClear(Shared<lang::Value> address, Shared<lang::Value> size) override;
    void                performMemoryCopy(Shared<lang::Value> destination,
                                          Shared<lang::Value> source,
                                          Shared<lang::Value> size) override;
    Shared<lang::Value> performStackAllocation(lang::ResolvingHandle<lang::Type> type,
                                               Shared<lang::Value>               count) override;
    Shared<lang::Value> performOperator(lang::UnaryOperator op, Shared<lang::Value> value) override;
    Shared<lang::Value> performOperator(lang::BinaryOperator op,
                                        Shared<lang::Value>  lhs,
                                        Shared<lang::Value>  rhs) override;
    Shared<lang::Value> performSelect(Shared<lang::Value> condition,
                                      Shared<lang::Value> true_value,
                                      Shared<lang::Value> false_value) override;
    Shared<lang::Value> performBooleanCollapse(Shared<lang::Value> value) override;

    llvm::IRBuilder<>&   ir() override;
    llvm::DIBuilder&     di() override;
    llvm::LLVMContext&   llvmContext() override;
    llvm::Function*      llvmFunction(Function function) override;
    llvm::DIScope*       llvmScope(lang::Scope const& scope) override;
    llvm::Type*          llvmType(lang::Type const& type) override;

    llvm::DIType*   llvmDiType(lang::Type const& type);
    llvm::Constant* llvmDefault(lang::Type const& type);

  private:
    CompileContext& context_;

    llvm::LLVMContext&   llvm_context_;
    llvm::Module&        llvm_module_;
    llvm::DICompileUnit* llvm_di_unit_;
    llvm::IRBuilder<>&   ir_builder_;
    llvm::DIBuilder&     di_builder_;

    std::map<std::string, llvm::Constant*>    byte_strings_      = {};
    std::map<std::u32string, llvm::Constant*> codepoint_strings_ = {};
    std::map<std::string, llvm::Constant*>    c_strings_         = {};

    struct NativeFunction {
        llvm::Function*                                llvm_function;
        lang::ResolvingHandle<lang::Type>              return_type;
        std::vector<lang::ResolvingHandle<lang::Type>> parameter_types;
    };

    struct NativeType {
        llvm::Type*     llvm_type;
        llvm::DIType*   llvm_di_type;
        llvm::Constant* llvm_default;
    };

    struct NativeGlobalVariable {
        llvm::GlobalVariable*             llvm_variable;
        lang::ResolvingHandle<lang::Type> type;
    };

    struct NativeLocalVariable {
        llvm::Value*                      llvm_variable;
        lang::ResolvingHandle<lang::Type> type;
        lang::Identifier                  name;
    };

    std::vector<NativeFunction>       functions_;
    std::vector<NativeType>           types_;
    std::vector<NativeGlobalVariable> global_variables_;
    std::vector<NativeLocalVariable>  local_variables_;

    llvm::Function* current_function_ = nullptr;

    lang::Type const* current_recursive_type_      = nullptr;
    NativeType        current_recursive_native_type_ = {nullptr, nullptr, nullptr};
};

#endif
