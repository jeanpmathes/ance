#ifndef ANCE_SRC_LANG_TYPE_BOOLEANTYPE_H_
#define ANCE_SRC_LANG_TYPE_BOOLEANTYPE_H_

#include "TypeDefinition.h"

namespace lang
{
    /**
     * The boolean type.
     */
    class BooleanType : virtual public lang::TypeDefinition
    {
      public:
        BooleanType();
        ~BooleanType() override = default;

        [[nodiscard]] StateCount getStateCount() const override;
        [[nodiscard]] bool       isBooleanType() const override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) override;

      protected:
        std::string   createMangledName() override;
        llvm::DIType* createDebugType(CompileContext* context) override;

      public:
        /**
         * Get the boolean type.
         * @return The boolean type.
         */
        static lang::ResolvingHandle<lang::Type> get();

      private:
        llvm::Type* native_type_ {nullptr};
    };
}

#endif
