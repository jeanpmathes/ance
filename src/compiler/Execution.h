#ifndef ANCE_SRC_COMPILER_EXECUTION_H_
#define ANCE_SRC_COMPILER_EXECUTION_H_

#include <variant>

#include "lang/AccessModifier.h"
#include "lang/BinaryOperator.h"
#include "lang/UnaryOperator.h"
#include "lang/construct/Parameter.h"
#include "lang/construct/constant/Constant.h"
#include "lang/construct/value/Value.h"
#include "lang/utility/ResolvingHandle.h"

class ConstantExpression;

namespace lang
{
    class Function;
    class Member;

    using Initializer =
        Optional<std::variant<std::reference_wrapper<lang::Function>, std::reference_wrapper<ConstantExpression>>>;
}

/**
 * An interface to define execution of a program.
 * Implementors might build LLVM IR or directly calculate the result.
 */
class Execution
{
  public:
    /**
     * Get the default value for the given type.
     * @param type The type to get the default value for.
     * @return The default value.
     */
    virtual Shared<lang::Value> getDefaultValue(lang::ResolvingHandle<lang::Type> type) = 0;

    /**
     * Get the given string as a constant.
     * @param string The string to get as a constant.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getCString(std::string string) = 0;

    /**
     * Get the given size as a constant.
     * @param size The size to get as a constant.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getSizeValue(std::size_t size) = 0;

    /**
     * Get the given difference as a constant.
     * @param diff The difference to get as a constant.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getDiffValue(std::ptrdiff_t diff) = 0;

    /**
     * Get the size of the given type as a constant.
     * @param type The type to get the size of.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getSizeOf(lang::ResolvingHandle<lang::Type> type) = 0;

    /**
     * Get the given number as a constant.
     * @param n The number to get as a constant.
     * @param type The type to get the number as, must be a numeric type or a vector of numeric types.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getN(std::variant<uint64_t, double> n, lang::ResolvingHandle<lang::Type> type) = 0;

    /**
     * Get the zero value for the given type.
     * @param type The type to get the zero value for, must be a numeric type or a vector of numeric types.
     * @return The zero value.
     */
    virtual Shared<lang::Constant> getZero(lang::ResolvingHandle<lang::Type> type) = 0;

    /**
     * Get the one value for the given type.
     * @param type The type to get the one value for, must be a numeric type or a vector of numeric types.
     * @return The one value.
     */
    virtual Shared<lang::Constant> getOne(lang::ResolvingHandle<lang::Type> type) = 0;

    /**
     * Get the null value for the given type.
     * @param type The type to get the null value for, must be a pointer or buffer type.
     * @return The null value.
     */
    virtual Shared<lang::Constant> getNull(lang::ResolvingHandle<lang::Type> type) = 0;

    /**
     * Get the given boolean as a constant.
     * @param boolean The boolean to get as a constant.
     * @param type The type to get the boolean as, can be either the boolean type or a vector of it.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getBoolean(bool boolean, lang::ResolvingHandle<lang::Type> type) = 0;

    /**
     * Get the given integer as a constant.
     * @param int_value The integer to get as a constant.
     * @param type The type to get the integer as, can be either the integer type or a vector of it.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getInteger(llvm::APInt int_value, lang::ResolvingHandle<lang::Type> type) = 0;

    virtual llvm::Constant* getBooleanConstant(bool boolean)                  = 0;
    virtual llvm::Constant* getCodepointConstant(char32_t codepoint)          = 0;
    virtual llvm::Constant* getByteConstant(uint8_t byte)                     = 0;
    virtual llvm::Constant* getFloatConstant(llvm::APFloat float_value)       = 0;
    virtual llvm::Constant* getIntegerConstant(llvm::APInt int_value)         = 0;
    virtual llvm::Constant* getByteStringConstant(std::string string)         = 0;
    virtual llvm::Constant* getCodepointStringConstant(std::u32string string) = 0;
    virtual llvm::Constant* getCStringConstant(std::string string)            = 0;

    enum class Application : size_t
    {
        GLOBAL_SCOPE
    };
    enum class Function : size_t
    {
    };
    enum class Struct : size_t
    {
    };
    enum class Alias : size_t
    {
    };
    enum class BasicType : size_t
    {
    };

    using Scoped = std::variant<Application, Function, Struct>;
    using Type   = std::variant<Struct, Alias, BasicType>;

    enum class GlobalVariable : size_t
    {
    };
    enum class LocalVariable : size_t
    {
    };

    using Variable = std::variant<GlobalVariable, LocalVariable>;

    /**
     * Create a function.
     * @param name The name of the function.
     * @param linkage_name The name of the function in native code.
     * @param access The access modifier of the function. Use std::nullopt for runtime functions.
     * @param is_imported Whether the function is imported.
     * @param parameters The parameters of the function.
     * @param return_type The return type of the function.
     * @param scope The scope of the function, or nullptr if the function is not part of a scope. Must be supplied for functions with a definition.
     * @param preserve_unit Whether to preserve a unit return type. Used e.g. for constructors, as they can't return void.
     * @param declaration_location The location of the function declaration.
     * @param definition_location The location of the function definition, meaning the code block. If no debug data is needed, use std::nullopt, else the location or global location if the function has no definition.
     * @return A handle to the function.
     */
    virtual Function createFunction(lang::Identifier const&               name,
                                    std::string const&                    linkage_name,
                                    Optional<lang::AccessModifier>        access,
                                    bool                                  is_imported,
                                    std::vector<Shared<lang::Parameter>>& parameters,
                                    lang::ResolvingHandle<lang::Type>     return_type,
                                    lang::Scope*                          scope,
                                    bool                                  preserve_unit,
                                    lang::Location                        declaration_location,
                                    Optional<lang::Location>              definition_location) = 0;

