
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

anceParser::EntryContext* anceParser::FileContext::entry() {
  return getRuleContext<anceParser::EntryContext>(0);
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
    setState(10);
    entry();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EntryContext ------------------------------------------------------------------

anceParser::EntryContext::EntryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::EntryContext::MAIN() {
  return getToken(anceParser::MAIN, 0);
}

tree::TerminalNode* anceParser::EntryContext::PARANTHESE_OPEN() {
  return getToken(anceParser::PARANTHESE_OPEN, 0);
}

tree::TerminalNode* anceParser::EntryContext::PARANTHESE_CLOSED() {
  return getToken(anceParser::PARANTHESE_CLOSED, 0);
}

tree::TerminalNode* anceParser::EntryContext::BRACE_OPEN() {
  return getToken(anceParser::BRACE_OPEN, 0);
}

tree::TerminalNode* anceParser::EntryContext::BRACE_CLOSED() {
  return getToken(anceParser::BRACE_CLOSED, 0);
}

std::vector<anceParser::StatementContext *> anceParser::EntryContext::statement() {
  return getRuleContexts<anceParser::StatementContext>();
}

anceParser::StatementContext* anceParser::EntryContext::statement(size_t i) {
  return getRuleContext<anceParser::StatementContext>(i);
}


size_t anceParser::EntryContext::getRuleIndex() const {
  return anceParser::RuleEntry;
}

void anceParser::EntryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEntry(this);
}

void anceParser::EntryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEntry(this);
}

anceParser::EntryContext* anceParser::entry() {
  EntryContext *_localctx = _tracker.createInstance<EntryContext>(_ctx, getState());
  enterRule(_localctx, 2, anceParser::RuleEntry);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(12);
    match(anceParser::MAIN);
    setState(13);
    match(anceParser::PARANTHESE_OPEN);
    setState(14);
    match(anceParser::PARANTHESE_CLOSED);
    setState(15);
    match(anceParser::BRACE_OPEN);
    setState(17); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(16);
      statement();
      setState(19); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == anceParser::PRINT

    || _la == anceParser::RETURN);
    setState(21);
    match(anceParser::BRACE_CLOSED);
   
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

anceParser::Print_statementContext* anceParser::StatementContext::print_statement() {
  return getRuleContext<anceParser::Print_statementContext>(0);
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
  enterRule(_localctx, 4, anceParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(25);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::PRINT: {
        enterOuterAlt(_localctx, 1);
        setState(23);
        print_statement();
        break;
      }

      case anceParser::RETURN: {
        enterOuterAlt(_localctx, 2);
        setState(24);
        return_statement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Print_statementContext ------------------------------------------------------------------

anceParser::Print_statementContext::Print_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Print_statementContext::PRINT() {
  return getToken(anceParser::PRINT, 0);
}

tree::TerminalNode* anceParser::Print_statementContext::STRING() {
  return getToken(anceParser::STRING, 0);
}

tree::TerminalNode* anceParser::Print_statementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}


size_t anceParser::Print_statementContext::getRuleIndex() const {
  return anceParser::RulePrint_statement;
}

void anceParser::Print_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrint_statement(this);
}

void anceParser::Print_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrint_statement(this);
}

anceParser::Print_statementContext* anceParser::print_statement() {
  Print_statementContext *_localctx = _tracker.createInstance<Print_statementContext>(_ctx, getState());
  enterRule(_localctx, 6, anceParser::RulePrint_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(27);
    match(anceParser::PRINT);
    setState(28);
    match(anceParser::STRING);
    setState(29);
    match(anceParser::SEMICOLON);
   
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
  enterRule(_localctx, 8, anceParser::RuleReturn_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(31);
    match(anceParser::RETURN);
    setState(33);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER) {
      setState(32);
      match(anceParser::INTEGER);
    }
    setState(35);
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
  "file", "entry", "statement", "print_statement", "return_statement"
};

std::vector<std::string> anceParser::_literalNames = {
  "", "", "", "'main'", "'print'", "'return'", "'('", "')'", "'{'", "'}'", 
  "';'"
};

std::vector<std::string> anceParser::_symbolicNames = {
  "", "STRING", "INTEGER", "MAIN", "PRINT", "RETURN", "PARANTHESE_OPEN", 
  "PARANTHESE_CLOSED", "BRACE_OPEN", "BRACE_CLOSED", "SEMICOLON", "WHITESPACE"
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
    0x3, 0xd, 0x28, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x6, 0x3, 0x14, 0xa, 0x3, 
    0xd, 0x3, 0xe, 0x3, 0x15, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x5, 
    0x4, 0x1c, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 
    0x3, 0x6, 0x5, 0x6, 0x24, 0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x2, 
    0x2, 0x7, 0x2, 0x4, 0x6, 0x8, 0xa, 0x2, 0x2, 0x2, 0x25, 0x2, 0xc, 0x3, 
    0x2, 0x2, 0x2, 0x4, 0xe, 0x3, 0x2, 0x2, 0x2, 0x6, 0x1b, 0x3, 0x2, 0x2, 
    0x2, 0x8, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xa, 0x21, 0x3, 0x2, 0x2, 0x2, 0xc, 
    0xd, 0x5, 0x4, 0x3, 0x2, 0xd, 0x3, 0x3, 0x2, 0x2, 0x2, 0xe, 0xf, 0x7, 
    0x5, 0x2, 0x2, 0xf, 0x10, 0x7, 0x8, 0x2, 0x2, 0x10, 0x11, 0x7, 0x9, 
    0x2, 0x2, 0x11, 0x13, 0x7, 0xa, 0x2, 0x2, 0x12, 0x14, 0x5, 0x6, 0x4, 
    0x2, 0x13, 0x12, 0x3, 0x2, 0x2, 0x2, 0x14, 0x15, 0x3, 0x2, 0x2, 0x2, 
    0x15, 0x13, 0x3, 0x2, 0x2, 0x2, 0x15, 0x16, 0x3, 0x2, 0x2, 0x2, 0x16, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x17, 0x18, 0x7, 0xb, 0x2, 0x2, 0x18, 0x5, 
    0x3, 0x2, 0x2, 0x2, 0x19, 0x1c, 0x5, 0x8, 0x5, 0x2, 0x1a, 0x1c, 0x5, 
    0xa, 0x6, 0x2, 0x1b, 0x19, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x1a, 0x3, 0x2, 
    0x2, 0x2, 0x1c, 0x7, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1e, 0x7, 0x6, 0x2, 
    0x2, 0x1e, 0x1f, 0x7, 0x3, 0x2, 0x2, 0x1f, 0x20, 0x7, 0xc, 0x2, 0x2, 
    0x20, 0x9, 0x3, 0x2, 0x2, 0x2, 0x21, 0x23, 0x7, 0x7, 0x2, 0x2, 0x22, 
    0x24, 0x7, 0x4, 0x2, 0x2, 0x23, 0x22, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 
    0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 0x3, 0x2, 0x2, 0x2, 0x25, 0x26, 0x7, 
    0xc, 0x2, 0x2, 0x26, 0xb, 0x3, 0x2, 0x2, 0x2, 0x5, 0x15, 0x1b, 0x23, 
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
