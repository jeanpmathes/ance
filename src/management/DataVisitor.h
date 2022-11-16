#ifndef ANCE_SRC_MANAGEMENT_DATAVISITOR_H_
#define ANCE_SRC_MANAGEMENT_DATAVISITOR_H_

#include "management/grammar/dataBaseVisitor.h"

/**
 * Reads a data file and builds the element structure. Base class is generated.
 */
class DataVisitor : public dataBaseVisitor
{
  public:
    antlrcpp::Any visitDictionary(dataParser::DictionaryContext* ctx) override;

    antlrcpp::Any visitEntry(dataParser::EntryContext* ctx) override;

    antlrcpp::Any visitList(dataParser::ListContext* ctx) override;

    antlrcpp::Any visitString(dataParser::StringContext* ctx) override;

    antlrcpp::Any visitTrue(dataParser::TrueContext* ctx) override;

    antlrcpp::Any visitFalse(dataParser::FalseContext* ctx) override;
};

#endif
