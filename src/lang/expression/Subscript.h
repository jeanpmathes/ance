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
    Subscript(std::unique_ptr<Expression> indexed, std::unique_ptr<Expression> index, lang::Location location);

    [[nodiscard]] Expression& indexed() const;
    [[nodiscard]] Expression& index() const;

    lang::ResolvingHandle<lang::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~Subscript() override;

  private:
    std::unique_ptr<Expression> indexed_;
    std::unique_ptr<Expression> index_;
};

#endif
