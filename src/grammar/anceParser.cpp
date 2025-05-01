
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
      "file", "statement", "expression", "arguments", "unary", "literal", 
      "boolean", "entity", "assigner"
    },
    std::vector<std::string>{
      "", "'let'", "'if'", "'then'", "'else'", "'loop'", "'break'", "'continue'", 
      "'while'", "'do'", "','", "'not'", "'true'", "'false'", "'<:'", "", 
      "';'", "", "", "", "'('", "')'", "'{'", "'}'", "'['", "']'", "'<'", 
      "'>'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "IDENTIFIER", 
      "SEMICOLON", "WHITESPACE", "BLOCK_COMMENT", "LINE_COMMENT", "BRACKET_OPEN", 
      "BRACKET_CLOSE", "CURLY_BRACKET_OPEN", "CURLY_BRACKET_CLOSE", "SQUARE_BRACKET_OPEN", 
      "SQUARE_BRACKET_CLOSE", "POINTY_BRACKET_OPEN", "POINTY_BRACKET_CLOSE", 
      "ERROR_CHAR"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,28,101,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,1,0,1,0,1,0,1,1,1,1,5,1,24,8,1,10,1,12,1,27,9,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,38,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,3,1,52,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,3,1,65,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,77,8,2,1,3,
  	1,3,1,3,5,3,82,8,3,10,3,12,3,85,9,3,3,3,87,8,3,1,4,1,4,1,5,1,5,1,6,1,
  	6,3,6,95,8,6,1,7,1,7,1,8,1,8,1,8,0,0,9,0,2,4,6,8,10,12,14,16,0,0,108,
  	0,18,1,0,0,0,2,64,1,0,0,0,4,76,1,0,0,0,6,86,1,0,0,0,8,88,1,0,0,0,10,90,
  	1,0,0,0,12,94,1,0,0,0,14,96,1,0,0,0,16,98,1,0,0,0,18,19,3,2,1,0,19,20,
  	5,0,0,1,20,1,1,0,0,0,21,25,5,22,0,0,22,24,3,2,1,0,23,22,1,0,0,0,24,27,
  	1,0,0,0,25,23,1,0,0,0,25,26,1,0,0,0,26,28,1,0,0,0,27,25,1,0,0,0,28,65,
  	5,23,0,0,29,30,3,4,2,0,30,31,5,16,0,0,31,65,1,0,0,0,32,33,5,1,0,0,33,
  	37,5,15,0,0,34,35,3,16,8,0,35,36,3,4,2,0,36,38,1,0,0,0,37,34,1,0,0,0,
  	37,38,1,0,0,0,38,39,1,0,0,0,39,65,5,16,0,0,40,41,3,14,7,0,41,42,3,16,
  	8,0,42,43,3,4,2,0,43,44,5,16,0,0,44,65,1,0,0,0,45,46,5,2,0,0,46,47,3,
  	4,2,0,47,48,5,3,0,0,48,51,3,2,1,0,49,50,5,4,0,0,50,52,3,2,1,0,51,49,1,
  	0,0,0,51,52,1,0,0,0,52,65,1,0,0,0,53,54,5,5,0,0,54,65,3,2,1,0,55,56,5,
  	6,0,0,56,65,5,16,0,0,57,58,5,7,0,0,58,65,5,16,0,0,59,60,5,8,0,0,60,61,
  	3,4,2,0,61,62,5,9,0,0,62,63,3,2,1,0,63,65,1,0,0,0,64,21,1,0,0,0,64,29,
  	1,0,0,0,64,32,1,0,0,0,64,40,1,0,0,0,64,45,1,0,0,0,64,53,1,0,0,0,64,55,
  	1,0,0,0,64,57,1,0,0,0,64,59,1,0,0,0,65,3,1,0,0,0,66,67,3,14,7,0,67,68,
  	5,20,0,0,68,69,3,6,3,0,69,70,5,21,0,0,70,77,1,0,0,0,71,77,3,14,7,0,72,
  	77,3,10,5,0,73,74,3,8,4,0,74,75,3,4,2,0,75,77,1,0,0,0,76,66,1,0,0,0,76,
  	71,1,0,0,0,76,72,1,0,0,0,76,73,1,0,0,0,77,5,1,0,0,0,78,83,3,4,2,0,79,
  	80,5,10,0,0,80,82,3,4,2,0,81,79,1,0,0,0,82,85,1,0,0,0,83,81,1,0,0,0,83,
  	84,1,0,0,0,84,87,1,0,0,0,85,83,1,0,0,0,86,78,1,0,0,0,86,87,1,0,0,0,87,
  	7,1,0,0,0,88,89,5,11,0,0,89,9,1,0,0,0,90,91,3,12,6,0,91,11,1,0,0,0,92,
  	95,5,12,0,0,93,95,5,13,0,0,94,92,1,0,0,0,94,93,1,0,0,0,95,13,1,0,0,0,
  	96,97,5,15,0,0,97,15,1,0,0,0,98,99,5,14,0,0,99,17,1,0,0,0,8,25,37,51,
  	64,76,83,86,94
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
    setState(18);
    statement();
    setState(19);
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

anceParser::AssignerContext* anceParser::LetStatementContext::assigner() {
  return getRuleContext<anceParser::AssignerContext>(0);
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
    setState(64);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::BlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(21);
      match(anceParser::CURLY_BRACKET_OPEN);
      setState(25);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << anceParser::T__0)
        | (1ULL << anceParser::T__1)
        | (1ULL << anceParser::T__4)
        | (1ULL << anceParser::T__5)
        | (1ULL << anceParser::T__6)
        | (1ULL << anceParser::T__7)
        | (1ULL << anceParser::T__10)
        | (1ULL << anceParser::T__11)
        | (1ULL << anceParser::T__12)
        | (1ULL << anceParser::IDENTIFIER)
        | (1ULL << anceParser::CURLY_BRACKET_OPEN))) != 0)) {
        setState(22);
        statement();
        setState(27);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(28);
      match(anceParser::CURLY_BRACKET_CLOSE);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::ExpressionStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(29);
      expression();
      setState(30);
      match(anceParser::SEMICOLON);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<anceParser::LetStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(32);
      match(anceParser::T__0);
      setState(33);
      match(anceParser::IDENTIFIER);
      setState(37);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == anceParser::T__13) {
        setState(34);
        assigner();
        setState(35);
        expression();
      }
      setState(39);
      match(anceParser::SEMICOLON);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<anceParser::AssignmentStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(40);
      entity();
      setState(41);
      assigner();
      setState(42);
      expression();
      setState(43);
      match(anceParser::SEMICOLON);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<anceParser::IfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(45);
      match(anceParser::T__1);
      setState(46);
      expression();
      setState(47);
      match(anceParser::T__2);
      setState(48);
      antlrcpp::downCast<IfStatementContext *>(_localctx)->trueBlock = statement();
      setState(51);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(49);
        match(anceParser::T__3);
        setState(50);
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
      setState(53);
      match(anceParser::T__4);
      setState(54);
      statement();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<anceParser::BreakStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(55);
      match(anceParser::T__5);
      setState(56);
      match(anceParser::SEMICOLON);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<anceParser::ContinueStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(57);
      match(anceParser::T__6);
      setState(58);
      match(anceParser::SEMICOLON);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<anceParser::WhileStatementContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(59);
      match(anceParser::T__7);
      setState(60);
      expression();
      setState(61);
      match(anceParser::T__8);
      setState(62);
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

