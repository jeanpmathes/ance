#ifndef ANCE_SRC_LANG_EXPRESSION_SIZEOFTYPE_H_
#define ANCE_SRC_LANG_EXPRESSION_SIZEOFTYPE_H_

#include "Expression.h"

#include "lang/Element.h"

class Application;

/**
 * Provides the size of a type.
 */
class SizeofType
    : public Expression
    , public lang::Element<SizeofType, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new sizeof type expression.
     * @param type The type to provide the size of.
     * @param location The source location.
     */
    explicit SizeofType(lang::ResolvingHandle<lang::Type> type, lang::Location type_location, lang::Location location);

    [[nodiscard]] lang::Entity const& target() const;

  protected:
    void walkDefinitions() override;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  private:
    lang::ResolvingHandle<lang::Entity> type_;
    lang::Location                      type_location_;
};

#endif
