#include "AnceSyntaxErrorListener.h"

#include "validation/Strings.h"

AnceSyntaxErrorListener::LexerErrorListener::LexerErrorListener(AnceSyntaxErrorListener& parent) : parent_(parent) {}

void AnceSyntaxErrorListener::LexerErrorListener::syntaxError(antlr4::Recognizer* recognizer,
                                                              antlr4::Token*      offending_symbol,
                                                              size_t              line,
                                                              size_t              char_position_in_line,
                                                              const std::string&  msg,
                                                              std::exception_ptr  e)
{
    auto [previous_line, previous_column] = previous_position_;
    previous_position_                    = std::make_pair(line, char_position_in_line + 1);

    bool continuing_previous_error = (line == previous_line && char_position_in_line == previous_column);
    if (continuing_previous_error && previous_column != 0) return;

    parent_.log("Cannot recognize tokens", line, char_position_in_line);
}

AnceSyntaxErrorListener::ParserErrorListener::ParserErrorListener(AnceSyntaxErrorListener& parent) : parent_(parent) {}

void AnceSyntaxErrorListener::ParserErrorListener::syntaxError(antlr4::Recognizer* recognizer,
                                                               antlr4::Token*      offending_symbol,
                                                               size_t              line,
                                                               size_t              char_position_in_line,
                                                               const std::string&  msg,
                                                               std::exception_ptr  e)
{
    parent_.log("Cannot understand code", line, char_position_in_line);
}

antlr4::BaseErrorListener* AnceSyntaxErrorListener::lexerErrorListener()
{
    return &lexer_error_listener_;
}

antlr4::BaseErrorListener* AnceSyntaxErrorListener::parserErrorListener()
{
    return &parser_error_listener_;
}

void AnceSyntaxErrorListener::log(const std::string& message, size_t line, size_t char_position)
{
    syntax_errors_.emplace_back(message, std::make_pair(line, char_position));
}

void AnceSyntaxErrorListener::emitMessages(const SourceFile& source_file)
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
