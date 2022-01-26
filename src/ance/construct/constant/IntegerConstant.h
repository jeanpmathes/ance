#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_INTEGERCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_INTEGERCONSTANT_H_

#include "Constant.h"

#include "ance/type/Type.h"
#include "ance/utility/ResolvingHandle.h"

class Application;

namespace ance
{
    /**
     * An integer constant using any of the integer types.
     */
    class IntegerConstant : public Constant
    {
      public:
        /**
         * Create a new integer constant.
         * @param integer The integer value to use, encoded as a string.
         * @param size The size of the integer, in bits.
         * @param is_signed Whether the integer should be signed or unsigned.
         * @param radix The radix to use when parsing the integer.
         */
        IntegerConstant(std::string integer, int64_t size, bool is_signed, int radix = 10);

        bool validate(ValidationLogger& validation_logger, ance::Location location) override;

        ance::ResolvingHandle<ance::Type> type() override;
        llvm::Constant*                   buildContent(llvm::Module* m) override;

      private:
        std::string                       text_;
        std::int64_t                      size_;
        int                               radix_;
        ance::ResolvingHandle<ance::Type> type_;
    };
}

#endif
