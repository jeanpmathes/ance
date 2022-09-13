#ifndef ANCE_SRC_LANG_EXPRESSION_MEMBERACCESS_H_
#define ANCE_SRC_LANG_EXPRESSION_MEMBERACCESS_H_

#include "DelayableExpression.h"

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
    : public DelayableExpression
    , public lang::Element<MemberAccess, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Construct a member access.
     * @param value The value of which a member is accessed.
     * @param member The identifier of the member.
     * @param location The location of the member access.
     */
    MemberAccess(std::unique_ptr<Expression> value, lang::Identifier member, lang::Location location);

    [[nodiscard]] Expression&             value() const;
    [[nodiscard]] const lang::Identifier& member() const;

  public:
    [[nodiscard]] std::optional<lang::ResolvingHandle<lang::Type>> tryGetType() const override;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  protected:
    void doBuild(CompileContext& context) override;

  public:
    ~MemberAccess() override;

  private:
    std::unique_ptr<Expression> value_;
    lang::Identifier            member_;
};

#endif

