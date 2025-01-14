#ifndef ANCE_SRC_LANG_UTILITY_SORTINGGRAPH_H_
#define ANCE_SRC_LANG_UTILITY_SORTINGGRAPH_H_

#include <map>
#include <set>
#include <vector>

namespace lang
{
    /**
     * A graph that can be sorted topologically.
     * @tparam NodeKey The type of the key of the nodes.
     * @tparam NodeValue The type of the value of the nodes.
     */
    template<typename NodeKey, typename NodeValue>
    class SortingGraph
    {
      public:
        /**
         * Add a node to the graph.
         * The key is not allowed to be in the graph already.
         * @param key The key of the node.
         * @param value The value of the node.
         * @return The key of the node.
         */
        NodeKey const& addNode(NodeKey const& key, NodeValue value);

        /**
         * Add an edge between two nodes.
         * Both nodes must already be in the graph.
         * @param from The key of the node the edge starts at.
         * @param to The key of the node the edge ends at.
         */
        void addEdge(NodeKey const& from, NodeKey const& to);

        /**
         * Get the value of a node.
         * @param key The key of the node.
         * @return The value of the node.
         */
        NodeValue& operator[](NodeKey const& key);

        /**
         * Sort the graph topologically.
         * @param on_cycle A function that is called when a cycle is detected.
         * @return The sorted keys of the nodes.
         */
        std::vector<NodeKey> sort(std::function<void(NodeKey const&)> const& on_cycle);

      private:
        struct NodeEntry {
            NodeValue         value;
            std::set<NodeKey> edges;
        };

        std::map<NodeKey, NodeEntry> nodes_;
    };
}

#include "SortingGraph.tpp"

#endif
