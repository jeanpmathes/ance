
// Generated from ./src/management/grammar/data.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "dataParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by dataParser.
 */
class  dataVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by dataParser.
   */
    virtual std::any visitElement(dataParser::ElementContext *context) = 0;

    virtual std::any visitDictionary(dataParser::DictionaryContext *context) = 0;

    virtual std::any visitEntry(dataParser::EntryContext *context) = 0;

    virtual std::any visitList(dataParser::ListContext *context) = 0;

    virtual std::any visitString(dataParser::StringContext *context) = 0;

    virtual std::any visitTrue(dataParser::TrueContext *context) = 0;

    virtual std::any visitFalse(dataParser::FalseContext *context) = 0;


};

