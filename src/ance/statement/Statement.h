#ifndef ANCE_SRC_ANCE_STATEMENT_STATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_STATEMENT_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "compiler/CompileContext.h"
#include "ance/utility/Location.h"

class CompileContext;

namespace ance
{
    class DefinedFunction;
}

class Statement
{
  public:
    Statement(ance::Location location);

    void setContainingFunction(ance::DefinedFunction* function);

  protected:
    virtual void setFunction(ance::DefinedFunction* function);

  public:
    [[nodiscard]] ance::DefinedFunction* getContainingFunction() const;

    [[nodiscard]] ance::Location location() const;

    virtual void build(CompileContext* context) = 0;

    virtual ~Statement() = default;

  private:
    ance::Location location_;

    ance::DefinedFunction* function_ {nullptr};
};

#endif