    /**
     * Indicate that the following commands are part of the body of the given function.
     * If the state is currently in another function, the function is exited first.
     * @param function The function to enter.
     */
    virtual void enterFunctionBody(Function function) = 0;

    /**
     * Call a function.
     * @param function The function to call.
     * @param arguments The arguments to pass to the function.
     * @return The result of the function call.
     */
    virtual Shared<lang::Value> performFunctionCall(Function function, std::vector<Shared<lang::Value>> arguments) = 0;

    /**
     * Create a struct type for execution.
     * @param name The name of the struct.
     * @param access The access modifier of the struct.
     * @param type The struct type in the AST.
     * @param members The members of the struct.
     * @param scope The scope in which the struct is defined.
     * @param definition_location The location of the struct.
     * @return The handle to the struct.
     */
    virtual Struct createStruct(lang::Identifier                                  name,
                                lang::AccessModifier                              access,
                                lang::Type const&                                 type,
                                std::vector<std::reference_wrapper<lang::Member>> members,
                                lang::Scope const&                                scope,
                                lang::Location                                    definition_location) = 0;

    /**
     * Create an alias for a type.
     * @param name The name of the alias.
     * @param access The access modifier of the alias.
     * @param actual_type The type to alias.
     * @param scope The scope in which the alias is defined.
     * @param definition_location The location of the alias.
     * @return The handle to the alias.
     */
    virtual Alias createAlias(lang::Identifier     name,
                              lang::AccessModifier access,
                              lang::Type const&    actual_type,
                              lang::Scope const&   scope,
                              lang::Location       definition_location) = 0;

    /**
     * Register a reference type for execution.
     * @param reference_type The type to register.
     * @return The handle to the reference type.
     */
    virtual BasicType registerReferenceType(lang::Type const& reference_type) = 0;

    /**
     * Register an address type for execution.
     * @param address_type The type to register.
     * @return The handle to the address type.
     */
    virtual BasicType registerAddressType(lang::Type const& address_type) = 0;

    /**
     * Register an opaque address type for execution.
     * @param opaque_pointer_type The type to register.
     * @return The handle to the opaque address type.
     */
    virtual BasicType registerOpaqueAddressType(lang::Type const& opaque_pointer_type) = 0;

    /**
     * Register a vector type for execution.
     * @param vector_type The type to register.
     * @return The handle to the vector type.
     */
    virtual BasicType registerVectorType(lang::Type const& vector_type) = 0;

    /**
     * Register an integer type for execution.
     * @param integer_type The type to register.
     * @return The handle to the integer type.
     */
    virtual BasicType registerIntegerType(lang::Type const& integer_type) = 0;

    /**
     * Register a floating point type for execution.
     * @param floating_point_type The type to register.
     * @return The handle to the floating point type.
     */
    virtual BasicType registerFloatingPointType(lang::Type const& floating_point_type) = 0;

    /**
     * Register a boolean type for execution.
     * @param boolean_type The type to register.
     * @return The handle to the boolean type.
     */
    virtual BasicType registerBooleanType(lang::Type const& boolean_type) = 0;

