#ifndef ANCE_SRC_COMPILER_SOURCEVISITOR_H_
#define ANCE_SRC_COMPILER_SOURCEVISITOR_H_

#include "grammar/anceBaseVisitor.h"

#include "lang/utility/Location.h"

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

    antlrcpp::Any visitVariableDeclaration(anceParser::VariableDeclarationContext* ctx) override;

    // Functions

    antlrcpp::Any visitFunctionDefinition(anceParser::FunctionDefinitionContext* ctx) override;
    antlrcpp::Any visitExternFunctionDeclaration(anceParser::ExternFunctionDeclarationContext* ctx) override;
    antlrcpp::Any visitParameters(anceParser::ParametersContext* ctx) override;
    antlrcpp::Any visitParameter(anceParser::ParameterContext* ctx) override;
    antlrcpp::Any visitDefineAs(anceParser::DefineAsContext* ctx) override;
    antlrcpp::Any visitDefineAlias(anceParser::DefineAliasContext* ctx) override;

    // Statements

    antlrcpp::Any visitBlock(anceParser::BlockContext* ctx) override;

    antlrcpp::Any visitExpressionStatement(anceParser::ExpressionStatementContext* ctx) override;
    antlrcpp::Any visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx) override;
    antlrcpp::Any visitLocalReferenceToValueDefinition(
        anceParser::LocalReferenceToValueDefinitionContext* ctx) override;
    antlrcpp::Any visitLocalReferenceToPointerDefinition(
        anceParser::LocalReferenceToPointerDefinitionContext* ctx) override;
    antlrcpp::Any visitAssignment(anceParser::AssignmentContext* ctx) override;
    antlrcpp::Any visitDeleteStatement(anceParser::DeleteStatementContext* ctx) override;
    antlrcpp::Any visitReturnStatement(anceParser::ReturnStatementContext* ctx) override;
    antlrcpp::Any visitAssertStatement(anceParser::AssertStatementContext* ctx) override;
    antlrcpp::Any visitIfStatement(anceParser::IfStatementContext* ctx) override;
    antlrcpp::Any visitWhileStatement(anceParser::WhileStatementContext* ctx) override;
    antlrcpp::Any visitMatchStatement(anceParser::MatchStatementContext* ctx) override;
    antlrcpp::Any visitLiteralCase(anceParser::LiteralCaseContext* ctx) override;
    antlrcpp::Any visitDefaultCase(anceParser::DefaultCaseContext* ctx) override;

    // Expressions

    antlrcpp::Any visitFunctionCall(anceParser::FunctionCallContext* ctx) override;
    antlrcpp::Any visitArguments(anceParser::ArgumentsContext* ctx) override;
    antlrcpp::Any visitVariableAccess(anceParser::VariableAccessContext* ctx) override;
    antlrcpp::Any visitAllocation(anceParser::AllocationContext* ctx) override;
    antlrcpp::Any visitAddressof(anceParser::AddressofContext* ctx) override;
    antlrcpp::Any visitBindReference(anceParser::BindReferenceContext* ctx) override;
    antlrcpp::Any visitBindReferenceToAddress(anceParser::BindReferenceToAddressContext* ctx) override;
    antlrcpp::Any visitSizeofType(anceParser::SizeofTypeContext* ctx) override;
    antlrcpp::Any visitSizeofExpression(anceParser::SizeofExpressionContext* ctx) override;
    antlrcpp::Any visitSubscript(anceParser::SubscriptContext* ctx) override;
    antlrcpp::Any visitBinaryOperation(anceParser::BinaryOperationContext* ctx) override;
    antlrcpp::Any visitParenthesis(anceParser::ParenthesisContext* ctx) override;

    // Literals and Types

    antlrcpp::Any visitStringLiteral(anceParser::StringLiteralContext* ctx) override;
    antlrcpp::Any visitByteLiteral(anceParser::ByteLiteralContext* ctx) override;
    antlrcpp::Any visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext* ctx) override;
    antlrcpp::Any visitTrue(anceParser::TrueContext* ctx) override;
    antlrcpp::Any visitFalse(anceParser::FalseContext* ctx) override;
    antlrcpp::Any visitSizeLiteral(anceParser::SizeLiteralContext* ctx) override;
    antlrcpp::Any visitDiffLiteral(anceParser::DiffLiteralContext* ctx) override;
    antlrcpp::Any visitUnsignedInteger(anceParser::UnsignedIntegerContext* ctx) override;
    antlrcpp::Any visitSignedInteger(anceParser::SignedIntegerContext* ctx) override;
    antlrcpp::Any visitSpecialInteger(anceParser::SpecialIntegerContext* ctx) override;
    antlrcpp::Any visitIntegerType(anceParser::IntegerTypeContext* ctx) override;
    antlrcpp::Any visitBooleanType(anceParser::BooleanTypeContext* ctx) override;
    antlrcpp::Any visitArrayType(anceParser::ArrayTypeContext* ctx) override;
    antlrcpp::Any visitKeywordType(anceParser::KeywordTypeContext* ctx) override;
    antlrcpp::Any visitPointer(anceParser::PointerContext* ctx) override;
    antlrcpp::Any visitReference(anceParser::ReferenceContext* ctx) override;
    antlrcpp::Any visitCustom(anceParser::CustomContext* ctx) override;

    // Other

    antlrcpp::Any visitPublic(anceParser::PublicContext* ctx) override;
    antlrcpp::Any visitPrivate(anceParser::PrivateContext* ctx) override;

    antlrcpp::Any visitAutomatic(anceParser::AutomaticContext* ctx) override;
    antlrcpp::Any visitDynamic(anceParser::DynamicContext* ctx) override;

    antlrcpp::Any visitCopyAssignment(anceParser::CopyAssignmentContext* ctx) override;
    antlrcpp::Any visitMoveAssignment(anceParser::MoveAssignmentContext* ctx) override;
    antlrcpp::Any visitFinalCopyAssignment(anceParser::FinalCopyAssignmentContext* ctx) override;

    antlrcpp::Any visitAddition(anceParser::AdditionContext* ctx) override;
    antlrcpp::Any visitSubtraction(anceParser::SubtractionContext* ctx) override;
    antlrcpp::Any visitMultiplication(anceParser::MultiplicationContext* ctx) override;
    antlrcpp::Any visitDivision(anceParser::DivisionContext* ctx) override;
    antlrcpp::Any visitRemainder(anceParser::RemainderContext* ctx) override;
    antlrcpp::Any visitLessThan(anceParser::LessThanContext* ctx) override;
    antlrcpp::Any visitLessThanOrEqual(anceParser::LessThanOrEqualContext* ctx) override;
    antlrcpp::Any visitGreaterThan(anceParser::GreaterThanContext* ctx) override;
    antlrcpp::Any visitGreaterThanOrEqual(anceParser::GreaterThanOrEqualContext* ctx) override;
    antlrcpp::Any visitEqual(anceParser::EqualContext* ctx) override;
    antlrcpp::Any visitNotEqual(anceParser::NotEqualContext* ctx) override;

  protected:
    static lang::Location location(antlr4::ParserRuleContext* ctx);

    static uint64_t parseIntegerTypeSize(const std::string& str);
    static uint64_t parseArrayTypeSize(const std::string& str);

    static uint64_t parseInRange(const std::string& str, uint64_t max);

  private:
    Application& application_;
};

#endif