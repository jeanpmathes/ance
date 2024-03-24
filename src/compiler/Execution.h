#ifndef ANCE_SRC_COMPILER_EXECUTION_H_
#define ANCE_SRC_COMPILER_EXECUTION_H_

#include <any>
#include <filesystem>
#include <map>
#include <utility>
#include <variant>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/AccessModifier.h"
#include "lang/BinaryOperator.h"
#include "lang/UnaryOperator.h"
#include "lang/utility/Identifier.h"
#include "lang/utility/Optional.h"
#include "lang/utility/Owners.h"

class Expression;
class LiteralExpression;
class Unit;
class Runtime;

namespace lang
{
    class Function;
    class Variable;
    class GlobalVariable;
    class LocalVariable;
    class Member;
    class Scope;
    class Type;
    class Context;

    class Parameter;
    class Constant;
    class Value;

    using GlobalInitializer =
        Optional<std::variant<std::reference_wrapper<lang::Function>, std::reference_wrapper<LiteralExpression>>>;

    using LocalParameterInitializer = std::pair<std::reference_wrapper<lang::Function const>, size_t>;

    using LocalInitializer = Optional<std::variant<std::reference_wrapper<Expression>, LocalParameterInitializer>>;
}

/**
 * An interface to define execution of a program.
 * Implementors might build LLVM IR or directly calculate the result.
 */
class Execution
{
  public:
    Execution(Unit& unit, Runtime& runtime);
    virtual ~Execution() = default;

    /**
     * Get the default constant for the given type.
     * @param type The type to get the constant value for.
     * @return The default constant.
     */
    virtual Shared<lang::Constant> getDefault(lang::Type const& type) = 0;

    /**
     * Get the given string as a constant.
     * @param string The string to get as a constant.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getCodepointString(std::u32string const& string) = 0;

    /**
     * Get the given string as a constant.
     * @param string The string to get as a constant.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getByteString(std::string const& string) = 0;

    /**
     * Get the given string as a constant.
     * @param string The string to get as a constant.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getCString(std::string const& string) = 0;

    /**
     * Get the given size as a constant.
     * @param size The size to get as a constant.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getSizeN(std::size_t size) = 0;

    /**
     * Get the given difference as a constant.
     * @param diff The difference to get as a constant.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getDiffN(std::ptrdiff_t diff) = 0;

    /**
     * Get the size of the given type as a constant.
     * @param type The type to get the size of.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getSizeOf(lang::Type const& type) = 0;

    /**
     * Get the given number as a constant.
     * @param n The number to get as a constant.
     * @param type The type to get the number as, must be a numeric type or a vector of numeric types.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getN(std::variant<uint64_t, double> n, lang::Type const& type) = 0;

    /**
     * Get the zero value for the given type.
     * @param type The type to get the zero value for, must be a numeric type or a vector of numeric types.
     * @return The zero value.
     */
    virtual Shared<lang::Constant> getZero(lang::Type const& type) = 0;

    /**
     * Get the one value for the given type.
     * @param type The type to get the one value for, must be a numeric type or a vector of numeric types.
     * @return The one value.
     */
    virtual Shared<lang::Constant> getOne(lang::Type const& type) = 0;

    /**
     * Get the null value for the given type.
     * @param type The type to get the null value for, must be a pointer or buffer type.
     * @return The null value.
     */
    virtual Shared<lang::Constant> getNull(lang::Type const& type) = 0;

    /**
     * Get the given boolean as a constant.
     * @param boolean The boolean to get as a constant.
     * @param type The type to get the boolean as, can be either the boolean type or a vector of it.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getBoolean(bool boolean, lang::Type const& type) = 0;

    /**
     * Get the given integer as a constant.
     * @param int_value The integer to get as a constant.
     * @param type The type to get the integer as, can be either the integer type or a vector of it.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getInteger(llvm::APInt int_value, lang::Type const& type) = 0;

    /**
     * Get the given float as a constant.
     * @param float_value The float to get as a constant.
     * @param type The type to get the float as, can be either the float type or a vector of it.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getFloatingPoint(llvm::APFloat float_value, lang::Type const& type) = 0;

    /**
     * Get the given codepoint value as a constant.
     * @param codepoint The codepoint to get as a constant.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getCodepoint(char32_t codepoint) = 0;

    /**
     * Get the given byte value as a constant.
     * @param byte The byte to get as a constant.
     * @return The constant.
     */
    virtual Shared<lang::Constant> getByte(uint8_t byte) = 0;

    /**
     * Register a function.
     * This is necessary to call the function.
     * @param function The AST function to register.
     */
    virtual void registerFunction(lang::Function const& function) = 0;

    /**
     * Get the value of a parameter of a function.
     * @param function The function to get the parameter value from.
     * @param index The index of the parameter.
     * @return The value of the parameter.
     */
    virtual Shared<lang::Value> getParameterValue(lang::Function const& function, size_t index) = 0;

