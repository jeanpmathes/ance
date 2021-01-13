
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
    setState(34); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(34);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case anceParser::MAIN:
        case anceParser::IDENTIFIER: {
          setState(32);
          type();
          break;
        }

        case anceParser::PUBLIC:
        case anceParser::PRIVATE: {
          setState(33);
          value();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(36); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::MAIN)
      | (1ULL << anceParser::PUBLIC)
      | (1ULL << anceParser::PRIVATE)
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

anceParser::Variable_declarationContext* anceParser::ValueContext::variable_declaration() {
  return getRuleContext<anceParser::Variable_declarationContext>(0);
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
    setState(40);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(38);
      constant_declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(39);
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
    setState(42);
    access_modifier();
    setState(43);
    match(anceParser::CONST);
    setState(44);
    match(anceParser::IDENTIFIER);
    setState(45);
    match(anceParser::ASSIGNMENT);
    setState(46);
    literal_expression();
    setState(47);
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

tree::TerminalNode* anceParser::Variable_declarationContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::Variable_declarationContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

tree::TerminalNode* anceParser::Variable_declarationContext::ASSIGNMENT() {
  return getToken(anceParser::ASSIGNMENT, 0);
}

anceParser::Literal_expressionContext* anceParser::Variable_declarationContext::literal_expression() {
  return getRuleContext<anceParser::Literal_expressionContext>(0);
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
    setState(49);
    access_modifier();
    setState(50);
    match(anceParser::IDENTIFIER);
    setState(53);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::ASSIGNMENT) {
      setState(51);
      match(anceParser::ASSIGNMENT);
      setState(52);
      literal_expression();
    }
    setState(55);
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
  enterRule(_localctx, 8, anceParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(59);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::MAIN: {
        enterOuterAlt(_localctx, 1);
        setState(57);
        entry();
        break;
      }

      case anceParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(58);
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
  enterRule(_localctx, 10, anceParser::RuleEntry);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(61);
    match(anceParser::MAIN);
    setState(62);
    match(anceParser::PARANTHESE_OPEN);
    setState(63);
    match(anceParser::PARANTHESE_CLOSED);
    setState(64);
    match(anceParser::BRACE_OPEN);
    setState(66); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(65);
      statement();
      setState(68); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::PRINT)
      | (1ULL << anceParser::RETURN)
      | (1ULL << anceParser::IDENTIFIER))) != 0));
    setState(70);
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
  enterRule(_localctx, 12, anceParser::RuleFunction);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(72);
    match(anceParser::IDENTIFIER);
    setState(73);
    match(anceParser::PARANTHESE_OPEN);
    setState(74);
    match(anceParser::PARANTHESE_CLOSED);
    setState(75);
    match(anceParser::BRACE_OPEN);
    setState(77); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(76);
      statement();
      setState(79); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::PRINT)
      | (1ULL << anceParser::RETURN)
      | (1ULL << anceParser::IDENTIFIER))) != 0));
    setState(81);
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
  enterRule(_localctx, 14, anceParser::RuleAccess_modifier);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(83);
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

