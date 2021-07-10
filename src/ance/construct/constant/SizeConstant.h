#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_SIZECONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_SIZECONSTANT_H_

#include "Constant.h"

class Application;

namespace ance
{
    class SizeConstant : public Constant
    {
      public:
        SizeConstant(std::string size, Application& app);

        ance::Type* getType() override;

        llvm::Constant* buildContent(llvm::Module* m) override;

      private:
        Application& app_;
        ance::Type*  type_;
        std::string  size_;
    };
}

#endif
