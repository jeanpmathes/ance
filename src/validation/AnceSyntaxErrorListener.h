#ifndef ANCE_SRC_VALIDATION_ANCESYNTAXERRORLISTENER_H_
#define ANCE_SRC_VALIDATION_ANCESYNTAXERRORLISTENER_H_

#include <antlr4-runtime.h>

#include "validation/SourceFile.h"

class AnceSyntaxErrorListener
{
  private:
    class LexerErrorListener : public antlr4::BaseErrorListener
    {
      public:
        explicit LexerErrorListener(AnceSyntaxErrorListener& parent);

        void syntaxError(antlr4::Recognizer* recognizer,
                         antlr4::Token*      offending_symbol,
                         size_t              line,
                         size_t              char_position_in_line,
                         const std::string&  msg,
                         std::exception_ptr  e) override;

        AnceSyntaxErrorListener& parent_;

      private:
        std::pair<size_t, size_t> previous_position_ {0, 0};
    };

    class ParserErrorListener : public antlr4::BaseErrorListener
    {
      public:
        explicit ParserErrorListener(AnceSyntaxErrorListener& parent);

        void syntaxError(antlr4::Recognizer* recognizer,
                         antlr4::Token*      offending_symbol,
                         size_t              line,
                         size_t              char_position_in_line,
                         const std::string&  msg,
                         std::exception_ptr  e) override;

        AnceSyntaxErrorListener& parent_;
    };

  public:
    antlr4::BaseErrorListener* lexerErrorListener();
    antlr4::BaseErrorListener* parserErrorListener();

  private:
    void log(const std::string& message, size_t line, size_t char_position);

  public:
    /**
     * Emit all messages describing found syntax errors.
     * @param source_file The source file that was validated.
     */
    void emitMessages(const SourceFile& source_file);

  private:
    LexerErrorListener  lexer_error_listener_ {*this};
    ParserErrorListener parser_error_listener_ {*this};

    std::vector<std::pair<std::string, std::pair<size_t, size_t>>> syntax_errors_;
};

#endif