    /**
     * Indicate that the following commands are part of the body of the given function.
     * If the state is currently in another function, the function is exited first.
     * All function operations must be performed in the builder.
     * The executor is allowed to call this function multiple times and store the lambda for later execution.
     * @param function The function of which the body is defined.
     * @param builder A function that is called to build the body of the function.
     */
    virtual void defineFunctionBody(lang::Function const&                       function, std::function<void(Execution&)> const& builder) = 0;

    /**
     * Call a function.
     * @param function The function to call.
     * @param arguments The arguments to pass to the function.
     * @return The result of the function call.
     */
    virtual Shared<lang::Value> performFunctionCall(lang::Function const&            function,
                                                    std::vector<Shared<lang::Value>> arguments) = 0;

    /**
     * Register a struct type for execution.
     * @param type The struct type in the AST.
     * @param members The members of the struct.
     * @param definition_location The location of the struct.
     */
    virtual void registerStruct(lang::Type const&                                 type,
                                std::vector<std::reference_wrapper<lang::Member>> members,
                              lang::Location                                    definition_location) = 0;

    /**
     * Register an alias for a type.
     * @param type The alias type, not the aliased type.
     * @param definition_location The location of the alias.
     */
    virtual void registerAlias(lang::Type const& type, lang::Location definition_location) = 0;

    /**
     * Register a reference type for execution.
     * @param reference_type The type to register.
     */
    virtual void registerReferenceType(lang::Type const& reference_type) = 0;

    /**
     * Register an address type for execution.
     * @param address_type The type to register.
     */
    virtual void registerAddressType(lang::Type const& address_type) = 0;

    /**
     * Register an opaque address type for execution.
     * @param opaque_pointer_type The type to register.
     */
    virtual void registerOpaqueAddressType(lang::Type const& opaque_pointer_type) = 0;

    /**
     * Register a vector type for execution.
     * @param vector_type The type to register.
     */
    virtual void registerVectorType(lang::Type const& vector_type) = 0;

    /**
     * Register an integer type for execution.
     * @param integer_type The type to register.
     */
    virtual void registerIntegerType(lang::Type const& integer_type) = 0;

    /**
     * Register a floating point type for execution.
     * @param floating_point_type The type to register.
     */
    virtual void registerFloatingPointType(lang::Type const& floating_point_type) = 0;

    /**
     * Register a boolean type for execution.
     * @param boolean_type The type to register.
     */
    virtual void registerBooleanType(lang::Type const& boolean_type) = 0;

    /**
     * Register a unit type for execution.
     * @param unit_type The type to register.
     */
    virtual void registerUnitType(lang::Type const& unit_type) = 0;

    /**
     * Register a code point type for execution.
     * @param codepoint_type The type to register.
     */
    virtual void registerCodepointType(lang::Type const& codepoint_type) = 0;

    /**
     * Register an array type for execution.
     * @param array_type The type to register.
     */
    virtual void registerArrayType(lang::Type const& array_type) = 0;

    /**
     * Register a global variable.
     * @param global_variable The global variable to register.
     * @param is_imported Whether the global variable is imported.
     * @param init The initializer of the global variable.
     */
    virtual void registerGlobalVariable(lang::GlobalVariable const& global_variable,
                                        bool                        is_imported,
                                      lang::GlobalInitializer     init) = 0;

    /**
     * Declare a local variable.
     * @param local_variable The local variable to declare.
     */
    virtual void declareLocalVariable(lang::LocalVariable const& local_variable) = 0;

    /**
     * Define a local variable.
     * @param local_variable The variable to define.
     * @param scope The scope in which the variable is defined.
     * @param parameter_index The index of the parameter that the variable is an alias for, if any.
     * @param location The location of the variable.
     */
    virtual void defineLocalVariable(lang::LocalVariable const& local_variable,
                                     lang::Scope const&         scope,
                                     Optional<size_t>           parameter_index,
                                     lang::Location             location) = 0;

    /**
     * Compute the value of a local initializer.
     * @param initializer The initializer to compute the value of.
     * @return The value of the initializer.
     */
    virtual Shared<lang::Value> computeInitializerValue(lang::LocalInitializer const& initializer) = 0;

    /**
     * Get the address of a variable.
     * @param variable The variable to get the address of.
     * @return The address of the variable.
     */
    virtual Shared<lang::Value> computeAddressOfVariable(lang::Variable const& variable) = 0;

    /**
     * Get the same value, but with the actual type of the value.
     * The actual type is the type an alias refers to.
     * If the value is not of alias type, the value is returned as is.
     * @param value The value to get the actual type of.
     * @return The value with the actual type.
     */
    virtual Shared<lang::Value> computeAsActualType(Shared<lang::Value> value) = 0;

