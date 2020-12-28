#include "Visitor.h"

#include "literal_expression.h"

Visitor::Visitor(Application& application) : application_(application)
{
}

antlrcpp::Any Visitor::visitConstant_declaration(anceParser::Constant_declarationContext* context)
{
	std::string identifier = context->IDENTIFIER()->getText();
	Expression* expr = visit(context->literal_expression());
	ConstantExpression* const_exp = static_cast<ConstantExpression*>(expr);

	application_.scope()->DeclareConstant(identifier, const_exp->get_constant_value());

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitEntry(anceParser::EntryContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	application_.scope()->AddAndEnterFunction(new ance::Function("main", line, column));

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitFunction(anceParser::FunctionContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	application_.scope()->AddAndEnterFunction(new ance::Function(context->IDENTIFIER()->getText(), line, column));

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitPrint_statement(anceParser::Print_statementContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	Expression* expression = this->visit(context->expression());

	print_statement* statement = new print_statement(line, column, expression);
	application_.scope()->PushStatementToCurrentFunction(statement);

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitReturn_statement(anceParser::Return_statementContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	uint32_t exit_code = 0;

	if (context->INTEGER() != nullptr)
	{
		exit_code = std::stoul(context->INTEGER()->getText());
	}

	return_statement* statement = new return_statement(line, column, exit_code);
	application_.scope()->PushStatementToCurrentFunction(statement);

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitFunction_call(anceParser::Function_callContext* context)
{
	std::string identifier = context->IDENTIFIER()->getText();

	application_.scope()->AddFunctionName(identifier);

	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	application_.scope()->PushStatementToCurrentFunction(new function_call(line, column, identifier));

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitLiteral_expression(anceParser::Literal_expressionContext* context)
{
	std::string unparsed = context->STRING()->getText();
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

	return static_cast<Expression*>(new literal_expression(builder.str()));
}