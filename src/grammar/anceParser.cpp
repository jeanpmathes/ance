
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
    setState(74);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == anceParser::PUBLIC

    || _la == anceParser::PRIVATE) {
      setState(72);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(70);
        data();
        break;
      }

      case 2: {
        setState(71);
        code();
        break;
      }

      }
      setState(76);
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
    setState(79);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(77);
      constant_declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(78);
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

tree::TerminalNode* anceParser::Constant_declarationContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
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
    setState(81);
    access_modifier();
    setState(82);
    match(anceParser::CONST);
    setState(83);
    type();
    setState(84);
    match(anceParser::IDENTIFIER);
    setState(85);
    match(anceParser::DEFINITION);
    setState(86);
    constant_expression();
    setState(87);
    match(anceParser::SEMICOLON);
   
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

tree::TerminalNode* anceParser::Variable_declarationContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
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
    setState(89);
    access_modifier();
    setState(90);
    type();
    setState(91);
    match(anceParser::IDENTIFIER);
    setState(94);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::ASSIGNMENT) {
      setState(92);
      match(anceParser::ASSIGNMENT);
      setState(93);
      constant_expression();
    }
    setState(96);
    match(anceParser::SEMICOLON);
   
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
    setState(98);
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

tree::TerminalNode* anceParser::FunctionContext::PARENTHESES_OPEN() {
  return getToken(anceParser::PARENTHESES_OPEN, 0);
}

anceParser::ParametersContext* anceParser::FunctionContext::parameters() {
  return getRuleContext<anceParser::ParametersContext>(0);
}

tree::TerminalNode* anceParser::FunctionContext::PARENTHESES_CLOSED() {
  return getToken(anceParser::PARENTHESES_CLOSED, 0);
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
    setState(100);
    access_modifier();
    setState(101);
    type();
    setState(102);
    match(anceParser::IDENTIFIER);
    setState(103);
    match(anceParser::PARENTHESES_OPEN);
    setState(104);
    parameters();
    setState(105);
    match(anceParser::PARENTHESES_CLOSED);
    setState(106);
    match(anceParser::BRACE_OPEN);
    setState(108); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(107);
      statement();
      setState(110); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::NATIVE_INTEGER_TYPE)
      | (1ULL << anceParser::HALF_TYPE)
      | (1ULL << anceParser::SINGLE_TYPE)
      | (1ULL << anceParser::DOUBLE_TYPE)
      | (1ULL << anceParser::QUAD_TYPE)
      | (1ULL << anceParser::SIZE)
      | (1ULL << anceParser::PRINT)
      | (1ULL << anceParser::RETURN)
      | (1ULL << anceParser::VOID)
      | (1ULL << anceParser::IDENTIFIER)
      | (1ULL << anceParser::BRACKET_OPEN))) != 0));
    setState(112);
    match(anceParser::BRACE_CLOSED);
   
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

std::vector<tree::TerminalNode *> anceParser::ParametersContext::COMMA() {
  return getTokens(anceParser::COMMA);
}

tree::TerminalNode* anceParser::ParametersContext::COMMA(size_t i) {
  return getToken(anceParser::COMMA, i);
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
    setState(122);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::NATIVE_INTEGER_TYPE)
      | (1ULL << anceParser::HALF_TYPE)
      | (1ULL << anceParser::SINGLE_TYPE)
      | (1ULL << anceParser::DOUBLE_TYPE)
      | (1ULL << anceParser::QUAD_TYPE)
      | (1ULL << anceParser::SIZE)
      | (1ULL << anceParser::VOID)
      | (1ULL << anceParser::BRACKET_OPEN))) != 0)) {
      setState(114);
      parameter();
      setState(119);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::COMMA) {
        setState(115);
        match(anceParser::COMMA);
        setState(116);
        parameter();
        setState(121);
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
    setState(124);
    type();
    setState(125);
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
    setState(127);
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
    setState(134);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(129);
      expression_statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(130);
      local_variable_definition();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(131);
      variable_assignment();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(132);
      print_statement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(133);
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

tree::TerminalNode* anceParser::Expression_statementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
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
    setState(136);
    independent_expression();
    setState(137);
    match(anceParser::SEMICOLON);
   
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

tree::TerminalNode* anceParser::Local_variable_definitionContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
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
    setState(139);
    type();
    setState(140);
    match(anceParser::IDENTIFIER);
    setState(143);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::ASSIGNMENT) {
      setState(141);
      match(anceParser::ASSIGNMENT);
      setState(142);
      expression();
    }
    setState(145);
    match(anceParser::SEMICOLON);
   
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

