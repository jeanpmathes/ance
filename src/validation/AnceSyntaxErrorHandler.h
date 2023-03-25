#ifndef ANCE_SRC_VALIDATION_ANCESYNTAXERRORHANDLER_H_
#define ANCE_SRC_VALIDATION_ANCESYNTAXERRORHANDLER_H_

#include <antlr4-runtime.h>

class SourceFile;

class AnceSyntaxErrorHandler
{
  private:
    class LexerErrorListener : public antlr4::BaseErrorListener
    {
      public:
        explicit LexerErrorListener(AnceSyntaxErrorHandler& parent);

        void syntaxError(antlr4::Recognizer* recognizer,
                         antlr4::Token*      offending_symbol,
                         size_t              line,
                         size_t              char_position_in_line,
                         std::string const&  msg,
                         std::exception_ptr  e) override;

        AnceSyntaxErrorHandler& parent_;

      private:
        std::pair<size_t, size_t> previous_position_ {0, 0};
    };

    class ParserErrorListener : public antlr4::BaseErrorListener
    {
      public:
        explicit ParserErrorListener(AnceSyntaxErrorHandler& parent);

        void syntaxError(antlr4::Recognizer* recognizer,
                         antlr4::Token*      offending_symbol,
                         size_t              line,
                         size_t              char_position_in_line,
                         std::string const&  msg,
                         std::exception_ptr  e) override;

        AnceSyntaxErrorHandler& parent_;
    };

  public:
    antlr4::BaseErrorListener* lexerErrorListener();
    antlr4::BaseErrorListener* parserErrorListener();

  private:
    void log(std::string const& message, size_t line, size_t char_position);

  public:
    /**
     * Create a new syntax error handler.
     * @param source_file The source file that is being parsed.
     */
    explicit AnceSyntaxErrorHandler(SourceFile const& source_file);

    /**
     * Emit all messages describing found syntax errors.
     */
    void emitMessages(std::ostream& stream);

    /**
     * Get the number of fatal syntax errors. Visiting the parse tree is not safe if fatal syntax errors occured.
     * @return The number of fatal syntax errors.
     */
    [[nodiscard]] size_t fatalSyntaxErrorCount() const;

  private:
    SourceFile const& source_file_;

    LexerErrorListener  lexer_error_listener_ {*this};
    ParserErrorListener parser_error_listener_ {*this};

    size_t fatal_error_count_ {0};

    std::vector<std::pair<std::string, std::pair<size_t, size_t>>> syntax_errors_;
};

#endif
