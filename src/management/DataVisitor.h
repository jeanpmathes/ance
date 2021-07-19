#ifndef ANCE_SRC_MANAGEMENT_DATAVISITOR_H_
#define ANCE_SRC_MANAGEMENT_DATAVISITOR_H_

#include "management/grammar/dataBaseVisitor.h"

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