anceParser::ArgumentsContext* anceParser::CallExpressionContext::arguments() {
  return getRuleContext<anceParser::ArgumentsContext>(0);
}

tree::TerminalNode* anceParser::CallExpressionContext::BRACKET_CLOSE() {
  return getToken(anceParser::BRACKET_CLOSE, 0);
}

anceParser::CallExpressionContext::CallExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::CallExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitCallExpression(this);
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
    setState(76);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::CallExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(66);
      entity();
      setState(67);
      match(anceParser::BRACKET_OPEN);
      setState(68);
      arguments();
      setState(69);
      match(anceParser::BRACKET_CLOSE);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::AccessExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(71);
      entity();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<anceParser::LiteralExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(72);
      literal();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<anceParser::UnaryOperationExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(73);
      unary();
      setState(74);
      expression();
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
    setState(86);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__10)
      | (1ULL << anceParser::T__11)
      | (1ULL << anceParser::T__12)
      | (1ULL << anceParser::IDENTIFIER))) != 0)) {
      setState(78);
      expression();
      setState(83);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__9) {
        setState(79);
        match(anceParser::T__9);
        setState(80);
        expression();
        setState(85);
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
    setState(88);
    match(anceParser::T__10);
   
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
    _localctx = _tracker.createInstance<anceParser::BooleanLiteralContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(90);
    boolean();
   
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
  enterRule(_localctx, 12, anceParser::RuleBoolean);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(94);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__11: {
        _localctx = _tracker.createInstance<anceParser::TrueContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(92);
        match(anceParser::T__11);
        break;
      }

      case anceParser::T__12: {
        _localctx = _tracker.createInstance<anceParser::FalseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(93);
        match(anceParser::T__12);
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
  enterRule(_localctx, 14, anceParser::RuleEntity);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
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
  enterRule(_localctx, 16, anceParser::RuleAssigner);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(98);
    match(anceParser::T__13);
   
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
