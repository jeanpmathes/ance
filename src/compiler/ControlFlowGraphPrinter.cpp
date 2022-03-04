#include "ControlFlowGraphPrinter.h"

ControlFlowGraphPrinter::ControlFlowGraphPrinter(std::ostream& out) : out_(out) {}

std::any ControlFlowGraphPrinter::visit(Application& app)
{
    out_ << "graph [" << std::endl;
    out_ << "\tlabel \"\"" << std::endl;
    out_ << "\tdirected 1" << std::endl;

    visitChildren(app);

    out_ << "]" << std::endl << std::endl;
    return {};
}

std::any ControlFlowGraphPrinter::visit(lang::CustomFunction& function)
{
    current_function_ = &function;

    visitChildren(function);

    printBlock("exit", NODE_EXIT);
    printGroup(function.name());

    out_ << nodes_.rdbuf();
    out_ << edges_.rdbuf();

    nodes_.clear();
    edges_.clear();

    current_function_ = nullptr;
    return {};
}

std::any ControlFlowGraphPrinter::visit(lang::BasicBlock& block)
{
    auto        id   = static_cast<int32_t>(block.getId());
    std::string name = (id > 0) ? std::to_string(id) + "b" : current_function_->name();

    printBlock(name, id);

    std::vector<lang::BasicBlock*> successors = block.getSuccessors();

    if (successors.empty()) { printLink(id, NODE_EXIT); }
    else {
        for (lang::BasicBlock* successor : successors) { printLink(id, static_cast<int32_t>(successor->getId())); }
    }

    return {};
}

void ControlFlowGraphPrinter::printBlock(const std::string& label, int32_t id)
{
    nodes_ << "\tnode [" << std::endl;
    nodes_ << "\t\tlabel \"" << label << "\"" << std::endl;
    nodes_ << "\t\tid " << map(id) << std::endl;
    nodes_ << "\t\tgid " << map(NODE_GROUP) << std::endl;
    nodes_ << "\t]" << std::endl;
}

void ControlFlowGraphPrinter::printLink(int32_t from, int32_t to)
{
    edges_ << "\tedge [" << std::endl;
    edges_ << "\t\tsource " << map(from) << std::endl;
    edges_ << "\t\ttarget " << map(to) << std::endl;
    edges_ << "\t]" << std::endl;
}

void ControlFlowGraphPrinter::printGroup(const std::string& label)
{
    nodes_ << "\tnode [" << std::endl;
    nodes_ << "\t\tlabel \"" << label << "\"" << std::endl;
    nodes_ << "\t\tid " << map(NODE_GROUP) << std::endl;
    nodes_ << "\t\tisGroup 1" << std::endl;
    nodes_ << "\t]" << std::endl;
}

uint32_t ControlFlowGraphPrinter::map(int32_t i)
{
    assert(current_function_);

    auto key = std::make_pair(current_function_, i);
    if (id_map_.contains(key)) { return id_map_[key]; }

    uint32_t id  = node_counter_++;
    id_map_[key] = id;
    return id;
}
