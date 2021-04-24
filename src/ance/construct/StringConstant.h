#ifndef ANCE_SRC_ANCE_CONSTRUCT_STRINGCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_STRINGCONSTANT_H_

#include "Scope.h"
#include "Constant.h"

namespace ance
{
    class StringConstant : public Constant
    {
        public:
            StringConstant(std::string string, ance::Scope* scope);
            ance::Type * getType() override;
            llvm::Constant* getConstant(llvm::LLVMContext &c) override;

            static std::string parse(const std::string& unparsed);

        private:
            ance::Type* type_;
            std::string string_;
            llvm::Constant* constant_{nullptr};
    };
}

#endif
