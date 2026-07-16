#include "SourceTest.h"

#include <algorithm>
#include <regex>
#include <span>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "ance/Program.h"

#include "TemporaryDirectory.h"

namespace
{
    class TestProject
    {
      public:
        TestProject() = default;

        TestProject(TestProject const&)            = delete;
        TestProject& operator=(TestProject const&) = delete;

        [[nodiscard]] std::filesystem::path getSourcePath() const
        {
            return directory_.root() / source_paths_.front();
        }

        [[nodiscard]] std::span<std::filesystem::path const> getSourcePaths() const
        {
            return source_paths_;
        }

        void addSource(std::filesystem::path const& relative_path, std::string_view const content)
        {
            std::filesystem::path const normalized_path = relative_path.lexically_normal();

            if (std::ranges::find(source_paths_, normalized_path) != source_paths_.end())
                throw std::invalid_argument("Duplicate test source path: " + normalized_path.generic_string());

            directory_.writeFile(normalized_path, content);
            source_paths_.push_back(normalized_path);
        }

      private:
        ance::test::TemporaryDirectory     directory_;
        std::vector<std::filesystem::path> source_paths_;
    };

    ance::core::Reporter::Level getLevel(std::string_view const level)
    {
        if (level == "trace") return ance::core::Reporter::Level::TRACE;
        if (level == "info") return ance::core::Reporter::Level::INFO;
        if (level == "warning") return ance::core::Reporter::Level::WARNING;
        if (level == "error") return ance::core::Reporter::Level::ERROR;

        throw std::invalid_argument("Unknown compiler output level: " + std::string(level));
    }

    bool isSourcePath(std::string_view const path, std::span<std::filesystem::path const> const source_paths)
    {
        return std::ranges::any_of(source_paths, [&](std::filesystem::path const& source_path) { return source_path.generic_string() == path; });
    }

    void parseCompilerOutput(ance::test::CompilerOutput& output, std::string const& message, std::span<std::filesystem::path const> const source_paths)
    {
        static std::regex const message_pattern {R"(^(?:((?:(.+) )?\((?:(\d+):(\d+))?\) ))?(.*)$)"};

        std::smatch match;

        if (std::regex_match(message, match, message_pattern))
        {
            bool const is_project_location = match[1].matched && !match[2].matched && !match[3].matched;
            bool const is_source_location  = match[1].matched && match[2].matched && isSourcePath(match[2].str(), source_paths);

            if (is_project_location || is_source_location)
            {
                ance::test::SourceLocation location;

                if (match[2].matched)
                {
                    location.relative_path = match[2].str();
                }

                if (match[3].matched)
                {
                    location.line   = std::stoull(match[3].str());
                    location.column = std::stoull(match[4].str());
                }

                output.location = location;
                output.content  = match[5].str();
            }
            else
            {
                output.content = message;
            }
        }
        else
        {
            throw std::invalid_argument("Invalid compiler output message: " + message);
        }
    }

    std::vector<ance::test::CompilerOutput> parseCompilerOutput(std::string const& output, std::span<std::filesystem::path const> const source_paths)
    {
        static std::regex const output_pattern {R"(^ance: (trace|info|warning|error): (.*)$)"};

        std::istringstream                      lines(output);
        std::vector<ance::test::CompilerOutput> compiler_output;
        std::string                             line;

        while (std::getline(lines, line))
        {
            if (line.ends_with('\r')) line.pop_back();

            std::smatch match;
            if (std::regex_match(line, match, output_pattern))
            {
                ance::test::CompilerOutput& entry = compiler_output.emplace_back();
                entry.level                       = getLevel(match[1].str());
                parseCompilerOutput(entry, match[2].str(), source_paths);
            }
        }

        return compiler_output;
    }
}

ance::test::SourceLocation ance::test::SourceLocation::inProject()
{
    return {};
}

ance::test::SourceLocation ance::test::SourceLocation::inFile(std::filesystem::path const& path)
{
    return {.relative_path = path};
}

ance::test::SourceLocation ance::test::SourceLocation::inPosition(std::filesystem::path const& path, size_t line, size_t column)
{
    return {.relative_path = path, .line = line, .column = column};
}

std::ostream& ance::test::operator<<(std::ostream& out, CompilerOutput const& output)
{
    out << "CompilerOutput{level=";

    switch (output.level)
    {
        case core::Reporter::Level::TRACE:
            out << "TRACE";
            break;
        case core::Reporter::Level::INFO:
            out << "INFO";
            break;
        case core::Reporter::Level::WARNING:
            out << "WARNING";
            break;
        case core::Reporter::Level::ERROR:
            out << "ERROR";
            break;
    }

    out << ", content=\"" << output.content << "\"";

    if (output.location.hasValue())
    {
        out << ", location=" << output.location.value();
    }

    out << "}";

    return out;
}

std::ostream& ance::test::operator<<(std::ostream& out, SourceLocation const& location)
{
    out << "SourceLocation{";

    if (location.relative_path.hasValue())
    {
        out << "path=\"" << location.relative_path.value().generic_string() << "\"";

        if (location.line.hasValue() || location.column.hasValue())
        {
            out << ", ";
        }
    }

    if (location.line.hasValue())
    {
        out << "line=" << location.line.value();

        if (location.column.hasValue())
        {
            out << ", ";
        }
    }

    if (location.column.hasValue())
    {
        out << "column=" << location.column.value();
    }

    out << "}";

    return out;
}

void ance::test::checkSource(std::string_view const source, Compilation const expected_compilation, std::initializer_list<CompilerOutput> const expected_output)
{
    checkSources(source, {}, expected_compilation, expected_output);
}

void ance::test::checkSources(std::string_view const                      source,
                              std::initializer_list<Source> const         additional_sources,
                              Compilation const                           expected_compilation,
                              std::initializer_list<CompilerOutput> const expected_output)
{
    TestProject project;
    project.addSource(MAIN_SOURCE_FILE, source);

    for (auto const& [relative_path, content] : additional_sources) project.addSource(relative_path, content);

    std::ostringstream program_output;
    std::ostringstream compiler_output;

    std::vector<std::string> arguments {"ance", "--no-color", project.getSourcePath().string()};
    std::vector<char*>       argument_pointers(arguments.size(), nullptr);
    std::ranges::transform(arguments, argument_pointers.begin(), [](std::string& argument) { return argument.data(); });

    int const exit_code = run(program_output, compiler_output, static_cast<int>(argument_pointers.size()), argument_pointers.data());

    std::vector<CompilerOutput> const actual_output = parseCompilerOutput(compiler_output.str(), project.getSourcePaths());
    std::vector const                 expected_output_vector(expected_output);
    bool const                        expected_success = expected_compilation == Compilation::SUCCESS;

    CAPTURE(program_output.str(), compiler_output.str());
    CHECK((exit_code == EXIT_SUCCESS) == expected_success);
    CHECK(actual_output == expected_output_vector);
}

void ance::test::checkSource(SourceTest const& test)
{
    checkSource(test.source, test.expected_compilation, test.expected_output);
}

void ance::test::checkSources(SourcesTest const& test)
{
    checkSources(test.source, test.additional_sources, test.expected_compilation, test.expected_output);
}
