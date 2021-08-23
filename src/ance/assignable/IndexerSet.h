#ifndef ANCE_SRC_ANCE_ASSIGNABLE_INDEXERSET_H_
#define ANCE_SRC_ANCE_ASSIGNABLE_INDEXERSET_H_

#include "Assignable.h"

#include "ance/expression/Expression.h"

/**
 * Assign via the set indexer of a type.
 */
class IndexerSet : public Assignable
{
  public:
    /**
     * Create a new IndexerSet.
     * @param indexed The expression providing the value to be indexed.
     * @param index The expression providing the value to use as index.
     */
    explicit IndexerSet(Expression* indexed, Expression* index);

    void setScope(ance::Scope* scope) override;
    void assign(ance::Value* value, CompileContext* context) override;

  private:
    Expression* indexed_;
    Expression* index_;
};

#endif