anceParser::Function_callContext* anceParser::StatementContext::function_call() {
  return getRuleContext<anceParser::Function_callContext>(0);
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
  enterRule(_localctx, 16, anceParser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(89);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(85);
      function_call();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(86);
      variable_assignment();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(87);
      print_statement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(88);
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
  enterRule(_localctx, 18, anceParser::RuleFunction_call);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(91);
    match(anceParser::IDENTIFIER);
    setState(92);
    match(anceParser::PARANTHESE_OPEN);
    setState(93);
    match(anceParser::PARANTHESE_CLOSED);
    setState(94);
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
    setState(96);
    match(anceParser::IDENTIFIER);
    setState(97);
    match(anceParser::ASSIGNMENT);
    setState(98);
    expression();
    setState(99);
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
    setState(101);
    match(anceParser::PRINT);
    setState(102);
    expression();
    setState(103);
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
  enterRule(_localctx, 24, anceParser::RuleReturn_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(105);
    match(anceParser::RETURN);
    setState(107);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER) {
      setState(106);
      match(anceParser::INTEGER);
    }
    setState(109);
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
  enterRule(_localctx, 26, anceParser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(113);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(111);
        variable_expression();
        break;
      }

      case anceParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(112);
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
  enterRule(_localctx, 28, anceParser::RuleVariable_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
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
  enterRule(_localctx, 30, anceParser::RuleLiteral_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(117);
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
  "file", "value", "constant_declaration", "variable_declaration", "type", 
  "entry", "function", "access_modifier", "statement", "function_call", 
  "variable_assignment", "print_statement", "return_statement", "expression", 
  "variable_expression", "literal_expression"
};

std::vector<std::string> anceParser::_literalNames = {
  "", "", "", "'main'", "'print'", "'return'", "'const'", "'public'", "'private'", 
  "", "'='", "'('", "')'", "'{'", "'}'", "';'"
};

std::vector<std::string> anceParser::_symbolicNames = {
  "", "STRING", "INTEGER", "MAIN", "PRINT", "RETURN", "CONST", "PUBLIC", 
  "PRIVATE", "IDENTIFIER", "ASSIGNMENT", "PARANTHESE_OPEN", "PARANTHESE_CLOSED", 
  "BRACE_OPEN", "BRACE_CLOSED", "SEMICOLON", "WHITESPACE"
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
    0x3, 0x12, 0x7a, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 0x4, 
    0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x3, 0x2, 
    0x3, 0x2, 0x6, 0x2, 0x25, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x26, 0x3, 0x3, 
    0x3, 0x3, 0x5, 0x3, 0x2b, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x5, 0x5, 0x38, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 
    0x5, 0x6, 0x3e, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x6, 0x7, 0x45, 0xa, 0x7, 0xd, 0x7, 0xe, 0x7, 0x46, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x6, 0x8, 0x50, 
    0xa, 0x8, 0xd, 0x8, 0xe, 0x8, 0x51, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x5c, 0xa, 0xa, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x6e, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xf, 0x3, 0xf, 0x5, 0xf, 0x74, 0xa, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 
    0x11, 0x3, 0x11, 0x3, 0x11, 0x2, 0x2, 0x12, 0x2, 0x4, 0x6, 0x8, 0xa, 
    0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x2, 
    0x3, 0x3, 0x2, 0x9, 0xa, 0x2, 0x75, 0x2, 0x24, 0x3, 0x2, 0x2, 0x2, 0x4, 
    0x2a, 0x3, 0x2, 0x2, 0x2, 0x6, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x8, 0x33, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x3d, 0x3, 0x2, 0x2, 0x2, 0xc, 0x3f, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x10, 0x55, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x14, 0x5d, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0x62, 0x3, 0x2, 0x2, 0x2, 0x18, 0x67, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x6b, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x73, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x75, 
    0x3, 0x2, 0x2, 0x2, 0x20, 0x77, 0x3, 0x2, 0x2, 0x2, 0x22, 0x25, 0x5, 
    0xa, 0x6, 0x2, 0x23, 0x25, 0x5, 0x4, 0x3, 0x2, 0x24, 0x22, 0x3, 0x2, 
    0x2, 0x2, 0x24, 0x23, 0x3, 0x2, 0x2, 0x2, 0x25, 0x26, 0x3, 0x2, 0x2, 
    0x2, 0x26, 0x24, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 0x3, 0x2, 0x2, 0x2, 
    0x27, 0x3, 0x3, 0x2, 0x2, 0x2, 0x28, 0x2b, 0x5, 0x6, 0x4, 0x2, 0x29, 
    0x2b, 0x5, 0x8, 0x5, 0x2, 0x2a, 0x28, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x29, 
    0x3, 0x2, 0x2, 0x2, 0x2b, 0x5, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0x5, 
    0x10, 0x9, 0x2, 0x2d, 0x2e, 0x7, 0x8, 0x2, 0x2, 0x2e, 0x2f, 0x7, 0xb, 
    0x2, 0x2, 0x2f, 0x30, 0x7, 0xc, 0x2, 0x2, 0x30, 0x31, 0x5, 0x20, 0x11, 
    0x2, 0x31, 0x32, 0x7, 0x11, 0x2, 0x2, 0x32, 0x7, 0x3, 0x2, 0x2, 0x2, 
    0x33, 0x34, 0x5, 0x10, 0x9, 0x2, 0x34, 0x37, 0x7, 0xb, 0x2, 0x2, 0x35, 
    0x36, 0x7, 0xc, 0x2, 0x2, 0x36, 0x38, 0x5, 0x20, 0x11, 0x2, 0x37, 0x35, 
    0x3, 0x2, 0x2, 0x2, 0x37, 0x38, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x3, 
    0x2, 0x2, 0x2, 0x39, 0x3a, 0x7, 0x11, 0x2, 0x2, 0x3a, 0x9, 0x3, 0x2, 
    0x2, 0x2, 0x3b, 0x3e, 0x5, 0xc, 0x7, 0x2, 0x3c, 0x3e, 0x5, 0xe, 0x8, 
    0x2, 0x3d, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3c, 0x3, 0x2, 0x2, 0x2, 
    0x3e, 0xb, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 0x7, 0x5, 0x2, 0x2, 0x40, 
    0x41, 0x7, 0xd, 0x2, 0x2, 0x41, 0x42, 0x7, 0xe, 0x2, 0x2, 0x42, 0x44, 
    0x7, 0xf, 0x2, 0x2, 0x43, 0x45, 0x5, 0x12, 0xa, 0x2, 0x44, 0x43, 0x3, 
    0x2, 0x2, 0x2, 0x45, 0x46, 0x3, 0x2, 0x2, 0x2, 0x46, 0x44, 0x3, 0x2, 
    0x2, 0x2, 0x46, 0x47, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x3, 0x2, 0x2, 
    0x2, 0x48, 0x49, 0x7, 0x10, 0x2, 0x2, 0x49, 0xd, 0x3, 0x2, 0x2, 0x2, 
    0x4a, 0x4b, 0x7, 0xb, 0x2, 0x2, 0x4b, 0x4c, 0x7, 0xd, 0x2, 0x2, 0x4c, 
    0x4d, 0x7, 0xe, 0x2, 0x2, 0x4d, 0x4f, 0x7, 0xf, 0x2, 0x2, 0x4e, 0x50, 
    0x5, 0x12, 0xa, 0x2, 0x4f, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 0x3, 
    0x2, 0x2, 0x2, 0x51, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x3, 0x2, 
    0x2, 0x2, 0x52, 0x53, 0x3, 0x2, 0x2, 0x2, 0x53, 0x54, 0x7, 0x10, 0x2, 
    0x2, 0x54, 0xf, 0x3, 0x2, 0x2, 0x2, 0x55, 0x56, 0x9, 0x2, 0x2, 0x2, 
    0x56, 0x11, 0x3, 0x2, 0x2, 0x2, 0x57, 0x5c, 0x5, 0x14, 0xb, 0x2, 0x58, 
    0x5c, 0x5, 0x16, 0xc, 0x2, 0x59, 0x5c, 0x5, 0x18, 0xd, 0x2, 0x5a, 0x5c, 
    0x5, 0x1a, 0xe, 0x2, 0x5b, 0x57, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x58, 0x3, 
    0x2, 0x2, 0x2, 0x5b, 0x59, 0x3, 0x2, 0x2, 0x2, 0x5b, 0x5a, 0x3, 0x2, 
    0x2, 0x2, 0x5c, 0x13, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5e, 0x7, 0xb, 0x2, 
    0x2, 0x5e, 0x5f, 0x7, 0xd, 0x2, 0x2, 0x5f, 0x60, 0x7, 0xe, 0x2, 0x2, 
    0x60, 0x61, 0x7, 0x11, 0x2, 0x2, 0x61, 0x15, 0x3, 0x2, 0x2, 0x2, 0x62, 
    0x63, 0x7, 0xb, 0x2, 0x2, 0x63, 0x64, 0x7, 0xc, 0x2, 0x2, 0x64, 0x65, 
    0x5, 0x1c, 0xf, 0x2, 0x65, 0x66, 0x7, 0x11, 0x2, 0x2, 0x66, 0x17, 0x3, 
    0x2, 0x2, 0x2, 0x67, 0x68, 0x7, 0x6, 0x2, 0x2, 0x68, 0x69, 0x5, 0x1c, 
    0xf, 0x2, 0x69, 0x6a, 0x7, 0x11, 0x2, 0x2, 0x6a, 0x19, 0x3, 0x2, 0x2, 
    0x2, 0x6b, 0x6d, 0x7, 0x7, 0x2, 0x2, 0x6c, 0x6e, 0x7, 0x4, 0x2, 0x2, 
    0x6d, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6e, 
    0x6f, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 0x7, 0x11, 0x2, 0x2, 0x70, 0x1b, 
    0x3, 0x2, 0x2, 0x2, 0x71, 0x74, 0x5, 0x1e, 0x10, 0x2, 0x72, 0x74, 0x5, 
    0x20, 0x11, 0x2, 0x73, 0x71, 0x3, 0x2, 0x2, 0x2, 0x73, 0x72, 0x3, 0x2, 
    0x2, 0x2, 0x74, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x75, 0x76, 0x7, 0xb, 0x2, 
    0x2, 0x76, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x77, 0x78, 0x7, 0x3, 0x2, 0x2, 
    0x78, 0x21, 0x3, 0x2, 0x2, 0x2, 0xc, 0x24, 0x26, 0x2a, 0x37, 0x3d, 0x46, 
    0x51, 0x5b, 0x6d, 0x73, 
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
