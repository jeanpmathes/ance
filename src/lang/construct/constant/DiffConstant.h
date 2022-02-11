#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_DIFFCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_DIFFCONSTANT_H_

#include "Constant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    /**
     * An integer constant for diff literals.
     */
    class DiffConstant : public Constant
    {
      public:
        /**
         * Create a new size constant.
         * @param value The string containing the literal value.
         */
        explicit DiffConstant(std::string value);

        bool validate(ValidationLogger& validation_logger, lang::Location location) override;

        lang::ResolvingHandle<lang::Type> type() override;
        llvm::Constant*                   buildContent(llvm::Module* m) override;

      private:
        lang::ResolvingHandle<lang::Type> type_;
        std::string                       value_;
    };
}

#endif
