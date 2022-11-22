#include "AnceSyntaxErrorHandler.h"

#include "grammar/anceLexer.h"
#include "grammar/anceParser.h"
#include "validation/ANSI.h"
#include "validation/SourceFile.h"
#include "validation/Strings.h"

AnceSyntaxErrorHandler::LexerErrorListener::LexerErrorListener(AnceSyntaxErrorHandler& parent) : parent_(parent) {}

void AnceSyntaxErrorHandler::LexerErrorListener::syntaxError(antlr4::Recognizer*,
                                                             antlr4::Token*,
                                                             size_t line,
                                                             size_t char_position_in_line,
                                                             std::string const&,
                                                             std::exception_ptr)
{
    auto [previous_line, previous_column] = previous_position_;
    previous_position_                    = std::make_pair(line, char_position_in_line + 1);

    bool continuing_previous_error = (line == previous_line && char_position_in_line == previous_column);
    if (continuing_previous_error && previous_column != 0) return;

    parent_.log("Cannot recognize tokens", line, char_position_in_line);
    parent_.fatal_error_count_++;
}

AnceSyntaxErrorHandler::ParserErrorListener::ParserErrorListener(AnceSyntaxErrorHandler& parent) : parent_(parent) {}

void AnceSyntaxErrorHandler::ParserErrorListener::syntaxError(antlr4::Recognizer* recognizer,
                                                              antlr4::Token*      offending_symbol,
                                                              size_t              line,
                                                              size_t              char_position_in_line,
                                                              std::string const&,
                                                              std::exception_ptr)
{
    char_position_in_line = parent_.source_file_.getUtf8Index(line, char_position_in_line);

    auto* parser = dynamic_cast<anceParser*>(recognizer);
    if (!parser) return;

    antlr4::Token* previous_symbol = parser->getTokenStream()->LT(-1);

    if (offending_symbol->getType() == antlr4::Token::EOF)
    {
        if (previous_symbol) offending_symbol = previous_symbol;
    }

    auto expected_tokens = parser->getExpectedTokens();
    auto expected        = expected_tokens.getSingleElement();

    size_t previous_line          = line;
    size_t previous_char_position = char_position_in_line;

    if (previous_symbol)
    {
        previous_line = previous_symbol->getLine();
        previous_char_position =
            parent_.source_file_.getUtf8Index(previous_line, previous_symbol->getCharPositionInLine())
            + previous_symbol->getText().size();
    }

    if (offending_symbol->getType() == anceLexer::ERROR_CHAR)
    {
        parent_.log("Unexpected character", line, char_position_in_line);
        return;
    }

    if (expected == anceLexer::SEMICOLON)
    {
        parent_.log("Expected ';' here", previous_line, previous_char_position);
        return;
    }

    parent_.log("Cannot understand code", line, char_position_in_line);
    parent_.fatal_error_count_++;
}

antlr4::BaseErrorListener* AnceSyntaxErrorHandler::lexerErrorListener()
{
    return &lexer_error_listener_;
}

antlr4::BaseErrorListener* AnceSyntaxErrorHandler::parserErrorListener()
{
    return &parser_error_listener_;
}

AnceSyntaxErrorHandler::AnceSyntaxErrorHandler(SourceFile const& source_file) : source_file_(source_file) {}

void AnceSyntaxErrorHandler::log(std::string const& message, size_t line, size_t char_position)
{
    syntax_errors_.emplace_back(message, std::make_pair(line, char_position));
}

void AnceSyntaxErrorHandler::emitMessages()
{
    for (auto& [message, location] : syntax_errors_)
    {
        auto& [line, char_position] = location;
        size_t column               = char_position + 1;

        size_t start;

        std::cout << "ance: " << ansi::ColorRed << "syntax" << ansi::ColorReset;
        std::cout << ": " << source_file_.getRelativePath().generic_string() << " ";
        std::cout << "(" << line << ", " << column << ") ";
        std::cout << message << std::endl;

        std::cout << std::endl;

        std::string_view line_view = trim(source_file_.getLine(line), start);

        std::cout << '\t' << line_view << std::endl;

        std::string_view text_to_mark    = line_view.substr(0, column - start - 1);
        size_t           marker_position = estimateWidth(text_to_mark);

        std::cout << '\t' << std::string(marker_position, ' ') << '^' << std::endl;
        std::cout << std::endl;
    }
}

size_t AnceSyntaxErrorHandler::fatalSyntaxErrorCount() const
{
    return fatal_error_count_;
}
