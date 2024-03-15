#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_CONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_CONSTANT_H_

#include "lang/construct/Value.h"
namespace lang
{
    class Constant : public Value
    {
      public:
        /**
         * Create a new constant.
         * @param type The type of the constant.
         */

        explicit Constant(lang::Type const& type);
        ~Constant() override = default;

        Execution::Handle<false> getExecutionValue() override;

        /**
         * Get a constant handle for the execution context associated with this constant.
         * If the constant is not associated with an execution context, this should not be called.
         * @return A constant handle. Can be different for each call.
         */
        virtual Execution::Handle<true> getExecutionConstant();
    };
}
#endif
