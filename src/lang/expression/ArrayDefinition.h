#ifndef ANCE_SRC_LANG_EXPRESSION_ARRAYDEFINITION_H_
#define ANCE_SRC_LANG_EXPRESSION_ARRAYDEFINITION_H_

#include "DelayableExpression.h"

#include <set>

#include "lang/Element.h"
#include "lang/construct/Function.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Scope;
}

/**
 * An expression that defines an array value.
 */
class ArrayDefinition
    : public DelayableExpression
    , public lang::Element<ArrayDefinition, ANCE_CONSTRUCTS>
{
  public:
    ArrayDefinition(std::optional<lang::ResolvingHandle<lang::Type>> type,
                    lang::Location                                   type_location,
                    std::vector<std::unique_ptr<Expression>>         elements,
                    lang::Location                                   location);

    [[nodiscard]] std::optional<lang::ResolvingHandle<lang::Type>> const& elementType() const;
    [[nodiscard]] std::vector<std::reference_wrapper<Expression>>         values() const;

  protected:
    void walkDefinitions() override;

  public:
    [[nodiscard]] std::optional<lang::ResolvingHandle<lang::Type>> tryGetType() const override;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  protected:
    void doBuild(CompileContext& context) override;

  public:
    ~ArrayDefinition() override;

  private:
    std::optional<lang::ResolvingHandle<lang::Type>> type_;
    lang::Location                                   type_location_;
    std::vector<std::unique_ptr<Expression>>         elements_;
};

#endif
