#include <filesystem>

#include <catch2/catch_test_macros.hpp>

#include "ance/sources/SourceFile.h"

#include "TemporaryDirectory.h"

namespace ance::sources
{
    TEST_CASE("SourceFile reads UTF-8 content as UTF-32 lines", "[unit]")
    {
        test::TemporaryDirectory    directory;
        std::filesystem::path const relative_path = std::filesystem::path("nested") / "source.ance";

        directory.writeFile(relative_path, "first\nAB😂ö");

        SourceFile const source(directory.root(), relative_path, 3);

        REQUIRE(source.isOk());
        CHECK(source.getLine(1) == U"first");
        CHECK(source.getLine(2) == U"AB😂ö");
    }

    TEST_CASE("SourceFile returns inclusive line slices", "[unit]")
    {
        test::TemporaryDirectory directory;
        directory.writeFile("source.ance", "abcdef");

        SourceFile const source(directory.root(), "source.ance", 0);

        REQUIRE(source.isOk());
        CHECK(source.getLineSlice(1, 2, 4) == U"bcd");
    }

    TEST_CASE("SourceFile exposes its path and index metadata", "[unit]")
    {
        test::TemporaryDirectory    directory;
        std::filesystem::path const relative_path = std::filesystem::path("nested") / "source.ance";
        directory.writeFile(relative_path, "source");

        SourceFile const source(directory.root(), relative_path, 9);

        CHECK(source.getRelativePath() == relative_path);
        CHECK(source.getAbsolutePath() == std::filesystem::absolute(directory.root() / relative_path));
        CHECK(source.getDirectory() == "nested");
        CHECK(source.getFilename() == "source.ance");
        CHECK(source.index() == 9);
    }

    TEST_CASE("SourceFile reports an unsuccessful read", "[unit]")
    {
        test::TemporaryDirectory const directory;

        SourceFile const source(directory.root(), "missing.ance", 0);

        CHECK_FALSE(source.isOk());
    }
}
