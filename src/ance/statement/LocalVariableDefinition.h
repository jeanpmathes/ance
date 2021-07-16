#ifndef ANCE_SRC_ANCE_STATEMENT_LOCALVARIABLEDEFINITION_H_
#define ANCE_SRC_ANCE_STATEMENT_LOCALVARIABLEDEFINITION_H_

#include "Statement.h"

#include "Assigner.h"

namespace ance
{
    class LocalVariable;
}

class Expression;

class LocalVariableDefinition : public Statement
{
  public:
    LocalVariableDefinition(
        std::string  identifier,
        ance::Type*  type,
        Assigner     assigner,
        Expression*  assigned,
        unsigned int l,
        unsigned int c);

    void setFunction(ance::DefinedFunction* function) override;

    void build(CompileContext* context) override;

  private:
    std::string identifier_;
    ance::Type* type_;
    Assigner    assigner_;
    Expression* assigned_;

    ance::LocalVariable* variable_ {nullptr};
};

#endif