
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  anceLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    IDENTIFIER = 21, INTEGER = 22, SEMICOLON = 23, WHITESPACE = 24, BLOCK_COMMENT = 25, 
    LINE_COMMENT = 26, BRACKET_OPEN = 27, BRACKET_CLOSE = 28, CURLY_BRACKET_OPEN = 29, 
    CURLY_BRACKET_CLOSE = 30, SQUARE_BRACKET_OPEN = 31, SQUARE_BRACKET_CLOSE = 32, 
    POINTY_BRACKET_OPEN = 33, POINTY_BRACKET_CLOSE = 34, ERROR_CHAR = 35
  };

  explicit anceLexer(antlr4::CharStream *input);

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

