#ifndef ANCE_SRC_ANCE_EXPRESSION_INDEXERGET_H_
#define ANCE_SRC_ANCE_EXPRESSION_INDEXERGET_H_

#include "DelayableExpression.h"

#include "ance/construct/value/ExpressionBackedValue.h"

/**
 * An indexer (subscript) get operation.
 */
class IndexerGet : public DelayableExpression
{
  public:
    /**
     * Create a new indexer get.
     * @param indexed The indexed value.
     * @param index The index to use.
     */
    IndexerGet(Expression* indexed, Expression* index);

    void setScope(ance::Scope* scope) override;

    ance::Type* type() override;

    void buildValue(CompileContext* context) override;

    ~IndexerGet() override;

  private:
    Expression* indexed_;
    Expression* index_;
};

#endif
