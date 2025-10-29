#include "Grapher.h"

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

        void visit(Unit const&) override
        {
            beginGraph();

            endGraph();
        }

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
