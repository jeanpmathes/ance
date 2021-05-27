
// Generated from ./src/grammar/ance.g4 by ANTLR 4.8

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
    virtual antlrcpp::Any visitFile(anceParser::FileContext *context) = 0;

    virtual antlrcpp::Any visitData(anceParser::DataContext *context) = 0;

    virtual antlrcpp::Any visitConstantDeclaration(anceParser::ConstantDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitVariableDeclaration(anceParser::VariableDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitCode(anceParser::CodeContext *context) = 0;

    virtual antlrcpp::Any visitFunction(anceParser::FunctionContext *context) = 0;

    virtual antlrcpp::Any visitParameters(anceParser::ParametersContext *context) = 0;

    virtual antlrcpp::Any visitParameter(anceParser::ParameterContext *context) = 0;

    virtual antlrcpp::Any visitPublic(anceParser::PublicContext *context) = 0;

    virtual antlrcpp::Any visitPrivate(anceParser::PrivateContext *context) = 0;

    virtual antlrcpp::Any visitStatement(anceParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitExpressionStatement(anceParser::ExpressionStatementContext *context) = 0;

    virtual antlrcpp::Any visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitAssignment(anceParser::AssignmentContext *context) = 0;

    virtual antlrcpp::Any visitPrintStatement(anceParser::PrintStatementContext *context) = 0;

    virtual antlrcpp::Any visitDeleteStatement(anceParser::DeleteStatementContext *context) = 0;

    virtual antlrcpp::Any visitReturnStatement(anceParser::ReturnStatementContext *context) = 0;

    virtual antlrcpp::Any visitAssignable(anceParser::AssignableContext *context) = 0;

    virtual antlrcpp::Any visitVariableAssignable(anceParser::VariableAssignableContext *context) = 0;

    virtual antlrcpp::Any visitExpression(anceParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitIndependentExpression(anceParser::IndependentExpressionContext *context) = 0;

    virtual antlrcpp::Any visitFunctionCall(anceParser::FunctionCallContext *context) = 0;

    virtual antlrcpp::Any visitArguments(anceParser::ArgumentsContext *context) = 0;

    virtual antlrcpp::Any visitVariableAccess(anceParser::VariableAccessContext *context) = 0;

    virtual antlrcpp::Any visitAllocation(anceParser::AllocationContext *context) = 0;

    virtual antlrcpp::Any visitDynamic(anceParser::DynamicContext *context) = 0;

    virtual antlrcpp::Any visitAutomatic(anceParser::AutomaticContext *context) = 0;

    virtual antlrcpp::Any visitRoughCast(anceParser::RoughCastContext *context) = 0;

    virtual antlrcpp::Any visitSizeofType(anceParser::SizeofTypeContext *context) = 0;

    virtual antlrcpp::Any visitSizeofExpression(anceParser::SizeofExpressionContext *context) = 0;

    virtual antlrcpp::Any visitLiteralExpression(anceParser::LiteralExpressionContext *context) = 0;

    virtual antlrcpp::Any visitStringLiteral(anceParser::StringLiteralContext *context) = 0;

    virtual antlrcpp::Any visitByteLiteral(anceParser::ByteLiteralContext *context) = 0;

    virtual antlrcpp::Any visitIntegerLiteral(anceParser::IntegerLiteralContext *context) = 0;

    virtual antlrcpp::Any visitUnsignedInteger(anceParser::UnsignedIntegerContext *context) = 0;

    virtual antlrcpp::Any visitSignedInteger(anceParser::SignedIntegerContext *context) = 0;

    virtual antlrcpp::Any visitSpecialInteger(anceParser::SpecialIntegerContext *context) = 0;

    virtual antlrcpp::Any visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext *context) = 0;

    virtual antlrcpp::Any visitTrue(anceParser::TrueContext *context) = 0;

    virtual antlrcpp::Any visitFalse(anceParser::FalseContext *context) = 0;

    virtual antlrcpp::Any visitSizeLiteral(anceParser::SizeLiteralContext *context) = 0;

    virtual antlrcpp::Any visitInteger(anceParser::IntegerContext *context) = 0;

    virtual antlrcpp::Any visitArray(anceParser::ArrayContext *context) = 0;

    virtual antlrcpp::Any visitKeyword(anceParser::KeywordContext *context) = 0;

    virtual antlrcpp::Any visitPointer(anceParser::PointerContext *context) = 0;

    virtual antlrcpp::Any visitIntegerType(anceParser::IntegerTypeContext *context) = 0;

    virtual antlrcpp::Any visitArrayType(anceParser::ArrayTypeContext *context) = 0;

    virtual antlrcpp::Any visitKeywordType(anceParser::KeywordTypeContext *context) = 0;

    virtual antlrcpp::Any visitFloatingPointType(anceParser::FloatingPointTypeContext *context) = 0;

    virtual antlrcpp::Any visitSizeType(anceParser::SizeTypeContext *context) = 0;

    virtual antlrcpp::Any visitUnsignedIntegerPointerType(anceParser::UnsignedIntegerPointerTypeContext *context) = 0;

    virtual antlrcpp::Any visitVoidType(anceParser::VoidTypeContext *context) = 0;


};

