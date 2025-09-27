
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
      "unorderedScopeFile", "orderedScopeFile", "statement", "expression", 
      "unary", "literal", "type", "boolean", "entity", "assigner"
    },
    std::vector<std::string>{
      "", "'let'", "':'", "'if'", "'then'", "'else'", "'loop'", "'break'", 
      "'continue'", "'while'", "'do'", "','", "'here'", "'not'", "'Bool'", 
      "'Unit'", "'Size'", "'String'", "'Type'", "'true'", "'false'", "'<:'", 
      "", "", "", "';'", "", "", "", "'('", "')'", "'{'", "'}'", "'['", 
      "']'", "'<'", "'>'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "IDENTIFIER", "INTEGER", "STRING", "SEMICOLON", 
      "WHITESPACE", "BLOCK_COMMENT", "LINE_COMMENT", "BRACKET_OPEN", "BRACKET_CLOSE", 
      "CURLY_BRACKET_OPEN", "CURLY_BRACKET_CLOSE", "SQUARE_BRACKET_OPEN", 
      "SQUARE_BRACKET_CLOSE", "POINTY_BRACKET_OPEN", "POINTY_BRACKET_CLOSE", 
      "ERROR_CHAR"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,37,121,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,1,0,1,0,1,1,1,1,1,1,1,2,1,2,5,2,28,8,2,10,2,12,
  	2,31,9,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,44,8,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,59,8,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,72,8,2,1,3,1,3,1,3,1,3,1,3,5,3,79,
  	8,3,10,3,12,3,82,9,3,3,3,84,8,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,94,
  	8,3,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,3,5,104,8,5,1,6,1,6,1,6,1,6,1,6,3,
  	6,111,8,6,1,7,1,7,3,7,115,8,7,1,8,1,8,1,9,1,9,1,9,0,0,10,0,2,4,6,8,10,
  	12,14,16,18,0,0,136,0,20,1,0,0,0,2,22,1,0,0,0,4,71,1,0,0,0,6,93,1,0,0,
  	0,8,95,1,0,0,0,10,103,1,0,0,0,12,110,1,0,0,0,14,114,1,0,0,0,16,116,1,
  	0,0,0,18,118,1,0,0,0,20,21,5,0,0,1,21,1,1,0,0,0,22,23,3,4,2,0,23,24,5,
  	0,0,1,24,3,1,0,0,0,25,29,5,31,0,0,26,28,3,4,2,0,27,26,1,0,0,0,28,31,1,
  	0,0,0,29,27,1,0,0,0,29,30,1,0,0,0,30,32,1,0,0,0,31,29,1,0,0,0,32,72,5,
  	32,0,0,33,34,3,6,3,0,34,35,5,25,0,0,35,72,1,0,0,0,36,37,5,1,0,0,37,38,
  	5,22,0,0,38,39,5,2,0,0,39,43,3,6,3,0,40,41,3,18,9,0,41,42,3,6,3,0,42,
  	44,1,0,0,0,43,40,1,0,0,0,43,44,1,0,0,0,44,45,1,0,0,0,45,46,5,25,0,0,46,
  	72,1,0,0,0,47,48,3,16,8,0,48,49,3,18,9,0,49,50,3,6,3,0,50,51,5,25,0,0,
  	51,72,1,0,0,0,52,53,5,3,0,0,53,54,3,6,3,0,54,55,5,4,0,0,55,58,3,4,2,0,
  	56,57,5,5,0,0,57,59,3,4,2,0,58,56,1,0,0,0,58,59,1,0,0,0,59,72,1,0,0,0,
  	60,61,5,6,0,0,61,72,3,4,2,0,62,63,5,7,0,0,63,72,5,25,0,0,64,65,5,8,0,
  	0,65,72,5,25,0,0,66,67,5,9,0,0,67,68,3,6,3,0,68,69,5,10,0,0,69,70,3,4,
  	2,0,70,72,1,0,0,0,71,25,1,0,0,0,71,33,1,0,0,0,71,36,1,0,0,0,71,47,1,0,
  	0,0,71,52,1,0,0,0,71,60,1,0,0,0,71,62,1,0,0,0,71,64,1,0,0,0,71,66,1,0,
  	0,0,72,5,1,0,0,0,73,74,3,16,8,0,74,83,5,29,0,0,75,80,3,6,3,0,76,77,5,
  	11,0,0,77,79,3,6,3,0,78,76,1,0,0,0,79,82,1,0,0,0,80,78,1,0,0,0,80,81,
  	1,0,0,0,81,84,1,0,0,0,82,80,1,0,0,0,83,75,1,0,0,0,83,84,1,0,0,0,84,85,
  	1,0,0,0,85,86,5,30,0,0,86,94,1,0,0,0,87,94,3,16,8,0,88,94,3,10,5,0,89,
  	90,3,8,4,0,90,91,3,6,3,0,91,94,1,0,0,0,92,94,5,12,0,0,93,73,1,0,0,0,93,
  	87,1,0,0,0,93,88,1,0,0,0,93,89,1,0,0,0,93,92,1,0,0,0,94,7,1,0,0,0,95,
  	96,5,13,0,0,96,9,1,0,0,0,97,104,3,14,7,0,98,104,5,23,0,0,99,100,5,29,
  	0,0,100,104,5,30,0,0,101,104,3,12,6,0,102,104,5,24,0,0,103,97,1,0,0,0,
  	103,98,1,0,0,0,103,99,1,0,0,0,103,101,1,0,0,0,103,102,1,0,0,0,104,11,
  	1,0,0,0,105,111,5,14,0,0,106,111,5,15,0,0,107,111,5,16,0,0,108,111,5,
  	17,0,0,109,111,5,18,0,0,110,105,1,0,0,0,110,106,1,0,0,0,110,107,1,0,0,
  	0,110,108,1,0,0,0,110,109,1,0,0,0,111,13,1,0,0,0,112,115,5,19,0,0,113,
  	115,5,20,0,0,114,112,1,0,0,0,114,113,1,0,0,0,115,15,1,0,0,0,116,117,5,
  	22,0,0,117,17,1,0,0,0,118,119,5,21,0,0,119,19,1,0,0,0,10,29,43,58,71,
  	80,83,93,103,110,114
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


//----------------- UnorderedScopeFileContext ------------------------------------------------------------------

anceParser::UnorderedScopeFileContext::UnorderedScopeFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::UnorderedScopeFileContext::EOF() {
  return getToken(anceParser::EOF, 0);
}


size_t anceParser::UnorderedScopeFileContext::getRuleIndex() const {
  return anceParser::RuleUnorderedScopeFile;
}


std::any anceParser::UnorderedScopeFileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitUnorderedScopeFile(this);
  else
    return visitor->visitChildren(this);
}

