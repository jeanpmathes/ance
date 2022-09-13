#ifndef ANCE_SRC_LANG_TYPE_UNSIGNEDINTEGERPOINTERTYPE_H_
#define ANCE_SRC_LANG_TYPE_UNSIGNEDINTEGERPOINTERTYPE_H_

#include "TypeDefinition.h"

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;
class CompileContext;

namespace lang
{
    /**
     * Represents the unsigned integer pointer type. It is capable of holding any pointer as an integer.
     */
    class UnsignedIntegerPointerType : public lang::TypeDefinition
    {
      private:
        UnsignedIntegerPointerType();

      public:
        StateCount getStateCount() const override;

        llvm::Constant* getDefaultContent(llvm::Module& m) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

        [[maybe_unused]] static llvm::Value* buildValue(llvm::Value* pointer, CompileContext& state);

      private:
        inline static Type*       instance_    = nullptr;
        inline static llvm::Type* native_type_ = nullptr;

      protected:
        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext& context) override;

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
        static lang::ResolvingHandle<lang::Type> get();
    };
}

#endif

