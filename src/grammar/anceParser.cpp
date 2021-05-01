
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
    setState(82);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == anceParser::PUBLIC

    || _la == anceParser::PRIVATE) {
      setState(80);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(78);
        data();
        break;
      }

      case 2: {
        setState(79);
        code();
        break;
      }

      }
      setState(84);
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

anceParser::Constant_declarationContext* anceParser::DataContext::constant_declaration() {
  return getRuleContext<anceParser::Constant_declarationContext>(0);
}

anceParser::Variable_declarationContext* anceParser::DataContext::variable_declaration() {
  return getRuleContext<anceParser::Variable_declarationContext>(0);
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
    setState(87);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(85);
      constant_declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(86);
      variable_declaration();
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

//----------------- Constant_declarationContext ------------------------------------------------------------------

anceParser::Constant_declarationContext::Constant_declarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::Access_modifierContext* anceParser::Constant_declarationContext::access_modifier() {
  return getRuleContext<anceParser::Access_modifierContext>(0);
}

tree::TerminalNode* anceParser::Constant_declarationContext::CONST() {
  return getToken(anceParser::CONST, 0);
}

anceParser::TypeContext* anceParser::Constant_declarationContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::Constant_declarationContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::Constant_declarationContext::DEFINITION() {
  return getToken(anceParser::DEFINITION, 0);
}

anceParser::Constant_expressionContext* anceParser::Constant_declarationContext::constant_expression() {
  return getRuleContext<anceParser::Constant_expressionContext>(0);
}


size_t anceParser::Constant_declarationContext::getRuleIndex() const {
  return anceParser::RuleConstant_declaration;
}


antlrcpp::Any anceParser::Constant_declarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitConstant_declaration(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Constant_declarationContext* anceParser::constant_declaration() {
  Constant_declarationContext *_localctx = _tracker.createInstance<Constant_declarationContext>(_ctx, getState());
  enterRule(_localctx, 4, anceParser::RuleConstant_declaration);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    access_modifier();
    setState(90);
    match(anceParser::CONST);
    setState(91);
    type();
    setState(92);
    match(anceParser::IDENTIFIER);
    setState(93);
    match(anceParser::DEFINITION);
    setState(94);
    constant_expression();
    setState(95);
    match(anceParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Variable_declarationContext ------------------------------------------------------------------

anceParser::Variable_declarationContext::Variable_declarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::Access_modifierContext* anceParser::Variable_declarationContext::access_modifier() {
  return getRuleContext<anceParser::Access_modifierContext>(0);
}

anceParser::TypeContext* anceParser::Variable_declarationContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::Variable_declarationContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::Variable_declarationContext::ASSIGNMENT() {
  return getToken(anceParser::ASSIGNMENT, 0);
}

anceParser::Constant_expressionContext* anceParser::Variable_declarationContext::constant_expression() {
  return getRuleContext<anceParser::Constant_expressionContext>(0);
}


size_t anceParser::Variable_declarationContext::getRuleIndex() const {
  return anceParser::RuleVariable_declaration;
}


antlrcpp::Any anceParser::Variable_declarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVariable_declaration(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Variable_declarationContext* anceParser::variable_declaration() {
  Variable_declarationContext *_localctx = _tracker.createInstance<Variable_declarationContext>(_ctx, getState());
  enterRule(_localctx, 6, anceParser::RuleVariable_declaration);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(97);
    access_modifier();
    setState(98);
    type();
    setState(99);
    match(anceParser::IDENTIFIER);
    setState(102);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::ASSIGNMENT) {
      setState(100);
      match(anceParser::ASSIGNMENT);
      setState(101);
      constant_expression();
    }
    setState(104);
    match(anceParser::T__0);
   
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
    setState(106);
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

anceParser::Access_modifierContext* anceParser::FunctionContext::access_modifier() {
  return getRuleContext<anceParser::Access_modifierContext>(0);
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
    setState(108);
    access_modifier();
    setState(109);
    type();
    setState(110);
    match(anceParser::IDENTIFIER);
    setState(111);
    match(anceParser::T__1);
    setState(112);
    parameters();
    setState(113);
    match(anceParser::T__2);
    setState(114);
    match(anceParser::T__3);
    setState(116); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(115);
      statement();
      setState(118); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__7)
      | (1ULL << anceParser::NATIVE_INTEGER_TYPE)
      | (1ULL << anceParser::HALF_TYPE)
      | (1ULL << anceParser::SINGLE_TYPE)
      | (1ULL << anceParser::DOUBLE_TYPE)
      | (1ULL << anceParser::QUAD_TYPE)
      | (1ULL << anceParser::SIZE)
      | (1ULL << anceParser::UIPTR)
      | (1ULL << anceParser::PRINT)
      | (1ULL << anceParser::RETURN)
      | (1ULL << anceParser::VOID)
      | (1ULL << anceParser::IDENTIFIER))) != 0));
    setState(120);
    match(anceParser::T__4);
   
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
    setState(130);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__7)
      | (1ULL << anceParser::NATIVE_INTEGER_TYPE)
      | (1ULL << anceParser::HALF_TYPE)
      | (1ULL << anceParser::SINGLE_TYPE)
      | (1ULL << anceParser::DOUBLE_TYPE)
      | (1ULL << anceParser::QUAD_TYPE)
      | (1ULL << anceParser::SIZE)
      | (1ULL << anceParser::UIPTR)
      | (1ULL << anceParser::VOID))) != 0)) {
      setState(122);
      parameter();
      setState(127);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(123);
        match(anceParser::T__5);
        setState(124);
        parameter();
        setState(129);
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
    setState(132);
    type();
    setState(133);
    match(anceParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Access_modifierContext ------------------------------------------------------------------

anceParser::Access_modifierContext::Access_modifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Access_modifierContext::PUBLIC() {
  return getToken(anceParser::PUBLIC, 0);
}

tree::TerminalNode* anceParser::Access_modifierContext::PRIVATE() {
  return getToken(anceParser::PRIVATE, 0);
}


size_t anceParser::Access_modifierContext::getRuleIndex() const {
  return anceParser::RuleAccess_modifier;
}


antlrcpp::Any anceParser::Access_modifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAccess_modifier(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Access_modifierContext* anceParser::access_modifier() {
  Access_modifierContext *_localctx = _tracker.createInstance<Access_modifierContext>(_ctx, getState());
  enterRule(_localctx, 16, anceParser::RuleAccess_modifier);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(135);
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

anceParser::Expression_statementContext* anceParser::StatementContext::expression_statement() {
  return getRuleContext<anceParser::Expression_statementContext>(0);
}

anceParser::Local_variable_definitionContext* anceParser::StatementContext::local_variable_definition() {
  return getRuleContext<anceParser::Local_variable_definitionContext>(0);
}

anceParser::Variable_assignmentContext* anceParser::StatementContext::variable_assignment() {
  return getRuleContext<anceParser::Variable_assignmentContext>(0);
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
    setState(142);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(137);
      expression_statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(138);
      local_variable_definition();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(139);
      variable_assignment();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(140);
      print_statement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(141);
      return_statement();
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

//----------------- Expression_statementContext ------------------------------------------------------------------

anceParser::Expression_statementContext::Expression_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::Independent_expressionContext* anceParser::Expression_statementContext::independent_expression() {
  return getRuleContext<anceParser::Independent_expressionContext>(0);
}


size_t anceParser::Expression_statementContext::getRuleIndex() const {
  return anceParser::RuleExpression_statement;
}


antlrcpp::Any anceParser::Expression_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitExpression_statement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Expression_statementContext* anceParser::expression_statement() {
  Expression_statementContext *_localctx = _tracker.createInstance<Expression_statementContext>(_ctx, getState());
  enterRule(_localctx, 20, anceParser::RuleExpression_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(144);
    independent_expression();
    setState(145);
    match(anceParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Local_variable_definitionContext ------------------------------------------------------------------

anceParser::Local_variable_definitionContext::Local_variable_definitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::TypeContext* anceParser::Local_variable_definitionContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::Local_variable_definitionContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::Local_variable_definitionContext::ASSIGNMENT() {
  return getToken(anceParser::ASSIGNMENT, 0);
}

anceParser::ExpressionContext* anceParser::Local_variable_definitionContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::Local_variable_definitionContext::getRuleIndex() const {
  return anceParser::RuleLocal_variable_definition;
}


antlrcpp::Any anceParser::Local_variable_definitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLocal_variable_definition(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Local_variable_definitionContext* anceParser::local_variable_definition() {
  Local_variable_definitionContext *_localctx = _tracker.createInstance<Local_variable_definitionContext>(_ctx, getState());
  enterRule(_localctx, 22, anceParser::RuleLocal_variable_definition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    type();
    setState(148);
    match(anceParser::IDENTIFIER);
    setState(151);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::ASSIGNMENT) {
      setState(149);
      match(anceParser::ASSIGNMENT);
      setState(150);
      expression();
    }
    setState(153);
    match(anceParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Variable_assignmentContext ------------------------------------------------------------------

anceParser::Variable_assignmentContext::Variable_assignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Variable_assignmentContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::Variable_assignmentContext::ASSIGNMENT() {
  return getToken(anceParser::ASSIGNMENT, 0);
}

anceParser::ExpressionContext* anceParser::Variable_assignmentContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::Variable_assignmentContext::getRuleIndex() const {
  return anceParser::RuleVariable_assignment;
}


antlrcpp::Any anceParser::Variable_assignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVariable_assignment(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Variable_assignmentContext* anceParser::variable_assignment() {
  Variable_assignmentContext *_localctx = _tracker.createInstance<Variable_assignmentContext>(_ctx, getState());
  enterRule(_localctx, 24, anceParser::RuleVariable_assignment);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    match(anceParser::IDENTIFIER);
    setState(156);
    match(anceParser::ASSIGNMENT);
    setState(157);
    expression();
    setState(158);
    match(anceParser::T__0);
   
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

anceParser::ExpressionContext* anceParser::Print_statementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::Print_statementContext::getRuleIndex() const {
  return anceParser::RulePrint_statement;
}


antlrcpp::Any anceParser::Print_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitPrint_statement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Print_statementContext* anceParser::print_statement() {
  Print_statementContext *_localctx = _tracker.createInstance<Print_statementContext>(_ctx, getState());
  enterRule(_localctx, 26, anceParser::RulePrint_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    match(anceParser::PRINT);
    setState(161);
    expression();
    setState(162);
    match(anceParser::T__0);
   
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

anceParser::ExpressionContext* anceParser::Return_statementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::Return_statementContext::getRuleIndex() const {
  return anceParser::RuleReturn_statement;
}


antlrcpp::Any anceParser::Return_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitReturn_statement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Return_statementContext* anceParser::return_statement() {
  Return_statementContext *_localctx = _tracker.createInstance<Return_statementContext>(_ctx, getState());
  enterRule(_localctx, 28, anceParser::RuleReturn_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(164);
    match(anceParser::RETURN);
    setState(166);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::SIGNED_INTEGER)
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
      | (1ULL << anceParser::SIZEOF)
      | (1ULL << anceParser::IDENTIFIER))) != 0)) {
      setState(165);
      expression();
    }
    setState(168);
    match(anceParser::T__0);
   
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

anceParser::Variable_expressionContext* anceParser::ExpressionContext::variable_expression() {
  return getRuleContext<anceParser::Variable_expressionContext>(0);
}

anceParser::Sizeof_type_expressionContext* anceParser::ExpressionContext::sizeof_type_expression() {
  return getRuleContext<anceParser::Sizeof_type_expressionContext>(0);
}

anceParser::Sizeof_exp_expressionContext* anceParser::ExpressionContext::sizeof_exp_expression() {
  return getRuleContext<anceParser::Sizeof_exp_expressionContext>(0);
}

anceParser::Constant_expressionContext* anceParser::ExpressionContext::constant_expression() {
  return getRuleContext<anceParser::Constant_expressionContext>(0);
}

anceParser::Independent_expressionContext* anceParser::ExpressionContext::independent_expression() {
  return getRuleContext<anceParser::Independent_expressionContext>(0);
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
  enterRule(_localctx, 30, anceParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(175);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(170);
      variable_expression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(171);
      sizeof_type_expression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(172);
      sizeof_exp_expression();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(173);
      constant_expression();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(174);
      independent_expression();
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

//----------------- Independent_expressionContext ------------------------------------------------------------------

anceParser::Independent_expressionContext::Independent_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::Function_callContext* anceParser::Independent_expressionContext::function_call() {
  return getRuleContext<anceParser::Function_callContext>(0);
}


size_t anceParser::Independent_expressionContext::getRuleIndex() const {
  return anceParser::RuleIndependent_expression;
}


antlrcpp::Any anceParser::Independent_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitIndependent_expression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Independent_expressionContext* anceParser::independent_expression() {
  Independent_expressionContext *_localctx = _tracker.createInstance<Independent_expressionContext>(_ctx, getState());
  enterRule(_localctx, 32, anceParser::RuleIndependent_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(177);
    function_call();
   
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

anceParser::ArgumentsContext* anceParser::Function_callContext::arguments() {
  return getRuleContext<anceParser::ArgumentsContext>(0);
}


size_t anceParser::Function_callContext::getRuleIndex() const {
  return anceParser::RuleFunction_call;
}


antlrcpp::Any anceParser::Function_callContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFunction_call(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Function_callContext* anceParser::function_call() {
  Function_callContext *_localctx = _tracker.createInstance<Function_callContext>(_ctx, getState());
  enterRule(_localctx, 34, anceParser::RuleFunction_call);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(179);
    match(anceParser::IDENTIFIER);
    setState(180);
    match(anceParser::T__1);
    setState(181);
    arguments();
    setState(182);
    match(anceParser::T__2);
   
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
  enterRule(_localctx, 36, anceParser::RuleArguments);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(192);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::SIGNED_INTEGER)
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
      | (1ULL << anceParser::SIZEOF)
      | (1ULL << anceParser::IDENTIFIER))) != 0)) {
      setState(184);
      expression();
      setState(189);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(185);
        match(anceParser::T__5);
        setState(186);
        expression();
        setState(191);
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

//----------------- Variable_expressionContext ------------------------------------------------------------------

anceParser::Variable_expressionContext::Variable_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Variable_expressionContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}


size_t anceParser::Variable_expressionContext::getRuleIndex() const {
  return anceParser::RuleVariable_expression;
}


antlrcpp::Any anceParser::Variable_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVariable_expression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Variable_expressionContext* anceParser::variable_expression() {
  Variable_expressionContext *_localctx = _tracker.createInstance<Variable_expressionContext>(_ctx, getState());
  enterRule(_localctx, 38, anceParser::RuleVariable_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(194);
    match(anceParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sizeof_type_expressionContext ------------------------------------------------------------------

anceParser::Sizeof_type_expressionContext::Sizeof_type_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Sizeof_type_expressionContext::SIZEOF() {
  return getToken(anceParser::SIZEOF, 0);
}

anceParser::TypeContext* anceParser::Sizeof_type_expressionContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}


size_t anceParser::Sizeof_type_expressionContext::getRuleIndex() const {
  return anceParser::RuleSizeof_type_expression;
}


antlrcpp::Any anceParser::Sizeof_type_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSizeof_type_expression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Sizeof_type_expressionContext* anceParser::sizeof_type_expression() {
  Sizeof_type_expressionContext *_localctx = _tracker.createInstance<Sizeof_type_expressionContext>(_ctx, getState());
  enterRule(_localctx, 40, anceParser::RuleSizeof_type_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(196);
    match(anceParser::SIZEOF);
    setState(197);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Sizeof_exp_expressionContext ------------------------------------------------------------------

anceParser::Sizeof_exp_expressionContext::Sizeof_exp_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Sizeof_exp_expressionContext::SIZEOF() {
  return getToken(anceParser::SIZEOF, 0);
}

anceParser::ExpressionContext* anceParser::Sizeof_exp_expressionContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::Sizeof_exp_expressionContext::getRuleIndex() const {
  return anceParser::RuleSizeof_exp_expression;
}


antlrcpp::Any anceParser::Sizeof_exp_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSizeof_exp_expression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Sizeof_exp_expressionContext* anceParser::sizeof_exp_expression() {
  Sizeof_exp_expressionContext *_localctx = _tracker.createInstance<Sizeof_exp_expressionContext>(_ctx, getState());
  enterRule(_localctx, 42, anceParser::RuleSizeof_exp_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(199);
    match(anceParser::SIZEOF);
    setState(200);
    match(anceParser::T__1);
    setState(201);
    expression();
    setState(202);
    match(anceParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Constant_expressionContext ------------------------------------------------------------------

anceParser::Constant_expressionContext::Constant_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::String_expressionContext* anceParser::Constant_expressionContext::string_expression() {
  return getRuleContext<anceParser::String_expressionContext>(0);
}

anceParser::Byte_expressionContext* anceParser::Constant_expressionContext::byte_expression() {
  return getRuleContext<anceParser::Byte_expressionContext>(0);
}

anceParser::Integer_expressionContext* anceParser::Constant_expressionContext::integer_expression() {
  return getRuleContext<anceParser::Integer_expressionContext>(0);
}

anceParser::Floating_point_expressionContext* anceParser::Constant_expressionContext::floating_point_expression() {
  return getRuleContext<anceParser::Floating_point_expressionContext>(0);
}

anceParser::Boolean_expressionContext* anceParser::Constant_expressionContext::boolean_expression() {
  return getRuleContext<anceParser::Boolean_expressionContext>(0);
}


size_t anceParser::Constant_expressionContext::getRuleIndex() const {
  return anceParser::RuleConstant_expression;
}


antlrcpp::Any anceParser::Constant_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitConstant_expression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Constant_expressionContext* anceParser::constant_expression() {
  Constant_expressionContext *_localctx = _tracker.createInstance<Constant_expressionContext>(_ctx, getState());
  enterRule(_localctx, 44, anceParser::RuleConstant_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(209);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(204);
        string_expression();
        break;
      }

      case anceParser::BYTE: {
        enterOuterAlt(_localctx, 2);
        setState(205);
        byte_expression();
        break;
      }

      case anceParser::SIGNED_INTEGER:
      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER:
      case anceParser::INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(206);
        integer_expression();
        break;
      }

      case anceParser::HALF:
      case anceParser::SINGLE:
      case anceParser::DOUBLE:
      case anceParser::QUAD: {
        enterOuterAlt(_localctx, 4);
        setState(207);
        floating_point_expression();
        break;
      }

      case anceParser::TRUE:
      case anceParser::FALSE: {
        enterOuterAlt(_localctx, 5);
        setState(208);
        boolean_expression();
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

//----------------- String_expressionContext ------------------------------------------------------------------

anceParser::String_expressionContext::String_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::String_expressionContext::STRING() {
  return getToken(anceParser::STRING, 0);
}


size_t anceParser::String_expressionContext::getRuleIndex() const {
  return anceParser::RuleString_expression;
}


antlrcpp::Any anceParser::String_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitString_expression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::String_expressionContext* anceParser::string_expression() {
  String_expressionContext *_localctx = _tracker.createInstance<String_expressionContext>(_ctx, getState());
  enterRule(_localctx, 46, anceParser::RuleString_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(211);
    match(anceParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Byte_expressionContext ------------------------------------------------------------------

anceParser::Byte_expressionContext::Byte_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Byte_expressionContext::BYTE() {
  return getToken(anceParser::BYTE, 0);
}


size_t anceParser::Byte_expressionContext::getRuleIndex() const {
  return anceParser::RuleByte_expression;
}


antlrcpp::Any anceParser::Byte_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitByte_expression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Byte_expressionContext* anceParser::byte_expression() {
  Byte_expressionContext *_localctx = _tracker.createInstance<Byte_expressionContext>(_ctx, getState());
  enterRule(_localctx, 48, anceParser::RuleByte_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(213);
    match(anceParser::BYTE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Integer_expressionContext ------------------------------------------------------------------

anceParser::Integer_expressionContext::Integer_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::Unsigned_integerContext* anceParser::Integer_expressionContext::unsigned_integer() {
  return getRuleContext<anceParser::Unsigned_integerContext>(0);
}

anceParser::Signed_integerContext* anceParser::Integer_expressionContext::signed_integer() {
  return getRuleContext<anceParser::Signed_integerContext>(0);
}

anceParser::Special_integerContext* anceParser::Integer_expressionContext::special_integer() {
  return getRuleContext<anceParser::Special_integerContext>(0);
}


size_t anceParser::Integer_expressionContext::getRuleIndex() const {
  return anceParser::RuleInteger_expression;
}


antlrcpp::Any anceParser::Integer_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitInteger_expression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Integer_expressionContext* anceParser::integer_expression() {
  Integer_expressionContext *_localctx = _tracker.createInstance<Integer_expressionContext>(_ctx, getState());
  enterRule(_localctx, 50, anceParser::RuleInteger_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(218);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(215);
        unsigned_integer();
        break;
      }

      case anceParser::SIGNED_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(216);
        signed_integer();
        break;
      }

      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(217);
        special_integer();
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

//----------------- Unsigned_integerContext ------------------------------------------------------------------

anceParser::Unsigned_integerContext::Unsigned_integerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> anceParser::Unsigned_integerContext::INTEGER() {
  return getTokens(anceParser::INTEGER);
}

tree::TerminalNode* anceParser::Unsigned_integerContext::INTEGER(size_t i) {
  return getToken(anceParser::INTEGER, i);
}


size_t anceParser::Unsigned_integerContext::getRuleIndex() const {
  return anceParser::RuleUnsigned_integer;
}


antlrcpp::Any anceParser::Unsigned_integerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitUnsigned_integer(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Unsigned_integerContext* anceParser::unsigned_integer() {
  Unsigned_integerContext *_localctx = _tracker.createInstance<Unsigned_integerContext>(_ctx, getState());
  enterRule(_localctx, 52, anceParser::RuleUnsigned_integer);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(220);
    match(anceParser::INTEGER);
    setState(223);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__6) {
      setState(221);
      match(anceParser::T__6);
      setState(222);
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

//----------------- Signed_integerContext ------------------------------------------------------------------

anceParser::Signed_integerContext::Signed_integerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Signed_integerContext::SIGNED_INTEGER() {
  return getToken(anceParser::SIGNED_INTEGER, 0);
}

tree::TerminalNode* anceParser::Signed_integerContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}


size_t anceParser::Signed_integerContext::getRuleIndex() const {
  return anceParser::RuleSigned_integer;
}


antlrcpp::Any anceParser::Signed_integerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSigned_integer(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Signed_integerContext* anceParser::signed_integer() {
  Signed_integerContext *_localctx = _tracker.createInstance<Signed_integerContext>(_ctx, getState());
  enterRule(_localctx, 54, anceParser::RuleSigned_integer);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(225);
    match(anceParser::SIGNED_INTEGER);
    setState(228);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__6) {
      setState(226);
      match(anceParser::T__6);
      setState(227);
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

//----------------- Special_integerContext ------------------------------------------------------------------

anceParser::Special_integerContext::Special_integerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Special_integerContext::HEX_INTEGER() {
  return getToken(anceParser::HEX_INTEGER, 0);
}

tree::TerminalNode* anceParser::Special_integerContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}

tree::TerminalNode* anceParser::Special_integerContext::BIN_INTEGER() {
  return getToken(anceParser::BIN_INTEGER, 0);
}

tree::TerminalNode* anceParser::Special_integerContext::OCT_INTEGER() {
  return getToken(anceParser::OCT_INTEGER, 0);
}


size_t anceParser::Special_integerContext::getRuleIndex() const {
  return anceParser::RuleSpecial_integer;
}


antlrcpp::Any anceParser::Special_integerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSpecial_integer(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Special_integerContext* anceParser::special_integer() {
  Special_integerContext *_localctx = _tracker.createInstance<Special_integerContext>(_ctx, getState());
  enterRule(_localctx, 56, anceParser::RuleSpecial_integer);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(245);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::HEX_INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(230);
        match(anceParser::HEX_INTEGER);
        setState(233);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::T__6) {
          setState(231);
          match(anceParser::T__6);
          setState(232);
          match(anceParser::INTEGER);
        }
        break;
      }

      case anceParser::BIN_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(235);
        match(anceParser::BIN_INTEGER);
        setState(238);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::T__6) {
          setState(236);
          match(anceParser::T__6);
          setState(237);
          match(anceParser::INTEGER);
        }
        break;
      }

      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(240);
        match(anceParser::OCT_INTEGER);
        setState(243);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::T__6) {
          setState(241);
          match(anceParser::T__6);
          setState(242);
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

//----------------- Floating_point_expressionContext ------------------------------------------------------------------

anceParser::Floating_point_expressionContext::Floating_point_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Floating_point_expressionContext::HALF() {
  return getToken(anceParser::HALF, 0);
}

tree::TerminalNode* anceParser::Floating_point_expressionContext::SINGLE() {
  return getToken(anceParser::SINGLE, 0);
}

tree::TerminalNode* anceParser::Floating_point_expressionContext::DOUBLE() {
  return getToken(anceParser::DOUBLE, 0);
}

tree::TerminalNode* anceParser::Floating_point_expressionContext::QUAD() {
  return getToken(anceParser::QUAD, 0);
}


size_t anceParser::Floating_point_expressionContext::getRuleIndex() const {
  return anceParser::RuleFloating_point_expression;
}


antlrcpp::Any anceParser::Floating_point_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFloating_point_expression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Floating_point_expressionContext* anceParser::floating_point_expression() {
  Floating_point_expressionContext *_localctx = _tracker.createInstance<Floating_point_expressionContext>(_ctx, getState());
  enterRule(_localctx, 58, anceParser::RuleFloating_point_expression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(247);
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

//----------------- Boolean_expressionContext ------------------------------------------------------------------

anceParser::Boolean_expressionContext::Boolean_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Boolean_expressionContext::TRUE() {
  return getToken(anceParser::TRUE, 0);
}

tree::TerminalNode* anceParser::Boolean_expressionContext::FALSE() {
  return getToken(anceParser::FALSE, 0);
}


size_t anceParser::Boolean_expressionContext::getRuleIndex() const {
  return anceParser::RuleBoolean_expression;
}


antlrcpp::Any anceParser::Boolean_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBoolean_expression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Boolean_expressionContext* anceParser::boolean_expression() {
  Boolean_expressionContext *_localctx = _tracker.createInstance<Boolean_expressionContext>(_ctx, getState());
  enterRule(_localctx, 60, anceParser::RuleBoolean_expression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(249);
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

anceParser::Integer_typeContext* anceParser::TypeContext::integer_type() {
  return getRuleContext<anceParser::Integer_typeContext>(0);
}

anceParser::Array_typeContext* anceParser::TypeContext::array_type() {
  return getRuleContext<anceParser::Array_typeContext>(0);
}

anceParser::Keyword_typeContext* anceParser::TypeContext::keyword_type() {
  return getRuleContext<anceParser::Keyword_typeContext>(0);
}


size_t anceParser::TypeContext::getRuleIndex() const {
  return anceParser::RuleType;
}


antlrcpp::Any anceParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::TypeContext* anceParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 62, anceParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(254);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::NATIVE_INTEGER_TYPE: {
        enterOuterAlt(_localctx, 1);
        setState(251);
        integer_type();
        break;
      }

      case anceParser::T__7: {
        enterOuterAlt(_localctx, 2);
        setState(252);
        array_type();
        break;
      }

      case anceParser::HALF_TYPE:
      case anceParser::SINGLE_TYPE:
      case anceParser::DOUBLE_TYPE:
      case anceParser::QUAD_TYPE:
      case anceParser::SIZE:
      case anceParser::UIPTR:
      case anceParser::VOID: {
        enterOuterAlt(_localctx, 3);
        setState(253);
        keyword_type();
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

//----------------- Integer_typeContext ------------------------------------------------------------------

anceParser::Integer_typeContext::Integer_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Integer_typeContext::NATIVE_INTEGER_TYPE() {
  return getToken(anceParser::NATIVE_INTEGER_TYPE, 0);
}


size_t anceParser::Integer_typeContext::getRuleIndex() const {
  return anceParser::RuleInteger_type;
}


antlrcpp::Any anceParser::Integer_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitInteger_type(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Integer_typeContext* anceParser::integer_type() {
  Integer_typeContext *_localctx = _tracker.createInstance<Integer_typeContext>(_ctx, getState());
  enterRule(_localctx, 64, anceParser::RuleInteger_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(256);
    match(anceParser::NATIVE_INTEGER_TYPE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Array_typeContext ------------------------------------------------------------------

anceParser::Array_typeContext::Array_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Array_typeContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}

anceParser::TypeContext* anceParser::Array_typeContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}


size_t anceParser::Array_typeContext::getRuleIndex() const {
  return anceParser::RuleArray_type;
}


antlrcpp::Any anceParser::Array_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitArray_type(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Array_typeContext* anceParser::array_type() {
  Array_typeContext *_localctx = _tracker.createInstance<Array_typeContext>(_ctx, getState());
  enterRule(_localctx, 66, anceParser::RuleArray_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(258);
    match(anceParser::T__7);
    setState(259);
    match(anceParser::INTEGER);
    setState(260);
    match(anceParser::T__6);
    setState(261);
    type();
    setState(262);
    match(anceParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Keyword_typeContext ------------------------------------------------------------------

anceParser::Keyword_typeContext::Keyword_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::Floating_point_typeContext* anceParser::Keyword_typeContext::floating_point_type() {
  return getRuleContext<anceParser::Floating_point_typeContext>(0);
}

anceParser::Size_typeContext* anceParser::Keyword_typeContext::size_type() {
  return getRuleContext<anceParser::Size_typeContext>(0);
}

anceParser::Unsigned_integer_pointer_typeContext* anceParser::Keyword_typeContext::unsigned_integer_pointer_type() {
  return getRuleContext<anceParser::Unsigned_integer_pointer_typeContext>(0);
}

anceParser::Void_typeContext* anceParser::Keyword_typeContext::void_type() {
  return getRuleContext<anceParser::Void_typeContext>(0);
}


size_t anceParser::Keyword_typeContext::getRuleIndex() const {
  return anceParser::RuleKeyword_type;
}


antlrcpp::Any anceParser::Keyword_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitKeyword_type(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Keyword_typeContext* anceParser::keyword_type() {
  Keyword_typeContext *_localctx = _tracker.createInstance<Keyword_typeContext>(_ctx, getState());
  enterRule(_localctx, 68, anceParser::RuleKeyword_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(268);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::HALF_TYPE:
      case anceParser::SINGLE_TYPE:
      case anceParser::DOUBLE_TYPE:
      case anceParser::QUAD_TYPE: {
        enterOuterAlt(_localctx, 1);
        setState(264);
        floating_point_type();
        break;
      }

      case anceParser::SIZE: {
        enterOuterAlt(_localctx, 2);
        setState(265);
        size_type();
        break;
      }

      case anceParser::UIPTR: {
        enterOuterAlt(_localctx, 3);
        setState(266);
        unsigned_integer_pointer_type();
        break;
      }

      case anceParser::VOID: {
        enterOuterAlt(_localctx, 4);
        setState(267);
        void_type();
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

//----------------- Floating_point_typeContext ------------------------------------------------------------------

anceParser::Floating_point_typeContext::Floating_point_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Floating_point_typeContext::HALF_TYPE() {
  return getToken(anceParser::HALF_TYPE, 0);
}

tree::TerminalNode* anceParser::Floating_point_typeContext::SINGLE_TYPE() {
  return getToken(anceParser::SINGLE_TYPE, 0);
}

tree::TerminalNode* anceParser::Floating_point_typeContext::DOUBLE_TYPE() {
  return getToken(anceParser::DOUBLE_TYPE, 0);
}

tree::TerminalNode* anceParser::Floating_point_typeContext::QUAD_TYPE() {
  return getToken(anceParser::QUAD_TYPE, 0);
}


size_t anceParser::Floating_point_typeContext::getRuleIndex() const {
  return anceParser::RuleFloating_point_type;
}


antlrcpp::Any anceParser::Floating_point_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFloating_point_type(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Floating_point_typeContext* anceParser::floating_point_type() {
  Floating_point_typeContext *_localctx = _tracker.createInstance<Floating_point_typeContext>(_ctx, getState());
  enterRule(_localctx, 70, anceParser::RuleFloating_point_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(270);
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

//----------------- Size_typeContext ------------------------------------------------------------------

anceParser::Size_typeContext::Size_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Size_typeContext::SIZE() {
  return getToken(anceParser::SIZE, 0);
}


size_t anceParser::Size_typeContext::getRuleIndex() const {
  return anceParser::RuleSize_type;
}


antlrcpp::Any anceParser::Size_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSize_type(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Size_typeContext* anceParser::size_type() {
  Size_typeContext *_localctx = _tracker.createInstance<Size_typeContext>(_ctx, getState());
  enterRule(_localctx, 72, anceParser::RuleSize_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(272);
    match(anceParser::SIZE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Unsigned_integer_pointer_typeContext ------------------------------------------------------------------

anceParser::Unsigned_integer_pointer_typeContext::Unsigned_integer_pointer_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Unsigned_integer_pointer_typeContext::UIPTR() {
  return getToken(anceParser::UIPTR, 0);
}


size_t anceParser::Unsigned_integer_pointer_typeContext::getRuleIndex() const {
  return anceParser::RuleUnsigned_integer_pointer_type;
}


antlrcpp::Any anceParser::Unsigned_integer_pointer_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitUnsigned_integer_pointer_type(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Unsigned_integer_pointer_typeContext* anceParser::unsigned_integer_pointer_type() {
  Unsigned_integer_pointer_typeContext *_localctx = _tracker.createInstance<Unsigned_integer_pointer_typeContext>(_ctx, getState());
  enterRule(_localctx, 74, anceParser::RuleUnsigned_integer_pointer_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(274);
    match(anceParser::UIPTR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Void_typeContext ------------------------------------------------------------------

anceParser::Void_typeContext::Void_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Void_typeContext::VOID() {
  return getToken(anceParser::VOID, 0);
}


size_t anceParser::Void_typeContext::getRuleIndex() const {
  return anceParser::RuleVoid_type;
}


antlrcpp::Any anceParser::Void_typeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVoid_type(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Void_typeContext* anceParser::void_type() {
  Void_typeContext *_localctx = _tracker.createInstance<Void_typeContext>(_ctx, getState());
  enterRule(_localctx, 76, anceParser::RuleVoid_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(276);
    match(anceParser::VOID);
   
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
  "file", "data", "constant_declaration", "variable_declaration", "code", 
  "function", "parameters", "parameter", "access_modifier", "statement", 
  "expression_statement", "local_variable_definition", "variable_assignment", 
  "print_statement", "return_statement", "expression", "independent_expression", 
  "function_call", "arguments", "variable_expression", "sizeof_type_expression", 
  "sizeof_exp_expression", "constant_expression", "string_expression", "byte_expression", 
  "integer_expression", "unsigned_integer", "signed_integer", "special_integer", 
  "floating_point_expression", "boolean_expression", "type", "integer_type", 
  "array_type", "keyword_type", "floating_point_type", "size_type", "unsigned_integer_pointer_type", 
  "void_type"
};

std::vector<std::string> anceParser::_literalNames = {
  "", "';'", "'('", "')'", "'{'", "'}'", "','", "':'", "'['", "']'", "", 
  "'half'", "'single'", "'double'", "'quad'", "", "", "", "", "", "", "", 
  "", "", "", "", "", "'true'", "'false'", "'sizeof'", "'size'", "'uiptr'", 
  "'print'", "'return'", "'const'", "'public'", "'private'", "'void'", "", 
  "':='", "'<-'"
};

std::vector<std::string> anceParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "NATIVE_INTEGER_TYPE", "HALF_TYPE", 
  "SINGLE_TYPE", "DOUBLE_TYPE", "QUAD_TYPE", "SIGNED_INTEGER", "HEX_INTEGER", 
  "BIN_INTEGER", "OCT_INTEGER", "HALF", "SINGLE", "DOUBLE", "QUAD", "DECIMAL", 
  "STRING", "BYTE", "INTEGER", "TRUE", "FALSE", "SIZEOF", "SIZE", "UIPTR", 
  "PRINT", "RETURN", "CONST", "PUBLIC", "PRIVATE", "VOID", "IDENTIFIER", 
  "DEFINITION", "ASSIGNMENT", "WHITESPACE", "BLOCK_COMMENT", "LINE_COMMENT"
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
    0x3, 0x2d, 0x119, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
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
    0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x53, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x56, 
    0xb, 0x2, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x5a, 0xa, 0x3, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x69, 0xa, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x6, 0x7, 0x77, 0xa, 
    0x7, 0xd, 0x7, 0xe, 0x7, 0x78, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x7, 0x8, 0x80, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x83, 0xb, 0x8, 
    0x5, 0x8, 0x85, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x91, 
    0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x5, 0xd, 0x9a, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0xa9, 0xa, 0x10, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 
    0xb2, 0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 0xbe, 
    0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0xc1, 0xb, 0x14, 0x5, 0x14, 0xc3, 0xa, 
    0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0xd4, 0xa, 0x18, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 
    0xdd, 0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0xe2, 0xa, 
    0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0xe7, 0xa, 0x1d, 0x3, 
    0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x5, 0x1e, 0xec, 0xa, 0x1e, 0x3, 0x1e, 0x3, 
    0x1e, 0x3, 0x1e, 0x5, 0x1e, 0xf1, 0xa, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 
    0x1e, 0x5, 0x1e, 0xf6, 0xa, 0x1e, 0x5, 0x1e, 0xf8, 0xa, 0x1e, 0x3, 0x1f, 
    0x3, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 
    0x21, 0x101, 0xa, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 
    0x24, 0x3, 0x24, 0x5, 0x24, 0x10f, 0xa, 0x24, 0x3, 0x25, 0x3, 0x25, 
    0x3, 0x26, 0x3, 0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 
    0x28, 0x2, 0x2, 0x29, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 
    0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 
    0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 
    0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x2, 0x6, 0x3, 0x2, 0x25, 0x26, 
    0x3, 0x2, 0x15, 0x18, 0x3, 0x2, 0x1d, 0x1e, 0x3, 0x2, 0xd, 0x10, 0x2, 
    0x116, 0x2, 0x54, 0x3, 0x2, 0x2, 0x2, 0x4, 0x59, 0x3, 0x2, 0x2, 0x2, 
    0x6, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x8, 0x63, 0x3, 0x2, 0x2, 0x2, 0xa, 0x6c, 
    0x3, 0x2, 0x2, 0x2, 0xc, 0x6e, 0x3, 0x2, 0x2, 0x2, 0xe, 0x84, 0x3, 0x2, 
    0x2, 0x2, 0x10, 0x86, 0x3, 0x2, 0x2, 0x2, 0x12, 0x89, 0x3, 0x2, 0x2, 
    0x2, 0x14, 0x90, 0x3, 0x2, 0x2, 0x2, 0x16, 0x92, 0x3, 0x2, 0x2, 0x2, 
    0x18, 0x95, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x1c, 
    0xa2, 0x3, 0x2, 0x2, 0x2, 0x1e, 0xa6, 0x3, 0x2, 0x2, 0x2, 0x20, 0xb1, 
    0x3, 0x2, 0x2, 0x2, 0x22, 0xb3, 0x3, 0x2, 0x2, 0x2, 0x24, 0xb5, 0x3, 
    0x2, 0x2, 0x2, 0x26, 0xc2, 0x3, 0x2, 0x2, 0x2, 0x28, 0xc4, 0x3, 0x2, 
    0x2, 0x2, 0x2a, 0xc6, 0x3, 0x2, 0x2, 0x2, 0x2c, 0xc9, 0x3, 0x2, 0x2, 
    0x2, 0x2e, 0xd3, 0x3, 0x2, 0x2, 0x2, 0x30, 0xd5, 0x3, 0x2, 0x2, 0x2, 
    0x32, 0xd7, 0x3, 0x2, 0x2, 0x2, 0x34, 0xdc, 0x3, 0x2, 0x2, 0x2, 0x36, 
    0xde, 0x3, 0x2, 0x2, 0x2, 0x38, 0xe3, 0x3, 0x2, 0x2, 0x2, 0x3a, 0xf7, 
    0x3, 0x2, 0x2, 0x2, 0x3c, 0xf9, 0x3, 0x2, 0x2, 0x2, 0x3e, 0xfb, 0x3, 
    0x2, 0x2, 0x2, 0x40, 0x100, 0x3, 0x2, 0x2, 0x2, 0x42, 0x102, 0x3, 0x2, 
    0x2, 0x2, 0x44, 0x104, 0x3, 0x2, 0x2, 0x2, 0x46, 0x10e, 0x3, 0x2, 0x2, 
    0x2, 0x48, 0x110, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x112, 0x3, 0x2, 0x2, 0x2, 
    0x4c, 0x114, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x116, 0x3, 0x2, 0x2, 0x2, 0x50, 
    0x53, 0x5, 0x4, 0x3, 0x2, 0x51, 0x53, 0x5, 0xa, 0x6, 0x2, 0x52, 0x50, 
    0x3, 0x2, 0x2, 0x2, 0x52, 0x51, 0x3, 0x2, 0x2, 0x2, 0x53, 0x56, 0x3, 
    0x2, 0x2, 0x2, 0x54, 0x52, 0x3, 0x2, 0x2, 0x2, 0x54, 0x55, 0x3, 0x2, 
    0x2, 0x2, 0x55, 0x3, 0x3, 0x2, 0x2, 0x2, 0x56, 0x54, 0x3, 0x2, 0x2, 
    0x2, 0x57, 0x5a, 0x5, 0x6, 0x4, 0x2, 0x58, 0x5a, 0x5, 0x8, 0x5, 0x2, 
    0x59, 0x57, 0x3, 0x2, 0x2, 0x2, 0x59, 0x58, 0x3, 0x2, 0x2, 0x2, 0x5a, 
    0x5, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5c, 0x5, 0x12, 0xa, 0x2, 0x5c, 0x5d, 
    0x7, 0x24, 0x2, 0x2, 0x5d, 0x5e, 0x5, 0x40, 0x21, 0x2, 0x5e, 0x5f, 0x7, 
    0x28, 0x2, 0x2, 0x5f, 0x60, 0x7, 0x29, 0x2, 0x2, 0x60, 0x61, 0x5, 0x2e, 
    0x18, 0x2, 0x61, 0x62, 0x7, 0x3, 0x2, 0x2, 0x62, 0x7, 0x3, 0x2, 0x2, 
    0x2, 0x63, 0x64, 0x5, 0x12, 0xa, 0x2, 0x64, 0x65, 0x5, 0x40, 0x21, 0x2, 
    0x65, 0x68, 0x7, 0x28, 0x2, 0x2, 0x66, 0x67, 0x7, 0x2a, 0x2, 0x2, 0x67, 
    0x69, 0x5, 0x2e, 0x18, 0x2, 0x68, 0x66, 0x3, 0x2, 0x2, 0x2, 0x68, 0x69, 
    0x3, 0x2, 0x2, 0x2, 0x69, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6b, 0x7, 
    0x3, 0x2, 0x2, 0x6b, 0x9, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x5, 0xc, 
    0x7, 0x2, 0x6d, 0xb, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6f, 0x5, 0x12, 0xa, 
    0x2, 0x6f, 0x70, 0x5, 0x40, 0x21, 0x2, 0x70, 0x71, 0x7, 0x28, 0x2, 0x2, 
    0x71, 0x72, 0x7, 0x4, 0x2, 0x2, 0x72, 0x73, 0x5, 0xe, 0x8, 0x2, 0x73, 
    0x74, 0x7, 0x5, 0x2, 0x2, 0x74, 0x76, 0x7, 0x6, 0x2, 0x2, 0x75, 0x77, 
    0x5, 0x14, 0xb, 0x2, 0x76, 0x75, 0x3, 0x2, 0x2, 0x2, 0x77, 0x78, 0x3, 
    0x2, 0x2, 0x2, 0x78, 0x76, 0x3, 0x2, 0x2, 0x2, 0x78, 0x79, 0x3, 0x2, 
    0x2, 0x2, 0x79, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7b, 0x7, 0x7, 0x2, 
    0x2, 0x7b, 0xd, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x81, 0x5, 0x10, 0x9, 0x2, 
    0x7d, 0x7e, 0x7, 0x8, 0x2, 0x2, 0x7e, 0x80, 0x5, 0x10, 0x9, 0x2, 0x7f, 
    0x7d, 0x3, 0x2, 0x2, 0x2, 0x80, 0x83, 0x3, 0x2, 0x2, 0x2, 0x81, 0x7f, 
    0x3, 0x2, 0x2, 0x2, 0x81, 0x82, 0x3, 0x2, 0x2, 0x2, 0x82, 0x85, 0x3, 
    0x2, 0x2, 0x2, 0x83, 0x81, 0x3, 0x2, 0x2, 0x2, 0x84, 0x7c, 0x3, 0x2, 
    0x2, 0x2, 0x84, 0x85, 0x3, 0x2, 0x2, 0x2, 0x85, 0xf, 0x3, 0x2, 0x2, 
    0x2, 0x86, 0x87, 0x5, 0x40, 0x21, 0x2, 0x87, 0x88, 0x7, 0x28, 0x2, 0x2, 
    0x88, 0x11, 0x3, 0x2, 0x2, 0x2, 0x89, 0x8a, 0x9, 0x2, 0x2, 0x2, 0x8a, 
    0x13, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x91, 0x5, 0x16, 0xc, 0x2, 0x8c, 0x91, 
    0x5, 0x18, 0xd, 0x2, 0x8d, 0x91, 0x5, 0x1a, 0xe, 0x2, 0x8e, 0x91, 0x5, 
    0x1c, 0xf, 0x2, 0x8f, 0x91, 0x5, 0x1e, 0x10, 0x2, 0x90, 0x8b, 0x3, 0x2, 
    0x2, 0x2, 0x90, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x90, 0x8d, 0x3, 0x2, 0x2, 
    0x2, 0x90, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x90, 0x8f, 0x3, 0x2, 0x2, 0x2, 
    0x91, 0x15, 0x3, 0x2, 0x2, 0x2, 0x92, 0x93, 0x5, 0x22, 0x12, 0x2, 0x93, 
    0x94, 0x7, 0x3, 0x2, 0x2, 0x94, 0x17, 0x3, 0x2, 0x2, 0x2, 0x95, 0x96, 
    0x5, 0x40, 0x21, 0x2, 0x96, 0x99, 0x7, 0x28, 0x2, 0x2, 0x97, 0x98, 0x7, 
    0x2a, 0x2, 0x2, 0x98, 0x9a, 0x5, 0x20, 0x11, 0x2, 0x99, 0x97, 0x3, 0x2, 
    0x2, 0x2, 0x99, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9b, 0x3, 0x2, 0x2, 
    0x2, 0x9b, 0x9c, 0x7, 0x3, 0x2, 0x2, 0x9c, 0x19, 0x3, 0x2, 0x2, 0x2, 
    0x9d, 0x9e, 0x7, 0x28, 0x2, 0x2, 0x9e, 0x9f, 0x7, 0x2a, 0x2, 0x2, 0x9f, 
    0xa0, 0x5, 0x20, 0x11, 0x2, 0xa0, 0xa1, 0x7, 0x3, 0x2, 0x2, 0xa1, 0x1b, 
    0x3, 0x2, 0x2, 0x2, 0xa2, 0xa3, 0x7, 0x22, 0x2, 0x2, 0xa3, 0xa4, 0x5, 
    0x20, 0x11, 0x2, 0xa4, 0xa5, 0x7, 0x3, 0x2, 0x2, 0xa5, 0x1d, 0x3, 0x2, 
    0x2, 0x2, 0xa6, 0xa8, 0x7, 0x23, 0x2, 0x2, 0xa7, 0xa9, 0x5, 0x20, 0x11, 
    0x2, 0xa8, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xa9, 0x3, 0x2, 0x2, 0x2, 
    0xa9, 0xaa, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xab, 0x7, 0x3, 0x2, 0x2, 0xab, 
    0x1f, 0x3, 0x2, 0x2, 0x2, 0xac, 0xb2, 0x5, 0x28, 0x15, 0x2, 0xad, 0xb2, 
    0x5, 0x2a, 0x16, 0x2, 0xae, 0xb2, 0x5, 0x2c, 0x17, 0x2, 0xaf, 0xb2, 
    0x5, 0x2e, 0x18, 0x2, 0xb0, 0xb2, 0x5, 0x22, 0x12, 0x2, 0xb1, 0xac, 
    0x3, 0x2, 0x2, 0x2, 0xb1, 0xad, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xae, 0x3, 
    0x2, 0x2, 0x2, 0xb1, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xb0, 0x3, 0x2, 
    0x2, 0x2, 0xb2, 0x21, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb4, 0x5, 0x24, 0x13, 
    0x2, 0xb4, 0x23, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb6, 0x7, 0x28, 0x2, 0x2, 
    0xb6, 0xb7, 0x7, 0x4, 0x2, 0x2, 0xb7, 0xb8, 0x5, 0x26, 0x14, 0x2, 0xb8, 
    0xb9, 0x7, 0x5, 0x2, 0x2, 0xb9, 0x25, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbf, 
    0x5, 0x20, 0x11, 0x2, 0xbb, 0xbc, 0x7, 0x8, 0x2, 0x2, 0xbc, 0xbe, 0x5, 
    0x20, 0x11, 0x2, 0xbd, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xc1, 0x3, 0x2, 
    0x2, 0x2, 0xbf, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xc0, 0x3, 0x2, 0x2, 
    0x2, 0xc0, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xbf, 0x3, 0x2, 0x2, 0x2, 
    0xc2, 0xba, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xc3, 0x3, 0x2, 0x2, 0x2, 0xc3, 
    0x27, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc5, 0x7, 0x28, 0x2, 0x2, 0xc5, 0x29, 
    0x3, 0x2, 0x2, 0x2, 0xc6, 0xc7, 0x7, 0x1f, 0x2, 0x2, 0xc7, 0xc8, 0x5, 
    0x40, 0x21, 0x2, 0xc8, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xca, 0x7, 0x1f, 
    0x2, 0x2, 0xca, 0xcb, 0x7, 0x4, 0x2, 0x2, 0xcb, 0xcc, 0x5, 0x20, 0x11, 
    0x2, 0xcc, 0xcd, 0x7, 0x5, 0x2, 0x2, 0xcd, 0x2d, 0x3, 0x2, 0x2, 0x2, 
    0xce, 0xd4, 0x5, 0x30, 0x19, 0x2, 0xcf, 0xd4, 0x5, 0x32, 0x1a, 0x2, 
    0xd0, 0xd4, 0x5, 0x34, 0x1b, 0x2, 0xd1, 0xd4, 0x5, 0x3c, 0x1f, 0x2, 
    0xd2, 0xd4, 0x5, 0x3e, 0x20, 0x2, 0xd3, 0xce, 0x3, 0x2, 0x2, 0x2, 0xd3, 
    0xcf, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd0, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd1, 
    0x3, 0x2, 0x2, 0x2, 0xd3, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xd4, 0x2f, 0x3, 
    0x2, 0x2, 0x2, 0xd5, 0xd6, 0x7, 0x1a, 0x2, 0x2, 0xd6, 0x31, 0x3, 0x2, 
    0x2, 0x2, 0xd7, 0xd8, 0x7, 0x1b, 0x2, 0x2, 0xd8, 0x33, 0x3, 0x2, 0x2, 
    0x2, 0xd9, 0xdd, 0x5, 0x36, 0x1c, 0x2, 0xda, 0xdd, 0x5, 0x38, 0x1d, 
    0x2, 0xdb, 0xdd, 0x5, 0x3a, 0x1e, 0x2, 0xdc, 0xd9, 0x3, 0x2, 0x2, 0x2, 
    0xdc, 0xda, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xdd, 
    0x35, 0x3, 0x2, 0x2, 0x2, 0xde, 0xe1, 0x7, 0x1c, 0x2, 0x2, 0xdf, 0xe0, 
    0x7, 0x9, 0x2, 0x2, 0xe0, 0xe2, 0x7, 0x1c, 0x2, 0x2, 0xe1, 0xdf, 0x3, 
    0x2, 0x2, 0x2, 0xe1, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe2, 0x37, 0x3, 0x2, 
    0x2, 0x2, 0xe3, 0xe6, 0x7, 0x11, 0x2, 0x2, 0xe4, 0xe5, 0x7, 0x9, 0x2, 
    0x2, 0xe5, 0xe7, 0x7, 0x1c, 0x2, 0x2, 0xe6, 0xe4, 0x3, 0x2, 0x2, 0x2, 
    0xe6, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xe7, 0x39, 0x3, 0x2, 0x2, 0x2, 0xe8, 
    0xeb, 0x7, 0x12, 0x2, 0x2, 0xe9, 0xea, 0x7, 0x9, 0x2, 0x2, 0xea, 0xec, 
    0x7, 0x1c, 0x2, 0x2, 0xeb, 0xe9, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xec, 0x3, 
    0x2, 0x2, 0x2, 0xec, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xed, 0xf0, 0x7, 0x13, 
    0x2, 0x2, 0xee, 0xef, 0x7, 0x9, 0x2, 0x2, 0xef, 0xf1, 0x7, 0x1c, 0x2, 
    0x2, 0xf0, 0xee, 0x3, 0x2, 0x2, 0x2, 0xf0, 0xf1, 0x3, 0x2, 0x2, 0x2, 
    0xf1, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xf5, 0x7, 0x14, 0x2, 0x2, 0xf3, 
    0xf4, 0x7, 0x9, 0x2, 0x2, 0xf4, 0xf6, 0x7, 0x1c, 0x2, 0x2, 0xf5, 0xf3, 
    0x3, 0x2, 0x2, 0x2, 0xf5, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf8, 0x3, 
    0x2, 0x2, 0x2, 0xf7, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xed, 0x3, 0x2, 
    0x2, 0x2, 0xf7, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf8, 0x3b, 0x3, 0x2, 0x2, 
    0x2, 0xf9, 0xfa, 0x9, 0x3, 0x2, 0x2, 0xfa, 0x3d, 0x3, 0x2, 0x2, 0x2, 
    0xfb, 0xfc, 0x9, 0x4, 0x2, 0x2, 0xfc, 0x3f, 0x3, 0x2, 0x2, 0x2, 0xfd, 
    0x101, 0x5, 0x42, 0x22, 0x2, 0xfe, 0x101, 0x5, 0x44, 0x23, 0x2, 0xff, 
    0x101, 0x5, 0x46, 0x24, 0x2, 0x100, 0xfd, 0x3, 0x2, 0x2, 0x2, 0x100, 
    0xfe, 0x3, 0x2, 0x2, 0x2, 0x100, 0xff, 0x3, 0x2, 0x2, 0x2, 0x101, 0x41, 
    0x3, 0x2, 0x2, 0x2, 0x102, 0x103, 0x7, 0xc, 0x2, 0x2, 0x103, 0x43, 0x3, 
    0x2, 0x2, 0x2, 0x104, 0x105, 0x7, 0xa, 0x2, 0x2, 0x105, 0x106, 0x7, 
    0x1c, 0x2, 0x2, 0x106, 0x107, 0x7, 0x9, 0x2, 0x2, 0x107, 0x108, 0x5, 
    0x40, 0x21, 0x2, 0x108, 0x109, 0x7, 0xb, 0x2, 0x2, 0x109, 0x45, 0x3, 
    0x2, 0x2, 0x2, 0x10a, 0x10f, 0x5, 0x48, 0x25, 0x2, 0x10b, 0x10f, 0x5, 
    0x4a, 0x26, 0x2, 0x10c, 0x10f, 0x5, 0x4c, 0x27, 0x2, 0x10d, 0x10f, 0x5, 
    0x4e, 0x28, 0x2, 0x10e, 0x10a, 0x3, 0x2, 0x2, 0x2, 0x10e, 0x10b, 0x3, 
    0x2, 0x2, 0x2, 0x10e, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x10e, 0x10d, 0x3, 
    0x2, 0x2, 0x2, 0x10f, 0x47, 0x3, 0x2, 0x2, 0x2, 0x110, 0x111, 0x9, 0x5, 
    0x2, 0x2, 0x111, 0x49, 0x3, 0x2, 0x2, 0x2, 0x112, 0x113, 0x7, 0x20, 
    0x2, 0x2, 0x113, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x114, 0x115, 0x7, 0x21, 
    0x2, 0x2, 0x115, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x116, 0x117, 0x7, 0x27, 
    0x2, 0x2, 0x117, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x19, 0x52, 0x54, 0x59, 0x68, 
    0x78, 0x81, 0x84, 0x90, 0x99, 0xa8, 0xb1, 0xbf, 0xc2, 0xd3, 0xdc, 0xe1, 
    0xe6, 0xeb, 0xf0, 0xf5, 0xf7, 0x100, 0x10e, 
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