anceParser::UnorderedScopeFileContext* anceParser::unorderedScopeFile() {
  UnorderedScopeFileContext *_localctx = _tracker.createInstance<UnorderedScopeFileContext>(_ctx, getState());
  enterRule(_localctx, 0, anceParser::RuleUnorderedScopeFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(20);
    match(anceParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OrderedScopeFileContext ------------------------------------------------------------------

anceParser::OrderedScopeFileContext::OrderedScopeFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::StatementContext* anceParser::OrderedScopeFileContext::statement() {
  return getRuleContext<anceParser::StatementContext>(0);
}

tree::TerminalNode* anceParser::OrderedScopeFileContext::EOF() {
  return getToken(anceParser::EOF, 0);
}


size_t anceParser::OrderedScopeFileContext::getRuleIndex() const {
  return anceParser::RuleOrderedScopeFile;
}


std::any anceParser::OrderedScopeFileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitOrderedScopeFile(this);
  else
    return visitor->visitChildren(this);
}

anceParser::OrderedScopeFileContext* anceParser::orderedScopeFile() {
  OrderedScopeFileContext *_localctx = _tracker.createInstance<OrderedScopeFileContext>(_ctx, getState());
  enterRule(_localctx, 2, anceParser::RuleOrderedScopeFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(22);
    statement();
    setState(23);
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

//----------------- BreakStatementContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::BreakStatementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

anceParser::BreakStatementContext::BreakStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any anceParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStatementContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::IfStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

std::vector<anceParser::StatementContext *> anceParser::IfStatementContext::statement() {
  return getRuleContexts<anceParser::StatementContext>();
}

anceParser::StatementContext* anceParser::IfStatementContext::statement(size_t i) {
  return getRuleContext<anceParser::StatementContext>(i);
}

anceParser::IfStatementContext::IfStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any anceParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignmentStatementContext ------------------------------------------------------------------

anceParser::EntityContext* anceParser::AssignmentStatementContext::entity() {
  return getRuleContext<anceParser::EntityContext>(0);
}

anceParser::AssignerContext* anceParser::AssignmentStatementContext::assigner() {
  return getRuleContext<anceParser::AssignerContext>(0);
}

anceParser::ExpressionContext* anceParser::AssignmentStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

tree::TerminalNode* anceParser::AssignmentStatementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

anceParser::AssignmentStatementContext::AssignmentStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any anceParser::AssignmentStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAssignmentStatement(this);
  else
    return visitor->visitChildren(this);
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
//----------------- LoopStatementContext ------------------------------------------------------------------

anceParser::StatementContext* anceParser::LoopStatementContext::statement() {
  return getRuleContext<anceParser::StatementContext>(0);
}

anceParser::LoopStatementContext::LoopStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any anceParser::LoopStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLoopStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileStatementContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::WhileStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::StatementContext* anceParser::WhileStatementContext::statement() {
  return getRuleContext<anceParser::StatementContext>(0);
}

anceParser::WhileStatementContext::WhileStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any anceParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
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

std::vector<anceParser::ExpressionContext *> anceParser::LetStatementContext::expression() {
  return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::LetStatementContext::expression(size_t i) {
  return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::AssignerContext* anceParser::LetStatementContext::assigner() {
  return getRuleContext<anceParser::AssignerContext>(0);
}

anceParser::LetStatementContext::LetStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any anceParser::LetStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLetStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContinueStatementContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::ContinueStatementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

anceParser::ContinueStatementContext::ContinueStatementContext(StatementContext *ctx) { copyFrom(ctx); }


std::any anceParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}
anceParser::StatementContext* anceParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 4, anceParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(71);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::BlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(25);
      match(anceParser::CURLY_BRACKET_OPEN);
      setState(29);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << anceParser::T__0)
        | (1ULL << anceParser::T__2)
        | (1ULL << anceParser::T__5)
        | (1ULL << anceParser::T__6)
        | (1ULL << anceParser::T__7)
        | (1ULL << anceParser::T__8)
        | (1ULL << anceParser::T__11)
        | (1ULL << anceParser::T__12)
        | (1ULL << anceParser::T__13)
        | (1ULL << anceParser::T__14)
        | (1ULL << anceParser::T__15)
        | (1ULL << anceParser::T__16)
        | (1ULL << anceParser::T__17)
        | (1ULL << anceParser::T__18)
        | (1ULL << anceParser::T__19)
        | (1ULL << anceParser::IDENTIFIER)
        | (1ULL << anceParser::INTEGER)
        | (1ULL << anceParser::STRING)
        | (1ULL << anceParser::BRACKET_OPEN)
        | (1ULL << anceParser::CURLY_BRACKET_OPEN))) != 0)) {
        setState(26);
        statement();
        setState(31);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(32);
      match(anceParser::CURLY_BRACKET_CLOSE);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::ExpressionStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(33);
      expression();
      setState(34);
      match(anceParser::SEMICOLON);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<anceParser::LetStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(36);
      match(anceParser::T__0);
      setState(37);
      match(anceParser::IDENTIFIER);
      setState(38);
      match(anceParser::T__1);
      setState(39);
      antlrcpp::downCast<LetStatementContext *>(_localctx)->varType = expression();
      setState(43);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == anceParser::T__20) {
        setState(40);
        assigner();
        setState(41);
        antlrcpp::downCast<LetStatementContext *>(_localctx)->assigned = expression();
      }
      setState(45);
      match(anceParser::SEMICOLON);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<anceParser::AssignmentStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(47);
      entity();
      setState(48);
      assigner();
      setState(49);
      expression();
      setState(50);
      match(anceParser::SEMICOLON);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<anceParser::IfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(52);
      match(anceParser::T__2);
      setState(53);
      expression();
      setState(54);
      match(anceParser::T__3);
      setState(55);
      antlrcpp::downCast<IfStatementContext *>(_localctx)->trueBlock = statement();
      setState(58);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(56);
        match(anceParser::T__4);
        setState(57);
        antlrcpp::downCast<IfStatementContext *>(_localctx)->falseBlock = statement();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<anceParser::LoopStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(60);
      match(anceParser::T__5);
      setState(61);
      statement();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<anceParser::BreakStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(62);
      match(anceParser::T__6);
      setState(63);
      match(anceParser::SEMICOLON);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<anceParser::ContinueStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(64);
      match(anceParser::T__7);
      setState(65);
      match(anceParser::SEMICOLON);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<anceParser::WhileStatementContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(66);
      match(anceParser::T__8);
      setState(67);
      expression();
      setState(68);
      match(anceParser::T__9);
      setState(69);
      statement();
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

