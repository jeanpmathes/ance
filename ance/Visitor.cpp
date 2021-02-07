#include "Visitor.h"

#include "AccessModifier.h"
#include "ArrayType.h"
#include "literal_expression.h"
#include "variable_expression.h"
#include "assignment_statement.h"
#include "default_value_expression.h"
#include "expression_statement.h"
#include "IntegerType.h"
#include "integer_expression.h"

Visitor::Visitor(Application& application) : application_(application)
{
}

antlrcpp::Any Visitor::visitConstant_declaration(anceParser::Constant_declarationContext* context)
{
	access_modifier access;

	if (context->access_modifier()->PUBLIC()) access = access_modifier::public_access;
	else if (context->access_modifier()->PRIVATE()) access = access_modifier::private_access;

	ance::Type* type = visit(context->type());
	std::string identifier = context->IDENTIFIER()->getText();
	Expression* expr = visit(context->constant_expression());
	ConstantExpression* const_exp = static_cast<ConstantExpression*>(expr);

	application_.scope()->DeclareConstant(access, identifier, type, const_exp->get_constant_value());

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitVariable_declaration(anceParser::Variable_declarationContext* context)
{
	access_modifier access;

	if (context->access_modifier()->PUBLIC()) access = access_modifier::public_access;
	else if (context->access_modifier()->PRIVATE()) access = access_modifier::private_access;

	ance::Type* type = visit(context->type());
	std::string identifier = context->IDENTIFIER()->getText();

	ConstantExpression* const_exp;

	if (context->constant_expression())
	{
		Expression* expr = visit(context->constant_expression());
		const_exp = static_cast<ConstantExpression*>(expr);
	}
	else
	{
		const_exp = new default_value_expression(type);
	}

	application_.scope()->DeclareGlobalVariable(access, identifier, type, const_exp->get_constant_value());

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitFunction(anceParser::FunctionContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	ance::Type* return_type = visit(context->type());

	application_.scope()->AddAndEnterFunction(new ance::Function(context->IDENTIFIER()->getText(), return_type, line, column));

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitExpression_statement(anceParser::Expression_statementContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	Expression* expression = visit(context->independent_expression());

	auto* statement = new expression_statement(expression, line, column);
	application_.scope()->PushStatementToCurrentFunction(statement);

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitPrint_statement(anceParser::Print_statementContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	Expression* expression = visit(context->expression());

	auto* statement = new print_statement(line, column, expression);
	application_.scope()->PushStatementToCurrentFunction(statement);

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitReturn_statement(anceParser::Return_statementContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	ance::Value* return_value = nullptr;

	if (context->expression() != nullptr)
	{
		Expression* expression = visit(context->expression());
		return_value = expression->get_value();
	}

	const auto statement = new return_statement(line, column, return_value);
	application_.scope()->PushStatementToCurrentFunction(statement);

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitVariable_assignment(anceParser::Variable_assignmentContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	std::string identifier = context->IDENTIFIER()->getText();
	Expression* assigned = visit(context->expression());

	application_.scope()->PushStatementToCurrentFunction(new assignment_statement(line, column, identifier, application_.scope(), assigned));

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitFunction_call(anceParser::Function_callContext* context)
{
	std::string identifier = context->IDENTIFIER()->getText();

	application_.scope()->AddFunctionName(identifier);

	return static_cast<Expression*>(new function_call(identifier));
}

antlrcpp::Any Visitor::visitVariable_expression(anceParser::Variable_expressionContext* context)
{
	std::string identifier = context->IDENTIFIER()->getText();

	return static_cast<Expression*>(new variable_expression(application_.scope(), identifier));
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
				break;

			case '0':
				builder << '\0';
				break;

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

	return static_cast<Expression*>(new literal_expression(builder.str(), application_.scope()));
}

antlrcpp::Any Visitor::visitUnsigned_integer(anceParser::Unsigned_integerContext* context)
{
	uint64_t size = 64;

	if (context->INTEGER(1))
	{
		size = std::stoi(context->INTEGER(1)->getText());
	}

	const llvm::APInt integer(size, context->INTEGER(0)->getText(), 10);
	return static_cast<Expression*>(new integer_expression(integer, application_.scope(), size, false));
}

antlrcpp::Any Visitor::visitSigned_integer(anceParser::Signed_integerContext* context)
{
	uint64_t size = 64;

	if (context->INTEGER())
	{
		size = std::stoi(context->INTEGER()->getText());
	}

	const llvm::APInt integer(size, context->SIGNED_INTEGER()->getText(), 10);
	return static_cast<Expression*>(new integer_expression(integer, application_.scope(), size, true));
}

antlrcpp::Any Visitor::visitSpecial_integer(anceParser::Special_integerContext* context)
{
	uint64_t size = 64;

	if (context->INTEGER())
	{
		size = std::stoi(context->INTEGER()->getText());
	}

	std::string integer_str;
	int radix;

	if (context->HEX_INTEGER())
	{
		integer_str = context->HEX_INTEGER()->getText();
		radix = 16;
	}

	if (context->BIN_INTEGER())
	{
		integer_str = context->BIN_INTEGER()->getText();
		radix = 2;
	}

	if (context->OCT_INTEGER())
	{
		integer_str = context->OCT_INTEGER()->getText();
		radix = 8;
	}

	const llvm::APInt integer(size, integer_str, radix);
	return static_cast<Expression*>(new integer_expression(integer, application_.scope(), size, false));
}

antlrcpp::Any Visitor::visitInteger_type(anceParser::Integer_typeContext* context)
{
	ance::Type* type;

	std::string integer_type_str = context->NATIVE_INTEGER_TYPE()->getText();

	bool is_unsigned = integer_type_str[0] == 'u';
	uint64_t size = std::stoi(integer_type_str.substr(1 + integer_type_str.find('i')));

	type = ance::IntegerType::get(application_.scope(), size, !is_unsigned);

	return type;
}

antlrcpp::Any Visitor::visitArray_type(anceParser::Array_typeContext* context)
{
	ance::Type* type;

	ance::Type* element_type = visit(context->type());
	type = ance::ArrayType::get(application_.scope(), element_type, std::stoi(context->INTEGER()->getText()));

	return type;
}