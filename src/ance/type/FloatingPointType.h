#ifndef ANCE_SRC_ANCE_TYPE_FLOATINGPOINTTYPE_H_
#define ANCE_SRC_ANCE_TYPE_FLOATINGPOINTTYPE_H_

#include "Type.h"

namespace ance
{
    /**
     * The base class of all floating point types.
     */
    class FloatingPointType : virtual public Type
    {
      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;
    };
}
#endif