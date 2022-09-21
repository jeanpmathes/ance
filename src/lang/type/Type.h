#ifndef ANCE_SRC_LANG_TYPE_TYPE_H_
#define ANCE_SRC_LANG_TYPE_TYPE_H_

#include <string>

#include <llvm/IR/Constant.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "lang/AccessModifier.h"
#include "lang/BinaryOperator.h"
#include "lang/UnaryOperator.h"
#include "lang/construct/Callable.h"
#include "lang/type/StateCount.h"
#include "lang/type/TypeDefinition.h"
#include "lang/utility/Identifier.h"
#include "lang/utility/Location.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Scope;
    class Value;
    class Function;
    class VectorizableType;
    class FloatingPointType;
    class IntegerType;
    class VectorType;
    class ArrayType;
}

class CompileContext;
class ValidationLogger;

namespace lang
{
    /**
     * Represents types in the ance language.
     */
    class Type
        : public Callable
        , public HandleTarget<lang::Type>
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
        explicit Type(std::unique_ptr<lang::TypeDefinition> definition);

      private:
        Type();

      public:
        Type(const Type&) = delete;
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
        [[nodiscard]] const lang::Identifier& name() const override;

        /**
         * Get the name of this type with helpful annotations. Useful for validation messages.
         * @param is_safe Whether the type is currently safe to use. Set to false when endless loops could occur.
         * @return The annotated name.
         */
        [[nodiscard]] std::string getAnnotatedName(bool is_safe = true) const;

        /**
         * Get the mangled name of this type. The mangled name can only be used after all type dependencies have been resolved.
         * @return The mangled name. Cannot contain any special characters, must be unique.
         */
        [[nodiscard]] const std::string& getMangledName() const;

        /**
         * Get whether this type is defined.
         */
        [[nodiscard]] bool isDefined() const override;

        /**
         * Define this type. Can only be used on undefined types.
         * @param definition The definition for this type.
         */
        void define(std::unique_ptr<lang::TypeDefinition> definition);

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
         * Get whether this type is an integer type. Integer types have a fixed size.
         * @return A pointer to the integer type if this type is an integer type, null otherwise.
         */
        [[nodiscard]] const IntegerType* isIntegerType() const;

        /**
         * Get whether this type is an integer type with a given size and signedness.
         * @param bit_size The size.
         * @param is_signed The signedness.
         * @return True if this type is an integer type with the given size and signedness.
         */
        [[nodiscard]] bool isIntegerType(uint64_t bit_size, bool is_signed) const;

        /**
         * Get whether this type is signed.
         * @return True if this type is signed.
         */
        [[nodiscard]] bool isSigned() const;

        /**
         * Get whether this type is a boolean type.
         * @return True if this type is a boolean type.
         */
        [[nodiscard]] bool isBooleanType() const;

        /**
         * Get whether this type is an unsigned integer pointer type.
         * @return True if this type is an unsigned integer pointer type.
         */
        [[nodiscard]] bool isUnsignedIntegerPointerType() const;

        /**
         * Get whether this type is a floating point type.
         * @return A pointer to the floating point type if this type is a floating point type, null otherwise.
         */
        [[nodiscard]] const FloatingPointType* isFloatingPointType() const;

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
         * Get whether this type is the void type.
         * @return True if this type is the void type.
         */
        [[nodiscard]] bool isVoidType() const;

        /**
         * Get whether this type is a pointer type.
         * @return True if this type is a pointer type.
         */
        [[nodiscard]] bool isPointerType() const;

        /**
         * Get whether this type is a buffer type.
         * @return True if this type is a buffer type.
         */
        [[nodiscard]] bool isBufferType() const;

        /**
         * Get whether this type is a reference type.
         * @return True if this type is a reference type.
         */
        [[nodiscard]] bool isReferenceType() const;

        /**
         * Get whether this type is a struct type.
         * @return True if this type is a struct type.
         */
        [[nodiscard]] bool isStructType() const;

        /**
         * Get whether this type is vectorizable.
         * All types can be vector elements, but for vectorizable types this is natively supported.
         * @return The vectorizable type.
         */
        [[nodiscard]] const lang::VectorizableType* isVectorizable() const;

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
        [[nodiscard]] const lang::VectorType* isVectorType() const;