    /**
     * Register a unit type for execution.
     * @param unit_type The type to register.
     * @return The handle to the unit type.
     */
    virtual BasicType registerUnitType(lang::Type const& unit_type) = 0;

    /**
     * Register a code point type for execution.
     * @param codepoint_type The type to register.
     * @return The handle to the code point type.
     */
    virtual BasicType registerCodepointType(lang::Type const& codepoint_type) = 0;

    /**
     * Register an array type for execution.
     * @param array_type The type to register.
     * @return The handle to the array type.
     */
    virtual BasicType registerArrayType(lang::Type const& array_type) = 0;

    /**
     * Create a global variable.
     * @param name The name of the global variable.
     * @param access The access modifier of the global variable.
     * @param is_imported Whether the global variable is imported.
     * @param type The type of the global variable.
     * @param is_constant Whether the global variable is constant.
     * @param init The initializer of the global variable.
     * @param location The location of the global variable.
     * @return The handle to the global variable.
     */
    virtual GlobalVariable createGlobalVariable(lang::Identifier                  name,
                                                lang::AccessModifier              access,
                                                bool                              is_imported,
                                                lang::ResolvingHandle<lang::Type> type,
                                                bool                              is_constant,
                                                lang::Initializer                 init,
                                                lang::Location                    location) = 0;

    /**
     * Declare a local variable.
     * @param name The name of the local variable.
     * @param type The type of the local variable.
     * @return The handle to the local variable.
     */
    virtual LocalVariable declareLocalVariable(lang::Identifier const&           name,
                                               lang::ResolvingHandle<lang::Type> type) = 0;

    /**
     * Define a local variable.
     * @param variable The variable to define.
     * @param scope The scope in which the variable is defined.
     * @param parameter_index The index of the parameter that the variable is an alias for, if any.
     * @param location The location of the variable.
     */
    virtual void defineLocalVariable(Execution::LocalVariable variable,
                                     lang::Scope&             scope,
                                     Optional<unsigned>       parameter_index,
                                     lang::Location           location) = 0;

    /**
     * Get the address of a variable.
     * @param variable The variable to get the address of.
     * @return The address of the variable.
     */
    virtual Shared<lang::Value> computeAddressOfVariable(Variable variable) = 0;

    /**
     * Compute the size in bytes of an allocation of the given type.
     * @param type The type to compute the size of.
     * @param count The number of elements that are allocated. If no count is given, the size of a single element is returned.
     * @return The size of the allocation, as a value with type 'size'.
     */
    virtual Shared<lang::Value> computeAllocatedSize(lang::ResolvingHandle<lang::Type> type,
                                                     Optional<Shared<lang::Value>>     count) = 0;

    enum class IndexingMode
    {
        SEQUENCE,
        POINTER,
    };

    /**
     * Compute the pointer to an element of a sequence.
     * @param sequence The sequence, must be an address.
     * @param index The index to perform the operation with, of type 'diff'.
     * @param mode The mode in which the indexing is performed. If the mode is SEQUENCE, sequence must be of type pointer to array/vector.
     * @param bounds The bounds of the sequence, if known.
     * @return The resulting pointer.
     */
    virtual Shared<lang::Value> computeElementPointer(Shared<lang::Value> sequence,
                                                      Shared<lang::Value> index,
                                                      IndexingMode        mode,
                                                      Optional<size_t>    bounds) = 0;

    /**
     * Compute the pointer to a member of a struct.
     * @param struct_ptr The pointer to the struct.
     * @param member_name The name of the member.
     * @return The resulting pointer.
     */
    virtual Shared<lang::Value> computeMemberPointer(Shared<lang::Value>     struct_ptr,
                                                     lang::Identifier const& member_name) = 0;

    /**
     * Get the address of a value.
     * If the value is a reference, the reference is just casted to a pointer.
     * @param value The value to get the address of.
     * @return A pointer to the value.
     */
    virtual Shared<lang::Value> computeAddressOf(Shared<lang::Value> value) = 0;

    /**
     * Compute the integer value of a pointer.
     * @param pointer The pointer to compute the integer from, must be of address type or a vector of address type.
     * @return An integer of type 'uiptr'.
     */
    virtual Shared<lang::Value> computePointerToInteger(Shared<lang::Value> pointer) = 0;

