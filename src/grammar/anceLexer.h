
// Generated from ./src/grammar/ance.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  anceLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, NATIVE_INTEGER_TYPE = 13, 
    HALF_TYPE = 14, SINGLE_TYPE = 15, DOUBLE_TYPE = 16, QUAD_TYPE = 17, 
    SIGNED_INTEGER = 18, HEX_INTEGER = 19, BIN_INTEGER = 20, OCT_INTEGER = 21, 
    HALF = 22, SINGLE = 23, DOUBLE = 24, QUAD = 25, DECIMAL = 26, STRING = 27, 
    BYTE = 28, INTEGER = 29, DYNAMIC = 30, AUTOMATIC = 31, TRUE = 32, FALSE = 33, 
    SIZE = 34, UIPTR = 35, PRINT = 36, RETURN = 37, DELETE = 38, CONST = 39, 
    PUBLIC = 40, PRIVATE = 41, VOID = 42, IDENTIFIER = 43, DEFINITION = 44, 
    ASSIGNMENT = 45, WHITESPACE = 46, BLOCK_COMMENT = 47, LINE_COMMENT = 48
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