        /**
         * Get whether this type is a vector type.
         * @return True if this type is a vector type.
         */
        [[nodiscard]] lang::VectorType* isVectorType();

        /**
         * Get whether this type is an array type.
         * @return The array type if this type is an array type, null otherwise.
         */
        [[nodiscard]] const lang::ArrayType* isArrayType() const;

        /**
         * Get whether this type is an array type.
         * @return The array type if this type is an array type, null otherwise.
         */
        [[nodiscard]] lang::ArrayType* isArrayType();

        /**
         * Get the element type of this type. A type can have only exactly one element type. Currently, only arrays, vectors, pointers and references have element types.
         * @return The element type, or undefined if this type has no element type.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> getElementType() const;

        /**
         * Get the actual type.
         * @return The actual type, or the type itself if it already is an actual type.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> getActualType() const;

        /**
         * Get the access modifier for this type.
         * @return The access modifier.
         */
        [[nodiscard]] lang::AccessModifier getAccessModifier() const;

        /**
         * Set the scope that contains this type. The type must be already defined.
         * @param scope The scope that contains the type.
         */
        void setContainingScope(lang::Scope* scope);

        /**
         * Get the scope that contains this type.
         * @return The scope that contains the type.
         */
        [[nodiscard]] lang::Scope* getContainingScope() const;

        void postResolve();

        bool requestOverload(std::vector<lang::ResolvingHandle<lang::Type>> parameters) override;
        bool enableImplicitConversionOnCall() const override;

        /**
         * Get the default content of a value of this type.
         * @param m The module.
         * @return The default content.
         */
        llvm::Constant* getDefaultContent(llvm::Module& m);

        /**
         * Get the native type. Values of this type are passed around using this type.
         * @param c The llvm context.
         * @return The native type.
         */
        llvm::Type* getNativeType(llvm::LLVMContext& c) const;
        /**
         * Get the content type. The semantic meaning of this type uses the content type.
         * @param c The llvm context.
         * @return The content type.
         */
        llvm::Type* getContentType(llvm::LLVMContext& c) const;

        /**
         * Get the debug type, containing information for debuggers.
         * @param context The current compile context.
         * @return The debug type.
         */
        llvm::DIType* getDebugType(CompileContext& context);

        /**
         * Get the size of the native type.
         * @param m The llvm module.
         * @return The native size.
         */
        llvm::TypeSize getNativeSize(llvm::Module* m);
        /**
         * Get the size of the content type.
         * @param m The llvm module.
         * @return The content size.
         */
        llvm::TypeSize getContentSize(llvm::Module* m);

        /**
         * See if the subscript operation is defined for this type.
         * @return True if the subscript is defined.
         */
        bool isSubscriptDefined();

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
        bool isOperatorDefined(lang::BinaryOperator op, lang::ResolvingHandle<lang::Type> other);

        /**
         * Get whether a unary operation is defined for this type.
         * @param op The operation.
         * @return True if the operation is defined.
         */
        bool isOperatorDefined(lang::UnaryOperator op);

