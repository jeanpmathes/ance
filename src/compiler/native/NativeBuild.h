#ifndef ANCE_SRC_COMPILER_NATIVEBUILD_H_
#define ANCE_SRC_COMPILER_NATIVEBUILD_H_

#include "compiler/Execution.h"

#include <map>
#include <stack>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

class Execution;
class NativeBuilder;
class SourceTree;
class CompileTimeBuild;

/**
 * A class to build operations as native LLVM IR.
 */
class NativeBuild : public Execution
{
  public:
    NativeBuild(SourceTree&        tree,
                Runtime&           runtime,
                llvm::LLVMContext&   c,
                llvm::Module&        m,
                llvm::IRBuilder<>&   ir,
                llvm::DIBuilder&   di);
    ~NativeBuild() override = default;

    static void initialize();
    static void terminate();

    static llvm::GlobalValue::LinkageTypes getLinkage(lang::AccessModifier access);
    llvm::DILocation*                      getLocation(lang::Location location, llvm::DIScope* scope);

    void setActiveVisitor(NativeBuilder* visitor);
    void setCMP(CompileTimeBuild* cmp);

    Shared<lang::Constant> getDefault(lang::Type const& type) override;
    Shared<lang::Constant> getCodepointString(std::u32string const& string) override;
    Shared<lang::Constant> getByteString(std::string const& string) override;
    Shared<lang::Constant> getCString(std::string const& string) override;
    Shared<lang::Constant> getSizeN(std::size_t size) override;
    Shared<lang::Constant> getDiffN(std::ptrdiff_t diff) override;
    Shared<lang::Constant> getSizeOf(lang::Type const& type) override;
    Shared<lang::Constant> getN(std::variant<uint64_t, double> n, lang::Type const& type) override;
    Shared<lang::Constant> getNull(lang::Type const& type) override;
    Shared<lang::Constant> getBoolean(bool boolean, lang::Type const& type) override;
    Shared<lang::Constant> getInteger(llvm::APInt int_value, lang::Type const& type) override;
    Shared<lang::Constant> getFloatingPoint(llvm::APFloat float_value, lang::Type const& type) override;
    Shared<lang::Constant> getCodepoint(char32_t codepoint) override;
    Shared<lang::Constant> getArray(std::vector<Shared<lang::Constant>> values, lang::Type const& type) override;
    Shared<lang::Constant> getVector(std::vector<Shared<lang::Constant>> values, lang::Type const& type) override;
    Shared<lang::Constant> getStruct(std::vector<Shared<lang::Constant>> values, lang::Type const& type) override;

    void                registerFunction(lang::Function const& function) override;
    void defineFunctionBody(lang::Function const& function, std::function<void(FnCtx&)> const& builder) override;
    Shared<lang::Value> performFunctionCall(lang::Function const&            function,
                                            std::vector<Shared<lang::Value>> arguments) override;

    void registerStruct(lang::Type const&                                 type,
                        std::vector<std::reference_wrapper<lang::Member>> members,
                      lang::Location                                    definition_location) override;

    void registerAlias(lang::Type const& type, lang::Location definition_location) override;

    void registerReferenceType(lang::Type const& reference_type) override;
    void registerAddressType(lang::Type const& address_type) override;
    void registerOpaqueAddressType(lang::Type const& opaque_address_type) override;
    void registerVectorType(lang::Type const& vector_type) override;
    void registerIntegerType(lang::Type const& integer_type) override;
    void registerFloatingPointType(lang::Type const& floating_point_type) override;
    void registerBooleanType(lang::Type const& boolean_type) override;
    void registerUnitType(lang::Type const& unit_type) override;
    void registerCodepointType(lang::Type const& codepoint_type) override;
    void registerArrayType(lang::Type const& array_type) override;

    void                registerGlobalVariable(lang::GlobalVariable const& global_variable,
                                               bool                        is_imported,
                                             lang::GlobalInitializer     init) override;
    void                declareLocalVariable(lang::LocalVariable const& local_variable) override;
    void                defineLocalVariable(lang::LocalVariable const& local_variable,
                                            lang::Scope const&         scope,
                                            Optional<size_t>           parameter_index,
                                            lang::Location             location) override;
    Shared<lang::Value> computeInitializerValue(lang::LocalInitializer const& initializer) override;
    Shared<lang::Value> computeAddressOfVariable(lang::Variable const& variable) override;

    Shared<lang::Value> computeAsActualType(Shared<lang::Value> value) override;

