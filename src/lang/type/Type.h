#ifndef ANCE_SRC_LANG_TYPE_TYPE_H_
#define ANCE_SRC_LANG_TYPE_TYPE_H_

#include <string>

#include <llvm/IR/Constant.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "compiler/Execution.h"
#include "lang/Accessibility.h"
#include "lang/BinaryOperator.h"
#include "lang/UnaryOperator.h"
#include "lang/construct/Callable.h"
#include "lang/construct/Entity.h"
#include "lang/type/StateCount.h"
#include "lang/utility/Identifier.h"
#include "lang/utility/Location.h"
#include "lang/utility/ResolvingHandle.h"
#include "validation/ValidationLogger.h"

namespace lang
{
    class Scope;
    class Value;
    class Function;
    class Member;
    class TypeDefinition;
    class StructType;
    class VectorizableType;
    class FloatingPointType;
    class AddressType;
    class FixedWidthIntegerType;
    class VectorType;
    class ArrayType;
    class IntegerType;
}

class Execution;
class ValidationLogger;
class Storage;

namespace lang
{
    /**
     * Represents types in the ance language.
     */
    class Type
        : public Callable
        , public HandleTarget<lang::Type>
        , public Entity
    {
      public:
        /**
         * Create a new undefined type.
         * @param name The name of the type.
         */
        explicit Type(Identifier name);

        /**
         * Create a defined type.
         * @param definition The type definition.
         */
        explicit Type(Owned<lang::TypeDefinition> definition);

      private:
        Type();

      public:
        Type(Type const&) = delete;
        Type(Type&&)      = delete;

        /**
         * Get a special undefined type that cannot be defined.
         * All undefined type handles are separate from each other.
         * @return The undefined type.
         */
        static lang::ResolvingHandle<lang::Type> getUndefined();

        /**
         * Get the name of this type.
         * @return The name.
         */
        [[nodiscard]] lang::Identifier const& name() const override;

        /**
         * Get the name of this type with helpful annotations. Useful for validation messages.
         * Use this only when the type is safe to use. Otherwise use the other overload.
         * @return The annotated name.
         */
        [[nodiscard]] std::string getAnnotatedName() const override;
        [[nodiscard]] std::string getAnnotatedName(bool is_safe) const override;

        /**
         * Get the mangled name of this type. The mangled name can only be used after all type dependencies have been resolved.
         * @return The mangled name. Cannot contain any special characters, must be unique.
         */
        [[nodiscard]] std::string const& getMangledName() const;

        /**
         * Get whether this type is defined.
         */
        [[nodiscard]] bool isDefined() const override;

        /**
         * Define this type. Can only be used on undefined types.
         * @param definition The definition for this type.
         */
        void define(Owned<lang::TypeDefinition> definition);

        [[nodiscard]] bool isCMP() const override;

        /**
         * Get the number of states for this type.
         * @return The number of states.
         */
        [[nodiscard]] StateCount getStateCount() const;

        /**
         * Get whether this type is a custom type.
         * @return True if this type is a custom type.
         */
        [[nodiscard]] bool isCustom() const;

        /**
         * Get whether this type is imported from another package.
         * @return True if this type is imported.
         */
        [[nodiscard]] bool isImported() const;

        /**
         * Get whether this type is a fixed width integer type.
         * @return A pointer to the integer type if this type is an integer type, null otherwise.
         */
        [[nodiscard]] FixedWidthIntegerType const* isFixedWidthIntegerType() const;

        /**
         * Get whether this type is an integer type with a given size and signedness.
         * @param bit_size The size.
         * @param is_signed The signedness.
         * @return True if this type is an integer type with the given size and signedness.
         */
        [[nodiscard]] bool isFixedWidthIntegerType(uint64_t bit_size, bool is_signed) const;

        /**
         * Get whether this type is signed.
         * @return True if this type is signed.
         */
        [[nodiscard]] bool isSigned() const;

        /**
         * Get whether this type is an integer type.
         * @return The integer type if this type is an integer type, null otherwise.
         */
        [[nodiscard]] IntegerType const* isIntegerType() const;

        /**
         * Get whether this type is a boolean type.
         * @return True if this type is a boolean type.
         */
        [[nodiscard]] bool isBooleanType() const;

        /**
         * Get whether this type is a char type.
         * @return True if this type is a char type.
         */
        [[nodiscard]] bool isCharType() const;

        /**
         * Get whether this type is an unsigned integer pointer type.
         * @return True if this type is an unsigned integer pointer type.
         */
        [[nodiscard]] bool isUnsignedIntegerPointerType() const;

        /**
         * Get whether this type is a floating point type.
         * @return A pointer to the floating point type if this type is a floating point type, null otherwise.
         */
        [[nodiscard]] FloatingPointType const* isFloatingPointType() const;

        /**
         * Get whether this type is a floating point type with a given precision.
         * @param precision The precision, in bits.
         * @return True if this type is a floating point type with the given precision.
         */
        [[nodiscard]] bool isFloatingPointType(size_t precision) const;

        /**
         * Get whether this type is a size type.
         * @return True if this type is a size type.
         */
        [[nodiscard]] bool isSizeType() const;

        /**
         * Get whether this type is a diff type.
         * @return True if this type is a diff type.
         */
        [[nodiscard]] bool isDiffType() const;

        /**
         * Get whether this type is the unit type.
         * @return True if this type is the unit type.
         */
        [[nodiscard]] bool isUnitType() const;

        /**
         * Get whether this type is the null value type used by the null literal.
         * @return True if this type is the null value type.
         */
        [[nodiscard]] bool isNullValueType() const;

        /**
         * Get whether this type is a normal pointer type. This excludes opaque pointer types.
         * @return True if this type is a pointer type.
         */
        [[nodiscard]] bool isPointerType() const;

        /**
         * Get whether this type is a type that represents a memory address.
         * @return The address type if this type is an address type, null otherwise.
         */
        [[nodiscard]] AddressType const* isAddressType() const;

        /**
         * Get whether this type is a buffer type.
         * @return True if this type is a buffer type.
         */
        [[nodiscard]] bool isBufferType() const;

        /**
         * Get whether this type is an opaque pointer type.
         * @return True if this type is an opaque pointer type.
         */
        [[nodiscard]] bool isOpaquePointerType() const;

        /**
         * Get whether this type is a reference type.
         * @return True if this type is a reference type.
         */
        [[nodiscard]] bool isReferenceType() const;

        /**
         * Get whether this type is a struct type.
         * @return The struct type if this type is a struct type, null otherwise.
         */
        [[nodiscard]] lang::StructType* isStructType();

        /**
         * Get whether this type is a struct type.
         * @return The struct type if this type is a struct type, null otherwise.
         */
        [[nodiscard]] lang::StructType const* isStructType() const;

        /**
         * Get whether this type is vectorizable.
         * All types can be vector elements, but for vectorizable types this is natively supported.
         * @return The vectorizable type.
         */
        [[nodiscard]] lang::VectorizableType const* isVectorizable() const;

        /**
         * Get whether this type is vectorizable.
         * All types can be vector elements, but for vectorizable types this is natively supported.
         * @return The vectorizable type.
         */
        [[nodiscard]] lang::VectorizableType* isVectorizable();

        /**
         * Get whether this type is a vector type.
         * @return True if this type is a vector type.
         */
        [[nodiscard]] lang::VectorType const* isVectorType() const;

        /**
         * Get whether this type is a vector type.
         * @return True if this type is a vector type.
         */
        [[nodiscard]] lang::VectorType* isVectorType();

        /**
         * Get whether this type is an array type.
         * @return The array type if this type is an array type, null otherwise.
         */
        [[nodiscard]] lang::ArrayType const* isArrayType() const;

        /**
         * Get whether this type is an array type.
         * @return The array type if this type is an array type, null otherwise.
         */
        [[nodiscard]] lang::ArrayType* isArrayType();

        /**
         * Get the element type of this type. A type can have only exactly one element type. Currently, only arrays, vectors, pointers and references have element types.
         * @return The element type, or undefined if this type has no element type.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> getElementType();

        /**
         * Get the element type of this type. A type can have only exactly one element type. Currently, only arrays, vectors, pointers and references have element types.
         * @return The element type, or undefined if this type has no element type.
         */
        [[nodiscard]] lang::Type const& getElementType() const;

        /**
         * Get the actual type.
         * @return The actual type, or the type itself if it already is an actual type.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> getActualType();

        /**
         * Get the actual type.
         * @return The actual type, or the type itself if it already is an actual type.
         */
        [[nodiscard]] lang::Type const& getActualType() const;

        /**
         * Test whether this type is fitting a predicate or is a vector of a type that is fitting a predicate.
         * @param predicate The predicate.
         * @return True if this type is fitting the predicate or is a vector of a type that is fitting the predicate.
         */
        [[nodiscard]] bool isXOrVectorOfX(std::function<bool(lang::Type const&)> const& predicate) const;

        /**
         * Get the accessibility for this type.
         * @return The accessibility.
         */
        [[nodiscard]] lang::Accessibility const& getAccessibility() const;

        /**
         * Set the scope that contains this type. The type must be already defined.
         * @param scope The scope that contains the type.
         */
        void setContainingScope(lang::Scope* scope) override;

        /**
         * Enables the creation of derived types, i.e. types that are based on this type and required for internals.
         * An example for a derived type is a pointer type to this type.
         * The creation of derived types is disabled by default to prevent infinite recursion.
         * Creating types trough the context enables the creation of derived types.
         */
        void enableDerivedTypeCreation();

        /**
         * Get the scope that contains this type.
         * @return The scope that contains the type.
         */
        [[nodiscard]] lang::Scope& scope() override;

        /**
         * Get the scope that contains this type.
         * @return The scope that contains the type.
         */
        [[nodiscard]] lang::Scope const& scope() const override;

        void postResolve();

        bool               requestOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters) override;
        [[nodiscard]] bool enableImplicitConversionOnCall() const override;

