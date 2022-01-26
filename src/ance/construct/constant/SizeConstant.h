#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_SIZECONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_SIZECONSTANT_H_

#include "Constant.h"

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"

class Application;

namespace ance
{
    /**
     * A size constant for size literals.
     */
    class SizeConstant : public Constant
    {
      public:
        /**
         * Create a new size constant.
         * @param value The string containing the literal.
         */
        explicit SizeConstant(std::string value);

        bool validate(ValidationLogger& validation_logger, ance::Location location) override;

        ance::ResolvingHandle<ance::Type> type() override;
        llvm::Constant*                   buildContent(llvm::Module* m) override;

      private:
        ance::ResolvingHandle<ance::Type> type_;
        std::string                       value_;
    };
}

#endif
