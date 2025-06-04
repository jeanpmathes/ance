#include "Grapher.h"

#include <sstream>

#include "ance/cet/Node.h"
#include "ance/cet/Printer.h"
#include "ance/core/Grapher.h"

struct ance::cet::Grapher::Implementation
{
    class CET final
        : public Visitor
        , core::Grapher
    {
      public:
        using Visitor::visit;

        explicit CET(std::ostream& out) : Grapher(out) {}
        ~CET() override = default;

        void visit(Unit const& unit) override
        {
            beginGraph();

            for (auto& child : unit.children)
            {
                beginGroup("");
                visit(*child);
                endGroup();
            }

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

        void visit(Independent const&) override
        {

        }

        void visit(Let const& ) override
        {

        }

        void visit(Assignment const&) override {}

        void visit(Temporary const& ) override {}

        void visit(WriteTemporary const& ) override {}

        void visit(Intrinsic const& ) override
        {

        }

        void visit(Call const& ) override
        {

        }

        void visit(Access const& ) override
        {

        }

        void visit(Constant const& ) override
        {

        }

        void visit(UnaryOperation const&) override {}

        void visit(ReadTemporary const& ) override {}

        size_t current_id_ = 0;
    };

    explicit Implementation(std::ostream& out) : out_(out) {}

    void graph(Unit const& unit) const
    {
        utility::Owned<CET> cet = utility::makeOwned<CET>(out_);
        cet->visit(unit);
    }

  private:
    std::ostream& out_;
};

ance::cet::Grapher::Grapher(std::ostream& out) : implementation_(utility::makeOwned<Implementation>(out)) {}
ance::cet::Grapher::~Grapher() = default;

void ance::cet::Grapher::graph(Unit const& unit) const
{
    implementation_->graph(unit);
}
