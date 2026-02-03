#include "Grapher.h"

#include <sstream>
#include <string>

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

        void visit(UnorderedScope const& scope) override
        {
            beginGraph();

            for (auto const& flow : scope.flows)
            {
                graphFlow(*flow, flow->id());
            }

            endGraph();
        }

        void visit(Flow const& flow) override
        {
            beginGraph();

            graphFlow(flow, "flow");

            endGraph();
        }

        void visit(BasicBlock const& block) override
        {
            // todo: print meta blocks differently (use the other style)

            std::stringstream code;
            Printer const     code_printer(code);
            code_printer.print(block);

            addNode(code.str(), block.id, Style::CODE);

            current_id_ = block.id;

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

        void visit(AnonymousFunctionConstructor const&) override {}

        void visit(Constant const&) override {}

        void visit(Default const&) override {}

        void visit(CurrentScope const&) override {}

        void visit(UnaryOperation const&) override {}

        void visit(TypeOf const&) override {}

        void visit(OrderedScopeEnter const&) override {}

        void visit(OrderedScopeExit const&) override {}

        void visit(SetReturnValue const&) override {}

      private:
        void graphFlow(Flow const& flow, std::string const& label)
        {
            beginGroup(label);

            for (auto& block : flow.blocks)
            {
                visit(*block);
            }

            endGroup();
        }

        size_t current_id_ = 0;
    };

    explicit Implementation(std::ostream& out) : out_(out) {}

    void graph(Node const& node) const
    {
        utility::Owned<BBT> bbt = utility::makeOwned<BBT>(out_);
        bbt->visit(node);
    }

  private:
    std::ostream& out_;
};

ance::bbt::Grapher::Grapher(std::ostream& out) : implementation_(utility::makeOwned<Implementation>(out)) {}
ance::bbt::Grapher::~Grapher() = default;

void ance::bbt::Grapher::graph(UnorderedScope const& scope) const
{
    implementation_->graph(scope);
}

void ance::bbt::Grapher::graph(Flow const& flow) const
{
    implementation_->graph(flow);
}
