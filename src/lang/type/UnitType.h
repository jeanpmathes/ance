#ifndef ANCE_SRC_LANG_TYPE_UNITTYPE_H_
#define ANCE_SRC_LANG_TYPE_UNITTYPE_H_

#include "TypeDefinition.h"

namespace lang
{
    /**
     * Represents the unit type. The unit type is a special type representing exactly one value.
     */
    class UnitType : public lang::TypeDefinition
    {
      public:
        UnitType();

        [[nodiscard]] StateCount getStateCount() const override;

        llvm::Constant*   getDefaultContent(llvm::Module& m) const override;
        llvm::StructType* getContentType(llvm::LLVMContext& c) const override;

        [[nodiscard]] bool isUnitType() const override;

        bool isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const override;
        lang::ResolvingHandle<lang::Type> getOperatorResultType(lang::BinaryOperator              op,
                                                                lang::ResolvingHandle<lang::Type> other) override;
        bool                              validateOperator(lang::BinaryOperator op,
                                                           lang::Type const&    other,
                                                           lang::Location       left_location,
                                                           lang::Location       right_location,
                                                           ValidationLogger&    validation_logger) const override;
        Shared<lang::Value>               buildOperator(lang::BinaryOperator op,
                                                        Shared<Value>        left,
                                                        Shared<Value>        right,
                                                        CompileContext&      context) override;

        void buildDefaultInitializer(llvm::Value* ptr, llvm::Value* count, CompileContext& context) override;
        void buildCopyInitializer(llvm::Value* ptr, llvm::Value* original, CompileContext& context) override;
        void buildFinalizer(llvm::Value* ptr, llvm::Value* count, CompileContext& context) override;

      protected:
        std::string   createMangledName() const override;
        llvm::DIType* createDebugType(CompileContext& context) const override;

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;

      private:
        mutable llvm::StructType* native_type_ {nullptr};
    };
}
#endif
