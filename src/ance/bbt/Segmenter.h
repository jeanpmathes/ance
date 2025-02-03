#ifndef ANCE_BBT_SEGMENTER_H
#define ANCE_BBT_SEGMENTER_H

#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

namespace ance::bbt
{
  /**
   * Segments RETs into BBTs.
   */
  class Segmenter
  {
  public:
    Segmenter();
    ~Segmenter();

  private:
    struct Implementation;
    utility::Owned<Implementation> implementation_;
  };
}

#endif
