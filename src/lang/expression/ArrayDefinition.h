#ifndef ANCE_SRC_LANG_EXPRESSION_ARRAYDEFINITION_H_
#define ANCE_SRC_LANG_EXPRESSION_ARRAYDEFINITION_H_

#include "Expression.h"

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
    : public Expression
    , public lang::Element<ArrayDefinition, ANCE_CONSTRUCTS>
{
  public:
    ArrayDefinition(Optional<lang::ResolvingHandle<lang::Type>> type,
                    lang::Location                              type_location,
                    std::vector<Owned<Expression>>              elements,
                    lang::Location                              location);

    [[nodiscard]] Optional<std::reference_wrapper<lang::Type const>>    elementType() const;
    [[nodiscard]] std::vector<std::reference_wrapper<Expression const>> values() const;

  protected:
    void walkDefinitions() override;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    ~ArrayDefinition() override;

  private:
    Optional<lang::ResolvingHandle<lang::Entity>> declared_type_;
    lang::Location                                type_location_;
    std::vector<Owned<Expression>>                elements_;
};

#endif
