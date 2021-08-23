#ifndef ANCE_SRC_ANCE_TYPE_FLOATINGPOINTTYPE_H_
#define ANCE_SRC_ANCE_TYPE_FLOATINGPOINTTYPE_H_

#include "Type.h"

namespace ance
{
    /**
     * The base class of all floating point types.
     */
    class FloatingPointType : public Type
    {
      public:
        std::string getName() override = 0;

        llvm::Constant* getDefaultContent(llvm::LLVMContext& c) override = 0;

        llvm::Type* getContentType(llvm::LLVMContext& c) override = 0;

      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;
    };
}
#endif