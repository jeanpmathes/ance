
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  anceParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, IDENTIFIER = 22, INTEGER = 23, STRING = 24, SEMICOLON = 25, 
    WHITESPACE = 26, BLOCK_COMMENT = 27, LINE_COMMENT = 28, BRACKET_OPEN = 29, 
    BRACKET_CLOSE = 30, CURLY_BRACKET_OPEN = 31, CURLY_BRACKET_CLOSE = 32, 
    SQUARE_BRACKET_OPEN = 33, SQUARE_BRACKET_CLOSE = 34, POINTY_BRACKET_OPEN = 35, 
    POINTY_BRACKET_CLOSE = 36, ERROR_CHAR = 37
  };

  enum {
    RuleUnorderedScopeFile = 0, RuleOrderedScopeFile = 1, RuleStatement = 2, 
    RuleExpression = 3, RuleUnary = 4, RuleLiteral = 5, RuleType = 6, RuleBoolean = 7, 
    RuleEntity = 8, RuleAssigner = 9
  };

  explicit anceParser(antlr4::TokenStream *input);

  anceParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~anceParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class UnorderedScopeFileContext;
  class OrderedScopeFileContext;
  class StatementContext;
  class ExpressionContext;
  class UnaryContext;
  class LiteralContext;
  class TypeContext;
  class BooleanContext;
  class EntityContext;
  class AssignerContext; 

  class  UnorderedScopeFileContext : public antlr4::ParserRuleContext {
  public:
    UnorderedScopeFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnorderedScopeFileContext* unorderedScopeFile();

  class  OrderedScopeFileContext : public antlr4::ParserRuleContext {
  public:
    OrderedScopeFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    antlr4::tree::TerminalNode *EOF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OrderedScopeFileContext* orderedScopeFile();

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

    anceParser::ExpressionContext *varType = nullptr;
    anceParser::ExpressionContext *assigned = nullptr;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    AssignerContext *assigner();

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

  class  UnaryOperationExpressionContext : public ExpressionContext {
  public:
    UnaryOperationExpressionContext(ExpressionContext *ctx);

    UnaryContext *unary();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
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
    antlr4::tree::TerminalNode *BRACKET_CLOSE();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  HereExpressionContext : public ExpressionContext {
  public:
    HereExpressionContext(ExpressionContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();

  class  UnaryContext : public antlr4::ParserRuleContext {
  public:
    UnaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    UnaryContext() = default;
    void copyFrom(UnaryContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  UnaryNotContext : public UnaryContext {
  public:
    UnaryNotContext(UnaryContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  UnaryContext* unary();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LiteralContext() = default;
    void copyFrom(LiteralContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TypeLiteralContext : public LiteralContext {
  public:
    TypeLiteralContext(LiteralContext *ctx);

    TypeContext *type();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StringLiteralContext : public LiteralContext {
  public:
    StringLiteralContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *STRING();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BooleanLiteralContext : public LiteralContext {
  public:
    BooleanLiteralContext(LiteralContext *ctx);

    BooleanContext *boolean();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnitLiteralContext : public LiteralContext {
  public:
    UnitLiteralContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *BRACKET_OPEN();
    antlr4::tree::TerminalNode *BRACKET_CLOSE();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SizeLiteralContext : public LiteralContext {
  public:
    SizeLiteralContext(LiteralContext *ctx);

    antlr4::tree::TerminalNode *INTEGER();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LiteralContext* literal();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TypeContext() = default;
    void copyFrom(TypeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BoolTypeContext : public TypeContext {
  public:
    BoolTypeContext(TypeContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StringTypeContext : public TypeContext {
  public:
    StringTypeContext(TypeContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnitTypeContext : public TypeContext {
  public:
    UnitTypeContext(TypeContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SizeTypeContext : public TypeContext {
  public:
    SizeTypeContext(TypeContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TypeTypeContext : public TypeContext {
  public:
    TypeTypeContext(TypeContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TypeContext* type();

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

