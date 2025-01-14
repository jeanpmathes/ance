#ifndef ANCE_SRC_LANG_EXPRESSION_CAST_H_
#define ANCE_SRC_LANG_EXPRESSION_CAST_H_

#include "CompileTimeExpression.h"

#include "lang/Element.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Scope;
}

/**
 * A cast of a value to another value in a given type.
 */
class Cast
    : public CompileTimeExpression
    , public lang::Element<Cast, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new cast.
     * @param value The value to cast.
     * @param type The type to cast to.
     * @param location The source location.
     */
    Cast(Owned<Expression>                 value,
         lang::ResolvingHandle<lang::Type> type,
         lang::Location                    location,
         lang::Location                    type_location);

    [[nodiscard]] Expression const&   value() const;
    [[nodiscard]] lang::Entity const& target() const;

    void defineType(lang::ResolvingHandle<lang::Type> type) override;

    void walkDefinitions() override;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

    ~Cast() override;

  private:
    Owned<Expression>                   value_;
    lang::ResolvingHandle<lang::Entity> type_;

    lang::Location type_location_;
};

#endif
