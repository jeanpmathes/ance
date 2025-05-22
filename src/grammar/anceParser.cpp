
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
      "file", "statement", "expression", "type", "unary", "literal", "boolean", 
      "entity", "assigner"
    },
    std::vector<std::string>{
      "", "'let'", "':'", "'if'", "'then'", "'else'", "'loop'", "'break'", 
      "'continue'", "'while'", "'do'", "','", "'Bool'", "'Unit'", "'Size'", 
      "'not'", "'true'", "'false'", "'<:'", "", "';'", "", "", "", "'('", 
      "')'", "'{'", "'}'", "'['", "']'", "'<'", "'>'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "IDENTIFIER", "SEMICOLON", "WHITESPACE", "BLOCK_COMMENT", 
      "LINE_COMMENT", "BRACKET_OPEN", "BRACKET_CLOSE", "CURLY_BRACKET_OPEN", 
      "CURLY_BRACKET_CLOSE", "SQUARE_BRACKET_OPEN", "SQUARE_BRACKET_CLOSE", 
      "POINTY_BRACKET_OPEN", "POINTY_BRACKET_CLOSE", "ERROR_CHAR"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,32,108,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,1,0,1,0,1,0,1,1,1,1,5,1,24,8,1,10,1,12,1,27,9,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,40,8,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,55,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,3,1,68,8,1,1,2,1,2,1,2,1,2,1,2,5,2,75,8,2,10,2,12,2,78,
  	9,2,3,2,80,8,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,89,8,2,1,3,1,3,1,3,3,3,
  	94,8,3,1,4,1,4,1,5,1,5,1,6,1,6,3,6,102,8,6,1,7,1,7,1,8,1,8,1,8,0,0,9,
  	0,2,4,6,8,10,12,14,16,0,0,117,0,18,1,0,0,0,2,67,1,0,0,0,4,88,1,0,0,0,
  	6,93,1,0,0,0,8,95,1,0,0,0,10,97,1,0,0,0,12,101,1,0,0,0,14,103,1,0,0,0,
  	16,105,1,0,0,0,18,19,3,2,1,0,19,20,5,0,0,1,20,1,1,0,0,0,21,25,5,26,0,
  	0,22,24,3,2,1,0,23,22,1,0,0,0,24,27,1,0,0,0,25,23,1,0,0,0,25,26,1,0,0,
  	0,26,28,1,0,0,0,27,25,1,0,0,0,28,68,5,27,0,0,29,30,3,4,2,0,30,31,5,20,
  	0,0,31,68,1,0,0,0,32,33,5,1,0,0,33,34,5,19,0,0,34,35,5,2,0,0,35,39,3,
  	6,3,0,36,37,3,16,8,0,37,38,3,4,2,0,38,40,1,0,0,0,39,36,1,0,0,0,39,40,
  	1,0,0,0,40,41,1,0,0,0,41,42,5,20,0,0,42,68,1,0,0,0,43,44,3,14,7,0,44,
  	45,3,16,8,0,45,46,3,4,2,0,46,47,5,20,0,0,47,68,1,0,0,0,48,49,5,3,0,0,
  	49,50,3,4,2,0,50,51,5,4,0,0,51,54,3,2,1,0,52,53,5,5,0,0,53,55,3,2,1,0,
  	54,52,1,0,0,0,54,55,1,0,0,0,55,68,1,0,0,0,56,57,5,6,0,0,57,68,3,2,1,0,
  	58,59,5,7,0,0,59,68,5,20,0,0,60,61,5,8,0,0,61,68,5,20,0,0,62,63,5,9,0,
  	0,63,64,3,4,2,0,64,65,5,10,0,0,65,66,3,2,1,0,66,68,1,0,0,0,67,21,1,0,
  	0,0,67,29,1,0,0,0,67,32,1,0,0,0,67,43,1,0,0,0,67,48,1,0,0,0,67,56,1,0,
  	0,0,67,58,1,0,0,0,67,60,1,0,0,0,67,62,1,0,0,0,68,3,1,0,0,0,69,70,3,14,
  	7,0,70,79,5,24,0,0,71,76,3,4,2,0,72,73,5,11,0,0,73,75,3,4,2,0,74,72,1,
  	0,0,0,75,78,1,0,0,0,76,74,1,0,0,0,76,77,1,0,0,0,77,80,1,0,0,0,78,76,1,
  	0,0,0,79,71,1,0,0,0,79,80,1,0,0,0,80,81,1,0,0,0,81,82,5,25,0,0,82,89,
  	1,0,0,0,83,89,3,14,7,0,84,89,3,10,5,0,85,86,3,8,4,0,86,87,3,4,2,0,87,
  	89,1,0,0,0,88,69,1,0,0,0,88,83,1,0,0,0,88,84,1,0,0,0,88,85,1,0,0,0,89,
  	5,1,0,0,0,90,94,5,12,0,0,91,94,5,13,0,0,92,94,5,14,0,0,93,90,1,0,0,0,
  	93,91,1,0,0,0,93,92,1,0,0,0,94,7,1,0,0,0,95,96,5,15,0,0,96,9,1,0,0,0,
  	97,98,3,12,6,0,98,11,1,0,0,0,99,102,5,16,0,0,100,102,5,17,0,0,101,99,
  	1,0,0,0,101,100,1,0,0,0,102,13,1,0,0,0,103,104,5,19,0,0,104,15,1,0,0,
  	0,105,106,5,18,0,0,106,17,1,0,0,0,9,25,39,54,67,76,79,88,93,101
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

anceParser::TypeContext* anceParser::LetStatementContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
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
    setState(67);
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
        | (1ULL << anceParser::T__2)
        | (1ULL << anceParser::T__5)
        | (1ULL << anceParser::T__6)
        | (1ULL << anceParser::T__7)
        | (1ULL << anceParser::T__8)
        | (1ULL << anceParser::T__14)
        | (1ULL << anceParser::T__15)
        | (1ULL << anceParser::T__16)
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
      setState(34);
      match(anceParser::T__1);
      setState(35);
      type();
      setState(39);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == anceParser::T__17) {
        setState(36);
        assigner();
        setState(37);
        expression();
      }
      setState(41);
      match(anceParser::SEMICOLON);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<anceParser::AssignmentStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(43);
      entity();
      setState(44);
      assigner();
      setState(45);
      expression();
      setState(46);
      match(anceParser::SEMICOLON);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<anceParser::IfStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(48);
      match(anceParser::T__2);
      setState(49);
      expression();
      setState(50);
      match(anceParser::T__3);
      setState(51);
      antlrcpp::downCast<IfStatementContext *>(_localctx)->trueBlock = statement();
      setState(54);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(52);
        match(anceParser::T__4);
        setState(53);
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
      setState(56);
      match(anceParser::T__5);
      setState(57);
      statement();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<anceParser::BreakStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(58);
      match(anceParser::T__6);
      setState(59);
      match(anceParser::SEMICOLON);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<anceParser::ContinueStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(60);
      match(anceParser::T__7);
      setState(61);
      match(anceParser::SEMICOLON);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<anceParser::WhileStatementContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(62);
      match(anceParser::T__8);
      setState(63);
      expression();
      setState(64);
      match(anceParser::T__9);
      setState(65);
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
anceParser::ExpressionContext* anceParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 4, anceParser::RuleExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(88);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::CallExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(69);
      entity();
      setState(70);
      match(anceParser::BRACKET_OPEN);
      setState(79);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << anceParser::T__14)
        | (1ULL << anceParser::T__15)
        | (1ULL << anceParser::T__16)
        | (1ULL << anceParser::IDENTIFIER))) != 0)) {
        setState(71);
        expression();
        setState(76);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__10) {
          setState(72);
          match(anceParser::T__10);
          setState(73);
          expression();
          setState(78);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(81);
      match(anceParser::BRACKET_CLOSE);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::AccessExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(83);
      entity();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<anceParser::LiteralExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(84);
      literal();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<anceParser::UnaryOperationExpressionContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(85);
      unary();
      setState(86);
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
anceParser::TypeContext* anceParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 6, anceParser::RuleType);

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
    switch (_input->LA(1)) {
      case anceParser::T__11: {
        _localctx = _tracker.createInstance<anceParser::BoolTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(90);
        match(anceParser::T__11);
        break;
      }

      case anceParser::T__12: {
        _localctx = _tracker.createInstance<anceParser::UnitTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(91);
        match(anceParser::T__12);
        break;
      }

      case anceParser::T__13: {
        _localctx = _tracker.createInstance<anceParser::SizeTypeContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(92);
        match(anceParser::T__13);
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
    match(anceParser::T__14);
   
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
    setState(97);
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
    setState(101);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__15: {
        _localctx = _tracker.createInstance<anceParser::TrueContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(99);
        match(anceParser::T__15);
        break;
      }

      case anceParser::T__16: {
        _localctx = _tracker.createInstance<anceParser::FalseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(100);
        match(anceParser::T__16);
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
    setState(103);
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
    setState(105);
    match(anceParser::T__17);
   
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
