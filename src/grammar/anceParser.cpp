
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
      "", "'do'", "'let'", "':'", "'if'", "'then'", "'else'", "'loop'", 
      "'break'", "'continue'", "'while'", "','", "'here'", "'not'", "'Bool'", 
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
  	4,1,37,128,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,1,0,1,0,5,0,23,8,0,10,0,12,0,26,9,0,1,0,1,0,1,1,
  	1,1,1,1,1,2,1,2,5,2,35,8,2,10,2,12,2,38,9,2,1,2,1,2,1,2,1,2,1,2,1,2,1,
  	2,1,2,1,2,1,2,1,2,3,2,51,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,1,2,1,2,3,2,66,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,
  	2,79,8,2,1,3,1,3,1,3,1,3,1,3,5,3,86,8,3,10,3,12,3,89,9,3,3,3,91,8,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,101,8,3,1,4,1,4,1,5,1,5,1,5,1,5,1,5,
  	1,5,3,5,111,8,5,1,6,1,6,1,6,1,6,1,6,3,6,118,8,6,1,7,1,7,3,7,122,8,7,1,
  	8,1,8,1,9,1,9,1,9,0,0,10,0,2,4,6,8,10,12,14,16,18,0,0,144,0,24,1,0,0,
  	0,2,29,1,0,0,0,4,78,1,0,0,0,6,100,1,0,0,0,8,102,1,0,0,0,10,110,1,0,0,
  	0,12,117,1,0,0,0,14,121,1,0,0,0,16,123,1,0,0,0,18,125,1,0,0,0,20,21,5,
  	1,0,0,21,23,3,4,2,0,22,20,1,0,0,0,23,26,1,0,0,0,24,22,1,0,0,0,24,25,1,
  	0,0,0,25,27,1,0,0,0,26,24,1,0,0,0,27,28,5,0,0,1,28,1,1,0,0,0,29,30,3,
  	4,2,0,30,31,5,0,0,1,31,3,1,0,0,0,32,36,5,31,0,0,33,35,3,4,2,0,34,33,1,
  	0,0,0,35,38,1,0,0,0,36,34,1,0,0,0,36,37,1,0,0,0,37,39,1,0,0,0,38,36,1,
  	0,0,0,39,79,5,32,0,0,40,41,3,6,3,0,41,42,5,25,0,0,42,79,1,0,0,0,43,44,
  	5,2,0,0,44,45,5,22,0,0,45,46,5,3,0,0,46,50,3,6,3,0,47,48,3,18,9,0,48,
  	49,3,6,3,0,49,51,1,0,0,0,50,47,1,0,0,0,50,51,1,0,0,0,51,52,1,0,0,0,52,
  	53,5,25,0,0,53,79,1,0,0,0,54,55,3,16,8,0,55,56,3,18,9,0,56,57,3,6,3,0,
  	57,58,5,25,0,0,58,79,1,0,0,0,59,60,5,4,0,0,60,61,3,6,3,0,61,62,5,5,0,
  	0,62,65,3,4,2,0,63,64,5,6,0,0,64,66,3,4,2,0,65,63,1,0,0,0,65,66,1,0,0,
  	0,66,79,1,0,0,0,67,68,5,7,0,0,68,79,3,4,2,0,69,70,5,8,0,0,70,79,5,25,
  	0,0,71,72,5,9,0,0,72,79,5,25,0,0,73,74,5,10,0,0,74,75,3,6,3,0,75,76,5,
  	1,0,0,76,77,3,4,2,0,77,79,1,0,0,0,78,32,1,0,0,0,78,40,1,0,0,0,78,43,1,
  	0,0,0,78,54,1,0,0,0,78,59,1,0,0,0,78,67,1,0,0,0,78,69,1,0,0,0,78,71,1,
  	0,0,0,78,73,1,0,0,0,79,5,1,0,0,0,80,81,3,16,8,0,81,90,5,29,0,0,82,87,
  	3,6,3,0,83,84,5,11,0,0,84,86,3,6,3,0,85,83,1,0,0,0,86,89,1,0,0,0,87,85,
  	1,0,0,0,87,88,1,0,0,0,88,91,1,0,0,0,89,87,1,0,0,0,90,82,1,0,0,0,90,91,
  	1,0,0,0,91,92,1,0,0,0,92,93,5,30,0,0,93,101,1,0,0,0,94,101,3,16,8,0,95,
  	101,3,10,5,0,96,97,3,8,4,0,97,98,3,6,3,0,98,101,1,0,0,0,99,101,5,12,0,
  	0,100,80,1,0,0,0,100,94,1,0,0,0,100,95,1,0,0,0,100,96,1,0,0,0,100,99,
  	1,0,0,0,101,7,1,0,0,0,102,103,5,13,0,0,103,9,1,0,0,0,104,111,3,14,7,0,
  	105,111,5,23,0,0,106,107,5,29,0,0,107,111,5,30,0,0,108,111,3,12,6,0,109,
  	111,5,24,0,0,110,104,1,0,0,0,110,105,1,0,0,0,110,106,1,0,0,0,110,108,
  	1,0,0,0,110,109,1,0,0,0,111,11,1,0,0,0,112,118,5,14,0,0,113,118,5,15,
  	0,0,114,118,5,16,0,0,115,118,5,17,0,0,116,118,5,18,0,0,117,112,1,0,0,
  	0,117,113,1,0,0,0,117,114,1,0,0,0,117,115,1,0,0,0,117,116,1,0,0,0,118,
  	13,1,0,0,0,119,122,5,19,0,0,120,122,5,20,0,0,121,119,1,0,0,0,121,120,
  	1,0,0,0,122,15,1,0,0,0,123,124,5,22,0,0,124,17,1,0,0,0,125,126,5,21,0,
  	0,126,19,1,0,0,0,11,24,36,50,65,78,87,90,100,110,117,121
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

