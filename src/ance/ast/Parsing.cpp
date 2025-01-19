#include "Parsing.h"

#include <exception>

#include <ANTLRInputStream.h>

#include "anceBaseVisitor.h"
#include "anceLexer.h"
#include "anceParser.h"

#include "ance/sources/SourceFile.h"

#include "Node.h"

namespace ance
{
    class ErrorHandler
    {
      public:
        explicit ErrorHandler(core::Reporter& reporter, sources::SourceFile const& source_file)
            : reporter_(reporter)
            , source_file_(source_file)
        {}

      private:
        class LexerErrorListener : public antlr4::BaseErrorListener
        {
          public:
            explicit LexerErrorListener(ErrorHandler& parent) : parent_(parent) {}

            void syntaxError(antlr4::Recognizer*      recognizer,
                             antlr4::Token*           offending_symbol,
                             size_t const             line,
                             size_t const             char_position_in_line,
                             std::string const&       msg,
                             std::exception_ptr const e) override
            {
                (void) recognizer;// todo: remove
                (void) offending_symbol;
                (void) line;
                (void) char_position_in_line;
                (void) msg;
                (void) e;

                // todo: test some possible errors here
                // todo: if fitting, convert to useful error message and report

                throw std::logic_error("Error handling for lexer error not implemented: " + msg);
            }

            ErrorHandler& parent_;
        };

        class ParserErrorListener : public antlr4::BaseErrorListener
        {
          public:
            explicit ParserErrorListener(ErrorHandler& parent) : parent_(parent) {}

            void syntaxError(antlr4::Recognizer* recognizer,
                             antlr4::Token*      offending_symbol,
                             size_t              line,
                             size_t              char_position,
                             std::string const&  msg,
                             std::exception_ptr const) override
            {
                // todo: test some possible errors here
                // todo: if fitting, convert to useful error message and report

                auto* parser = dynamic_cast<anceParser*>(recognizer);
                if (!parser) return;

                char_position = parent_.source_file_.getUtf8Index(line, char_position);

                antlr4::Token* previous_symbol = parser->getTokenStream()->LT(-1);

                size_t previous_line          = line;
                size_t previous_char_position = char_position;

                if (previous_symbol)
                {
                    previous_line = previous_symbol->getLine();
                    previous_char_position =
                        parent_.source_file_.getUtf8Index(previous_line, previous_symbol->getCharPositionInLine())
                        + previous_symbol->getText().size();

                    if (offending_symbol->getType() == antlr4::Token::EOF)
                    {
                        offending_symbol = previous_symbol;

                        line          = previous_line;
                        char_position = previous_char_position;
                    }
                }

                if (offending_symbol->getType() == anceLexer::ERROR_CHAR)
                {
                    parent_.reporter_.error("Unexpected character",
                                            core::Location::simple(line, char_position, parent_.source_file_.index()));
                    return;
                }

                auto const expected_tokens = parser->getExpectedTokens();

                if (static_cast<size_t>(expected_tokens.getSingleElement()) == anceLexer::EOF)
                {
                    parent_.reporter_.error("Exactly one statement is allowed per file",
                                            core::Location::simple(line, char_position, parent_.source_file_.index()));
                    return;
                }

                if (static_cast<size_t>(expected_tokens.getSingleElement()) == anceLexer::SEMICOLON)
                {
                    parent_.reporter_.error("Missing semicolon",
                                            core::Location::simple(previous_line,
                                                                   previous_char_position + 1,
                                                                   parent_.source_file_.index()));
                    return;
                }

                if (expected_tokens.size() == 1)
                {
                    std::string const expected_text(parser->getVocabulary().getLiteralName(
                        static_cast<size_t>(expected_tokens.getSingleElement())));

                    parent_.reporter_.error("Expected " + expected_text + " somewhere around here",
                                            core::Location::simple(line, char_position, parent_.source_file_.index()));
                    return;
                }

                throw std::logic_error("Error handling for parser error not implemented: " + msg);
            }

            ErrorHandler& parent_;
        };

      public:
        antlr4::BaseErrorListener* lexerErrorListener() { return &lexer_error_listener_; }
        antlr4::BaseErrorListener* parserErrorListener() { return &parser_error_listener_; }

      private:
        LexerErrorListener  lexer_error_listener_ {*this};
        ParserErrorListener parser_error_listener_ {*this};

        core::Reporter&            reporter_;
        sources::SourceFile const& source_file_;
    };

    class SourceVisitor : public anceBaseVisitor
    {
        // todo: source locations in nodes

      public:
        std::any visitFile(anceParser::FileContext* context) override { return visit(context->statement()); }

        std::any visitBlockStatement(anceParser::BlockStatementContext* context) override
        {
            utility::List<utility::Owned<ast::Statement>> statements;

            for (anceParser::StatementContext* statement : context->statement())
            {
                statements.push_back(utility::wrap<ast::Statement>(visit(statement)));
            }

            ast::Statement* statement = new ast::Block(std::move(statements));
            return statement;
        }

        std::any visitExpressionStatement(anceParser::ExpressionStatementContext* context) override
        {
            utility::Owned<ast::Expression> expression = utility::wrap<ast::Expression>(visit(context->expression()));

            ast::Statement* statement = new ast::Independent(std::move(expression));
            return statement;
        }

        std::any visitCall(anceParser::CallContext*) override
        {
            ast::Expression* expression = new ast::Call();
            return expression;
        }
    };
}

struct ance::ast::Parsing::Implementation {
    explicit Implementation(core::Reporter& reporter) : reporter_(reporter) {}

    utility::Owned<Statement> parse(sources::SourceFile const& source_file)
    {
        std::fstream code;
        code.open(source_file.getRelativePath());

        utility::Owned<ErrorHandler> syntax_error_listener = utility::makeOwned<ErrorHandler>(reporter_, source_file);

        utility::Owned<antlr4::ANTLRInputStream> input = utility::makeOwned<antlr4::ANTLRInputStream>(code);
        utility::Owned<anceLexer>                lexer = utility::makeOwned<anceLexer>(input.get());
        lexer->removeErrorListeners();
        lexer->addErrorListener(syntax_error_listener->lexerErrorListener());

        utility::Owned<antlr4::CommonTokenStream> tokens = utility::makeOwned<antlr4::CommonTokenStream>(lexer.get());
        utility::Owned<anceParser>                parser = utility::makeOwned<anceParser>(tokens.get());
        parser->removeErrorListeners();
        parser->addErrorListener(syntax_error_listener->parserErrorListener());

        antlr4::tree::ParseTree* tree = parser->file();

        SourceVisitor visitor;
        return utility::wrap<Statement>(visitor.visit(tree));

        // todo: cause compiler errors (create a reporter class, should take source tree), should only be called in the listeners
        // todo: give source to reporter and emit the logs
        // todo: test out many cases to break the current simple grammar

        // todo: make the visitor fault tolerant - return error nodes
        // todo: it might be that the simple grammar does not have cases where error nodes are needed, try some stuff out
        // todo: when the grammar gets more complex, error nodes might be needed
    }

  private:
    core::Reporter& reporter_;
};

ance::ast::Parsing::Parsing(sources::SourceTree& source_tree, core::Reporter& reporter)
    : source_tree_(source_tree)
    , reporter_(reporter)
    , implementation_(utility::makeOwned<Implementation>(reporter))
{}

ance::ast::Parsing::~Parsing() = default;

ance::utility::Owned<ance::ast::Statement> ance::ast::Parsing::parse(size_t const index)
{
    return implementation_->parse(source_tree_.getFile(index));
}
