
// Generated from ./src/management/grammar/data.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "dataVisitor.h"


/**
 * This class provides an empty implementation of dataVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  dataBaseVisitor : public dataVisitor {
public:

  virtual std::any visitElement(dataParser::ElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDictionary(dataParser::DictionaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEntry(dataParser::EntryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitList(dataParser::ListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitString(dataParser::StringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrue(dataParser::TrueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFalse(dataParser::FalseContext *ctx) override {
    return visitChildren(ctx);
  }


};

