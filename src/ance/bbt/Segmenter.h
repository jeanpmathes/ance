#ifndef ANCE_BBT_SEGMENTER_H
#define ANCE_BBT_SEGMENTER_H

#include <filesystem>

#include "ance/core/Context.h"
#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

namespace ance::sources
{
    class SourceTree;
}

namespace ance::bbt
{
  struct Flow;

  /// Segments RETs into BBTs.
  class Segmenter
  {
  public:
    Segmenter(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context);
    ~Segmenter();

    /// Segment a file into a basic block control flow.
    /// \param file The path to the file to segment.
    /// \param out The output stream to report to.
    /// \return The control flow built from the file.
    utility::Optional<utility::Owned<Flow>> segment(std::filesystem::path const& file, std::ostream& out);

  private:
    struct Implementation;
    utility::Owned<Implementation> implementation_;
  };
}

#endif
