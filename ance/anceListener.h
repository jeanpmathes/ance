
// Generated from ./ance.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "anceParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by anceParser.
 */
class  anceListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterFile(anceParser::FileContext *ctx) = 0;
  virtual void exitFile(anceParser::FileContext *ctx) = 0;

  virtual void enterEntry(anceParser::EntryContext *ctx) = 0;
  virtual void exitEntry(anceParser::EntryContext *ctx) = 0;

  virtual void enterStatement(anceParser::StatementContext *ctx) = 0;
  virtual void exitStatement(anceParser::StatementContext *ctx) = 0;

  virtual void enterPrint_statement(anceParser::Print_statementContext *ctx) = 0;
  virtual void exitPrint_statement(anceParser::Print_statementContext *ctx) = 0;

  virtual void enterReturn_statement(anceParser::Return_statementContext *ctx) = 0;
  virtual void exitReturn_statement(anceParser::Return_statementContext *ctx) = 0;


};

