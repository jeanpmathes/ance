
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

std::vector<anceParser::TypeContext *> anceParser::FileContext::type() {
  return getRuleContexts<anceParser::TypeContext>();
}

anceParser::TypeContext* anceParser::FileContext::type(size_t i) {
  return getRuleContext<anceParser::TypeContext>(i);
}

std::vector<anceParser::ValueContext *> anceParser::FileContext::value() {
  return getRuleContexts<anceParser::ValueContext>();
}

anceParser::ValueContext* anceParser::FileContext::value(size_t i) {
  return getRuleContext<anceParser::ValueContext>(i);
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
    setState(28); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(28);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case anceParser::MAIN:
        case anceParser::IDENTIFIER: {
          setState(26);
          type();
          break;
        }

        case anceParser::CONST: {
          setState(27);
          value();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(30); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::MAIN)
      | (1ULL << anceParser::CONST)
      | (1ULL << anceParser::IDENTIFIER))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

anceParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::Constant_declarationContext* anceParser::ValueContext::constant_declaration() {
  return getRuleContext<anceParser::Constant_declarationContext>(0);
}


size_t anceParser::ValueContext::getRuleIndex() const {
  return anceParser::RuleValue;
}


antlrcpp::Any anceParser::ValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitValue(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ValueContext* anceParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 2, anceParser::RuleValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(32);
    constant_declaration();
   
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

tree::TerminalNode* anceParser::Constant_declarationContext::CONST() {
  return getToken(anceParser::CONST, 0);
}

tree::TerminalNode* anceParser::Constant_declarationContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::Constant_declarationContext::ASSIGNMENT() {
  return getToken(anceParser::ASSIGNMENT, 0);
}

anceParser::Literal_expressionContext* anceParser::Constant_declarationContext::literal_expression() {
  return getRuleContext<anceParser::Literal_expressionContext>(0);
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
    setState(34);
    match(anceParser::CONST);
    setState(35);
    match(anceParser::IDENTIFIER);
    setState(36);
    match(anceParser::ASSIGNMENT);
    setState(37);
    literal_expression();
    setState(38);
    match(anceParser::SEMICOLON);
   
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


antlrcpp::Any anceParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::TypeContext* anceParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 6, anceParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(42);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::MAIN: {
        enterOuterAlt(_localctx, 1);
        setState(40);
        entry();
        break;
      }

      case anceParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(41);
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


antlrcpp::Any anceParser::EntryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitEntry(this);
  else
    return visitor->visitChildren(this);
}

anceParser::EntryContext* anceParser::entry() {
  EntryContext *_localctx = _tracker.createInstance<EntryContext>(_ctx, getState());
  enterRule(_localctx, 8, anceParser::RuleEntry);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(44);
    match(anceParser::MAIN);
    setState(45);
    match(anceParser::PARANTHESE_OPEN);
    setState(46);
    match(anceParser::PARANTHESE_CLOSED);
    setState(47);
    match(anceParser::BRACE_OPEN);
    setState(49); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(48);
      statement();
      setState(51); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::PRINT)
      | (1ULL << anceParser::RETURN)
      | (1ULL << anceParser::IDENTIFIER))) != 0));
    setState(53);
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
    setState(55);
    match(anceParser::IDENTIFIER);
    setState(56);
    match(anceParser::PARANTHESE_OPEN);
    setState(57);
    match(anceParser::PARANTHESE_CLOSED);
    setState(58);
    match(anceParser::BRACE_OPEN);
    setState(60); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(59);
      statement();
      setState(62); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::PRINT)
      | (1ULL << anceParser::RETURN)
      | (1ULL << anceParser::IDENTIFIER))) != 0));
    setState(64);
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


