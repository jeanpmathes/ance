#ifndef ANCE_SRC_ANCE_UTILITY_LOCATION_H_
#define ANCE_SRC_ANCE_UTILITY_LOCATION_H_

#include <llvm/IR/DebugLoc.h>

namespace ance
{
    class Location
    {
      public:
        Location(unsigned line, unsigned column);

        [[nodiscard]] unsigned line() const;
        [[nodiscard]] unsigned column() const;

        llvm::DebugLoc getDebugLoc(llvm::LLVMContext* llvm_context, llvm::DIScope* scope);

      private:
        unsigned line_;
        unsigned column_;
    };
}

#endif
