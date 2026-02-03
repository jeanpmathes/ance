
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1

#pragma once

#include "antlr4-runtime.h"

class anceParser : public antlr4::Parser
{
  public:
    enum
    {
        T__0                 = 1,
        T__1                 = 2,
        T__2                 = 3,
        T__3                 = 4,
        T__4                 = 5,
        T__5                 = 6,
        T__6                 = 7,
        T__7                 = 8,
        T__8                 = 9,
        T__9                 = 10,
        T__10                = 11,
        T__11                = 12,
        T__12                = 13,
        T__13                = 14,
        T__14                = 15,
        T__15                = 16,
        T__16                = 17,
        T__17                = 18,
        T__18                = 19,
        T__19                = 20,
        T__20                = 21,
        T__21                = 22,
        T__22                = 23,
        IDENTIFIER           = 24,
        INTEGER              = 25,
        STRING               = 26,
        LAMBDA               = 27,
        SEMICOLON            = 28,
        WHITESPACE           = 29,
        BLOCK_COMMENT        = 30,
        LINE_COMMENT         = 31,
        BRACKET_OPEN         = 32,
        BRACKET_CLOSE        = 33,
        CURLY_BRACKET_OPEN   = 34,
        CURLY_BRACKET_CLOSE  = 35,
        SQUARE_BRACKET_OPEN  = 36,
        SQUARE_BRACKET_CLOSE = 37,
        POINTY_BRACKET_OPEN  = 38,
        POINTY_BRACKET_CLOSE = 39,
        ERROR_CHAR           = 40
    };

    enum
    {
        RuleUnorderedScopeFile = 0,
        RuleOrderedScopeFile   = 1,
        RuleDeclaration        = 2,
        RuleStatement          = 3,
        RuleExpression         = 4,
        RuleUnary              = 5,
        RuleLiteral            = 6,
        RuleBoolean            = 7,
        RuleEntity             = 8,
        RuleParameter          = 9,
        RuleAssigner           = 10,
        RuleAccessModifier     = 11
    };

    explicit anceParser(antlr4::TokenStream* input);

    anceParser(antlr4::TokenStream* input, antlr4::atn::ParserATNSimulatorOptions const& options);

    ~anceParser() override;

    std::string getGrammarFileName() const override;

    antlr4::atn::ATN const& getATN() const override;

    std::vector<std::string> const& getRuleNames() const override;

    antlr4::dfa::Vocabulary const& getVocabulary() const override;

    antlr4::atn::SerializedATNView getSerializedATN() const override;

    class UnorderedScopeFileContext;
    class OrderedScopeFileContext;
    class DeclarationContext;
    class StatementContext;
    class ExpressionContext;
    class UnaryContext;
    class LiteralContext;
    class BooleanContext;
    class EntityContext;
    class ParameterContext;
    class AssignerContext;
    class AccessModifierContext;

    class UnorderedScopeFileContext : public antlr4::ParserRuleContext
    {
      public:
        UnorderedScopeFileContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                   getRuleIndex() const override;
        antlr4::tree::TerminalNode*      EOF();
        std::vector<DeclarationContext*> declaration();
        DeclarationContext*              declaration(size_t i);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    UnorderedScopeFileContext* unorderedScopeFile();

    class OrderedScopeFileContext : public antlr4::ParserRuleContext
    {
      public:
        OrderedScopeFileContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        StatementContext*           statement();
        antlr4::tree::TerminalNode* EOF();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    OrderedScopeFileContext* orderedScopeFile();

