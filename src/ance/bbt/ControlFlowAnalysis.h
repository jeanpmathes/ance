#ifndef ANCE_BBT_CONTROL_FLOW_ANALYSIS_H
#define ANCE_BBT_CONTROL_FLOW_ANALYSIS_H

#include <functional>

#include "ance/core/Occurrence.h"
#include "ance/utility/Containers.h"
#include "ance/utility/Owners.h"

namespace ance::bbt
{
    struct BasicBlock;
    struct Flow;
    struct Statement;

    /// Analyzes occurrence counts across paths of a control flow.
    class ControlFlowAnalysis
    {
      public:
        using CounterFunction = std::function<size_t(Statement const&)>;

        explicit ControlFlowAnalysis(CounterFunction counter);

        /// The occurrence of the counts of the counter on all (ending) paths.
        [[nodiscard]] core::Occurrence analyze(
            utility::List<utility::Owned<BasicBlock>> const& blocks,
            BasicBlock const&                                entry
        ) const;

        /// The occurrence of the counts of the counter on all (ending) paths.
        [[nodiscard]] core::Occurrence analyze(Flow const& flow) const;

      private:
        CounterFunction counter_;
    };
}

#endif
