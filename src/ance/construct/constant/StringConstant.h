#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_STRINGCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_STRINGCONSTANT_H_

#include "Constant.h"

#include "compiler/Application.h"

namespace ance
{
    class StringConstant : public Constant
    {
      public:
        StringConstant(std::string prefix, std::string string, Application& app);

        ance::Type* type() override;

        llvm::Constant* buildContent(llvm::Module* m) override;

        static std::string parse(const std::string& unparsed);

      private:
        static ance::Type* resolveType(std::string& prefix, std::string& string, Application& app);

      private:
        ance::Type* type_;
        std::string prefix_;
        std::string string_;
    };
}

#endif
