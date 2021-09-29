#ifndef ANCE_SRC_ANCE_TYPE_REFERENCETYPE_H_
#define ANCE_SRC_ANCE_TYPE_REFERENCETYPE_H_

#include "Type.h"

class Application;

namespace ance
{
    /**
     * A reference refers to another stored value.
     */
    class ReferenceType : public Type
    {
      private:
        explicit ReferenceType(ance::Type* element_type);

      public:
        std::string getName() override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::PointerType* getContentType(llvm::LLVMContext& c) override;

        bool isIndexerDefined(Indexer indexer) override;

        ance::Type* getIndexerReturnType() override;

        bool validate(ValidationLogger& validation_logger, ance::Location location) override;

        bool         validateGetIndexer(ance::Value*      indexed,
                                        ance::Location    indexed_location,
                                        ance::Value*      index,
                                        ance::Location    index_location,
                                        ValidationLogger& validation_logger) override;
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

        ~ReferenceType() override = default;

      private:
        ance::Type* element_type_;

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

      public:
        /**
         * Get the referenced backing value.
         * @param value A native value for a reference-type variable.
         * @param context The current compile context.
         * @return A native value for the referenced value.
         */
        static llvm::Value* getReferenced(llvm::Value* value, CompileContext* context);

        /**
         * Get the referenced value.
         * @param value A value of reference type.
         * @param context The current compile context.
         * @return The referenced value.
         */
        ance::Value* getReferenced(ance::Value* value, CompileContext* context);

        /**
         * Get a reference type instance.
         * @param app The current application.
         * @param element_type The element type.
         * @return The instance.
         */
        static ance::Type* get(Application& app, ance::Type* element_type);

        /**
         * Check if a given type is a reference type.
         * @param type The type.
         * @return True if it is a reference type.
         */
        static bool isReferenceType(ance::Type* type);

        /**
         * Get the referenced type of a reference type.
         * @return The element type, or null if the given type is not a reference type.
         */
        static ance::Type* getReferencedType(ance::Type* type);
    };
}

#endif
