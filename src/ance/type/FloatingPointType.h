#ifndef ANCE_SRC_ANCE_TYPE_FLOATINGPOINTTYPE_H_
#define ANCE_SRC_ANCE_TYPE_FLOATINGPOINTTYPE_H_

#include "TypeDefinition.h"

namespace ance
{
    /**
     * The base class of all floating point types.
     */
    class FloatingPointType : virtual public ance::TypeDefinition
    {
      protected:
        llvm::DIType* createDebugType(CompileContext* context) override;

      public:
        ~FloatingPointType() override = default;

        [[nodiscard]] bool isFloatingPointType() const override;
        [[nodiscard]] bool isFloatingPointType(size_t precision) const override = 0;
    };
}
#endif