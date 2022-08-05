#ifndef ANCE_SRC_LANG_TYPE_BOOLEANTYPE_H_
#define ANCE_SRC_LANG_TYPE_BOOLEANTYPE_H_

#include "TypeDefinition.h"

namespace lang
{
    /**
     * The boolean type.
     */
    class BooleanType : virtual public lang::TypeDefinition
    {
      public:
        BooleanType();
        ~BooleanType() override = default;

        [[nodiscard]] StateCount getStateCount() const override;
        [[nodiscard]] bool       isBooleanType() const override;

        llvm::Constant* getDefaultContent(llvm::Module& m) override;
        llvm::Type*     getContentType(llvm::LLVMContext& c) const override;

        bool                              isOperatorDefined(lang::UnaryOperator op) override;
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::UnaryOperator op) override;
        bool                              validateOperator(lang::UnaryOperator op,
                                                           lang::Location      location,
                                                           ValidationLogger&   validation_logger) const override;
        std::shared_ptr<lang::Value>      buildOperator(lang::UnaryOperator    op,
                                                        std::shared_ptr<Value> value,
                                                        CompileContext*        context) override;

      protected:
        [[nodiscard]] bool isTriviallyDefaultConstructible() const override;
        [[nodiscard]] bool isTriviallyCopyConstructible() const override;
        [[nodiscard]] bool isTriviallyDestructible() const override;

        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext* context) override;

      public:
        /**
         * Get the boolean type.
         * @return The boolean type.
         */
        static lang::ResolvingHandle<lang::Type> get();
    };
}

#endif
