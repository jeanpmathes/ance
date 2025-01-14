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
    };
}
#endif
