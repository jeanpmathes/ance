
// Generated from ./ance.g4 by ANTLR 4.8

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

    virtual antlrcpp::Any visitValue(anceParser::ValueContext *context) = 0;

    virtual antlrcpp::Any visitConstant_declaration(anceParser::Constant_declarationContext *context) = 0;

    virtual antlrcpp::Any visitType(anceParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitEntry(anceParser::EntryContext *context) = 0;

    virtual antlrcpp::Any visitFunction(anceParser::FunctionContext *context) = 0;

    virtual antlrcpp::Any visitStatement(anceParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitFunction_call(anceParser::Function_callContext *context) = 0;

    virtual antlrcpp::Any visitPrint_statement(anceParser::Print_statementContext *context) = 0;

    virtual antlrcpp::Any visitReturn_statement(anceParser::Return_statementContext *context) = 0;

    virtual antlrcpp::Any visitExpression(anceParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitVariable_expression(anceParser::Variable_expressionContext *context) = 0;

    virtual antlrcpp::Any visitLiteral_expression(anceParser::Literal_expressionContext *context) = 0;


};

