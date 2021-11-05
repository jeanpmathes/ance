#ifndef ANCE_SRC_ANCE_TYPE_TYPE_H_
#define ANCE_SRC_ANCE_TYPE_TYPE_H_

#include <string>

#include <llvm/IR/Constant.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "ance/type/TypeDefinition.h"
#include "ance/utility/Location.h"

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
    class Type
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
        virtual ~Type() = default;

      public:
        Type(const Type&) = delete;
        Type(Type&&)      = delete;

        /**
         * Get the name of this type.
         * @return The name.
         */
        [[nodiscard]] const std::string& getName() const;

        /**
         * Get whether this type is defined.
         */
        bool isDefined() const;

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
        ance::Type* getSubscriptReturnType();

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
        bool validateSubscript(ance::Location    indexed_location,
                               Type*             index_type,
                               ance::Location    index_location,
                               ValidationLogger& validation_logger);

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

      public:
        /**
         * Validate that a type matches the expected type.
         * @param expected The expected type.
         * @param actual The actual type.
         * @param location The source location to use for logging.
         * @param validation_logger The validation logger.
         * @return True if the types match.
         */
        static bool checkMismatch(ance::Type*       expected,
                                  ance::Type*       actual,
                                  ance::Location    location,
                                  ValidationLogger& validation_logger);

        /**
         * Transform a value so it matches an expected type.
         * @param expected The expected type.
         * @param value The value to transform.
         * @param context The current compile context.
         * @return A value with the expected type. It can be the same value as passed in.
         */
        static std::shared_ptr<ance::Value> makeMatching(ance::Type*                  expected,
                                                         std::shared_ptr<ance::Value> value,
                                                         CompileContext*              context);

      private:
        std::string                           name_;
        std::unique_ptr<ance::TypeDefinition> definition_ {};
    };
}
#endif