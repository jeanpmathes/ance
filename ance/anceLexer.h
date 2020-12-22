
// Generated from ./ance.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  anceLexer : public antlr4::Lexer {
public:
  enum {
    STRING = 1, INTEGER = 2, MAIN = 3, PRINT = 4, RETURN = 5, CONST = 6, 
    IDENTIFIER = 7, ASSIGNMENT = 8, PARANTHESE_OPEN = 9, PARANTHESE_CLOSED = 10, 
    BRACE_OPEN = 11, BRACE_CLOSED = 12, SEMICOLON = 13, WHITESPACE = 14
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

