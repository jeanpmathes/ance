#pragma once
#include "antlr4-runtime.h"
#include "anceLexer.h"
#include "anceParser.h"
#include "anceBaseListener.h"
#include "Application.h"
class FileListener :
	public anceBaseListener
{
public:
	FileListener(Application& application);

	void exitReturn_statement(anceParser::Return_statementContext* ctx) override;

private:
	Application& application;
};
