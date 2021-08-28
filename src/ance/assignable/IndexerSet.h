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
     * @param location The source location.
     */
    explicit IndexerSet(Expression* indexed, Expression* index, ance::Location location);

    void validate() override;

  protected:
    void setScope(ance::Scope* scope) override;
    void doBuild(CompileContext* context) override;

  private:
    Expression* indexed_;
    Expression* index_;
};

#endif
