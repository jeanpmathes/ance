
// Generated from ./src/grammar/ance.g4 by ANTLR 4.9.3

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
        T__32               = 33,
        T__33               = 34,
        T__34               = 35,
        T__35               = 36,
        T__36               = 37,
        T__37               = 38,
        T__38               = 39,
        T__39               = 40,
        T__40               = 41,
        T__41               = 42,
        T__42               = 43,
        T__43               = 44,
        T__44               = 45,
        T__45               = 46,
        T__46               = 47,
        T__47               = 48,
        T__48               = 49,
        T__49               = 50,
        T__50               = 51,
        T__51               = 52,
        T__52               = 53,
        T__53               = 54,
        T__54               = 55,
        NATIVE_INTEGER_TYPE = 56,
        SIGNED_INTEGER      = 57,
        HEX_INTEGER         = 58,
        BIN_INTEGER         = 59,
        OCT_INTEGER         = 60,
        HALF                = 61,
        SINGLE              = 62,
        DOUBLE              = 63,
        QUAD                = 64,
        DECIMAL             = 65,
        STRING              = 66,
        BYTE                = 67,
        INTEGER             = 68,
        BUFFER              = 69,
        CONST               = 70,
        IDENTIFIER          = 71,
        SEMICOLON           = 72,
        WHITESPACE          = 73,
        BLOCK_COMMENT       = 74,
        LINE_COMMENT        = 75
    };

    enum
    {
        RuleFile                         = 0,
        RuleVariableDeclaration          = 1,
        RuleFunction                     = 2,
        RuleParameters                   = 3,
        RuleParameter                    = 4,
        RuleTypeDefinition               = 5,
        RuleDefineAs                     = 6,
        RuleDefineAlias                  = 7,
        RuleAccessModifier               = 8,
        RuleCode                         = 9,
        RuleBlock                        = 10,
        RuleStatement                    = 11,
        RuleExpressionStatement          = 12,
        RuleLocalVariableDefinition      = 13,
        RuleLocalReferenceDefinition     = 14,
        RuleAssignment                   = 15,
        RuleAssigner                     = 16,
        RuleDeleteStatement              = 17,
        RuleReturnStatement              = 18,
        RuleAssertStatement              = 19,
        RuleIfStatement                  = 20,
        RuleWhileStatement               = 21,
        RuleExpression                   = 22,
        RuleBinaryOperatorMultiplicative = 23,
        RuleBinaryOperatorAdditive       = 24,
        RuleBinaryOperatorRelational     = 25,
        RuleBinaryOperatorEquality       = 26,
        RuleIndependentExpression        = 27,
        RuleFunctionCall                 = 28,
        RuleArguments                    = 29,
        RuleVariableAccess               = 30,
        RuleAllocation                   = 31,
        RuleAllocator                    = 32,
        RuleAddressof                    = 33,
        RuleBindRef                      = 34,
        RuleSizeofType                   = 35,
        RuleSizeofExpression             = 36,
        RuleLiteralExpression            = 37,
        RuleStringLiteral                = 38,
        RuleByteLiteral                  = 39,
        RuleIntegerLiteral               = 40,
        RuleUnsignedInteger              = 41,
        RuleSignedInteger                = 42,
        RuleSpecialInteger               = 43,
        RuleFloatingPointLiteral         = 44,
        RuleBooleanLiteral               = 45,
        RuleSizeLiteral                  = 46,
        RuleDiffLiteral                  = 47,
        RuleType                         = 48,
        RuleIntegerType                  = 49,
        RuleArrayType                    = 50,
        RuleKeywordType                  = 51,
        RuleFloatingPointType            = 52,
        RuleTargetDependentType          = 53,
        RuleVoidType                     = 54,
        RuleCustomType                   = 55
    };

    explicit anceParser(antlr4::TokenStream* input);
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
    class TypeDefinitionContext;
    class DefineAsContext;
    class DefineAliasContext;
    class AccessModifierContext;
    class CodeContext;
    class BlockContext;
    class StatementContext;
    class ExpressionStatementContext;
    class LocalVariableDefinitionContext;
    class LocalReferenceDefinitionContext;
    class AssignmentContext;
    class AssignerContext;
    class DeleteStatementContext;
    class ReturnStatementContext;
    class AssertStatementContext;
    class IfStatementContext;
    class WhileStatementContext;
    class ExpressionContext;
    class BinaryOperatorMultiplicativeContext;
    class BinaryOperatorAdditiveContext;
    class BinaryOperatorRelationalContext;
    class BinaryOperatorEqualityContext;
    class IndependentExpressionContext;
    class FunctionCallContext;
    class ArgumentsContext;
    class VariableAccessContext;
    class AllocationContext;
    class AllocatorContext;
    class AddressofContext;
    class BindRefContext;
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
    class CustomTypeContext;

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
        std::vector<TypeDefinitionContext*>      typeDefinition();
        TypeDefinitionContext*                   typeDefinition(size_t i);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    FileContext* file();

    class VariableDeclarationContext : public antlr4::ParserRuleContext
    {
      public:
        VariableDeclarationContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        AccessModifierContext*      accessModifier();
        antlr4::tree::TerminalNode* IDENTIFIER();
        TypeContext*                type();
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

        antlr4::tree::TerminalNode* IDENTIFIER();
        ParametersContext*          parameters();
        antlr4::tree::TerminalNode* SEMICOLON();
        TypeContext*                type();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class FunctionDefinitionContext : public FunctionContext
    {
      public:
        FunctionDefinitionContext(FunctionContext* ctx);

        AccessModifierContext*      accessModifier();
        antlr4::tree::TerminalNode* IDENTIFIER();
        ParametersContext*          parameters();
        TypeContext*                type();
        std::vector<CodeContext*>   code();
        CodeContext*                code(size_t i);

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
        antlr4::tree::TerminalNode* IDENTIFIER();
        TypeContext*                type();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ParameterContext* parameter();

    class TypeDefinitionContext : public antlr4::ParserRuleContext
    {
      public:
        TypeDefinitionContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t      getRuleIndex() const override;
        DefineAsContext*    defineAs();
        DefineAliasContext* defineAlias();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    TypeDefinitionContext* typeDefinition();

    class DefineAsContext : public antlr4::ParserRuleContext
    {
      public:
        DefineAsContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* IDENTIFIER();
        TypeContext*                type();
        antlr4::tree::TerminalNode* SEMICOLON();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    DefineAsContext* defineAs();

    class DefineAliasContext : public antlr4::ParserRuleContext
    {
      public:
        DefineAliasContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* IDENTIFIER();
        TypeContext*                type();
        antlr4::tree::TerminalNode* SEMICOLON();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    DefineAliasContext* defineAlias();

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

    class CodeContext : public antlr4::ParserRuleContext
    {
      public:
        CodeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t    getRuleIndex() const override;
        StatementContext* statement();
        BlockContext*     block();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    CodeContext* code();

    class BlockContext : public antlr4::ParserRuleContext
    {
      public:
        BlockContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t            getRuleIndex() const override;
        std::vector<CodeContext*> code();
        CodeContext*              code(size_t i);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    BlockContext* block();

    class StatementContext : public antlr4::ParserRuleContext
    {
      public:
        StatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                   getRuleIndex() const override;
        ExpressionStatementContext*      expressionStatement();
        LocalVariableDefinitionContext*  localVariableDefinition();
        LocalReferenceDefinitionContext* localReferenceDefinition();
        AssignmentContext*               assignment();
        DeleteStatementContext*          deleteStatement();
        ReturnStatementContext*          returnStatement();
        AssertStatementContext*          assertStatement();
        IfStatementContext*              ifStatement();
        WhileStatementContext*           whileStatement();

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
        antlr4::tree::TerminalNode* IDENTIFIER();
        TypeContext*                type();
        antlr4::tree::TerminalNode* SEMICOLON();
        AssignerContext*            assigner();
        ExpressionContext*          expression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    LocalVariableDefinitionContext* localVariableDefinition();

    class LocalReferenceDefinitionContext : public antlr4::ParserRuleContext
    {
      public:
        LocalReferenceDefinitionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        LocalReferenceDefinitionContext() = default;
        void copyFrom(LocalReferenceDefinitionContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class LocalReferenceToValueDefinitionContext : public LocalReferenceDefinitionContext
    {
      public:
        LocalReferenceToValueDefinitionContext(LocalReferenceDefinitionContext* ctx);

        antlr4::tree::TerminalNode* IDENTIFIER();
        TypeContext*                type();
        ExpressionContext*          expression();
        antlr4::tree::TerminalNode* SEMICOLON();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class LocalReferenceToPointerDefinitionContext : public LocalReferenceDefinitionContext
    {
      public:
        LocalReferenceToPointerDefinitionContext(LocalReferenceDefinitionContext* ctx);

        antlr4::tree::TerminalNode* IDENTIFIER();
        TypeContext*                type();
        ExpressionContext*          expression();
        antlr4::tree::TerminalNode* SEMICOLON();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    LocalReferenceDefinitionContext* localReferenceDefinition();

    class AssignmentContext : public antlr4::ParserRuleContext
    {
      public:
        anceParser::ExpressionContext* assignable = nullptr;
        anceParser::ExpressionContext* assigned   = nullptr;
        AssignmentContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t                  getRuleIndex() const override;
        AssignerContext*                assigner();
        antlr4::tree::TerminalNode*     SEMICOLON();
        std::vector<ExpressionContext*> expression();
        ExpressionContext*              expression(size_t i);

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

    class AssertStatementContext : public antlr4::ParserRuleContext
    {
      public:
        AssertStatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        ExpressionContext*          expression();
        antlr4::tree::TerminalNode* SEMICOLON();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    AssertStatementContext* assertStatement();

    class IfStatementContext : public antlr4::ParserRuleContext
    {
      public:
        anceParser::CodeContext* ifBlock   = nullptr;
        anceParser::CodeContext* elseBlock = nullptr;
        IfStatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t            getRuleIndex() const override;
        ExpressionContext*        expression();
        std::vector<CodeContext*> code();
        CodeContext*              code(size_t i);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    IfStatementContext* ifStatement();

    class WhileStatementContext : public antlr4::ParserRuleContext
    {
      public:
        WhileStatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t     getRuleIndex() const override;
        ExpressionContext* expression();
        CodeContext*       code();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    WhileStatementContext* whileStatement();

    class ExpressionContext : public antlr4::ParserRuleContext
    {
      public:
        ExpressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        ExpressionContext() = default;
        void copyFrom(ExpressionContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class RefContext : public ExpressionContext
    {
      public:
        RefContext(ExpressionContext* ctx);

        BindRefContext* bindRef();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class IndependentContext : public ExpressionContext
    {
      public:
        IndependentContext(ExpressionContext* ctx);

        IndependentExpressionContext* independentExpression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class ParenthesisContext : public ExpressionContext
    {
      public:
        ParenthesisContext(ExpressionContext* ctx);

        ExpressionContext* expression();

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

    class AdressOfContext : public ExpressionContext
    {
      public:
        AdressOfContext(ExpressionContext* ctx);

        AddressofContext* addressof();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class BinaryOperationContext : public ExpressionContext
    {
      public:
        BinaryOperationContext(ExpressionContext* ctx);

        anceParser::ExpressionContext*       left  = nullptr;
        anceParser::ExpressionContext*       right = nullptr;
        BinaryOperatorMultiplicativeContext* binaryOperatorMultiplicative();
        std::vector<ExpressionContext*>      expression();
        ExpressionContext*                   expression(size_t i);
        BinaryOperatorAdditiveContext*       binaryOperatorAdditive();
        BinaryOperatorRelationalContext*     binaryOperatorRelational();
        BinaryOperatorEqualityContext*       binaryOperatorEquality();

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

    class SubscriptContext : public ExpressionContext
    {
      public:
        SubscriptContext(ExpressionContext* ctx);

        anceParser::ExpressionContext*  indexed = nullptr;
        anceParser::ExpressionContext*  index   = nullptr;
        std::vector<ExpressionContext*> expression();
        ExpressionContext*              expression(size_t i);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ExpressionContext* expression();
    ExpressionContext* expression(int precedence);
    class BinaryOperatorMultiplicativeContext : public antlr4::ParserRuleContext
    {
      public:
        BinaryOperatorMultiplicativeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        BinaryOperatorMultiplicativeContext() = default;
        void copyFrom(BinaryOperatorMultiplicativeContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class MultiplicationContext : public BinaryOperatorMultiplicativeContext
    {
      public:
        MultiplicationContext(BinaryOperatorMultiplicativeContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class DivisionContext : public BinaryOperatorMultiplicativeContext
    {
      public:
        DivisionContext(BinaryOperatorMultiplicativeContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class RemainderContext : public BinaryOperatorMultiplicativeContext
    {
      public:
        RemainderContext(BinaryOperatorMultiplicativeContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    BinaryOperatorMultiplicativeContext* binaryOperatorMultiplicative();

    class BinaryOperatorAdditiveContext : public antlr4::ParserRuleContext
    {
      public:
        BinaryOperatorAdditiveContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        BinaryOperatorAdditiveContext() = default;
        void copyFrom(BinaryOperatorAdditiveContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class AdditionContext : public BinaryOperatorAdditiveContext
    {
      public:
        AdditionContext(BinaryOperatorAdditiveContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class SubtractionContext : public BinaryOperatorAdditiveContext
    {
      public:
        SubtractionContext(BinaryOperatorAdditiveContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    BinaryOperatorAdditiveContext* binaryOperatorAdditive();

    class BinaryOperatorRelationalContext : public antlr4::ParserRuleContext
    {
      public:
        BinaryOperatorRelationalContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        BinaryOperatorRelationalContext() = default;
        void copyFrom(BinaryOperatorRelationalContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class LessThanContext : public BinaryOperatorRelationalContext
    {
      public:
        LessThanContext(BinaryOperatorRelationalContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class LessThanOrEqualContext : public BinaryOperatorRelationalContext
    {
      public:
        LessThanOrEqualContext(BinaryOperatorRelationalContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class GreaterThanContext : public BinaryOperatorRelationalContext
    {
      public:
        GreaterThanContext(BinaryOperatorRelationalContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class GreaterThanOrEqualContext : public BinaryOperatorRelationalContext
    {
      public:
        GreaterThanOrEqualContext(BinaryOperatorRelationalContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    BinaryOperatorRelationalContext* binaryOperatorRelational();

    class BinaryOperatorEqualityContext : public antlr4::ParserRuleContext
    {
      public:
        BinaryOperatorEqualityContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        BinaryOperatorEqualityContext() = default;
        void copyFrom(BinaryOperatorEqualityContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class NotEqualContext : public BinaryOperatorEqualityContext
    {
      public:
        NotEqualContext(BinaryOperatorEqualityContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class EqualContext : public BinaryOperatorEqualityContext
    {
      public:
        EqualContext(BinaryOperatorEqualityContext* ctx);

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    BinaryOperatorEqualityContext* binaryOperatorEquality();

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

    class AddressofContext : public antlr4::ParserRuleContext
    {
      public:
        AddressofContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t     getRuleIndex() const override;
        ExpressionContext* expression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    AddressofContext* addressof();

    class BindRefContext : public antlr4::ParserRuleContext
    {
      public:
        BindRefContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        BindRefContext() = default;
        void copyFrom(BindRefContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class BindReferenceToAddressContext : public BindRefContext
    {
      public:
        BindReferenceToAddressContext(BindRefContext* ctx);

        ExpressionContext* expression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class BindReferenceContext : public BindRefContext
    {
      public:
        BindReferenceContext(BindRefContext* ctx);

        ExpressionContext* expression();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    BindRefContext* bindRef();

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
        antlr4::Token* value = nullptr;
        antlr4::Token* width = nullptr;
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
        antlr4::Token* value = nullptr;
        antlr4::Token* width = nullptr;
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
        antlr4::Token* width = nullptr;
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

    class ReferenceContext : public TypeContext
    {
      public:
        ReferenceContext(TypeContext* ctx);

        TypeContext* type();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class PointerContext : public TypeContext
    {
      public:
        PointerContext(TypeContext* ctx);

        TypeContext* type();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class CustomContext : public TypeContext
    {
      public:
        CustomContext(TypeContext* ctx);

        CustomTypeContext* customType();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    TypeContext* type();

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

    class CustomTypeContext : public antlr4::ParserRuleContext
    {
      public:
        CustomTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t              getRuleIndex() const override;
        antlr4::tree::TerminalNode* IDENTIFIER();

        virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    CustomTypeContext* customType();

    virtual bool sempred(antlr4::RuleContext* _localctx, size_t ruleIndex, size_t predicateIndex) override;
    bool         expressionSempred(ExpressionContext* _localctx, size_t predicateIndex);

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

