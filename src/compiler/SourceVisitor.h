#ifndef ANCE_SRC_COMPILER_SOURCEVISITOR_H_
#define ANCE_SRC_COMPILER_SOURCEVISITOR_H_

#include "grammar/anceBaseVisitor.h"

#include "ance/utility/Location.h"

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

    // Statements

    antlrcpp::Any visitExpressionStatement(anceParser::ExpressionStatementContext* ctx) override;
    antlrcpp::Any visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx) override;
    antlrcpp::Any visitAssignment(anceParser::AssignmentContext* ctx) override;
    antlrcpp::Any visitDeleteStatement(anceParser::DeleteStatementContext* ctx) override;
    antlrcpp::Any visitReturnStatement(anceParser::ReturnStatementContext* ctx) override;

    // Assignables

    antlrcpp::Any visitVariableAssignable(anceParser::VariableAssignableContext* ctx) override;
    antlrcpp::Any visitIndexerSet(anceParser::IndexerSetContext* ctx) override;
    antlrcpp::Any visitDiscard(anceParser::DiscardContext* ctx) override;

    // Expressions

    antlrcpp::Any visitFunctionCall(anceParser::FunctionCallContext* ctx) override;
    antlrcpp::Any visitArguments(anceParser::ArgumentsContext* ctx) override;
    antlrcpp::Any visitVariableAccess(anceParser::VariableAccessContext* ctx) override;
    antlrcpp::Any visitAllocation(anceParser::AllocationContext* ctx) override;
    antlrcpp::Any visitRoughCast(anceParser::RoughCastContext* ctx) override;
    antlrcpp::Any visitSizeofType(anceParser::SizeofTypeContext* ctx) override;
    antlrcpp::Any visitSizeofExpression(anceParser::SizeofExpressionContext* ctx) override;
    antlrcpp::Any visitIndexerGet(anceParser::IndexerGetContext* ctx) override;

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
    antlrcpp::Any visitArrayType(anceParser::ArrayTypeContext* ctx) override;
    antlrcpp::Any visitKeywordType(anceParser::KeywordTypeContext* ctx) override;
    antlrcpp::Any visitPointer(anceParser::PointerContext* ctx) override;

    // Other

    antlrcpp::Any visitPublic(anceParser::PublicContext* ctx) override;
    antlrcpp::Any visitPrivate(anceParser::PrivateContext* ctx) override;
    antlrcpp::Any visitAutomatic(anceParser::AutomaticContext* ctx) override;
    antlrcpp::Any visitDynamic(anceParser::DynamicContext* ctx) override;
    antlrcpp::Any visitCopyAssignment(anceParser::CopyAssignmentContext* ctx) override;
    antlrcpp::Any visitMoveAssignment(anceParser::MoveAssignmentContext* ctx) override;
    antlrcpp::Any visitFinalCopyAssignment(anceParser::FinalCopyAssignmentContext* ctx) override;

  protected:
    static ance::Location location(antlr4::ParserRuleContext* ctx);

  private:
    Application& application_;
};

#endif