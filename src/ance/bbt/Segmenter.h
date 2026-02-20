#ifndef ANCE_BBT_SEGMENTER_H
#define ANCE_BBT_SEGMENTER_H

#include <filesystem>

#include "ance/core/Context.h"
#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

#include "ance/bbt/Type.h"

namespace ance::sources
{
    class SourceTree;
}

namespace ance::bbt
{
    struct Flow;
    struct Flows;

    /// Segments RETs into BBTs.
    class Segmenter
    {
      public:
        Segmenter(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context, TypeContext& type_context);
        ~Segmenter();

        /// Segment an ordered file into a basic block control flow.
        /// \param file The path to the file to segment.
        /// \return The control flow built from the file.
        utility::Optional<utility::Owned<Flow>> segmentOrderedFile(std::filesystem::path const& file);

        /// Segment an unordered file into the set of flows it contains.
        /// \param file The path to the file to segment.
        /// \return The unordered scope built from the file.
        utility::Optional<utility::Owned<Flows>> segmentUnorderedFile(std::filesystem::path const& file);

        /// Segment a piece of core code containing a single declaration into a flow.
        /// \param code The code to segment.
        /// \param id An identifier of the declaration.
        /// \return The flow built from the code.
        utility::Optional<utility::Owned<Flow>> segmentDeclaration(std::string const& code, std::string const& id);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
