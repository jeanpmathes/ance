
// Generated from ./ance.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  anceParser : public antlr4::Parser {
public:
  enum {
    STRING = 1, INTEGER = 2, MAIN = 3, PRINT = 4, RETURN = 5, CONST = 6, 
    IDENTIFIER = 7, ASSIGNMENT = 8, PARANTHESE_OPEN = 9, PARANTHESE_CLOSED = 10, 
    BRACE_OPEN = 11, BRACE_CLOSED = 12, SEMICOLON = 13, WHITESPACE = 14
  };

  enum {
    RuleFile = 0, RuleValue = 1, RuleConstant_declaration = 2, RuleType = 3, 
    RuleEntry = 4, RuleFunction = 5, RuleStatement = 6, RuleFunction_call = 7, 
    RulePrint_statement = 8, RuleReturn_statement = 9, RuleExpression = 10, 
    RuleVariable_expression = 11, RuleLiteral_expression = 12
  };

  anceParser(antlr4::TokenStream *input);
  ~anceParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class FileContext;
  class ValueContext;
  class Constant_declarationContext;
  class TypeContext;
  class EntryContext;
  class FunctionContext;
  class StatementContext;
  class Function_callContext;
  class Print_statementContext;
  class Return_statementContext;
  class ExpressionContext;
  class Variable_expressionContext;
  class Literal_expressionContext; 

  class  FileContext : public antlr4::ParserRuleContext {
  public:
    FileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<ValueContext *> value();
    ValueContext* value(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FileContext* file();

  class  ValueContext : public antlr4::ParserRuleContext {
  public:
    ValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Constant_declarationContext *constant_declaration();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ValueContext* value();

  class  Constant_declarationContext : public antlr4::ParserRuleContext {
  public:
    Constant_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONST();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *ASSIGNMENT();
    Literal_expressionContext *literal_expression();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Constant_declarationContext* constant_declaration();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EntryContext *entry();
    FunctionContext *function();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class  EntryContext : public antlr4::ParserRuleContext {
  public:
    EntryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MAIN();
    antlr4::tree::TerminalNode *PARANTHESE_OPEN();
    antlr4::tree::TerminalNode *PARANTHESE_CLOSED();
    antlr4::tree::TerminalNode *BRACE_OPEN();
    antlr4::tree::TerminalNode *BRACE_CLOSED();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EntryContext* entry();

  class  FunctionContext : public antlr4::ParserRuleContext {
  public:
    FunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *PARANTHESE_OPEN();
    antlr4::tree::TerminalNode *PARANTHESE_CLOSED();
    antlr4::tree::TerminalNode *BRACE_OPEN();
    antlr4::tree::TerminalNode *BRACE_CLOSED();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionContext* function();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Function_callContext *function_call();
    Print_statementContext *print_statement();
    Return_statementContext *return_statement();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  Function_callContext : public antlr4::ParserRuleContext {
  public:
    Function_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *PARANTHESE_OPEN();
    antlr4::tree::TerminalNode *PARANTHESE_CLOSED();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_callContext* function_call();

  class  Print_statementContext : public antlr4::ParserRuleContext {
  public:
    Print_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PRINT();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Print_statementContext* print_statement();

  class  Return_statementContext : public antlr4::ParserRuleContext {
  public:
    Return_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RETURN();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *INTEGER();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Return_statementContext* return_statement();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Variable_expressionContext *variable_expression();
    Literal_expressionContext *literal_expression();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  Variable_expressionContext : public antlr4::ParserRuleContext {
  public:
    Variable_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variable_expressionContext* variable_expression();

  class  Literal_expressionContext : public antlr4::ParserRuleContext {
  public:
    Literal_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Literal_expressionContext* literal_expression();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

