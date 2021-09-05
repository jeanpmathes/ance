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
     * @param location The source location.
     */
    IndexerGet(Expression* indexed, Expression* index, ance::Location location);

  protected:
    void setScope(ance::Scope* scope) override;

  public:
    ance::Type* type() override;

    bool validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~IndexerGet() override;

  private:
    Expression* indexed_;
    Expression* index_;
};

#endif
