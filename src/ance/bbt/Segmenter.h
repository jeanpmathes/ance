#ifndef ANCE_BBT_SEGMENTER_H
#define ANCE_BBT_SEGMENTER_H

#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

namespace ance::ret
{
    struct Statement;
}

namespace ance::bbt
{
  struct BasicBlock;

  /// Segments RETs into BBTs.
  class Segmenter
  {
  public:
    explicit Segmenter(core::Reporter& reporter);
    ~Segmenter();

    /// Segment a statement into a basic block.
    /// \param statement The statement to segment.
    /// \return The basic block.
    utility::Owned<BasicBlock> segment(ret::Statement const& statement);

    // todo: think how to do simplification here, maybe internal bb representation first with mutable state
    // todo: then run simplify on that like in old implementation, only then return the bb nodes

  private:
    struct Implementation;
    utility::Owned<Implementation> implementation_;
  };
}

#endif
