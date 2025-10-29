#include "Compiler.h"

#include "ance/core/Intrinsic.h"

#include "ance/cet/Node.h"

struct ance::build::Compiler::Implementation
{
    class Intrinsics final : core::IntrinsicVisitor
    {
    public:
        using IntrinsicVisitor::visit;

        explicit Intrinsics(core::Reporter& reporter) : reporter_(reporter) {}

        void run(core::Intrinsic const& intrinsic, core::Location const& location)
        {
            location_ = location;

            this->visit(intrinsic);

            location_ = core::Location::global();
        }

        void unsupported(core::Intrinsic const& intrinsic) const
        {
            reporter_.error("Unsupported intrinsic '" + intrinsic.identifier() + "'", location_);
        }

        void visit(core::Dynamic const& dynamic) override
        {
            unsupported(dynamic);
        }

        void visit(core::NoOp const&) override
        {
            // Do nothing.
        }

        void visit(core::Declare const& declare) override
        {
            unsupported(declare);
        }

        void visit(core::Resolve const& resolve) override
        {
            unsupported(resolve);
        }

        void visit(core::GetParent const& get_parent) override
        {
            unsupported(get_parent);
        }

        void visit(core::Log const& log) override
        {
            unsupported(log);
        }

        void visit(core::Include const& include) override
        {
            unsupported(include);
        }

        void visit(core::B2Str const& b2str) override
        {
            unsupported(b2str);
        }

    private:
        core::Reporter& reporter_;

        core::Location location_ = core::Location::global();
    };

    class CET final : public cet::Visitor
    {
    public:
        using Visitor::visit;

        explicit CET(core::Reporter& reporter) : reporter_(reporter) {}
        ~CET() override = default;

        void visit(cet::Unit const& unit) override
        {
            (void) unit;// todo: implement
        }

      private:
        core::Reporter& reporter_;

        Intrinsics intrinsics_ {reporter_};
    };

    explicit Implementation(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context) : source_tree_(source_tree), reporter_(reporter), context_(context) {}

    bool compile(cet::Unit const& unit)
    {
        utility::Owned<CET> cet = utility::makeOwned<CET>(reporter_);

        cet->visit(unit);

        (void) context_; // todo: use or remove
        (void) source_tree_; // todo: use or remove

        return reporter_.isFailed();
    }

private:
    sources::SourceTree& source_tree_;
    core::Reporter& reporter_;
    core::Context& context_;
};

ance::build::Compiler::Compiler(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context) : implementation_(utility::makeOwned<Implementation>(source_tree, reporter, context)) {}

ance::build::Compiler::~Compiler() = default;

bool ance::build::Compiler::compile(cet::Unit const& unit)
{
    return implementation_->compile(unit);
}
