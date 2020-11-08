#include "FileListener.h"

#include "function_call.h"
#include "print_statement.h"
#include "return_statement.h"

FileListener::FileListener(Application& app)
	: application(app)
{
}

void FileListener::enterEntry(anceParser::EntryContext* ctx)
{
	application.AddAndEnterFunction(new ance::Function("main"));
}

void FileListener::enterFunction(anceParser::FunctionContext* ctx)
{
	application.AddAndEnterFunction(new ance::Function(ctx->IDENTIFIER()->getText()));
}

void FileListener::exitPrint_statement(anceParser::Print_statementContext* ctx)
{
	unsigned int line = ctx->getStart()->getLine();
	unsigned int column = ctx->getStart()->getCharPositionInLine();

	std::string unparsed = ctx->STRING()->getText();
	std::stringstream builder;

	bool escaped = false;

	for (char const& c : unparsed)
	{
		if (escaped)
		{
			switch (c)
			{
			case 'n':
				builder << '\n';
				break;;

			default:
				builder << c;
				break;
			}

			escaped = false;
		}
		else
		{
			if (c == '\\')
			{
				escaped = true;
			}
			else if (c != '"')
			{
				builder << c;
			}
		}
	}

	print_statement* statement = new print_statement(line, column, builder.str());
	application.PushStatementToCurrentFunction(statement);
}

void FileListener::exitReturn_statement(anceParser::Return_statementContext* ctx)
{
	unsigned int line = ctx->getStart()->getLine();
	unsigned int column = ctx->getStart()->getCharPositionInLine();

	uint32_t exit_code = 0;

	if (ctx->INTEGER() != nullptr)
	{
		exit_code = std::stoul(ctx->INTEGER()->getText());
	}

	return_statement* statement = new return_statement(line, column, exit_code);
	application.PushStatementToCurrentFunction(statement);
}

void FileListener::exitFunction_call(anceParser::Function_callContext* ctx)
{
	std::string identifier = ctx->IDENTIFIER()->getText();

	application.AddFunctionName(identifier);

	unsigned int line = ctx->getStart()->getLine();
	unsigned int column = ctx->getStart()->getCharPositionInLine();

	application.PushStatementToCurrentFunction(new function_call(line, column, identifier));
}