    Shared<lang::Value> computeElementPointer(Shared<lang::Value> sequence,
                                              Shared<lang::Value> index,
                                              IndexingMode        mode,
                                              Optional<size_t>    bounds) override;
    Shared<lang::Value> computeMemberPointer(Shared<lang::Value>     struct_ptr,
                                             lang::Identifier const& member_name) override;
    Shared<lang::Value> computeAddressOf(Shared<lang::Value> value) override;
    Shared<lang::Value> computePointerToInteger(Shared<lang::Value> pointer) override;
    Shared<lang::Value> computeIntegerToPointer(Shared<lang::Value> integer, lang::Type const& pointer_type) override;
    Shared<lang::Value> computeCastedAddress(Shared<lang::Value> address, lang::Type const& new_type) override;
    Shared<lang::Value> computeConversionOnFP(Shared<lang::Value> value, lang::Type const& destination_type) override;
    Shared<lang::Value> computeConversionOnI(Shared<lang::Value> value, lang::Type const& destination_type) override;
    Shared<lang::Value> computeConversionFP2I(Shared<lang::Value> value, lang::Type const& destination_type) override;
    Shared<lang::Value> computeConversionI2FP(Shared<lang::Value> value, lang::Type const& destination_type) override;
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
    void                performMemoryClear(Shared<lang::Value> address, Shared<lang::Value> count) override;
    void                performMemoryCopy(Shared<lang::Value> destination,
                                          Shared<lang::Value> source,
                                          Shared<lang::Value> count) override;
    Shared<lang::Value> performStackAllocation(lang::Type const& type, Shared<lang::Value> count) override;
    Shared<lang::Value> performOperator(lang::UnaryOperator op, Shared<lang::Value> value) override;
    Shared<lang::Value> performOperator(lang::BinaryOperator op,
                                        Shared<lang::Value>  lhs,
                                        Shared<lang::Value>  rhs) override;
    Shared<lang::Value> performSelect(Shared<lang::Value> condition,
                                      Shared<lang::Value> true_value,
                                      Shared<lang::Value> false_value) override;
    Shared<lang::Value> performBooleanCollapse(Shared<lang::Value> value) override;

    Shared<lang::Value> performIntegerReinterpretation(Shared<lang::Value> value,
                                                       lang::Type const&   target_type) override;

    llvm::IRBuilder<>& ir();
    llvm::DIBuilder&   di();
    llvm::LLVMContext& llvmContext();
    llvm::Module&      llvmModule();
    llvm::DIScope*     llvmScope(lang::Scope const& scope);
    llvm::Type*        llvmType(lang::Type const& type);

    llvm::DIType*   llvmDiType(lang::Type const& type);
    llvm::Constant* llvmDefault(lang::Type const& type);

    llvm::Value*    llvmNativeValue(Shared<lang::Value> value);
    llvm::Value*    llvmContentValue(Shared<lang::Value> value);
    llvm::Constant* llvmConstant(Shared<lang::Constant> constant);

    llvm::Function* getCurrentFunction();
    void            setCurrentFunction(lang::Function const* function);

    /**
     * Get the debug information for a source file that contains the given location.
     * @param location The location.
     * @return The debug information for the source file.
     */
    llvm::DIFile* getSourceFile(lang::Location location);

    std::filesystem::path getSourceFilePath(lang::Location location) override;

    void        setDebugLocation(lang::Location location, lang::Scope const& scope) override;
    void        resetDebugLocation() override;
    bool        allDebugLocationsPopped() override;
    std::string getLocationString() override;

  private:
    NativeBuilder*  visitor_ = nullptr;
    CompileTimeBuild* cmp_build_ = nullptr;

    llvm::LLVMContext&   llvm_context_;
    llvm::Module&        llvm_module_;
    llvm::IRBuilder<>&   ir_builder_;
    llvm::DIBuilder&     di_builder_;
    llvm::DICompileUnit* llvm_di_unit_ = nullptr;

    std::map<std::string, llvm::Constant*>    byte_strings_      = {};
    std::map<std::u32string, llvm::Constant*> codepoint_strings_ = {};
    std::map<std::string, llvm::Constant*>    c_strings_         = {};

    struct NativeFunction {
        llvm::Function*                                       llvm_function;
        bool                                                  preserve_unit_return;
        lang::Type const&                                     return_type;
        std::vector<std::reference_wrapper<lang::Type const>> parameter_types;
    };

    struct NativeType {
        llvm::Type*     llvm_type;
        llvm::DIType*   llvm_di_type;
        llvm::Constant* llvm_default;
    };

    struct NativeGlobalVariable {
        llvm::GlobalVariable* llvm_variable;
        lang::Type const&     type;
    };

    struct NativeLocalVariable {
        llvm::Value*      llvm_variable;
        lang::Type const& type;
        lang::Identifier  name;
    };

    std::map<lang::Function const*, NativeFunction>       functions_;
    std::map<lang::Type const*, NativeType>               types_;
    std::map<lang::Variable const*, NativeGlobalVariable> global_variables_;
    std::map<lang::Variable const*, NativeLocalVariable>  local_variables_;

    NativeType& getNativeType(lang::Type const& type);

    lang::Type const* current_recursive_type_        = nullptr;
    NativeType        current_recursive_native_type_ = {nullptr, nullptr, nullptr};

    struct DebugLocation {
        llvm::DebugLoc di_location;
        lang::Location location;
    };

    DebugLocation current_debug_location_ {.di_location = {}, .location = lang::Location::global()};
    std::stack<DebugLocation, std::vector<DebugLocation>> debug_loc_stack_;

    struct SourceFile {
        std::filesystem::path path;
        llvm::DIFile*         debug_info;
    };

    std::vector<SourceFile> source_files_ {};

    class NativeFnCtx : public FnCtx
    {
      public:
        ~NativeFnCtx() override = default;
        NativeFnCtx(NativeBuild& build, NativeFunction& function);

        Shared<lang::Value> getParameterValue(size_t index) override;
        Execution&          exec() override;

        [[nodiscard]] llvm::Function*   llvmFunction() const;
        [[nodiscard]] lang::Type const& returnType() const;
        [[nodiscard]] bool              preserveUnitReturn() const;

      private:
        NativeBuild&    build_;
        NativeFunction& function_;
    };

    Optional<Owned<NativeFnCtx>> current_fn_ctx_ = {};
};

#endif
