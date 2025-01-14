
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

  virtual std::any visitBlockStatement(anceParser::BlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(anceParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCall(anceParser::CallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArguments(anceParser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEntity(anceParser::EntityContext *ctx) override {
    return visitChildren(ctx);
  }


};

