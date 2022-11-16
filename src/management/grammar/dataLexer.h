
// Generated from ./src/management/grammar/data.g4 by ANTLR 4.10.1

#pragma once

#include "antlr4-runtime.h"

class dataLexer : public antlr4::Lexer
{
  public:
    enum
    {
        T__0         = 1,
        T__1         = 2,
        T__2         = 3,
        T__3         = 4,
        T__4         = 5,
        T__5         = 6,
        T__6         = 7,
        T__7         = 8,
        KEY          = 9,
        STRING       = 10,
        WHITESPACE   = 11,
        LINE_COMMENT = 12
    };

    explicit dataLexer(antlr4::CharStream* input);

    ~dataLexer() override;

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

