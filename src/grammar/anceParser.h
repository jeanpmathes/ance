
// Generated from ./src/grammar/ance.g4 by ANTLR 4.8

#pragma once

#include "antlr4-runtime.h"

class anceParser : public antlr4::Parser
{
  public:
    enum
    {
        T__0                = 1,
        T__1                = 2,
        T__2                = 3,
        T__3                = 4,
        T__4                = 5,
        T__5                = 6,
        T__6                = 7,
        T__7                = 8,
        T__8                = 9,
        T__9                = 10,
        T__10               = 11,
        T__11               = 12,
        T__12               = 13,
        T__13               = 14,
        T__14               = 15,
        T__15               = 16,
        T__16               = 17,
        T__17               = 18,
        T__18               = 19,
        T__19               = 20,
        T__20               = 21,
        T__21               = 22,
        T__22               = 23,
        T__23               = 24,
        T__24               = 25,
        T__25               = 26,
        T__26               = 27,
        T__27               = 28,
        T__28               = 29,
        T__29               = 30,
        T__30               = 31,
        T__31               = 32,
        NATIVE_INTEGER_TYPE = 33,
        SIGNED_INTEGER      = 34,
        HEX_INTEGER         = 35,
        BIN_INTEGER         = 36,
        OCT_INTEGER         = 37,
        HALF                = 38,
        SINGLE              = 39,
        DOUBLE              = 40,
        QUAD                = 41,
        DECIMAL             = 42,
        STRING              = 43,
        BYTE                = 44,
        INTEGER             = 45,
        BUFFER              = 46,
        CONST               = 47,
        IDENTIFIER          = 48,
        SEMICOLON           = 49,
        WHITESPACE          = 50,
        BLOCK_COMMENT       = 51,
        LINE_COMMENT        = 52
    };

    enum
    {
        RuleFile                    = 0,
        RuleVariableDeclaration     = 1,
        RuleFunction                = 2,
        RuleParameters              = 3,
        RuleParameter               = 4,
        RuleAccessModifier          = 5,
        RuleStatement               = 6,
        RuleExpressionStatement     = 7,
        RuleLocalVariableDefinition = 8,
        RuleAssignment              = 9,
        RuleAssigner                = 10,
        RuleDeleteStatement         = 11,
        RuleReturnStatement         = 12,
        RuleAssignable              = 13,
        RuleVariableAssignable      = 14,
        RuleIndexerSet              = 15,
        RuleDiscard                 = 16,
        RuleExpression              = 17,
        RuleIndependentExpression   = 18,
        RuleFunctionCall            = 19,
        RuleArguments               = 20,
        RuleVariableAccess          = 21,
        RuleAllocation              = 22,
        RuleAllocator               = 23,
        RuleRoughCast               = 24,
        RuleSizeofType              = 25,
        RuleSizeofExpression        = 26,
        RuleLiteralExpression       = 27,
        RuleStringLiteral           = 28,
        RuleByteLiteral             = 29,
        RuleIntegerLiteral          = 30,
        RuleUnsignedInteger         = 31,
        RuleSignedInteger           = 32,
        RuleSpecialInteger          = 33,
        RuleFloatingPointLiteral    = 34,
        RuleBooleanLiteral          = 35,
        RuleSizeLiteral             = 36,
        RuleDiffLiteral             = 37,
        RuleType                    = 38,
        RuleIntegerType             = 39,
        RuleArrayType               = 40,
        RuleKeywordType             = 41,
        RuleFloatingPointType       = 42,
        RuleTargetDependentType     = 43,
        RuleVoidType                = 44
    };

    anceParser(antlr4::TokenStream* input);
    ~anceParser();

    virtual std::string                     getGrammarFileName() const override;
    virtual const antlr4::atn::ATN&         getATN() const override { return _atn; };
    virtual const std::vector<std::string>& getTokenNames() const override
    {
        return _tokenNames;
    };// deprecated: use vocabulary instead.
    virtual const std::vector<std::string>& getRuleNames() const override;
    virtual antlr4::dfa::Vocabulary&        getVocabulary() const override;

