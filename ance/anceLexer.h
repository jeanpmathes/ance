
// Generated from ./ance.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  anceLexer : public antlr4::Lexer {
public:
  enum {
    NATIVE_INTEGER_TYPE = 1, HALF_TYPE = 2, SINGLE_TYPE = 3, DOUBLE_TYPE = 4, 
    QUAD_TYPE = 5, SIGNED_INTEGER = 6, HEX_INTEGER = 7, BIN_INTEGER = 8, 
    OCT_INTEGER = 9, HALF = 10, SINGLE = 11, DOUBLE = 12, QUAD = 13, DECIMAL = 14, 
    STRING = 15, INTEGER = 16, PRINT = 17, RETURN = 18, CONST = 19, PUBLIC = 20, 
    PRIVATE = 21, VOID = 22, IDENTIFIER = 23, DEFINITION = 24, ASSIGNMENT = 25, 
    PARANTHESE_OPEN = 26, PARANTHESE_CLOSED = 27, BRACE_OPEN = 28, BRACE_CLOSED = 29, 
    BRACKET_OPEN = 30, BRACKET_CLOSED = 31, COMMA = 32, COLON = 33, SEMICOLON = 34, 
    WHITESPACE = 35
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

