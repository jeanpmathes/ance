
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1


#include "anceVisitor.h"

#include "anceParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct AnceParserStaticData final {
  AnceParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  AnceParserStaticData(const AnceParserStaticData&) = delete;
  AnceParserStaticData(AnceParserStaticData&&) = delete;
  AnceParserStaticData& operator=(const AnceParserStaticData&) = delete;
  AnceParserStaticData& operator=(AnceParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag anceParserOnceFlag;
AnceParserStaticData *anceParserStaticData = nullptr;

void anceParserInitialize() {
  assert(anceParserStaticData == nullptr);
  auto staticData = std::make_unique<AnceParserStaticData>(
    std::vector<std::string>{
      "file", "statement", "expression", "arguments", "entity"
    },
    std::vector<std::string>{
      "", "'let'", "'<:'", "','", "", "';'", "", "", "", "'('", "')'", "'{'", 
      "'}'", "'['", "']'", "'<'", "'>'"
    },
    std::vector<std::string>{
      "", "", "", "", "IDENTIFIER", "SEMICOLON", "WHITESPACE", "BLOCK_COMMENT", 
      "LINE_COMMENT", "BRACKET_OPEN", "BRACKET_CLOSE", "CURLY_BRACKET_OPEN", 
      "CURLY_BRACKET_CLOSE", "SQUARE_BRACKET_OPEN", "SQUARE_BRACKET_CLOSE", 
      "POINTY_BRACKET_OPEN", "POINTY_BRACKET_CLOSE", "ERROR_CHAR"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,17,54,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,1,0,1,0,1,0,1,1,1,1,
  	5,1,16,8,1,10,1,12,1,19,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,29,8,
  	1,1,1,3,1,32,8,1,1,2,1,2,1,2,1,2,1,2,1,2,3,2,40,8,2,1,3,1,3,1,3,5,3,45,
  	8,3,10,3,12,3,48,9,3,3,3,50,8,3,1,4,1,4,1,4,0,0,5,0,2,4,6,8,0,0,55,0,
  	10,1,0,0,0,2,31,1,0,0,0,4,39,1,0,0,0,6,49,1,0,0,0,8,51,1,0,0,0,10,11,
  	3,2,1,0,11,12,5,0,0,1,12,1,1,0,0,0,13,17,5,11,0,0,14,16,3,2,1,0,15,14,
  	1,0,0,0,16,19,1,0,0,0,17,15,1,0,0,0,17,18,1,0,0,0,18,20,1,0,0,0,19,17,
  	1,0,0,0,20,32,5,12,0,0,21,22,3,4,2,0,22,23,5,5,0,0,23,32,1,0,0,0,24,25,
  	5,1,0,0,25,28,5,4,0,0,26,27,5,2,0,0,27,29,3,4,2,0,28,26,1,0,0,0,28,29,
  	1,0,0,0,29,30,1,0,0,0,30,32,5,5,0,0,31,13,1,0,0,0,31,21,1,0,0,0,31,24,
  	1,0,0,0,32,3,1,0,0,0,33,34,3,8,4,0,34,35,5,9,0,0,35,36,3,6,3,0,36,37,
  	5,10,0,0,37,40,1,0,0,0,38,40,3,8,4,0,39,33,1,0,0,0,39,38,1,0,0,0,40,5,
  	1,0,0,0,41,46,3,4,2,0,42,43,5,3,0,0,43,45,3,4,2,0,44,42,1,0,0,0,45,48,
  	1,0,0,0,46,44,1,0,0,0,46,47,1,0,0,0,47,50,1,0,0,0,48,46,1,0,0,0,49,41,
  	1,0,0,0,49,50,1,0,0,0,50,7,1,0,0,0,51,52,5,4,0,0,52,9,1,0,0,0,6,17,28,
  	31,39,46,49
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  anceParserStaticData = staticData.release();
}

}

anceParser::anceParser(TokenStream *input) : anceParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

anceParser::anceParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  anceParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *anceParserStaticData->atn, anceParserStaticData->decisionToDFA, anceParserStaticData->sharedContextCache, options);
}

anceParser::~anceParser() {
  delete _interpreter;
}

const atn::ATN& anceParser::getATN() const {
  return *anceParserStaticData->atn;
}

std::string anceParser::getGrammarFileName() const {
  return "ance.g4";
}

const std::vector<std::string>& anceParser::getRuleNames() const {
  return anceParserStaticData->ruleNames;
}

const dfa::Vocabulary& anceParser::getVocabulary() const {
  return anceParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView anceParser::getSerializedATN() const {
  return anceParserStaticData->serializedATN;
}


//----------------- FileContext ------------------------------------------------------------------

anceParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::StatementContext* anceParser::FileContext::statement() {
  return getRuleContext<anceParser::StatementContext>(0);
}

tree::TerminalNode* anceParser::FileContext::EOF() {
  return getToken(anceParser::EOF, 0);
}


size_t anceParser::FileContext::getRuleIndex() const {
  return anceParser::RuleFile;
}


std::any anceParser::FileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFile(this);
  else
    return visitor->visitChildren(this);
}

anceParser::FileContext* anceParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, anceParser::RuleFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(10);
    statement();
    setState(11);
    match(anceParser::EOF);
   
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