    class FileContext;
    class VariableDeclarationContext;
    class FunctionContext;
    class ParametersContext;
    class ParameterContext;
    class AccessModifierContext;
    class StatementContext;
    class ExpressionStatementContext;
    class LocalVariableDefinitionContext;
    class AssignmentContext;
    class AssignerContext;
    class DeleteStatementContext;
    class ReturnStatementContext;
    class AssignableContext;
    class VariableAssignableContext;
    class IndexerSetContext;
    class DiscardContext;
    class ExpressionContext;
    class IndependentExpressionContext;
    class FunctionCallContext;
    class ArgumentsContext;
    class VariableAccessContext;
    class AllocationContext;
    class AllocatorContext;
    class RoughCastContext;
    class SizeofTypeContext;
    class SizeofExpressionContext;
    class LiteralExpressionContext;
    class StringLiteralContext;
    class ByteLiteralContext;
    class IntegerLiteralContext;
    class UnsignedIntegerContext;
    class SignedIntegerContext;
    class SpecialIntegerContext;
    class FloatingPointLiteralContext;
    class BooleanLiteralContext;
    class SizeLiteralContext;
    class DiffLiteralContext;
    class TypeContext;
    class IntegerTypeContext;
    class ArrayTypeContext;
    class KeywordTypeContext;
    class FloatingPointTypeContext;
    class TargetDependentTypeContext;
    class VoidTypeContext;

    class FileContext : public antlr4::ParserRuleContext
    {
      public:
        FileContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                           getRuleIndex() const override;
        antlr4::tree::TerminalNode*              EOF();
        std::vector<VariableDeclarationContext*> variableDeclaration();
        VariableDeclarationContext*              variableDeclaration(size_t i);
        std::vector<FunctionContext*>            function();
        FunctionContext*                         function(size_t i);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FileContext* file();

    class VariableDeclarationContext : public antlr4::ParserRuleContext
    {
      public:
        VariableDeclarationContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        AccessModifierContext*      accessModifier();
        TypeContext*                type();
        antlr4::tree::TerminalNode* IDENTIFIER();
        antlr4::tree::TerminalNode* SEMICOLON();
        antlr4::tree::TerminalNode* CONST();
        AssignerContext*            assigner();
        LiteralExpressionContext*   literalExpression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    VariableDeclarationContext* variableDeclaration();

