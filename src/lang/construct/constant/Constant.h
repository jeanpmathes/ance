#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_CONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_CONSTANT_H_

#include "lang/construct/value/Value.h"

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

namespace lang
{
    class Constant : public Value
    {
      public:
        /**
         * Validate the constant value.
         * @param location The location of the constant.
         * @param validation_logger The logger to log the validation result.
         * @return True if the constant value is valid.
         */
        virtual bool validate(ValidationLogger& validation_logger, lang::Location location);

        /**
         * Build the content constant of this constant.
         * @param m The module.
         */
        void buildContentConstant(llvm::Module* m);

      protected:
        /**
         * Build the content of this constant.
         * @param m The module.
         * @return The content constant.
         */
        virtual llvm::Constant* buildContent(llvm::Module* m) = 0;

      public:
        /**
         * Get the content value of this constant as a llvm constant. The constant must be built first.
         * @return The content constant.
         */
        llvm::Constant* getContentConstant();

        void buildNativeValue(CompileContext* context) final;
        void buildContentValue(CompileContext* context) final;

        llvm::Value* getNativeValue() final;
        llvm::Value* getContentValue() final;

      protected:
        llvm::Value*    native_value_ {nullptr};
        llvm::Constant* content_constant_ {nullptr};
    };
}
#endif