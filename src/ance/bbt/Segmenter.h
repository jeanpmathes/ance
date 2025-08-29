#ifndef ANCE_BBT_SEGMENTER_H
#define ANCE_BBT_SEGMENTER_H

#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

namespace ance::est
{
    struct Statement;
}

namespace ance::bbt
{
  struct Flow;

  /// Segments RETs into BBTs.
  class Segmenter
  {
  public:
    explicit Segmenter(core::Reporter& reporter);
    ~Segmenter();

    /// Segment a statement into a basic block control flow.
    /// \param statement The statement to segment.
    /// \return The control flow built from the statement.
    utility::Owned<Flow> segment(est::Statement const& statement);

  private:
    struct Implementation;
    utility::Owned<Implementation> implementation_;
  };
}

#endif
