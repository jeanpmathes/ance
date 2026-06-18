#include "SourceTree.h"

#include <future>
#include <utility>

ance::sources::SourceTree::SourceTree(std::filesystem::path base_directory) : base_directory_(std::move(base_directory))
{

}

ance::sources::SourceFile& ance::sources::SourceTree::addFile(std::filesystem::path const& file)
{
    return *source_files_.emplace_back(utility::makeOwned<SourceFile>(base_directory_, file, source_files_.size()));
}

ance::sources::SourceFile& ance::sources::SourceTree::getFile(size_t const index)
{
    return *source_files_[index];
}
