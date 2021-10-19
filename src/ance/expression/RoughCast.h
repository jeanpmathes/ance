#ifndef ANCE_SRC_ANCE_EXPRESSION_ROUGHCAST_H_
#define ANCE_SRC_ANCE_EXPRESSION_ROUGHCAST_H_

#include "Expression.h"

namespace ance
{
    class Scope;
}

/**
 * A rough cast, casting between two different types that use the same native type.
 */
class RoughCast : public Expression
{
  public:
    /**
     * Create a new rough cast.
     * @param target_type The target type.
     * @param expression The expression providing the value to cast.
     * @param location The source location.
     */
    RoughCast(ance::Type* target_type, std::unique_ptr<Expression> expression, ance::Location location);

    ance::Type* type() override;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] std::shared_ptr<ance::Value> getValue() const override;

    bool accept(ance::ApplicationVisitor& visitor) override;

    ~RoughCast() override;

  protected:
    void setScope(ance::Scope* scope) override;

  private:
    ance::Type*                 target_type_;
    std::unique_ptr<Expression>  expression_;
    std::shared_ptr<ance::Value> return_value_;
};

#endif
