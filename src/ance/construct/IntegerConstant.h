#ifndef ANCE_SRC_ANCE_CONSTRUCT_INTEGERCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_INTEGERCONSTANT_H_

#include "Scope.h"
#include "Constant.h"

namespace ance
{
    class IntegerConstant : public Constant
    {
        public:
            IntegerConstant(llvm::APInt integer, bool is_signed, ance::Scope* scope);
            ance::Type * getType() override;
            llvm::Constant* getConstant(llvm::LLVMContext &c) override;

        private:
            ance::Type* type_;
            llvm::APInt integer_;
            llvm::Constant* constant_;
    };
}

#endif
