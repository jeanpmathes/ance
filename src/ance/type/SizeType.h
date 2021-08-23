#ifndef ANCE_SRC_ANCE_TYPE_SIZETYPE_H_
#define ANCE_SRC_ANCE_TYPE_SIZETYPE_H_

#include "Type.h"

class Application;

namespace ance
{
    /**
     * Represents an unsigned integer capable of holding the size of the largest possible array.
     */
    class SizeType : public ance::Type
    {
      public:
        std::string getName() override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

        static llvm::Value* buildValue(llvm::TypeSize size);

      private:
        inline static SizeType*   instance_    = nullptr;
        inline static llvm::Type* native_type_ = nullptr;

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

      public:
        /**
         * Initialize the size type.
         * @param c The llvm context.
         * @param app The current application.
         */
        static void init(llvm::LLVMContext& c, Application& app);

        /**
         * Get the size type instance.
         * @return The instance.
         */
        static ance::SizeType* get();
    };
}
#endif