
// Generated from ./src/grammar/ance.g4 by ANTLR 4.9.3

#pragma once

#include "antlr4-runtime.h"
#include "anceVisitor.h"

/**
 * This class provides an empty implementation of anceVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class anceBaseVisitor : public anceVisitor
{
  public:
    virtual antlrcpp::Any visitFile(anceParser::FileContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitVariableDeclaration(anceParser::VariableDeclarationContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFunctionDefinition(anceParser::FunctionDefinitionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitExternFunctionDeclaration(anceParser::ExternFunctionDeclarationContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitParameters(anceParser::ParametersContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitParameter(anceParser::ParameterContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitTypeDefinition(anceParser::TypeDefinitionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitDefineAs(anceParser::DefineAsContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitDefineAlias(anceParser::DefineAliasContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitPublic(anceParser::PublicContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitPrivate(anceParser::PrivateContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitCode(anceParser::CodeContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitBlock(anceParser::BlockContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitStatement(anceParser::StatementContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitExpressionStatement(anceParser::ExpressionStatementContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitLocalReferenceToValueDefinition(
        anceParser::LocalReferenceToValueDefinitionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitLocalReferenceToPointerDefinition(
        anceParser::LocalReferenceToPointerDefinitionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitDropStatement(anceParser::DropStatementContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAssignment(anceParser::AssignmentContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitCopyAssignment(anceParser::CopyAssignmentContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitMoveAssignment(anceParser::MoveAssignmentContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFinalCopyAssignment(anceParser::FinalCopyAssignmentContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitDeleteStatement(anceParser::DeleteStatementContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitReturnStatement(anceParser::ReturnStatementContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAssertStatement(anceParser::AssertStatementContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitIfStatement(anceParser::IfStatementContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitWhileStatement(anceParser::WhileStatementContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitMatchStatement(anceParser::MatchStatementContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitLiteralCase(anceParser::LiteralCaseContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitDefaultCase(anceParser::DefaultCaseContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitIfExpression(anceParser::IfExpressionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitVariable(anceParser::VariableContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitAdressOf(anceParser::AdressOfContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitBinaryOperation(anceParser::BinaryOperationContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitNotOperation(anceParser::NotOperationContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitSubscript(anceParser::SubscriptContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitLogicalOr(anceParser::LogicalOrContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitMatch(anceParser::MatchContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitRef(anceParser::RefContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitIndependent(anceParser::IndependentContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitParenthesis(anceParser::ParenthesisContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitAlloc(anceParser::AllocContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitLiteral(anceParser::LiteralContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitLogicalAnd(anceParser::LogicalAndContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitSizeOf(anceParser::SizeOfContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitMultiplication(anceParser::MultiplicationContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitDivision(anceParser::DivisionContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitRemainder(anceParser::RemainderContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitAddition(anceParser::AdditionContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitSubtraction(anceParser::SubtractionContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitLessThan(anceParser::LessThanContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitLessThanOrEqual(anceParser::LessThanOrEqualContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitGreaterThan(anceParser::GreaterThanContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitGreaterThanOrEqual(anceParser::GreaterThanOrEqualContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitEqual(anceParser::EqualContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitNotEqual(anceParser::NotEqualContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitIndependentExpression(anceParser::IndependentExpressionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFunctionCall(anceParser::FunctionCallContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitArguments(anceParser::ArgumentsContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitVariableAccess(anceParser::VariableAccessContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAllocation(anceParser::AllocationContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitDynamic(anceParser::DynamicContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitAutomatic(anceParser::AutomaticContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitAddressof(anceParser::AddressofContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitBindReference(anceParser::BindReferenceContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitBindReferenceToAddress(anceParser::BindReferenceToAddressContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitSizeofType(anceParser::SizeofTypeContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitSizeofExpression(anceParser::SizeofExpressionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitMatchExpression(anceParser::MatchExpressionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitLiteralExpressionCase(anceParser::LiteralExpressionCaseContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitDefaultExpressionCase(anceParser::DefaultExpressionCaseContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitLiteralExpression(anceParser::LiteralExpressionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitStringLiteral(anceParser::StringLiteralContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitByteLiteral(anceParser::ByteLiteralContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitIntegerLiteral(anceParser::IntegerLiteralContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitNormalInteger(anceParser::NormalIntegerContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitSpecialInteger(anceParser::SpecialIntegerContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitTrue(anceParser::TrueContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitFalse(anceParser::FalseContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitSizeLiteral(anceParser::SizeLiteralContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitDiffLiteral(anceParser::DiffLiteralContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitInteger(anceParser::IntegerContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitArray(anceParser::ArrayContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitKeyword(anceParser::KeywordContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitPointer(anceParser::PointerContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitReference(anceParser::ReferenceContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitCustom(anceParser::CustomContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitIntegerType(anceParser::IntegerTypeContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitArrayType(anceParser::ArrayTypeContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitKeywordType(anceParser::KeywordTypeContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitFloatingPointType(anceParser::FloatingPointTypeContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitTargetDependentType(anceParser::TargetDependentTypeContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitBooleanType(anceParser::BooleanTypeContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitVoidType(anceParser::VoidTypeContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitCustomType(anceParser::CustomTypeContext* ctx) override { return visitChildren(ctx); }
};