antlrcpp::Any anceParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::StatementContext* anceParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 12, anceParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(69);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(66);
        function_call();
        break;
      }

      case anceParser::PRINT: {
        enterOuterAlt(_localctx, 2);
        setState(67);
        print_statement();
        break;
      }

      case anceParser::RETURN: {
        enterOuterAlt(_localctx, 3);
        setState(68);
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


antlrcpp::Any anceParser::Function_callContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFunction_call(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Function_callContext* anceParser::function_call() {
  Function_callContext *_localctx = _tracker.createInstance<Function_callContext>(_ctx, getState());
  enterRule(_localctx, 14, anceParser::RuleFunction_call);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    match(anceParser::IDENTIFIER);
    setState(72);
    match(anceParser::PARANTHESE_OPEN);
    setState(73);
    match(anceParser::PARANTHESE_CLOSED);
    setState(74);
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
  enterRule(_localctx, 16, anceParser::RulePrint_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    match(anceParser::PRINT);
    setState(77);
    expression();
    setState(78);
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


antlrcpp::Any anceParser::Return_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitReturn_statement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::Return_statementContext* anceParser::return_statement() {
  Return_statementContext *_localctx = _tracker.createInstance<Return_statementContext>(_ctx, getState());
  enterRule(_localctx, 18, anceParser::RuleReturn_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(80);
    match(anceParser::RETURN);
    setState(82);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER) {
      setState(81);
      match(anceParser::INTEGER);
    }
    setState(84);
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

anceParser::Literal_expressionContext* anceParser::ExpressionContext::literal_expression() {
  return getRuleContext<anceParser::Literal_expressionContext>(0);
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
  enterRule(_localctx, 20, anceParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(88);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(86);
        variable_expression();
        break;
      }

      case anceParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(87);
        literal_expression();
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
  enterRule(_localctx, 22, anceParser::RuleVariable_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    match(anceParser::IDENTIFIER);
   
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
  enterRule(_localctx, 24, anceParser::RuleLiteral_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    match(anceParser::STRING);
   
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
  "file", "value", "constant_declaration", "type", "entry", "function", 
  "statement", "function_call", "print_statement", "return_statement", "expression", 
  "variable_expression", "literal_expression"
};

std::vector<std::string> anceParser::_literalNames = {
  "", "", "", "'main'", "'print'", "'return'", "'const'", "", "'='", "'('", 
  "')'", "'{'", "'}'", "';'"
};

std::vector<std::string> anceParser::_symbolicNames = {
  "", "STRING", "INTEGER", "MAIN", "PRINT", "RETURN", "CONST", "IDENTIFIER", 
  "ASSIGNMENT", "PARANTHESE_OPEN", "PARANTHESE_CLOSED", "BRACE_OPEN", "BRACE_CLOSED", 
  "SEMICOLON", "WHITESPACE"
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
    0x3, 0x10, 0x61, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x3, 
    0x2, 0x3, 0x2, 0x6, 0x2, 0x1f, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x20, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x2d, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x6, 0x6, 0x34, 0xa, 0x6, 0xd, 0x6, 0xe, 
    0x6, 0x35, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x6, 0x7, 0x3f, 0xa, 0x7, 0xd, 0x7, 0xe, 0x7, 0x40, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x48, 0xa, 0x8, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x55, 0xa, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x5b, 0xa, 0xc, 0x3, 0xd, 0x3, 
    0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x2, 0x2, 0xf, 0x2, 0x4, 0x6, 0x8, 
    0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x2, 0x2, 0x2, 0x5c, 
    0x2, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x4, 0x22, 0x3, 0x2, 0x2, 0x2, 0x6, 0x24, 
    0x3, 0x2, 0x2, 0x2, 0x8, 0x2c, 0x3, 0x2, 0x2, 0x2, 0xa, 0x2e, 0x3, 0x2, 
    0x2, 0x2, 0xc, 0x39, 0x3, 0x2, 0x2, 0x2, 0xe, 0x47, 0x3, 0x2, 0x2, 0x2, 
    0x10, 0x49, 0x3, 0x2, 0x2, 0x2, 0x12, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x14, 
    0x52, 0x3, 0x2, 0x2, 0x2, 0x16, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x18, 0x5c, 
    0x3, 0x2, 0x2, 0x2, 0x1a, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1f, 0x5, 
    0x8, 0x5, 0x2, 0x1d, 0x1f, 0x5, 0x4, 0x3, 0x2, 0x1e, 0x1c, 0x3, 0x2, 
    0x2, 0x2, 0x1e, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x3, 0x2, 0x2, 
    0x2, 0x20, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x3, 0x2, 0x2, 0x2, 
    0x21, 0x3, 0x3, 0x2, 0x2, 0x2, 0x22, 0x23, 0x5, 0x6, 0x4, 0x2, 0x23, 
    0x5, 0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 0x7, 0x8, 0x2, 0x2, 0x25, 0x26, 
    0x7, 0x9, 0x2, 0x2, 0x26, 0x27, 0x7, 0xa, 0x2, 0x2, 0x27, 0x28, 0x5, 
    0x1a, 0xe, 0x2, 0x28, 0x29, 0x7, 0xf, 0x2, 0x2, 0x29, 0x7, 0x3, 0x2, 
    0x2, 0x2, 0x2a, 0x2d, 0x5, 0xa, 0x6, 0x2, 0x2b, 0x2d, 0x5, 0xc, 0x7, 
    0x2, 0x2c, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2b, 0x3, 0x2, 0x2, 0x2, 
    0x2d, 0x9, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x2f, 0x7, 0x5, 0x2, 0x2, 0x2f, 
    0x30, 0x7, 0xb, 0x2, 0x2, 0x30, 0x31, 0x7, 0xc, 0x2, 0x2, 0x31, 0x33, 
    0x7, 0xd, 0x2, 0x2, 0x32, 0x34, 0x5, 0xe, 0x8, 0x2, 0x33, 0x32, 0x3, 
    0x2, 0x2, 0x2, 0x34, 0x35, 0x3, 0x2, 0x2, 0x2, 0x35, 0x33, 0x3, 0x2, 
    0x2, 0x2, 0x35, 0x36, 0x3, 0x2, 0x2, 0x2, 0x36, 0x37, 0x3, 0x2, 0x2, 
    0x2, 0x37, 0x38, 0x7, 0xe, 0x2, 0x2, 0x38, 0xb, 0x3, 0x2, 0x2, 0x2, 
    0x39, 0x3a, 0x7, 0x9, 0x2, 0x2, 0x3a, 0x3b, 0x7, 0xb, 0x2, 0x2, 0x3b, 
    0x3c, 0x7, 0xc, 0x2, 0x2, 0x3c, 0x3e, 0x7, 0xd, 0x2, 0x2, 0x3d, 0x3f, 
    0x5, 0xe, 0x8, 0x2, 0x3e, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 0x3, 
    0x2, 0x2, 0x2, 0x40, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x40, 0x41, 0x3, 0x2, 
    0x2, 0x2, 0x41, 0x42, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x7, 0xe, 0x2, 
    0x2, 0x43, 0xd, 0x3, 0x2, 0x2, 0x2, 0x44, 0x48, 0x5, 0x10, 0x9, 0x2, 
    0x45, 0x48, 0x5, 0x12, 0xa, 0x2, 0x46, 0x48, 0x5, 0x14, 0xb, 0x2, 0x47, 
    0x44, 0x3, 0x2, 0x2, 0x2, 0x47, 0x45, 0x3, 0x2, 0x2, 0x2, 0x47, 0x46, 
    0x3, 0x2, 0x2, 0x2, 0x48, 0xf, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4a, 0x7, 
    0x9, 0x2, 0x2, 0x4a, 0x4b, 0x7, 0xb, 0x2, 0x2, 0x4b, 0x4c, 0x7, 0xc, 
    0x2, 0x2, 0x4c, 0x4d, 0x7, 0xf, 0x2, 0x2, 0x4d, 0x11, 0x3, 0x2, 0x2, 
    0x2, 0x4e, 0x4f, 0x7, 0x6, 0x2, 0x2, 0x4f, 0x50, 0x5, 0x16, 0xc, 0x2, 
    0x50, 0x51, 0x7, 0xf, 0x2, 0x2, 0x51, 0x13, 0x3, 0x2, 0x2, 0x2, 0x52, 
    0x54, 0x7, 0x7, 0x2, 0x2, 0x53, 0x55, 0x7, 0x4, 0x2, 0x2, 0x54, 0x53, 
    0x3, 0x2, 0x2, 0x2, 0x54, 0x55, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x3, 
    0x2, 0x2, 0x2, 0x56, 0x57, 0x7, 0xf, 0x2, 0x2, 0x57, 0x15, 0x3, 0x2, 
    0x2, 0x2, 0x58, 0x5b, 0x5, 0x18, 0xd, 0x2, 0x59, 0x5b, 0x5, 0x1a, 0xe, 
    0x2, 0x5a, 0x58, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x59, 0x3, 0x2, 0x2, 0x2, 
    0x5b, 0x17, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 0x7, 0x9, 0x2, 0x2, 0x5d, 
    0x19, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x5f, 0x7, 0x3, 0x2, 0x2, 0x5f, 0x1b, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x1e, 0x20, 0x2c, 0x35, 0x40, 0x47, 0x54, 0x5a, 
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
