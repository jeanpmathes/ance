#ifndef ANCE_SRC_LANG_EXPRESSION_MEMBERACCESS_H_
#define ANCE_SRC_LANG_EXPRESSION_MEMBERACCESS_H_

#include "CompileTimeExpression.h"

#include "lang/Element.h"
#include "lang/construct/Variable.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Scope;
}

/**
 * Access a member of a type.
 */
class MemberAccess
    : public CompileTimeExpression
    , public lang::Element<MemberAccess, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Construct a member access.
     * @param value The value of which a member is accessed.
     * @param member The identifier of the member.
     * @param location The location of the member access.
     */
    MemberAccess(Owned<Expression> value, lang::Identifier member, lang::Location location);

    [[nodiscard]] Expression const&       value() const;
    [[nodiscard]] lang::Identifier const& member() const;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void walkDefinitions() override;
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    ~MemberAccess() override;

  private:
    Owned<Expression> value_;
    lang::Identifier  member_;
};

#endif
