
// Generated from ./ance.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  anceLexer : public antlr4::Lexer {
public:
  enum {
    NATIVE_INTEGER_TYPE = 1, SIGNED_INTEGER = 2, HEX_INTEGER = 3, BIN_INTEGER = 4, 
    OCT_INTEGER = 5, STRING = 6, INTEGER = 7, PRINT = 8, RETURN = 9, CONST = 10, 
    PUBLIC = 11, PRIVATE = 12, VOID = 13, IDENTIFIER = 14, DEFINITION = 15, 
    ASSIGNMENT = 16, PARANTHESE_OPEN = 17, PARANTHESE_CLOSED = 18, BRACE_OPEN = 19, 
    BRACE_CLOSED = 20, BRACKET_OPEN = 21, BRACKET_CLOSED = 22, COMMA = 23, 
    COLON = 24, SEMICOLON = 25, WHITESPACE = 26
  };

  anceLexer(antlr4::CharStream *input);
  ~anceLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