//----------------- UnaryOperationExpressionContext ------------------------------------------------------------------

anceParser::UnaryContext* anceParser::UnaryOperationExpressionContext::unary() {
  return getRuleContext<anceParser::UnaryContext>(0);
}

anceParser::ExpressionContext* anceParser::UnaryOperationExpressionContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::UnaryOperationExpressionContext::UnaryOperationExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::UnaryOperationExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitUnaryOperationExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LiteralExpressionContext ------------------------------------------------------------------

anceParser::LiteralContext* anceParser::LiteralExpressionContext::literal() {
  return getRuleContext<anceParser::LiteralContext>(0);
}

anceParser::LiteralExpressionContext::LiteralExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::LiteralExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLiteralExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AccessExpressionContext ------------------------------------------------------------------

anceParser::EntityContext* anceParser::AccessExpressionContext::entity() {
  return getRuleContext<anceParser::EntityContext>(0);
}

anceParser::AccessExpressionContext::AccessExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::AccessExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAccessExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CallExpressionContext ------------------------------------------------------------------

anceParser::EntityContext* anceParser::CallExpressionContext::entity() {
  return getRuleContext<anceParser::EntityContext>(0);
}

tree::TerminalNode* anceParser::CallExpressionContext::BRACKET_OPEN() {
  return getToken(anceParser::BRACKET_OPEN, 0);
}

