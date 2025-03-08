
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

    virtual std::any visitCall(anceParser::CallContext *context) = 0;

    virtual std::any visitAccess(anceParser::AccessContext *context) = 0;

    virtual std::any visitArguments(anceParser::ArgumentsContext *context) = 0;

    virtual std::any visitEntity(anceParser::EntityContext *context) = 0;


};

