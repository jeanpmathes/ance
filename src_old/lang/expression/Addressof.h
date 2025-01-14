#ifndef ANCE_SRC_LANG_EXPRESSION_ADDRESSOF_H_
#define ANCE_SRC_LANG_EXPRESSION_ADDRESSOF_H_

#include "Expression.h"

#include <optional>

#include "compiler/Runtime.h"

class Application;

/**
 * An addressof expression.
 */
class Addressof
    : public Expression
    , public lang::Element<Addressof, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create an addressof expression that provides the address of the arg.
     * @param arg The argument to get the address of.
     * @param location The source location of the expression.
     */
    Addressof(Owned<Expression> arg, lang::Location location);

    [[nodiscard]] Expression const& argument() const;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    ~Addressof() override;

  private:
    Owned<Expression> arg_;
};
#endif
