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

    // todo: do all the intermediate steps for the minimal grammar
    // todo: do the segmenter without any complex algorithm for now, simply put all statements in one BB
    // todo: when arrived at the compiler, add empty visitor there
    // todo: in the runner, simply print the identifiers to console
    // todo: then add the function registration to resolver and an intrinsic class instead of std::function
    // todo: then add an extended grammar with all statements and expressions

  private:
    struct Implementation;
    utility::Owned<Implementation> implementation_;
  };
}

#endif
