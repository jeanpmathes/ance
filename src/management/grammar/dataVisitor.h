
// Generated from ./src/management/grammar/data.g4 by ANTLR 4.8

#pragma once

#include "antlr4-runtime.h"
#include "dataParser.h"

/**
 * This class defines an abstract visitor for a parse tree
 * produced by dataParser.
 */
class dataVisitor : public antlr4::tree::AbstractParseTreeVisitor
{
	public:

		/**
		 * Visit parse trees produced by dataParser.
		 */
		virtual antlrcpp::Any visitElement(dataParser::ElementContext* context) = 0;

		virtual antlrcpp::Any visitDictionary(dataParser::DictionaryContext* context) = 0;

		virtual antlrcpp::Any visitEntry(dataParser::EntryContext* context) = 0;

		virtual antlrcpp::Any visitList(dataParser::ListContext* context) = 0;

		virtual antlrcpp::Any visitString(dataParser::StringContext* context) = 0;

		virtual antlrcpp::Any visitTrue(dataParser::TrueContext* context) = 0;

		virtual antlrcpp::Any visitFalse(dataParser::FalseContext* context) = 0;

};

