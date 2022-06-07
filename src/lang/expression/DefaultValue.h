#ifndef ANCE_SRC_LANG_EXPRESSION_DEFAULTVALUE_H_
#define ANCE_SRC_LANG_EXPRESSION_DEFAULTVALUE_H_

#include "BackingConstantExpression.h"

#include "lang/construct/constant/ExpressionBackedConstant.h"
#include "lang/Element.h"

/**
 * Provides the default value for a type.
 */
class DefaultValue
    : public BackingConstantExpression
    , public lang::Element<DefaultValue, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new default value expression.
     * @param type The type to use the default value of.
     * @param location The source location.
     */
    explicit DefaultValue(lang::ResolvingHandle<lang::Type> type, lang::Location location);

    lang::ResolvingHandle<lang::Type> type() const override;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

    [[nodiscard]] std::shared_ptr<lang::Value>    getValue() const override;
    [[nodiscard]] std::shared_ptr<lang::Constant> getConstantValue() const override;
    llvm::Constant*                               buildContentConstant(llvm::LLVMContext& c) override;

    ~DefaultValue() override;

  private:
    lang::ResolvingHandle<lang::Type> type_;
    std::shared_ptr<lang::Constant>   constant_ {std::make_shared<lang::ExpressionBackedConstant>(*this)};
};

#endif