    /**
     * Compute the pointer value of an integer.
     * @param integer The integer to compute the pointer from, must be of type 'uiptr' or a vector of type 'uiptr'.
     * @param pointer_type The type of the pointer to compute.
     * @return A pointer of address type.
     */
    virtual Shared<lang::Value> computeIntegerToPointer(Shared<lang::Value>               integer,
                                                        lang::ResolvingHandle<lang::Type> pointer_type) = 0;

    /**
     * Compute an address cast.
     * @param address The address to cast, must be either a pointer or buffer - or a vector of pointers or buffers.
     * @param new_type The new type of the address, must be either a pointer or buffer - or a vector of pointers or buffers.
     * @return The casted address.
     */
    virtual Shared<lang::Value> computeCastedAddress(Shared<lang::Value>               address,
                                                     lang::ResolvingHandle<lang::Type> new_type) = 0;

    /**
     * Compute a floating point conversion.
     * @param value The value to convert. Must be a floating point value or a vector of floating point values.
     * @param destination_type The type to convert to. Must be a floating point type or a vector of floating point types.
     * @return The converted value.
     */
    virtual Shared<lang::Value> computeConversionOnFP(Shared<lang::Value>               value,
                                                      lang::ResolvingHandle<lang::Type> destination_type) = 0;

    /**
     * Compute an integer conversion.
     * @param value The value to convert. Must be an integer value or a vector of integer values.
     * @param destination_type The type to convert to. Must be an integer type or a vector of integer types.
     * @return The converted value.
     */
    virtual Shared<lang::Value> computeConversionOnI(Shared<lang::Value>               value,
                                                     lang::ResolvingHandle<lang::Type> destination_type) = 0;

    /**
     * Compute an floating point to integer conversion.
     * @param value The value to convert. Must be a floating point value or a vector of floating point values.
     * @param destination_type The type to convert to. Must be an integer type or a vector of integer types.
     * @return The converted value.
     */
    virtual Shared<lang::Value> computeConversionFP2I(Shared<lang::Value>               value,
                                                      lang::ResolvingHandle<lang::Type> destination_type) = 0;

    /**
     * Compute an integer to floating point conversion.
     * @param value The value to convert. Must be an integer value or a vector of integer values.
     * @param destination_type The type to convert to. Must be a floating point type or a vector of floating point types.
     * @return The converted value.
     */
    virtual Shared<lang::Value> computeConversionI2FP(Shared<lang::Value>               value,
                                                      lang::ResolvingHandle<lang::Type> destination_type) = 0;

    /**
     * Compute the pointer to a value from a reference.
     * @param reference The reference to compute the pointer from.
     * @return The pointer to the value, the element type will be the same as the element type of the reference.
     */
    virtual Shared<lang::Value> computePointerFromReference(Shared<lang::Value> reference) = 0;

    /**
     * Compute the reference to a value from a pointer.
     * @param pointer The pointer to compute the pointer from.
     * @return The reference to the value, the element type will be the same as the element type of the pointer.
     */
    virtual Shared<lang::Value> computeReferenceFromPointer(Shared<lang::Value> pointer) = 0;

    /**
     * Compute whether the given address is not null.
     * @param address The address to check, must be a pointer, buffer or vector of those.
     * @return True if the address is not null, false otherwise.
     */
    virtual Shared<lang::Value> computeAddressIsNotNull(Shared<lang::Value> address) = 0;

    /**
     * Compute the difference between two addresses.
     * @param lhs The left hand side address, must be a pointer, buffer or vector of those.
     * @param rhs The right hand side address, must be a pointer, buffer or vector of those.
     * @return The difference between the addresses, the result will be of type 'diff' or a vector of 'diff'.
     */
    virtual Shared<lang::Value> computeAddressDiff(Shared<lang::Value> lhs, Shared<lang::Value> rhs) = 0;

    /**
     * Perform a load from the given address. Must use indirection so that computing the address of the return value will yield the given address.
     * @param address The address to load from, must be a pointer.
     * @return The value, with the pointee type, that was loaded.
     */
    virtual Shared<lang::Value> performLoadFromAddress(Shared<lang::Value> address) = 0;

    /**
     * Perform a dereference of the given reference.
     * This is a combination of using ::computeAddressOf and ::performLoadFromAddress.
     * @param reference The reference to dereference.
     * @return The value that was dereferenced.
     */
    Shared<lang::Value> performDereference(Shared<lang::Value> reference);

