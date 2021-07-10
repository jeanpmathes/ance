#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_BYTECONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_BYTECONSTANT_H_

#include <string>

#include "Application.h"
#include "Constant.h"

namespace ance
{

    class Type;

    class ByteConstant : public Constant
    {
      public:
        explicit ByteConstant(uint8_t byte, Application& app);

        ance::Type* getType() override;

        llvm::Constant* buildContent(llvm::Module* m) override;

        static char resolveEscaped(char content);

        static uint8_t parse(const std::string& unparsed);

      private:
        ance::Type* type_;
        uint8_t     byte_;
    };
}

#endif
