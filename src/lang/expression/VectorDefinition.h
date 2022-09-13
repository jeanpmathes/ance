#ifndef ANCE_SRC_LANG_EXPRESSION_VECTORDEFINITION_H_
#define ANCE_SRC_LANG_EXPRESSION_VECTORDEFINITION_H_

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
 * A vector value definition.
 */
class VectorDefinition
    : public DelayableExpression
    , public lang::Element<VectorDefinition, ANCE_CONSTRUCTS>
{
  public:
    VectorDefinition(std::optional<lang::ResolvingHandle<lang::Type>> type,
                     lang::Location                                   type_location,
                     std::vector<std::unique_ptr<Expression>>         elements,
                     lang::Location                                   location);

    [[nodiscard]] const std::optional<lang::ResolvingHandle<lang::Type>>& elementType() const;
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
    ~VectorDefinition() override;

  private:
    std::optional<lang::ResolvingHandle<lang::Type>> type_;
    lang::Location                                   type_location_;
    std::vector<std::unique_ptr<Expression>>         elements_;
};

#endif

