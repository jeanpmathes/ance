#ifndef ANCE_SRC_ANCE_EXPRESSION_SIZEOFTYPE_H_
#define ANCE_SRC_ANCE_EXPRESSION_SIZEOFTYPE_H_

#include "BackingExpression.h"

#include "lang/construct/value/ExpressionBackedValue.h"

class Application;

/**
 * Provides the size of a type.
 */
class SizeofType : public BackingExpression
{
  public:
    /**
     * Create a new sizeof type expression.
     * @param type The type to provide the size of.
     * @param location The source location.
     */
    explicit SizeofType(lang::ResolvingHandle<lang::Type> type, lang::Location type_location, lang::Location location);

  protected:
    void setScope(lang::Scope* scope) override;

  public:
    lang::ResolvingHandle<lang::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] std::shared_ptr<lang::Value> getValue() const override;

  protected:
    llvm::Value* buildNativeValue(CompileContext* context) override;

  private:
    std::shared_ptr<lang::Value>      return_value_ {std::make_shared<lang::ExpressionBackedValue>(this)};
    lang::ResolvingHandle<lang::Type> type_;
    lang::Location                    type_location_;
};

#endif