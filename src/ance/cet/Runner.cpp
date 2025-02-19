#include "Runner.h"

#include <array>
#include <iostream>

#include "ance/bbt/Node.h"
#include "ance/cet/Node.h"

namespace ance::cet
{
    class BBT final : public bbt::Visitor
    {
    public:
        using Visitor::visit;

        ~BBT() override = default;

        void visit(bbt::BasicBlock const& basic_block) override
        {
            for (auto& statement : basic_block.statements)
            {
                visit(*statement);
            }
        }

        void visit(bbt::ErrorStatement const&) override
        {
            is_invalid_ = true;
        }

        void visit(bbt::Independent const& independent) override
        {
            visit(*independent.expression);
        }

        void visit(bbt::ErrorExpression const&) override
        {
            is_invalid_ = true;
        }

        void visit(bbt::Intrinsic const& intrinsic) override
        {
            std::cout << "DEBUG: " << intrinsic.identifier << std::endl; // todo: remove
        }

    private:
        bool is_invalid_ = false;
    };
}

struct ance::cet::Runner::Implementation
{
    utility::Owned<Unit> run(bbt::BasicBlock const& block)
    {
        utility::Owned<Unit> unit = utility::makeOwned<Unit>();

        utility::Owned<BBT> bbt = utility::makeOwned<BBT>();
        bbt->visit(block);

        return unit;
    }
};

ance::cet::Runner::Runner() : implementation_(utility::makeOwned<Implementation>()) {}

ance::cet::Runner::~Runner() = default;

ance::utility::Owned<ance::cet::Unit> ance::cet::Runner::run(bbt::BasicBlock const& block)
{
    return implementation_->run(block);
}
