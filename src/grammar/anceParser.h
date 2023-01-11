
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  anceParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, T__24 = 25, T__25 = 26, 
    T__26 = 27, T__27 = 28, T__28 = 29, T__29 = 30, T__30 = 31, T__31 = 32, 
    T__32 = 33, T__33 = 34, T__34 = 35, T__35 = 36, T__36 = 37, T__37 = 38, 
    T__38 = 39, T__39 = 40, T__40 = 41, T__41 = 42, T__42 = 43, T__43 = 44, 
    T__44 = 45, T__45 = 46, T__46 = 47, T__47 = 48, T__48 = 49, T__49 = 50, 
    T__50 = 51, T__51 = 52, T__52 = 53, T__53 = 54, T__54 = 55, T__55 = 56, 
    T__56 = 57, T__57 = 58, T__58 = 59, T__59 = 60, T__60 = 61, T__61 = 62, 
    T__62 = 63, T__63 = 64, T__64 = 65, T__65 = 66, T__66 = 67, T__67 = 68, 
    T__68 = 69, T__69 = 70, T__70 = 71, T__71 = 72, T__72 = 73, T__73 = 74, 
    T__74 = 75, T__75 = 76, T__76 = 77, NATIVE_INTEGER_TYPE = 78, SIGNED_INTEGER = 79, 
    HEX_INTEGER = 80, BIN_INTEGER = 81, OCT_INTEGER = 82, HALF = 83, SINGLE = 84, 
    DOUBLE = 85, QUAD = 86, DECIMAL = 87, STRING = 88, CHAR = 89, INTEGER = 90, 
    BUFFER = 91, CONST = 92, NOT = 93, IDENTIFIER = 94, SEMICOLON = 95, 
    WHITESPACE = 96, BLOCK_COMMENT = 97, LINE_COMMENT = 98, ERROR_CHAR = 99
  };

  enum {
    RuleFile = 0, RuleProjectFile = 1, RuleVariableDeclaration = 2, RuleFunction = 3, 
    RuleParameters = 4, RuleParameter = 5, RuleTypeDefinition = 6, RuleDefineAlias = 7, 
    RuleStructDefinition = 8, RuleMember = 9, RuleAccessModifier = 10, RuleCode = 11, 
    RuleBlock = 12, RuleStatement = 13, RuleExpressionStatement = 14, RuleLocalVariableDefinition = 15, 
    RuleLocalReferenceDefinition = 16, RuleDropStatement = 17, RuleAssignment = 18, 
    RuleAssigner = 19, RuleDeleteStatement = 20, RuleBreakStatement = 21, 
    RuleContinueStatement = 22, RuleReturnStatement = 23, RuleAssertStatement = 24, 
    RuleIfStatement = 25, RuleWhileStatement = 26, RuleMatchStatement = 27, 
    RuleMatchCase = 28, RuleExpression = 29, RuleUnaryOperator = 30, RuleBinaryOperatorMultiplicative = 31, 
    RuleBinaryOperatorAdditive = 32, RuleBinaryOperatorBitwise = 33, RuleBinaryOperatorShift = 34, 
    RuleBinaryOperatorRelational = 35, RuleBinaryOperatorEquality = 36, 
    RuleIndependentExpression = 37, RuleFunctionCall = 38, RuleArguments = 39, 
    RuleVariableAccess = 40, RuleAllocation = 41, RuleAllocator = 42, RuleAddressof = 43, 
    RuleBindRef = 44, RuleSizeofType = 45, RuleSizeofExpression = 46, RuleMatchExpression = 47, 
    RuleMatchExpressionCase = 48, RuleLiteralExpression = 49, RuleStringLiteral = 50, 
    RuleCharLiteral = 51, RuleIntegerLiteral = 52, RuleNormalInteger = 53, 
    RuleSpecialInteger = 54, RuleFloatingPointLiteral = 55, RuleBooleanLiteral = 56, 
    RuleNullLiteral = 57, RuleSizeLiteral = 58, RuleDiffLiteral = 59, RuleUiptrLiteral = 60, 
    RuleType = 61, RuleIntegerType = 62, RuleArrayType = 63, RuleVectorType = 64, 
    RuleKeywordType = 65, RuleFloatingPointType = 66, RuleTargetDependentType = 67, 
    RuleBooleanType = 68, RuleCharType = 69, RuleNullPointerType = 70, RuleVoidType = 71, 
    RuleCustomType = 72
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
  class ProjectFileContext;
  class VariableDeclarationContext;
  class FunctionContext;
  class ParametersContext;
  class ParameterContext;
  class TypeDefinitionContext;
  class DefineAliasContext;
  class StructDefinitionContext;
  class MemberContext;
  class AccessModifierContext;
  class CodeContext;
  class BlockContext;
  class StatementContext;
  class ExpressionStatementContext;
  class LocalVariableDefinitionContext;
  class LocalReferenceDefinitionContext;
  class DropStatementContext;
  class AssignmentContext;
  class AssignerContext;
  class DeleteStatementContext;
  class BreakStatementContext;
  class ContinueStatementContext;
  class ReturnStatementContext;
  class AssertStatementContext;
  class IfStatementContext;
  class WhileStatementContext;
  class MatchStatementContext;
  class MatchCaseContext;
  class ExpressionContext;
  class UnaryOperatorContext;
  class BinaryOperatorMultiplicativeContext;
  class BinaryOperatorAdditiveContext;
  class BinaryOperatorBitwiseContext;
  class BinaryOperatorShiftContext;
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
  class MatchExpressionContext;
  class MatchExpressionCaseContext;
  class LiteralExpressionContext;
  class StringLiteralContext;
  class CharLiteralContext;
  class IntegerLiteralContext;
  class NormalIntegerContext;
  class SpecialIntegerContext;
  class FloatingPointLiteralContext;
  class BooleanLiteralContext;
  class NullLiteralContext;
  class SizeLiteralContext;
  class DiffLiteralContext;
  class UiptrLiteralContext;
  class TypeContext;
  class IntegerTypeContext;
  class ArrayTypeContext;
  class VectorTypeContext;
  class KeywordTypeContext;
  class FloatingPointTypeContext;
  class TargetDependentTypeContext;
  class BooleanTypeContext;
  class CharTypeContext;
  class NullPointerTypeContext;
  class VoidTypeContext;
  class CustomTypeContext; 

  class  FileContext : public antlr4::ParserRuleContext {
  public:
    FileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<VariableDeclarationContext *> variableDeclaration();
    VariableDeclarationContext* variableDeclaration(size_t i);
    std::vector<FunctionContext *> function();
    FunctionContext* function(size_t i);
    std::vector<TypeDefinitionContext *> typeDefinition();
    TypeDefinitionContext* typeDefinition(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FileContext* file();

  class  ProjectFileContext : public antlr4::ParserRuleContext {
  public:
    ProjectFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<CodeContext *> code();
    CodeContext* code(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProjectFileContext* projectFile();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AccessModifierContext *accessModifier();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *CONST();
    TypeContext *type();
    AssignerContext *assigner();
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  FunctionContext : public antlr4::ParserRuleContext {
  public:
    FunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    FunctionContext() = default;
    void copyFrom(FunctionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ExternFunctionDeclarationContext : public FunctionContext {
  public:
    ExternFunctionDeclarationContext(FunctionContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    ParametersContext *parameters();
    antlr4::tree::TerminalNode *SEMICOLON();
    TypeContext *type();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionDefinitionContext : public FunctionContext {
  public:
    FunctionDefinitionContext(FunctionContext *ctx);

    AccessModifierContext *accessModifier();
    antlr4::tree::TerminalNode *IDENTIFIER();
    ParametersContext *parameters();
    TypeContext *type();
    std::vector<CodeContext *> code();
    CodeContext* code(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FunctionContext* function();

  class  ParametersContext : public antlr4::ParserRuleContext {
  public:
    ParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParameterContext *> parameter();
    ParameterContext* parameter(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParametersContext* parameters();

  class  ParameterContext : public antlr4::ParserRuleContext {
  public:
    ParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    TypeContext *type();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterContext* parameter();

  class  TypeDefinitionContext : public antlr4::ParserRuleContext {
  public:
    TypeDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DefineAliasContext *defineAlias();
    StructDefinitionContext *structDefinition();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeDefinitionContext* typeDefinition();

  class  DefineAliasContext : public antlr4::ParserRuleContext {
  public:
    DefineAliasContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AccessModifierContext *accessModifier();
    antlr4::tree::TerminalNode *IDENTIFIER();
    TypeContext *type();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DefineAliasContext* defineAlias();

  class  StructDefinitionContext : public antlr4::ParserRuleContext {
  public:
    StructDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AccessModifierContext *accessModifier();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<MemberContext *> member();
    MemberContext* member(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDefinitionContext* structDefinition();

  class  MemberContext : public antlr4::ParserRuleContext {
  public:
    MemberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AccessModifierContext *accessModifier();
    antlr4::tree::TerminalNode *IDENTIFIER();
    TypeContext *type();
    antlr4::tree::TerminalNode *SEMICOLON();
    AssignerContext *assigner();
    LiteralExpressionContext *literalExpression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MemberContext* member();

  class  AccessModifierContext : public antlr4::ParserRuleContext {
  public:
    AccessModifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AccessModifierContext() = default;
    void copyFrom(AccessModifierContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PrivateContext : public AccessModifierContext {
  public:
    PrivateContext(AccessModifierContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PublicContext : public AccessModifierContext {
  public:
    PublicContext(AccessModifierContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExternContext : public AccessModifierContext {
  public:
    ExternContext(AccessModifierContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AccessModifierContext* accessModifier();

  class  CodeContext : public antlr4::ParserRuleContext {
  public:
    CodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementContext *statement();
    BlockContext *block();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CodeContext* code();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CodeContext *> code();
    CodeContext* code(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionStatementContext *expressionStatement();
    LocalVariableDefinitionContext *localVariableDefinition();
    LocalReferenceDefinitionContext *localReferenceDefinition();
    DropStatementContext *dropStatement();
    AssignmentContext *assignment();
    DeleteStatementContext *deleteStatement();
    BreakStatementContext *breakStatement();
    ContinueStatementContext *continueStatement();
    ReturnStatementContext *returnStatement();
    AssertStatementContext *assertStatement();
    IfStatementContext *ifStatement();
    WhileStatementContext *whileStatement();
    MatchStatementContext *matchStatement();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  ExpressionStatementContext : public antlr4::ParserRuleContext {
  public:
    ExpressionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IndependentExpressionContext *independentExpression();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionStatementContext* expressionStatement();

  class  LocalVariableDefinitionContext : public antlr4::ParserRuleContext {
  public:
    LocalVariableDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();
    TypeContext *type();
    AssignerContext *assigner();
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocalVariableDefinitionContext* localVariableDefinition();

  class  LocalReferenceDefinitionContext : public antlr4::ParserRuleContext {
  public:
    LocalReferenceDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    TypeContext *type();
    BindRefContext *bindRef();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LocalReferenceDefinitionContext* localReferenceDefinition();

  class  DropStatementContext : public antlr4::ParserRuleContext {
  public:
    DropStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DropStatementContext* dropStatement();

  class  AssignmentContext : public antlr4::ParserRuleContext {
  public:
    anceParser::ExpressionContext *assignable = nullptr;
    anceParser::ExpressionContext *assigned = nullptr;
    AssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AssignerContext *assigner();
    antlr4::tree::TerminalNode *SEMICOLON();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentContext* assignment();

  class  AssignerContext : public antlr4::ParserRuleContext {
  public:
    AssignerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AssignerContext() = default;
    void copyFrom(AssignerContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MoveAssignmentContext : public AssignerContext {
  public:
    MoveAssignmentContext(AssignerContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FinalCopyAssignmentContext : public AssignerContext {
  public:
    FinalCopyAssignmentContext(AssignerContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CopyAssignmentContext : public AssignerContext {
  public:
    CopyAssignmentContext(AssignerContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AssignerContext* assigner();

  class  DeleteStatementContext : public antlr4::ParserRuleContext {
  public:
    DeleteStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *BUFFER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeleteStatementContext* deleteStatement();

  class  BreakStatementContext : public antlr4::ParserRuleContext {
  public:
    BreakStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BreakStatementContext* breakStatement();

  class  ContinueStatementContext : public antlr4::ParserRuleContext {
  public:
    ContinueStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ContinueStatementContext* continueStatement();

  class  ReturnStatementContext : public antlr4::ParserRuleContext {
  public:
    ReturnStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMICOLON();
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturnStatementContext* returnStatement();

  class  AssertStatementContext : public antlr4::ParserRuleContext {
  public:
    AssertStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMICOLON();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssertStatementContext* assertStatement();

  class  IfStatementContext : public antlr4::ParserRuleContext {
  public:
    anceParser::CodeContext *ifBlock = nullptr;
    anceParser::CodeContext *elseBlock = nullptr;
    IfStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    std::vector<CodeContext *> code();
    CodeContext* code(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfStatementContext* ifStatement();

  class  WhileStatementContext : public antlr4::ParserRuleContext {
  public:
    WhileStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    CodeContext *code();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhileStatementContext* whileStatement();

  class  MatchStatementContext : public antlr4::ParserRuleContext {
  public:
    MatchStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    std::vector<MatchCaseContext *> matchCase();
    MatchCaseContext* matchCase(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MatchStatementContext* matchStatement();

  class  MatchCaseContext : public antlr4::ParserRuleContext {
  public:
    MatchCaseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    MatchCaseContext() = default;
    void copyFrom(MatchCaseContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LiteralCaseContext : public MatchCaseContext {
  public:
    LiteralCaseContext(MatchCaseContext *ctx);

    std::vector<LiteralExpressionContext *> literalExpression();
    LiteralExpressionContext* literalExpression(size_t i);
    CodeContext *code();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DefaultCaseContext : public MatchCaseContext {
  public:
    DefaultCaseContext(MatchCaseContext *ctx);

    CodeContext *code();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  MatchCaseContext* matchCase();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExpressionContext() = default;
    void copyFrom(ExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IfExpressionContext : public ExpressionContext {
  public:
    IfExpressionContext(ExpressionContext *ctx);

    anceParser::ExpressionContext *condition = nullptr;
    anceParser::ExpressionContext *thenBlock = nullptr;
    anceParser::ExpressionContext *elseBlock = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VariableContext : public ExpressionContext {
  public:
    VariableContext(ExpressionContext *ctx);

    VariableAccessContext *variableAccess();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UnaryOperationContext : public ExpressionContext {
  public:
    UnaryOperationContext(ExpressionContext *ctx);

    UnaryOperatorContext *unaryOperator();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BinaryOperationContext : public ExpressionContext {
  public:
    BinaryOperationContext(ExpressionContext *ctx);

    anceParser::ExpressionContext *left = nullptr;
    anceParser::ExpressionContext *right = nullptr;
    BinaryOperatorMultiplicativeContext *binaryOperatorMultiplicative();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    BinaryOperatorAdditiveContext *binaryOperatorAdditive();
    BinaryOperatorBitwiseContext *binaryOperatorBitwise();
    BinaryOperatorShiftContext *binaryOperatorShift();
    BinaryOperatorRelationalContext *binaryOperatorRelational();
    BinaryOperatorEqualityContext *binaryOperatorEquality();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SubscriptContext : public ExpressionContext {
  public:
    SubscriptContext(ExpressionContext *ctx);

    anceParser::ExpressionContext *indexed = nullptr;
    anceParser::ExpressionContext *index = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LogicalOrContext : public ExpressionContext {
  public:
    LogicalOrContext(ExpressionContext *ctx);

    anceParser::ExpressionContext *left = nullptr;
    anceParser::ExpressionContext *right = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *NOT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MatchContext : public ExpressionContext {
  public:
    MatchContext(ExpressionContext *ctx);

    MatchExpressionContext *matchExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RefContext : public ExpressionContext {
  public:
    RefContext(ExpressionContext *ctx);

    BindRefContext *bindRef();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IndependentContext : public ExpressionContext {
  public:
    IndependentContext(ExpressionContext *ctx);

    IndependentExpressionContext *independentExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenthesisContext : public ExpressionContext {
  public:
    ParenthesisContext(ExpressionContext *ctx);

    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AllocContext : public ExpressionContext {
  public:
    AllocContext(ExpressionContext *ctx);

    AllocationContext *allocation();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MemberAccessContext : public ExpressionContext {
  public:
    MemberAccessContext(ExpressionContext *ctx);

    anceParser::ExpressionContext *accessed = nullptr;
    antlr4::tree::TerminalNode *IDENTIFIER();
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralContext : public ExpressionContext {
  public:
    LiteralContext(ExpressionContext *ctx);

    LiteralExpressionContext *literalExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LogicalAndContext : public ExpressionContext {
  public:
    LogicalAndContext(ExpressionContext *ctx);

    anceParser::ExpressionContext *left = nullptr;
    anceParser::ExpressionContext *right = nullptr;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *NOT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VectorDefinitionContext : public ExpressionContext {
  public:
    VectorDefinitionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    TypeContext *type();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AddressOfContext : public ExpressionContext {
  public:
    AddressOfContext(ExpressionContext *ctx);

    AddressofContext *addressof();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayDefinitionContext : public ExpressionContext {
  public:
    ArrayDefinitionContext(ExpressionContext *ctx);

    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    TypeContext *type();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SizeOfContext : public ExpressionContext {
  public:
    SizeOfContext(ExpressionContext *ctx);

    SizeofTypeContext *sizeofType();
    SizeofExpressionContext *sizeofExpression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IndirectionContext : public ExpressionContext {
  public:
    IndirectionContext(ExpressionContext *ctx);

    anceParser::ExpressionContext *value = nullptr;
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  UnaryOperatorContext : public antlr4::ParserRuleContext {
  public:
    UnaryOperatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    UnaryOperatorContext() = default;
    void copyFrom(UnaryOperatorContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NotContext : public UnaryOperatorContext {
  public:
    NotContext(UnaryOperatorContext *ctx);

    antlr4::tree::TerminalNode *NOT();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NegationContext : public UnaryOperatorContext {
  public:
    NegationContext(UnaryOperatorContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BitwiseNotContext : public UnaryOperatorContext {
  public:
    BitwiseNotContext(UnaryOperatorContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  UnaryOperatorContext* unaryOperator();

  class  BinaryOperatorMultiplicativeContext : public antlr4::ParserRuleContext {
  public:
    BinaryOperatorMultiplicativeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BinaryOperatorMultiplicativeContext() = default;
    void copyFrom(BinaryOperatorMultiplicativeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MultiplicationContext : public BinaryOperatorMultiplicativeContext {
  public:
    MultiplicationContext(BinaryOperatorMultiplicativeContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DivisionContext : public BinaryOperatorMultiplicativeContext {
  public:
    DivisionContext(BinaryOperatorMultiplicativeContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RemainderContext : public BinaryOperatorMultiplicativeContext {
  public:
    RemainderContext(BinaryOperatorMultiplicativeContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BinaryOperatorMultiplicativeContext* binaryOperatorMultiplicative();

  class  BinaryOperatorAdditiveContext : public antlr4::ParserRuleContext {
  public:
    BinaryOperatorAdditiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BinaryOperatorAdditiveContext() = default;
    void copyFrom(BinaryOperatorAdditiveContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AdditionContext : public BinaryOperatorAdditiveContext {
  public:
    AdditionContext(BinaryOperatorAdditiveContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SubtractionContext : public BinaryOperatorAdditiveContext {
  public:
    SubtractionContext(BinaryOperatorAdditiveContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BinaryOperatorAdditiveContext* binaryOperatorAdditive();

  class  BinaryOperatorBitwiseContext : public antlr4::ParserRuleContext {
  public:
    BinaryOperatorBitwiseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BinaryOperatorBitwiseContext() = default;
    void copyFrom(BinaryOperatorBitwiseContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BitwiseOrContext : public BinaryOperatorBitwiseContext {
  public:
    BitwiseOrContext(BinaryOperatorBitwiseContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BitwiseXorContext : public BinaryOperatorBitwiseContext {
  public:
    BitwiseXorContext(BinaryOperatorBitwiseContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BitwiseAndContext : public BinaryOperatorBitwiseContext {
  public:
    BitwiseAndContext(BinaryOperatorBitwiseContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BinaryOperatorBitwiseContext* binaryOperatorBitwise();

  class  BinaryOperatorShiftContext : public antlr4::ParserRuleContext {
  public:
    BinaryOperatorShiftContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BinaryOperatorShiftContext() = default;
    void copyFrom(BinaryOperatorShiftContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  RightShiftContext : public BinaryOperatorShiftContext {
  public:
    RightShiftContext(BinaryOperatorShiftContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LeftShiftContext : public BinaryOperatorShiftContext {
  public:
    LeftShiftContext(BinaryOperatorShiftContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BinaryOperatorShiftContext* binaryOperatorShift();

  class  BinaryOperatorRelationalContext : public antlr4::ParserRuleContext {
  public:
    BinaryOperatorRelationalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BinaryOperatorRelationalContext() = default;
    void copyFrom(BinaryOperatorRelationalContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LessThanContext : public BinaryOperatorRelationalContext {
  public:
    LessThanContext(BinaryOperatorRelationalContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LessThanOrEqualContext : public BinaryOperatorRelationalContext {
  public:
    LessThanOrEqualContext(BinaryOperatorRelationalContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GreaterThanContext : public BinaryOperatorRelationalContext {
  public:
    GreaterThanContext(BinaryOperatorRelationalContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GreaterThanOrEqualContext : public BinaryOperatorRelationalContext {
  public:
    GreaterThanOrEqualContext(BinaryOperatorRelationalContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BinaryOperatorRelationalContext* binaryOperatorRelational();

  class  BinaryOperatorEqualityContext : public antlr4::ParserRuleContext {
  public:
    BinaryOperatorEqualityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BinaryOperatorEqualityContext() = default;
    void copyFrom(BinaryOperatorEqualityContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NotEqualContext : public BinaryOperatorEqualityContext {
  public:
    NotEqualContext(BinaryOperatorEqualityContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EqualContext : public BinaryOperatorEqualityContext {
  public:
    EqualContext(BinaryOperatorEqualityContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BinaryOperatorEqualityContext* binaryOperatorEquality();

  class  IndependentExpressionContext : public antlr4::ParserRuleContext {
  public:
    IndependentExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FunctionCallContext *functionCall();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IndependentExpressionContext* independentExpression();

  class  FunctionCallContext : public antlr4::ParserRuleContext {
  public:
    FunctionCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    ArgumentsContext *arguments();
    TypeContext *type();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionCallContext* functionCall();

  class  ArgumentsContext : public antlr4::ParserRuleContext {
  public:
    ArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentsContext* arguments();

  class  VariableAccessContext : public antlr4::ParserRuleContext {
  public:
    VariableAccessContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableAccessContext* variableAccess();

  class  AllocationContext : public antlr4::ParserRuleContext {
  public:
    AllocationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AllocatorContext *allocator();
    TypeContext *type();
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AllocationContext* allocation();

  class  AllocatorContext : public antlr4::ParserRuleContext {
  public:
    AllocatorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AllocatorContext() = default;
    void copyFrom(AllocatorContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  DynamicContext : public AllocatorContext {
  public:
    DynamicContext(AllocatorContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AutomaticContext : public AllocatorContext {
  public:
    AutomaticContext(AllocatorContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AllocatorContext* allocator();

  class  AddressofContext : public antlr4::ParserRuleContext {
  public:
    AddressofContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AddressofContext* addressof();

  class  BindRefContext : public antlr4::ParserRuleContext {
  public:
    BindRefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BindRefContext() = default;
    void copyFrom(BindRefContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  BindReferenceToAddressContext : public BindRefContext {
  public:
    BindReferenceToAddressContext(BindRefContext *ctx);

    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BindReferenceContext : public BindRefContext {
  public:
    BindReferenceContext(BindRefContext *ctx);

    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BindRefContext* bindRef();

  class  SizeofTypeContext : public antlr4::ParserRuleContext {
  public:
    SizeofTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SizeofTypeContext* sizeofType();

  class  SizeofExpressionContext : public antlr4::ParserRuleContext {
  public:
    SizeofExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SizeofExpressionContext* sizeofExpression();

  class  MatchExpressionContext : public antlr4::ParserRuleContext {
  public:
    anceParser::ExpressionContext *condition = nullptr;
    MatchExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    std::vector<MatchExpressionCaseContext *> matchExpressionCase();
    MatchExpressionCaseContext* matchExpressionCase(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MatchExpressionContext* matchExpression();

  class  MatchExpressionCaseContext : public antlr4::ParserRuleContext {
  public:
    MatchExpressionCaseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    MatchExpressionCaseContext() = default;
    void copyFrom(MatchExpressionCaseContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  LiteralExpressionCaseContext : public MatchExpressionCaseContext {
  public:
    LiteralExpressionCaseContext(MatchExpressionCaseContext *ctx);

    std::vector<LiteralExpressionContext *> literalExpression();
    LiteralExpressionContext* literalExpression(size_t i);
    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DefaultExpressionCaseContext : public MatchExpressionCaseContext {
  public:
    DefaultExpressionCaseContext(MatchExpressionCaseContext *ctx);

    ExpressionContext *expression();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  MatchExpressionCaseContext* matchExpressionCase();

  class  LiteralExpressionContext : public antlr4::ParserRuleContext {
  public:
    LiteralExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringLiteralContext *stringLiteral();
    CharLiteralContext *charLiteral();
    IntegerLiteralContext *integerLiteral();
    FloatingPointLiteralContext *floatingPointLiteral();
    BooleanLiteralContext *booleanLiteral();
    NullLiteralContext *nullLiteral();
    SizeLiteralContext *sizeLiteral();
    DiffLiteralContext *diffLiteral();
    UiptrLiteralContext *uiptrLiteral();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralExpressionContext* literalExpression();

  class  StringLiteralContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *prefix = nullptr;
    StringLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *INTEGER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StringLiteralContext* stringLiteral();

  class  CharLiteralContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *prefix = nullptr;
    CharLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CHAR();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *INTEGER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CharLiteralContext* charLiteral();

  class  IntegerLiteralContext : public antlr4::ParserRuleContext {
  public:
    IntegerLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NormalIntegerContext *normalInteger();
    SpecialIntegerContext *specialInteger();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntegerLiteralContext* integerLiteral();

  class  NormalIntegerContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *uvalue = nullptr;
    antlr4::Token *svalue = nullptr;
    antlr4::Token *width = nullptr;
    NormalIntegerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> INTEGER();
    antlr4::tree::TerminalNode* INTEGER(size_t i);
    antlr4::tree::TerminalNode *SIGNED_INTEGER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NormalIntegerContext* normalInteger();

  class  SpecialIntegerContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *width = nullptr;
    SpecialIntegerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HEX_INTEGER();
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *BIN_INTEGER();
    antlr4::tree::TerminalNode *OCT_INTEGER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SpecialIntegerContext* specialInteger();

  class  FloatingPointLiteralContext : public antlr4::ParserRuleContext {
  public:
    FloatingPointLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HALF();
    antlr4::tree::TerminalNode *SINGLE();
    antlr4::tree::TerminalNode *DOUBLE();
    antlr4::tree::TerminalNode *QUAD();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FloatingPointLiteralContext* floatingPointLiteral();

  class  BooleanLiteralContext : public antlr4::ParserRuleContext {
  public:
    BooleanLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    BooleanLiteralContext() = default;
    void copyFrom(BooleanLiteralContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  TrueContext : public BooleanLiteralContext {
  public:
    TrueContext(BooleanLiteralContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FalseContext : public BooleanLiteralContext {
  public:
    FalseContext(BooleanLiteralContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  BooleanLiteralContext* booleanLiteral();

  class  NullLiteralContext : public antlr4::ParserRuleContext {
  public:
    NullLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    NullLiteralContext() = default;
    void copyFrom(NullLiteralContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NullContext : public NullLiteralContext {
  public:
    NullContext(NullLiteralContext *ctx);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  NullLiteralContext* nullLiteral();

  class  SizeLiteralContext : public antlr4::ParserRuleContext {
  public:
    SizeLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SizeLiteralContext* sizeLiteral();

  class  DiffLiteralContext : public antlr4::ParserRuleContext {
  public:
    DiffLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SIGNED_INTEGER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DiffLiteralContext* diffLiteral();

  class  UiptrLiteralContext : public antlr4::ParserRuleContext {
  public:
    UiptrLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HEX_INTEGER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UiptrLiteralContext* uiptrLiteral();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TypeContext() = default;
    void copyFrom(TypeContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IntegerContext : public TypeContext {
  public:
    IntegerContext(TypeContext *ctx);

    IntegerTypeContext *integerType();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ArrayContext : public TypeContext {
  public:
    ArrayContext(TypeContext *ctx);

    ArrayTypeContext *arrayType();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BufferContext : public TypeContext {
  public:
    BufferContext(TypeContext *ctx);

    antlr4::tree::TerminalNode *BUFFER();
    TypeContext *type();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  KeywordContext : public TypeContext {
  public:
    KeywordContext(TypeContext *ctx);

    KeywordTypeContext *keywordType();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ReferenceContext : public TypeContext {
  public:
    ReferenceContext(TypeContext *ctx);

    TypeContext *type();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  PointerContext : public TypeContext {
  public:
    PointerContext(TypeContext *ctx);

    TypeContext *type();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  CustomContext : public TypeContext {
  public:
    CustomContext(TypeContext *ctx);

    CustomTypeContext *customType();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VectorContext : public TypeContext {
  public:
    VectorContext(TypeContext *ctx);

    VectorTypeContext *vectorType();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TypeContext* type();

  class  IntegerTypeContext : public antlr4::ParserRuleContext {
  public:
    IntegerTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NATIVE_INTEGER_TYPE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntegerTypeContext* integerType();

  class  ArrayTypeContext : public antlr4::ParserRuleContext {
  public:
    ArrayTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *INTEGER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayTypeContext* arrayType();

  class  VectorTypeContext : public antlr4::ParserRuleContext {
  public:
    VectorTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeContext *type();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *INTEGER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VectorTypeContext* vectorType();

  class  KeywordTypeContext : public antlr4::ParserRuleContext {
  public:
    KeywordTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FloatingPointTypeContext *floatingPointType();
    TargetDependentTypeContext *targetDependentType();
    BooleanTypeContext *booleanType();
    CharTypeContext *charType();
    NullPointerTypeContext *nullPointerType();
    VoidTypeContext *voidType();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeywordTypeContext* keywordType();

  class  FloatingPointTypeContext : public antlr4::ParserRuleContext {
  public:
    FloatingPointTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FloatingPointTypeContext* floatingPointType();

  class  TargetDependentTypeContext : public antlr4::ParserRuleContext {
  public:
    TargetDependentTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TargetDependentTypeContext* targetDependentType();

  class  BooleanTypeContext : public antlr4::ParserRuleContext {
  public:
    BooleanTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BooleanTypeContext* booleanType();

  class  CharTypeContext : public antlr4::ParserRuleContext {
  public:
    CharTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CharTypeContext* charType();

  class  NullPointerTypeContext : public antlr4::ParserRuleContext {
  public:
    NullPointerTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NullPointerTypeContext* nullPointerType();

  class  VoidTypeContext : public antlr4::ParserRuleContext {
  public:
    VoidTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VoidTypeContext* voidType();

  class  CustomTypeContext : public antlr4::ParserRuleContext {
  public:
    CustomTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CustomTypeContext* customType();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

