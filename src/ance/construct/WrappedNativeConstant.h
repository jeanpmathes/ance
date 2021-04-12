#ifndef ANCE_SRC_ANCE_CONSTRUCT_WRAPPEDNATIVECONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_WRAPPEDNATIVECONSTANT_H_

#include "Constant.h"

namespace ance
{
    class WrappedNativeConstant : public Constant
    {
        public:
            WrappedNativeConstant(ance::Type* type, llvm::Constant* constant = nullptr);

            void set_constant(llvm::Constant* constant);

            ance::Type* get_type() override;
            llvm::Constant * get_constant(llvm::LLVMContext &c) override;

        private:
            ance::Type* type_;
            llvm::Constant* constant_;
    };
}

#endif
