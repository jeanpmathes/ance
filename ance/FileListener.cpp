#include "FileListener.h"
#include "return_statement.h"

FileListener::FileListener(Application& app)
	: application(app)
{
}

void FileListener::exitReturn_statement(anceParser::Return_statementContext* ctx)
{
	application.PushStatement(return_statement());
}