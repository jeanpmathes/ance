#include "Grapher.h"

#include <cassert>
#include <sstream>

#include "ance/core/Intrinsic.h"

ance::core::Grapher::Grapher(std::ostream& out) : out_(out) {}
ance::core::Grapher::~Grapher() = default;

void ance::core::Grapher::beginGraph()
{
    assert(!in_graph_);

    out_ << "graph [" << std::endl;
    out_ << "\tlabel \"\"" << std::endl;
    out_ << "\tdirected 1" << std::endl;

    in_graph_ = true;
}

void ance::core::Grapher::endGraph()
{
    assert(in_graph_);

    out_ << groups_.str() << std::endl;
    out_ << nodes_.str() << std::endl;
    out_ << edges_.str() << std::endl;

    out_ << "]" << std::endl << std::endl;

    in_graph_ = false;
}

void ance::core::Grapher::beginGroup(std::string const& label)
{
    assert(!in_group_);

    current_group_id_ = node_count_;
    node_count_ += 1;

    groups_ << "\tnode [" << std::endl;
    groups_ << "\t\tlabel \"" << escape(label) << "\"" << std::endl;
    groups_ << "\t\tid " << current_group_id_ << std::endl;
    groups_ << "\t\tisGroup 1" << std::endl;
    groups_ << "\t]" << std::endl;

    id_map_.emplace_back();

    in_group_ = true;
}

void ance::core::Grapher::endGroup()
{
    assert(in_group_);

    in_group_ = false;
}

void ance::core::Grapher::addNode(std::string const& content, size_t const id, Style const style)
{
    std::string color   = "#F8F8F8";
    bool        is_code = false;

    switch (style)
    {
        case Style::CODE:
            color   = "#F8F8F8";
            is_code = true;
            break;
        case Style::META:
            color   = "#FCE205";
            is_code = false;
            break;
    }

    nodes_ << "\tnode [" << std::endl;
    nodes_ << "\t\tlabel \"" << escape(content) << "\"" << std::endl;
    nodes_ << "\t\tid " << map(id) << std::endl;
    nodes_ << "\t\tgid " << current_group_id_ << std::endl;

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

void ance::core::Grapher::addEdge(size_t const from, size_t const to)
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

uint32_t ance::core::Grapher::map(size_t id)
{
    auto const key = static_cast<uint32_t>(id);

    auto& group_map = id_map_.back();

    if (auto const it = group_map.find(key); it != group_map.end()) { return it->second; }

    uint32_t const mapped_id = node_count_++;
    group_map[key]           = mapped_id;

    return mapped_id;
}

std::string ance::core::Grapher::escape(std::string const& string)
{
    std::stringstream result;

    for (char const c : string)
    {
        switch (c)
        {
            case '"':
                result << "&quot;";
                break;
            case '&':
                result << "&amp;";
                break;
            default:
                result << c;
        }
    }

    return result.str();
}
