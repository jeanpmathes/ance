#include <filesystem>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "ance/sources/SourceFile.h"
#include "ance/sources/SourceTree.h"

#include "TemporaryDirectory.h"

namespace ance::sources
{
    TEST_CASE("SourceTree assigns indices and retrieves files by index", "[unit]")
    {
        test::TemporaryDirectory directory;
        directory.writeFile("first.ance", "first");
        directory.writeFile(std::filesystem::path("nested") / "second.ance", "second");

        SourceTree tree(directory.root());

        SourceFile& first  = tree.addFile("first.ance");
        SourceFile& second = tree.addFile(std::filesystem::path("nested") / "second.ance");

        CHECK(first.index() == 0);
        CHECK(second.index() == 1);
        CHECK(&tree.getFile(0) == &first);
        CHECK(&tree.getFile(1) == &second);
    }

    TEST_CASE("SourceTree iterates files by reference in insertion order", "[unit]")
    {
        test::TemporaryDirectory directory;
        directory.writeFile("first.ance", "first");
        directory.writeFile("second.ance", "second");

        SourceTree tree(directory.root());

        SourceFile& first  = tree.addFile("first.ance");
        SourceFile& second = tree.addFile("second.ance");

        std::vector<SourceFile*> files;
        for (SourceFile& file : tree.getSourceFiles()) files.push_back(&file);

        REQUIRE(files.size() == 2);
        CHECK(files[0] == &first);
        CHECK(files[1] == &second);
    }
}
