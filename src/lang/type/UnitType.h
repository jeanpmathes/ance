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

        llvm::Constant*   getDefaultContent(CompileContext& context) const override;
        llvm::StructType* getContentType(CompileContext& context) const override;

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

        void performDefaultInitializer(Shared<Value> ptr, Shared<Value> count, CompileContext& context) override;
        void performCopyInitializer(Shared<Value> ptr, Shared<Value> original, CompileContext& context) override;
        void performFinalizer(Shared<Value> ptr, Shared<Value> count, CompileContext& context) override;

      protected:
        std::string   createMangledName() const override;
        Execution::Type createDebugType(CompileContext& context) const override;

      public:
        lang::ResolvingHandle<lang::Type> clone(lang::Context& new_context) const override;

      private:
        mutable llvm::StructType* native_type_ {nullptr};
    };
}
#endif
