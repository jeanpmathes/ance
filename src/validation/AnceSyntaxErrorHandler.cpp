#include "AnceSyntaxErrorHandler.h"

#include "validation/Strings.h"

#include "grammar/anceLexer.h"
#include "grammar/anceParser.h"

AnceSyntaxErrorHandler::LexerErrorListener::LexerErrorListener(AnceSyntaxErrorHandler& parent) : parent_(parent) {}

void AnceSyntaxErrorHandler::LexerErrorListener::syntaxError(antlr4::Recognizer*,
                                                             antlr4::Token*,
                                                             size_t line,
                                                             size_t char_position_in_line,
                                                             const std::string&,
                                                             std::exception_ptr)
{
    auto [previous_line, previous_column] = previous_position_;
    previous_position_                    = std::make_pair(line, char_position_in_line + 1);

    bool continuing_previous_error = (line == previous_line && char_position_in_line == previous_column);
    if (continuing_previous_error && previous_column != 0) return;

    parent_.log("Cannot recognize tokens", line, char_position_in_line);
}

AnceSyntaxErrorHandler::ParserErrorListener::ParserErrorListener(AnceSyntaxErrorHandler& parent) : parent_(parent) {}

void AnceSyntaxErrorHandler::ParserErrorListener::syntaxError(antlr4::Recognizer* recognizer,
                                                              antlr4::Token*      offending_symbol,
                                                              size_t              line,
                                                              size_t              char_position_in_line,
                                                              const std::string&,
                                                              std::exception_ptr)
{
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
        previous_line          = previous_symbol->getLine();
        previous_char_position = previous_symbol->getCharPositionInLine() + previous_symbol->getText().size();
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

void AnceSyntaxErrorHandler::log(const std::string& message, size_t line, size_t char_position)
{
    syntax_errors_.emplace_back(message, std::make_pair(line, char_position));
}

void AnceSyntaxErrorHandler::emitMessages(const SourceFile& source_file)
{
    for (auto& [message, location] : syntax_errors_)
    {
        auto& [line, char_position] = location;
        size_t column               = char_position + 1;

        unsigned int start;

        std::cout << "ance-c: syntax: (" << line << ", " << column << ") " << message << std::endl;
        std::cout << '\t' << trim(source_file.getLine(line), start) << std::endl;

        unsigned int marker_position = column - start - 1;

        std::cout << '\t' << std::string(marker_position, ' ') << '^' << std::endl;
    }
}

size_t AnceSyntaxErrorHandler::fatalSyntaxErrorCount() const
{
    return fatal_error_count_;
}