    class FunctionContext : public antlr4::ParserRuleContext
    {
      public:
        FunctionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        FunctionContext() = default;
        void copyFrom(FunctionContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class ExternFunctionDeclarationContext : public FunctionContext
    {
      public:
        ExternFunctionDeclarationContext(FunctionContext* ctx);

        TypeContext*                type();
        antlr4::tree::TerminalNode* IDENTIFIER();
        ParametersContext*          parameters();
        antlr4::tree::TerminalNode* SEMICOLON();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FunctionDefinitionContext : public FunctionContext
    {
      public:
        FunctionDefinitionContext(FunctionContext* ctx);

        AccessModifierContext*         accessModifier();
        TypeContext*                   type();
        antlr4::tree::TerminalNode*    IDENTIFIER();
        ParametersContext*             parameters();
        std::vector<StatementContext*> statement();
        StatementContext*              statement(size_t i);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FunctionContext* function();

    class ParametersContext : public antlr4::ParserRuleContext
    {
      public:
        ParametersContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                 getRuleIndex() const override;
        std::vector<ParameterContext*> parameter();
        ParameterContext*              parameter(size_t i);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ParametersContext* parameters();

    class ParameterContext : public antlr4::ParserRuleContext
    {
      public:
        ParameterContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        TypeContext*                type();
        antlr4::tree::TerminalNode* IDENTIFIER();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ParameterContext* parameter();

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

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class PublicContext : public AccessModifierContext
    {
      public:
        PublicContext(AccessModifierContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    AccessModifierContext* accessModifier();

    class StatementContext : public antlr4::ParserRuleContext
    {
      public:
        StatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                  getRuleIndex() const override;
        ExpressionStatementContext*     expressionStatement();
        LocalVariableDefinitionContext* localVariableDefinition();
        AssignmentContext*              assignment();
        DeleteStatementContext*         deleteStatement();
        ReturnStatementContext*         returnStatement();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    StatementContext* statement();

    class ExpressionStatementContext : public antlr4::ParserRuleContext
    {
      public:
        ExpressionStatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                getRuleIndex() const override;
        IndependentExpressionContext* independentExpression();
        antlr4::tree::TerminalNode*   SEMICOLON();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ExpressionStatementContext* expressionStatement();

    class LocalVariableDefinitionContext : public antlr4::ParserRuleContext
    {
      public:
        LocalVariableDefinitionContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        TypeContext*                type();
        antlr4::tree::TerminalNode* IDENTIFIER();
        antlr4::tree::TerminalNode* SEMICOLON();
        AssignerContext*            assigner();
        ExpressionContext*          expression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    LocalVariableDefinitionContext* localVariableDefinition();

    class AssignmentContext : public antlr4::ParserRuleContext
    {
      public:
        AssignmentContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        AssignableContext*          assignable();
        AssignerContext*            assigner();
        ExpressionContext*          expression();
        antlr4::tree::TerminalNode* SEMICOLON();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    AssignmentContext* assignment();

    class AssignerContext : public antlr4::ParserRuleContext
    {
      public:
        AssignerContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        AssignerContext() = default;
        void copyFrom(AssignerContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class MoveAssignmentContext : public AssignerContext
    {
      public:
        MoveAssignmentContext(AssignerContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FinalCopyAssignmentContext : public AssignerContext
    {
      public:
        FinalCopyAssignmentContext(AssignerContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class CopyAssignmentContext : public AssignerContext
    {
      public:
        CopyAssignmentContext(AssignerContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    AssignerContext* assigner();

    class DeleteStatementContext : public antlr4::ParserRuleContext
    {
      public:
        DeleteStatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        ExpressionContext*          expression();
        antlr4::tree::TerminalNode* SEMICOLON();
        antlr4::tree::TerminalNode* BUFFER();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    DeleteStatementContext* deleteStatement();

    class ReturnStatementContext : public antlr4::ParserRuleContext
    {
      public:
        ReturnStatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* SEMICOLON();
        ExpressionContext*          expression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ReturnStatementContext* returnStatement();

    class AssignableContext : public antlr4::ParserRuleContext
    {
      public:
        AssignableContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t             getRuleIndex() const override;
        VariableAssignableContext* variableAssignable();
        IndexerSetContext*         indexerSet();
        DiscardContext*            discard();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    AssignableContext* assignable();

    class VariableAssignableContext : public antlr4::ParserRuleContext
    {
      public:
        VariableAssignableContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* IDENTIFIER();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    VariableAssignableContext* variableAssignable();

    class IndexerSetContext : public antlr4::ParserRuleContext
    {
      public:
        anceParser::ExpressionContext* indexed = nullptr;
        ;
        anceParser::ExpressionContext* index = nullptr;
        ;
        IndexerSetContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                  getRuleIndex() const override;
        std::vector<ExpressionContext*> expression();
        ExpressionContext*              expression(size_t i);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    IndexerSetContext* indexerSet();

    class DiscardContext : public antlr4::ParserRuleContext
    {
      public:
        DiscardContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    DiscardContext* discard();

    class ExpressionContext : public antlr4::ParserRuleContext
    {
      public:
        ExpressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        ExpressionContext() = default;
        void copyFrom(ExpressionContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class CastContext : public ExpressionContext
    {
      public:
        CastContext(ExpressionContext* ctx);

        RoughCastContext* roughCast();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class IndependentContext : public ExpressionContext
    {
      public:
        IndependentContext(ExpressionContext* ctx);

        IndependentExpressionContext* independentExpression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class VariableContext : public ExpressionContext
    {
      public:
        VariableContext(ExpressionContext* ctx);

        VariableAccessContext* variableAccess();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class AllocContext : public ExpressionContext
    {
      public:
        AllocContext(ExpressionContext* ctx);

        AllocationContext* allocation();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class LiteralContext : public ExpressionContext
    {
      public:
        LiteralContext(ExpressionContext* ctx);

        LiteralExpressionContext* literalExpression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class SizeOfContext : public ExpressionContext
    {
      public:
        SizeOfContext(ExpressionContext* ctx);

        SizeofTypeContext*       sizeofType();
        SizeofExpressionContext* sizeofExpression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class IndexerGetContext : public ExpressionContext
    {
      public:
        IndexerGetContext(ExpressionContext* ctx);

        anceParser::ExpressionContext*  indexed = nullptr;
        anceParser::ExpressionContext*  index   = nullptr;
        std::vector<ExpressionContext*> expression();
        ExpressionContext*              expression(size_t i);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ExpressionContext* expression();
    ExpressionContext* expression(int precedence);
    class IndependentExpressionContext : public antlr4::ParserRuleContext
    {
      public:
        IndependentExpressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t       getRuleIndex() const override;
        FunctionCallContext* functionCall();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    IndependentExpressionContext* independentExpression();

    class FunctionCallContext : public antlr4::ParserRuleContext
    {
      public:
        FunctionCallContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* IDENTIFIER();
        ArgumentsContext*           arguments();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FunctionCallContext* functionCall();

    class ArgumentsContext : public antlr4::ParserRuleContext
    {
      public:
        ArgumentsContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                  getRuleIndex() const override;
        std::vector<ExpressionContext*> expression();
        ExpressionContext*              expression(size_t i);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ArgumentsContext* arguments();

    class VariableAccessContext : public antlr4::ParserRuleContext
    {
      public:
        VariableAccessContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* IDENTIFIER();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    VariableAccessContext* variableAccess();

    class AllocationContext : public antlr4::ParserRuleContext
    {
      public:
        AllocationContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t     getRuleIndex() const override;
        AllocatorContext*  allocator();
        TypeContext*       type();
        ExpressionContext* expression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    AllocationContext* allocation();

    class AllocatorContext : public antlr4::ParserRuleContext
    {
      public:
        AllocatorContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        AllocatorContext() = default;
        void copyFrom(AllocatorContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class DynamicContext : public AllocatorContext
    {
      public:
        DynamicContext(AllocatorContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class AutomaticContext : public AllocatorContext
    {
      public:
        AutomaticContext(AllocatorContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    AllocatorContext* allocator();

    class RoughCastContext : public antlr4::ParserRuleContext
    {
      public:
        RoughCastContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t     getRuleIndex() const override;
        TypeContext*       type();
        ExpressionContext* expression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    RoughCastContext* roughCast();

    class SizeofTypeContext : public antlr4::ParserRuleContext
    {
      public:
        SizeofTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;
        TypeContext*   type();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    SizeofTypeContext* sizeofType();

    class SizeofExpressionContext : public antlr4::ParserRuleContext
    {
      public:
        SizeofExpressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t     getRuleIndex() const override;
        ExpressionContext* expression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    SizeofExpressionContext* sizeofExpression();

    class LiteralExpressionContext : public antlr4::ParserRuleContext
    {
      public:
        LiteralExpressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t               getRuleIndex() const override;
        StringLiteralContext*        stringLiteral();
        ByteLiteralContext*          byteLiteral();
        IntegerLiteralContext*       integerLiteral();
        FloatingPointLiteralContext* floatingPointLiteral();
        BooleanLiteralContext*       booleanLiteral();
        SizeLiteralContext*          sizeLiteral();
        DiffLiteralContext*          diffLiteral();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    LiteralExpressionContext* literalExpression();

    class StringLiteralContext : public antlr4::ParserRuleContext
    {
      public:
        antlr4::Token* prefix = nullptr;
        ;
        StringLiteralContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* STRING();
        antlr4::tree::TerminalNode* IDENTIFIER();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    StringLiteralContext* stringLiteral();

    class ByteLiteralContext : public antlr4::ParserRuleContext
    {
      public:
        ByteLiteralContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* BYTE();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ByteLiteralContext* byteLiteral();

    class IntegerLiteralContext : public antlr4::ParserRuleContext
    {
      public:
        IntegerLiteralContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t          getRuleIndex() const override;
        UnsignedIntegerContext* unsignedInteger();
        SignedIntegerContext*   signedInteger();
        SpecialIntegerContext*  specialInteger();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    IntegerLiteralContext* integerLiteral();

    class UnsignedIntegerContext : public antlr4::ParserRuleContext
    {
      public:
        UnsignedIntegerContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                           getRuleIndex() const override;
        std::vector<antlr4::tree::TerminalNode*> INTEGER();
        antlr4::tree::TerminalNode*              INTEGER(size_t i);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    UnsignedIntegerContext* unsignedInteger();

    class SignedIntegerContext : public antlr4::ParserRuleContext
    {
      public:
        SignedIntegerContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* SIGNED_INTEGER();
        antlr4::tree::TerminalNode* INTEGER();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    SignedIntegerContext* signedInteger();

    class SpecialIntegerContext : public antlr4::ParserRuleContext
    {
      public:
        SpecialIntegerContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* HEX_INTEGER();
        antlr4::tree::TerminalNode* INTEGER();
        antlr4::tree::TerminalNode* BIN_INTEGER();
        antlr4::tree::TerminalNode* OCT_INTEGER();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    SpecialIntegerContext* specialInteger();

    class FloatingPointLiteralContext : public antlr4::ParserRuleContext
    {
      public:
        FloatingPointLiteralContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* HALF();
        antlr4::tree::TerminalNode* SINGLE();
        antlr4::tree::TerminalNode* DOUBLE();
        antlr4::tree::TerminalNode* QUAD();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FloatingPointLiteralContext* floatingPointLiteral();

    class BooleanLiteralContext : public antlr4::ParserRuleContext
    {
      public:
        BooleanLiteralContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        BooleanLiteralContext() = default;
        void copyFrom(BooleanLiteralContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class TrueContext : public BooleanLiteralContext
    {
      public:
        TrueContext(BooleanLiteralContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FalseContext : public BooleanLiteralContext
    {
      public:
        FalseContext(BooleanLiteralContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    BooleanLiteralContext* booleanLiteral();

    class SizeLiteralContext : public antlr4::ParserRuleContext
    {
      public:
        SizeLiteralContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* INTEGER();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    SizeLiteralContext* sizeLiteral();

    class DiffLiteralContext : public antlr4::ParserRuleContext
    {
      public:
        DiffLiteralContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* SIGNED_INTEGER();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    DiffLiteralContext* diffLiteral();

    class TypeContext : public antlr4::ParserRuleContext
    {
      public:
        TypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        TypeContext() = default;
        void copyFrom(TypeContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class IntegerContext : public TypeContext
    {
      public:
        IntegerContext(TypeContext* ctx);

        IntegerTypeContext* integerType();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class ArrayContext : public TypeContext
    {
      public:
        ArrayContext(TypeContext* ctx);

        ArrayTypeContext* arrayType();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class KeywordContext : public TypeContext
    {
      public:
        KeywordContext(TypeContext* ctx);

        KeywordTypeContext* keywordType();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class PointerContext : public TypeContext
    {
      public:
        PointerContext(TypeContext* ctx);

        TypeContext* type();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    TypeContext* type();
    TypeContext* type(int precedence);
    class IntegerTypeContext : public antlr4::ParserRuleContext
    {
      public:
        IntegerTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* NATIVE_INTEGER_TYPE();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    IntegerTypeContext* integerType();

    class ArrayTypeContext : public antlr4::ParserRuleContext
    {
      public:
        ArrayTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        TypeContext*                type();
        antlr4::tree::TerminalNode* SEMICOLON();
        antlr4::tree::TerminalNode* INTEGER();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ArrayTypeContext* arrayType();

    class KeywordTypeContext : public antlr4::ParserRuleContext
    {
      public:
        KeywordTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        FloatingPointTypeContext*   floatingPointType();
        TargetDependentTypeContext* targetDependentType();
        VoidTypeContext*            voidType();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    KeywordTypeContext* keywordType();

    class FloatingPointTypeContext : public antlr4::ParserRuleContext
    {
      public:
        FloatingPointTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FloatingPointTypeContext* floatingPointType();

    class TargetDependentTypeContext : public antlr4::ParserRuleContext
    {
      public:
        TargetDependentTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    TargetDependentTypeContext* targetDependentType();

    class VoidTypeContext : public antlr4::ParserRuleContext
    {
      public:
        VoidTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    VoidTypeContext* voidType();

    virtual bool sempred(antlr4::RuleContext* _localctx, size_t ruleIndex, size_t predicateIndex) override;
    bool         expressionSempred(ExpressionContext* _localctx, size_t predicateIndex);
    bool         typeSempred(TypeContext* _localctx, size_t predicateIndex);

  private:
    static std::vector<antlr4::dfa::DFA>       _decisionToDFA;
    static antlr4::atn::PredictionContextCache _sharedContextCache;
    static std::vector<std::string>            _ruleNames;
    static std::vector<std::string>            _tokenNames;

    static std::vector<std::string> _literalNames;
    static std::vector<std::string> _symbolicNames;
    static antlr4::dfa::Vocabulary  _vocabulary;
    static antlr4::atn::ATN         _atn;
    static std::vector<uint16_t>    _serializedATN;

    struct Initializer {
        Initializer();
    };
    static Initializer _init;
};

