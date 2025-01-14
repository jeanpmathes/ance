#include "SortingGraph.h"

#include <cassert>

template<typename NodeKey, typename NodeValue>
NodeKey const& lang::SortingGraph<NodeKey, NodeValue>::addNode(NodeKey const& key, NodeValue value)
{
    auto [iterator, inserted] = nodes_.emplace(key, NodeEntry {value, {}});
    assert(inserted);

    return key;
}

template<typename NodeKey, typename NodeValue>
void lang::SortingGraph<NodeKey, NodeValue>::addEdge(NodeKey const& from, NodeKey const& to)
{
    auto source = nodes_.find(from);
    assert(source != nodes_.end());

    auto target = nodes_.find(to);
    assert(target != nodes_.end());

    auto& [target_key, target_value] = *target;
    auto& [source_key, source_value] = *source;

    if (source_value.edges.contains(target_key)) return;
    source_value.edges.emplace(target_key);
}

template<typename NodeKey, typename NodeValue>
NodeValue& lang::SortingGraph<NodeKey, NodeValue>::operator[](NodeKey const& key)
{
    return nodes_.at(key).value;
}

template<typename NodeKey, typename NodeValue>
std::vector<NodeKey> lang::SortingGraph<NodeKey, NodeValue>::sort(std::function<void(NodeKey const&)> const& on_cycle)
{
    int const unvisited = 0;
    int const visited   = 1;
    int const finished  = 2;

    std::stack<std::pair<NodeKey, bool>> to_check;
    std::map<NodeKey, int>               state;
    std::vector<NodeKey>                 ordered_nodes;

    for (auto& node : nodes_)
    {
        auto& [key, value] = node;

        if (!state.contains(key)) to_check.emplace(key, false);

        while (!to_check.empty())
        {
            auto& [current_node, visited_children] = to_check.top();

            if (visited_children)
            {
                ordered_nodes.emplace_back(current_node);

                if (!state.contains(current_node)) state.emplace(current_node, unvisited);
                state.at(current_node) = finished;

                to_check.pop();
            }
            else
            {
                to_check.top() = std::make_pair(current_node, true);

                if (!state.contains(current_node)) state.emplace(current_node, unvisited);

                if (state.at(current_node) == visited)
                {
                    on_cycle(current_node);

                    return {};
                }

                state.at(current_node) = visited;

                for (auto& dependency : nodes_.at(current_node).edges)
                {
                    if (state.contains(dependency) && state.at(dependency) == finished) continue;
                    to_check.emplace(dependency, false);
                }
            }
        }
    }

    return ordered_nodes;
}
