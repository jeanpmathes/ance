#ifndef ANCE_SRC_LANG_EXPRESSION_ALLOCATION_H_
#define ANCE_SRC_LANG_EXPRESSION_ALLOCATION_H_

#include "DelayableExpression.h"

#include "compiler/Runtime.h"
#include "lang/Element.h"

class Application;

/**
 * An allocation expression.
 */
class Allocation
    : public DelayableExpression
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
               std::unique_ptr<Expression>       count,
               lang::Location                    location,
               lang::Location                    allocated_type_location);

    [[nodiscard]] Runtime::Allocator                allocator() const;
    [[nodiscard]] lang::ResolvingHandle<lang::Type> allocatedType() const;
    [[nodiscard]] Expression*                       count() const;

  protected:
    void setScope(lang::Scope* scope) override;

  public:
    lang::ResolvingHandle<lang::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~Allocation() override;

  private:
    Runtime::Allocator                allocation_;
    lang::ResolvingHandle<lang::Type> allocated_type_;
    lang::Location                    allocated_type_location_;
    std::unique_ptr<Expression>       count_;
    lang::ResolvingHandle<lang::Type> return_type_;
};

#endif
