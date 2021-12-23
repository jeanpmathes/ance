#ifndef ANCE_SRC_ANCE_TYPE_TYPE_H_
#define ANCE_SRC_ANCE_TYPE_TYPE_H_

#include <string>

#include <llvm/IR/Constant.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "ance/type/TypeDefinition.h"
#include "ance/utility/Location.h"
#include "ance/utility/ResolvingHandle.h"

namespace ance
{
    class Scope;
    class Value;
}

class CompileContext;
class ValidationLogger;

namespace ance
{
    /**
     * Represents types in the ance language.
     */
    class Type : public HandleTarget<ance::Type>
    {
      public:
        /**
         * Create a new undefined type.
         * @param name The name of the type.
         */
        explicit Type(std::string name);

        /**
         * Create a defined type.
         * @param definition The type definition.
         */
        explicit Type(std::unique_ptr<ance::TypeDefinition> definition);

      public:
        Type(const Type&) = delete;
        Type(Type&&)      = delete;

        /**
         * Get the name of this type.
         * @return The name.
         */
        [[nodiscard]] const std::string& getName() const;

        std::string getAnnotatedName();

        /**
         * Get the mangled name of this type. The mangled name can only be used after all type dependencies have been resolved.
         * @return The mangled name. Cannot contain any special characters, must be unique.
         */
        const std::string& getMangledName();

        /**
         * Get whether this type is defined.
         */
        [[nodiscard]] bool isDefined() const;

        /**
         * Define this type. Can only be used on undefined types.
         * @param definition The definition for this type.
         */
        void define(std::unique_ptr<ance::TypeDefinition> definition);

        /**
         * Get whether this type is a custom type.
         * @return True if this type is a custom type.
         */
        [[nodiscard]] bool isCustom() const;

        /**
         * Get whether this type is an integer type. Integer types have a fixed size.
         * @return True if this type is an integer type.
         */
        [[nodiscard]] bool isIntegerType() const;

        /**
         * Get whether this type is an integer type with a given size and signedness.
         * @param bit_size The size.
         * @param is_signed The signedness.
         * @return True if this type is an integer type with the given size and signedness.
         */
        [[nodiscard]] bool isIntegerType(uint64_t bit_size, bool is_signed) const;

        /**
         * Get whether this type is a boolean type.
         * @return True if this type is a boolean type.
         */
        [[nodiscard]] bool isBooleanType() const;

        /**
         * Get whether this type is a floating point type.
         * @return True if this type is a floating point type.
         */
        [[nodiscard]] bool isFloatingPointType() const;

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
         * Get whether this type is a reference type.
         * @return True if this type is a reference type.
         */
        [[nodiscard]] bool isReferenceType() const;

        /**
         * Get the element type of this type. A type can have only exactly one element type. Currently, only arrays, pointers and references have element types.
         * @return The element type, or void if this type has no element type.
         */
        [[nodiscard]] ance::ResolvingHandle<ance::Type> getElementType() const;

        /**
         * Get the actual type.
         * @return The actual type, or the type itself if it already is an actual type.
         */
        ance::ResolvingHandle<ance::Type> getActualType();

        /**
         * Get the original type.
         * @return The original type, or the type itself if it already is an original type.
         */
        ance::ResolvingHandle<ance::Type> getOriginalType();

        /**
         * Set the scope that contains this type. The type must be already defined.
         * @param scope The scope that contains the type.
         */
        void setContainingScope(ance::Scope* scope);

        /**
         * Get the scope that contains this type.
         * @return The scope that contains the type.
         */
        [[nodiscard]] ance::Scope* getContainingScope() const;

        /**
         * Get the default content of a value of this type.
         * @param c The llvm context.
         * @return The default content.
         */
        llvm::Constant* getDefaultContent(llvm::LLVMContext& c);

        /**
         * Get the native type. Values of this type are passed around using this type.
         * @param c The llvm context.
         * @return The native type.
         */
        llvm::Type* getNativeType(llvm::LLVMContext& c);
        /**
         * Get the content type. The semantic meaning of this type uses the content type.
         * @param c The llvm context.
         * @return The content type.
         */
        llvm::Type* getContentType(llvm::LLVMContext& c);

        /**
         * Get the debug type, containing information for debuggers.
         * @param context The current compile context.
         * @return The debug type.
         */
        llvm::DIType* getDebugType(CompileContext* context);

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
        ance::ResolvingHandle<ance::Type> getSubscriptReturnType();

        /**
         * Validate the definition of this type, if there is any.
         * @param validation_logger The validation logger to use.
         * @return True if the type has a valid definition.
         */
        bool validateDefinition(ValidationLogger& validation_logger);

        /**
         * Validate if this type is well-formed.
         * @param validation_logger The validation logger to use.
         * @param location The source location of the type declaration.
         * @return True if the type is valid.
         */
        bool validate(ValidationLogger& validation_logger, ance::Location location);

        /**
         * Validate a subscript access.
         * @param indexed_location The source location of the indexed value.
         * @param index_type The type of the used index.
         * @param index_location The source location of the index.
         * @param validation_logger A logger to log validation messages.
         * @return True if the get indexer is valid.
         */
        bool validateSubscript(ance::Location                    indexed_location,
                               ance::ResolvingHandle<ance::Type> index_type,
                               ance::Location                    index_location,
                               ValidationLogger&                 validation_logger);

        /**
         * Build a subscript access.
         * @param indexed The indexed value.
         * @param index The index to use.
         * @param context The current compile context.
         * @return The return value.
         */
        std::shared_ptr<ance::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext*        context);

        ance::TypeDefinition* getDefinition();

        /**
         * Validate that a type matches the expected type.
         * @param expected The expected type.
         * @param actual The actual type.
         * @param location The source location to use for logging.
         * @param validation_logger The validation logger.
         * @return True if the types match.
         */
        static bool checkMismatch(ance::ResolvingHandle<ance::Type> expected,
                                  ance::ResolvingHandle<ance::Type> actual,
                                  ance::Location                    location,
                                  ValidationLogger&                 validation_logger);

        /**
         * Transform a value so it matches an expected type.
         * @param expected The expected type.
         * @param value The value to transform.
         * @param context The current compile context.
         * @return A value with the expected type. It can be the same value as passed in.
         */
        static std::shared_ptr<ance::Value> makeMatching(ance::ResolvingHandle<ance::Type> expected,
                                                         std::shared_ptr<ance::Value>      value,
                                                         CompileContext*                   context);

        /**
         * Check if the actual types of two types are the same.
         * @param lhs The left hand side type.
         * @param rhs The right hand side type.
         * @return True if the types are actually the same.
         */
        static bool areSame(ance::ResolvingHandle<ance::Type> lhs, ance::ResolvingHandle<ance::Type> rhs);

        /**
         * Get the value as its actual type.
         * @param value The value to change the type of.
         * @return The value with the actual type.
         */
        static std::shared_ptr<ance::Value> makeActual(std::shared_ptr<ance::Value> value);

      private:
        std::string                           name_;
        std::unique_ptr<ance::TypeDefinition> definition_ {};
    };
}
#endif