        /**
         * Get a binary operation result type.
         * @param op The operation.
         * @param other The other type.
         * @return The result type.
         */
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::BinaryOperator              op,
                                                                lang::ResolvingHandle<lang::Type> other);

        /**
         * Get the unary operation result type.
         * @param op The operation.
         * @return The result type.
         */
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::UnaryOperator op);

        /**
         * Check whether implicit conversion to a specified type is possible.
         * @param other The other type.
         * @return True if implicit conversion is possible.
         */
        bool isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other);

        /**
         * Check if this type has a member with the given name.
         * @param name The name of the member.
         * @return True if the member exists.
         */
        bool hasMember(const lang::Identifier& name);

        /**
         * Get the type of a member.
         * @param name The name of the member.
         * @return The type of the member.
         */
        lang::ResolvingHandle<lang::Type> getMemberType(const lang::Identifier& name);

        /**
         * Get whether this type defines the indirection operator.
         * @return True if the type defines the indirection operator.
         */
        bool definesIndirection();

        /**
         * Get the type this type is an indirection to.
         * The actual return type of the indirection operator is a reference to that type.
         * @return The type this type is an indirection to.
         */
        lang::ResolvingHandle<lang::Type> getIndirectionType();

        /**
         * Validate the definition of this type, if there is any.
         * @param validation_logger The validation logger to use.
         * @return True if the type has a valid definition.
         */
        bool validateDefinition(ValidationLogger& validation_logger) const;

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
        bool validateSubscript(lang::Location                    indexed_location,
                               lang::ResolvingHandle<lang::Type> index_type,
                               lang::Location                    index_location,
                               ValidationLogger&                 validation_logger) const;

        /**
         * Validate a binary operation. May only be called if the operation is defined.
         * @param op The operation.
         * @param other The other type.
         * @param left_location The source location of the left value.
         * @param right_location The source location of the right value.
         * @param validation_logger The validation logger to use.
         * @return True if the operation is valid.
         */
        bool validateOperator(lang::BinaryOperator              op,
                              lang::ResolvingHandle<lang::Type> other,
                              lang::Location                    left_location,
                              lang::Location                    right_location,
                              ValidationLogger&                 validation_logger) const;

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
        bool validateImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                        lang::Location                    location,
                                        ValidationLogger&                 validation_logger) const;

        /**
         * Validate a member access.
         * @param name The name of the member.
         * @param validation_logger The validation logger to use.
         * @return True if the member access is valid.
         */
        bool validateMemberAccess(const lang::Identifier& name, ValidationLogger& validation_logger) const;

        /**
         * Validate indirection.
         * @param location The source location of the indirection.
         * @param validation_logger The validation logger to use.
         * @return True if the indirection is valid.
         */
        bool validateIndirection(lang::Location location, ValidationLogger& validation_logger) const;

        /**
         * Build a subscript access.
         * @param indexed The indexed value.
         * @param index The index to use.
         * @param context The current compile context.
         * @return The return value.
         */
        std::shared_ptr<lang::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext&        context);

        /**
         * Build a binary operation.
         * @param op The operation.
         * @param left The left value, must be of this type.
         * @param right The right value.
         * @param context The current compile context.
         * @return The result value.
         */
        std::shared_ptr<lang::Value> buildOperator(lang::BinaryOperator   op,
                                                   std::shared_ptr<Value> left,
                                                   std::shared_ptr<Value> right,
                                                   CompileContext&        context);

        /**
         * Build a unary operation.
         * @param op The operation.
         * @param value The value to operate on.
         * @param context The current compile context.
         * @return The result value.
         */
        std::shared_ptr<lang::Value> buildOperator(lang::UnaryOperator    op,
                                                   std::shared_ptr<Value> value,
                                                   CompileContext&        context);

        /**
         * Build an implicit conversion.
         * @param other The type to convert to.
         * @param value The value to convert.
         * @param context The current compile context.
         * @return The converted value.
         */
        std::shared_ptr<lang::Value> buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                             std::shared_ptr<Value>            value,
                                                             CompileContext&                   context);

        /**
         * Build a member access.
         * @param value The value to access.
         * @param name The name of the member.
         * @param context The current compile context.
         * @return The result value.
         */
        std::shared_ptr<lang::Value> buildMemberAccess(std::shared_ptr<Value>  value,
                                                       const lang::Identifier& name,
                                                       CompileContext&         context);

        /**
         * Build indirection.
         * @param value The value to indirect.
         * @param context The current compile context.
         * @return The result value, which is a reference of indirection return type.
         */
        std::shared_ptr<lang::Value> buildIndirection(std::shared_ptr<Value> value, CompileContext& context);

        /**
         * Build the default initializer for this type.
         * @param ptr A pointer to where the value should be initialized.
         * @param context The current compile context.
         */
        void buildDefaultInitializer(llvm::Value* ptr, CompileContext& context);

        /**
         * Build the default initializer for this type, initializing multiple instances.
         * @param ptr The pointer to the first instance.
         * @param count The number of instances to initialize.
         * @param context The current compile context.
         */
        void buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext& context);

        /**
         * Build the copy initializer for this type.
         * @param ptr A pointer to where the value should be initialized.
         * @param original A pointer to the original value.
         * @param context The current compile context.
         */
        void buildCopyInitializer(llvm::Value* ptr, llvm::Value* original, CompileContext& context);

        /**
         * Build the destructor for this type.
         * @param ptr The pointer to the value to destruct.
         * @param context The current compile context.
         */
        void buildFinalizer(llvm::Value* ptr, CompileContext& context);

        /**
         * Build the default destructor for this type.
         * @param ptr The pointer to the value to destruct.
         * @param count The number of instances to destruct.
         * @param context The current compile context.
         */
        void buildFinalizer(llvm::Value* ptr, llvm::Value* count, CompileContext& context);

        /**
         * Build the native backing required for the declaration.
         * @param context The current compile context.
         */
        void buildNativeDeclaration(CompileContext& context);

        /**
         * Build the native backing required for the definition of this type.
         * @param context The current compile context.
         */
        void buildNativeDefinition(CompileContext& context);

        [[nodiscard]] lang::TypeDefinition* getDefinition() const;

        /**
         * Check if two types are matching, meaning the available type can be converted to the expected type.
         * @param expected The expected type.
         * @param actual The available type.
         * @return True if the types are matching.
         */
        static bool isMatching(lang::ResolvingHandle<lang::Type> expected, lang::ResolvingHandle<lang::Type> actual);

        /**
         * Validate that a type matches the expected type.
         * @param expected The expected type.
         * @param actual The actual type.
         * @param location The source location to use for logging.
         * @param validation_logger The validation logger.
         * @return True if the types match.
         */
        static bool checkMismatch(lang::ResolvingHandle<lang::Type> expected,
                                  lang::ResolvingHandle<lang::Type> actual,
                                  lang::Location                    location,
                                  ValidationLogger&                 validation_logger);

        /**
         * Transform a value so it matches an expected type.
         * @param expected The expected type.
         * @param value The value to transform.
         * @param context The current compile context.
         * @return A value with the expected type. It can be the same value as passed in.
         */
        static std::shared_ptr<lang::Value> makeMatching(lang::ResolvingHandle<lang::Type> expected,
                                                         std::shared_ptr<lang::Value>      value,
                                                         CompileContext&                   context);

        /**
         * Get the referenced type, meaning the type itself if it is not a reference type, or the element type.
         * @param type The type to get the referenced type of.
         * @return The dereferenced type.
         */
        static lang::ResolvingHandle<lang::Type> getReferencedType(lang::ResolvingHandle<lang::Type> type);

        /**
         * Get the value directly, or the referenced value if it is a reference type.
         * @param value The value to get the referenced value of.
         * @param context The current compile context.
         * @return The referenced value.
         */
        static std::shared_ptr<lang::Value> getValueOrReferencedValue(std::shared_ptr<lang::Value> value,
                                                                      CompileContext&              context);

        /**
         * Check if the actual types of two types are the same.
         * @param lhs The left hand side type.
         * @param rhs The right hand side type.
         * @return True if the types are actually the same.
         */
        static bool areSame(lang::ResolvingHandle<lang::Type> lhs, lang::ResolvingHandle<lang::Type> rhs);

        /**
         * Get the value as its actual type.
         * @param value The value to change the type of.
         * @return The value with the actual type.
         */
        static std::shared_ptr<lang::Value> makeActual(std::shared_ptr<lang::Value> value);

        /**
         * Get an undefined type with the same name. Types given by literals cannot be undefined.
         * Therefore, for these types the returned type will be the same as the type passed in.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> toUndefined() const;

        /**
         * Get a separate type handle if the type is undefined, otherwise return the same type.
         * @return The type handle.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> toSeparateUndefined() const;

        /**
         * Get the common types from a list of types.
         * @param types The types to get the common types from.
         * @return A list of common types. It can be empty if there are no common types.
         */
        static std::vector<lang::ResolvingHandle<lang::Type>> getCommonType(
            const std::vector<lang::ResolvingHandle<lang::Type>>& types);

      private:
        lang::Identifier                      name_;
        std::unique_ptr<lang::TypeDefinition> definition_ {};
    };
}
#endif