tree::TerminalNode* anceParser::Variable_assignmentContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
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
    setState(147);
    match(anceParser::IDENTIFIER);
    setState(148);
    match(anceParser::ASSIGNMENT);
    setState(149);
    expression();
    setState(150);
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

anceParser::ExpressionContext* anceParser::Print_statementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

tree::TerminalNode* anceParser::Print_statementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
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
    setState(152);
    match(anceParser::PRINT);
    setState(153);
    expression();
    setState(154);
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
    setState(156);
    match(anceParser::RETURN);
    setState(158);
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
      | (1ULL << anceParser::INTEGER)
      | (1ULL << anceParser::SIZEOF)
      | (1ULL << anceParser::IDENTIFIER))) != 0)) {
      setState(157);
      expression();
    }
    setState(160);
    match(anceParser::SEMICOLON);
   
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
    setState(167);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(162);
      variable_expression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(163);
      sizeof_type_expression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(164);
      sizeof_exp_expression();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(165);
      constant_expression();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(166);
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
    setState(169);
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

tree::TerminalNode* anceParser::Function_callContext::PARENTHESES_OPEN() {
  return getToken(anceParser::PARENTHESES_OPEN, 0);
}

anceParser::ArgumentsContext* anceParser::Function_callContext::arguments() {
  return getRuleContext<anceParser::ArgumentsContext>(0);
}

