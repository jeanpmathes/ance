#ifndef ANCE_SRC_ANCE_TYPE_POINTERTYPE_H_
#define ANCE_SRC_ANCE_TYPE_POINTERTYPE_H_

#include "Type.h"

class Application;

namespace ance
{
    /**
     * Represents a pointer type. A pointer type has an element type, which is the type of the value pointed too.
     */
    class PointerType : public Type
    {
      private:
        explicit PointerType(Type* element_type);

      public:
        std::string getName() override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::PointerType* getContentType(llvm::LLVMContext& c) override;

        bool isIndexerDefined(Indexer indexer) override;

        ance::Type* getIndexerReturnType() override;

        void validateGetIndexer(ance::Value* indexed, ance::Value* index, ValidationLogger& validation_logger) override;
        ance::Value* buildGetIndexer(ance::Value* indexed, ance::Value* index, CompileContext* context) override;

        void validateSetIndexer(ance::Value*      indexed,
                                ance::Location    indexed_location,
                                ance::Value*      index,
                                ance::Location    index_location,
                                ance::Value*      value,
                                ance::Location    value_location,
                                ValidationLogger& validation_logger) override;
        void buildSetIndexer(ance::Value*    indexed,
                             ance::Value*    index,
                             ance::Value*    value,
                             CompileContext* context) override;

      private:
        static llvm::Value* buildGetElementPointer(ance::Value* indexed, ance::Value* index, CompileContext* context);

      public:
        ~PointerType() override = default;

      private:
        ance::Type* element_type_;

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

      public:
        /**
         * Get a pointer type instance.
         * @param app The current application.
         * @param element_type The element type.
         * @return The instance.
         */
        static ance::Type* get(Application& app, ance::Type* element_type);

        /**
         * Check if a given type is a pointer type.
         * @param type The type.
         * @return True if it is a pointer type.
         */
        static bool isPointerType(ance::Type* type);
    };
}

#endif