    class DeclarationContext : public antlr4::ParserRuleContext
    {
      public:
        DeclarationContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        DeclarationContext() = default;
        void copyFrom(DeclarationContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class VariableDeclarationContext : public DeclarationContext
    {
      public:
        VariableDeclarationContext(DeclarationContext* ctx);

        anceParser::ExpressionContext*  varType  = nullptr;
        anceParser::ExpressionContext*  assigned = nullptr;
        AccessModifierContext*          accessModifier();
        antlr4::tree::TerminalNode*     IDENTIFIER();
        antlr4::tree::TerminalNode*     SEMICOLON();
        std::vector<ExpressionContext*> expression();
        ExpressionContext*              expression(size_t i);
        AssignerContext*                assigner();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class RunnableDeclarationContext : public DeclarationContext
    {
      public:
        RunnableDeclarationContext(DeclarationContext* ctx);

        StatementContext* statement();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    DeclarationContext* declaration();

    class StatementContext : public antlr4::ParserRuleContext
    {
      public:
        StatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        StatementContext() = default;
        void copyFrom(StatementContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class BreakStatementContext : public StatementContext
    {
      public:
        BreakStatementContext(StatementContext* ctx);

        antlr4::tree::TerminalNode* SEMICOLON();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class IfStatementContext : public StatementContext
    {
      public:
        IfStatementContext(StatementContext* ctx);

        anceParser::StatementContext*  trueBlock  = nullptr;
        anceParser::StatementContext*  falseBlock = nullptr;
        ExpressionContext*             expression();
        std::vector<StatementContext*> statement();
        StatementContext*              statement(size_t i);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class AssignmentStatementContext : public StatementContext
    {
      public:
        AssignmentStatementContext(StatementContext* ctx);

        EntityContext*              entity();
        AssignerContext*            assigner();
        ExpressionContext*          expression();
        antlr4::tree::TerminalNode* SEMICOLON();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class ExpressionStatementContext : public StatementContext
    {
      public:
        ExpressionStatementContext(StatementContext* ctx);

        ExpressionContext*          expression();
        antlr4::tree::TerminalNode* SEMICOLON();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class ReturnStatementContext : public StatementContext
    {
      public:
        ReturnStatementContext(StatementContext* ctx);

        antlr4::tree::TerminalNode* SEMICOLON();
        ExpressionContext*          expression();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class BlockStatementContext : public StatementContext
    {
      public:
        BlockStatementContext(StatementContext* ctx);

        antlr4::tree::TerminalNode*    CURLY_BRACKET_OPEN();
        antlr4::tree::TerminalNode*    CURLY_BRACKET_CLOSE();
        std::vector<StatementContext*> statement();
        StatementContext*              statement(size_t i);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class LoopStatementContext : public StatementContext
    {
      public:
        LoopStatementContext(StatementContext* ctx);

        StatementContext* statement();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class WhileStatementContext : public StatementContext
    {
      public:
        WhileStatementContext(StatementContext* ctx);

        ExpressionContext* expression();
        StatementContext*  statement();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class LetStatementContext : public StatementContext
    {
      public:
        LetStatementContext(StatementContext* ctx);

        anceParser::ExpressionContext*  varType  = nullptr;
        anceParser::ExpressionContext*  assigned = nullptr;
        antlr4::tree::TerminalNode*     IDENTIFIER();
        antlr4::tree::TerminalNode*     SEMICOLON();
        std::vector<ExpressionContext*> expression();
        ExpressionContext*              expression(size_t i);
        AssignerContext*                assigner();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class ContinueStatementContext : public StatementContext
    {
      public:
        ContinueStatementContext(StatementContext* ctx);

        antlr4::tree::TerminalNode* SEMICOLON();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    StatementContext* statement();

    class ExpressionContext : public antlr4::ParserRuleContext
    {
      public:
        ExpressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        ExpressionContext() = default;
        void copyFrom(ExpressionContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class UnaryOperationExpressionContext : public ExpressionContext
    {
      public:
        UnaryOperationExpressionContext(ExpressionContext* ctx);

        UnaryContext*      unary();
        ExpressionContext* expression();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class LiteralExpressionContext : public ExpressionContext
    {
      public:
        LiteralExpressionContext(ExpressionContext* ctx);

        LiteralContext* literal();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class AccessExpressionContext : public ExpressionContext
    {
      public:
        AccessExpressionContext(ExpressionContext* ctx);

        EntityContext* entity();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class CallExpressionContext : public ExpressionContext
    {
      public:
        CallExpressionContext(ExpressionContext* ctx);

        EntityContext*                  entity();
        antlr4::tree::TerminalNode*     BRACKET_OPEN();
        antlr4::tree::TerminalNode*     BRACKET_CLOSE();
        std::vector<ExpressionContext*> expression();
        ExpressionContext*              expression(size_t i);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class LambdaExpressionContext : public ExpressionContext
    {
      public:
        LambdaExpressionContext(ExpressionContext* ctx);

        anceParser::ExpressionContext*  type = nullptr;
        anceParser::ExpressionContext*  body = nullptr;
        antlr4::tree::TerminalNode*     LAMBDA();
        antlr4::tree::TerminalNode*     BRACKET_OPEN();
        antlr4::tree::TerminalNode*     BRACKET_CLOSE();
        std::vector<ExpressionContext*> expression();
        ExpressionContext*              expression(size_t i);
        antlr4::tree::TerminalNode*     SQUARE_BRACKET_OPEN();
        antlr4::tree::TerminalNode*     SQUARE_BRACKET_CLOSE();
        std::vector<ParameterContext*>  parameter();
        ParameterContext*               parameter(size_t i);
        antlr4::tree::TerminalNode*     CURLY_BRACKET_OPEN();
        antlr4::tree::TerminalNode*     CURLY_BRACKET_CLOSE();
        std::vector<StatementContext*>  statement();
        StatementContext*               statement(size_t i);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class HereExpressionContext : public ExpressionContext
    {
      public:
        HereExpressionContext(ExpressionContext* ctx);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ExpressionContext* expression();

    class UnaryContext : public antlr4::ParserRuleContext
    {
      public:
        UnaryContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        UnaryContext() = default;
        void copyFrom(UnaryContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class UnaryNotContext : public UnaryContext
    {
      public:
        UnaryNotContext(UnaryContext* ctx);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    UnaryContext* unary();

    class LiteralContext : public antlr4::ParserRuleContext
    {
      public:
        LiteralContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        LiteralContext() = default;
        void copyFrom(LiteralContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class StringLiteralContext : public LiteralContext
    {
      public:
        StringLiteralContext(LiteralContext* ctx);

        antlr4::tree::TerminalNode* STRING();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class BooleanLiteralContext : public LiteralContext
    {
      public:
        BooleanLiteralContext(LiteralContext* ctx);

        BooleanContext* boolean();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class UnitLiteralContext : public LiteralContext
    {
      public:
        UnitLiteralContext(LiteralContext* ctx);

        antlr4::tree::TerminalNode* BRACKET_OPEN();
        antlr4::tree::TerminalNode* BRACKET_CLOSE();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class SizeLiteralContext : public LiteralContext
    {
      public:
        SizeLiteralContext(LiteralContext* ctx);

        antlr4::tree::TerminalNode* INTEGER();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    LiteralContext* literal();

    class BooleanContext : public antlr4::ParserRuleContext
    {
      public:
        BooleanContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        BooleanContext() = default;
        void copyFrom(BooleanContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class TrueContext : public BooleanContext
    {
      public:
        TrueContext(BooleanContext* ctx);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FalseContext : public BooleanContext
    {
      public:
        FalseContext(BooleanContext* ctx);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    BooleanContext* boolean();

    class EntityContext : public antlr4::ParserRuleContext
    {
      public:
        EntityContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* IDENTIFIER();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    EntityContext* entity();

    class ParameterContext : public antlr4::ParserRuleContext
    {
      public:
        ParameterContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* IDENTIFIER();
        ExpressionContext*          expression();

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ParameterContext* parameter();

    class AssignerContext : public antlr4::ParserRuleContext
    {
      public:
        AssignerContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        AssignerContext() = default;
        void copyFrom(AssignerContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class CopyAssignerContext : public AssignerContext
    {
      public:
        CopyAssignerContext(AssignerContext* ctx);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FinalCopyAssignerContext : public AssignerContext
    {
      public:
        FinalCopyAssignerContext(AssignerContext* ctx);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    AssignerContext* assigner();

    class AccessModifierContext : public antlr4::ParserRuleContext
    {
      public:
        AccessModifierContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        AccessModifierContext() = default;
        void copyFrom(AccessModifierContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class PrivateContext : public AccessModifierContext
    {
      public:
        PrivateContext(AccessModifierContext* ctx);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class PublicContext : public AccessModifierContext
    {
      public:
        PublicContext(AccessModifierContext* ctx);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class ExternContext : public AccessModifierContext
    {
      public:
        ExternContext(AccessModifierContext* ctx);

        virtual std::any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    AccessModifierContext* accessModifier();

    // By default the static state used to implement the parser is lazily initialized during the first
    // call to the constructor. You can call this function if you wish to initialize the static state
    // ahead of time.
    static void initialize();

  private:
};