        /**
         * See if the subscript operation is defined for this type.
         * @return True if the subscript is defined.
         */
        [[nodiscard]] bool isSubscriptDefined() const;

        /**
         * Get the return type of the get indexer.
         * @return The return type.
         */
        [[nodiscard]] lang::Type const& getSubscriptReturnType() const;

        /**
         * Get the return type of the get indexer.
         * @return The return type.
         */
        lang::ResolvingHandle<lang::Type> getSubscriptReturnType();

        /**
         * Get whether a binary operation is defined for this type.
         * @param op The operation.
         * @param other The other type.
         * @return True if the operation is defined.
         */
        [[nodiscard]] bool isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const;

        /**
         * Get whether a unary operation is defined for this type.
         * @param op The operation.
         * @return True if the operation is defined.
         */
        [[nodiscard]] bool isOperatorDefined(lang::UnaryOperator op) const;

        /**
         * Get a binary operation result type.
         * @param op The operation.
         * @param other The other type.
         * @return The result type.
         */
        [[nodiscard]] lang::Type const& getOperatorResultType(lang::BinaryOperator op, lang::Type const& other) const;

        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::BinaryOperator op, lang::Type const& other);

        /**
         * Get the unary operation result type.
         * @param op The operation.
         * @return The result type.
         */
        [[nodiscard]] lang::Type const& getOperatorResultType(lang::UnaryOperator op) const;

        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::UnaryOperator op);

        /**
         * Check whether implicit conversion to a specified type is possible.
         * @param other The other type.
         * @return True if implicit conversion is possible.
         */
        [[nodiscard]] bool isImplicitlyConvertibleTo(lang::Type const& other) const;

        /**
         * Check whether casting to a specified type is possible.
         * @param other The other type.
         * @return True if casting is possible.
         */
        [[nodiscard]] bool isCastingPossibleTo(lang::Type const& other) const;

        /**
         * Check if this type has a member with the given name.
         * @param name The name of the member.
         * @return True if the member exists.
         */
        [[nodiscard]] bool hasMember(lang::Identifier const& name) const;

        /**
         * Get the member with the given name.
         * Check if the member exists before calling this function.
         * @param name The name of the member.
         * @return The member.
         */
        Member& getMember(lang::Identifier const& name);

        /**
         * Get the member with the given name.
         * Check if the member exists before calling this function.
         * @param name The name of the member.
         * @return The member.
         */
        [[nodiscard]] Member const& getMember(lang::Identifier const& name) const;

        /**
         * Get whether this type defines the indirection operator.
         * @return True if the type defines the indirection operator.
         */
        [[nodiscard]] bool definesIndirection() const;

        lang::ResolvingHandle<lang::Type> getIndirectionType();

        /**
         * Get the type this type is an indirection to.
         * The actual return type of the indirection operator is a reference to that type.
         * @return The type this type is an indirection to.
         */
        [[nodiscard]] lang::Type const& getIndirectionType() const;

        /**
         * Validate if this type is well-formed.
         * @param validation_logger The validation logger to use.
         * @param location The source location of the type declaration.
         * @return True if the type is valid.
         */
        bool validate(ValidationLogger& validation_logger, lang::Location location) const;

        /**
         * Validate a subscript access.
         * @param indexed_location The source location of the indexed value.
         * @param index_type The type of the used index.
         * @param index_location The source location of the index.
         * @param validation_logger A logger to log validation messages.
         * @return True if the get indexer is valid.
         */
        bool validateSubscript(lang::Location    indexed_location,
                               Type const&       index_type,
                               lang::Location    index_location,
                               ValidationLogger& validation_logger) const;

        /**
         * Validate a binary operation. May only be called if the operation is defined.
         * @param op The operation.
         * @param other The other type.
         * @param left_location The source location of the left value.
         * @param right_location The source location of the right value.
         * @param validation_logger The validation logger to use.
         * @return True if the operation is valid.
         */
        bool validateOperator(lang::BinaryOperator op,
                              lang::Type const&    other,
                              lang::Location       left_location,
                              lang::Location       right_location,
                              ValidationLogger&    validation_logger) const;

        /**
         * Validate a unary operation. May only be called if the operation is defined.
         * @param op The operation.
         * @param location The source location of the value.
         * @param validation_logger The validation logger to use.
         * @return True if the operation is valid.
         */
        bool validateOperator(lang::UnaryOperator op,
                              lang::Location      location,
                              ValidationLogger&   validation_logger) const;

        /**
         * Validate an implicit conversion.
         * @param other The other type.
         * @param location The source location of implicit conversion.
         * @param validation_logger The validation logger to use.
         * @return True if the implicit conversion is valid.
         */
        bool validateImplicitConversion(lang::Type const& other,
                                        lang::Location    location,
                                        ValidationLogger& validation_logger) const;

        /**
         * Validate an explicit cast.
         * @param other The other type.
         * @param location The source location of the cast.
         * @param validation_logger The validation logger to use.
         * @return True if the cast is valid.
         */
        bool validateCast(lang::Type const& other, lang::Location location, ValidationLogger& validation_logger) const;

        /**
         * Validate a member access.
         * @param name The name of the member.
         * @param validation_logger The validation logger to use.
         * @return True if the member access is valid.
         */
        bool validateMemberAccess(lang::Identifier const& name, ValidationLogger& validation_logger) const;

        /**
         * Validate indirection.
         * @param location The source location of the indirection.
         * @param validation_logger The validation logger to use.
         * @return True if the indirection is valid.
         */
        bool validateIndirection(lang::Location location, ValidationLogger& validation_logger) const;

        /**
         * Execute a subscript access.
         * @param indexed The indexed value.
         * @param index The index to use.
         * @param exec The current execution context.
         * @return The return value.
         */
        Shared<lang::Value> execSubscript(Shared<lang::Value> indexed,
                                          Shared<lang::Value> index,
                                           Execution&          exec) const;

        /**
         * Execute an binary operation.
         * @param op The operation.
         * @param left The left value, must be of this type.
         * @param right The right value.
         * @param exec The current execution context.
         * @return The result value.
         */
        Shared<lang::Value> execOperator(lang::BinaryOperator op,
                                         Shared<lang::Value>  left,
                                          Shared<lang::Value>  right,
                                          Execution&           exec) const;

        /**
         * Execute an unary operation.
         * @param op The operation.
         * @param value The value to operate on.
         * @param exec The current execution context.
         * @return The result value.
         */
        Shared<lang::Value> execOperator(lang::UnaryOperator op, Shared<lang::Value> value, Execution& exec) const;

        /**
         * Execute an implicit conversion.
         * @param other The type to convert to.
         * @param value The value to convert.
         * @param exec The current execution context.
         * @return The converted value.
         */
        Shared<lang::Value> execImplicitConversion(lang::Type const&   other,
                                                   Shared<lang::Value> value,
                                                    Execution&          exec) const;

        /**
         * Execute an explicit cast.
         * @param other The type to cast to.
         * @param value The value to cast.
         * @param exec The current execution context.
         * @return The casted value.
         */
        Shared<lang::Value> execCast(lang::Type const& other, Shared<lang::Value> value, Execution& exec) const;

        /**
         * Execute a member access.
         * @param value The value to access.
         * @param name The name of the member.
         * @param exec The current execution context.
         * @return The result value.
         */
        Shared<lang::Value> execMemberAccess(Shared<lang::Value>     value,
                                             lang::Identifier const& name,
                                              Execution&              exec) const;

        /**
         * Execute indirection.
         * @param value The value to indirect.
         * @param exec The current execution context.
         * @return The result value, which is a reference of indirection return type.
         */
        Shared<lang::Value> execIndirection(Shared<lang::Value> value, Execution& exec) const;

        /**
         * Build the default initializer for this type.
         * @param ptr A pointer to where the value should be initialized.
         * @param exec The current execution context.
         */
        void performDefaultInitializer(Shared<lang::Value> ptr, Execution& exec) const;

        /**
         * Build the default initializer for this type, initializing multiple instances.
         * @param ptr The pointer to the first instance.
         * @param count The number of instances to initialize.
         * @param exec The current execution context.
         */
        void performDefaultInitializer(Shared<lang::Value> ptr,
                                       Shared<lang::Value> count, Execution& exec) const;

        /**
         * Build the copy initializer for this type.
         * @param destination A pointer to where the value should be initialized.
         * @param source A pointer to the original value.
         * @param exec The current execution context.
         */
        void performCopyInitializer(Shared<lang::Value> destination,
                                    Shared<lang::Value> source, Execution& exec) const;

        /**
         * Build the destructor for this type.
         * @param ptr The pointer to the value to destruct.
         * @param exec The current execution context.
         */
        void performFinalizer(Shared<lang::Value> ptr, Execution& exec) const;

        /**
         * Build the default destructor for this type.
         * @param ptr The pointer to the value to destruct.
         * @param count The number of instances to destruct.
         * @param exec The current execution context.
         */
        void performFinalizer(Shared<lang::Value> ptr, Shared<lang::Value> count, Execution& exec) const;

        /**
         * Register the type for execution.
         * @param exec The current execution context.
         */
        void registerExecutionType(Execution& exec) const;

        /**
         * Register the backing required for the declaration.
         * @param exec The current execution context.
         */
        void registerDeclaration(Execution& exec) const;

        /**
         * Register the backing required for the definition of this type.
         * @param exec The current execution context.
         */
        void registerDefinition(Execution& exec) const;

        [[nodiscard]] lang::TypeDefinition*       getDefinition();
        [[nodiscard]] lang::TypeDefinition const* getDefinition() const;

        /**
         * Check if two types are matching, meaning the available type can be converted to the expected type.
         * @param expected The expected type.
         * @param actual The available type.
         * @return True if the types are matching.
         */
        static bool isMatching(lang::Type const& expected, lang::Type const& actual);

        /**
         * Check if an entity is matching the expected cmp type.
         * @tparam Expected The expected type.
         * @param actual The actual entity.
         * @return True if the entity is matching.
         */
        template<typename Expected>
        static bool isMatching(lang::Entity const& actual)
        {
            auto const* actual_pointer   = &actual;
            auto const* expected_pointer = dynamic_cast<Expected const*>(actual_pointer);

            return expected_pointer != nullptr;
        }

        /**
         * Validate that a type matches the expected type.
         * @param expected The expected type.
         * @param actual The actual type.
         * @param location The source location to use for logging.
         * @param validation_logger The validation logger.
         * @return True if the types match.
         */
        static bool checkMismatch(lang::Type const& expected,
                                  lang::Type const& actual,
                                  lang::Location    location,
                                  ValidationLogger& validation_logger);

        /**
         * Validate that an entity matches the expected cmp type.
         * @tparam Expected The expected type.
         * @param actual The actual entity.
         * @param expected_name The name of the expected type.
         * @param location The source location to use for logging.
         * @param validation_logger The validation logger.
         * @return True if the entity matches.
         */
        template<typename Expected>
        static bool checkMismatch(lang::Entity const& actual,
                                  std::string const&  expected_name,
                                  lang::Location      location,
                                  ValidationLogger&   validation_logger)
        {
            bool const is_matching = isMatching<Expected>(actual);

            if (!is_matching)
            {
                validation_logger.logError("Cannot implicitly convert " + actual.getAnnotatedName() + " to a "
                                               + expected_name,
                                           location);
            }

            return !is_matching;
        }

        /**
         * Transform a value so it matches an expected type.
         * @param expected The expected type.
         * @param value The value to transform.
         * @param exec The current execution context.
         * @return A value with the expected type. It can be the same value as passed in.
         */
        static Shared<lang::Value> makeMatching(lang::Type const&   expected,
                                                Shared<lang::Value> value, Execution& exec);

        template<typename Expected>
        static lang::ResolvingHandle<Expected> makeMatching(lang::ResolvingHandle<Entity> value)
        {
            bool const is_matching = isMatching<Expected>(*value);

            if (is_matching) { return value.template as<Expected>().value(); }

            assert(false && "Cannot make the value matching, was mismatch checked before?");
            throw std::logic_error("Cannot make the value matching, was mismatch checked before?");
        }

        template<typename Expected>
        static Expected const& makeMatching(lang::Entity const& value)
        {
            bool const is_matching = isMatching<Expected>(value);

            if (is_matching) { return *dynamic_cast<Expected const*>(&value); }

            assert(false && "Cannot make the value matching, was mismatch checked before?");
            throw std::logic_error("Cannot make the value matching, was mismatch checked before?");
        }

        /**
         * Get the referenced type, meaning the type itself if it is not a reference type, or the element type.
         * @param type The type to get the referenced type of.
         * @return The dereferenced type.
         */
        static lang::Type const& getReferencedType(lang::Type const& type);

        /**
         * Check if the actual types of two types are the same.
         * @param lhs The left hand side type.
         * @param rhs The right hand side type.
         * @return True if the types are actually the same.
         */
        static bool areSame(lang::Type const& lhs, lang::Type const& rhs);

        /**
         * Get an undefined type with the same name. Types given by literals cannot be undefined.
         * Therefore, for these types the returned type will already defined - but in the new context.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> getUndefinedTypeClone(lang::Context& new_context) const;

        ResolvingHandle<lang::Entity> getUndefinedClone(Context& new_context) const override;

        /**
         * Get a separate type get if the type is undefined, otherwise return the same type.
         * @return The type get.
         */
        lang::ResolvingHandle<lang::Type> getDetachedIfUndefined();

        /**
         * Get the common types from a list of types.
         * @param types The types to get the common types from.
         * @return A list of common types. It can be empty if there are no common types.
         */
        static std::vector<lang::ResolvingHandle<lang::Type>> getCommonType(
            std::vector<lang::ResolvingHandle<lang::Type>>& types);

        /**
         * Get the common types from a list of types.
         * @param types The types to get the common types from.
         * @return A list of common types. It can be empty if there are no common types.
         */
        static std::vector<std::reference_wrapper<lang::Type const>> getCommonType(
            std::vector<std::reference_wrapper<lang::Type const>> const& types);

        template<typename In, typename Out>
        friend struct GetCommonType;

        /**
         * Check equality of types. This compares identity, meaning that same types (e.g. type and alias) are not equal.
         * @param other The other type to compare to.
         * @return True if the types are equal.
         */
        bool operator==(lang::Type const& other) const;

        /**
         * Check inequality of types. This is the inverse of the equality operator.
         * @param other The other type to compare to.
         * @return True if the types are not equal.
         */
        bool operator!=(lang::Type const& other) const;

        /**
         * Check whether a type is undefined. If so, a message is logged.
         */
        static bool isTypeUndefined(lang::Type const&  type,
                                    lang::Scope const& scope,
                                    lang::Location     location,
                                    ValidationLogger&  validation_logger);

        /**
         * Get handles to the types that need to be resolved for this type to have a valid declaration.
         * @return The types to resolve.
         */
        std::vector<lang::ResolvingHandle<lang::Type>> getDeclarationDependencies();

        /**
         * Get handles to the types that need to be resolved for this type to have a valid definition.
         * @return The types to resolve.
         */
        std::vector<lang::ResolvingHandle<lang::Type>> getDefinitionDependencies();

        /**
         * Whether this type is a compound type, meaning it is created from other types.
         * Examples are arrays, vectors, pointers, structs, etc.
         * @return True if this type is a compound type.
         */
        [[nodiscard]] bool isCompound();

      protected:
        lang::Callable&                     getFunctionSource() override;
        [[nodiscard]] lang::Callable const& getFunctionSource() const override;

      private:
        lang::Identifier                      name_;
        Optional<Owned<lang::TypeDefinition>> definition_ {};
    };
}

void synchronize(lang::ResolvingHandle<lang::Type> type, Storage& storage);

#endif
