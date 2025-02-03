#ifndef ANCE_EST_EXPANDER_H
#define ANCE_EST_EXPANDER_H

#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

namespace ance::ret
{
  /**
   * Resolves ESTs into RETs.
   */
  class Resolver
  {
  public:
    Resolver();
    ~Resolver();

  private:
    struct Implementation;
    utility::Owned<Implementation> implementation_;
  };
}

#endif
