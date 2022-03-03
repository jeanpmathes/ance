#include "ControlFlowGraphPrinter.h"

ControlFlowGraphPrinter::ControlFlowGraphPrinter(std::ostream& out) : out_(out) {}

std::any ControlFlowGraphPrinter::visit(lang::CustomFunction& function)
{
    out_ << "graph [" << std::endl;
    out_ << "\tlabel \"" << function.name() << "\"" << std::endl;
    out_ << "\tid " << std::to_string(graph_counter_) << std::endl;

    graph_counter_++;
    node_counter_ = 0;

    current_function_ = &function;

    visitChildren(function);

    current_function_ = nullptr;

    printNode("exit", 0);

    out_ << "]" << std::endl << std::endl;
    return {};
}

std::any ControlFlowGraphPrinter::visit(lang::BasicBlock& block)
{
    size_t      id   = block.getId();
    std::string name = (id > 0) ? std::to_string(id) + "b" : current_function_->name();

    printNode(name, offset(id));
    node_counter_++;

    std::vector<lang::BasicBlock*> successors = block.getSuccessors();

    if (successors.empty()) { printEdge(offset(id), 0); }
    else {
        for (lang::BasicBlock* successor : successors) { printEdge(offset(id), offset(successor->getId())); }
    }

    return {};
}

void ControlFlowGraphPrinter::printNode(const std::string& label, size_t id)
{
    out_ << "\tnode [" << std::endl;
    out_ << "\t\tlabel \"" << label << "\"" << std::endl;
    out_ << "\t\tid " << id << std::endl;
    out_ << "\t]" << std::endl;
}

void ControlFlowGraphPrinter::printEdge(size_t from, size_t to)
{
    out_ << "\tedge [" << std::endl;
    out_ << "\t\tsource " << from << std::endl;
    out_ << "\t\ttarget " << to << std::endl;
    out_ << "\t]" << std::endl;
}

size_t ControlFlowGraphPrinter::offset(size_t x)
{
    return x + 1;
}
