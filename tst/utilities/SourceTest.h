#ifndef ANCE_TST_UTILITIES_SOURCETEST_H
#define ANCE_TST_UTILITIES_SOURCETEST_H

#include <filesystem>
#include <initializer_list>
#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>

#include "ance/core/Reporter.h"

namespace ance::test
{
    static constexpr auto MAIN_SOURCE_FILE = "test.ance";

    enum class Compilation
    {
        SUCCESS,
        FAILURE
    };

    struct Source
    {
        std::filesystem::path relative_path;
        std::string           content;
    };

    struct SourceLocation
    {
        utility::Optional<std::filesystem::path> relative_path = std::nullopt;
        utility::Optional<size_t>                line          = std::nullopt;
        utility::Optional<size_t>                column        = std::nullopt;

        static SourceLocation inProject();
        static SourceLocation inFile(std::filesystem::path const& path);
        static SourceLocation inPosition(std::filesystem::path const& path, size_t line, size_t column);

        bool operator==(SourceLocation const&) const = default;
    };

    struct CompilerOutput
    {
        core::Reporter::Level             level;
        std::string                       content;
        utility::Optional<SourceLocation> location = std::nullopt;

        bool operator==(CompilerOutput const&) const = default;
    };

    std::ostream& operator<<(std::ostream& out, CompilerOutput const& output);
    std::ostream& operator<<(std::ostream& out, SourceLocation const& location);

    /// Compile source code and check whether the compilation result and compiler output match the expected values.
    /// \param source The only source code; will be considered as a top-level source file.
    /// \param expected_compilation The expected compilation result.
    /// \param expected_output The expected compiler output.
    void checkSource(std::string_view source, Compilation expected_compilation, std::initializer_list<CompilerOutput> expected_output);

    /// Compile source code and check whether the compilation result and compiler output match the expected values.
    /// \param source The entry source code. It will be considered as a top-level source file.
    /// \param additional_sources Will be made available as additional files during compilation. The entry source code needs to include them first.
    /// \param expected_compilation The expected compilation result.
    /// \param expected_output The expected compiler output.
    void checkSources(std::string_view                      source,
                      std::initializer_list<Source>         additional_sources,
                      Compilation                           expected_compilation,
                      std::initializer_list<CompilerOutput> expected_output);

    struct SourceTest
    {
        std::string_view                      source;
        Compilation                           expected_compilation;
        std::initializer_list<CompilerOutput> expected_output;
    };

    void checkSource(SourceTest const& test);

    struct SourcesTest
    {
        std::string_view                      source;
        std::initializer_list<Source>         additional_sources;
        Compilation                           expected_compilation;
        std::initializer_list<CompilerOutput> expected_output;
    };

    void checkSources(SourcesTest const& test);
}

#endif
