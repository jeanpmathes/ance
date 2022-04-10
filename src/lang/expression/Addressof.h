#ifndef ANCE_SRC_LANG_EXPRESSION_ADDRESSOF_H_
#define ANCE_SRC_LANG_EXPRESSION_ADDRESSOF_H_

#include "DelayableExpression.h"

#include <optional>

#include "compiler/Runtime.h"

class Application;

/**
 * An addressof expression.
 */
class Addressof
    : public DelayableExpression
    , public lang::Element<Addressof, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create an addressof expression that provides the address of the arg.
     * @param arg The argument to get the address of.
     * @param location The source location of the expression.
     */
    Addressof(std::unique_ptr<Expression> arg, lang::Location location);

    [[nodiscard]] Expression& argument() const;

  public:
    lang::ResolvingHandle<lang::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~Addressof() override;

  private:
    std::unique_ptr<Expression>                      arg_;
    std::optional<lang::ResolvingHandle<lang::Type>> return_type_ {};
};
#endif