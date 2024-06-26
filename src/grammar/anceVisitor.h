
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "anceParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by anceParser.
 */
class  anceVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by anceParser.
   */
    virtual std::any visitFile(anceParser::FileContext *context) = 0;

    virtual std::any visitProjectFile(anceParser::ProjectFileContext *context) = 0;

    virtual std::any visitGlobal(anceParser::GlobalContext *context) = 0;

    virtual std::any visitDescription(anceParser::DescriptionContext *context) = 0;

    virtual std::any visitVariableDescription(anceParser::VariableDescriptionContext *context) = 0;

    virtual std::any visitFunctionDescription(anceParser::FunctionDescriptionContext *context) = 0;

    virtual std::any visitFunctionBlock(anceParser::FunctionBlockContext *context) = 0;

    virtual std::any visitParameters(anceParser::ParametersContext *context) = 0;

    virtual std::any visitParameter(anceParser::ParameterContext *context) = 0;

    virtual std::any visitTypeDescription(anceParser::TypeDescriptionContext *context) = 0;

    virtual std::any visitAliasDescription(anceParser::AliasDescriptionContext *context) = 0;

    virtual std::any visitStructDescription(anceParser::StructDescriptionContext *context) = 0;

    virtual std::any visitMember(anceParser::MemberContext *context) = 0;

    virtual std::any visitPublic(anceParser::PublicContext *context) = 0;

    virtual std::any visitPrivate(anceParser::PrivateContext *context) = 0;

    virtual std::any visitExtern(anceParser::ExternContext *context) = 0;

    virtual std::any visitCode(anceParser::CodeContext *context) = 0;

    virtual std::any visitBlock(anceParser::BlockContext *context) = 0;

    virtual std::any visitStatement(anceParser::StatementContext *context) = 0;

    virtual std::any visitExpressionStatement(anceParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext *context) = 0;

    virtual std::any visitLocalReferenceDefinition(anceParser::LocalReferenceDefinitionContext *context) = 0;

    virtual std::any visitEraseStatement(anceParser::EraseStatementContext *context) = 0;

    virtual std::any visitAssignment(anceParser::AssignmentContext *context) = 0;

    virtual std::any visitCopyAssignment(anceParser::CopyAssignmentContext *context) = 0;

    virtual std::any visitMoveAssignment(anceParser::MoveAssignmentContext *context) = 0;

    virtual std::any visitFinalCopyAssignment(anceParser::FinalCopyAssignmentContext *context) = 0;

    virtual std::any visitDeleteStatement(anceParser::DeleteStatementContext *context) = 0;

    virtual std::any visitBreakStatement(anceParser::BreakStatementContext *context) = 0;

    virtual std::any visitContinueStatement(anceParser::ContinueStatementContext *context) = 0;

    virtual std::any visitReturnStatement(anceParser::ReturnStatementContext *context) = 0;

    virtual std::any visitAssertStatement(anceParser::AssertStatementContext *context) = 0;

    virtual std::any visitIfStatement(anceParser::IfStatementContext *context) = 0;

    virtual std::any visitWhileStatement(anceParser::WhileStatementContext *context) = 0;

    virtual std::any visitLoopStatement(anceParser::LoopStatementContext *context) = 0;

    virtual std::any visitMatchStatement(anceParser::MatchStatementContext *context) = 0;

    virtual std::any visitLiteralCase(anceParser::LiteralCaseContext *context) = 0;

    virtual std::any visitDefaultCase(anceParser::DefaultCaseContext *context) = 0;

    virtual std::any visitCast(anceParser::CastContext *context) = 0;

    virtual std::any visitIfExpression(anceParser::IfExpressionContext *context) = 0;

    virtual std::any visitVariable(anceParser::VariableContext *context) = 0;

    virtual std::any visitUnaryOperation(anceParser::UnaryOperationContext *context) = 0;

    virtual std::any visitBinaryOperation(anceParser::BinaryOperationContext *context) = 0;

    virtual std::any visitSubscript(anceParser::SubscriptContext *context) = 0;

    virtual std::any visitLogicalOr(anceParser::LogicalOrContext *context) = 0;

    virtual std::any visitMatch(anceParser::MatchContext *context) = 0;

    virtual std::any visitRef(anceParser::RefContext *context) = 0;

    virtual std::any visitIndependent(anceParser::IndependentContext *context) = 0;

    virtual std::any visitParenthesis(anceParser::ParenthesisContext *context) = 0;

    virtual std::any visitAlloc(anceParser::AllocContext *context) = 0;

    virtual std::any visitMemberAccess(anceParser::MemberAccessContext *context) = 0;

    virtual std::any visitLiteral(anceParser::LiteralContext *context) = 0;

    virtual std::any visitLogicalAnd(anceParser::LogicalAndContext *context) = 0;

    virtual std::any visitVectorDefinition(anceParser::VectorDefinitionContext *context) = 0;

    virtual std::any visitAddressOf(anceParser::AddressOfContext *context) = 0;

    virtual std::any visitArrayDefinition(anceParser::ArrayDefinitionContext *context) = 0;

    virtual std::any visitSizeOf(anceParser::SizeOfContext *context) = 0;

    virtual std::any visitIndirection(anceParser::IndirectionContext *context) = 0;

    virtual std::any visitNot(anceParser::NotContext *context) = 0;

    virtual std::any visitBitwiseNot(anceParser::BitwiseNotContext *context) = 0;

    virtual std::any visitNegation(anceParser::NegationContext *context) = 0;

    virtual std::any visitMultiplication(anceParser::MultiplicationContext *context) = 0;

    virtual std::any visitDivision(anceParser::DivisionContext *context) = 0;

    virtual std::any visitRemainder(anceParser::RemainderContext *context) = 0;

    virtual std::any visitAddition(anceParser::AdditionContext *context) = 0;

    virtual std::any visitSubtraction(anceParser::SubtractionContext *context) = 0;

    virtual std::any visitBitwiseAnd(anceParser::BitwiseAndContext *context) = 0;

    virtual std::any visitBitwiseOr(anceParser::BitwiseOrContext *context) = 0;

    virtual std::any visitBitwiseXor(anceParser::BitwiseXorContext *context) = 0;

    virtual std::any visitLeftShift(anceParser::LeftShiftContext *context) = 0;

    virtual std::any visitRightShift(anceParser::RightShiftContext *context) = 0;

    virtual std::any visitLessThan(anceParser::LessThanContext *context) = 0;

    virtual std::any visitLessThanOrEqual(anceParser::LessThanOrEqualContext *context) = 0;

    virtual std::any visitGreaterThan(anceParser::GreaterThanContext *context) = 0;

    virtual std::any visitGreaterThanOrEqual(anceParser::GreaterThanOrEqualContext *context) = 0;

    virtual std::any visitEqual(anceParser::EqualContext *context) = 0;

    virtual std::any visitNotEqual(anceParser::NotEqualContext *context) = 0;

    virtual std::any visitIndependentExpression(anceParser::IndependentExpressionContext *context) = 0;

    virtual std::any visitFunctionCall(anceParser::FunctionCallContext *context) = 0;

    virtual std::any visitArguments(anceParser::ArgumentsContext *context) = 0;

    virtual std::any visitVariableAccess(anceParser::VariableAccessContext *context) = 0;

    virtual std::any visitAllocation(anceParser::AllocationContext *context) = 0;

    virtual std::any visitDynamic(anceParser::DynamicContext *context) = 0;

    virtual std::any visitAutomatic(anceParser::AutomaticContext *context) = 0;

    virtual std::any visitAddressof(anceParser::AddressofContext *context) = 0;

    virtual std::any visitBindReference(anceParser::BindReferenceContext *context) = 0;

    virtual std::any visitBindReferenceToAddress(anceParser::BindReferenceToAddressContext *context) = 0;

    virtual std::any visitSizeofType(anceParser::SizeofTypeContext *context) = 0;

    virtual std::any visitSizeofExpression(anceParser::SizeofExpressionContext *context) = 0;

    virtual std::any visitMatchExpression(anceParser::MatchExpressionContext *context) = 0;

    virtual std::any visitLiteralExpressionCase(anceParser::LiteralExpressionCaseContext *context) = 0;

    virtual std::any visitDefaultExpressionCase(anceParser::DefaultExpressionCaseContext *context) = 0;

    virtual std::any visitLiteralExpression(anceParser::LiteralExpressionContext *context) = 0;

    virtual std::any visitStringLiteral(anceParser::StringLiteralContext *context) = 0;

    virtual std::any visitCharLiteral(anceParser::CharLiteralContext *context) = 0;

    virtual std::any visitIntegerLiteral(anceParser::IntegerLiteralContext *context) = 0;

    virtual std::any visitNormalInteger(anceParser::NormalIntegerContext *context) = 0;

    virtual std::any visitSpecialInteger(anceParser::SpecialIntegerContext *context) = 0;

    virtual std::any visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext *context) = 0;

    virtual std::any visitTrue(anceParser::TrueContext *context) = 0;

    virtual std::any visitFalse(anceParser::FalseContext *context) = 0;

    virtual std::any visitNull(anceParser::NullContext *context) = 0;

    virtual std::any visitSizeLiteral(anceParser::SizeLiteralContext *context) = 0;

    virtual std::any visitDiffLiteral(anceParser::DiffLiteralContext *context) = 0;

    virtual std::any visitUiptrLiteral(anceParser::UiptrLiteralContext *context) = 0;

    virtual std::any visitUnitLiteral(anceParser::UnitLiteralContext *context) = 0;

    virtual std::any visitInteger(anceParser::IntegerContext *context) = 0;

    virtual std::any visitArray(anceParser::ArrayContext *context) = 0;

    virtual std::any visitVector(anceParser::VectorContext *context) = 0;

    virtual std::any visitKeyword(anceParser::KeywordContext *context) = 0;

    virtual std::any visitPointer(anceParser::PointerContext *context) = 0;

    virtual std::any visitBuffer(anceParser::BufferContext *context) = 0;

    virtual std::any visitReference(anceParser::ReferenceContext *context) = 0;

    virtual std::any visitCustom(anceParser::CustomContext *context) = 0;

    virtual std::any visitIntegerType(anceParser::IntegerTypeContext *context) = 0;

    virtual std::any visitArrayType(anceParser::ArrayTypeContext *context) = 0;

    virtual std::any visitVectorType(anceParser::VectorTypeContext *context) = 0;

    virtual std::any visitKeywordType(anceParser::KeywordTypeContext *context) = 0;

    virtual std::any visitFloatingPointType(anceParser::FloatingPointTypeContext *context) = 0;

    virtual std::any visitTargetDependentType(anceParser::TargetDependentTypeContext *context) = 0;

    virtual std::any visitBooleanType(anceParser::BooleanTypeContext *context) = 0;

    virtual std::any visitCharType(anceParser::CharTypeContext *context) = 0;

    virtual std::any visitNullPointerType(anceParser::NullPointerTypeContext *context) = 0;

    virtual std::any visitUnitType(anceParser::UnitTypeContext *context) = 0;

    virtual std::any visitCustomType(anceParser::CustomTypeContext *context) = 0;


};

