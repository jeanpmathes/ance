
// Generated from ./ance.g4 by ANTLR 4.8


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
    setState(58);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == anceParser::PUBLIC

    || _la == anceParser::PRIVATE) {
      setState(56);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(54);
        data();
        break;
      }

      case 2: {
        setState(55);
        code();
        break;
      }

      }
      setState(60);
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
    setState(63);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(61);
      constant_declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(62);
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
    setState(65);
    access_modifier();
    setState(66);
    match(anceParser::CONST);
    setState(67);
    type();
    setState(68);
    match(anceParser::IDENTIFIER);
    setState(69);
    match(anceParser::DEFINITION);
    setState(70);
    constant_expression();
    setState(71);
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
    setState(73);
    access_modifier();
    setState(74);
    type();
    setState(75);
    match(anceParser::IDENTIFIER);
    setState(78);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::ASSIGNMENT) {
      setState(76);
      match(anceParser::ASSIGNMENT);
      setState(77);
      constant_expression();
    }
    setState(80);
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
    setState(82);
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
    setState(84);
    access_modifier();
    setState(85);
    type();
    setState(86);
    match(anceParser::IDENTIFIER);
    setState(87);
    match(anceParser::PARANTHESE_OPEN);
    setState(88);
    match(anceParser::PARANTHESE_CLOSED);
    setState(89);
    match(anceParser::BRACE_OPEN);
    setState(91); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(90);
      statement();
      setState(93); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::NATIVE_INTEGER_TYPE)
      | (1ULL << anceParser::PRINT)
      | (1ULL << anceParser::RETURN)
      | (1ULL << anceParser::VOID)
      | (1ULL << anceParser::IDENTIFIER)
      | (1ULL << anceParser::BRACKET_OPEN))) != 0));
    setState(95);
    match(anceParser::BRACE_CLOSED);
   
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
  enterRule(_localctx, 12, anceParser::RuleAccess_modifier);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(97);
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
  enterRule(_localctx, 14, anceParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(104);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(99);
      expression_statement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(100);
      local_variable_definition();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(101);
      variable_assignment();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(102);
      print_statement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(103);
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
  enterRule(_localctx, 16, anceParser::RuleExpression_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(106);
    independent_expression();
    setState(107);
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
  enterRule(_localctx, 18, anceParser::RuleLocal_variable_definition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    type();
    setState(110);
    match(anceParser::IDENTIFIER);
    setState(113);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::ASSIGNMENT) {
      setState(111);
      match(anceParser::ASSIGNMENT);
      setState(112);
      expression();
    }
    setState(115);
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
  enterRule(_localctx, 20, anceParser::RuleVariable_assignment);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(117);
    match(anceParser::IDENTIFIER);
    setState(118);
    match(anceParser::ASSIGNMENT);
    setState(119);
    expression();
    setState(120);
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
  enterRule(_localctx, 22, anceParser::RulePrint_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(anceParser::PRINT);
    setState(123);
    expression();
    setState(124);
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
  enterRule(_localctx, 24, anceParser::RuleReturn_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(126);
    match(anceParser::RETURN);
    setState(128);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::SIGNED_INTEGER)
      | (1ULL << anceParser::HEX_INTEGER)
      | (1ULL << anceParser::BIN_INTEGER)
      | (1ULL << anceParser::OCT_INTEGER)
      | (1ULL << anceParser::STRING)
      | (1ULL << anceParser::INTEGER)
      | (1ULL << anceParser::IDENTIFIER))) != 0)) {
      setState(127);
      expression();
    }
    setState(130);
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
  enterRule(_localctx, 26, anceParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(135);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(132);
      variable_expression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(133);
      constant_expression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(134);
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
  enterRule(_localctx, 28, anceParser::RuleIndependent_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
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

tree::TerminalNode* anceParser::Function_callContext::PARANTHESE_OPEN() {
  return getToken(anceParser::PARANTHESE_OPEN, 0);
}

tree::TerminalNode* anceParser::Function_callContext::PARANTHESE_CLOSED() {
  return getToken(anceParser::PARANTHESE_CLOSED, 0);
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
  enterRule(_localctx, 30, anceParser::RuleFunction_call);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(139);
    match(anceParser::IDENTIFIER);
    setState(140);
    match(anceParser::PARANTHESE_OPEN);
    setState(141);
    match(anceParser::PARANTHESE_CLOSED);
   
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
  enterRule(_localctx, 32, anceParser::RuleVariable_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    match(anceParser::IDENTIFIER);
   
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
  enterRule(_localctx, 34, anceParser::RuleConstant_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(147);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::STRING: {
        enterOuterAlt(_localctx, 1);
        setState(145);
        literal_expression();
        break;
      }

      case anceParser::SIGNED_INTEGER:
      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER:
      case anceParser::INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(146);
        integer_expression();
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
  enterRule(_localctx, 36, anceParser::RuleLiteral_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(149);
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
  enterRule(_localctx, 38, anceParser::RuleInteger_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(154);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(151);
        unsigned_integer();
        break;
      }

      case anceParser::SIGNED_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(152);
        signed_integer();
        break;
      }

      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(153);
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
  enterRule(_localctx, 40, anceParser::RuleUnsigned_integer);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(156);
    match(anceParser::INTEGER);
    setState(159);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::COLON) {
      setState(157);
      match(anceParser::COLON);
      setState(158);
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
  enterRule(_localctx, 42, anceParser::RuleSigned_integer);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    match(anceParser::SIGNED_INTEGER);
    setState(164);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::COLON) {
      setState(162);
      match(anceParser::COLON);
      setState(163);
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
  enterRule(_localctx, 44, anceParser::RuleSpecial_integer);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(181);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::HEX_INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(166);
        match(anceParser::HEX_INTEGER);
        setState(169);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::COLON) {
          setState(167);
          match(anceParser::COLON);
          setState(168);
          match(anceParser::INTEGER);
        }
        break;
      }

      case anceParser::BIN_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(171);
        match(anceParser::BIN_INTEGER);
        setState(174);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::COLON) {
          setState(172);
          match(anceParser::COLON);
          setState(173);
          match(anceParser::INTEGER);
        }
        break;
      }

      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(176);
        match(anceParser::OCT_INTEGER);
        setState(179);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::COLON) {
          setState(177);
          match(anceParser::COLON);
          setState(178);
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
  enterRule(_localctx, 46, anceParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(186);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::NATIVE_INTEGER_TYPE: {
        enterOuterAlt(_localctx, 1);
        setState(183);
        integer_type();
        break;
      }

      case anceParser::BRACKET_OPEN: {
        enterOuterAlt(_localctx, 2);
        setState(184);
        array_type();
        break;
      }

      case anceParser::VOID: {
        enterOuterAlt(_localctx, 3);
        setState(185);
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
  enterRule(_localctx, 48, anceParser::RuleInteger_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(188);
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

tree::TerminalNode* anceParser::Array_typeContext::BRACKET_OPEN() {
  return getToken(anceParser::BRACKET_OPEN, 0);
}

anceParser::TypeContext* anceParser::Array_typeContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::Array_typeContext::COLON() {
  return getToken(anceParser::COLON, 0);
}

tree::TerminalNode* anceParser::Array_typeContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
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
  enterRule(_localctx, 50, anceParser::RuleArray_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    match(anceParser::BRACKET_OPEN);
    setState(191);
    type();
    setState(192);
    match(anceParser::COLON);
    setState(193);
    match(anceParser::INTEGER);
    setState(194);
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
  enterRule(_localctx, 52, anceParser::RuleVoid_type);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(196);
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
  "function", "access_modifier", "statement", "expression_statement", "local_variable_definition", 
  "variable_assignment", "print_statement", "return_statement", "expression", 
  "independent_expression", "function_call", "variable_expression", "constant_expression", 
  "literal_expression", "integer_expression", "unsigned_integer", "signed_integer", 
  "special_integer", "type", "integer_type", "array_type", "void_type"
};

std::vector<std::string> anceParser::_literalNames = {
  "", "", "", "", "", "", "", "", "'print'", "'return'", "'const'", "'public'", 
  "'private'", "'void'", "", "':='", "'<-'", "'('", "')'", "'{'", "'}'", 
  "'['", "']'", "':'", "';'"
};

std::vector<std::string> anceParser::_symbolicNames = {
  "", "NATIVE_INTEGER_TYPE", "SIGNED_INTEGER", "HEX_INTEGER", "BIN_INTEGER", 
  "OCT_INTEGER", "STRING", "INTEGER", "PRINT", "RETURN", "CONST", "PUBLIC", 
  "PRIVATE", "VOID", "IDENTIFIER", "DEFINITION", "ASSIGNMENT", "PARANTHESE_OPEN", 
  "PARANTHESE_CLOSED", "BRACE_OPEN", "BRACE_CLOSED", "BRACKET_OPEN", "BRACKET_CLOSED", 
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
    0x3, 0x1b, 0xc9, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 0x12, 
    0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 0x9, 
    0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 
    0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x4, 
    0x1c, 0x9, 0x1c, 0x3, 0x2, 0x3, 0x2, 0x7, 0x2, 0x3b, 0xa, 0x2, 0xc, 
    0x2, 0xe, 0x2, 0x3e, 0xb, 0x2, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x42, 0xa, 
    0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 
    0x5, 0x51, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x6, 0x7, 
    0x5e, 0xa, 0x7, 0xd, 0x7, 0xe, 0x7, 0x5f, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 
    0x6b, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x5, 0xb, 0x74, 0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x83, 0xa, 0xe, 0x3, 0xe, 0x3, 
    0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x8a, 0xa, 0xf, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x3, 
    0x12, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x96, 0xa, 0x13, 0x3, 0x14, 0x3, 
    0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0x9d, 0xa, 0x15, 0x3, 
    0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0xa2, 0xa, 0x16, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x5, 0x17, 0xa7, 0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x5, 0x18, 0xac, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 
    0x18, 0xb1, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0xb6, 
    0xa, 0x18, 0x5, 0x18, 0xb8, 0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x5, 0x19, 0xbd, 0xa, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 
    0x1c, 0x2, 0x2, 0x1d, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 
    0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 
    0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x2, 0x3, 0x3, 0x2, 0xd, 0xe, 0x2, 
    0xc6, 0x2, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x4, 0x41, 0x3, 0x2, 0x2, 0x2, 
    0x6, 0x43, 0x3, 0x2, 0x2, 0x2, 0x8, 0x4b, 0x3, 0x2, 0x2, 0x2, 0xa, 0x54, 
    0x3, 0x2, 0x2, 0x2, 0xc, 0x56, 0x3, 0x2, 0x2, 0x2, 0xe, 0x63, 0x3, 0x2, 
    0x2, 0x2, 0x10, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x12, 0x6c, 0x3, 0x2, 0x2, 
    0x2, 0x14, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x16, 0x77, 0x3, 0x2, 0x2, 0x2, 
    0x18, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x80, 0x3, 0x2, 0x2, 0x2, 0x1c, 
    0x89, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x20, 0x8d, 
    0x3, 0x2, 0x2, 0x2, 0x22, 0x91, 0x3, 0x2, 0x2, 0x2, 0x24, 0x95, 0x3, 
    0x2, 0x2, 0x2, 0x26, 0x97, 0x3, 0x2, 0x2, 0x2, 0x28, 0x9c, 0x3, 0x2, 
    0x2, 0x2, 0x2a, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x2c, 0xa3, 0x3, 0x2, 0x2, 
    0x2, 0x2e, 0xb7, 0x3, 0x2, 0x2, 0x2, 0x30, 0xbc, 0x3, 0x2, 0x2, 0x2, 
    0x32, 0xbe, 0x3, 0x2, 0x2, 0x2, 0x34, 0xc0, 0x3, 0x2, 0x2, 0x2, 0x36, 
    0xc6, 0x3, 0x2, 0x2, 0x2, 0x38, 0x3b, 0x5, 0x4, 0x3, 0x2, 0x39, 0x3b, 
    0x5, 0xa, 0x6, 0x2, 0x3a, 0x38, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x39, 0x3, 
    0x2, 0x2, 0x2, 0x3b, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3a, 0x3, 0x2, 
    0x2, 0x2, 0x3c, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3, 0x3, 0x2, 0x2, 
    0x2, 0x3e, 0x3c, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x42, 0x5, 0x6, 0x4, 0x2, 
    0x40, 0x42, 0x5, 0x8, 0x5, 0x2, 0x41, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x41, 
    0x40, 0x3, 0x2, 0x2, 0x2, 0x42, 0x5, 0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 
    0x5, 0xe, 0x8, 0x2, 0x44, 0x45, 0x7, 0xc, 0x2, 0x2, 0x45, 0x46, 0x5, 
    0x30, 0x19, 0x2, 0x46, 0x47, 0x7, 0x10, 0x2, 0x2, 0x47, 0x48, 0x7, 0x11, 
    0x2, 0x2, 0x48, 0x49, 0x5, 0x24, 0x13, 0x2, 0x49, 0x4a, 0x7, 0x1a, 0x2, 
    0x2, 0x4a, 0x7, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4c, 0x5, 0xe, 0x8, 0x2, 
    0x4c, 0x4d, 0x5, 0x30, 0x19, 0x2, 0x4d, 0x50, 0x7, 0x10, 0x2, 0x2, 0x4e, 
    0x4f, 0x7, 0x12, 0x2, 0x2, 0x4f, 0x51, 0x5, 0x24, 0x13, 0x2, 0x50, 0x4e, 
    0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x3, 
    0x2, 0x2, 0x2, 0x52, 0x53, 0x7, 0x1a, 0x2, 0x2, 0x53, 0x9, 0x3, 0x2, 
    0x2, 0x2, 0x54, 0x55, 0x5, 0xc, 0x7, 0x2, 0x55, 0xb, 0x3, 0x2, 0x2, 
    0x2, 0x56, 0x57, 0x5, 0xe, 0x8, 0x2, 0x57, 0x58, 0x5, 0x30, 0x19, 0x2, 
    0x58, 0x59, 0x7, 0x10, 0x2, 0x2, 0x59, 0x5a, 0x7, 0x13, 0x2, 0x2, 0x5a, 
    0x5b, 0x7, 0x14, 0x2, 0x2, 0x5b, 0x5d, 0x7, 0x15, 0x2, 0x2, 0x5c, 0x5e, 
    0x5, 0x10, 0x9, 0x2, 0x5d, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x3, 
    0x2, 0x2, 0x2, 0x5f, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x5f, 0x60, 0x3, 0x2, 
    0x2, 0x2, 0x60, 0x61, 0x3, 0x2, 0x2, 0x2, 0x61, 0x62, 0x7, 0x16, 0x2, 
    0x2, 0x62, 0xd, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x9, 0x2, 0x2, 0x2, 
    0x64, 0xf, 0x3, 0x2, 0x2, 0x2, 0x65, 0x6b, 0x5, 0x12, 0xa, 0x2, 0x66, 
    0x6b, 0x5, 0x14, 0xb, 0x2, 0x67, 0x6b, 0x5, 0x16, 0xc, 0x2, 0x68, 0x6b, 
    0x5, 0x18, 0xd, 0x2, 0x69, 0x6b, 0x5, 0x1a, 0xe, 0x2, 0x6a, 0x65, 0x3, 
    0x2, 0x2, 0x2, 0x6a, 0x66, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x67, 0x3, 0x2, 
    0x2, 0x2, 0x6a, 0x68, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x69, 0x3, 0x2, 0x2, 
    0x2, 0x6b, 0x11, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x5, 0x1e, 0x10, 0x2, 
    0x6d, 0x6e, 0x7, 0x1a, 0x2, 0x2, 0x6e, 0x13, 0x3, 0x2, 0x2, 0x2, 0x6f, 
    0x70, 0x5, 0x30, 0x19, 0x2, 0x70, 0x73, 0x7, 0x10, 0x2, 0x2, 0x71, 0x72, 
    0x7, 0x12, 0x2, 0x2, 0x72, 0x74, 0x5, 0x1c, 0xf, 0x2, 0x73, 0x71, 0x3, 
    0x2, 0x2, 0x2, 0x73, 0x74, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x3, 0x2, 
    0x2, 0x2, 0x75, 0x76, 0x7, 0x1a, 0x2, 0x2, 0x76, 0x15, 0x3, 0x2, 0x2, 
    0x2, 0x77, 0x78, 0x7, 0x10, 0x2, 0x2, 0x78, 0x79, 0x7, 0x12, 0x2, 0x2, 
    0x79, 0x7a, 0x5, 0x1c, 0xf, 0x2, 0x7a, 0x7b, 0x7, 0x1a, 0x2, 0x2, 0x7b, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x7, 0xa, 0x2, 0x2, 0x7d, 0x7e, 
    0x5, 0x1c, 0xf, 0x2, 0x7e, 0x7f, 0x7, 0x1a, 0x2, 0x2, 0x7f, 0x19, 0x3, 
    0x2, 0x2, 0x2, 0x80, 0x82, 0x7, 0xb, 0x2, 0x2, 0x81, 0x83, 0x5, 0x1c, 
    0xf, 0x2, 0x82, 0x81, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x3, 0x2, 0x2, 
    0x2, 0x83, 0x84, 0x3, 0x2, 0x2, 0x2, 0x84, 0x85, 0x7, 0x1a, 0x2, 0x2, 
    0x85, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x86, 0x8a, 0x5, 0x22, 0x12, 0x2, 0x87, 
    0x8a, 0x5, 0x24, 0x13, 0x2, 0x88, 0x8a, 0x5, 0x1e, 0x10, 0x2, 0x89, 
    0x86, 0x3, 0x2, 0x2, 0x2, 0x89, 0x87, 0x3, 0x2, 0x2, 0x2, 0x89, 0x88, 
    0x3, 0x2, 0x2, 0x2, 0x8a, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x8c, 0x5, 
    0x20, 0x11, 0x2, 0x8c, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8e, 0x7, 0x10, 
    0x2, 0x2, 0x8e, 0x8f, 0x7, 0x13, 0x2, 0x2, 0x8f, 0x90, 0x7, 0x14, 0x2, 
    0x2, 0x90, 0x21, 0x3, 0x2, 0x2, 0x2, 0x91, 0x92, 0x7, 0x10, 0x2, 0x2, 
    0x92, 0x23, 0x3, 0x2, 0x2, 0x2, 0x93, 0x96, 0x5, 0x26, 0x14, 0x2, 0x94, 
    0x96, 0x5, 0x28, 0x15, 0x2, 0x95, 0x93, 0x3, 0x2, 0x2, 0x2, 0x95, 0x94, 
    0x3, 0x2, 0x2, 0x2, 0x96, 0x25, 0x3, 0x2, 0x2, 0x2, 0x97, 0x98, 0x7, 
    0x8, 0x2, 0x2, 0x98, 0x27, 0x3, 0x2, 0x2, 0x2, 0x99, 0x9d, 0x5, 0x2a, 
    0x16, 0x2, 0x9a, 0x9d, 0x5, 0x2c, 0x17, 0x2, 0x9b, 0x9d, 0x5, 0x2e, 
    0x18, 0x2, 0x9c, 0x99, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9a, 0x3, 0x2, 0x2, 
    0x2, 0x9c, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x29, 0x3, 0x2, 0x2, 0x2, 
    0x9e, 0xa1, 0x7, 0x9, 0x2, 0x2, 0x9f, 0xa0, 0x7, 0x19, 0x2, 0x2, 0xa0, 
    0xa2, 0x7, 0x9, 0x2, 0x2, 0xa1, 0x9f, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa2, 
    0x3, 0x2, 0x2, 0x2, 0xa2, 0x2b, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa6, 0x7, 
    0x4, 0x2, 0x2, 0xa4, 0xa5, 0x7, 0x19, 0x2, 0x2, 0xa5, 0xa7, 0x7, 0x9, 
    0x2, 0x2, 0xa6, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 0x3, 0x2, 0x2, 
    0x2, 0xa7, 0x2d, 0x3, 0x2, 0x2, 0x2, 0xa8, 0xab, 0x7, 0x5, 0x2, 0x2, 
    0xa9, 0xaa, 0x7, 0x19, 0x2, 0x2, 0xaa, 0xac, 0x7, 0x9, 0x2, 0x2, 0xab, 
    0xa9, 0x3, 0x2, 0x2, 0x2, 0xab, 0xac, 0x3, 0x2, 0x2, 0x2, 0xac, 0xb8, 
    0x3, 0x2, 0x2, 0x2, 0xad, 0xb0, 0x7, 0x6, 0x2, 0x2, 0xae, 0xaf, 0x7, 
    0x19, 0x2, 0x2, 0xaf, 0xb1, 0x7, 0x9, 0x2, 0x2, 0xb0, 0xae, 0x3, 0x2, 
    0x2, 0x2, 0xb0, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xb1, 0xb8, 0x3, 0x2, 0x2, 
    0x2, 0xb2, 0xb5, 0x7, 0x7, 0x2, 0x2, 0xb3, 0xb4, 0x7, 0x19, 0x2, 0x2, 
    0xb4, 0xb6, 0x7, 0x9, 0x2, 0x2, 0xb5, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb5, 
    0xb6, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb8, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xa8, 
    0x3, 0x2, 0x2, 0x2, 0xb7, 0xad, 0x3, 0x2, 0x2, 0x2, 0xb7, 0xb2, 0x3, 
    0x2, 0x2, 0x2, 0xb8, 0x2f, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xbd, 0x5, 0x32, 
    0x1a, 0x2, 0xba, 0xbd, 0x5, 0x34, 0x1b, 0x2, 0xbb, 0xbd, 0x5, 0x36, 
    0x1c, 0x2, 0xbc, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xba, 0x3, 0x2, 0x2, 
    0x2, 0xbc, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xbd, 0x31, 0x3, 0x2, 0x2, 0x2, 
    0xbe, 0xbf, 0x7, 0x3, 0x2, 0x2, 0xbf, 0x33, 0x3, 0x2, 0x2, 0x2, 0xc0, 
    0xc1, 0x7, 0x17, 0x2, 0x2, 0xc1, 0xc2, 0x5, 0x30, 0x19, 0x2, 0xc2, 0xc3, 
    0x7, 0x19, 0x2, 0x2, 0xc3, 0xc4, 0x7, 0x9, 0x2, 0x2, 0xc4, 0xc5, 0x7, 
    0x18, 0x2, 0x2, 0xc5, 0x35, 0x3, 0x2, 0x2, 0x2, 0xc6, 0xc7, 0x7, 0xf, 
    0x2, 0x2, 0xc7, 0x37, 0x3, 0x2, 0x2, 0x2, 0x14, 0x3a, 0x3c, 0x41, 0x50, 
    0x5f, 0x6a, 0x73, 0x82, 0x89, 0x95, 0x9c, 0xa1, 0xa6, 0xab, 0xb0, 0xb5, 
    0xb7, 0xbc, 
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
