#include "Visitor.h"

#include <stdexcept>

#include "HalfType.h"
#include "IntegerType.h"
#include "SingleType.h"
#include "PointerType.h"
#include "ArrayType.h"
#include "QuadType.h"
#include "DoubleType.h"

#include "GlobalScope.h"
#include "LocalScope.h"

#include "Runtime.h"
#include "AccessModifier.h"
#include "Function.h"
#include "Parameter.h"

#include "AssignmentStatement.h"
#include "ExpressionStatement.h"
#include "LocalVariableDefinition.h"
#include "PrintStatement.h"

#include "FunctionCall.h"
#include "SizeofExprExpression.h"
#include "SizeofTypeExpression.h"
#include "ConstantLiteralExpression.h"
#include "DefaultValueExpression.h"
#include "VariableExpression.h"
#include "AllocationExpression.h"

#include "StringConstant.h"
#include "ByteConstant.h"
#include "IntegerConstant.h"
#include "FloatConstant.h"
#include "BooleanConstant.h"

Visitor::Visitor(Application& application)
	: application_(application)
{
}

antlrcpp::Any Visitor::visitConstant_declaration(anceParser::Constant_declarationContext* context)
{
	AccessModifier access = visit(context->access_modifier());
	ance::Type* type = visit(context->type());
	std::string identifier = context->IDENTIFIER()->getText();
	Expression* expr = visit(context->constant_expression());
	auto* const_expr = dynamic_cast<ConstantExpression*>(expr);

	application_.globalScope()->defineGlobalConstant(access, identifier, type, const_expr->getConstantValue());

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitVariable_declaration(anceParser::Variable_declarationContext* context)
{
	AccessModifier access = visit(context->access_modifier());
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
		const_expr = new DefaultValueExpression(type);
	}

	application_.globalScope()->defineGlobalVariable(access, identifier, type, const_expr->getConstantValue());

	return this->visitChildren(context);
}

antlrcpp::Any Visitor::visitFunction(anceParser::FunctionContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	AccessModifier access = visit(context->access_modifier());
	ance::Type* return_type = visit(context->type());

	std::vector<ance::Parameter*> parameters = visit(context->parameters());

	auto* function = new ance::Function(
		access, context->IDENTIFIER()->getText(), return_type, parameters,
		application_.globalScope(), line, column
	);

	application_.globalScope()->addFunction(function);

	for (auto statement_context : context->statement())
	{
		Statement* statement = visit(statement_context);
		function->pushStatement(statement);
	}

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
	const std::string k_identifier = context->IDENTIFIER()->getText();

	return new ance::Parameter(type, k_identifier);
}

antlrcpp::Any Visitor::visitExpression_statement(anceParser::Expression_statementContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	Expression* expression = visit(context->independent_expression());
	auto* buildable_expression = dynamic_cast<BuildableExpression*>(expression);

	auto* statement =
		new ExpressionStatement(buildable_expression, line, column);

	return static_cast<Statement*>(statement);
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
		assigned = new DefaultValueExpression(type);
	}

	auto* statement =
		new LocalVariableDefinition(identifier, type, assigned, line, column);

	return static_cast<Statement*>(statement);
}

antlrcpp::Any Visitor::visitVariable_assignment(anceParser::Variable_assignmentContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	std::string identifier = context->IDENTIFIER()->getText();
	Expression* assigned = visit(context->expression());

	auto* statement =
		new AssignmentStatement(identifier, assigned, line, column);

	return static_cast<Statement*>(statement);
}

antlrcpp::Any Visitor::visitPrint_statement(anceParser::Print_statementContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	Expression* expression = visit(context->expression());

	auto* statement = new PrintStatement(expression, line, column);

	return static_cast<Statement*>(statement);
}

antlrcpp::Any Visitor::visitReturn_statement(anceParser::Return_statementContext* context)
{
	unsigned int line = context->getStart()->getLine();
	unsigned int column = context->getStart()->getCharPositionInLine();

	Expression* return_value = nullptr;

	if (context->expression() != nullptr)
	{
		return_value = visit(context->expression());
	}

	auto* statement =
		new ReturnStatement(return_value, line, column);

	return static_cast<Statement*>(statement);
}

antlrcpp::Any Visitor::visitFunction_call(anceParser::Function_callContext* context)
{
	std::string identifier = context->IDENTIFIER()->getText();
	std::vector<Expression*> arguments = visit(context->arguments());

	application_.globalScope()->addFunctionName(identifier);

	return static_cast<Expression*>(new FunctionCall(identifier, arguments));
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
	Expression* expression = new VariableExpression(identifier);
	return expression;
}

antlrcpp::Any Visitor::visitAllocation_expression(anceParser::Allocation_expressionContext* ctx)
{
	Runtime::Allocator allocator = visit(ctx->allocator());
	ance::Type* type = visit(ctx->type());

	Expression* expression = new AllocationExpression(allocator, type, application_);
	return expression;
}

antlrcpp::Any Visitor::visitSizeof_type_expression(anceParser::Sizeof_type_expressionContext* context)
{
	ance::Type* type = visit(context->type());
	return static_cast<Expression*>(new SizeofTypeExpression(type));
}

antlrcpp::Any Visitor::visitSizeof_exp_expression(anceParser::Sizeof_exp_expressionContext* context)
{
	Expression* expr = visit(context->expression());
	return static_cast<Expression*>(new SizeofExprExpression(expr));
}

