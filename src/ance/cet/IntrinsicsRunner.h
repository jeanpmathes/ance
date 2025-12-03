#ifndef ANCE_CET_INTRINSICSRUNNER_H
#define ANCE_CET_INTRINSICSRUNNER_H

#include <functional>

#include "ance/core/Intrinsic.h"
#include "ance/core/Reporter.h"

#include "ance/sources/SourceTree.h"

#include "ance/bbt/Value.h"

#include "ance/cet/Scope.h"

namespace ance::cet
{
    /// A resolution which could not be completed, resulting in the run point being pending.
    struct PendingResolution
    {
        core::Identifier identifier;
    };

    class IntrinsicsRunner final : core::IntrinsicVisitor
    {
      public:
        using IntrinsicVisitor::visit;

        IntrinsicsRunner(sources::SourceTree& source_tree, core::Reporter& reporter, std::function<void(std::filesystem::path const&)> include);

        struct Result
        {
            utility::Optional<utility::Shared<bbt::Value>> return_value_      = std::nullopt;
            utility::Optional<PendingResolution>           pending_resolution = std::nullopt;

            bool isPending() const;
            bool isFailed() const;

            [[nodiscard]] PendingResolution const&    getPending() const;
            [[nodiscard]] utility::Shared<bbt::Value> getResult();
        };

        /// Run an intrinsic with the given arguments.
        Result run(core::Intrinsic const& intrinsic, utility::List<utility::Shared<bbt::Value>> & arguments, core::Location const& location);

        void visit(core::Dynamic const& dynamic) override;
        void visit(core::NoOp const&) override;
        void visit(core::Declare const&) override;
        void visit(core::Resolve const&) override;
        void visit(core::GetParent const&) override;
        void visit(core::Log const&) override;
        void visit(core::B2Str const&) override;
        void visit(core::Include const&) override;

      private:
        void setResult(utility::Shared<bbt::Value> value);
        void setPending(core::Identifier const& identifier);

        void abort();

        sources::SourceTree& source_tree_;
        core::Reporter&      reporter_;

        std::function<void(std::filesystem::path const&)> include_;

        struct State
        {
            core::Location                                location             = core::Location::global();
            utility::List<utility::Shared<bbt::Value>>*   arguments            = nullptr;
            utility::Optional<utility::Shared<bbt::Type>> expected_return_type = std::nullopt;

            utility::Optional<utility::Shared<bbt::Value>> return_value_      = std::nullopt;
            utility::Optional<PendingResolution>           pending_resolution = std::nullopt;
        };

        State state_;
    };
}

#endif
