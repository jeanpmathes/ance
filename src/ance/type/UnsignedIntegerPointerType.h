#ifndef ANCE_SRC_ANCE_TYPE_UNSIGNEDINTEGERPOINTERTYPE_H_
#define ANCE_SRC_ANCE_TYPE_UNSIGNEDINTEGERPOINTERTYPE_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "Type.h"

class Application;
class CompileContext;

namespace ance
{
    /**
     * Represents the unsigned integer pointer type. It is capable of holding any pointer as an integer.
     */
    class UnsignedIntegerPointerType : public Type
    {
      private:
        UnsignedIntegerPointerType();

      public:
        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

        static llvm::Value* buildValue(llvm::Value*       pointer,
                                       llvm::LLVMContext& c,
                                       llvm::Module*      m,
                                       CompileContext*    state,
                                       llvm::IRBuilder<>& ir,
                                       llvm::DIBuilder*   di);

      private:
        inline static UnsignedIntegerPointerType* instance_    = nullptr;
        inline static llvm::Type*                 native_type_ = nullptr;

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

      public:
        /**
         * Initialize the type.
         * @param llvm_context The llvm context.
         * @param data_layout The data layout of the current build target.
         */
        static void init(llvm::LLVMContext& llvm_context, llvm::DataLayout& data_layout);

        /**
         * Get the uiptr type instance.
         * @return The instance.
         */
        static ance::UnsignedIntegerPointerType* get();
    };
}

#endif
