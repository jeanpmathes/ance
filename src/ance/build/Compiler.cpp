#include "Compiler.h"

#include "ance/core/Intrinsic.h"

#include "ance/cet/Node.h"

struct ance::build::Compiler::Implementation
{
    class CET final : public cet::Visitor
    {
      public:
        using Visitor::visit;

        explicit CET(core::Reporter& reporter) : reporter_(reporter) {}
        ~CET() override = default;

        void visit(cet::Unit const& unit) override
        {
            (void) unit;     // todo: implement
            (void) reporter_;// todo: use or remove
        }

      private:
        core::Reporter& reporter_;
    };

    explicit Implementation(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
        : source_tree_(source_tree)
        , reporter_(reporter)
        , context_(context)
    {}

    bool compile(cet::Unit const& unit)
    {
        utility::Owned<CET> cet = utility::makeOwned<CET>(reporter_);

        cet->visit(unit);

        (void) context_;    // todo: use or remove
        (void) source_tree_;// todo: use or remove

        return reporter_.isFailed();
    }

  private:
    sources::SourceTree& source_tree_;
    core::Reporter&      reporter_;
    core::Context&       context_;
};

ance::build::Compiler::Compiler(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
    : implementation_(utility::makeOwned<Implementation>(source_tree, reporter, context))
{}

ance::build::Compiler::~Compiler() = default;

bool ance::build::Compiler::compile(cet::Unit const& unit)
{
    return implementation_->compile(unit);
}
