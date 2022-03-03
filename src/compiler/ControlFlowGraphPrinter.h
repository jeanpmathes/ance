#ifndef ANCE_SRC_COMPILER_CONTROLFLOWGRAPHPRINTER_H_
#define ANCE_SRC_COMPILER_CONTROLFLOWGRAPHPRINTER_H_

#include "lang/ApplicationVisitor.h"

class ControlFlowGraphPrinter : public lang::ApplicationVisitor
{
  public:
    using lang::ApplicationVisitor::visit;

    explicit ControlFlowGraphPrinter(std::ostream& out);

    std::any visit(lang::CustomFunction& function) override;
    std::any visit(lang::BasicBlock& block) override;

  private:
    void printNode(const std::string& label, size_t id);
    void printEdge(size_t from, size_t to);

    static size_t offset(size_t x);

  private:
    std::ostream& out_;

    size_t graph_counter_ {0};
    size_t node_counter_ {0};

    lang::CustomFunction* current_function_ {nullptr};
};

#endif
