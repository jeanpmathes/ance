#include "Grapher.h"

#include <sstream>

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

        void visit(Flow const& flow) override
        {
            beginGraph();

            beginGroup("flow");

            for (auto& block : flow.blocks)
            {
                visit(*block);
            }

            endGroup();

            endGraph();
        }

        void visit(BasicBlock const& block) override
        {
            // todo: print meta blocks differently (use the other style)

            std::stringstream code;
            Printer const code_printer(code);
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

        void visit(ErrorStatement const&) override {  }

        void visit(Independent const& ) override
        {

        }

        void visit(Let const& ) override
        {

        }

        void visit(Assignment const& ) override
        {

        }

        void visit(Temporary const& ) override {}

        void visit(WriteTemporary const& ) override {}

        void visit(ErrorExpression const&) override {  }

        void visit(Intrinsic const& ) override
        {

        }

        void visit(Call const&) override
        {

        }

        void visit(Access const& ) override
        {

        }

        void visit(Constant const& ) override
        {

        }

        void visit(UnaryOperation const&) override {}

        void visit(ReadTemporary const&) override {}

        size_t current_id_ = 0;
    };

    explicit Implementation(std::ostream& out) : out_(out) {}

    void graph(Flow const& flow) const
    {
        utility::Owned<BBT> bbt = utility::makeOwned<BBT>(out_);
        bbt->visit(flow);
    }

  private:
    std::ostream& out_;
};

ance::bbt::Grapher::Grapher(std::ostream& out) : implementation_(utility::makeOwned<Implementation>(out)) {}
ance::bbt::Grapher::~Grapher() = default;

void ance::bbt::Grapher::graph(Flow const& flow) const
{
    implementation_->graph(flow);
}
