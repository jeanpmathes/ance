#ifndef ANCE_SRC_ANCE_EXPRESSION_SIZEOFTYPE_H_
#define ANCE_SRC_ANCE_EXPRESSION_SIZEOFTYPE_H_

#include "BackingExpression.h"

#include "ance/construct/value/ExpressionBackedValue.h"

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
    explicit SizeofType(ance::Type* type, ance::Location location);

    ance::Type* type() override;

    void validate() override;

    [[nodiscard]] ance::Value* getValue() const override;

  protected:
    llvm::Value* buildNativeValue(CompileContext* context) override;

  private:
    ance::Value* return_value_ {new ance::ExpressionBackedValue(this)};
    ance::Type*  type_;
};

#endif