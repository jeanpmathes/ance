#ifndef ANCE_SRC_COMPILER_CONTROLFLOWGRAPHPRINTER_H_
#define ANCE_SRC_COMPILER_CONTROLFLOWGRAPHPRINTER_H_

#include "lang/ApplicationVisitor.h"

class ControlFlowGraphPrinter : public lang::ApplicationVisitor
{
  public:
    using lang::ApplicationVisitor::visit;

    explicit ControlFlowGraphPrinter(std::ostream& out);

    std::any visit(Application& app) override;
    std::any visit(lang::CustomFunction& function) override;
    std::any visit(lang::BasicBlock& block) override;

  private:
    void printBlock(const std::string& label, int32_t id);
    void printLink(int32_t from, int32_t to);
    void printGroup(const std::string& label);

    uint32_t map(int32_t i);

  private:
    enum SpecialNodes
    {
        NODE_EXIT  = -1,
        NODE_GROUP = -2,
    };

  private:
    std::ostream& out_;

    std::stringstream nodes_ {};
    std::stringstream edges_ {};

    std::map<std::pair<lang::CustomFunction*, int32_t>, uint32_t> id_map_ {};
    uint32_t                                                      node_counter_ {0};
    lang::CustomFunction*                                         current_function_ {nullptr};
};

#endif