std::vector<anceParser::StatementContext *> anceParser::UnorderedScopeFileContext::statement() {
  return getRuleContexts<anceParser::StatementContext>();
}

anceParser::StatementContext* anceParser::UnorderedScopeFileContext::statement(size_t i) {
  return getRuleContext<anceParser::StatementContext>(i);
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
    setState(24);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == anceParser::T__0) {
      setState(20);
      match(anceParser::T__0);
      setState(21);
      statement();
      setState(26);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(27);
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
    setState(29);
    statement();
    setState(30);
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
    setState(78);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::BlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(32);
      match(anceParser::CURLY_BRACKET_OPEN);
      setState(36);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << anceParser::T__1)
        | (1ULL << anceParser::T__3)
        | (1ULL << anceParser::T__6)
        | (1ULL << anceParser::T__7)
        | (1ULL << anceParser::T__8)
        | (1ULL << anceParser::T__9)
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
        setState(33);
        statement();
        setState(38);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(39);
      match(anceParser::CURLY_BRACKET_CLOSE);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::ExpressionStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(40);
      expression();
      setState(41);
      match(anceParser::SEMICOLON);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<anceParser::LetStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(43);
      match(anceParser::T__1);
      setState(44);
      match(anceParser::IDENTIFIER);
      setState(45);
      match(anceParser::T__2);
      setState(46);
      antlrcpp::downCast<LetStatementContext *>(_localctx)->varType = expression();
      setState(50);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == anceParser::T__20) {
        setState(47);
        assigner();
        setState(48);
        antlrcpp::downCast<LetStatementContext *>(_localctx)->assigned = expression();
      }
      setState(52);
      match(anceParser::SEMICOLON);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<anceParser::AssignmentStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(54);
      entity();
      setState(55);
      assigner();
      setState(56);
      expression();
      setState(57);
      match(anceParser::SEMICOLON);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<anceParser::IfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(59);
      match(anceParser::T__3);
      setState(60);
      expression();
      setState(61);
      match(anceParser::T__4);
      setState(62);
      antlrcpp::downCast<IfStatementContext *>(_localctx)->trueBlock = statement();
      setState(65);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
      case 1: {
        setState(63);
        match(anceParser::T__5);
        setState(64);
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
      setState(67);
      match(anceParser::T__6);
      setState(68);
      statement();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<anceParser::BreakStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(69);
      match(anceParser::T__7);
      setState(70);
      match(anceParser::SEMICOLON);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<anceParser::ContinueStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(71);
      match(anceParser::T__8);
      setState(72);
      match(anceParser::SEMICOLON);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<anceParser::WhileStatementContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(73);
      match(anceParser::T__9);
      setState(74);
      expression();
      setState(75);
      match(anceParser::T__0);
      setState(76);
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
    setState(100);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::CallExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(80);
      entity();
      setState(81);
      match(anceParser::BRACKET_OPEN);
      setState(90);
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
        setState(82);
        expression();
        setState(87);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__10) {
          setState(83);
          match(anceParser::T__10);
          setState(84);
          expression();
          setState(89);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(92);
      match(anceParser::BRACKET_CLOSE);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::AccessExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(94);
      entity();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<anceParser::LiteralExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(95);
      literal();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<anceParser::UnaryOperationExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(96);
      unary();
      setState(97);
      expression();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<anceParser::HereExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(99);
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
    setState(102);
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
    setState(110);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__18:
      case anceParser::T__19: {
        _localctx = _tracker.createInstance<anceParser::BooleanLiteralContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(104);
        boolean();
        break;
      }

      case anceParser::INTEGER: {
        _localctx = _tracker.createInstance<anceParser::SizeLiteralContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(105);
        match(anceParser::INTEGER);
        break;
      }

      case anceParser::BRACKET_OPEN: {
        _localctx = _tracker.createInstance<anceParser::UnitLiteralContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(106);
        match(anceParser::BRACKET_OPEN);
        setState(107);
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
        setState(108);
        type();
        break;
      }

      case anceParser::STRING: {
        _localctx = _tracker.createInstance<anceParser::StringLiteralContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(109);
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
    setState(117);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__13: {
        _localctx = _tracker.createInstance<anceParser::BoolTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(112);
        match(anceParser::T__13);
        break;
      }

      case anceParser::T__14: {
        _localctx = _tracker.createInstance<anceParser::UnitTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(113);
        match(anceParser::T__14);
        break;
      }

      case anceParser::T__15: {
        _localctx = _tracker.createInstance<anceParser::SizeTypeContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(114);
        match(anceParser::T__15);
        break;
      }

      case anceParser::T__16: {
        _localctx = _tracker.createInstance<anceParser::StringTypeContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(115);
        match(anceParser::T__16);
        break;
      }

      case anceParser::T__17: {
        _localctx = _tracker.createInstance<anceParser::TypeTypeContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(116);
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
    setState(121);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__18: {
        _localctx = _tracker.createInstance<anceParser::TrueContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(119);
        match(anceParser::T__18);
        break;
      }

      case anceParser::T__19: {
        _localctx = _tracker.createInstance<anceParser::FalseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(120);
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
    setState(123);
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
    setState(125);
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
