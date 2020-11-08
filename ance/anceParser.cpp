
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

std::vector<anceParser::TypeContext *> anceParser::FileContext::type() {
  return getRuleContexts<anceParser::TypeContext>();
}

anceParser::TypeContext* anceParser::FileContext::type(size_t i) {
  return getRuleContext<anceParser::TypeContext>(i);
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
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(17); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(16);
      type();
      setState(19); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == anceParser::MAIN

    || _la == anceParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

anceParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::EntryContext* anceParser::TypeContext::entry() {
  return getRuleContext<anceParser::EntryContext>(0);
}

anceParser::FunctionContext* anceParser::TypeContext::function() {
  return getRuleContext<anceParser::FunctionContext>(0);
}


size_t anceParser::TypeContext::getRuleIndex() const {
  return anceParser::RuleType;
}

void anceParser::TypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType(this);
}

void anceParser::TypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType(this);
}

anceParser::TypeContext* anceParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 2, anceParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(23);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::MAIN: {
        enterOuterAlt(_localctx, 1);
        setState(21);
        entry();
        break;
      }

      case anceParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(22);
        function();
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
  enterRule(_localctx, 4, anceParser::RuleEntry);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(25);
    match(anceParser::MAIN);
    setState(26);
    match(anceParser::PARANTHESE_OPEN);
    setState(27);
    match(anceParser::PARANTHESE_CLOSED);
    setState(28);
    match(anceParser::BRACE_OPEN);
    setState(30); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(29);
      statement();
      setState(32); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::PRINT)
      | (1ULL << anceParser::RETURN)
      | (1ULL << anceParser::IDENTIFIER))) != 0));
    setState(34);
    match(anceParser::BRACE_CLOSED);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

anceParser::FunctionContext::FunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::FunctionContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::FunctionContext::PARANTHESE_OPEN() {
  return getToken(anceParser::PARANTHESE_OPEN, 0);
}

tree::TerminalNode* anceParser::FunctionContext::PARANTHESE_CLOSED() {
  return getToken(anceParser::PARANTHESE_CLOSED, 0);
}

tree::TerminalNode* anceParser::FunctionContext::BRACE_OPEN() {
  return getToken(anceParser::BRACE_OPEN, 0);
}

tree::TerminalNode* anceParser::FunctionContext::BRACE_CLOSED() {
  return getToken(anceParser::BRACE_CLOSED, 0);
}

std::vector<anceParser::StatementContext *> anceParser::FunctionContext::statement() {
  return getRuleContexts<anceParser::StatementContext>();
}

anceParser::StatementContext* anceParser::FunctionContext::statement(size_t i) {
  return getRuleContext<anceParser::StatementContext>(i);
}


size_t anceParser::FunctionContext::getRuleIndex() const {
  return anceParser::RuleFunction;
}

void anceParser::FunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction(this);
}

void anceParser::FunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction(this);
}

anceParser::FunctionContext* anceParser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 6, anceParser::RuleFunction);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(36);
    match(anceParser::IDENTIFIER);
    setState(37);
    match(anceParser::PARANTHESE_OPEN);
    setState(38);
    match(anceParser::PARANTHESE_CLOSED);
    setState(39);
    match(anceParser::BRACE_OPEN);
    setState(41); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(40);
      statement();
      setState(43); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::PRINT)
      | (1ULL << anceParser::RETURN)
      | (1ULL << anceParser::IDENTIFIER))) != 0));
    setState(45);
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

anceParser::Function_callContext* anceParser::StatementContext::function_call() {
  return getRuleContext<anceParser::Function_callContext>(0);
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
  enterRule(_localctx, 8, anceParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(50);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(47);
        function_call();
        break;
      }

      case anceParser::PRINT: {
        enterOuterAlt(_localctx, 2);
        setState(48);
        print_statement();
        break;
      }

      case anceParser::RETURN: {
        enterOuterAlt(_localctx, 3);
        setState(49);
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

//----------------- Function_callContext ------------------------------------------------------------------

anceParser::Function_callContext::Function_callContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Function_callContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::Function_callContext::PARANTHESE_OPEN() {
  return getToken(anceParser::PARANTHESE_OPEN, 0);
}

tree::TerminalNode* anceParser::Function_callContext::PARANTHESE_CLOSED() {
  return getToken(anceParser::PARANTHESE_CLOSED, 0);
}

tree::TerminalNode* anceParser::Function_callContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}


size_t anceParser::Function_callContext::getRuleIndex() const {
  return anceParser::RuleFunction_call;
}

void anceParser::Function_callContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction_call(this);
}

void anceParser::Function_callContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<anceListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction_call(this);
}

anceParser::Function_callContext* anceParser::function_call() {
  Function_callContext *_localctx = _tracker.createInstance<Function_callContext>(_ctx, getState());
  enterRule(_localctx, 10, anceParser::RuleFunction_call);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52);
    match(anceParser::IDENTIFIER);
    setState(53);
    match(anceParser::PARANTHESE_OPEN);
    setState(54);
    match(anceParser::PARANTHESE_CLOSED);
    setState(55);
    match(anceParser::SEMICOLON);
   
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
  enterRule(_localctx, 12, anceParser::RulePrint_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(57);
    match(anceParser::PRINT);
    setState(58);
    match(anceParser::STRING);
    setState(59);
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
  enterRule(_localctx, 14, anceParser::RuleReturn_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(61);
    match(anceParser::RETURN);
    setState(63);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER) {
      setState(62);
      match(anceParser::INTEGER);
    }
    setState(65);
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
  "file", "type", "entry", "function", "statement", "function_call", "print_statement", 
  "return_statement"
};

