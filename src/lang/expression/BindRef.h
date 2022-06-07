#ifndef ANCE_SRC_LANG_EXPRESSION_BINDREF_H_
#define ANCE_SRC_LANG_EXPRESSION_BINDREF_H_

#include "UnexpandedExpression.h"

#include <optional>

#include "lang/Element.h"

class Application;

class BindRef
    : public UnexpandedExpression
    , public lang::Element<BindRef, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Creates a new bind reference.
     * @param value The value to bind.
     * @param location The location of the bind reference.
     */
    BindRef(std::unique_ptr<Expression> value, lang::Location location);

  public:
    [[nodiscard]] Expression& value() const;

    lang::ResolvingHandle<lang::Type> type() const override;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  public:
    ~BindRef() override;

  private:
    std::unique_ptr<Expression> value_;

    mutable std::optional<lang::ResolvingHandle<lang::Type>> type_ {};
};

#endif
