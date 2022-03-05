#ifndef ANCE_SRC_COMPILER_CODEPRINTER_H_
#define ANCE_SRC_COMPILER_CODEPRINTER_H_

#include "lang/ApplicationVisitor.h"

class CodePrinter : public lang::ApplicationVisitor
{
  public:
    using lang::ApplicationVisitor::visit;

    explicit CodePrinter(std::ostream& out);

  private:
    std::ostream& out_;
};

#endif
