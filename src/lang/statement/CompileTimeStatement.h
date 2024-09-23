#ifndef ANCE_SRC_LANG_STATEMENT_COMPILETIMESTATEMENT_H_
#define ANCE_SRC_LANG_STATEMENT_COMPILETIMESTATEMENT_H_

#include "Statement.h"

/**
 * A statement that can be evaluated at compile-time.
 * Note that runtime evaluation is not excluded.
 */
class CompileTimeStatement : public virtual Statement
{
  public:
    [[nodiscard]] bool isRootCMP() const override;
};

#endif
