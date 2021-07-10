#ifndef ANCE_SRC_ANCE_TYPE_VOIDTYPE_H_
#define ANCE_SRC_ANCE_TYPE_VOIDTYPE_H_

#include "Type.h"

namespace ance
{
    class VoidType : public Type
    {
      public:
        std::string getName() override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

      private:
        VoidType() = default;

      public:
        static VoidType* get();

      private:
        inline static VoidType* instance_ = nullptr;
    };
}
#endif
