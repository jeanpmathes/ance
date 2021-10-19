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
        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::PointerType* getContentType(llvm::LLVMContext& c) override;

        bool validate(ValidationLogger& validation_logger, ance::Location location) override;

        bool isSubscriptDefined() override;

        ance::Type* getSubscriptReturnType() override;

        bool                         validateSubscript(Type*             indexed_type,
                                                       ance::Location    indexed_location,
                                                       Type*             index_type,
                                                       ance::Location    index_location,
                                                       ValidationLogger& validation_logger) override;
        std::shared_ptr<ance::Value> buildSubscript(std::shared_ptr<Value> indexed,
                                                    std::shared_ptr<Value> index,
                                                    CompileContext*        context) override;

      private:
        static llvm::Value* buildGetElementPointer(const std::shared_ptr<ance::Value>& indexed,
                                                   const std::shared_ptr<ance::Value>& index,
                                                   CompileContext*                     context);

      public:
        ~PointerType() override = default;

      private:
        ance::Type* element_type_;
        ance::Type* element_reference_;

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

      private:
        static std::map<ance::Type*, ance::PointerType*>& getPointerTypes();

      public:
        /**
         * Get a pointer type instance.
         * @param element_type The element type.
         * @return The instance.
         */
        static ance::Type* get(ance::Type* element_type);

        /**
         * Check if a given type is a pointer type.
         * @param type The type.
         * @return True if it is a pointer type.
         */
        static bool isPointerType(ance::Type* type);

        /**
         * Get the pointee type of a given pointer type.
         * @param type The pointer type.
         * @return The pointee type or nullptr if the given type is not a pointer type.
         */
        static ance::Type* getPointeeType(ance::Type* type);
    };
}

#endif
