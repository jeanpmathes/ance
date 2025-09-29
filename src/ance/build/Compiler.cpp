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

        void visit(cet::BasicBlock const& basic_block) override
        {
            (void) basic_block;// todo: implement
        }

        void visit(cet::Return const& return_link) override
        {
            (void) return_link;// todo: implement
        }

        void visit(cet::Branch const& branch_link) override
        {
            (void) branch_link;// todo: implement
        }

        void visit(cet::Jump const& jump_link) override
        {
            (void) jump_link;// todo: implement
        }

        void visit(cet::Declare const& declare) override
        {
            (void) declare;// todo: implement
        }

        void visit(cet::Store const& store) override
        {
            (void) store;// todo: implement
        }

        void visit(cet::Temporary const& temporary) override
        {
            (void) temporary;// todo: implement
        }

        void visit(cet::CopyTemporary const& write_temporary) override
        {
            (void) write_temporary;// todo: implement
        }

        void visit(cet::Intrinsic const& intrinsic) override
        {
            intrinsics_.run(intrinsic.intrinsic, intrinsic.location);
        }

        void visit(cet::Call const& call) override
        {
            (void) call;// todo: implement
        }

        void visit(cet::Read const& read) override
        {
            (void) read;// todo: implement
        }

        void visit(cet::Constant const& constant) override
        {
            (void) constant;// todo: implement
        }

        void visit(cet::UnaryOperation const& unary_operation) override
        {
            (void) unary_operation;// todo: implement
        }

      private:
        core::Reporter& reporter_;

        Intrinsics intrinsics_ {reporter_};
    };

    explicit Implementation(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context) : source_tree_(source_tree), reporter_(reporter), context_(context) {}

    bool compile(cet::Unit const& unit, std::ostream& out)
    {
        utility::Owned<CET> cet = utility::makeOwned<CET>(reporter_);

        cet->visit(unit);

        (void) context_; // todo: use or remove

        return reporter_.checkForFail(source_tree_, out);
    }

private:
    sources::SourceTree& source_tree_;
    core::Reporter& reporter_;
    core::Context& context_;
};

ance::build::Compiler::Compiler(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context) : implementation_(utility::makeOwned<Implementation>(source_tree, reporter, context)) {}

ance::build::Compiler::~Compiler() = default;

bool ance::build::Compiler::compile(cet::Unit const& unit, std::ostream& out)
{
    return implementation_->compile(unit, out);
}
