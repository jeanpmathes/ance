#ifndef ANCE_SRC_ANCE_CONSTRUCT_PARAMETER_H_
#define ANCE_SRC_ANCE_CONSTRUCT_PARAMETER_H_

#include <string>

#include "ance/construct/value/Value.h"
#include "ance/utility/Location.h"

namespace ance
{
    class Type;
}

namespace ance
{
    /**
     * A function parameter value.
     */
    class Parameter : public ance::Value
    {
      public:
        /**
         * Create a new parameter.
         * @param type The type of the parameter.
         * @param name The name of the parameter.
         * @param location The source location.
         */
        Parameter(ance::Type* type, std::string name, ance::Location location);

        ance::Type* type() override;
        /**
         * Get the parameter name.
         * @return The name.
         */
        std::string name();

        /**
         * Get the source location.
         * @return The source location.
         */
        [[nodiscard]] ance::Location location() const;

        /**
         * Wrap an llvm argument as content value.
         * @param argument The native argument of this parameter.
         */
        void wrap(llvm::Argument* argument);

        void buildNativeValue(CompileContext* context) override;
        void buildContentValue(CompileContext* context) override;

        llvm::Value* getNativeValue() override;
        llvm::Value* getContentValue() override;

      private:
        ance::Type* type_;
        std::string name_;

        ance::Location location_;

        llvm::Value* native_value_ {nullptr};
        llvm::Value* content_value_ {nullptr};
    };
}
#endif