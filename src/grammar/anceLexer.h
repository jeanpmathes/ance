
// Generated from ./src/grammar/ance.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  anceLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, NATIVE_INTEGER_TYPE = 11, HALF_TYPE = 12, 
    SINGLE_TYPE = 13, DOUBLE_TYPE = 14, QUAD_TYPE = 15, SIGNED_INTEGER = 16, 
    HEX_INTEGER = 17, BIN_INTEGER = 18, OCT_INTEGER = 19, HALF = 20, SINGLE = 21, 
    DOUBLE = 22, QUAD = 23, DECIMAL = 24, STRING = 25, BYTE = 26, INTEGER = 27, 
    TRUE = 28, FALSE = 29, SIZEOF = 30, SIZE = 31, UIPTR = 32, PRINT = 33, 
    RETURN = 34, CONST = 35, PUBLIC = 36, PRIVATE = 37, VOID = 38, IDENTIFIER = 39, 
    DEFINITION = 40, ASSIGNMENT = 41, WHITESPACE = 42, BLOCK_COMMENT = 43, 
    LINE_COMMENT = 44
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

