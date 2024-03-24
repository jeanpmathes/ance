#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_VALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_VALUE_H_

#include "compiler/Execution.h"

class Expression;
class Execution;

namespace lang
{
    class Type;
}

namespace lang
{
    /**
     * Represents any value that can be passed around in the final program.
     * This interface is used during the execution phase.
     */
    class Value
    {
      public:
        explicit Value(lang::Type const& type);
        virtual ~Value() = default;

        /**
         * Get the type of the value.
         * @return The type.
         */
        [[nodiscard]] virtual lang::Type const& type() const;

        /**
         * Get a value handle for the execution context associated with this value.
         * If the value is not associated with an execution context, this should not be called.
         * @return A value handle. Can be different for each call.
         */
        virtual Execution::Handle<false> getExecutionValue() = 0;

      private:
        lang::Type const& type_;
    };
}
#endif
