#ifndef ANCE_SRC_ANCE_TYPE_TYPE_H_
#define ANCE_SRC_ANCE_TYPE_TYPE_H_

#include <string>

#include <llvm/IR/Constant.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

#include "ance/Indexer.h"
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
      protected:
        Type()          = default;
        virtual ~Type() = default;

      public:
        Type(const Type&) = delete;
        Type(Type&&)      = delete;

        /**
         * Get the name of this type.
         * @return The name.
         */
        virtual std::string getName() = 0;

        /**
         * Get the default content of a value of this type.
         * @param c The llvm context.
         * @return The default content.
         */
        virtual llvm::Constant* getDefaultContent(llvm::LLVMContext& c) = 0;

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
        virtual llvm::Type* getContentType(llvm::LLVMContext& c) = 0;

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
         * See if the given indexer is defined for this type.
         * @param indexer The indexer to check.
         * @return True if the indexer is defined.
         */
        virtual bool isIndexerDefined(Indexer indexer);

        /**
         * Get the return type of the get indexer.
         * @return The return type.
         */
        virtual ance::Type* getIndexerReturnType();

        /**
         * Validate an indexer get access.
         * @param indexed The indexed value.
         * @param indexed_location The source location of the indexed value.
         * @param index The used index.
         * @param index_location The source location of the index.
         * @param validation_logger A logger to log validation messages.
         * @return True if the get indexer is valid.
         */
        virtual bool validateGetIndexer(ance::Value*      indexed,
                                        ance::Location    indexed_location,
                                        ance::Value*      index,
                                        ance::Location    index_location,
                                        ValidationLogger& validation_logger);

        /**
         * Validate an indexer set access.
         * @param indexed The indexed value.
         * @param indexed_location The source location of the indexed value.
         * @param index The used index.
         * @param index_location The source location of the index.
         * @param value The assigned value.
         * @param value_location The source location of the assigned value.
         * @param validation_logger A logger to log validation messages.
         */
        virtual void validateSetIndexer(ance::Value*      indexed,
                                        ance::Location    indexed_location,
                                        ance::Value*      index,
                                        ance::Location    index_location,
                                        ance::Value*      value,
                                        ance::Location    value_location,
                                        ValidationLogger& validation_logger);

        /**
         * Build a get indexer access.
         * @param indexed The indexed value.
         * @param index The index to use.
         * @param context The current compile context.
         * @return The return value.
         */
        virtual ance::Value* buildGetIndexer(ance::Value* indexed, ance::Value* index, CompileContext* context);

        /**
         * Build a set indexer access.
         * @param indexed The indexed value.
         * @param index The used index.
         * @param value The value to set.
         * @param context The current compile context.
         */
        virtual void buildSetIndexer(ance::Value*    indexed,
                                     ance::Value*    index,
                                     ance::Value*    value,
                                     CompileContext* context);

      protected:
        virtual llvm::DIType* createDebugType(CompileContext* context) = 0;

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

      private:
        llvm::DIType* debug_type_ {nullptr};
    };
}
#endif