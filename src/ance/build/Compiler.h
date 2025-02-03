#ifndef ANCE_BUILD_COMPILER_H
#define ANCE_BUILD_COMPILER_H

#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

namespace ance::build
{
  /**
   * Compiles CETs into binaries.
   */
  class Compiler
  {
  public:
    Compiler();
    ~Compiler();

  private:
    struct Implementation;
    utility::Owned<Implementation> implementation_;
  };
}

#endif
