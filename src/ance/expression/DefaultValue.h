#ifndef ANCE_SRC_ANCE_EXPRESSION_DEFAULTVALUE_H_
#define ANCE_SRC_ANCE_EXPRESSION_DEFAULTVALUE_H_

#include "BackingConstantExpression.h"

#include "ance/construct/constant/ExpressionBackedConstant.h"

/**
 * Provides the default value for a type.
 */
class DefaultValue : public BackingConstantExpression
{
  public:
    /**
     * Create a new default value expression.
     * @param type The type to use the default value of.
     * @param location The source location.
     */
    explicit DefaultValue(ance::Type* type, ance::Location location);

    ance::Type* type() override;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] ance::Value*    getValue() const override;
    [[nodiscard]] ance::Constant* getConstantValue() const override;
    llvm::Constant*               buildContentConstant(llvm::LLVMContext& c) override;

    bool accept(ance::ApplicationVisitor& visitor) override;

    ~DefaultValue() override;

  private:
    ance::Type*     type_;
    ance::Constant* constant_ {new ance::ExpressionBackedConstant(this)};
};

#endif