tree::TerminalNode* anceParser::CallExpressionContext::BRACKET_CLOSE() {
  return getToken(anceParser::BRACKET_CLOSE, 0);
}

std::vector<anceParser::ExpressionContext *> anceParser::CallExpressionContext::expression() {
  return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::CallExpressionContext::expression(size_t i) {
  return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::CallExpressionContext::CallExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::CallExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitCallExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- HereExpressionContext ------------------------------------------------------------------

anceParser::HereExpressionContext::HereExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::HereExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitHereExpression(this);
  else
    return visitor->visitChildren(this);
}
anceParser::ExpressionContext* anceParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 6, anceParser::RuleExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(93);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::CallExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(73);
      entity();
      setState(74);
      match(anceParser::BRACKET_OPEN);
      setState(83);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << anceParser::T__11)
        | (1ULL << anceParser::T__12)
        | (1ULL << anceParser::T__13)
        | (1ULL << anceParser::T__14)
        | (1ULL << anceParser::T__15)
        | (1ULL << anceParser::T__16)
        | (1ULL << anceParser::T__17)
        | (1ULL << anceParser::T__18)
        | (1ULL << anceParser::T__19)
        | (1ULL << anceParser::IDENTIFIER)
        | (1ULL << anceParser::INTEGER)
        | (1ULL << anceParser::STRING)
        | (1ULL << anceParser::BRACKET_OPEN))) != 0)) {
        setState(75);
        expression();
        setState(80);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__10) {
          setState(76);
          match(anceParser::T__10);
          setState(77);
          expression();
          setState(82);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(85);
      match(anceParser::BRACKET_CLOSE);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::AccessExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(87);
      entity();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<anceParser::LiteralExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(88);
      literal();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<anceParser::UnaryOperationExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(89);
      unary();
      setState(90);
      expression();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<anceParser::HereExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(92);
      match(anceParser::T__11);
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

//----------------- UnaryContext ------------------------------------------------------------------

anceParser::UnaryContext::UnaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::UnaryContext::getRuleIndex() const {
  return anceParser::RuleUnary;
}

void anceParser::UnaryContext::copyFrom(UnaryContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnaryNotContext ------------------------------------------------------------------

anceParser::UnaryNotContext::UnaryNotContext(UnaryContext *ctx) { copyFrom(ctx); }


std::any anceParser::UnaryNotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitUnaryNot(this);
  else
    return visitor->visitChildren(this);
}
anceParser::UnaryContext* anceParser::unary() {
  UnaryContext *_localctx = _tracker.createInstance<UnaryContext>(_ctx, getState());
  enterRule(_localctx, 8, anceParser::RuleUnary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<anceParser::UnaryNotContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(95);
    match(anceParser::T__12);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

anceParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::LiteralContext::getRuleIndex() const {
  return anceParser::RuleLiteral;
}

void anceParser::LiteralContext::copyFrom(LiteralContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TypeLiteralContext ------------------------------------------------------------------

anceParser::TypeContext* anceParser::TypeLiteralContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::TypeLiteralContext::TypeLiteralContext(LiteralContext *ctx) { copyFrom(ctx); }


std::any anceParser::TypeLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitTypeLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StringLiteralContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::StringLiteralContext::STRING() {
  return getToken(anceParser::STRING, 0);
}

anceParser::StringLiteralContext::StringLiteralContext(LiteralContext *ctx) { copyFrom(ctx); }


std::any anceParser::StringLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitStringLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BooleanLiteralContext ------------------------------------------------------------------

anceParser::BooleanContext* anceParser::BooleanLiteralContext::boolean() {
  return getRuleContext<anceParser::BooleanContext>(0);
}

anceParser::BooleanLiteralContext::BooleanLiteralContext(LiteralContext *ctx) { copyFrom(ctx); }


std::any anceParser::BooleanLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBooleanLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnitLiteralContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::UnitLiteralContext::BRACKET_OPEN() {
  return getToken(anceParser::BRACKET_OPEN, 0);
}

tree::TerminalNode* anceParser::UnitLiteralContext::BRACKET_CLOSE() {
  return getToken(anceParser::BRACKET_CLOSE, 0);
}

anceParser::UnitLiteralContext::UnitLiteralContext(LiteralContext *ctx) { copyFrom(ctx); }


std::any anceParser::UnitLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitUnitLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SizeLiteralContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::SizeLiteralContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}

anceParser::SizeLiteralContext::SizeLiteralContext(LiteralContext *ctx) { copyFrom(ctx); }


std::any anceParser::SizeLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSizeLiteral(this);
  else
    return visitor->visitChildren(this);
}
anceParser::LiteralContext* anceParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 10, anceParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(103);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__18:
      case anceParser::T__19: {
        _localctx = _tracker.createInstance<anceParser::BooleanLiteralContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(97);
        boolean();
        break;
      }

      case anceParser::INTEGER: {
        _localctx = _tracker.createInstance<anceParser::SizeLiteralContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(98);
        match(anceParser::INTEGER);
        break;
      }

      case anceParser::BRACKET_OPEN: {
        _localctx = _tracker.createInstance<anceParser::UnitLiteralContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(99);
        match(anceParser::BRACKET_OPEN);
        setState(100);
        match(anceParser::BRACKET_CLOSE);
        break;
      }

      case anceParser::T__13:
      case anceParser::T__14:
      case anceParser::T__15:
      case anceParser::T__16:
      case anceParser::T__17: {
        _localctx = _tracker.createInstance<anceParser::TypeLiteralContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(101);
        type();
        break;
      }

      case anceParser::STRING: {
        _localctx = _tracker.createInstance<anceParser::StringLiteralContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(102);
        match(anceParser::STRING);
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

//----------------- TypeContext ------------------------------------------------------------------

anceParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::TypeContext::getRuleIndex() const {
  return anceParser::RuleType;
}

void anceParser::TypeContext::copyFrom(TypeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BoolTypeContext ------------------------------------------------------------------

anceParser::BoolTypeContext::BoolTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any anceParser::BoolTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBoolType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StringTypeContext ------------------------------------------------------------------

anceParser::StringTypeContext::StringTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any anceParser::StringTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitStringType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnitTypeContext ------------------------------------------------------------------

anceParser::UnitTypeContext::UnitTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any anceParser::UnitTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitUnitType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SizeTypeContext ------------------------------------------------------------------

anceParser::SizeTypeContext::SizeTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any anceParser::SizeTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSizeType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TypeTypeContext ------------------------------------------------------------------

anceParser::TypeTypeContext::TypeTypeContext(TypeContext *ctx) { copyFrom(ctx); }


std::any anceParser::TypeTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitTypeType(this);
  else
    return visitor->visitChildren(this);
}
anceParser::TypeContext* anceParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 12, anceParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(110);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__13: {
        _localctx = _tracker.createInstance<anceParser::BoolTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(105);
        match(anceParser::T__13);
        break;
      }

      case anceParser::T__14: {
        _localctx = _tracker.createInstance<anceParser::UnitTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(106);
        match(anceParser::T__14);
        break;
      }

      case anceParser::T__15: {
        _localctx = _tracker.createInstance<anceParser::SizeTypeContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(107);
        match(anceParser::T__15);
        break;
      }

      case anceParser::T__16: {
        _localctx = _tracker.createInstance<anceParser::StringTypeContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(108);
        match(anceParser::T__16);
        break;
      }

      case anceParser::T__17: {
        _localctx = _tracker.createInstance<anceParser::TypeTypeContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(109);
        match(anceParser::T__17);
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

//----------------- BooleanContext ------------------------------------------------------------------

anceParser::BooleanContext::BooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::BooleanContext::getRuleIndex() const {
  return anceParser::RuleBoolean;
}

void anceParser::BooleanContext::copyFrom(BooleanContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TrueContext ------------------------------------------------------------------

anceParser::TrueContext::TrueContext(BooleanContext *ctx) { copyFrom(ctx); }


std::any anceParser::TrueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitTrue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FalseContext ------------------------------------------------------------------

anceParser::FalseContext::FalseContext(BooleanContext *ctx) { copyFrom(ctx); }


std::any anceParser::FalseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFalse(this);
  else
    return visitor->visitChildren(this);
}
anceParser::BooleanContext* anceParser::boolean() {
  BooleanContext *_localctx = _tracker.createInstance<BooleanContext>(_ctx, getState());
  enterRule(_localctx, 14, anceParser::RuleBoolean);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(114);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__18: {
        _localctx = _tracker.createInstance<anceParser::TrueContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(112);
        match(anceParser::T__18);
        break;
      }

      case anceParser::T__19: {
        _localctx = _tracker.createInstance<anceParser::FalseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(113);
        match(anceParser::T__19);
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
  enterRule(_localctx, 16, anceParser::RuleEntity);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    match(anceParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignerContext ------------------------------------------------------------------

anceParser::AssignerContext::AssignerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::AssignerContext::getRuleIndex() const {
  return anceParser::RuleAssigner;
}


std::any anceParser::AssignerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAssigner(this);
  else
    return visitor->visitChildren(this);
}

anceParser::AssignerContext* anceParser::assigner() {
  AssignerContext *_localctx = _tracker.createInstance<AssignerContext>(_ctx, getState());
  enterRule(_localctx, 18, anceParser::RuleAssigner);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    match(anceParser::T__20);
   
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
