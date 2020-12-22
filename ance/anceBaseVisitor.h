
// Generated from ./ance.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "anceVisitor.h"


/**
 * This class provides an empty implementation of anceVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  anceBaseVisitor : public anceVisitor {
public:

  virtual antlrcpp::Any visitFile(anceParser::FileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValue(anceParser::ValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstant_declaration(anceParser::Constant_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType(anceParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEntry(anceParser::EntryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunction(anceParser::FunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(anceParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunction_call(anceParser::Function_callContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrint_statement(anceParser::Print_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReturn_statement(anceParser::Return_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(anceParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariable_expression(anceParser::Variable_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLiteral_expression(anceParser::Literal_expressionContext *ctx) override {
    return visitChildren(ctx);
  }


};

