#ifndef ANCE_SRC_LANG_EXPRESSION_MATCHSELECT_H_
#define ANCE_SRC_LANG_EXPRESSION_MATCHSELECT_H_

#include "UnexpandedExpression.h"

#include <memory>

#include "lang/Element.h"

/**
 * Selects a value from multiple cases.
 */
class MatchSelect
    : public UnexpandedExpression
    , public lang::Element<MatchSelect, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Constructs a new match select.
     * @param condition The condition to match.
     * @param cases The cases to select from.
     * @param location The location of the match select.
     */
    MatchSelect(Owned<Expression> condition, std::vector<Owned<Case>> cases, lang::Location location);

    [[nodiscard]] Expression const&                               condition() const;
    [[nodiscard]] std::vector<std::reference_wrapper<Case const>> cases() const;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    void walkDefinitions() override;
    void postResolve() override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type>& type) override;

  public:
    ~MatchSelect() override;

  private:
    Owned<Expression>        condition_;
    std::vector<Owned<Case>> cases_;
};

#endif
