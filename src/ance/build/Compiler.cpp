#include "Compiler.h"

#include "ance/cet/Node.h"
#include "ance/cet/Runner.h"
#include "ance/cet/LanguageCore.h"

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
        , runner_(source_tree, reporter, context)
    {
        cet::defineLanguageCore(runner_);
    }

    bool compile(std::filesystem::path const& file)
    {
        utility::Optional<utility::Owned<cet::Unit>> unit = runner_.runOrderedFile(file);

        if (!unit.hasValue()) return false;

        utility::Owned<CET> cet = utility::makeOwned<CET>(reporter_);

        cet->visit(**unit);

        (void) context_;    // todo: use or remove
        (void) source_tree_;// todo: use or remove

        bool const ok = !reporter_.isFailed();

        return ok;
    }

  private:
    sources::SourceTree& source_tree_;
    core::Reporter&      reporter_;
    core::Context&       context_;

    cet::Runner runner_;
};

ance::build::Compiler::Compiler(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context)
    : implementation_(utility::makeOwned<Implementation>(source_tree, reporter, context))
{}

ance::build::Compiler::~Compiler() = default;

bool ance::build::Compiler::compile(std::filesystem::path const& file)
{
    return implementation_->compile(file);
}
