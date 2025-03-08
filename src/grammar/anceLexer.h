
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  anceLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, IDENTIFIER = 4, SEMICOLON = 5, WHITESPACE = 6, 
    BLOCK_COMMENT = 7, LINE_COMMENT = 8, BRACKET_OPEN = 9, BRACKET_CLOSE = 10, 
    CURLY_BRACKET_OPEN = 11, CURLY_BRACKET_CLOSE = 12, SQUARE_BRACKET_OPEN = 13, 
    SQUARE_BRACKET_CLOSE = 14, POINTY_BRACKET_OPEN = 15, POINTY_BRACKET_CLOSE = 16, 
    ERROR_CHAR = 17
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

