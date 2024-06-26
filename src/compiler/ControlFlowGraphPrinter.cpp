#include "ControlFlowGraphPrinter.h"

ControlFlowGraphPrinter::ControlFlowGraphPrinter(std::ostream& out) : out_(out) {}

std::any ControlFlowGraphPrinter::visit(Unit const& unit)
{
    out_ << "graph [" << std::endl;
    out_ << "\tlabel \"\"" << std::endl;
    out_ << "\tdirected 1" << std::endl;

    visitChildren(unit);

    out_ << "]" << std::endl << std::endl;
    return {};
}

std::any ControlFlowGraphPrinter::visit(lang::FunctionDescription const& function_description)
{
    current_function_ = function_description.function();
    assert(current_function_);

    for (auto& basic_block : current_function_->getBasicBlocks())
    {
        lang::BasicBlock const& block = *basic_block;
        visitBB(block);
    }

    printBlock("exit", NODE_EXIT, BlockStyle::META);
    printGroup(current_function_->signature().toString());

    out_ << nodes_.str();
    out_ << edges_.str();

    std::stringstream().swap(nodes_);
    std::stringstream().swap(edges_);

    current_function_ = nullptr;
    return {};
}

std::any ControlFlowGraphPrinter::visitBB(lang::BasicBlock const& block)
{
    auto id = static_cast<int32_t>(block.id());

    std::string label;
    BlockStyle  style;

    if (!block.isMeta())
    {
        for (size_t child_index = 0; child_index < block.childCount(); child_index++)
        {
            std::stringstream code_stream;
            CodePrinter       code_printer(code_stream);

            code_printer.visitTree(block.getChild(child_index));

            label += escape(code_stream.str());
            label += '\n';
        }

        label += block.getExitRepresentation();
        style = block.isUnreached() ? BlockStyle::UNREACHABLE_CODE : BlockStyle::NORMAL_CODE;
    }
    else
    {
        bool const inside = id > 0;

        label = inside ? block.getExitRepresentation() : current_function_->name().text();
        style = BlockStyle::META;
    }

    printBlock(label, id, style);

    std::vector<lang::BasicBlock const*> const successors = block.getSuccessors();

    if (successors.empty()) { printLink(id, NODE_EXIT); }
    else
    {
        for (lang::BasicBlock const* successor : successors)
        { printLink(id, static_cast<int32_t>(successor->id())); }
    }

    return {};
}

void ControlFlowGraphPrinter::printBlock(std::string const& label, int32_t id, BlockStyle style)
{
    std::string color;
    bool        is_code;

    switch (style)
    {
        case BlockStyle::NORMAL_CODE:
            color   = "#F8F8F8";
            is_code = true;
            break;
        case BlockStyle::UNREACHABLE_CODE:
            color   = "#A9A9A9";
            is_code = true;
            break;
        case BlockStyle::META:
            color   = "#FCE205";
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

    edges_ << "\t\tgraphics [" << std::endl;
    edges_ << "\t\t\tfill \"#000000\"" << std::endl;
    edges_ << "\t\t\ttargetArrow \"short\"" << std::endl;
    edges_ << "\t\t]" << std::endl;

    edges_ << "\t]" << std::endl;
}

void ControlFlowGraphPrinter::printGroup(std::string const& label)
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

    uint32_t const id = node_counter_++;
    id_map_[key]      = id;
    return id;
}

std::string ControlFlowGraphPrinter::escape(std::string const& s)
{
    std::string result;

    for (char const c : s)
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
