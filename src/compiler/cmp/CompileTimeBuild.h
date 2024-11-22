#ifndef ANCE_SRC_COMPILER_CMP_COMPILETIMEBUILD_H_
#define ANCE_SRC_COMPILER_CMP_COMPILETIMEBUILD_H_

#include "compiler/Execution.h"

#include <stack>
#include <variant>

#include "lang/utility/ResolvingHandle.h"

class CompileTimeBuilder;
class CompileTimeValue;

class NativeBuild;

class CompileTimeBuild : public Execution
{
  public:
    CompileTimeBuild(Unit& unit, Runtime& runtime, NativeBuild& native);
    ~CompileTimeBuild() override = default;

    void setActiveVisitor(CompileTimeBuilder* visitor);

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

    void registerFunction(lang::Function const& function) override;
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

    void                declareGlobalVariable(lang::GlobalVariable const& global_variable) override;
    void                defineGlobalVariable(lang::GlobalVariable const& global_variable) override;
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

    /**
     * Get the value of a global variable.
     * @param variable The global variable.
     * @param exec The execution context in which to embed the value.
     * @return The value of the global variable.
     */
    Shared<lang::Constant> getGlobalVariableValue(lang::GlobalVariable const& variable, Execution& exec);

    std::filesystem::path getSourceFilePath(lang::Location location) override;
    void                  pushSourceLocation(lang::Location location, lang::Scope const& scope) override;
    void                  popSourceLocation() override;
    bool                  allSourceLocationsPopped() override;
    lang::Location        getCurrentSourceLocation() override;

    struct Address {
        friend class CompileTimeBuild;

        static Address const NULL_ADDRESS;

        Address() = default;

        enum class Location
        {
            Local,
            Global,
            Null
        };

      private:
        size_t              memory_index_  = 0;
        size_t              array_index_   = 0;
        std::vector<size_t> inner_indices_ = {};

        Location location_ = Location::Null;

      public:
        Address(Location location, size_t memory_index);

        bool operator==(Address const& other) const;
        bool operator!=(Address const& other) const;

        Address operator+(ptrdiff_t offset) const;
        Address operator+(size_t offset) const;

        [[nodiscard]] Address inner(ptrdiff_t index) const;
        [[nodiscard]] Address inner(size_t index) const;

        [[nodiscard]] size_t              memory() const;
        [[nodiscard]] size_t              array() const;
        [[nodiscard]] std::vector<size_t> inners() const;
        [[nodiscard]] Location            location() const;

        [[nodiscard]] std::string toString() const;
    };

    Address allocateLocal(lang::Type const& type, size_t count = 1);
    Address allocateGlobal(lang::Type const& type, size_t count = 1);

    Shared<CompileTimeValue> load(Address const& address);
    void                     store(Address address, Shared<CompileTimeValue> value);

    Shared<CompileTimeValue> cmpContentOf(Shared<lang::Value> value);
    Address                  cmpAddressOf(Shared<lang::Value> value);
    Shared<CompileTimeValue> cmpAddressValueOf(Shared<lang::Value> value);

    Shared<CompileTimeValue> cmpHandledValueOf(Shared<lang::Value> value);// todo: remove
    Shared<CompileTimeValue> cmpHandledValueOf(Address address, lang::Type const& type);

    using Memory    = std::vector<std::vector<Shared<CompileTimeValue>>>;
    using Variables = std::map<lang::Variable const*, Address>;
    Memory& memory(Address::Location location);

  private:
    lang::Context& context_;
    NativeBuild&   native_;

    CompileTimeBuilder* visitor_ = nullptr;

    struct TypeInformation {
        Shared<lang::Constant> default_value;
    };

    std::map<lang::Type const*, TypeInformation> type_information_;

    TypeInformation& getTypeInformation(lang::Type const& type);

    struct FunctionInformation {
        std::function<void(FnCtx&)> body;
    };

    std::map<lang::Function const*, FunctionInformation> function_information_;

    FunctionInformation& getFunctionInformation(lang::Function const& function);

    std::map<std::u32string, Shared<CompileTimeValue>> codepoint_strings_;
    std::map<std::string, Shared<CompileTimeValue>>    byte_strings_;
    std::map<std::string, Shared<CompileTimeValue>>    c_strings_;

    std::stack<lang::Location> source_locations_;

    Memory    global_memory_;
    Variables global_variables_;

    class CmpFnCtx : public FnCtx
    {
      public:
        ~CmpFnCtx() override = default;

        CmpFnCtx(lang::Function const& fn, CompileTimeBuild& build, std::vector<Shared<lang::Value>> arguments);

        Shared<lang::Value> getParameterValue(size_t index) override;
        Execution&          exec() override;
        lang::Function const& function() override;

        Memory                             memory;
        Variables                          variables;
        Optional<Shared<CompileTimeValue>> return_value;

      private:
        lang::Function const&            function_;
        CompileTimeBuild&                build_;
        std::vector<Shared<lang::Value>> arguments_;
    };

    std::stack<CmpFnCtx> fns_;
};

#endif
