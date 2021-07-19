#ifndef ANCE_SRC_ANCE_EXPRESSION_ALLOCATION_H_
#define ANCE_SRC_ANCE_EXPRESSION_ALLOCATION_H_

#include "DelayableExpression.h"

#include "compiler/Application.h"
#include "compiler/Runtime.h"

class Allocation : public DelayableExpression
{
  public:
    Allocation(Runtime::Allocator allocation, ance::Type* type, Expression* count, Application& app);

    void setScope(ance::Scope* scope) override;

    ance::Type* type() override;

    void buildValue(CompileContext* context) override;

    ~Allocation() override;

  private:
    Runtime::Allocator allocation_;
    ance::Type*        allocated_type_;
    Expression*        count_;
    ance::Type*        return_type_;
};

#endif
