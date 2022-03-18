
// Generated from ./src/grammar/ance.g4 by ANTLR 4.9.3

#pragma once

#include "antlr4-runtime.h"
#include "anceParser.h"

/**
 * This class defines an abstract visitor for a parse tree
 * produced by anceParser.
 */
class anceVisitor : public antlr4::tree::AbstractParseTreeVisitor
{
  public:
    /**
   * Visit parse trees produced by anceParser.
   */
    virtual antlrcpp::Any visitFile(anceParser::FileContext* context) = 0;

    virtual antlrcpp::Any visitVariableDeclaration(anceParser::VariableDeclarationContext* context) = 0;

    virtual antlrcpp::Any visitFunctionDefinition(anceParser::FunctionDefinitionContext* context) = 0;

    virtual antlrcpp::Any visitExternFunctionDeclaration(anceParser::ExternFunctionDeclarationContext* context) = 0;

    virtual antlrcpp::Any visitParameters(anceParser::ParametersContext* context) = 0;

    virtual antlrcpp::Any visitParameter(anceParser::ParameterContext* context) = 0;

    virtual antlrcpp::Any visitTypeDefinition(anceParser::TypeDefinitionContext* context) = 0;

    virtual antlrcpp::Any visitDefineAs(anceParser::DefineAsContext* context) = 0;

    virtual antlrcpp::Any visitDefineAlias(anceParser::DefineAliasContext* context) = 0;

    virtual antlrcpp::Any visitPublic(anceParser::PublicContext* context) = 0;

    virtual antlrcpp::Any visitPrivate(anceParser::PrivateContext* context) = 0;

    virtual antlrcpp::Any visitCode(anceParser::CodeContext* context) = 0;

    virtual antlrcpp::Any visitBlock(anceParser::BlockContext* context) = 0;

    virtual antlrcpp::Any visitStatement(anceParser::StatementContext* context) = 0;

    virtual antlrcpp::Any visitExpressionStatement(anceParser::ExpressionStatementContext* context) = 0;

