#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_BOOLEANCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_BOOLEANCONSTANT_H_

#include "Constant.h"

class Application;

namespace ance
{
    class BooleanConstant : public Constant
    {
      private:
        explicit BooleanConstant(bool boolean, Application& app);

      public:
        ance::Type* getType() override;

        llvm::Constant* buildContent(llvm::Module* m) override;

        static ance::BooleanConstant* createFalse(Application& app);

        static ance::BooleanConstant* createTrue(Application& app);

      private:
        ance::Type* type_;
        bool        boolean_;
    };
}

#endif
