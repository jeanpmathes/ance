#include "FileListener.h"
#include "print_statement.h"
#include "return_statement.h"

FileListener::FileListener(Application& app)
	: application(app)
{
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
	application.PushStatement(statement);
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
	application.PushStatement(statement);
}