    virtual antlrcpp::Any visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* context) = 0;

    virtual antlrcpp::Any visitLocalReferenceToValueDefinition(
        anceParser::LocalReferenceToValueDefinitionContext* context) = 0;

    virtual antlrcpp::Any visitLocalReferenceToPointerDefinition(
        anceParser::LocalReferenceToPointerDefinitionContext* context) = 0;

    virtual antlrcpp::Any visitAssignment(anceParser::AssignmentContext* context) = 0;

    virtual antlrcpp::Any visitCopyAssignment(anceParser::CopyAssignmentContext* context) = 0;

    virtual antlrcpp::Any visitMoveAssignment(anceParser::MoveAssignmentContext* context) = 0;

    virtual antlrcpp::Any visitFinalCopyAssignment(anceParser::FinalCopyAssignmentContext* context) = 0;

    virtual antlrcpp::Any visitDeleteStatement(anceParser::DeleteStatementContext* context) = 0;

    virtual antlrcpp::Any visitReturnStatement(anceParser::ReturnStatementContext* context) = 0;

    virtual antlrcpp::Any visitAssertStatement(anceParser::AssertStatementContext* context) = 0;

    virtual antlrcpp::Any visitRef(anceParser::RefContext* context) = 0;

    virtual antlrcpp::Any visitIndependent(anceParser::IndependentContext* context) = 0;

    virtual antlrcpp::Any visitParenthesis(anceParser::ParenthesisContext* context) = 0;

    virtual antlrcpp::Any visitVariable(anceParser::VariableContext* context) = 0;

    virtual antlrcpp::Any visitAlloc(anceParser::AllocContext* context) = 0;

    virtual antlrcpp::Any visitAdressOf(anceParser::AdressOfContext* context) = 0;

    virtual antlrcpp::Any visitBinaryOperation(anceParser::BinaryOperationContext* context) = 0;

    virtual antlrcpp::Any visitLiteral(anceParser::LiteralContext* context) = 0;

    virtual antlrcpp::Any visitSizeOf(anceParser::SizeOfContext* context) = 0;

    virtual antlrcpp::Any visitSubscript(anceParser::SubscriptContext* context) = 0;

    virtual antlrcpp::Any visitMultiplication(anceParser::MultiplicationContext* context) = 0;

    virtual antlrcpp::Any visitDivision(anceParser::DivisionContext* context) = 0;

    virtual antlrcpp::Any visitRemainder(anceParser::RemainderContext* context) = 0;

    virtual antlrcpp::Any visitAddition(anceParser::AdditionContext* context) = 0;

    virtual antlrcpp::Any visitSubtraction(anceParser::SubtractionContext* context) = 0;

    virtual antlrcpp::Any visitLessThan(anceParser::LessThanContext* context) = 0;

    virtual antlrcpp::Any visitLessThanOrEqual(anceParser::LessThanOrEqualContext* context) = 0;

    virtual antlrcpp::Any visitGreaterThan(anceParser::GreaterThanContext* context) = 0;

    virtual antlrcpp::Any visitGreaterThanOrEqual(anceParser::GreaterThanOrEqualContext* context) = 0;

    virtual antlrcpp::Any visitEqual(anceParser::EqualContext* context) = 0;

    virtual antlrcpp::Any visitNotEqual(anceParser::NotEqualContext* context) = 0;

    virtual antlrcpp::Any visitIndependentExpression(anceParser::IndependentExpressionContext* context) = 0;

    virtual antlrcpp::Any visitFunctionCall(anceParser::FunctionCallContext* context) = 0;

    virtual antlrcpp::Any visitArguments(anceParser::ArgumentsContext* context) = 0;

    virtual antlrcpp::Any visitVariableAccess(anceParser::VariableAccessContext* context) = 0;

    virtual antlrcpp::Any visitAllocation(anceParser::AllocationContext* context) = 0;

    virtual antlrcpp::Any visitDynamic(anceParser::DynamicContext* context) = 0;

    virtual antlrcpp::Any visitAutomatic(anceParser::AutomaticContext* context) = 0;

    virtual antlrcpp::Any visitAddressof(anceParser::AddressofContext* context) = 0;

    virtual antlrcpp::Any visitBindReference(anceParser::BindReferenceContext* context) = 0;

    virtual antlrcpp::Any visitBindReferenceToAddress(anceParser::BindReferenceToAddressContext* context) = 0;

    virtual antlrcpp::Any visitSizeofType(anceParser::SizeofTypeContext* context) = 0;

    virtual antlrcpp::Any visitSizeofExpression(anceParser::SizeofExpressionContext* context) = 0;

    virtual antlrcpp::Any visitLiteralExpression(anceParser::LiteralExpressionContext* context) = 0;

    virtual antlrcpp::Any visitStringLiteral(anceParser::StringLiteralContext* context) = 0;

    virtual antlrcpp::Any visitByteLiteral(anceParser::ByteLiteralContext* context) = 0;

    virtual antlrcpp::Any visitIntegerLiteral(anceParser::IntegerLiteralContext* context) = 0;

    virtual antlrcpp::Any visitUnsignedInteger(anceParser::UnsignedIntegerContext* context) = 0;

    virtual antlrcpp::Any visitSignedInteger(anceParser::SignedIntegerContext* context) = 0;

    virtual antlrcpp::Any visitSpecialInteger(anceParser::SpecialIntegerContext* context) = 0;

    virtual antlrcpp::Any visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext* context) = 0;

    virtual antlrcpp::Any visitTrue(anceParser::TrueContext* context) = 0;

    virtual antlrcpp::Any visitFalse(anceParser::FalseContext* context) = 0;

    virtual antlrcpp::Any visitSizeLiteral(anceParser::SizeLiteralContext* context) = 0;

    virtual antlrcpp::Any visitDiffLiteral(anceParser::DiffLiteralContext* context) = 0;

    virtual antlrcpp::Any visitInteger(anceParser::IntegerContext* context) = 0;

    virtual antlrcpp::Any visitArray(anceParser::ArrayContext* context) = 0;

    virtual antlrcpp::Any visitKeyword(anceParser::KeywordContext* context) = 0;

    virtual antlrcpp::Any visitPointer(anceParser::PointerContext* context) = 0;

    virtual antlrcpp::Any visitReference(anceParser::ReferenceContext* context) = 0;

    virtual antlrcpp::Any visitCustom(anceParser::CustomContext* context) = 0;

    virtual antlrcpp::Any visitIntegerType(anceParser::IntegerTypeContext* context) = 0;

    virtual antlrcpp::Any visitArrayType(anceParser::ArrayTypeContext* context) = 0;

    virtual antlrcpp::Any visitKeywordType(anceParser::KeywordTypeContext* context) = 0;

    virtual antlrcpp::Any visitFloatingPointType(anceParser::FloatingPointTypeContext* context) = 0;

    virtual antlrcpp::Any visitTargetDependentType(anceParser::TargetDependentTypeContext* context) = 0;

    virtual antlrcpp::Any visitVoidType(anceParser::VoidTypeContext* context) = 0;

    virtual antlrcpp::Any visitCustomType(anceParser::CustomTypeContext* context) = 0;
};

