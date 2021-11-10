#ifndef ANCE_SRC_ANCE_TYPE_POINTERTYPE_H_
#define ANCE_SRC_ANCE_TYPE_POINTERTYPE_H_

#include "TypeDefinition.h"

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"

class Application;

namespace ance
{
    /**
     * Represents a pointer type. A pointer type has an element type, which is the type of the value pointed too.
     */
    class PointerType : public ance::TypeDefinition
    {
      private:
        explicit PointerType(ance::ResolvingHandle<ance::Type> element_type);

      public:
        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::PointerType* getContentType(llvm::LLVMContext& c) override;

        bool validate(ValidationLogger& validation_logger, ance::Location location) override;

        bool isSubscriptDefined() override;

        ance::ResolvingHandle<ance::Type> getSubscriptReturnType() override;

        bool                         validateSubscript(ance::Location                    indexed_location,
                                                       ance::ResolvingHandle<ance::Type> index_type,
                                                       ance::Location                    index_location,
                                                       ValidationLogger&                 validation_logger) override;
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
        ance::ResolvingHandle<ance::Type> element_type_;
        ance::ResolvingHandle<ance::Type> element_reference_;

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

      private:
        static std::vector<std::pair<ance::ResolvingHandle<ance::Type>, ance::ResolvingHandle<ance::Type>>>&
        getPointerTypes();

      public:
        /**
         * Get a pointer type instance.
         * @param element_type The element type.
         * @return The instance.
         */
        static ance::ResolvingHandle<ance::Type> get(ance::ResolvingHandle<ance::Type> element_type);

        /**
         * Check if a given type is a pointer type.
         * @param type The type.
         * @return True if it is a pointer type.
         */
        static bool isPointerType(ance::ResolvingHandle<ance::Type> type);

        /**
         * Get the pointee type of a given pointer type.
         * @param type The pointer type.
         * @return The pointee type or nullptr if the given type is not a pointer type.
         */
        static ance::ResolvingHandle<ance::Type> getPointeeType(ance::ResolvingHandle<ance::Type> type);
    };
}

#endif
