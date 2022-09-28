
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1

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
    virtual std::any visitFile(anceParser::FileContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitVariableDeclaration(anceParser::VariableDeclarationContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitFunctionDefinition(anceParser::FunctionDefinitionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitExternFunctionDeclaration(anceParser::ExternFunctionDeclarationContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitParameters(anceParser::ParametersContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitParameter(anceParser::ParameterContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitTypeDefinition(anceParser::TypeDefinitionContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitDefineAlias(anceParser::DefineAliasContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitStructDefinition(anceParser::StructDefinitionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitMember(anceParser::MemberContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitPublic(anceParser::PublicContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitPrivate(anceParser::PrivateContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitCode(anceParser::CodeContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitBlock(anceParser::BlockContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitStatement(anceParser::StatementContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitExpressionStatement(anceParser::ExpressionStatementContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitLocalReferenceDefinition(anceParser::LocalReferenceDefinitionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitDropStatement(anceParser::DropStatementContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitAssignment(anceParser::AssignmentContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitCopyAssignment(anceParser::CopyAssignmentContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitMoveAssignment(anceParser::MoveAssignmentContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitFinalCopyAssignment(anceParser::FinalCopyAssignmentContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitDeleteStatement(anceParser::DeleteStatementContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitReturnStatement(anceParser::ReturnStatementContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitAssertStatement(anceParser::AssertStatementContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitIfStatement(anceParser::IfStatementContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitWhileStatement(anceParser::WhileStatementContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitMatchStatement(anceParser::MatchStatementContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitLiteralCase(anceParser::LiteralCaseContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitDefaultCase(anceParser::DefaultCaseContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitIfExpression(anceParser::IfExpressionContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitVariable(anceParser::VariableContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitAdressOf(anceParser::AdressOfContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitBinaryOperation(anceParser::BinaryOperationContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitNotOperation(anceParser::NotOperationContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitSubscript(anceParser::SubscriptContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitLogicalOr(anceParser::LogicalOrContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitMatch(anceParser::MatchContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitRef(anceParser::RefContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitIndependent(anceParser::IndependentContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitParenthesis(anceParser::ParenthesisContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitAlloc(anceParser::AllocContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitMemberAccess(anceParser::MemberAccessContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitLiteral(anceParser::LiteralContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitLogicalAnd(anceParser::LogicalAndContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitVectorDefinition(anceParser::VectorDefinitionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitArrayDefinition(anceParser::ArrayDefinitionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitSizeOf(anceParser::SizeOfContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitIndirection(anceParser::IndirectionContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitMultiplication(anceParser::MultiplicationContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitDivision(anceParser::DivisionContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitRemainder(anceParser::RemainderContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitAddition(anceParser::AdditionContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitSubtraction(anceParser::SubtractionContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitLessThan(anceParser::LessThanContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitLessThanOrEqual(anceParser::LessThanOrEqualContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitGreaterThan(anceParser::GreaterThanContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitGreaterThanOrEqual(anceParser::GreaterThanOrEqualContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitEqual(anceParser::EqualContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitNotEqual(anceParser::NotEqualContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitIndependentExpression(anceParser::IndependentExpressionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitFunctionCall(anceParser::FunctionCallContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitArguments(anceParser::ArgumentsContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitVariableAccess(anceParser::VariableAccessContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitAllocation(anceParser::AllocationContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitDynamic(anceParser::DynamicContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitAutomatic(anceParser::AutomaticContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitAddressof(anceParser::AddressofContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitBindReference(anceParser::BindReferenceContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitBindReferenceToAddress(anceParser::BindReferenceToAddressContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitSizeofType(anceParser::SizeofTypeContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitSizeofExpression(anceParser::SizeofExpressionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitMatchExpression(anceParser::MatchExpressionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitLiteralExpressionCase(anceParser::LiteralExpressionCaseContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitDefaultExpressionCase(anceParser::DefaultExpressionCaseContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitLiteralExpression(anceParser::LiteralExpressionContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitStringLiteral(anceParser::StringLiteralContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitByteLiteral(anceParser::ByteLiteralContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitIntegerLiteral(anceParser::IntegerLiteralContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitNormalInteger(anceParser::NormalIntegerContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitSpecialInteger(anceParser::SpecialIntegerContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitTrue(anceParser::TrueContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitFalse(anceParser::FalseContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitNull(anceParser::NullContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitSizeLiteral(anceParser::SizeLiteralContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitDiffLiteral(anceParser::DiffLiteralContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitUiptrLiteral(anceParser::UiptrLiteralContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitInteger(anceParser::IntegerContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitArray(anceParser::ArrayContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitVector(anceParser::VectorContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitKeyword(anceParser::KeywordContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitPointer(anceParser::PointerContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitBuffer(anceParser::BufferContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitReference(anceParser::ReferenceContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitCustom(anceParser::CustomContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitIntegerType(anceParser::IntegerTypeContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitArrayType(anceParser::ArrayTypeContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitVectorType(anceParser::VectorTypeContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitKeywordType(anceParser::KeywordTypeContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitFloatingPointType(anceParser::FloatingPointTypeContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitTargetDependentType(anceParser::TargetDependentTypeContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitBooleanType(anceParser::BooleanTypeContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitNullPointerType(anceParser::NullPointerTypeContext* ctx) override
    {
        return visitChildren(ctx);
    }

    virtual std::any visitVoidType(anceParser::VoidTypeContext* ctx) override { return visitChildren(ctx); }

    virtual std::any visitCustomType(anceParser::CustomTypeContext* ctx) override { return visitChildren(ctx); }
};

