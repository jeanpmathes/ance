#include "Grapher.h"

#include <sstream>
#include <string>
#include <unordered_set>
#include <queue>

#include "ance/bbt/Node.h"
#include "ance/bbt/Printer.h"
#include "ance/core/Grapher.h"

struct ance::bbt::Grapher::Implementation
{
    class BBT final
        : public Visitor
        , core::Grapher
    {
      public:
        using Visitor::visit;

        explicit BBT(std::ostream& out) : Grapher(out) {}
        ~BBT() override = default;

        void visit(Flows const& flows) override
        {
            for (auto const& flow : flows.flows)
            {
                visit(*flow);
            }
        }

        void visit(UnorderedScope const& scope) override
        {
            beginGraph();

            for (auto const& flow : scope.flows)
            {
                visit(*flow);
            }
        }

        void visit(Flow const& flow) override
        {
            auto [_, inserted] = graphed_flows_.insert(&flow);
            if (!inserted) return;

            bool const is_top_level_flow = flow_depth_ == 0;
            flow_depth_++;

            beginGroup(flow.id());

            for (auto& block : flow.blocks)
            {
                visit(*block);
            }

            endGroup();

            if (is_top_level_flow)
            {
                while (!nested_flows_to_graph_.empty())
                {
                    visit(*nested_flows_to_graph_.front());
                    nested_flows_to_graph_.pop();
                }

                graphed_flows_.clear();
            }

            flow_depth_--;
        }

        void visit(BasicBlock const& block) override
        {
            // todo: print meta blocks differently (use the other style)

            std::stringstream code;
            Printer const     code_printer(code);
            code_printer.print(block);

            addNode(code.str(), block.id, Style::CODE);

            current_id_ = block.id;

            for (auto& statement : block.statements)
            {
                visit(*statement);
            }

            visit(*block.link);
        }

        void visit(ErrorLink const&) override {}

        void visit(Return const&) override
        {
            // Nothing to link.

            // todo: maybe add a meta return block and link to that
        }

        void visit(Branch const& branch_link) override
        {
            addEdge(current_id_, branch_link.true_branch.id);
            addEdge(current_id_, branch_link.false_branch.id);
        }

        void visit(Jump const& jump_link) override
        {
            addEdge(current_id_, jump_link.target.id);
        }

        void visit(ErrorStatement const&) override {}

        void visit(Pass const&) override {}

        void visit(Store const&) override {}

        void visit(Access const&) override {}

        void visit(Temporary const&) override {}

        void visit(CopyTemporary const&) override {}

        void visit(Intrinsic const&) override {}

        void visit(Call const&) override {}

        void visit(AnonymousFunctionConstructor const& function_constructor) override
        {
            nested_flows_to_graph_.push(function_constructor.body.get());
        }

        void visit(Constant const&) override {}

        void visit(Default const&) override {}

        void visit(CurrentScope const&) override {}

        void visit(UnaryOperation const&) override {}

        void visit(TypeOf const&) override {}

        void visit(OrderedScopeEnter const&) override {}

        void visit(OrderedScopeExit const&) override {}

        void visit(SetReturnValue const&) override {}

        void begin()
        {
            beginGraph();
        }

        void end()
        {
            endGraph();
        }

      private:
        size_t current_id_ = 0;

        size_t flow_depth_ = 0;
        std::queue<Flow const*> nested_flows_to_graph_;
        std::unordered_set<Flow const*> graphed_flows_;
    };

    explicit Implementation(std::ostream& out) : out_(out) {}

    void graph(Node const& node) const
    {
        utility::Owned<BBT> bbt = utility::makeOwned<BBT>(out_);
        bbt->begin();
        bbt->visit(node);
        bbt->end();
    }

  private:
    std::ostream& out_;
};

ance::bbt::Grapher::Grapher(std::ostream& out) : implementation_(utility::makeOwned<Implementation>(out)) {}
ance::bbt::Grapher::~Grapher() = default;

void ance::bbt::Grapher::graph(Flows const& flows) const
{
    implementation_->graph(flows);
}

void ance::bbt::Grapher::graph(Flow const& flow) const
{
    implementation_->graph(flow);
}
