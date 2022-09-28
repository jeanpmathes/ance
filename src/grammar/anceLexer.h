
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1

#pragma once

#include "antlr4-runtime.h"

class anceLexer : public antlr4::Lexer
{
  public:
    enum
    {
        T__0                = 1,
        T__1                = 2,
        T__2                = 3,
        T__3                = 4,
        T__4                = 5,
        T__5                = 6,
        T__6                = 7,
        T__7                = 8,
        T__8                = 9,
        T__9                = 10,
        T__10               = 11,
        T__11               = 12,
        T__12               = 13,
        T__13               = 14,
        T__14               = 15,
        T__15               = 16,
        T__16               = 17,
        T__17               = 18,
        T__18               = 19,
        T__19               = 20,
        T__20               = 21,
        T__21               = 22,
        T__22               = 23,
        T__23               = 24,
        T__24               = 25,
        T__25               = 26,
        T__26               = 27,
        T__27               = 28,
        T__28               = 29,
        T__29               = 30,
        T__30               = 31,
        T__31               = 32,
        T__32               = 33,
        T__33               = 34,
        T__34               = 35,
        T__35               = 36,
        T__36               = 37,
        T__37               = 38,
        T__38               = 39,
        T__39               = 40,
        T__40               = 41,
        T__41               = 42,
        T__42               = 43,
        T__43               = 44,
        T__44               = 45,
        T__45               = 46,
        T__46               = 47,
        T__47               = 48,
        T__48               = 49,
        T__49               = 50,
        T__50               = 51,
        T__51               = 52,
        T__52               = 53,
        T__53               = 54,
        T__54               = 55,
        T__55               = 56,
        T__56               = 57,
        T__57               = 58,
        T__58               = 59,
        T__59               = 60,
        T__60               = 61,
        T__61               = 62,
        T__62               = 63,
        T__63               = 64,
        T__64               = 65,
        T__65               = 66,
        T__66               = 67,
        NATIVE_INTEGER_TYPE = 68,
        SIGNED_INTEGER      = 69,
        HEX_INTEGER         = 70,
        BIN_INTEGER         = 71,
        OCT_INTEGER         = 72,
        HALF                = 73,
        SINGLE              = 74,
        DOUBLE              = 75,
        QUAD                = 76,
        DECIMAL             = 77,
        STRING              = 78,
        BYTE                = 79,
        INTEGER             = 80,
        BUFFER              = 81,
        CONST               = 82,
        IDENTIFIER          = 83,
        SEMICOLON           = 84,
        WHITESPACE          = 85,
        BLOCK_COMMENT       = 86,
        LINE_COMMENT        = 87
    };

    explicit anceLexer(antlr4::CharStream* input);

    ~anceLexer() override;

    std::string getGrammarFileName() const override;

    const std::vector<std::string>& getRuleNames() const override;

    const std::vector<std::string>& getChannelNames() const override;

    const std::vector<std::string>& getModeNames() const override;

    const antlr4::dfa::Vocabulary& getVocabulary() const override;

    antlr4::atn::SerializedATNView getSerializedATN() const override;

    const antlr4::atn::ATN& getATN() const override;

    // By default the static state used to implement the lexer is lazily initialized during the first
    // call to the constructor. You can call this function if you wish to initialize the static state
    // ahead of time.
    static void initialize();

  private:
    // Individual action functions triggered by action() above.

    // Individual semantic predicate functions triggered by sempred() above.
};

