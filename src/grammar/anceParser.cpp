
// Generated from ./src/grammar/ance.g4 by ANTLR 4.8


#include "anceVisitor.h"

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

std::vector<anceParser::DataContext *> anceParser::FileContext::data() {
  return getRuleContexts<anceParser::DataContext>();
}

anceParser::DataContext* anceParser::FileContext::data(size_t i) {
  return getRuleContext<anceParser::DataContext>(i);
}

std::vector<anceParser::CodeContext *> anceParser::FileContext::code() {
  return getRuleContexts<anceParser::CodeContext>();
}

anceParser::CodeContext* anceParser::FileContext::code(size_t i) {
  return getRuleContext<anceParser::CodeContext>(i);
}


size_t anceParser::FileContext::getRuleIndex() const {
  return anceParser::RuleFile;
}


antlrcpp::Any anceParser::FileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFile(this);
  else
    return visitor->visitChildren(this);
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
    setState(90);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == anceParser::PUBLIC

    || _la == anceParser::PRIVATE) {
      setState(88);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(86);
        data();
        break;
      }

      case 2: {
        setState(87);
        code();
        break;
      }

      }
      setState(92);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DataContext ------------------------------------------------------------------

anceParser::DataContext::DataContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ConstantDeclarationContext* anceParser::DataContext::constantDeclaration() {
  return getRuleContext<anceParser::ConstantDeclarationContext>(0);
}

anceParser::VariableDeclarationContext* anceParser::DataContext::variableDeclaration() {
  return getRuleContext<anceParser::VariableDeclarationContext>(0);
}


size_t anceParser::DataContext::getRuleIndex() const {
  return anceParser::RuleData;
}


antlrcpp::Any anceParser::DataContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitData(this);
  else
    return visitor->visitChildren(this);
}

anceParser::DataContext* anceParser::data() {
  DataContext *_localctx = _tracker.createInstance<DataContext>(_ctx, getState());
  enterRule(_localctx, 2, anceParser::RuleData);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(95);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(93);
      constantDeclaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(94);
      variableDeclaration();
      break;
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

//----------------- ConstantDeclarationContext ------------------------------------------------------------------

anceParser::ConstantDeclarationContext::ConstantDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AccessModifierContext* anceParser::ConstantDeclarationContext::accessModifier() {
  return getRuleContext<anceParser::AccessModifierContext>(0);
}

anceParser::TypeContext* anceParser::ConstantDeclarationContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::ConstantDeclarationContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::LiteralExpressionContext* anceParser::ConstantDeclarationContext::literalExpression() {
  return getRuleContext<anceParser::LiteralExpressionContext>(0);
}


size_t anceParser::ConstantDeclarationContext::getRuleIndex() const {
  return anceParser::RuleConstantDeclaration;
}


antlrcpp::Any anceParser::ConstantDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitConstantDeclaration(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ConstantDeclarationContext* anceParser::constantDeclaration() {
  ConstantDeclarationContext *_localctx = _tracker.createInstance<ConstantDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, anceParser::RuleConstantDeclaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(97);
    accessModifier();
    setState(98);
    match(anceParser::T__0);
    setState(99);
    type(0);
    setState(100);
    match(anceParser::IDENTIFIER);
    setState(101);
    match(anceParser::T__1);
    setState(102);
    literalExpression();
    setState(103);
    match(anceParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

anceParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AccessModifierContext* anceParser::VariableDeclarationContext::accessModifier() {
  return getRuleContext<anceParser::AccessModifierContext>(0);
}

anceParser::TypeContext* anceParser::VariableDeclarationContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::VariableDeclarationContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::LiteralExpressionContext* anceParser::VariableDeclarationContext::literalExpression() {
  return getRuleContext<anceParser::LiteralExpressionContext>(0);
}


size_t anceParser::VariableDeclarationContext::getRuleIndex() const {
  return anceParser::RuleVariableDeclaration;
}


antlrcpp::Any anceParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

anceParser::VariableDeclarationContext* anceParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 6, anceParser::RuleVariableDeclaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(105);
    accessModifier();
    setState(106);
    type(0);
    setState(107);
    match(anceParser::IDENTIFIER);
    setState(110);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__3) {
      setState(108);
      match(anceParser::T__3);
      setState(109);
      literalExpression();
    }
    setState(112);
    match(anceParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CodeContext ------------------------------------------------------------------

anceParser::CodeContext::CodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::FunctionContext* anceParser::CodeContext::function() {
  return getRuleContext<anceParser::FunctionContext>(0);
}


size_t anceParser::CodeContext::getRuleIndex() const {
  return anceParser::RuleCode;
}


antlrcpp::Any anceParser::CodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitCode(this);
  else
    return visitor->visitChildren(this);
}

anceParser::CodeContext* anceParser::code() {
  CodeContext *_localctx = _tracker.createInstance<CodeContext>(_ctx, getState());
  enterRule(_localctx, 8, anceParser::RuleCode);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(114);
    function();
   
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

anceParser::AccessModifierContext* anceParser::FunctionContext::accessModifier() {
  return getRuleContext<anceParser::AccessModifierContext>(0);
}

anceParser::TypeContext* anceParser::FunctionContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::FunctionContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ParametersContext* anceParser::FunctionContext::parameters() {
  return getRuleContext<anceParser::ParametersContext>(0);
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


antlrcpp::Any anceParser::FunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFunction(this);
  else
    return visitor->visitChildren(this);
}

anceParser::FunctionContext* anceParser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 10, anceParser::RuleFunction);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    accessModifier();
    setState(117);
    type(0);
    setState(118);
    match(anceParser::IDENTIFIER);
    setState(119);
    match(anceParser::T__4);
    setState(120);
    parameters();
    setState(121);
    match(anceParser::T__5);
    setState(122);
    match(anceParser::T__6);
    setState(124); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(123);
      statement();
      setState(126); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__9)
      | (1ULL << anceParser::T__10)
      | (1ULL << anceParser::T__11)
      | (1ULL << anceParser::T__16)
      | (1ULL << anceParser::T__18)
      | (1ULL << anceParser::T__19)
      | (1ULL << anceParser::T__20)
      | (1ULL << anceParser::NATIVE_INTEGER_TYPE)
      | (1ULL << anceParser::HALF_TYPE)
      | (1ULL << anceParser::SINGLE_TYPE)
      | (1ULL << anceParser::DOUBLE_TYPE)
      | (1ULL << anceParser::QUAD_TYPE)
      | (1ULL << anceParser::IDENTIFIER))) != 0));
    setState(128);
    match(anceParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParametersContext ------------------------------------------------------------------

anceParser::ParametersContext::ParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<anceParser::ParameterContext *> anceParser::ParametersContext::parameter() {
  return getRuleContexts<anceParser::ParameterContext>();
}

anceParser::ParameterContext* anceParser::ParametersContext::parameter(size_t i) {
  return getRuleContext<anceParser::ParameterContext>(i);
}


size_t anceParser::ParametersContext::getRuleIndex() const {
  return anceParser::RuleParameters;
}


antlrcpp::Any anceParser::ParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitParameters(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ParametersContext* anceParser::parameters() {
  ParametersContext *_localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
  enterRule(_localctx, 12, anceParser::RuleParameters);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(138);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__16)
      | (1ULL << anceParser::T__18)
      | (1ULL << anceParser::T__19)
      | (1ULL << anceParser::T__20)
      | (1ULL << anceParser::NATIVE_INTEGER_TYPE)
      | (1ULL << anceParser::HALF_TYPE)
      | (1ULL << anceParser::SINGLE_TYPE)
      | (1ULL << anceParser::DOUBLE_TYPE)
      | (1ULL << anceParser::QUAD_TYPE))) != 0)) {
      setState(130);
      parameter();
      setState(135);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__8) {
        setState(131);
        match(anceParser::T__8);
        setState(132);
        parameter();
        setState(137);
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

//----------------- ParameterContext ------------------------------------------------------------------

anceParser::ParameterContext::ParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::TypeContext* anceParser::ParameterContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::ParameterContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}


size_t anceParser::ParameterContext::getRuleIndex() const {
  return anceParser::RuleParameter;
}


antlrcpp::Any anceParser::ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ParameterContext* anceParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 14, anceParser::RuleParameter);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(140);
    type(0);
    setState(141);
    match(anceParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AccessModifierContext ------------------------------------------------------------------

anceParser::AccessModifierContext::AccessModifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::AccessModifierContext::PUBLIC() {
  return getToken(anceParser::PUBLIC, 0);
}

tree::TerminalNode* anceParser::AccessModifierContext::PRIVATE() {
  return getToken(anceParser::PRIVATE, 0);
}


size_t anceParser::AccessModifierContext::getRuleIndex() const {
  return anceParser::RuleAccessModifier;
}


antlrcpp::Any anceParser::AccessModifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAccessModifier(this);
  else
    return visitor->visitChildren(this);
}

