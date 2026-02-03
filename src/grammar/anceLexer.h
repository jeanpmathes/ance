
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1

#pragma once

#include "antlr4-runtime.h"

class anceLexer : public antlr4::Lexer
{
  public:
    enum
    {
        T__0                 = 1,
        T__1                 = 2,
        T__2                 = 3,
        T__3                 = 4,
        T__4                 = 5,
        T__5                 = 6,
        T__6                 = 7,
        T__7                 = 8,
        T__8                 = 9,
        T__9                 = 10,
        T__10                = 11,
        T__11                = 12,
        T__12                = 13,
        T__13                = 14,
        T__14                = 15,
        T__15                = 16,
        T__16                = 17,
        T__17                = 18,
        T__18                = 19,
        T__19                = 20,
        T__20                = 21,
        T__21                = 22,
        T__22                = 23,
        IDENTIFIER           = 24,
        INTEGER              = 25,
        STRING               = 26,
        LAMBDA               = 27,
        SEMICOLON            = 28,
        WHITESPACE           = 29,
        BLOCK_COMMENT        = 30,
        LINE_COMMENT         = 31,
        BRACKET_OPEN         = 32,
        BRACKET_CLOSE        = 33,
        CURLY_BRACKET_OPEN   = 34,
        CURLY_BRACKET_CLOSE  = 35,
        SQUARE_BRACKET_OPEN  = 36,
        SQUARE_BRACKET_CLOSE = 37,
        POINTY_BRACKET_OPEN  = 38,
        POINTY_BRACKET_CLOSE = 39,
        ERROR_CHAR           = 40
    };

    explicit anceLexer(antlr4::CharStream* input);

    ~anceLexer() override;

    std::string getGrammarFileName() const override;

    std::vector<std::string> const& getRuleNames() const override;

    std::vector<std::string> const& getChannelNames() const override;

    std::vector<std::string> const& getModeNames() const override;

    antlr4::dfa::Vocabulary const& getVocabulary() const override;

    antlr4::atn::SerializedATNView getSerializedATN() const override;

    antlr4::atn::ATN const& getATN() const override;

    // By default the static state used to implement the lexer is lazily initialized during the first
    // call to the constructor. You can call this function if you wish to initialize the static state
    // ahead of time.
    static void initialize();

  private:
    // Individual action functions triggered by action() above.

    // Individual semantic predicate functions triggered by sempred() above.
};
