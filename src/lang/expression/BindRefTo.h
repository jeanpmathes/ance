#ifndef ANCE_SRC_LANG_EXPRESSION_BINDREFTO_H_
#define ANCE_SRC_LANG_EXPRESSION_BINDREFTO_H_

#include "Expression.h"

#include <optional>

#include "lang/Element.h"

class Application;

class BindRefTo
    : public Expression
    , public lang::Element<BindRefTo, ANCE_CONSTRUCTS>
{
  public:
    BindRefTo(Owned<Expression> address, lang::Location location);

  public:
    [[nodiscard]] Expression const& address() const;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    ~BindRefTo() override;

  private:
    Owned<Expression> address_;
};

#endif