anceParser::AccessModifierContext* anceParser::accessModifier() {
  AccessModifierContext *_localctx = _tracker.createInstance<AccessModifierContext>(_ctx, getState());
  enterRule(_localctx, 16, anceParser::RuleAccessModifier);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    _la = _input->LA(1);
    if (!(_la == anceParser::PUBLIC

    || _la == anceParser::PRIVATE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
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

anceParser::ExpressionStatementContext* anceParser::StatementContext::expressionStatement() {
  return getRuleContext<anceParser::ExpressionStatementContext>(0);
}

anceParser::LocalVariableDefinitionContext* anceParser::StatementContext::localVariableDefinition() {
  return getRuleContext<anceParser::LocalVariableDefinitionContext>(0);
}

anceParser::VariableAssignmentContext* anceParser::StatementContext::variableAssignment() {
  return getRuleContext<anceParser::VariableAssignmentContext>(0);
}

anceParser::PrintStatementContext* anceParser::StatementContext::printStatement() {
  return getRuleContext<anceParser::PrintStatementContext>(0);
}

anceParser::DeleteStatementContext* anceParser::StatementContext::deleteStatement() {
  return getRuleContext<anceParser::DeleteStatementContext>(0);
}

anceParser::ReturnStatementContext* anceParser::StatementContext::returnStatement() {
  return getRuleContext<anceParser::ReturnStatementContext>(0);
}


size_t anceParser::StatementContext::getRuleIndex() const {
  return anceParser::RuleStatement;
}


antlrcpp::Any anceParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::StatementContext* anceParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 18, anceParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(151);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(145);
      expressionStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(146);
      localVariableDefinition();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(147);
      variableAssignment();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(148);
      printStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(149);
      deleteStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(150);
      returnStatement();
      break;
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

//----------------- ExpressionStatementContext ------------------------------------------------------------------

anceParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::IndependentExpressionContext* anceParser::ExpressionStatementContext::independentExpression() {
  return getRuleContext<anceParser::IndependentExpressionContext>(0);
}


size_t anceParser::ExpressionStatementContext::getRuleIndex() const {
  return anceParser::RuleExpressionStatement;
}


antlrcpp::Any anceParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ExpressionStatementContext* anceParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, anceParser::RuleExpressionStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
    independentExpression();
    setState(154);
    match(anceParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocalVariableDefinitionContext ------------------------------------------------------------------

anceParser::LocalVariableDefinitionContext::LocalVariableDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::TypeContext* anceParser::LocalVariableDefinitionContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::LocalVariableDefinitionContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ExpressionContext* anceParser::LocalVariableDefinitionContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::LocalVariableDefinitionContext::getRuleIndex() const {
  return anceParser::RuleLocalVariableDefinition;
}


antlrcpp::Any anceParser::LocalVariableDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLocalVariableDefinition(this);
  else
    return visitor->visitChildren(this);
}

anceParser::LocalVariableDefinitionContext* anceParser::localVariableDefinition() {
  LocalVariableDefinitionContext *_localctx = _tracker.createInstance<LocalVariableDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 22, anceParser::RuleLocalVariableDefinition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(156);
    type(0);
    setState(157);
    match(anceParser::IDENTIFIER);
    setState(160);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__3) {
      setState(158);
      match(anceParser::T__3);
      setState(159);
      expression();
    }
    setState(162);
    match(anceParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableAssignmentContext ------------------------------------------------------------------

anceParser::VariableAssignmentContext::VariableAssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::VariableAssignmentContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ExpressionContext* anceParser::VariableAssignmentContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::VariableAssignmentContext::getRuleIndex() const {
  return anceParser::RuleVariableAssignment;
}


antlrcpp::Any anceParser::VariableAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVariableAssignment(this);
  else
    return visitor->visitChildren(this);
}

anceParser::VariableAssignmentContext* anceParser::variableAssignment() {
  VariableAssignmentContext *_localctx = _tracker.createInstance<VariableAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 24, anceParser::RuleVariableAssignment);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(164);
    match(anceParser::IDENTIFIER);
    setState(165);
    match(anceParser::T__3);
    setState(166);
    expression();
    setState(167);
    match(anceParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrintStatementContext ------------------------------------------------------------------

anceParser::PrintStatementContext::PrintStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ExpressionContext* anceParser::PrintStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::PrintStatementContext::getRuleIndex() const {
  return anceParser::RulePrintStatement;
}


antlrcpp::Any anceParser::PrintStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitPrintStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::PrintStatementContext* anceParser::printStatement() {
  PrintStatementContext *_localctx = _tracker.createInstance<PrintStatementContext>(_ctx, getState());
  enterRule(_localctx, 26, anceParser::RulePrintStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(169);
    match(anceParser::T__9);
    setState(170);
    expression();
    setState(171);
    match(anceParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeleteStatementContext ------------------------------------------------------------------

anceParser::DeleteStatementContext::DeleteStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ExpressionContext* anceParser::DeleteStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::DeleteStatementContext::getRuleIndex() const {
  return anceParser::RuleDeleteStatement;
}


antlrcpp::Any anceParser::DeleteStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitDeleteStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::DeleteStatementContext* anceParser::deleteStatement() {
  DeleteStatementContext *_localctx = _tracker.createInstance<DeleteStatementContext>(_ctx, getState());
  enterRule(_localctx, 28, anceParser::RuleDeleteStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(173);
    match(anceParser::T__10);
    setState(174);
    expression();
    setState(175);
    match(anceParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

anceParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ExpressionContext* anceParser::ReturnStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::ReturnStatementContext::getRuleIndex() const {
  return anceParser::RuleReturnStatement;
}


antlrcpp::Any anceParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ReturnStatementContext* anceParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 30, anceParser::RuleReturnStatement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(177);
    match(anceParser::T__11);
    setState(179);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__6)
      | (1ULL << anceParser::T__12)
      | (1ULL << anceParser::T__13)
      | (1ULL << anceParser::SIGNED_INTEGER)
      | (1ULL << anceParser::HEX_INTEGER)
      | (1ULL << anceParser::BIN_INTEGER)
      | (1ULL << anceParser::OCT_INTEGER)
      | (1ULL << anceParser::HALF)
      | (1ULL << anceParser::SINGLE)
      | (1ULL << anceParser::DOUBLE)
      | (1ULL << anceParser::QUAD)
      | (1ULL << anceParser::STRING)
      | (1ULL << anceParser::BYTE)
      | (1ULL << anceParser::INTEGER)
      | (1ULL << anceParser::TRUE)
      | (1ULL << anceParser::FALSE)
      | (1ULL << anceParser::IDENTIFIER))) != 0)) {
      setState(178);
      expression();
    }
    setState(181);
    match(anceParser::T__2);
   
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

anceParser::VariableAccessContext* anceParser::ExpressionContext::variableAccess() {
  return getRuleContext<anceParser::VariableAccessContext>(0);
}

anceParser::AllocationContext* anceParser::ExpressionContext::allocation() {
  return getRuleContext<anceParser::AllocationContext>(0);
}

anceParser::RoughCastContext* anceParser::ExpressionContext::roughCast() {
  return getRuleContext<anceParser::RoughCastContext>(0);
}

anceParser::SizeofTypeContext* anceParser::ExpressionContext::sizeofType() {
  return getRuleContext<anceParser::SizeofTypeContext>(0);
}

anceParser::SizeofExpressionContext* anceParser::ExpressionContext::sizeofExpression() {
  return getRuleContext<anceParser::SizeofExpressionContext>(0);
}

anceParser::LiteralExpressionContext* anceParser::ExpressionContext::literalExpression() {
  return getRuleContext<anceParser::LiteralExpressionContext>(0);
}

anceParser::IndependentExpressionContext* anceParser::ExpressionContext::independentExpression() {
  return getRuleContext<anceParser::IndependentExpressionContext>(0);
}


size_t anceParser::ExpressionContext::getRuleIndex() const {
  return anceParser::RuleExpression;
}


antlrcpp::Any anceParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ExpressionContext* anceParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 32, anceParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(190);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(183);
      variableAccess();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(184);
      allocation();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(185);
      roughCast();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(186);
      sizeofType();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(187);
      sizeofExpression();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(188);
      literalExpression();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(189);
      independentExpression();
      break;
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

//----------------- IndependentExpressionContext ------------------------------------------------------------------

anceParser::IndependentExpressionContext::IndependentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::FunctionCallContext* anceParser::IndependentExpressionContext::functionCall() {
  return getRuleContext<anceParser::FunctionCallContext>(0);
}


size_t anceParser::IndependentExpressionContext::getRuleIndex() const {
  return anceParser::RuleIndependentExpression;
}


antlrcpp::Any anceParser::IndependentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitIndependentExpression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::IndependentExpressionContext* anceParser::independentExpression() {
  IndependentExpressionContext *_localctx = _tracker.createInstance<IndependentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 34, anceParser::RuleIndependentExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(192);
    functionCall();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

anceParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::FunctionCallContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ArgumentsContext* anceParser::FunctionCallContext::arguments() {
  return getRuleContext<anceParser::ArgumentsContext>(0);
}


size_t anceParser::FunctionCallContext::getRuleIndex() const {
  return anceParser::RuleFunctionCall;
}


antlrcpp::Any anceParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

anceParser::FunctionCallContext* anceParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 36, anceParser::RuleFunctionCall);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(194);
    match(anceParser::IDENTIFIER);
    setState(195);
    match(anceParser::T__4);
    setState(196);
    arguments();
    setState(197);
    match(anceParser::T__5);
   
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


antlrcpp::Any anceParser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ArgumentsContext* anceParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 38, anceParser::RuleArguments);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(207);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__6)
      | (1ULL << anceParser::T__12)
      | (1ULL << anceParser::T__13)
      | (1ULL << anceParser::SIGNED_INTEGER)
      | (1ULL << anceParser::HEX_INTEGER)
      | (1ULL << anceParser::BIN_INTEGER)
      | (1ULL << anceParser::OCT_INTEGER)
      | (1ULL << anceParser::HALF)
      | (1ULL << anceParser::SINGLE)
      | (1ULL << anceParser::DOUBLE)
      | (1ULL << anceParser::QUAD)
      | (1ULL << anceParser::STRING)
      | (1ULL << anceParser::BYTE)
      | (1ULL << anceParser::INTEGER)
      | (1ULL << anceParser::TRUE)
      | (1ULL << anceParser::FALSE)
      | (1ULL << anceParser::IDENTIFIER))) != 0)) {
      setState(199);
      expression();
      setState(204);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__8) {
        setState(200);
        match(anceParser::T__8);
        setState(201);
        expression();
        setState(206);
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

//----------------- VariableAccessContext ------------------------------------------------------------------

anceParser::VariableAccessContext::VariableAccessContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::VariableAccessContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}


