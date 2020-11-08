#include "anceParser.h"
#include "anceBaseListener.h"
#include "Application.h"
class FileListener :
	public anceBaseListener
{
public:
	FileListener(Application& application);

	void enterEntry(anceParser::EntryContext* ctx) override;
	void enterFunction(anceParser::FunctionContext* ctx) override;

	void exitPrint_statement(anceParser::Print_statementContext* ctx) override;
	void exitReturn_statement(anceParser::Return_statementContext* ctx) override;

	void exitFunction_call(anceParser::Function_callContext* ctx) override;

private:
	Application& application;
};
