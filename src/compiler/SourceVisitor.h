#ifndef ANCE_SRC_COMPILER_SOURCEVISITOR_H_
#define ANCE_SRC_COMPILER_SOURCEVISITOR_H_

#include "grammar/anceBaseVisitor.h"

#include "lang/utility/Location.h"
#include "lang/utility/Identifier.h"

class Application;

/**
 * The ance syntax visitor creating the application. Base class is generated.
 */
class SourceVisitor : public anceBaseVisitor
{
  public:
    /**
     * Create a new visitor.
     * @param application The application to fill.
     */
    explicit SourceVisitor(Application& application);

    // Declarations

    std::any visitVariableDeclaration(anceParser::VariableDeclarationContext* ctx) override;
    std::any visitStructDefinition(anceParser::StructDefinitionContext* ctx) override;
    std::any visitMember(anceParser::MemberContext* ctx) override;

    // Functions

    std::any visitFunctionDefinition(anceParser::FunctionDefinitionContext* ctx) override;
    std::any visitExternFunctionDeclaration(anceParser::ExternFunctionDeclarationContext* ctx) override;
    std::any visitParameters(anceParser::ParametersContext* ctx) override;
    std::any visitParameter(anceParser::ParameterContext* ctx) override;
    std::any visitDefineAlias(anceParser::DefineAliasContext* ctx) override;

    // Statements

    std::any visitBlock(anceParser::BlockContext* ctx) override;