size_t anceParser::VariableAccessContext::getRuleIndex() const {
  return anceParser::RuleVariableAccess;
}


antlrcpp::Any anceParser::VariableAccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVariableAccess(this);
  else
    return visitor->visitChildren(this);
}

anceParser::VariableAccessContext* anceParser::variableAccess() {
  VariableAccessContext *_localctx = _tracker.createInstance<VariableAccessContext>(_ctx, getState());
  enterRule(_localctx, 40, anceParser::RuleVariableAccess);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(209);
    match(anceParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AllocationContext ------------------------------------------------------------------

anceParser::AllocationContext::AllocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AllocatorContext* anceParser::AllocationContext::allocator() {
  return getRuleContext<anceParser::AllocatorContext>(0);
}

anceParser::TypeContext* anceParser::AllocationContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}


size_t anceParser::AllocationContext::getRuleIndex() const {
  return anceParser::RuleAllocation;
}


antlrcpp::Any anceParser::AllocationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAllocation(this);
  else
    return visitor->visitChildren(this);
}

anceParser::AllocationContext* anceParser::allocation() {
  AllocationContext *_localctx = _tracker.createInstance<AllocationContext>(_ctx, getState());
  enterRule(_localctx, 42, anceParser::RuleAllocation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(211);
    match(anceParser::T__12);
    setState(212);
    allocator();
    setState(213);
    type(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AllocatorContext ------------------------------------------------------------------

anceParser::AllocatorContext::AllocatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::AllocatorContext::DYNAMIC() {
  return getToken(anceParser::DYNAMIC, 0);
}

tree::TerminalNode* anceParser::AllocatorContext::AUTOMATIC() {
  return getToken(anceParser::AUTOMATIC, 0);
}


size_t anceParser::AllocatorContext::getRuleIndex() const {
  return anceParser::RuleAllocator;
}


antlrcpp::Any anceParser::AllocatorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAllocator(this);
  else
    return visitor->visitChildren(this);
}

anceParser::AllocatorContext* anceParser::allocator() {
  AllocatorContext *_localctx = _tracker.createInstance<AllocatorContext>(_ctx, getState());
  enterRule(_localctx, 44, anceParser::RuleAllocator);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(215);
    _la = _input->LA(1);
    if (!(_la == anceParser::DYNAMIC

    || _la == anceParser::AUTOMATIC)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RoughCastContext ------------------------------------------------------------------

anceParser::RoughCastContext::RoughCastContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::TypeContext* anceParser::RoughCastContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::ExpressionContext* anceParser::RoughCastContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::RoughCastContext::getRuleIndex() const {
  return anceParser::RuleRoughCast;
}


antlrcpp::Any anceParser::RoughCastContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitRoughCast(this);
  else
    return visitor->visitChildren(this);
}

anceParser::RoughCastContext* anceParser::roughCast() {
  RoughCastContext *_localctx = _tracker.createInstance<RoughCastContext>(_ctx, getState());
  enterRule(_localctx, 46, anceParser::RuleRoughCast);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(217);
    match(anceParser::T__6);
    setState(218);
    type(0);
    setState(219);
    match(anceParser::T__7);
    setState(220);
    expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SizeofTypeContext ------------------------------------------------------------------

anceParser::SizeofTypeContext::SizeofTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::TypeContext* anceParser::SizeofTypeContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}


size_t anceParser::SizeofTypeContext::getRuleIndex() const {
  return anceParser::RuleSizeofType;
}


antlrcpp::Any anceParser::SizeofTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSizeofType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::SizeofTypeContext* anceParser::sizeofType() {
  SizeofTypeContext *_localctx = _tracker.createInstance<SizeofTypeContext>(_ctx, getState());
  enterRule(_localctx, 48, anceParser::RuleSizeofType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(222);
    match(anceParser::T__13);
    setState(223);
    type(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SizeofExpressionContext ------------------------------------------------------------------

anceParser::SizeofExpressionContext::SizeofExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ExpressionContext* anceParser::SizeofExpressionContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::SizeofExpressionContext::getRuleIndex() const {
  return anceParser::RuleSizeofExpression;
}


antlrcpp::Any anceParser::SizeofExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSizeofExpression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::SizeofExpressionContext* anceParser::sizeofExpression() {
  SizeofExpressionContext *_localctx = _tracker.createInstance<SizeofExpressionContext>(_ctx, getState());
  enterRule(_localctx, 50, anceParser::RuleSizeofExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(225);
    match(anceParser::T__13);
    setState(226);
    match(anceParser::T__4);
    setState(227);
    expression();
    setState(228);
    match(anceParser::T__5);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralExpressionContext ------------------------------------------------------------------

anceParser::LiteralExpressionContext::LiteralExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::StringLiteralContext* anceParser::LiteralExpressionContext::stringLiteral() {
  return getRuleContext<anceParser::StringLiteralContext>(0);
}

anceParser::ByteLiteralContext* anceParser::LiteralExpressionContext::byteLiteral() {
  return getRuleContext<anceParser::ByteLiteralContext>(0);
}

anceParser::IntegerLiteralContext* anceParser::LiteralExpressionContext::integerLiteral() {
  return getRuleContext<anceParser::IntegerLiteralContext>(0);
}

anceParser::FloatingPointLiteralContext* anceParser::LiteralExpressionContext::floatingPointLiteral() {
  return getRuleContext<anceParser::FloatingPointLiteralContext>(0);
}

anceParser::BooleanLiteralContext* anceParser::LiteralExpressionContext::booleanLiteral() {
  return getRuleContext<anceParser::BooleanLiteralContext>(0);
}


size_t anceParser::LiteralExpressionContext::getRuleIndex() const {
  return anceParser::RuleLiteralExpression;
}


antlrcpp::Any anceParser::LiteralExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLiteralExpression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::LiteralExpressionContext* anceParser::literalExpression() {
  LiteralExpressionContext *_localctx = _tracker.createInstance<LiteralExpressionContext>(_ctx, getState());
  enterRule(_localctx, 52, anceParser::RuleLiteralExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(235);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(230);
        stringLiteral();
        break;
      }

      case anceParser::BYTE: {
        enterOuterAlt(_localctx, 2);
        setState(231);
        byteLiteral();
        break;
      }

      case anceParser::SIGNED_INTEGER:
      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER:
      case anceParser::INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(232);
        integerLiteral();
        break;
      }

      case anceParser::HALF:
      case anceParser::SINGLE:
      case anceParser::DOUBLE:
      case anceParser::QUAD: {
        enterOuterAlt(_localctx, 4);
        setState(233);
        floatingPointLiteral();
        break;
      }

      case anceParser::TRUE:
      case anceParser::FALSE: {
        enterOuterAlt(_localctx, 5);
        setState(234);
        booleanLiteral();
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

//----------------- StringLiteralContext ------------------------------------------------------------------

anceParser::StringLiteralContext::StringLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::StringLiteralContext::STRING() {
  return getToken(anceParser::STRING, 0);
}


size_t anceParser::StringLiteralContext::getRuleIndex() const {
  return anceParser::RuleStringLiteral;
}


antlrcpp::Any anceParser::StringLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitStringLiteral(this);
  else
    return visitor->visitChildren(this);
}

anceParser::StringLiteralContext* anceParser::stringLiteral() {
  StringLiteralContext *_localctx = _tracker.createInstance<StringLiteralContext>(_ctx, getState());
  enterRule(_localctx, 54, anceParser::RuleStringLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(237);
    match(anceParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ByteLiteralContext ------------------------------------------------------------------

anceParser::ByteLiteralContext::ByteLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::ByteLiteralContext::BYTE() {
  return getToken(anceParser::BYTE, 0);
}


size_t anceParser::ByteLiteralContext::getRuleIndex() const {
  return anceParser::RuleByteLiteral;
}


antlrcpp::Any anceParser::ByteLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitByteLiteral(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ByteLiteralContext* anceParser::byteLiteral() {
  ByteLiteralContext *_localctx = _tracker.createInstance<ByteLiteralContext>(_ctx, getState());
  enterRule(_localctx, 56, anceParser::RuleByteLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(239);
    match(anceParser::BYTE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntegerLiteralContext ------------------------------------------------------------------

anceParser::IntegerLiteralContext::IntegerLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::UnsignedIntegerContext* anceParser::IntegerLiteralContext::unsignedInteger() {
  return getRuleContext<anceParser::UnsignedIntegerContext>(0);
}

anceParser::SignedIntegerContext* anceParser::IntegerLiteralContext::signedInteger() {
  return getRuleContext<anceParser::SignedIntegerContext>(0);
}

anceParser::SpecialIntegerContext* anceParser::IntegerLiteralContext::specialInteger() {
  return getRuleContext<anceParser::SpecialIntegerContext>(0);
}


size_t anceParser::IntegerLiteralContext::getRuleIndex() const {
  return anceParser::RuleIntegerLiteral;
}


antlrcpp::Any anceParser::IntegerLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitIntegerLiteral(this);
  else
    return visitor->visitChildren(this);
}

anceParser::IntegerLiteralContext* anceParser::integerLiteral() {
  IntegerLiteralContext *_localctx = _tracker.createInstance<IntegerLiteralContext>(_ctx, getState());
  enterRule(_localctx, 58, anceParser::RuleIntegerLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(244);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(241);
        unsignedInteger();
        break;
      }

      case anceParser::SIGNED_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(242);
        signedInteger();
        break;
      }

      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(243);
        specialInteger();
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

//----------------- UnsignedIntegerContext ------------------------------------------------------------------

anceParser::UnsignedIntegerContext::UnsignedIntegerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> anceParser::UnsignedIntegerContext::INTEGER() {
  return getTokens(anceParser::INTEGER);
}

tree::TerminalNode* anceParser::UnsignedIntegerContext::INTEGER(size_t i) {
  return getToken(anceParser::INTEGER, i);
}


size_t anceParser::UnsignedIntegerContext::getRuleIndex() const {
  return anceParser::RuleUnsignedInteger;
}


antlrcpp::Any anceParser::UnsignedIntegerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitUnsignedInteger(this);
  else
    return visitor->visitChildren(this);
}

anceParser::UnsignedIntegerContext* anceParser::unsignedInteger() {
  UnsignedIntegerContext *_localctx = _tracker.createInstance<UnsignedIntegerContext>(_ctx, getState());
  enterRule(_localctx, 60, anceParser::RuleUnsignedInteger);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(246);
    match(anceParser::INTEGER);
    setState(249);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__14) {
      setState(247);
      match(anceParser::T__14);
      setState(248);
      match(anceParser::INTEGER);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SignedIntegerContext ------------------------------------------------------------------

anceParser::SignedIntegerContext::SignedIntegerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::SignedIntegerContext::SIGNED_INTEGER() {
  return getToken(anceParser::SIGNED_INTEGER, 0);
}

tree::TerminalNode* anceParser::SignedIntegerContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}


size_t anceParser::SignedIntegerContext::getRuleIndex() const {
  return anceParser::RuleSignedInteger;
}


antlrcpp::Any anceParser::SignedIntegerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSignedInteger(this);
  else
    return visitor->visitChildren(this);
}

anceParser::SignedIntegerContext* anceParser::signedInteger() {
  SignedIntegerContext *_localctx = _tracker.createInstance<SignedIntegerContext>(_ctx, getState());
  enterRule(_localctx, 62, anceParser::RuleSignedInteger);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(251);
    match(anceParser::SIGNED_INTEGER);
    setState(254);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__14) {
      setState(252);
      match(anceParser::T__14);
      setState(253);
      match(anceParser::INTEGER);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SpecialIntegerContext ------------------------------------------------------------------

anceParser::SpecialIntegerContext::SpecialIntegerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::SpecialIntegerContext::HEX_INTEGER() {
  return getToken(anceParser::HEX_INTEGER, 0);
}

tree::TerminalNode* anceParser::SpecialIntegerContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}

tree::TerminalNode* anceParser::SpecialIntegerContext::BIN_INTEGER() {
  return getToken(anceParser::BIN_INTEGER, 0);
}

tree::TerminalNode* anceParser::SpecialIntegerContext::OCT_INTEGER() {
  return getToken(anceParser::OCT_INTEGER, 0);
}


size_t anceParser::SpecialIntegerContext::getRuleIndex() const {
  return anceParser::RuleSpecialInteger;
}


antlrcpp::Any anceParser::SpecialIntegerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSpecialInteger(this);
  else
    return visitor->visitChildren(this);
}

anceParser::SpecialIntegerContext* anceParser::specialInteger() {
  SpecialIntegerContext *_localctx = _tracker.createInstance<SpecialIntegerContext>(_ctx, getState());
  enterRule(_localctx, 64, anceParser::RuleSpecialInteger);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(271);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::HEX_INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(256);
        match(anceParser::HEX_INTEGER);
        setState(259);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::T__14) {
          setState(257);
          match(anceParser::T__14);
          setState(258);
          match(anceParser::INTEGER);
        }
        break;
      }

      case anceParser::BIN_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(261);
        match(anceParser::BIN_INTEGER);
        setState(264);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::T__14) {
          setState(262);
          match(anceParser::T__14);
          setState(263);
          match(anceParser::INTEGER);
        }
        break;
      }

      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(266);
        match(anceParser::OCT_INTEGER);
        setState(269);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::T__14) {
          setState(267);
          match(anceParser::T__14);
          setState(268);
          match(anceParser::INTEGER);
        }
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

//----------------- FloatingPointLiteralContext ------------------------------------------------------------------

anceParser::FloatingPointLiteralContext::FloatingPointLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::FloatingPointLiteralContext::HALF() {
  return getToken(anceParser::HALF, 0);
}

tree::TerminalNode* anceParser::FloatingPointLiteralContext::SINGLE() {
  return getToken(anceParser::SINGLE, 0);
}

tree::TerminalNode* anceParser::FloatingPointLiteralContext::DOUBLE() {
  return getToken(anceParser::DOUBLE, 0);
}

tree::TerminalNode* anceParser::FloatingPointLiteralContext::QUAD() {
  return getToken(anceParser::QUAD, 0);
}


size_t anceParser::FloatingPointLiteralContext::getRuleIndex() const {
  return anceParser::RuleFloatingPointLiteral;
}


antlrcpp::Any anceParser::FloatingPointLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFloatingPointLiteral(this);
  else
    return visitor->visitChildren(this);
}

anceParser::FloatingPointLiteralContext* anceParser::floatingPointLiteral() {
  FloatingPointLiteralContext *_localctx = _tracker.createInstance<FloatingPointLiteralContext>(_ctx, getState());
  enterRule(_localctx, 66, anceParser::RuleFloatingPointLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(273);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::HALF)
      | (1ULL << anceParser::SINGLE)
      | (1ULL << anceParser::DOUBLE)
      | (1ULL << anceParser::QUAD))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanLiteralContext ------------------------------------------------------------------

anceParser::BooleanLiteralContext::BooleanLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::BooleanLiteralContext::TRUE() {
  return getToken(anceParser::TRUE, 0);
}

tree::TerminalNode* anceParser::BooleanLiteralContext::FALSE() {
  return getToken(anceParser::FALSE, 0);
}


size_t anceParser::BooleanLiteralContext::getRuleIndex() const {
  return anceParser::RuleBooleanLiteral;
}


antlrcpp::Any anceParser::BooleanLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBooleanLiteral(this);
  else
    return visitor->visitChildren(this);
}

anceParser::BooleanLiteralContext* anceParser::booleanLiteral() {
  BooleanLiteralContext *_localctx = _tracker.createInstance<BooleanLiteralContext>(_ctx, getState());
  enterRule(_localctx, 68, anceParser::RuleBooleanLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(275);
    _la = _input->LA(1);
    if (!(_la == anceParser::TRUE

    || _la == anceParser::FALSE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
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

//----------------- IntegerContext ------------------------------------------------------------------

anceParser::IntegerTypeContext* anceParser::IntegerContext::integerType() {
  return getRuleContext<anceParser::IntegerTypeContext>(0);
}

anceParser::IntegerContext::IntegerContext(TypeContext *ctx) { copyFrom(ctx); }


antlrcpp::Any anceParser::IntegerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitInteger(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayContext ------------------------------------------------------------------

anceParser::ArrayTypeContext* anceParser::ArrayContext::arrayType() {
  return getRuleContext<anceParser::ArrayTypeContext>(0);
}

anceParser::ArrayContext::ArrayContext(TypeContext *ctx) { copyFrom(ctx); }


antlrcpp::Any anceParser::ArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitArray(this);
  else
    return visitor->visitChildren(this);
}
//----------------- KeywordContext ------------------------------------------------------------------

anceParser::KeywordTypeContext* anceParser::KeywordContext::keywordType() {
  return getRuleContext<anceParser::KeywordTypeContext>(0);
}

anceParser::KeywordContext::KeywordContext(TypeContext *ctx) { copyFrom(ctx); }


antlrcpp::Any anceParser::KeywordContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitKeyword(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PointerContext ------------------------------------------------------------------

anceParser::TypeContext* anceParser::PointerContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::PointerContext::PointerContext(TypeContext *ctx) { copyFrom(ctx); }


antlrcpp::Any anceParser::PointerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitPointer(this);
  else
    return visitor->visitChildren(this);
}

anceParser::TypeContext* anceParser::type() {
   return type(0);
}

anceParser::TypeContext* anceParser::type(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  anceParser::TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, parentState);
  anceParser::TypeContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 70;
  enterRecursionRule(_localctx, 70, anceParser::RuleType, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(281);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::NATIVE_INTEGER_TYPE: {
        _localctx = _tracker.createInstance<IntegerContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(278);
        integerType();
        break;
      }

      case anceParser::T__16: {
        _localctx = _tracker.createInstance<ArrayContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(279);
        arrayType();
        break;
      }

      case anceParser::T__18:
      case anceParser::T__19:
      case anceParser::T__20:
      case anceParser::HALF_TYPE:
      case anceParser::SINGLE_TYPE:
      case anceParser::DOUBLE_TYPE:
      case anceParser::QUAD_TYPE: {
        _localctx = _tracker.createInstance<KeywordContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(280);
        keywordType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(287);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<PointerContext>(_tracker.createInstance<TypeContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleType);
        setState(283);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(284);
        match(anceParser::T__15); 
      }
      setState(289);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- IntegerTypeContext ------------------------------------------------------------------

anceParser::IntegerTypeContext::IntegerTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::IntegerTypeContext::NATIVE_INTEGER_TYPE() {
  return getToken(anceParser::NATIVE_INTEGER_TYPE, 0);
}


size_t anceParser::IntegerTypeContext::getRuleIndex() const {
  return anceParser::RuleIntegerType;
}


antlrcpp::Any anceParser::IntegerTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitIntegerType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::IntegerTypeContext* anceParser::integerType() {
  IntegerTypeContext *_localctx = _tracker.createInstance<IntegerTypeContext>(_ctx, getState());
  enterRule(_localctx, 72, anceParser::RuleIntegerType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(290);
    match(anceParser::NATIVE_INTEGER_TYPE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayTypeContext ------------------------------------------------------------------

anceParser::ArrayTypeContext::ArrayTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::ArrayTypeContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}

anceParser::TypeContext* anceParser::ArrayTypeContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}


size_t anceParser::ArrayTypeContext::getRuleIndex() const {
  return anceParser::RuleArrayType;
}


antlrcpp::Any anceParser::ArrayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitArrayType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ArrayTypeContext* anceParser::arrayType() {
  ArrayTypeContext *_localctx = _tracker.createInstance<ArrayTypeContext>(_ctx, getState());
  enterRule(_localctx, 74, anceParser::RuleArrayType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(292);
    match(anceParser::T__16);
    setState(293);
    match(anceParser::INTEGER);
    setState(294);
    match(anceParser::T__14);
    setState(295);
    type(0);
    setState(296);
    match(anceParser::T__17);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeywordTypeContext ------------------------------------------------------------------

anceParser::KeywordTypeContext::KeywordTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::FloatingPointTypeContext* anceParser::KeywordTypeContext::floatingPointType() {
  return getRuleContext<anceParser::FloatingPointTypeContext>(0);
}

anceParser::SizeTypeContext* anceParser::KeywordTypeContext::sizeType() {
  return getRuleContext<anceParser::SizeTypeContext>(0);
}

anceParser::UnsignedIntegerPointerTypeContext* anceParser::KeywordTypeContext::unsignedIntegerPointerType() {
  return getRuleContext<anceParser::UnsignedIntegerPointerTypeContext>(0);
}

anceParser::VoidTypeContext* anceParser::KeywordTypeContext::voidType() {
  return getRuleContext<anceParser::VoidTypeContext>(0);
}


size_t anceParser::KeywordTypeContext::getRuleIndex() const {
  return anceParser::RuleKeywordType;
}


antlrcpp::Any anceParser::KeywordTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitKeywordType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::KeywordTypeContext* anceParser::keywordType() {
  KeywordTypeContext *_localctx = _tracker.createInstance<KeywordTypeContext>(_ctx, getState());
  enterRule(_localctx, 76, anceParser::RuleKeywordType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(302);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::HALF_TYPE:
      case anceParser::SINGLE_TYPE:
      case anceParser::DOUBLE_TYPE:
      case anceParser::QUAD_TYPE: {
        enterOuterAlt(_localctx, 1);
        setState(298);
        floatingPointType();
        break;
      }

      case anceParser::T__18: {
        enterOuterAlt(_localctx, 2);
        setState(299);
        sizeType();
        break;
      }

      case anceParser::T__19: {
        enterOuterAlt(_localctx, 3);
        setState(300);
        unsignedIntegerPointerType();
        break;
      }

      case anceParser::T__20: {
        enterOuterAlt(_localctx, 4);
        setState(301);
        voidType();
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

//----------------- FloatingPointTypeContext ------------------------------------------------------------------

anceParser::FloatingPointTypeContext::FloatingPointTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::FloatingPointTypeContext::HALF_TYPE() {
  return getToken(anceParser::HALF_TYPE, 0);
}

tree::TerminalNode* anceParser::FloatingPointTypeContext::SINGLE_TYPE() {
  return getToken(anceParser::SINGLE_TYPE, 0);
}

tree::TerminalNode* anceParser::FloatingPointTypeContext::DOUBLE_TYPE() {
  return getToken(anceParser::DOUBLE_TYPE, 0);
}

tree::TerminalNode* anceParser::FloatingPointTypeContext::QUAD_TYPE() {
  return getToken(anceParser::QUAD_TYPE, 0);
}


size_t anceParser::FloatingPointTypeContext::getRuleIndex() const {
  return anceParser::RuleFloatingPointType;
}


antlrcpp::Any anceParser::FloatingPointTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFloatingPointType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::FloatingPointTypeContext* anceParser::floatingPointType() {
  FloatingPointTypeContext *_localctx = _tracker.createInstance<FloatingPointTypeContext>(_ctx, getState());
  enterRule(_localctx, 78, anceParser::RuleFloatingPointType);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(304);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::HALF_TYPE)
      | (1ULL << anceParser::SINGLE_TYPE)
      | (1ULL << anceParser::DOUBLE_TYPE)
      | (1ULL << anceParser::QUAD_TYPE))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SizeTypeContext ------------------------------------------------------------------

anceParser::SizeTypeContext::SizeTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::SizeTypeContext::getRuleIndex() const {
  return anceParser::RuleSizeType;
}


antlrcpp::Any anceParser::SizeTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSizeType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::SizeTypeContext* anceParser::sizeType() {
  SizeTypeContext *_localctx = _tracker.createInstance<SizeTypeContext>(_ctx, getState());
  enterRule(_localctx, 80, anceParser::RuleSizeType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(306);
    match(anceParser::T__18);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnsignedIntegerPointerTypeContext ------------------------------------------------------------------

anceParser::UnsignedIntegerPointerTypeContext::UnsignedIntegerPointerTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::UnsignedIntegerPointerTypeContext::getRuleIndex() const {
  return anceParser::RuleUnsignedIntegerPointerType;
}


antlrcpp::Any anceParser::UnsignedIntegerPointerTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitUnsignedIntegerPointerType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::UnsignedIntegerPointerTypeContext* anceParser::unsignedIntegerPointerType() {
  UnsignedIntegerPointerTypeContext *_localctx = _tracker.createInstance<UnsignedIntegerPointerTypeContext>(_ctx, getState());
  enterRule(_localctx, 82, anceParser::RuleUnsignedIntegerPointerType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(308);
    match(anceParser::T__19);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VoidTypeContext ------------------------------------------------------------------

anceParser::VoidTypeContext::VoidTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::VoidTypeContext::getRuleIndex() const {
  return anceParser::RuleVoidType;
}


antlrcpp::Any anceParser::VoidTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVoidType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::VoidTypeContext* anceParser::voidType() {
  VoidTypeContext *_localctx = _tracker.createInstance<VoidTypeContext>(_ctx, getState());
  enterRule(_localctx, 84, anceParser::RuleVoidType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(310);
    match(anceParser::T__20);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool anceParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 35: return typeSempred(dynamic_cast<TypeContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool anceParser::typeSempred(TypeContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> anceParser::_decisionToDFA;
atn::PredictionContextCache anceParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN anceParser::_atn;
std::vector<uint16_t> anceParser::_serializedATN;

std::vector<std::string> anceParser::_ruleNames = {
  "file", "data", "constantDeclaration", "variableDeclaration", "code", 
  "function", "parameters", "parameter", "accessModifier", "statement", 
  "expressionStatement", "localVariableDefinition", "variableAssignment", 
  "printStatement", "deleteStatement", "returnStatement", "expression", 
  "independentExpression", "functionCall", "arguments", "variableAccess", 
  "allocation", "allocator", "roughCast", "sizeofType", "sizeofExpression", 
  "literalExpression", "stringLiteral", "byteLiteral", "integerLiteral", 
  "unsignedInteger", "signedInteger", "specialInteger", "floatingPointLiteral", 
  "booleanLiteral", "type", "integerType", "arrayType", "keywordType", "floatingPointType", 
  "sizeType", "unsignedIntegerPointerType", "voidType"
};

std::vector<std::string> anceParser::_literalNames = {
  "", "'const'", "':='", "';'", "'<-'", "'('", "')'", "'{'", "'}'", "','", 
  "'print'", "'delete'", "'return'", "'new'", "'sizeof'", "':'", "'*'", 
  "'['", "']'", "'size'", "'uiptr'", "'void'", "", "'half'", "'single'", 
  "'double'", "'quad'", "", "", "", "", "", "", "", "", "", "", "", "", 
  "'dynamic'", "'automatic'", "'true'", "'false'", "'public'", "'private'"
};

std::vector<std::string> anceParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "NATIVE_INTEGER_TYPE", "HALF_TYPE", "SINGLE_TYPE", "DOUBLE_TYPE", 
  "QUAD_TYPE", "SIGNED_INTEGER", "HEX_INTEGER", "BIN_INTEGER", "OCT_INTEGER", 
  "HALF", "SINGLE", "DOUBLE", "QUAD", "DECIMAL", "STRING", "BYTE", "INTEGER", 
  "DYNAMIC", "AUTOMATIC", "TRUE", "FALSE", "PUBLIC", "PRIVATE", "IDENTIFIER", 
  "WHITESPACE", "BLOCK_COMMENT", "LINE_COMMENT"
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
    0x3, 0x32, 0x13b, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x5b, 0xa, 0x2, 0xc, 
    0x2, 0xe, 0x2, 0x5e, 0xb, 0x2, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x62, 0xa, 
    0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 
    0x5, 0x71, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x6, 0x7, 0x7f, 0xa, 0x7, 0xd, 0x7, 0xe, 0x7, 0x80, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x88, 0xa, 0x8, 0xc, 0x8, 0xe, 
    0x8, 0x8b, 0xb, 0x8, 0x5, 0x8, 0x8d, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x5, 0xb, 0x9a, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0xa3, 0xa, 0xd, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0xb6, 0xa, 0x11, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x5, 0x12, 0xc1, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x7, 0x15, 0xcd, 0xa, 0x15, 0xc, 0x15, 0xe, 0x15, 0xd0, 0xb, 
    0x15, 0x5, 0x15, 0xd2, 0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 
    0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 
    0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0xee, 0xa, 0x1c, 0x3, 0x1d, 
    0x3, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x5, 
    0x1f, 0xf7, 0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0xfc, 
    0xa, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 0x21, 0x101, 0xa, 0x21, 
    0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x106, 0xa, 0x22, 0x3, 0x22, 
    0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x10b, 0xa, 0x22, 0x3, 0x22, 0x3, 0x22, 
    0x3, 0x22, 0x5, 0x22, 0x110, 0xa, 0x22, 0x5, 0x22, 0x112, 0xa, 0x22, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x25, 0x3, 0x25, 0x3, 
    0x25, 0x3, 0x25, 0x5, 0x25, 0x11c, 0xa, 0x25, 0x3, 0x25, 0x3, 0x25, 
    0x7, 0x25, 0x120, 0xa, 0x25, 0xc, 0x25, 0xe, 0x25, 0x123, 0xb, 0x25, 
    0x3, 0x26, 0x3, 0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 
    0x27, 0x3, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x5, 0x28, 
    0x131, 0xa, 0x28, 0x3, 0x29, 0x3, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2b, 
    0x3, 0x2b, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x2, 0x3, 0x48, 0x2d, 0x2, 
    0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 
    0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 
    0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 
    0x4e, 0x50, 0x52, 0x54, 0x56, 0x2, 0x7, 0x3, 0x2, 0x2d, 0x2e, 0x3, 0x2, 
    0x29, 0x2a, 0x3, 0x2, 0x21, 0x24, 0x3, 0x2, 0x2b, 0x2c, 0x3, 0x2, 0x19, 
    0x1c, 0x2, 0x138, 0x2, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x4, 0x61, 0x3, 0x2, 
    0x2, 0x2, 0x6, 0x63, 0x3, 0x2, 0x2, 0x2, 0x8, 0x6b, 0x3, 0x2, 0x2, 0x2, 
    0xa, 0x74, 0x3, 0x2, 0x2, 0x2, 0xc, 0x76, 0x3, 0x2, 0x2, 0x2, 0xe, 0x8c, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x12, 0x91, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x99, 0x3, 0x2, 0x2, 0x2, 0x16, 0x9b, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x1a, 0xa6, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0xab, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xaf, 0x3, 0x2, 0x2, 0x2, 
    0x20, 0xb3, 0x3, 0x2, 0x2, 0x2, 0x22, 0xc0, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0xc2, 0x3, 0x2, 0x2, 0x2, 0x26, 0xc4, 0x3, 0x2, 0x2, 0x2, 0x28, 0xd1, 
    0x3, 0x2, 0x2, 0x2, 0x2a, 0xd3, 0x3, 0x2, 0x2, 0x2, 0x2c, 0xd5, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0xd9, 0x3, 0x2, 0x2, 0x2, 0x30, 0xdb, 0x3, 0x2, 
    0x2, 0x2, 0x32, 0xe0, 0x3, 0x2, 0x2, 0x2, 0x34, 0xe3, 0x3, 0x2, 0x2, 
    0x2, 0x36, 0xed, 0x3, 0x2, 0x2, 0x2, 0x38, 0xef, 0x3, 0x2, 0x2, 0x2, 
    0x3a, 0xf1, 0x3, 0x2, 0x2, 0x2, 0x3c, 0xf6, 0x3, 0x2, 0x2, 0x2, 0x3e, 
    0xf8, 0x3, 0x2, 0x2, 0x2, 0x40, 0xfd, 0x3, 0x2, 0x2, 0x2, 0x42, 0x111, 
    0x3, 0x2, 0x2, 0x2, 0x44, 0x113, 0x3, 0x2, 0x2, 0x2, 0x46, 0x115, 0x3, 
    0x2, 0x2, 0x2, 0x48, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x124, 0x3, 0x2, 
    0x2, 0x2, 0x4c, 0x126, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x130, 0x3, 0x2, 0x2, 
    0x2, 0x50, 0x132, 0x3, 0x2, 0x2, 0x2, 0x52, 0x134, 0x3, 0x2, 0x2, 0x2, 
    0x54, 0x136, 0x3, 0x2, 0x2, 0x2, 0x56, 0x138, 0x3, 0x2, 0x2, 0x2, 0x58, 
    0x5b, 0x5, 0x4, 0x3, 0x2, 0x59, 0x5b, 0x5, 0xa, 0x6, 0x2, 0x5a, 0x58, 
    0x3, 0x2, 0x2, 0x2, 0x5a, 0x59, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5e, 0x3, 
    0x2, 0x2, 0x2, 0x5c, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x3, 0x2, 
    0x2, 0x2, 0x5d, 0x3, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5c, 0x3, 0x2, 0x2, 
    0x2, 0x5f, 0x62, 0x5, 0x6, 0x4, 0x2, 0x60, 0x62, 0x5, 0x8, 0x5, 0x2, 
    0x61, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x61, 0x60, 0x3, 0x2, 0x2, 0x2, 0x62, 
    0x5, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x5, 0x12, 0xa, 0x2, 0x64, 0x65, 
    0x7, 0x3, 0x2, 0x2, 0x65, 0x66, 0x5, 0x48, 0x25, 0x2, 0x66, 0x67, 0x7, 
    0x2f, 0x2, 0x2, 0x67, 0x68, 0x7, 0x4, 0x2, 0x2, 0x68, 0x69, 0x5, 0x36, 
    0x1c, 0x2, 0x69, 0x6a, 0x7, 0x5, 0x2, 0x2, 0x6a, 0x7, 0x3, 0x2, 0x2, 
    0x2, 0x6b, 0x6c, 0x5, 0x12, 0xa, 0x2, 0x6c, 0x6d, 0x5, 0x48, 0x25, 0x2, 
    0x6d, 0x70, 0x7, 0x2f, 0x2, 0x2, 0x6e, 0x6f, 0x7, 0x6, 0x2, 0x2, 0x6f, 
    0x71, 0x5, 0x36, 0x1c, 0x2, 0x70, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x70, 0x71, 
    0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0x7, 
    0x5, 0x2, 0x2, 0x73, 0x9, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x5, 0xc, 
    0x7, 0x2, 0x75, 0xb, 0x3, 0x2, 0x2, 0x2, 0x76, 0x77, 0x5, 0x12, 0xa, 
    0x2, 0x77, 0x78, 0x5, 0x48, 0x25, 0x2, 0x78, 0x79, 0x7, 0x2f, 0x2, 0x2, 
    0x79, 0x7a, 0x7, 0x7, 0x2, 0x2, 0x7a, 0x7b, 0x5, 0xe, 0x8, 0x2, 0x7b, 
    0x7c, 0x7, 0x8, 0x2, 0x2, 0x7c, 0x7e, 0x7, 0x9, 0x2, 0x2, 0x7d, 0x7f, 
    0x5, 0x14, 0xb, 0x2, 0x7e, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x7f, 0x80, 0x3, 
    0x2, 0x2, 0x2, 0x80, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x80, 0x81, 0x3, 0x2, 
    0x2, 0x2, 0x81, 0x82, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x7, 0xa, 0x2, 
    0x2, 0x83, 0xd, 0x3, 0x2, 0x2, 0x2, 0x84, 0x89, 0x5, 0x10, 0x9, 0x2, 
    0x85, 0x86, 0x7, 0xb, 0x2, 0x2, 0x86, 0x88, 0x5, 0x10, 0x9, 0x2, 0x87, 
    0x85, 0x3, 0x2, 0x2, 0x2, 0x88, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x89, 0x87, 
    0x3, 0x2, 0x2, 0x2, 0x89, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x8d, 0x3, 
    0x2, 0x2, 0x2, 0x8b, 0x89, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x84, 0x3, 0x2, 
    0x2, 0x2, 0x8c, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x8d, 0xf, 0x3, 0x2, 0x2, 
    0x2, 0x8e, 0x8f, 0x5, 0x48, 0x25, 0x2, 0x8f, 0x90, 0x7, 0x2f, 0x2, 0x2, 
    0x90, 0x11, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0x9, 0x2, 0x2, 0x2, 0x92, 
    0x13, 0x3, 0x2, 0x2, 0x2, 0x93, 0x9a, 0x5, 0x16, 0xc, 0x2, 0x94, 0x9a, 
    0x5, 0x18, 0xd, 0x2, 0x95, 0x9a, 0x5, 0x1a, 0xe, 0x2, 0x96, 0x9a, 0x5, 
    0x1c, 0xf, 0x2, 0x97, 0x9a, 0x5, 0x1e, 0x10, 0x2, 0x98, 0x9a, 0x5, 0x20, 
    0x11, 0x2, 0x99, 0x93, 0x3, 0x2, 0x2, 0x2, 0x99, 0x94, 0x3, 0x2, 0x2, 
    0x2, 0x99, 0x95, 0x3, 0x2, 0x2, 0x2, 0x99, 0x96, 0x3, 0x2, 0x2, 0x2, 
    0x99, 0x97, 0x3, 0x2, 0x2, 0x2, 0x99, 0x98, 0x3, 0x2, 0x2, 0x2, 0x9a, 
    0x15, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x9c, 0x5, 0x24, 0x13, 0x2, 0x9c, 0x9d, 
    0x7, 0x5, 0x2, 0x2, 0x9d, 0x17, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x9f, 0x5, 
    0x48, 0x25, 0x2, 0x9f, 0xa2, 0x7, 0x2f, 0x2, 0x2, 0xa0, 0xa1, 0x7, 0x6, 
    0x2, 0x2, 0xa1, 0xa3, 0x5, 0x22, 0x12, 0x2, 0xa2, 0xa0, 0x3, 0x2, 0x2, 
    0x2, 0xa2, 0xa3, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa4, 0x3, 0x2, 0x2, 0x2, 
    0xa4, 0xa5, 0x7, 0x5, 0x2, 0x2, 0xa5, 0x19, 0x3, 0x2, 0x2, 0x2, 0xa6, 
    0xa7, 0x7, 0x2f, 0x2, 0x2, 0xa7, 0xa8, 0x7, 0x6, 0x2, 0x2, 0xa8, 0xa9, 
    0x5, 0x22, 0x12, 0x2, 0xa9, 0xaa, 0x7, 0x5, 0x2, 0x2, 0xaa, 0x1b, 0x3, 
    0x2, 0x2, 0x2, 0xab, 0xac, 0x7, 0xc, 0x2, 0x2, 0xac, 0xad, 0x5, 0x22, 
    0x12, 0x2, 0xad, 0xae, 0x7, 0x5, 0x2, 0x2, 0xae, 0x1d, 0x3, 0x2, 0x2, 
    0x2, 0xaf, 0xb0, 0x7, 0xd, 0x2, 0x2, 0xb0, 0xb1, 0x5, 0x22, 0x12, 0x2, 
    0xb1, 0xb2, 0x7, 0x5, 0x2, 0x2, 0xb2, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xb3, 
    0xb5, 0x7, 0xe, 0x2, 0x2, 0xb4, 0xb6, 0x5, 0x22, 0x12, 0x2, 0xb5, 0xb4, 
    0x3, 0x2, 0x2, 0x2, 0xb5, 0xb6, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb7, 0x3, 
    0x2, 0x2, 0x2, 0xb7, 0xb8, 0x7, 0x5, 0x2, 0x2, 0xb8, 0x21, 0x3, 0x2, 
    0x2, 0x2, 0xb9, 0xc1, 0x5, 0x2a, 0x16, 0x2, 0xba, 0xc1, 0x5, 0x2c, 0x17, 
    0x2, 0xbb, 0xc1, 0x5, 0x30, 0x19, 0x2, 0xbc, 0xc1, 0x5, 0x32, 0x1a, 
    0x2, 0xbd, 0xc1, 0x5, 0x34, 0x1b, 0x2, 0xbe, 0xc1, 0x5, 0x36, 0x1c, 
    0x2, 0xbf, 0xc1, 0x5, 0x24, 0x13, 0x2, 0xc0, 0xb9, 0x3, 0x2, 0x2, 0x2, 
    0xc0, 0xba, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xc0, 
    0xbc, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xc0, 0xbe, 
    0x3, 0x2, 0x2, 0x2, 0xc0, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xc1, 0x23, 0x3, 
    0x2, 0x2, 0x2, 0xc2, 0xc3, 0x5, 0x26, 0x14, 0x2, 0xc3, 0x25, 0x3, 0x2, 
    0x2, 0x2, 0xc4, 0xc5, 0x7, 0x2f, 0x2, 0x2, 0xc5, 0xc6, 0x7, 0x7, 0x2, 
    0x2, 0xc6, 0xc7, 0x5, 0x28, 0x15, 0x2, 0xc7, 0xc8, 0x7, 0x8, 0x2, 0x2, 
    0xc8, 0x27, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xce, 0x5, 0x22, 0x12, 0x2, 0xca, 
    0xcb, 0x7, 0xb, 0x2, 0x2, 0xcb, 0xcd, 0x5, 0x22, 0x12, 0x2, 0xcc, 0xca, 
    0x3, 0x2, 0x2, 0x2, 0xcd, 0xd0, 0x3, 0x2, 0x2, 0x2, 0xce, 0xcc, 0x3, 
    0x2, 0x2, 0x2, 0xce, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xcf, 0xd2, 0x3, 0x2, 
    0x2, 0x2, 0xd0, 0xce, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xc9, 0x3, 0x2, 0x2, 
    0x2, 0xd1, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xd2, 0x29, 0x3, 0x2, 0x2, 0x2, 
    0xd3, 0xd4, 0x7, 0x2f, 0x2, 0x2, 0xd4, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xd5, 
    0xd6, 0x7, 0xf, 0x2, 0x2, 0xd6, 0xd7, 0x5, 0x2e, 0x18, 0x2, 0xd7, 0xd8, 
    0x5, 0x48, 0x25, 0x2, 0xd8, 0x2d, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xda, 0x9, 
    0x3, 0x2, 0x2, 0xda, 0x2f, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xdc, 0x7, 0x9, 
    0x2, 0x2, 0xdc, 0xdd, 0x5, 0x48, 0x25, 0x2, 0xdd, 0xde, 0x7, 0xa, 0x2, 
    0x2, 0xde, 0xdf, 0x5, 0x22, 0x12, 0x2, 0xdf, 0x31, 0x3, 0x2, 0x2, 0x2, 
    0xe0, 0xe1, 0x7, 0x10, 0x2, 0x2, 0xe1, 0xe2, 0x5, 0x48, 0x25, 0x2, 0xe2, 
    0x33, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe4, 0x7, 0x10, 0x2, 0x2, 0xe4, 0xe5, 
    0x7, 0x7, 0x2, 0x2, 0xe5, 0xe6, 0x5, 0x22, 0x12, 0x2, 0xe6, 0xe7, 0x7, 
    0x8, 0x2, 0x2, 0xe7, 0x35, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xee, 0x5, 0x38, 
    0x1d, 0x2, 0xe9, 0xee, 0x5, 0x3a, 0x1e, 0x2, 0xea, 0xee, 0x5, 0x3c, 
    0x1f, 0x2, 0xeb, 0xee, 0x5, 0x44, 0x23, 0x2, 0xec, 0xee, 0x5, 0x46, 
    0x24, 0x2, 0xed, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xed, 0xe9, 0x3, 0x2, 0x2, 
    0x2, 0xed, 0xea, 0x3, 0x2, 0x2, 0x2, 0xed, 0xeb, 0x3, 0x2, 0x2, 0x2, 
    0xed, 0xec, 0x3, 0x2, 0x2, 0x2, 0xee, 0x37, 0x3, 0x2, 0x2, 0x2, 0xef, 
    0xf0, 0x7, 0x26, 0x2, 0x2, 0xf0, 0x39, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xf2, 
    0x7, 0x27, 0x2, 0x2, 0xf2, 0x3b, 0x3, 0x2, 0x2, 0x2, 0xf3, 0xf7, 0x5, 
    0x3e, 0x20, 0x2, 0xf4, 0xf7, 0x5, 0x40, 0x21, 0x2, 0xf5, 0xf7, 0x5, 
    0x42, 0x22, 0x2, 0xf6, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf4, 0x3, 0x2, 
    0x2, 0x2, 0xf6, 0xf5, 0x3, 0x2, 0x2, 0x2, 0xf7, 0x3d, 0x3, 0x2, 0x2, 
    0x2, 0xf8, 0xfb, 0x7, 0x28, 0x2, 0x2, 0xf9, 0xfa, 0x7, 0x11, 0x2, 0x2, 
    0xfa, 0xfc, 0x7, 0x28, 0x2, 0x2, 0xfb, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xfb, 
    0xfc, 0x3, 0x2, 0x2, 0x2, 0xfc, 0x3f, 0x3, 0x2, 0x2, 0x2, 0xfd, 0x100, 
    0x7, 0x1d, 0x2, 0x2, 0xfe, 0xff, 0x7, 0x11, 0x2, 0x2, 0xff, 0x101, 0x7, 
    0x28, 0x2, 0x2, 0x100, 0xfe, 0x3, 0x2, 0x2, 0x2, 0x100, 0x101, 0x3, 
    0x2, 0x2, 0x2, 0x101, 0x41, 0x3, 0x2, 0x2, 0x2, 0x102, 0x105, 0x7, 0x1e, 
    0x2, 0x2, 0x103, 0x104, 0x7, 0x11, 0x2, 0x2, 0x104, 0x106, 0x7, 0x28, 
    0x2, 0x2, 0x105, 0x103, 0x3, 0x2, 0x2, 0x2, 0x105, 0x106, 0x3, 0x2, 
    0x2, 0x2, 0x106, 0x112, 0x3, 0x2, 0x2, 0x2, 0x107, 0x10a, 0x7, 0x1f, 
    0x2, 0x2, 0x108, 0x109, 0x7, 0x11, 0x2, 0x2, 0x109, 0x10b, 0x7, 0x28, 
    0x2, 0x2, 0x10a, 0x108, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x10b, 0x3, 0x2, 
    0x2, 0x2, 0x10b, 0x112, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x10f, 0x7, 0x20, 
    0x2, 0x2, 0x10d, 0x10e, 0x7, 0x11, 0x2, 0x2, 0x10e, 0x110, 0x7, 0x28, 
    0x2, 0x2, 0x10f, 0x10d, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x110, 0x3, 0x2, 
    0x2, 0x2, 0x110, 0x112, 0x3, 0x2, 0x2, 0x2, 0x111, 0x102, 0x3, 0x2, 
    0x2, 0x2, 0x111, 0x107, 0x3, 0x2, 0x2, 0x2, 0x111, 0x10c, 0x3, 0x2, 
    0x2, 0x2, 0x112, 0x43, 0x3, 0x2, 0x2, 0x2, 0x113, 0x114, 0x9, 0x4, 0x2, 
    0x2, 0x114, 0x45, 0x3, 0x2, 0x2, 0x2, 0x115, 0x116, 0x9, 0x5, 0x2, 0x2, 
    0x116, 0x47, 0x3, 0x2, 0x2, 0x2, 0x117, 0x118, 0x8, 0x25, 0x1, 0x2, 
    0x118, 0x11c, 0x5, 0x4a, 0x26, 0x2, 0x119, 0x11c, 0x5, 0x4c, 0x27, 0x2, 
    0x11a, 0x11c, 0x5, 0x4e, 0x28, 0x2, 0x11b, 0x117, 0x3, 0x2, 0x2, 0x2, 
    0x11b, 0x119, 0x3, 0x2, 0x2, 0x2, 0x11b, 0x11a, 0x3, 0x2, 0x2, 0x2, 
    0x11c, 0x121, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x11e, 0xc, 0x3, 0x2, 0x2, 
    0x11e, 0x120, 0x7, 0x12, 0x2, 0x2, 0x11f, 0x11d, 0x3, 0x2, 0x2, 0x2, 
    0x120, 0x123, 0x3, 0x2, 0x2, 0x2, 0x121, 0x11f, 0x3, 0x2, 0x2, 0x2, 
    0x121, 0x122, 0x3, 0x2, 0x2, 0x2, 0x122, 0x49, 0x3, 0x2, 0x2, 0x2, 0x123, 
    0x121, 0x3, 0x2, 0x2, 0x2, 0x124, 0x125, 0x7, 0x18, 0x2, 0x2, 0x125, 
    0x4b, 0x3, 0x2, 0x2, 0x2, 0x126, 0x127, 0x7, 0x13, 0x2, 0x2, 0x127, 
    0x128, 0x7, 0x28, 0x2, 0x2, 0x128, 0x129, 0x7, 0x11, 0x2, 0x2, 0x129, 
    0x12a, 0x5, 0x48, 0x25, 0x2, 0x12a, 0x12b, 0x7, 0x14, 0x2, 0x2, 0x12b, 
    0x4d, 0x3, 0x2, 0x2, 0x2, 0x12c, 0x131, 0x5, 0x50, 0x29, 0x2, 0x12d, 
    0x131, 0x5, 0x52, 0x2a, 0x2, 0x12e, 0x131, 0x5, 0x54, 0x2b, 0x2, 0x12f, 
    0x131, 0x5, 0x56, 0x2c, 0x2, 0x130, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x130, 
    0x12d, 0x3, 0x2, 0x2, 0x2, 0x130, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x130, 
    0x12f, 0x3, 0x2, 0x2, 0x2, 0x131, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x132, 0x133, 
    0x9, 0x6, 0x2, 0x2, 0x133, 0x51, 0x3, 0x2, 0x2, 0x2, 0x134, 0x135, 0x7, 
    0x15, 0x2, 0x2, 0x135, 0x53, 0x3, 0x2, 0x2, 0x2, 0x136, 0x137, 0x7, 
    0x16, 0x2, 0x2, 0x137, 0x55, 0x3, 0x2, 0x2, 0x2, 0x138, 0x139, 0x7, 
    0x17, 0x2, 0x2, 0x139, 0x57, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x5a, 0x5c, 0x61, 
    0x70, 0x80, 0x89, 0x8c, 0x99, 0xa2, 0xb5, 0xc0, 0xce, 0xd1, 0xed, 0xf6, 
    0xfb, 0x100, 0x105, 0x10a, 0x10f, 0x111, 0x11b, 0x121, 0x130, 
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
