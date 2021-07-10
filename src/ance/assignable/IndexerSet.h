#ifndef ANCE_SRC_ANCE_ASSIGNABLE_INDEXERSET_H_
#define ANCE_SRC_ANCE_ASSIGNABLE_INDEXERSET_H_

#include "Assignable.h"

#include "Expression.h"

class IndexerSet : public Assignable
{
  public:
    explicit IndexerSet(Expression* indexed, Expression* index);

    void setScope(ance::Scope* scope) override;

    void assign(ance::Value* value, CompileContext* context) override;

  private:
    Expression* indexed_;
    Expression* index_;
};

#endif
