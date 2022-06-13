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

    for (auto& bb : function.getBasicBlocks()) { visit(*bb); }

    printBlock("exit", NODE_EXIT, BlockStyle::IMPLICIT);
    printGroup(function.signature().toString());

    out_ << nodes_.rdbuf();
    out_ << edges_.rdbuf();

    nodes_.clear();
    edges_.clear();

    current_function_ = nullptr;
    return {};
}

std::any ControlFlowGraphPrinter::visit(lang::BasicBlock& block)
{
    auto id       = static_cast<int32_t>(block.getId());
    bool has_code = id > 0;

    std::string label;

    if (has_code)
    {
        std::stringstream code_stream;
        CodePrinter       code_printer(code_stream);

        code_printer.visit(block);

        label = escape(code_stream.str());
        label += block.getExitRepresentation();
    }
    else {
        label = current_function_->name().text();
    }

    printBlock(label, id, block.isUnreached() ? BlockStyle::UNREACHABLE_CODE : BlockStyle::NORMAL_CODE);

    std::vector<lang::BasicBlock*> successors = block.getSuccessors();

    if (successors.empty()) { printLink(id, NODE_EXIT); }
    else {
        for (lang::BasicBlock* successor : successors) { printLink(id, static_cast<int32_t>(successor->getId())); }
    }

    return {};
}

void ControlFlowGraphPrinter::printBlock(const std::string& label, int32_t id, BlockStyle style)
{
    std::string color;
    bool        is_code;

    switch (style)
    {
        case BlockStyle::NORMAL_CODE:
            color = "#F8F8F8";
            is_code = true;
            break;
        case BlockStyle::UNREACHABLE_CODE:
            color = "#A9A9A9";
            is_code = true;
            break;
        case BlockStyle::IMPLICIT:
            color = "#FCE205";
            is_code = false;
            break;
    }

    nodes_ << "\tnode [" << std::endl;
    nodes_ << "\t\tlabel \"" << label << "\"" << std::endl;
    nodes_ << "\t\tid " << map(id) << std::endl;
    nodes_ << "\t\tgid " << map(NODE_GROUP) << std::endl;

    nodes_ << "\t\tgraphics [" << std::endl;
    nodes_ << "\t\t\tfill \"" << color << "\"" << std::endl;
    nodes_ << "\t\t]" << std::endl;

    nodes_ << "\t\tLabelGraphics [" << std::endl;
    nodes_ << "\t\t\tfontName \"Consolas\"" << std::endl;
    if (!is_code) nodes_ << "\t\t\tfontStyle \"bold\"" << std::endl;
    if (is_code) nodes_ << "\t\t\talignment \"left\"" << std::endl;
    nodes_ << "\t\t]" << std::endl;

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

std::string ControlFlowGraphPrinter::escape(const std::string& s)
{
    std::string result;

    for (char c : s)
    {
        switch (c)
        {
            case '"':
                result += "&quot;";
                break;
            case '&':
                result += "&amp;";
                break;
            default:
                result += c;
        }
    }

    return result;
}
