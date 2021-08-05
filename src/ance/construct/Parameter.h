#ifndef ANCE_SRC_ANCE_CONSTRUCT_PARAMETER_H_
#define ANCE_SRC_ANCE_CONSTRUCT_PARAMETER_H_

#include <string>

#include "ance/construct/LocalVariable.h"
#include "ance/construct/value/Value.h"

namespace ance
{
    class Type;

    class Parameter : public ance::Value
    {
      public:
        Parameter(ance::Type* type, std::string name, ance::Location location);

        ance::Type* type() override;
        std::string name();

        [[nodiscard]] ance::Location location() const;

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