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
        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::PointerType* getContentType(llvm::LLVMContext& c) override;

        bool isSubscriptDefined() override;

        ance::Type* getSubscriptReturnType() override;

        bool validate(ValidationLogger& validation_logger, ance::Location location) override;

        bool                         validateSubscript(Type*             indexed_type,
                                                       ance::Location    indexed_location,
                                                       Type*             index_type,
                                                       ance::Location    index_location,
                                                       ValidationLogger& validation_logger) override;
        std::shared_ptr<ance::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext*        context) override;

        ~ReferenceType() override = default;

      private:
        ance::Type* element_type_;

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

      private:
        static std::map<ance::Type*, ance::ReferenceType*>& getReferenceTypes();

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
        std::shared_ptr<ance::Value> getReferenced(const std::shared_ptr<ance::Value>& value, CompileContext* context);

        /**
         * Get a reference type instance.
         * @param element_type The element type.
         * @return The instance.
         */
        static ance::Type* get(ance::Type* element_type);

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
