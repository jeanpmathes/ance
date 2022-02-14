
// Generated from ./src/management/grammar/data.g4 by ANTLR 4.9.3

#pragma once


#include "antlr4-runtime.h"
#include "dataVisitor.h"


/**
 * This class provides an empty implementation of dataVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  dataBaseVisitor : public dataVisitor {
public:

  virtual antlrcpp::Any visitElement(dataParser::ElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDictionary(dataParser::DictionaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEntry(dataParser::EntryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitList(dataParser::ListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitString(dataParser::StringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTrue(dataParser::TrueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFalse(dataParser::FalseContext *ctx) override {
    return visitChildren(ctx);
  }


};

