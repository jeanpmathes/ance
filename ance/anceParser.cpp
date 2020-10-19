
// Generated from ./ance.g4 by ANTLR 4.8


#include "anceListener.h"

#include "anceParser.h"


using namespace antlrcpp;
using namespace antlr4;

anceParser::anceParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

anceParser::~anceParser() {
  delete _interpreter;
}

std::string anceParser::getGrammarFileName() const {
  return "ance.g4";
}

const std::vector<std::string>& anceParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& anceParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- FileContext ------------------------------------------------------------------

anceParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::StatementContext* anceParser::FileContext::statement() {
  return getRuleContext<anceParser::StatementContext>(0);
}


size_t anceParser::FileContext::getRuleIndex() const {
  return anceParser::RuleFile;
}

void anceParser::FileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFile(this);
}

void anceParser::FileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFile(this);
}

anceParser::FileContext* anceParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, anceParser::RuleFile);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(6);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

anceParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::Return_statementContext* anceParser::StatementContext::return_statement() {
  return getRuleContext<anceParser::Return_statementContext>(0);
}


size_t anceParser::StatementContext::getRuleIndex() const {
  return anceParser::RuleStatement;
}

void anceParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void anceParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

anceParser::StatementContext* anceParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, anceParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(8);
    return_statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Return_statementContext ------------------------------------------------------------------

anceParser::Return_statementContext::Return_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Return_statementContext::RETURN() {
  return getToken(anceParser::RETURN, 0);
}

tree::TerminalNode* anceParser::Return_statementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

tree::TerminalNode* anceParser::Return_statementContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}


size_t anceParser::Return_statementContext::getRuleIndex() const {
  return anceParser::RuleReturn_statement;
}

void anceParser::Return_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturn_statement(this);
}

void anceParser::Return_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturn_statement(this);
}

anceParser::Return_statementContext* anceParser::return_statement() {
  Return_statementContext *_localctx = _tracker.createInstance<Return_statementContext>(_ctx, getState());
  enterRule(_localctx, 4, anceParser::RuleReturn_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(10);
    match(anceParser::RETURN);
    setState(12);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER) {
      setState(11);
      match(anceParser::INTEGER);
    }
    setState(14);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> anceParser::_decisionToDFA;
atn::PredictionContextCache anceParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN anceParser::_atn;
std::vector<uint16_t> anceParser::_serializedATN;

std::vector<std::string> anceParser::_ruleNames = {
  "file", "statement", "return_statement"
};

std::vector<std::string> anceParser::_literalNames = {
  "", "", "'return'", "';'"
};

std::vector<std::string> anceParser::_symbolicNames = {
  "", "INTEGER", "RETURN", "SEMICOLON", "WHITESPACE"
};

dfa::Vocabulary anceParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> anceParser::_tokenNames;

anceParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x6, 0x13, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x5, 
    0x4, 0xf, 0xa, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x2, 0x2, 0x5, 0x2, 
    0x4, 0x6, 0x2, 0x2, 0x2, 0x10, 0x2, 0x8, 0x3, 0x2, 0x2, 0x2, 0x4, 0xa, 
    0x3, 0x2, 0x2, 0x2, 0x6, 0xc, 0x3, 0x2, 0x2, 0x2, 0x8, 0x9, 0x5, 0x4, 
    0x3, 0x2, 0x9, 0x3, 0x3, 0x2, 0x2, 0x2, 0xa, 0xb, 0x5, 0x6, 0x4, 0x2, 
    0xb, 0x5, 0x3, 0x2, 0x2, 0x2, 0xc, 0xe, 0x7, 0x4, 0x2, 0x2, 0xd, 0xf, 
    0x7, 0x3, 0x2, 0x2, 0xe, 0xd, 0x3, 0x2, 0x2, 0x2, 0xe, 0xf, 0x3, 0x2, 
    0x2, 0x2, 0xf, 0x10, 0x3, 0x2, 0x2, 0x2, 0x10, 0x11, 0x7, 0x5, 0x2, 
    0x2, 0x11, 0x7, 0x3, 0x2, 0x2, 0x2, 0x3, 0xe, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

anceParser::Initializer anceParser::_init;
