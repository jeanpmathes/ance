#include "Compiler.h"

#include <array>

#include "ance/cet/Node.h"

namespace ance::build
{
    class CET final : public cet::Visitor
    {
      public:
        using Visitor::visit;

        ~CET() override = default;

        void visit(cet::Unit const& unit) override
        {
            (void) unit;// todo: implement
        }

        void visit(cet::BasicBlock const& basic_block) override
        {
            (void) basic_block;// todo: implement
        }

        void visit(cet::Independent const& independent) override
        {
            (void) independent;// todo: implement
        }

        void visit(cet::Intrinsic const& intrinsic) override
        {
            (void) intrinsic;// todo: implement
        }
    };
}

struct ance::build::Compiler::Implementation {
    void compile(cet::Unit const& unit)
    {
        utility::Owned<CET> cet = utility::makeOwned<CET>();

        cet->visit(unit);
    }
};

ance::build::Compiler::Compiler() : implementation_(utility::makeOwned<Implementation>()) {}

ance::build::Compiler::~Compiler() = default;

void ance::build::Compiler::compile(cet::Unit const& unit)
{
    implementation_->compile(unit);
}