tree::TerminalNode* anceParser::Function_callContext::PARENTHESES_CLOSED() {
  return getToken(anceParser::PARENTHESES_CLOSED, 0);
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
    setState(171);
    match(anceParser::IDENTIFIER);
    setState(172);
    match(anceParser::PARENTHESES_OPEN);
    setState(173);
    arguments();
    setState(174);
    match(anceParser::PARENTHESES_CLOSED);
   
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

std::vector<tree::TerminalNode *> anceParser::ArgumentsContext::COMMA() {
  return getTokens(anceParser::COMMA);
}

tree::TerminalNode* anceParser::ArgumentsContext::COMMA(size_t i) {
  return getToken(anceParser::COMMA, i);
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
    setState(184);
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
      | (1ULL << anceParser::INTEGER)
      | (1ULL << anceParser::SIZEOF)
      | (1ULL << anceParser::IDENTIFIER))) != 0)) {
      setState(176);
      expression();
      setState(181);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::COMMA) {
        setState(177);
        match(anceParser::COMMA);
        setState(178);
        expression();
        setState(183);
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
    setState(186);
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
    setState(188);
    match(anceParser::SIZEOF);
    setState(189);
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

tree::TerminalNode* anceParser::Sizeof_exp_expressionContext::PARENTHESES_OPEN() {
  return getToken(anceParser::PARENTHESES_OPEN, 0);
}

anceParser::ExpressionContext* anceParser::Sizeof_exp_expressionContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

tree::TerminalNode* anceParser::Sizeof_exp_expressionContext::PARENTHESES_CLOSED() {
  return getToken(anceParser::PARENTHESES_CLOSED, 0);
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
    setState(191);
    match(anceParser::SIZEOF);
    setState(192);
    match(anceParser::PARENTHESES_OPEN);
    setState(193);
    expression();
    setState(194);
    match(anceParser::PARENTHESES_CLOSED);
   
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

anceParser::Literal_expressionContext* anceParser::Constant_expressionContext::literal_expression() {
  return getRuleContext<anceParser::Literal_expressionContext>(0);
}

anceParser::Integer_expressionContext* anceParser::Constant_expressionContext::integer_expression() {
  return getRuleContext<anceParser::Integer_expressionContext>(0);
}

anceParser::Floating_point_expressionContext* anceParser::Constant_expressionContext::floating_point_expression() {
  return getRuleContext<anceParser::Floating_point_expressionContext>(0);
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
    setState(199);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(196);
        literal_expression();
        break;
      }

      case anceParser::SIGNED_INTEGER:
      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER:
      case anceParser::INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(197);
        integer_expression();
        break;
      }

      case anceParser::HALF:
      case anceParser::SINGLE:
      case anceParser::DOUBLE:
      case anceParser::QUAD: {
        enterOuterAlt(_localctx, 3);
        setState(198);
        floating_point_expression();
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

//----------------- Literal_expressionContext ------------------------------------------------------------------

anceParser::Literal_expressionContext::Literal_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::Literal_expressionContext::STRING() {
  return getToken(anceParser::STRING, 0);
}


size_t anceParser::Literal_expressionContext::getRuleIndex() const {
  return anceParser::RuleLiteral_expression;
}


antlrcpp::Any anceParser::Literal_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLiteral_expression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Literal_expressionContext* anceParser::literal_expression() {
  Literal_expressionContext *_localctx = _tracker.createInstance<Literal_expressionContext>(_ctx, getState());
  enterRule(_localctx, 46, anceParser::RuleLiteral_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(201);
    match(anceParser::STRING);
   
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
  enterRule(_localctx, 48, anceParser::RuleInteger_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(206);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(203);
        unsigned_integer();
        break;
      }

      case anceParser::SIGNED_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(204);
        signed_integer();
        break;
      }

      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(205);
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

tree::TerminalNode* anceParser::Unsigned_integerContext::COLON() {
  return getToken(anceParser::COLON, 0);
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
  enterRule(_localctx, 50, anceParser::RuleUnsigned_integer);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(208);
    match(anceParser::INTEGER);
    setState(211);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::COLON) {
      setState(209);
      match(anceParser::COLON);
      setState(210);
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

tree::TerminalNode* anceParser::Signed_integerContext::COLON() {
  return getToken(anceParser::COLON, 0);
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
  enterRule(_localctx, 52, anceParser::RuleSigned_integer);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(213);
    match(anceParser::SIGNED_INTEGER);
    setState(216);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::COLON) {
      setState(214);
      match(anceParser::COLON);
      setState(215);
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

tree::TerminalNode* anceParser::Special_integerContext::COLON() {
  return getToken(anceParser::COLON, 0);
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
  enterRule(_localctx, 54, anceParser::RuleSpecial_integer);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(233);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::HEX_INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(218);
        match(anceParser::HEX_INTEGER);
        setState(221);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::COLON) {
          setState(219);
          match(anceParser::COLON);
          setState(220);
          match(anceParser::INTEGER);
        }
        break;
      }

      case anceParser::BIN_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(223);
        match(anceParser::BIN_INTEGER);
        setState(226);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::COLON) {
          setState(224);
          match(anceParser::COLON);
          setState(225);
          match(anceParser::INTEGER);
        }
        break;
      }

      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(228);
        match(anceParser::OCT_INTEGER);
        setState(231);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::COLON) {
          setState(229);
          match(anceParser::COLON);
          setState(230);
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
  enterRule(_localctx, 56, anceParser::RuleFloating_point_expression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(235);
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

//----------------- TypeContext ------------------------------------------------------------------

anceParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::Integer_typeContext* anceParser::TypeContext::integer_type() {
  return getRuleContext<anceParser::Integer_typeContext>(0);
}

anceParser::Floating_point_typeContext* anceParser::TypeContext::floating_point_type() {
  return getRuleContext<anceParser::Floating_point_typeContext>(0);
}

anceParser::Size_typeContext* anceParser::TypeContext::size_type() {
  return getRuleContext<anceParser::Size_typeContext>(0);
}

anceParser::Array_typeContext* anceParser::TypeContext::array_type() {
  return getRuleContext<anceParser::Array_typeContext>(0);
}

anceParser::Void_typeContext* anceParser::TypeContext::void_type() {
  return getRuleContext<anceParser::Void_typeContext>(0);
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
  enterRule(_localctx, 58, anceParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(242);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::NATIVE_INTEGER_TYPE: {
        enterOuterAlt(_localctx, 1);
        setState(237);
        integer_type();
        break;
      }

      case anceParser::HALF_TYPE:
      case anceParser::SINGLE_TYPE:
      case anceParser::DOUBLE_TYPE:
      case anceParser::QUAD_TYPE: {
        enterOuterAlt(_localctx, 2);
        setState(238);
        floating_point_type();
        break;
      }

      case anceParser::SIZE: {
        enterOuterAlt(_localctx, 3);
        setState(239);
        size_type();
        break;
      }

      case anceParser::BRACKET_OPEN: {
        enterOuterAlt(_localctx, 4);
        setState(240);
        array_type();
        break;
      }

      case anceParser::VOID: {
        enterOuterAlt(_localctx, 5);
        setState(241);
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
  enterRule(_localctx, 60, anceParser::RuleInteger_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(244);
    match(anceParser::NATIVE_INTEGER_TYPE);
   
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
  enterRule(_localctx, 62, anceParser::RuleFloating_point_type);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(246);
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
  enterRule(_localctx, 64, anceParser::RuleSize_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(248);
    match(anceParser::SIZE);
   
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

tree::TerminalNode* anceParser::Array_typeContext::BRACKET_OPEN() {
  return getToken(anceParser::BRACKET_OPEN, 0);
}

tree::TerminalNode* anceParser::Array_typeContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}

tree::TerminalNode* anceParser::Array_typeContext::COLON() {
  return getToken(anceParser::COLON, 0);
}

anceParser::TypeContext* anceParser::Array_typeContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::Array_typeContext::BRACKET_CLOSED() {
  return getToken(anceParser::BRACKET_CLOSED, 0);
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
    setState(250);
    match(anceParser::BRACKET_OPEN);
    setState(251);
    match(anceParser::INTEGER);
    setState(252);
    match(anceParser::COLON);
    setState(253);
    type();
    setState(254);
    match(anceParser::BRACKET_CLOSED);
   
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
  enterRule(_localctx, 68, anceParser::RuleVoid_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(256);
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
  "sizeof_exp_expression", "constant_expression", "literal_expression", 
  "integer_expression", "unsigned_integer", "signed_integer", "special_integer", 
  "floating_point_expression", "type", "integer_type", "floating_point_type", 
  "size_type", "array_type", "void_type"
};

std::vector<std::string> anceParser::_literalNames = {
  "", "", "'half'", "'single'", "'double'", "'quad'", "", "", "", "", "", 
  "", "", "", "", "", "", "'sizeof'", "'size'", "'print'", "'return'", "'const'", 
  "'public'", "'private'", "'void'", "", "':='", "'<-'", "'('", "')'", "'{'", 
  "'}'", "'['", "']'", "','", "':'", "';'"
};

std::vector<std::string> anceParser::_symbolicNames = {
  "", "NATIVE_INTEGER_TYPE", "HALF_TYPE", "SINGLE_TYPE", "DOUBLE_TYPE", 
  "QUAD_TYPE", "SIGNED_INTEGER", "HEX_INTEGER", "BIN_INTEGER", "OCT_INTEGER", 
  "HALF", "SINGLE", "DOUBLE", "QUAD", "DECIMAL", "STRING", "INTEGER", "SIZEOF", 
  "SIZE", "PRINT", "RETURN", "CONST", "PUBLIC", "PRIVATE", "VOID", "IDENTIFIER", 
  "DEFINITION", "ASSIGNMENT", "PARENTHESES_OPEN", "PARENTHESES_CLOSED", 
  "BRACE_OPEN", "BRACE_CLOSED", "BRACKET_OPEN", "BRACKET_CLOSED", "COMMA", 
  "COLON", "SEMICOLON", "WHITESPACE"
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
    0x3, 0x27, 0x105, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x3, 0x2, 0x3, 
    0x2, 0x7, 0x2, 0x4b, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x4e, 0xb, 0x2, 0x3, 
    0x3, 0x3, 0x3, 0x5, 0x3, 0x52, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x61, 0xa, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x6, 0x7, 0x6f, 0xa, 0x7, 0xd, 0x7, 
    0xe, 0x7, 0x70, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 
    0x8, 0x78, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x7b, 0xb, 0x8, 0x5, 0x8, 0x7d, 
    0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x89, 0xa, 0xb, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 
    0xd, 0x92, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 
    0x3, 0x10, 0x5, 0x10, 0xa1, 0xa, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0xaa, 0xa, 0x11, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x7, 0x14, 0xb6, 0xa, 0x14, 0xc, 
    0x14, 0xe, 0x14, 0xb9, 0xb, 0x14, 0x5, 0x14, 0xbb, 0xa, 0x14, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 
    0xca, 0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
    0x5, 0x1a, 0xd1, 0xa, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 
    0xd6, 0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0xdb, 0xa, 
    0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0xe0, 0xa, 0x1d, 0x3, 
    0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0xe5, 0xa, 0x1d, 0x3, 0x1d, 0x3, 
    0x1d, 0x3, 0x1d, 0x5, 0x1d, 0xea, 0xa, 0x1d, 0x5, 0x1d, 0xec, 0xa, 0x1d, 
    0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 
    0x1f, 0x5, 0x1f, 0xf5, 0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x21, 0x3, 
    0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x2, 0x2, 0x25, 
    0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 
    0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 
    0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x2, 0x5, 
    0x3, 0x2, 0x18, 0x19, 0x3, 0x2, 0xc, 0xf, 0x3, 0x2, 0x4, 0x7, 0x2, 0x103, 
    0x2, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x4, 0x51, 0x3, 0x2, 0x2, 0x2, 0x6, 0x53, 
    0x3, 0x2, 0x2, 0x2, 0x8, 0x5b, 0x3, 0x2, 0x2, 0x2, 0xa, 0x64, 0x3, 0x2, 
    0x2, 0x2, 0xc, 0x66, 0x3, 0x2, 0x2, 0x2, 0xe, 0x7c, 0x3, 0x2, 0x2, 0x2, 
    0x10, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x12, 0x81, 0x3, 0x2, 0x2, 0x2, 0x14, 
    0x88, 0x3, 0x2, 0x2, 0x2, 0x16, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x18, 0x8d, 
    0x3, 0x2, 0x2, 0x2, 0x1a, 0x95, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x9a, 0x3, 
    0x2, 0x2, 0x2, 0x1e, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x20, 0xa9, 0x3, 0x2, 
    0x2, 0x2, 0x22, 0xab, 0x3, 0x2, 0x2, 0x2, 0x24, 0xad, 0x3, 0x2, 0x2, 
    0x2, 0x26, 0xba, 0x3, 0x2, 0x2, 0x2, 0x28, 0xbc, 0x3, 0x2, 0x2, 0x2, 
    0x2a, 0xbe, 0x3, 0x2, 0x2, 0x2, 0x2c, 0xc1, 0x3, 0x2, 0x2, 0x2, 0x2e, 
    0xc9, 0x3, 0x2, 0x2, 0x2, 0x30, 0xcb, 0x3, 0x2, 0x2, 0x2, 0x32, 0xd0, 
    0x3, 0x2, 0x2, 0x2, 0x34, 0xd2, 0x3, 0x2, 0x2, 0x2, 0x36, 0xd7, 0x3, 
    0x2, 0x2, 0x2, 0x38, 0xeb, 0x3, 0x2, 0x2, 0x2, 0x3a, 0xed, 0x3, 0x2, 
    0x2, 0x2, 0x3c, 0xf4, 0x3, 0x2, 0x2, 0x2, 0x3e, 0xf6, 0x3, 0x2, 0x2, 
    0x2, 0x40, 0xf8, 0x3, 0x2, 0x2, 0x2, 0x42, 0xfa, 0x3, 0x2, 0x2, 0x2, 
    0x44, 0xfc, 0x3, 0x2, 0x2, 0x2, 0x46, 0x102, 0x3, 0x2, 0x2, 0x2, 0x48, 
    0x4b, 0x5, 0x4, 0x3, 0x2, 0x49, 0x4b, 0x5, 0xa, 0x6, 0x2, 0x4a, 0x48, 
    0x3, 0x2, 0x2, 0x2, 0x4a, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4e, 0x3, 
    0x2, 0x2, 0x2, 0x4c, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4d, 0x3, 0x2, 
    0x2, 0x2, 0x4d, 0x3, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x4c, 0x3, 0x2, 0x2, 
    0x2, 0x4f, 0x52, 0x5, 0x6, 0x4, 0x2, 0x50, 0x52, 0x5, 0x8, 0x5, 0x2, 
    0x51, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x51, 0x50, 0x3, 0x2, 0x2, 0x2, 0x52, 
    0x5, 0x3, 0x2, 0x2, 0x2, 0x53, 0x54, 0x5, 0x12, 0xa, 0x2, 0x54, 0x55, 
    0x7, 0x17, 0x2, 0x2, 0x55, 0x56, 0x5, 0x3c, 0x1f, 0x2, 0x56, 0x57, 0x7, 
    0x1b, 0x2, 0x2, 0x57, 0x58, 0x7, 0x1c, 0x2, 0x2, 0x58, 0x59, 0x5, 0x2e, 
    0x18, 0x2, 0x59, 0x5a, 0x7, 0x26, 0x2, 0x2, 0x5a, 0x7, 0x3, 0x2, 0x2, 
    0x2, 0x5b, 0x5c, 0x5, 0x12, 0xa, 0x2, 0x5c, 0x5d, 0x5, 0x3c, 0x1f, 0x2, 
    0x5d, 0x60, 0x7, 0x1b, 0x2, 0x2, 0x5e, 0x5f, 0x7, 0x1d, 0x2, 0x2, 0x5f, 
    0x61, 0x5, 0x2e, 0x18, 0x2, 0x60, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 
    0x3, 0x2, 0x2, 0x2, 0x61, 0x62, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x7, 
    0x26, 0x2, 0x2, 0x63, 0x9, 0x3, 0x2, 0x2, 0x2, 0x64, 0x65, 0x5, 0xc, 
    0x7, 0x2, 0x65, 0xb, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x5, 0x12, 0xa, 
    0x2, 0x67, 0x68, 0x5, 0x3c, 0x1f, 0x2, 0x68, 0x69, 0x7, 0x1b, 0x2, 0x2, 
    0x69, 0x6a, 0x7, 0x1e, 0x2, 0x2, 0x6a, 0x6b, 0x5, 0xe, 0x8, 0x2, 0x6b, 
    0x6c, 0x7, 0x1f, 0x2, 0x2, 0x6c, 0x6e, 0x7, 0x20, 0x2, 0x2, 0x6d, 0x6f, 
    0x5, 0x14, 0xb, 0x2, 0x6e, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0x3, 
    0x2, 0x2, 0x2, 0x70, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x70, 0x71, 0x3, 0x2, 
    0x2, 0x2, 0x71, 0x72, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0x7, 0x21, 0x2, 
    0x2, 0x73, 0xd, 0x3, 0x2, 0x2, 0x2, 0x74, 0x79, 0x5, 0x10, 0x9, 0x2, 
    0x75, 0x76, 0x7, 0x24, 0x2, 0x2, 0x76, 0x78, 0x5, 0x10, 0x9, 0x2, 0x77, 
    0x75, 0x3, 0x2, 0x2, 0x2, 0x78, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x79, 0x77, 
    0x3, 0x2, 0x2, 0x2, 0x79, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7d, 0x3, 
    0x2, 0x2, 0x2, 0x7b, 0x79, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x74, 0x3, 0x2, 
    0x2, 0x2, 0x7c, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x7d, 0xf, 0x3, 0x2, 0x2, 
    0x2, 0x7e, 0x7f, 0x5, 0x3c, 0x1f, 0x2, 0x7f, 0x80, 0x7, 0x1b, 0x2, 0x2, 
    0x80, 0x11, 0x3, 0x2, 0x2, 0x2, 0x81, 0x82, 0x9, 0x2, 0x2, 0x2, 0x82, 
    0x13, 0x3, 0x2, 0x2, 0x2, 0x83, 0x89, 0x5, 0x16, 0xc, 0x2, 0x84, 0x89, 
    0x5, 0x18, 0xd, 0x2, 0x85, 0x89, 0x5, 0x1a, 0xe, 0x2, 0x86, 0x89, 0x5, 
    0x1c, 0xf, 0x2, 0x87, 0x89, 0x5, 0x1e, 0x10, 0x2, 0x88, 0x83, 0x3, 0x2, 
    0x2, 0x2, 0x88, 0x84, 0x3, 0x2, 0x2, 0x2, 0x88, 0x85, 0x3, 0x2, 0x2, 
    0x2, 0x88, 0x86, 0x3, 0x2, 0x2, 0x2, 0x88, 0x87, 0x3, 0x2, 0x2, 0x2, 
    0x89, 0x15, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x8b, 0x5, 0x22, 0x12, 0x2, 0x8b, 
    0x8c, 0x7, 0x26, 0x2, 0x2, 0x8c, 0x17, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8e, 
    0x5, 0x3c, 0x1f, 0x2, 0x8e, 0x91, 0x7, 0x1b, 0x2, 0x2, 0x8f, 0x90, 0x7, 
    0x1d, 0x2, 0x2, 0x90, 0x92, 0x5, 0x20, 0x11, 0x2, 0x91, 0x8f, 0x3, 0x2, 
    0x2, 0x2, 0x91, 0x92, 0x3, 0x2, 0x2, 0x2, 0x92, 0x93, 0x3, 0x2, 0x2, 
    0x2, 0x93, 0x94, 0x7, 0x26, 0x2, 0x2, 0x94, 0x19, 0x3, 0x2, 0x2, 0x2, 
    0x95, 0x96, 0x7, 0x1b, 0x2, 0x2, 0x96, 0x97, 0x7, 0x1d, 0x2, 0x2, 0x97, 
    0x98, 0x5, 0x20, 0x11, 0x2, 0x98, 0x99, 0x7, 0x26, 0x2, 0x2, 0x99, 0x1b, 
    0x3, 0x2, 0x2, 0x2, 0x9a, 0x9b, 0x7, 0x15, 0x2, 0x2, 0x9b, 0x9c, 0x5, 
    0x20, 0x11, 0x2, 0x9c, 0x9d, 0x7, 0x26, 0x2, 0x2, 0x9d, 0x1d, 0x3, 0x2, 
    0x2, 0x2, 0x9e, 0xa0, 0x7, 0x16, 0x2, 0x2, 0x9f, 0xa1, 0x5, 0x20, 0x11, 
    0x2, 0xa0, 0x9f, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa1, 0x3, 0x2, 0x2, 0x2, 
    0xa1, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa2, 0xa3, 0x7, 0x26, 0x2, 0x2, 0xa3, 
    0x1f, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xaa, 0x5, 0x28, 0x15, 0x2, 0xa5, 0xaa, 
    0x5, 0x2a, 0x16, 0x2, 0xa6, 0xaa, 0x5, 0x2c, 0x17, 0x2, 0xa7, 0xaa, 
    0x5, 0x2e, 0x18, 0x2, 0xa8, 0xaa, 0x5, 0x22, 0x12, 0x2, 0xa9, 0xa4, 
    0x3, 0x2, 0x2, 0x2, 0xa9, 0xa5, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xa6, 0x3, 
    0x2, 0x2, 0x2, 0xa9, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xa9, 0xa8, 0x3, 0x2, 
    0x2, 0x2, 0xaa, 0x21, 0x3, 0x2, 0x2, 0x2, 0xab, 0xac, 0x5, 0x24, 0x13, 
    0x2, 0xac, 0x23, 0x3, 0x2, 0x2, 0x2, 0xad, 0xae, 0x7, 0x1b, 0x2, 0x2, 
    0xae, 0xaf, 0x7, 0x1e, 0x2, 0x2, 0xaf, 0xb0, 0x5, 0x26, 0x14, 0x2, 0xb0, 
    0xb1, 0x7, 0x1f, 0x2, 0x2, 0xb1, 0x25, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xb7, 
    0x5, 0x20, 0x11, 0x2, 0xb3, 0xb4, 0x7, 0x24, 0x2, 0x2, 0xb4, 0xb6, 0x5, 
    0x20, 0x11, 0x2, 0xb5, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb9, 0x3, 0x2, 
    0x2, 0x2, 0xb7, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xb8, 0x3, 0x2, 0x2, 
    0x2, 0xb8, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xb7, 0x3, 0x2, 0x2, 0x2, 
    0xba, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xba, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xbb, 
    0x27, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 0x7, 0x1b, 0x2, 0x2, 0xbd, 0x29, 
    0x3, 0x2, 0x2, 0x2, 0xbe, 0xbf, 0x7, 0x13, 0x2, 0x2, 0xbf, 0xc0, 0x5, 
    0x3c, 0x1f, 0x2, 0xc0, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xc1, 0xc2, 0x7, 0x13, 
    0x2, 0x2, 0xc2, 0xc3, 0x7, 0x1e, 0x2, 0x2, 0xc3, 0xc4, 0x5, 0x20, 0x11, 
    0x2, 0xc4, 0xc5, 0x7, 0x1f, 0x2, 0x2, 0xc5, 0x2d, 0x3, 0x2, 0x2, 0x2, 
    0xc6, 0xca, 0x5, 0x30, 0x19, 0x2, 0xc7, 0xca, 0x5, 0x32, 0x1a, 0x2, 
    0xc8, 0xca, 0x5, 0x3a, 0x1e, 0x2, 0xc9, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc9, 
    0xc7, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xca, 0x2f, 
    0x3, 0x2, 0x2, 0x2, 0xcb, 0xcc, 0x7, 0x11, 0x2, 0x2, 0xcc, 0x31, 0x3, 
    0x2, 0x2, 0x2, 0xcd, 0xd1, 0x5, 0x34, 0x1b, 0x2, 0xce, 0xd1, 0x5, 0x36, 
    0x1c, 0x2, 0xcf, 0xd1, 0x5, 0x38, 0x1d, 0x2, 0xd0, 0xcd, 0x3, 0x2, 0x2, 
    0x2, 0xd0, 0xce, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xcf, 0x3, 0x2, 0x2, 0x2, 
    0xd1, 0x33, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd5, 0x7, 0x12, 0x2, 0x2, 0xd3, 
    0xd4, 0x7, 0x25, 0x2, 0x2, 0xd4, 0xd6, 0x7, 0x12, 0x2, 0x2, 0xd5, 0xd3, 
    0x3, 0x2, 0x2, 0x2, 0xd5, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd6, 0x35, 0x3, 
    0x2, 0x2, 0x2, 0xd7, 0xda, 0x7, 0x8, 0x2, 0x2, 0xd8, 0xd9, 0x7, 0x25, 
    0x2, 0x2, 0xd9, 0xdb, 0x7, 0x12, 0x2, 0x2, 0xda, 0xd8, 0x3, 0x2, 0x2, 
    0x2, 0xda, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xdb, 0x37, 0x3, 0x2, 0x2, 0x2, 
    0xdc, 0xdf, 0x7, 0x9, 0x2, 0x2, 0xdd, 0xde, 0x7, 0x25, 0x2, 0x2, 0xde, 
    0xe0, 0x7, 0x12, 0x2, 0x2, 0xdf, 0xdd, 0x3, 0x2, 0x2, 0x2, 0xdf, 0xe0, 
    0x3, 0x2, 0x2, 0x2, 0xe0, 0xec, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xe4, 0x7, 
    0xa, 0x2, 0x2, 0xe2, 0xe3, 0x7, 0x25, 0x2, 0x2, 0xe3, 0xe5, 0x7, 0x12, 
    0x2, 0x2, 0xe4, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe5, 0x3, 0x2, 0x2, 
    0x2, 0xe5, 0xec, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xe9, 0x7, 0xb, 0x2, 0x2, 
    0xe7, 0xe8, 0x7, 0x25, 0x2, 0x2, 0xe8, 0xea, 0x7, 0x12, 0x2, 0x2, 0xe9, 
    0xe7, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xea, 0x3, 0x2, 0x2, 0x2, 0xea, 0xec, 
    0x3, 0x2, 0x2, 0x2, 0xeb, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xe1, 0x3, 
    0x2, 0x2, 0x2, 0xeb, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xec, 0x39, 0x3, 0x2, 
    0x2, 0x2, 0xed, 0xee, 0x9, 0x3, 0x2, 0x2, 0xee, 0x3b, 0x3, 0x2, 0x2, 
    0x2, 0xef, 0xf5, 0x5, 0x3e, 0x20, 0x2, 0xf0, 0xf5, 0x5, 0x40, 0x21, 
    0x2, 0xf1, 0xf5, 0x5, 0x42, 0x22, 0x2, 0xf2, 0xf5, 0x5, 0x44, 0x23, 
    0x2, 0xf3, 0xf5, 0x5, 0x46, 0x24, 0x2, 0xf4, 0xef, 0x3, 0x2, 0x2, 0x2, 
    0xf4, 0xf0, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xf1, 0x3, 0x2, 0x2, 0x2, 0xf4, 
    0xf2, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf5, 0x3d, 
    0x3, 0x2, 0x2, 0x2, 0xf6, 0xf7, 0x7, 0x3, 0x2, 0x2, 0xf7, 0x3f, 0x3, 
    0x2, 0x2, 0x2, 0xf8, 0xf9, 0x9, 0x4, 0x2, 0x2, 0xf9, 0x41, 0x3, 0x2, 
    0x2, 0x2, 0xfa, 0xfb, 0x7, 0x14, 0x2, 0x2, 0xfb, 0x43, 0x3, 0x2, 0x2, 
    0x2, 0xfc, 0xfd, 0x7, 0x22, 0x2, 0x2, 0xfd, 0xfe, 0x7, 0x12, 0x2, 0x2, 
    0xfe, 0xff, 0x7, 0x25, 0x2, 0x2, 0xff, 0x100, 0x5, 0x3c, 0x1f, 0x2, 
    0x100, 0x101, 0x7, 0x23, 0x2, 0x2, 0x101, 0x45, 0x3, 0x2, 0x2, 0x2, 
    0x102, 0x103, 0x7, 0x1a, 0x2, 0x2, 0x103, 0x47, 0x3, 0x2, 0x2, 0x2, 
    0x18, 0x4a, 0x4c, 0x51, 0x60, 0x70, 0x79, 0x7c, 0x88, 0x91, 0xa0, 0xa9, 
    0xb7, 0xba, 0xc9, 0xd0, 0xd5, 0xda, 0xdf, 0xe4, 0xe9, 0xeb, 0xf4, 
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