    std::any visitExpressionStatement(anceParser::ExpressionStatementContext* ctx) override;
    std::any visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx) override;
    std::any visitLocalReferenceDefinition(anceParser::LocalReferenceDefinitionContext* ctx) override;
    std::any visitDropStatement(anceParser::DropStatementContext* ctx) override;
    std::any visitAssignment(anceParser::AssignmentContext* ctx) override;
    std::any visitDeleteStatement(anceParser::DeleteStatementContext* ctx) override;
    std::any visitReturnStatement(anceParser::ReturnStatementContext* ctx) override;
    std::any visitAssertStatement(anceParser::AssertStatementContext* ctx) override;
    std::any visitIfStatement(anceParser::IfStatementContext* ctx) override;
    std::any visitWhileStatement(anceParser::WhileStatementContext* ctx) override;
    std::any visitMatchStatement(anceParser::MatchStatementContext* ctx) override;
    std::any visitLiteralCase(anceParser::LiteralCaseContext* ctx) override;
    std::any visitDefaultCase(anceParser::DefaultCaseContext* ctx) override;

    // Expressions

    std::any visitMemberAccess(anceParser::MemberAccessContext* ctx) override;
    std::any visitFunctionCall(anceParser::FunctionCallContext* ctx) override;
    std::any visitArguments(anceParser::ArgumentsContext* ctx) override;
    std::any visitVariableAccess(anceParser::VariableAccessContext* ctx) override;
    std::any visitAllocation(anceParser::AllocationContext* ctx) override;
    std::any visitAddressof(anceParser::AddressofContext* ctx) override;
    std::any visitBindReference(anceParser::BindReferenceContext* ctx) override;
    std::any visitBindReferenceToAddress(anceParser::BindReferenceToAddressContext* ctx) override;
    std::any visitSizeofType(anceParser::SizeofTypeContext* ctx) override;
    std::any visitSizeofExpression(anceParser::SizeofExpressionContext* ctx) override;
    std::any visitSubscript(anceParser::SubscriptContext* ctx) override;
    std::any visitBinaryOperation(anceParser::BinaryOperationContext* ctx) override;
    std::any visitParenthesis(anceParser::ParenthesisContext* ctx) override;
    std::any visitNotOperation(anceParser::NotOperationContext* ctx) override;
    std::any visitLogicalAnd(anceParser::LogicalAndContext* ctx) override;
    std::any visitLogicalOr(anceParser::LogicalOrContext* ctx) override;
    std::any visitIfExpression(anceParser::IfExpressionContext* ctx) override;
    std::any visitDefaultExpressionCase(anceParser::DefaultExpressionCaseContext* ctx) override;
    std::any visitLiteralExpressionCase(anceParser::LiteralExpressionCaseContext* ctx) override;
    std::any visitMatchExpression(anceParser::MatchExpressionContext* ctx) override;
    std::any visitIndirection(anceParser::IndirectionContext* ctx) override;
    std::any visitVectorDefinition(anceParser::VectorDefinitionContext* ctx) override;

    // Literals and Types

    std::any visitStringLiteral(anceParser::StringLiteralContext* ctx) override;
    std::any visitByteLiteral(anceParser::ByteLiteralContext* ctx) override;
    std::any visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext* ctx) override;
    std::any visitTrue(anceParser::TrueContext* ctx) override;
    std::any visitFalse(anceParser::FalseContext* ctx) override;
    std::any visitSizeLiteral(anceParser::SizeLiteralContext* ctx) override;
    std::any visitDiffLiteral(anceParser::DiffLiteralContext* ctx) override;
    std::any visitNormalInteger(anceParser::NormalIntegerContext* ctx) override;
    std::any visitSpecialInteger(anceParser::SpecialIntegerContext* ctx) override;
    std::any visitIntegerType(anceParser::IntegerTypeContext* ctx) override;
    std::any visitBooleanType(anceParser::BooleanTypeContext* ctx) override;
    std::any visitArrayType(anceParser::ArrayTypeContext* ctx) override;
    std::any visitVectorType(anceParser::VectorTypeContext* ctx) override;
    std::any visitKeywordType(anceParser::KeywordTypeContext* ctx) override;
    std::any visitPointer(anceParser::PointerContext* ctx) override;
    std::any visitReference(anceParser::ReferenceContext* ctx) override;
    std::any visitCustom(anceParser::CustomContext* ctx) override;

    // Other

    std::any visitPublic(anceParser::PublicContext* ctx) override;
    std::any visitPrivate(anceParser::PrivateContext* ctx) override;

    std::any visitAutomatic(anceParser::AutomaticContext* ctx) override;
    std::any visitDynamic(anceParser::DynamicContext* ctx) override;

    std::any visitCopyAssignment(anceParser::CopyAssignmentContext* ctx) override;
    std::any visitMoveAssignment(anceParser::MoveAssignmentContext* ctx) override;
    std::any visitFinalCopyAssignment(anceParser::FinalCopyAssignmentContext* ctx) override;

    std::any visitAddition(anceParser::AdditionContext* ctx) override;
    std::any visitSubtraction(anceParser::SubtractionContext* ctx) override;
    std::any visitMultiplication(anceParser::MultiplicationContext* ctx) override;
    std::any visitDivision(anceParser::DivisionContext* ctx) override;
    std::any visitRemainder(anceParser::RemainderContext* ctx) override;
    std::any visitLessThan(anceParser::LessThanContext* ctx) override;
    std::any visitLessThanOrEqual(anceParser::LessThanOrEqualContext* ctx) override;
    std::any visitGreaterThan(anceParser::GreaterThanContext* ctx) override;
    std::any visitGreaterThanOrEqual(anceParser::GreaterThanOrEqualContext* ctx) override;
    std::any visitEqual(anceParser::EqualContext* ctx) override;
    std::any visitNotEqual(anceParser::NotEqualContext* ctx) override;

  protected:
    static lang::Location   location(antlr4::ParserRuleContext* ctx);
    static lang::Identifier ident(antlr4::tree::TerminalNode* i);
    static lang::Identifier createIdentifier(const std::string& text, lang::Location location);

    static uint64_t parseIntegerTypeSize(const std::string& str);
    static uint64_t parseCompoundTypeSize(const std::string& str);

    static uint64_t parseInRange(const std::string& str, uint64_t max);

  private:
    Application& application_;
};

#endif