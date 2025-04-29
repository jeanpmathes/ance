
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  anceParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, IDENTIFIER = 14, 
    SEMICOLON = 15, WHITESPACE = 16, BLOCK_COMMENT = 17, LINE_COMMENT = 18, 
    BRACKET_OPEN = 19, BRACKET_CLOSE = 20, CURLY_BRACKET_OPEN = 21, CURLY_BRACKET_CLOSE = 22, 
    SQUARE_BRACKET_OPEN = 23, SQUARE_BRACKET_CLOSE = 24, POINTY_BRACKET_OPEN = 25, 
    POINTY_BRACKET_CLOSE = 26, ERROR_CHAR = 27
  };

  enum {
    RuleFile = 0, RuleStatement = 1, RuleExpression = 2, RuleArguments = 3, 
    RuleLiteral = 4, RuleBoolean = 5, RuleEntity = 6, RuleAssigner = 7
  };

  explicit anceParser(antlr4::TokenStream *input);

  anceParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~anceParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class FileContext;
  class StatementContext;
  class ExpressionContext;
  class ArgumentsContext;
  class LiteralContext;
  class BooleanContext;
  class EntityContext;
  class AssignerContext; 

  class  FileContext : public antlr4::ParserRuleContext {
  public:
    FileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    antlr4::tree::TerminalNode *EOF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FileContext* file();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StatementContext() = default;
    void copyFrom(StatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BreakStatementContext : public StatementContext {
  public:
    BreakStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IfStatementContext : public StatementContext {
  public:
    IfStatementContext(StatementContext *ctx);

    anceParser::StatementContext *trueBlock = nullptr;
    anceParser::StatementContext *falseBlock = nullptr;
    ExpressionContext *expression();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignmentStatementContext : public StatementContext {
  public:
    AssignmentStatementContext(StatementContext *ctx);

    EntityContext *entity();
    AssignerContext *assigner();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExpressionStatementContext : public StatementContext {
  public:
    ExpressionStatementContext(StatementContext *ctx);

    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BlockStatementContext : public StatementContext {
  public:
    BlockStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *CURLY_BRACKET_OPEN();
    antlr4::tree::TerminalNode *CURLY_BRACKET_CLOSE();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LoopStatementContext : public StatementContext {
  public:
    LoopStatementContext(StatementContext *ctx);

    StatementContext *statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  WhileStatementContext : public StatementContext {
  public:
    WhileStatementContext(StatementContext *ctx);

    ExpressionContext *expression();
    StatementContext *statement();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LetStatementContext : public StatementContext {
  public:
    LetStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();
    AssignerContext *assigner();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ContinueStatementContext : public StatementContext {
  public:
    ContinueStatementContext(StatementContext *ctx);

    antlr4::tree::TerminalNode *SEMICOLON();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StatementContext* statement();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LiteralExpressionContext : public ExpressionContext {
  public:
    LiteralExpressionContext(ExpressionContext *ctx);

    LiteralContext *literal();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AccessExpressionContext : public ExpressionContext {
  public:
    AccessExpressionContext(ExpressionContext *ctx);

    EntityContext *entity();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CallExpressionContext : public ExpressionContext {
  public:
    CallExpressionContext(ExpressionContext *ctx);

    EntityContext *entity();
    antlr4::tree::TerminalNode *BRACKET_OPEN();
    ArgumentsContext *arguments();
    antlr4::tree::TerminalNode *BRACKET_CLOSE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();

  class  ArgumentsContext : public antlr4::ParserRuleContext {
  public:
    ArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentsContext* arguments();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LiteralContext() = default;
    void copyFrom(LiteralContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BooleanLiteralContext : public LiteralContext {
  public:
    BooleanLiteralContext(LiteralContext *ctx);

    BooleanContext *boolean();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LiteralContext* literal();

  class  BooleanContext : public antlr4::ParserRuleContext {
  public:
    BooleanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BooleanContext() = default;
    void copyFrom(BooleanContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TrueContext : public BooleanContext {
  public:
    TrueContext(BooleanContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FalseContext : public BooleanContext {
  public:
    FalseContext(BooleanContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BooleanContext* boolean();

  class  EntityContext : public antlr4::ParserRuleContext {
  public:
    EntityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EntityContext* entity();

  class  AssignerContext : public antlr4::ParserRuleContext {
  public:
    AssignerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignerContext* assigner();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

