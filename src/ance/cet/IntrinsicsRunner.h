#ifndef ANCE_CET_INTRINSICSRUNNER_H
#define ANCE_CET_INTRINSICSRUNNER_H

#include <filesystem>
#include <functional>

#include "ance/utility/Owners.h"

#include "ance/bbt/Value.h"
#include "ance/cet/Scope.h"
#include "ance/core/Intrinsic.h"

namespace ance::sources
{
    class SourceTree;
}

namespace ance::core
{
    class Reporter;
}

namespace ance::bbt
{
    class TypeContext;
}

namespace ance::cet
{
    /// A resolution which could not be completed, resulting in the run point being pending.
    struct PendingResolution
    {
        core::Identifier                                       identifier;
        std::variant<FindResult::NotFound, FindResult::Erased> reason;
    };

    class IntrinsicsRunner final
    {
      public:
        IntrinsicsRunner(sources::SourceTree&                              source_tree,
                         core::Reporter&                                   reporter,
                         bbt::TypeContext&                                 type_context,
                         std::function<void(std::filesystem::path const&)> include);

        ~IntrinsicsRunner();

        struct Result
        {
            utility::Optional<utility::Shared<bbt::Value const>> return_value_      = std::nullopt;
            utility::Optional<PendingResolution>           pending_resolution = std::nullopt;

            bool isPending() const;
            bool isFailed() const;

            [[nodiscard]] PendingResolution const&    getPending() const;
            [[nodiscard]] utility::Shared<bbt::Value const> getResult();
        };

        /// Run an intrinsic with the given arguments.
        Result run(core::Intrinsic const& intrinsic, utility::List<utility::Shared<bbt::Value const>>& arguments, core::Location const& location);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
