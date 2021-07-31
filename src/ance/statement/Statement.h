#ifndef ANCE_SRC_ANCE_STATEMENT_STATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_STATEMENT_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "compiler/CompileContext.h"

class CompileContext;

namespace ance
{
    class DefinedFunction;
}

class Statement
{
  public:
    Statement(unsigned int line, unsigned int column);

    void setContainingFunction(ance::DefinedFunction* function);

  protected:
    virtual void setFunction(ance::DefinedFunction* function);

  public:
    [[nodiscard]] ance::DefinedFunction* getContainingFunction() const;

    [[nodiscard]] unsigned int line() const;
    [[nodiscard]] unsigned int column() const;

    virtual void build(CompileContext* context) = 0;

    virtual ~Statement() = default;

  private:
    unsigned int line_;
    unsigned int column_;

    ance::DefinedFunction* function_ {nullptr};
};

#endif