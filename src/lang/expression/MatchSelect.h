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
    MatchSelect(std::unique_ptr<Expression>        condition,
                std::vector<std::unique_ptr<Case>> cases,
                lang::Location                     location);

    [[nodiscard]] Expression&                               condition() const;
    [[nodiscard]] std::vector<std::reference_wrapper<Case>> cases() const;

  public:
    lang::ResolvingHandle<lang::Type>               type() override;
    [[nodiscard]] lang::ResolvingHandle<lang::Type> type() const;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  public:
    ~MatchSelect() override;

  private:
    std::unique_ptr<Expression>        condition_;
    std::vector<std::unique_ptr<Case>> cases_;

    std::optional<lang::ResolvingHandle<lang::Type>> type_;
};

#endif