std::vector<std::string> anceParser::_literalNames = {
  "", "", "", "'main'", "'print'", "'return'", "", "'('", "')'", "'{'", 
  "'}'", "';'"
};

std::vector<std::string> anceParser::_symbolicNames = {
  "", "STRING", "INTEGER", "MAIN", "PRINT", "RETURN", "IDENTIFIER", "PARANTHESE_OPEN", 
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
    0x3, 0xe, 0x46, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x3, 0x2, 0x6, 0x2, 0x14, 0xa, 0x2, 
    0xd, 0x2, 0xe, 0x2, 0x15, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x1a, 0xa, 0x3, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x6, 0x4, 0x21, 0xa, 
    0x4, 0xd, 0x4, 0xe, 0x4, 0x22, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x6, 0x5, 0x2c, 0xa, 0x5, 0xd, 0x5, 0xe, 
    0x5, 0x2d, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 
    0x35, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x42, 
    0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x2, 0x2, 0xa, 0x2, 0x4, 0x6, 
    0x8, 0xa, 0xc, 0xe, 0x10, 0x2, 0x2, 0x2, 0x44, 0x2, 0x13, 0x3, 0x2, 
    0x2, 0x2, 0x4, 0x19, 0x3, 0x2, 0x2, 0x2, 0x6, 0x1b, 0x3, 0x2, 0x2, 0x2, 
    0x8, 0x26, 0x3, 0x2, 0x2, 0x2, 0xa, 0x34, 0x3, 0x2, 0x2, 0x2, 0xc, 0x36, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x10, 0x3f, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x14, 0x5, 0x4, 0x3, 0x2, 0x13, 0x12, 0x3, 0x2, 
    0x2, 0x2, 0x14, 0x15, 0x3, 0x2, 0x2, 0x2, 0x15, 0x13, 0x3, 0x2, 0x2, 
    0x2, 0x15, 0x16, 0x3, 0x2, 0x2, 0x2, 0x16, 0x3, 0x3, 0x2, 0x2, 0x2, 
    0x17, 0x1a, 0x5, 0x6, 0x4, 0x2, 0x18, 0x1a, 0x5, 0x8, 0x5, 0x2, 0x19, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x19, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x5, 
    0x3, 0x2, 0x2, 0x2, 0x1b, 0x1c, 0x7, 0x5, 0x2, 0x2, 0x1c, 0x1d, 0x7, 
    0x9, 0x2, 0x2, 0x1d, 0x1e, 0x7, 0xa, 0x2, 0x2, 0x1e, 0x20, 0x7, 0xb, 
    0x2, 0x2, 0x1f, 0x21, 0x5, 0xa, 0x6, 0x2, 0x20, 0x1f, 0x3, 0x2, 0x2, 
    0x2, 0x21, 0x22, 0x3, 0x2, 0x2, 0x2, 0x22, 0x20, 0x3, 0x2, 0x2, 0x2, 
    0x22, 0x23, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0x25, 0x7, 0xc, 0x2, 0x2, 0x25, 0x7, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 
    0x7, 0x8, 0x2, 0x2, 0x27, 0x28, 0x7, 0x9, 0x2, 0x2, 0x28, 0x29, 0x7, 
    0xa, 0x2, 0x2, 0x29, 0x2b, 0x7, 0xb, 0x2, 0x2, 0x2a, 0x2c, 0x5, 0xa, 
    0x6, 0x2, 0x2b, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0x3, 0x2, 0x2, 
    0x2, 0x2d, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x2d, 0x2e, 0x3, 0x2, 0x2, 0x2, 
    0x2e, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x30, 0x7, 0xc, 0x2, 0x2, 0x30, 
    0x9, 0x3, 0x2, 0x2, 0x2, 0x31, 0x35, 0x5, 0xc, 0x7, 0x2, 0x32, 0x35, 
    0x5, 0xe, 0x8, 0x2, 0x33, 0x35, 0x5, 0x10, 0x9, 0x2, 0x34, 0x31, 0x3, 
    0x2, 0x2, 0x2, 0x34, 0x32, 0x3, 0x2, 0x2, 0x2, 0x34, 0x33, 0x3, 0x2, 
    0x2, 0x2, 0x35, 0xb, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x7, 0x8, 0x2, 
    0x2, 0x37, 0x38, 0x7, 0x9, 0x2, 0x2, 0x38, 0x39, 0x7, 0xa, 0x2, 0x2, 
    0x39, 0x3a, 0x7, 0xd, 0x2, 0x2, 0x3a, 0xd, 0x3, 0x2, 0x2, 0x2, 0x3b, 
    0x3c, 0x7, 0x6, 0x2, 0x2, 0x3c, 0x3d, 0x7, 0x3, 0x2, 0x2, 0x3d, 0x3e, 
    0x7, 0xd, 0x2, 0x2, 0x3e, 0xf, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x41, 0x7, 
    0x7, 0x2, 0x2, 0x40, 0x42, 0x7, 0x4, 0x2, 0x2, 0x41, 0x40, 0x3, 0x2, 
    0x2, 0x2, 0x41, 0x42, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x3, 0x2, 0x2, 
    0x2, 0x43, 0x44, 0x7, 0xd, 0x2, 0x2, 0x44, 0x11, 0x3, 0x2, 0x2, 0x2, 
    0x8, 0x15, 0x19, 0x22, 0x2d, 0x34, 0x41, 
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
