
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

    virtual std::any visitBlockStatement(anceParser::BlockStatementContext *context) = 0;

    virtual std::any visitExpressionStatement(anceParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitLetStatement(anceParser::LetStatementContext *context) = 0;

    virtual std::any visitAssignmentStatement(anceParser::AssignmentStatementContext *context) = 0;

    virtual std::any visitIfStatement(anceParser::IfStatementContext *context) = 0;

    virtual std::any visitLoopStatement(anceParser::LoopStatementContext *context) = 0;

    virtual std::any visitBreakStatement(anceParser::BreakStatementContext *context) = 0;

    virtual std::any visitContinueStatement(anceParser::ContinueStatementContext *context) = 0;

    virtual std::any visitWhileStatement(anceParser::WhileStatementContext *context) = 0;

    virtual std::any visitCallExpression(anceParser::CallExpressionContext *context) = 0;

    virtual std::any visitAccessExpression(anceParser::AccessExpressionContext *context) = 0;

    virtual std::any visitLiteralExpression(anceParser::LiteralExpressionContext *context) = 0;

    virtual std::any visitUnaryOperationExpression(anceParser::UnaryOperationExpressionContext *context) = 0;

    virtual std::any visitUnaryNot(anceParser::UnaryNotContext *context) = 0;

    virtual std::any visitBooleanLiteral(anceParser::BooleanLiteralContext *context) = 0;

    virtual std::any visitSizeLiteral(anceParser::SizeLiteralContext *context) = 0;

    virtual std::any visitUnitLiteral(anceParser::UnitLiteralContext *context) = 0;

    virtual std::any visitTypeLiteral(anceParser::TypeLiteralContext *context) = 0;

    virtual std::any visitBoolType(anceParser::BoolTypeContext *context) = 0;

    virtual std::any visitUnitType(anceParser::UnitTypeContext *context) = 0;

    virtual std::any visitSizeType(anceParser::SizeTypeContext *context) = 0;

    virtual std::any visitTypeType(anceParser::TypeTypeContext *context) = 0;

    virtual std::any visitTrue(anceParser::TrueContext *context) = 0;

    virtual std::any visitFalse(anceParser::FalseContext *context) = 0;

    virtual std::any visitEntity(anceParser::EntityContext *context) = 0;

    virtual std::any visitAssigner(anceParser::AssignerContext *context) = 0;


};

