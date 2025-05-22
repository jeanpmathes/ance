
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "anceVisitor.h"


/**
 * This class provides an empty implementation of anceVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  anceBaseVisitor : public anceVisitor {
public:

  virtual std::any visitFile(anceParser::FileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockStatement(anceParser::BlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(anceParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLetStatement(anceParser::LetStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentStatement(anceParser::AssignmentStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(anceParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLoopStatement(anceParser::LoopStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStatement(anceParser::BreakStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStatement(anceParser::ContinueStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStatement(anceParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallExpression(anceParser::CallExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAccessExpression(anceParser::AccessExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralExpression(anceParser::LiteralExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOperationExpression(anceParser::UnaryOperationExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolType(anceParser::BoolTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnitType(anceParser::UnitTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSizeType(anceParser::SizeTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryNot(anceParser::UnaryNotContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBooleanLiteral(anceParser::BooleanLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrue(anceParser::TrueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFalse(anceParser::FalseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEntity(anceParser::EntityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssigner(anceParser::AssignerContext *ctx) override {
    return visitChildren(ctx);
  }


};

