#ifndef ANCE_SRC_COMPILER_CONTROLFLOWGRAPHPRINTER_H_
#define ANCE_SRC_COMPILER_CONTROLFLOWGRAPHPRINTER_H_

#include "lang/ApplicationVisitor.h"

#include "compiler/CodePrinter.h"

class ControlFlowGraphPrinter : public lang::ApplicationVisitorConst
{
  private:
    enum class BlockStyle
    {
        NORMAL_CODE,
        UNREACHABLE_CODE,
        META
    };

  public:
    using lang::ApplicationVisitorConst::visit;

    explicit ControlFlowGraphPrinter(std::ostream& out);

    std::any visit(Unit const& unit) override;
    std::any visit(lang::FunctionDescription const& function) override;

  private:
    std::any visitBB(lang::BasicBlock const& block);

    void printBlock(std::string const& label, int32_t id, BlockStyle style);
    void printLink(int32_t from, int32_t to);
    void printGroup(std::string const& label);

    uint32_t map(int32_t i);

    static std::string escape(std::string const& s);

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

    std::map<std::pair<lang::Function const*, int32_t>, uint32_t> id_map_ {};
    uint32_t                                                      node_counter_ {0};
    lang::Function const*                                         current_function_ {nullptr};
};

#endif
