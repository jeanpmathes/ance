#ifndef ANCE_CORE_GRAPHER_H
#define ANCE_CORE_GRAPHER_H

#include <map>
#include <ostream>
#include <sstream>
#include <vector>

namespace ance::core
{
    struct Intrinsic;

    /// Utility to simplify implementing code graphers for different trees.
    class Grapher
    {
      public:
        explicit Grapher(std::ostream& out);
        virtual ~Grapher();

        enum class Style
        {
            CODE,
            META
        };

      protected:
        void beginGraph();
        void endGraph();

        void beginGroup(std::string const& label);
        void endGroup();

        void addNode(std::string const& content, size_t id, Style style);
        void addEdge(size_t from, size_t to);

      private:
        uint32_t           map(size_t id);
        static std::string escape(std::string const& string);

        std::ostream& out_;

        std::stringstream groups_ {};
        std::stringstream nodes_ {};
        std::stringstream edges_ {};

        bool in_graph_ {false};
        bool in_group_ {false};

        uint32_t node_count_ {0};

        uint32_t                                  current_group_id_ {0};
        std::vector<std::map<uint32_t, uint32_t>> id_map_ {};
    };
}

#endif
