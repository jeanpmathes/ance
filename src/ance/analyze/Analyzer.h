#ifndef ANCE_ANALYZE_ANALYZER_H
#define ANCE_ANALYZE_ANALYZER_H

#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

namespace ance::ret
{
    struct Statement;
}

namespace ance::analyze
{
    /// Analyzes the RET for semantic correctness.
    class Analyzer
    {
    public:
      explicit Analyzer(core::Reporter& reporter);
      ~Analyzer();

      /// Analyze a statement.
      /// \param statement The statement to analyze.
      void analyze(ret::Statement const& statement);

    private:
      struct Implementation;
      utility::Owned<Implementation> implementation_;
    };
}

#endif
