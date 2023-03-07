#ifndef ANCE_SRC_LANG_EXPRESSION_SUBSCRIPT_H_
#define ANCE_SRC_LANG_EXPRESSION_SUBSCRIPT_H_

#include "DelayableExpression.h"

#include "lang/Element.h"

/**
 * A subscript operation.
 */
class Subscript
    : public DelayableExpression
    , public lang::Element<Subscript, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new subscript access.
     * @param indexed The indexed value.
     * @param index The index to use.
     * @param location The source location.
     */
    Subscript(Owned<Expression> indexed, Owned<Expression> index, lang::Location location);

    [[nodiscard]] Expression const& indexed() const;
    [[nodiscard]] Expression const& index() const;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type>& type) override;
    void doBuild(CompileContext& context) override;

  public:
    ~Subscript() override;

  private:
    Owned<Expression> indexed_;
    Owned<Expression> index_;
};

#endif