size_t anceParser::StatementContext::getRuleIndex() const {
  return anceParser::RuleStatement;
}

void anceParser::StatementContext::copyFrom(StatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::ExpressionStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

tree::TerminalNode* anceParser::ExpressionStatementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

anceParser::ExpressionStatementContext::ExpressionStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any anceParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStatementContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::BlockStatementContext::CURLY_BRACKET_OPEN() {
  return getToken(anceParser::CURLY_BRACKET_OPEN, 0);
}

tree::TerminalNode* anceParser::BlockStatementContext::CURLY_BRACKET_CLOSE() {
  return getToken(anceParser::CURLY_BRACKET_CLOSE, 0);
}

std::vector<anceParser::StatementContext *> anceParser::BlockStatementContext::statement() {
  return getRuleContexts<anceParser::StatementContext>();
}

anceParser::StatementContext* anceParser::BlockStatementContext::statement(size_t i) {
  return getRuleContext<anceParser::StatementContext>(i);
}

anceParser::BlockStatementContext::BlockStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any anceParser::BlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBlockStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LetStatementContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::LetStatementContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::LetStatementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

anceParser::ExpressionContext* anceParser::LetStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::LetStatementContext::LetStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any anceParser::LetStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLetStatement(this);
  else
    return visitor->visitChildren(this);
}
anceParser::StatementContext* anceParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, anceParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(31);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::CURLY_BRACKET_OPEN: {
        _localctx = _tracker.createInstance<anceParser::BlockStatementContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(13);
        match(anceParser::CURLY_BRACKET_OPEN);
        setState(17);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << anceParser::T__0)
          | (1ULL << anceParser::IDENTIFIER)
          | (1ULL << anceParser::CURLY_BRACKET_OPEN))) != 0)) {
          setState(14);
          statement();
          setState(19);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(20);
        match(anceParser::CURLY_BRACKET_CLOSE);
        break;
      }

      case anceParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<anceParser::ExpressionStatementContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(21);
        expression();
        setState(22);
        match(anceParser::SEMICOLON);
        break;
      }

      case anceParser::T__0: {
        _localctx = _tracker.createInstance<anceParser::LetStatementContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(24);
        match(anceParser::T__0);
        setState(25);
        match(anceParser::IDENTIFIER);
        setState(28);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::T__1) {
          setState(26);
          match(anceParser::T__1);
          setState(27);
          expression();
        }
        setState(30);
        match(anceParser::SEMICOLON);
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

//----------------- ExpressionContext ------------------------------------------------------------------

anceParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::ExpressionContext::getRuleIndex() const {
  return anceParser::RuleExpression;
}

void anceParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CallContext ------------------------------------------------------------------

anceParser::EntityContext* anceParser::CallContext::entity() {
  return getRuleContext<anceParser::EntityContext>(0);
}

tree::TerminalNode* anceParser::CallContext::BRACKET_OPEN() {
  return getToken(anceParser::BRACKET_OPEN, 0);
}

anceParser::ArgumentsContext* anceParser::CallContext::arguments() {
  return getRuleContext<anceParser::ArgumentsContext>(0);
}

tree::TerminalNode* anceParser::CallContext::BRACKET_CLOSE() {
  return getToken(anceParser::BRACKET_CLOSE, 0);
}

anceParser::CallContext::CallContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::CallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AccessContext ------------------------------------------------------------------

anceParser::EntityContext* anceParser::AccessContext::entity() {
  return getRuleContext<anceParser::EntityContext>(0);
}

anceParser::AccessContext::AccessContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::AccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAccess(this);
  else
    return visitor->visitChildren(this);
}
anceParser::ExpressionContext* anceParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 4, anceParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(39);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::CallContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(33);
      entity();
      setState(34);
      match(anceParser::BRACKET_OPEN);
      setState(35);
      arguments();
      setState(36);
      match(anceParser::BRACKET_CLOSE);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::AccessContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(38);
      entity();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

anceParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<anceParser::ExpressionContext *> anceParser::ArgumentsContext::expression() {
  return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::ArgumentsContext::expression(size_t i) {
  return getRuleContext<anceParser::ExpressionContext>(i);
}


size_t anceParser::ArgumentsContext::getRuleIndex() const {
  return anceParser::RuleArguments;
}


std::any anceParser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ArgumentsContext* anceParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 6, anceParser::RuleArguments);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(49);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::IDENTIFIER) {
      setState(41);
      expression();
      setState(46);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__2) {
        setState(42);
        match(anceParser::T__2);
        setState(43);
        expression();
        setState(48);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EntityContext ------------------------------------------------------------------

anceParser::EntityContext::EntityContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::EntityContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}


size_t anceParser::EntityContext::getRuleIndex() const {
  return anceParser::RuleEntity;
}


std::any anceParser::EntityContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitEntity(this);
  else
    return visitor->visitChildren(this);
}

anceParser::EntityContext* anceParser::entity() {
  EntityContext *_localctx = _tracker.createInstance<EntityContext>(_ctx, getState());
  enterRule(_localctx, 8, anceParser::RuleEntity);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(51);
    match(anceParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void anceParser::initialize() {
  std::call_once(anceParserOnceFlag, anceParserInitialize);
}
