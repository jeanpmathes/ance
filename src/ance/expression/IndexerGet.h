#ifndef ANCE_SRC_ANCE_EXPRESSION_INDEXERGET_H_
#define ANCE_SRC_ANCE_EXPRESSION_INDEXERGET_H_

#include "DelayableExpression.h"

#include "ance/construct/value/ExpressionBackedValue.h"

class IndexerGet : public DelayableExpression
{
  public:
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