antlrcpp::Any Visitor::visitString_expression(anceParser::String_expressionContext* ctx)
{
	std::string str = ance::StringConstant::parse(ctx->STRING()->getText());

	ance::Constant* string = new ance::StringConstant(str, application_);
	return static_cast<Expression*>(new ConstantLiteralExpression(string));
}

antlrcpp::Any Visitor::visitByte_expression(anceParser::Byte_expressionContext* ctx)
{
	uint8_t b = ance::ByteConstant::parse(ctx->BYTE()->getText());

	ance::Constant* byte = new ance::ByteConstant(b, application_);
	return static_cast<Expression*>(new ConstantLiteralExpression(byte));
}

antlrcpp::Any Visitor::visitFloating_point_expression(anceParser::Floating_point_expressionContext* context)
{
	llvm::APFloat number = llvm::APFloat::getZero(llvm::APFloat::Bogus());
	ance::FloatingPointType* type = nullptr;

	if (context->HALF())
	{
		number = llvm::APFloat(llvm::APFloat::IEEEhalf(), context->getText().erase(context->getText().size() - 1));
		type = ance::HalfType::get();
	}

	if (context->SINGLE())
	{
		number = llvm::APFloat(llvm::APFloat::IEEEsingle(), context->getText().erase(context->getText().size() - 1));
		type = ance::SingleType::get();
	}

	if (context->DOUBLE())
	{
		number = llvm::APFloat(llvm::APFloat::IEEEdouble(), context->getText().erase(context->getText().size() - 1));
		type = ance::DoubleType::get();
	}

	if (context->QUAD())
	{
		number = llvm::APFloat(llvm::APFloat::IEEEquad(), context->getText().erase(context->getText().size() - 1));
		type = ance::QuadType::get();
	}

	auto* flt = new ance::FloatConstant(number, type);
	return static_cast<Expression*>(new ConstantLiteralExpression(flt));
}

antlrcpp::Any Visitor::visitBoolean_expression(anceParser::Boolean_expressionContext* ctx)
{
	ance::Constant* constant = nullptr;

	if (ctx->FALSE()) constant = ance::BooleanConstant::createFalse(application_);
	if (ctx->TRUE()) constant = ance::BooleanConstant::createTrue(application_);

	return static_cast<Expression*>(new ConstantLiteralExpression(constant));
}

antlrcpp::Any Visitor::visitUnsigned_integer(anceParser::Unsigned_integerContext* context)
{
	uint64_t size = 64;

	if (context->INTEGER(1))
	{
		size = std::stoi(context->INTEGER(1)->getText());
	}

	const llvm::APInt kInteger(size, context->INTEGER(0)->getText(), 10);
	auto* integer = new ance::IntegerConstant(kInteger, false, application_);
	Expression* expression = new ConstantLiteralExpression(integer);
	return expression;
}

antlrcpp::Any Visitor::visitSigned_integer(anceParser::Signed_integerContext* context)
{
	uint64_t size = 64;

	if (context->INTEGER())
	{
		size = std::stoi(context->INTEGER()->getText());
	}

	const llvm::APInt kInteger(size, context->SIGNED_INTEGER()->getText(), 10);
	auto* integer = new ance::IntegerConstant(kInteger, true, application_);
	Expression* expression = new ConstantLiteralExpression(integer);
	return expression;
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

	const llvm::APInt kInteger(size, integer_str, radix);
	auto* integer = new ance::IntegerConstant(kInteger, false, application_);
	Expression* expression = new ConstantLiteralExpression(integer);
	return expression;
}

antlrcpp::Any Visitor::visitInteger_type(anceParser::Integer_typeContext* context)
{
	ance::Type* type;

	std::string integer_type_str = context->NATIVE_INTEGER_TYPE()->getText();

	bool is_unsigned = integer_type_str[0] == 'u';
	uint64_t size = std::stoi(integer_type_str.substr(1 + integer_type_str.find('i')));

	type = ance::IntegerType::get(application_, size, !is_unsigned);

	return type;
}

antlrcpp::Any Visitor::visitArray_type(anceParser::Array_typeContext* context)
{
	ance::Type* type;

	ance::Type* element_type = visit(context->type());
	uint64_t size = std::stoi(context->INTEGER()->getText());
	type = ance::ArrayType::get(application_, element_type, size);

	return type;
}

antlrcpp::Any Visitor::visitKeyword_type(anceParser::Keyword_typeContext* ctx)
{
	ance::Type* type = application_.globalScope()->getType(ctx->getText());
	return type;
}

antlrcpp::Any Visitor::visitPointer(anceParser::PointerContext* ctx)
{
	ance::Type* element_type = visit(ctx->type());
	ance::Type* type = ance::PointerType::get(application_, element_type);
	return type;
}

antlrcpp::Any Visitor::visitAccess_modifier(anceParser::Access_modifierContext* context)
{
	AccessModifier access;

	if (context->PUBLIC()) access = AccessModifier::PUBLIC_ACCESS;
	else if (context->PRIVATE()) access = AccessModifier::PRIVATE_ACCESS;

	return access;
}

antlrcpp::Any Visitor::visitAllocator(anceParser::AllocatorContext* ctx)
{
	if (ctx->AUTOMATIC())
	{
		return Runtime::Allocator::AUTOMATIC;
	}

	if (ctx->DYNAMIC())
	{
		return Runtime::Allocator::DYNAMIC;
	}

	throw std::logic_error("Allocator not defined.");
}
