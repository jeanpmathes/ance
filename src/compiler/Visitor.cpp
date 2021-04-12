#include "Visitor.h"

#include "AccessModifier.h"
#include "Parameter.h"
#include "ArrayType.h"
#include "literal_expression.h"
#include "variable_expression.h"
#include "assignment_statement.h"
#include "default_value_expression.h"
#include "DoubleType.h"
#include "expression_statement.h"
#include "floating_point_expression.h"
#include "SingleType.h"
#include "Function.h"
#include "function_call.h"
#include "GlobalScope.h"
#include "HalfType.h"
#include "IntegerType.h"
#include "integer_expression.h"
#include "LocalScope.h"
#include "local_variable_definition.h"
#include "print_statement.h"
#include "QuadType.h"
#include "sizeof_expression.h"
#include "sizeof_type.h"
#include "SizeType.h"
#include "VoidType.h"

Visitor::Visitor(Application& application) : application_(application)
{
}

antlrcpp::Any Visitor::visitConstant_declaration(anceParser::Constant_declarationContext* context)
{
	access_modifier access = visit(context->access_modifier());
	ance::Type* type = visit(context->type());
	std::string identifier = context->IDENTIFIER()->getText();
	Expression* expr = visit(context->constant_expression());
	auto* const_exp = dynamic_cast<ConstantExpression*>(expr);

	application_.global_scope()->define_global_constant(access, identifier, type, const_exp->get_constant_value());

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitVariable_declaration(anceParser::Variable_declarationContext* context)
{
	access_modifier access = visit(context->access_modifier());
	ance::Type* type = visit(context->type());
	std::string identifier = context->IDENTIFIER()->getText();

	ConstantExpression* const_expr;

	if (context->constant_expression())
	{
		Expression* expr = visit(context->constant_expression());
		const_expr = dynamic_cast<ConstantExpression*>(expr);
	}
	else
	{
		const_expr = new default_value_expression(type);
	}

	application_.global_scope()->define_global_variable(access, identifier, type, const_expr->get_constant_value());

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitFunction(anceParser::FunctionContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	access_modifier access = visit(context->access_modifier());
	ance::Type* return_type = visit(context->type());

	std::vector<ance::Parameter*> parameters = visit(context->parameters());

	application_.global_scope()->AddAndEnterFunction(new ance::Function(access, context->IDENTIFIER()->getText(), return_type, parameters, application_.global_scope(), line, column));

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitParameters(anceParser::ParametersContext* context)
{
	std::vector<ance::Parameter*> params;

	for (auto* param : context->parameter())
	{
		params.push_back(visit(param));
	}

	return params;
}

antlrcpp::Any Visitor::visitParameter(anceParser::ParameterContext* context)
{
	ance::Type* type = visit(context->type());
	const std::string identifier = context->IDENTIFIER()->getText();

	return new ance::Parameter(type, identifier);
}

antlrcpp::Any Visitor::visitExpression_statement(anceParser::Expression_statementContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	Expression* expression = visit(context->independent_expression());

	auto* statement = new expression_statement(application_.global_scope()->get_current_function(), dynamic_cast<BuildableExpression*>(expression), line, column);
	application_.global_scope()->PushStatementToCurrentFunction(statement);

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitLocal_variable_definition(anceParser::Local_variable_definitionContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	ance::Type* type = visit(context->type());
	std::string identifier = context->IDENTIFIER()->getText();

	Expression* assigned;

	if (context->expression())
	{
		assigned = visit(context->expression());
	}
	else
	{
		assigned = new default_value_expression(type);
	}

	ance::LocalVariable* variable = application_.global_scope()->get_current_function()->get_scope()->define_local_variable(identifier, type, assigned);
	auto* statement = new local_variable_definition(application_.global_scope()->get_current_function(), line, column, variable);
	application_.global_scope()->PushStatementToCurrentFunction(statement);

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitVariable_assignment(anceParser::Variable_assignmentContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	std::string identifier = context->IDENTIFIER()->getText();
	Expression* assigned = visit(context->expression());

	application_.global_scope()->PushStatementToCurrentFunction(new assignment_statement(application_.global_scope()->get_current_function(), line, column, identifier, assigned));

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitPrint_statement(anceParser::Print_statementContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	Expression* expression = visit(context->expression());

	auto* statement = new print_statement(application_.global_scope()->get_current_function(), line, column, expression);
	application_.global_scope()->PushStatementToCurrentFunction(statement);

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

	auto* const statement = new return_statement(application_.global_scope()->get_current_function(), line, column, return_value);
	application_.global_scope()->PushStatementToCurrentFunction(statement);

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitFunction_call(anceParser::Function_callContext* context)
{
	std::string identifier = context->IDENTIFIER()->getText();
	std::vector<Expression*> arguments = visit(context->arguments());

	application_.global_scope()->AddFunctionName(identifier);

	return static_cast<Expression*>(new function_call(identifier, application_.global_scope(), arguments));
}

antlrcpp::Any Visitor::visitArguments(anceParser::ArgumentsContext* context)
{
	std::vector<Expression*> arguments;

	for (auto* argument : context->expression())
	{
		arguments.push_back(visit(argument));
	}

	return arguments;
}

antlrcpp::Any Visitor::visitVariable_expression(anceParser::Variable_expressionContext* context)
{
	std::string identifier = context->IDENTIFIER()->getText();

	return static_cast<Expression*>(new variable_expression(application_.global_scope()->get_current_function()->get_scope()->get_variable(identifier)));
}

antlrcpp::Any Visitor::visitSizeof_type_expression(anceParser::Sizeof_type_expressionContext* context)
{
	ance::Type* type = visit(context->type());
	return static_cast<Expression*>(new sizeof_type(type, application_));
}

antlrcpp::Any Visitor::visitSizeof_exp_expression(anceParser::Sizeof_exp_expressionContext* context)
{
	Expression* exp = visit(context->expression());
	return static_cast<Expression*>(new sizeof_expression(exp, application_));
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

	return static_cast<Expression*>(new literal_expression(builder.str(), application_.global_scope()));
}

antlrcpp::Any Visitor::visitFloating_point_expression(anceParser::Floating_point_expressionContext* context)
{
	llvm::APFloat number = llvm::APFloat::getZero(llvm::APFloat::Bogus());
	ance::FloatingPointType* type = nullptr;

	if (context->HALF())
	{
		number = llvm::APFloat(llvm::APFloat::IEEEhalf(), context->getText().erase(context->getText().size() - 1));
		type = ance::HalfType::get(application_.global_scope());
	}

	if (context->SINGLE())
	{
		number = llvm::APFloat(llvm::APFloat::IEEEsingle(), context->getText().erase(context->getText().size() - 1));
		type = ance::SingleType::get(application_.global_scope());
	}

	if (context->DOUBLE())
	{
		number = llvm::APFloat(llvm::APFloat::IEEEdouble(), context->getText().erase(context->getText().size() - 1));
		type = ance::DoubleType::get(application_.global_scope());
	}

	if (context->QUAD())
	{
		number = llvm::APFloat(llvm::APFloat::IEEEquad(), context->getText().erase(context->getText().size() - 1));
		type = ance::QuadType::get(application_.global_scope());
	}

	return static_cast<Expression*>(new floating_point_expression(type, number));
}

antlrcpp::Any Visitor::visitUnsigned_integer(anceParser::Unsigned_integerContext* context)
{
	uint64_t size = 64;

	if (context->INTEGER(1))
	{
		size = std::stoi(context->INTEGER(1)->getText());
	}

	const llvm::APInt integer(size, context->INTEGER(0)->getText(), 10);
	return static_cast<Expression*>(new integer_expression(integer, application_.global_scope(), size, false));
}

antlrcpp::Any Visitor::visitSigned_integer(anceParser::Signed_integerContext* context)
{
	uint64_t size = 64;

	if (context->INTEGER())
	{
		size = std::stoi(context->INTEGER()->getText());
	}

	const llvm::APInt integer(size, context->SIGNED_INTEGER()->getText(), 10);
	return static_cast<Expression*>(new integer_expression(integer, application_.global_scope(), size, true));
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

    integer_str.erase(0, 2);

	const llvm::APInt integer(size, integer_str, radix);
	return static_cast<Expression*>(new integer_expression(integer, application_.global_scope(), size, false));
}

antlrcpp::Any Visitor::visitInteger_type(anceParser::Integer_typeContext* context)
{
	ance::Type* type;

	std::string integer_type_str = context->NATIVE_INTEGER_TYPE()->getText();

	bool is_unsigned = integer_type_str[0] == 'u';
	uint64_t size = std::stoi(integer_type_str.substr(1 + integer_type_str.find('i')));

	type = ance::IntegerType::get(application_.global_scope(), size, !is_unsigned);

	return type;
}

antlrcpp::Any Visitor::visitFloating_point_type(anceParser::Floating_point_typeContext* context)
{
	ance::Type* type;

	if (context->HALF_TYPE())
	{
		type = ance::HalfType::get(application_.global_scope());
	}

	if (context->SINGLE_TYPE())
	{
		type = ance::SingleType::get(application_.global_scope());
	}

	if (context->DOUBLE_TYPE())
	{
		type = ance::DoubleType::get(application_.global_scope());
	}

	if (context->QUAD_TYPE())
	{
		type = ance::QuadType::get(application_.global_scope());
	}

	return type;
}

antlrcpp::Any Visitor::visitSize_type(anceParser::Size_typeContext*)
{
	ance::Type* type = ance::SizeType::get(application_);
	return type;
}

antlrcpp::Any Visitor::visitArray_type(anceParser::Array_typeContext* context)
{
	ance::Type* type;

	ance::Type* element_type = visit(context->type());
	type = ance::ArrayType::get(application_.global_scope(), element_type, std::stoi(context->INTEGER()->getText()));

	return type;
}

antlrcpp::Any Visitor::visitVoid_type(anceParser::Void_typeContext*)
{
	ance::Type* type = ance::VoidType::get();
	return type;
}

antlrcpp::Any Visitor::visitAccess_modifier(anceParser::Access_modifierContext* context)
{
	access_modifier access;

	if (context->PUBLIC()) access = access_modifier::public_access;
	else if (context->PRIVATE()) access = access_modifier::private_access;

	return access;
}