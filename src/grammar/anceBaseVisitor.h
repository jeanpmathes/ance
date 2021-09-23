
// Generated from ./src/grammar/ance.g4 by ANTLR 4.8

#pragma once

#include "anceVisitor.h"
#include "antlr4-runtime.h"

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

    virtual antlrcpp::Any visitPublic(anceParser::PublicContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitPrivate(anceParser::PrivateContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitStatement(anceParser::StatementContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitExpressionStatement(anceParser::ExpressionStatementContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx) override
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

    virtual antlrcpp::Any visitAssignable(anceParser::AssignableContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitVariableAssignable(anceParser::VariableAssignableContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitIndexerSet(anceParser::IndexerSetContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitDiscard(anceParser::DiscardContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitCast(anceParser::CastContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitIndependent(anceParser::IndependentContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitVariable(anceParser::VariableContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitAlloc(anceParser::AllocContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitLiteral(anceParser::LiteralContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitSizeOf(anceParser::SizeOfContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitIndexerGet(anceParser::IndexerGetContext* ctx) override { return visitChildren(ctx); }

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

    virtual antlrcpp::Any visitRoughCast(anceParser::RoughCastContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitSizeofType(anceParser::SizeofTypeContext* ctx) override { return visitChildren(ctx); }

    virtual antlrcpp::Any visitSizeofExpression(anceParser::SizeofExpressionContext* ctx) override
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

    virtual antlrcpp::Any visitUnsignedInteger(anceParser::UnsignedIntegerContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitSignedInteger(anceParser::SignedIntegerContext* ctx) override
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

    virtual antlrcpp::Any visitVoidType(anceParser::VoidTypeContext* ctx) override { return visitChildren(ctx); }
};

