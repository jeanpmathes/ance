#include "FileListener.h"
#include "return_statement.h"

FileListener::FileListener(Application& app)
	: application(app)
{
}

void FileListener::exitReturn_statement(anceParser::Return_statementContext* ctx)
{
	return_statement* statement = new return_statement(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine());
	application.PushStatement(statement);
}