#ifndef ANCE_SRC_LANG_EXPRESSION_ALLOCATION_H_
#define ANCE_SRC_LANG_EXPRESSION_ALLOCATION_H_

#include "Expression.h"

#include <optional>

#include "../utility/ResolvingHandle.h"
#include "compiler/Runtime.h"
#include "lang/Element.h"

class Application;

/**
 * An allocation expression.
 */
class Allocation
    : public Expression
    , public lang::Element<Allocation, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new allocation.
     * @param allocation The allocation type.
     * @param type The type of the value to allocate.
     * @param count An expression providing the number of elements to allocate.
     * @param location The source location.
     * @param allocated_type_location The source location of the type that is allocated.
     */
    Allocation(Runtime::Allocator                allocation,
               lang::ResolvingHandle<lang::Type> type,
               Optional<Owned<Expression>>       count,
               lang::Location                    location,
               lang::Location                    allocated_type_location);

    [[nodiscard]] Runtime::Allocator  allocator() const;
    [[nodiscard]] lang::Entity const& allocatedType() const;
    [[nodiscard]] Expression const*   count() const;

  protected:
    void walkDefinitions() override;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    ~Allocation() override;

  private:
    Runtime::Allocator                  allocation_;
    lang::ResolvingHandle<lang::Entity> allocated_type_;
    lang::Location                      allocated_type_location_;
    Optional<Owned<Expression>>         count_;
};

#endif
