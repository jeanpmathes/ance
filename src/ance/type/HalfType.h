#ifndef ANCE_SRC_ANCE_TYPE_HALFTYPE_H_
#define ANCE_SRC_ANCE_TYPE_HALFTYPE_H_

#include "FloatingPointType.h"
#include "Type.h"

namespace ance
{
    class Scope;

    class HalfType : public FloatingPointType
    {
      public:
        std::string getName() override;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override;

        llvm::Type* getContentType(llvm::LLVMContext& c) override;

      private:
        inline static FloatingPointType* instance_ = nullptr;

      public:
        static ance::FloatingPointType* get();
    };
}
#endif