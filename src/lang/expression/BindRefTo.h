#ifndef ANCE_SRC_LANG_EXPRESSION_BINDREFTO_H_
#define ANCE_SRC_LANG_EXPRESSION_BINDREFTO_H_

#include "DelayableExpression.h"

#include <optional>

#include "lang/Element.h"

class Application;

class BindRefTo
    : public DelayableExpression
    , public lang::Element<BindRefTo, ANCE_CONSTRUCTS>
{
  public:
    BindRefTo(std::unique_ptr<Expression> address, lang::Location location);

  public:
    [[nodiscard]] Expression& address() const;

    [[nodiscard]] std::optional<lang::ResolvingHandle<lang::Type>> tryGetType() const override;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  protected:
    void doBuild(CompileContext& context) override;

  public:
    ~BindRefTo() override;

  private:
    std::unique_ptr<Expression> address_;
};

#endif