    /**
     * Compute the size in bytes of an allocation of the given type.
     * @param type The type to compute the size of.
     * @param count The number of elements that are allocated. If no count is given, the size of a single element is returned.
     * @return The size of the allocation, as a value with type 'size'.
     */
    virtual Shared<lang::Value> computeAllocatedSize(lang::Type const& type, Optional<Shared<lang::Value>> count) = 0;

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
    virtual Shared<lang::Value> computeIntegerToPointer(Shared<lang::Value> integer,
                                                        lang::Type const&   pointer_type) = 0;

    /**
     * Compute an address cast.
     * @param address The address to cast, must be either a pointer or buffer - or a vector of pointers or buffers.
     * @param new_type The new type of the address, must be either a pointer or buffer - or a vector of pointers or buffers.
     * @return The casted address.
     */
    virtual Shared<lang::Value> computeCastedAddress(Shared<lang::Value> address, lang::Type const& new_type) = 0;

    /**
     * Compute a floating point conversion.
     * @param value The value to convert. Must be a floating point value or a vector of floating point values.
     * @param destination_type The type to convert to. Must be a floating point type or a vector of floating point types.
     * @return The converted value.
     */
    virtual Shared<lang::Value> computeConversionOnFP(Shared<lang::Value> value,
                                                      lang::Type const&   destination_type) = 0;

    /**
     * Compute an integer conversion.
     * @param value The value to convert. Must be an integer value or a vector of integer values.
     * @param destination_type The type to convert to. Must be an integer type or a vector of integer types.
     * @return The converted value.
     */
    virtual Shared<lang::Value> computeConversionOnI(Shared<lang::Value> value, lang::Type const& destination_type) = 0;

    /**
     * Compute an floating point to integer conversion.
     * @param value The value to convert. Must be a floating point value or a vector of floating point values.
     * @param destination_type The type to convert to. Must be an integer type or a vector of integer types.
     * @return The converted value.
     */
    virtual Shared<lang::Value> computeConversionFP2I(Shared<lang::Value> value,
                                                      lang::Type const&   destination_type) = 0;

    /**
     * Compute an integer to floating point conversion.
     * @param value The value to convert. Must be an integer value or a vector of integer values.
     * @param destination_type The type to convert to. Must be a floating point type or a vector of floating point types.
     * @return The converted value.
     */
    virtual Shared<lang::Value> computeConversionI2FP(Shared<lang::Value> value,
                                                      lang::Type const&   destination_type) = 0;

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
    Shared<lang::Value> performStackAllocation(lang::Type const& type);

    /**
     * Perform a stack allocation.
     * @param type The type to allocate.
     * @param count The number of elements to allocate, given as a value with type 'size'.
     * @return A pointer to the allocated memory.
     */
    virtual Shared<lang::Value> performStackAllocation(lang::Type const& type, Shared<lang::Value> count) = 0;

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

    /**
     * Reinterpret a integer-like value to another integer-like type.
     * @param value The value to reinterpret. Must be integer-like.
     * @param target_type The target type to reinterpret to. Must be integer-like and compatible with the source type.
     * @return The reinterpreted value.
     */
    virtual Shared<lang::Value> performIntegerReinterpretation(Shared<lang::Value> value,
                                                               lang::Type const&   target_type) = 0;

    /**
     * A handle that allows to refer to values and constants in the representation used by the concrete execution implementation.
     */
    template<bool IsConstant>
    struct Handle {
        Execution* execution;
        std::any   handle;

        Handle(Execution* exec, std::any h) : execution(exec), handle(std::move(h)) {}

        Handle(Handle const& other)            = delete;
        Handle& operator=(Handle const& other) = delete;

        Handle(Handle&& other) noexcept : execution(other.execution), handle(other.handle) { other.handle = nullptr; }
        Handle& operator=(Handle&& other) noexcept
        {
            execution    = other.execution;
            handle       = other.handle;
            other.handle = nullptr;
            return *this;
        }

        ~Handle()
        {
            if (not handle.has_value()) return;

            if constexpr (IsConstant) execution->releaseConstant(handle);
            else execution->releaseValue(handle);
        }
    };

    virtual void releaseValue(std::any handle)    = 0;
    virtual void releaseConstant(std::any handle) = 0;

    Unit&          unit();
    Runtime&       runtime();
    lang::Context& ctx();

    /**
     * Get the path to the source file that contains the given location.
     * @param location The location.
     * @return The path to the source file.
     */
    virtual std::filesystem::path getSourceFilePath(lang::Location location) = 0;

    /**
     * Set the current debug location.
     * @param location The source location.
     * @param scope The current scope.
     */
    virtual void setDebugLocation(lang::Location location, lang::Scope const& scope) = 0;

    /**
     * Reset the previous debug location.
     */
    virtual void resetDebugLocation() = 0;

    /**
     * Get whether all debug locations were popped.
     * @return True if all locations were popped correctly.
     */
    virtual bool allDebugLocationsPopped() = 0;

    /**
     * Get a string describing the current location in the source code.
     * @return The location string.
     */
    virtual std::string getLocationString() = 0;

  private:
    Unit&    unit_;
    Runtime& runtime_;
};

#endif