    /**
     * Perform a store to the given address.
     * @param address The address to store to, must be a pointer.
     * @param value The value to store.
     */
    virtual void performStoreToAddress(Shared<lang::Value> address, Shared<lang::Value> value) = 0;

    /**
     * Perform an iteration over a pointed region of memory.
     * Further commands will be placed after the iteration.
     * @param pointer The pointer to the first element of the region.
     * @param count The number of elements in the region, given as a value with type 'size'.
     * @param body A function that is called to build the body of the iteration. The passed value represents a pointer to the current element.
     */
    virtual void performPointerIteration(Shared<lang::Value>                      pointer,
                                         Shared<lang::Value>                      count,
                                         std::function<void(Shared<lang::Value>)> body) = 0;

    /**
     * Perform a return from the current function, optionally with a value.
     * @param value The value to return.
     */
    virtual void performReturn(Optional<Shared<lang::Value>> value) = 0;

    /**
     * Clear a memory region.
     * @param address The address of the memory region to clear.
     * @param size The size of the region, in bytes, given as a value with type 'size'.
     */
    virtual void performMemoryClear(Shared<lang::Value> address, Shared<lang::Value> size) = 0;

    /**
     * Copy a memory region.
     * @param destination The address of the destination memory region.
     * @param source The address of the source memory region.
     * @param size The size of the region, in bytes, given as a value with type 'size'.
     */
    virtual void performMemoryCopy(Shared<lang::Value> destination,
                                   Shared<lang::Value> source,
                                   Shared<lang::Value> size) = 0;

    /**
     * Perform a stack allocation.
     * @param type The type to allocate.
     * @return A pointer to the allocated memory.
     */
    Shared<lang::Value> performStackAllocation(lang::ResolvingHandle<lang::Type> type);

    /**
     * Perform a stack allocation.
     * @param type The type to allocate.
     * @param count The number of elements to allocate, given as a value with type 'size'.
     * @return A pointer to the allocated memory.
     */
    virtual Shared<lang::Value> performStackAllocation(lang::ResolvingHandle<lang::Type> type,
                                                       Shared<lang::Value>               count) = 0;

    /**
     * Perform a unary operator.
     * @param op The operator to perform.
     * @param value The value to perform the operator on. Must be a scalar or a vector and must have a numeric/boolean type.
     * @return The result of the operation.
     */
    virtual Shared<lang::Value> performOperator(lang::UnaryOperator op, Shared<lang::Value> value) = 0;

    /**
     * Perform a binary operator.
     * @param op The operator to perform.
     * @param lhs The left hand side of the operation. Must be a scalar or a vector and must have a numeric/boolean type.
     * @param rhs The right hand side of the operation. Must be a scalar or a vector and must have a numeric/boolean type.
     * @return The result of the operation.
     */
    virtual Shared<lang::Value> performOperator(lang::BinaryOperator op,
                                                Shared<lang::Value>  lhs,
                                                Shared<lang::Value>  rhs) = 0;

    /**
     * Perform a select operation.
     * @param condition The condition to select on. Must be a boolean value or a vector of boolean values.
     * @param true_value The value to select if the condition is true. Can be of vector type.
     * @param false_value The value to select if the condition is false. Can be of vector type.
     * @return The selected value.
     */
    virtual Shared<lang::Value> performSelect(Shared<lang::Value> condition,
                                              Shared<lang::Value> true_value,
                                              Shared<lang::Value> false_value) = 0;

    /**
     * Perform a collapse of a boolean value by ANDing all elements together.
     * @param value The value to collapse. Must be a boolean value or a vector of boolean values.
     * @return The collapsed value. If the value is a vector, the result will be a scalar.
     */
    virtual Shared<lang::Value> performBooleanCollapse(Shared<lang::Value> value) = 0;

    virtual llvm::IRBuilder<>&   ir()                                               = 0;
    virtual llvm::DIBuilder&     di()                                               = 0;
    virtual llvm::Module&        llvmModule()                                       = 0;
    virtual llvm::LLVMContext&   llvmContext()                                      = 0;
    virtual llvm::DICompileUnit& llvmUnit()                                         = 0;
    virtual llvm::Function*      llvmFunction(Function function)                    = 0;
    virtual llvm::DIScope*       llvmScope(Scoped scope)                            = 0;
    virtual llvm::DIType*        llvmType(Type type)                                = 0;
    virtual llvm::TypeSize       llvmSizeOf(lang::ResolvingHandle<lang::Type> type) = 0;

    virtual ~Execution() = default;
};

#endif
