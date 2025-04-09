
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  anceLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, IDENTIFIER = 9, SEMICOLON = 10, WHITESPACE = 11, BLOCK_COMMENT = 12, 
    LINE_COMMENT = 13, BRACKET_OPEN = 14, BRACKET_CLOSE = 15, CURLY_BRACKET_OPEN = 16, 
    CURLY_BRACKET_CLOSE = 17, SQUARE_BRACKET_OPEN = 18, SQUARE_BRACKET_CLOSE = 19, 
    POINTY_BRACKET_OPEN = 20, POINTY_BRACKET_CLOSE = 21, ERROR_CHAR = 22
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

