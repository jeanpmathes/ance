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

#include "Assigner.h"
#include "AccessModifier.h"
#include "Function.h"
#include "DefinedFunction.h"
#include "Parameter.h"

#include "AssignmentStatement.h"
#include "ExpressionStatement.h"
#include "LocalVariableDefinition.h"
#include "PrintStatement.h"
#include "DeleteStatement.h"

#include "Assignable.h"
#include "VariableAssignable.h"
#include "IndexerSet.h"
#include "Discard.h"

#include "Expression.h"
#include "FunctionCall.h"
#include "SizeofExpression.h"
#include "SizeofType.h"
#include "ConstantLiteral.h"
#include "DefaultValueExpression.h"
#include "VariableAccess.h"
#include "Allocation.h"
#include "RoughCast.h"
#include "IndexerGet.h"
#include "BackingExpression.h"
#include "BuildableExpression.h"

#include "StringConstant.h"
#include "ByteConstant.h"
#include "IntegerConstant.h"
#include "FloatConstant.h"
#include "BooleanConstant.h"
#include "SizeConstant.h"

Visitor::Visitor(Application& application)
	: application_(application)
{
}

antlrcpp::Any Visitor::visitConstantDeclaration(anceParser::ConstantDeclarationContext* ctx)
{
	AccessModifier access = visit(ctx->accessModifier());
	ance::Type* type = visit(ctx->type());
	std::string identifier = ctx->IDENTIFIER()->getText();

	Assigner assigner = visit(ctx->assigner());
	assert(assigner == Assigner::FINAL_COPY_ASSIGNMENT && "Constant declaration has to be final.");

	Expression* expr = visit(ctx->literalExpression());
	auto* const_expr = dynamic_cast<ConstantExpression*>(expr);

	application_.globalScope()->defineGlobalConstant(access, identifier, type, const_expr->getConstantValue());

	return this->visitChildren(ctx);
}

antlrcpp::Any Visitor::visitVariableDeclaration(anceParser::VariableDeclarationContext* ctx)
{
	AccessModifier access = visit(ctx->accessModifier());
	ance::Type* type = visit(ctx->type());
	std::string identifier = ctx->IDENTIFIER()->getText();

	ConstantExpression* const_expr;

	if (ctx->literalExpression())
	{
		Assigner assigner = visit(ctx->assigner());
		assert(assigner == Assigner::COPY_ASSIGNMENT && "Final declaration not yet supported.");

		Expression* expr = visit(ctx->literalExpression());
		const_expr = dynamic_cast<ConstantExpression*>(expr);
	}
	else
	{
		const_expr = new DefaultValueExpression(type);
	}

	application_.globalScope()->defineGlobalVariable(access, identifier, type, const_expr->getConstantValue());

	return this->visitChildren(ctx);
}

antlrcpp::Any Visitor::visitFunctionDefinition(anceParser::FunctionDefinitionContext* ctx)
{
	unsigned int line = ctx->getStart()->getLine();
	unsigned int column = ctx->getStart()->getCharPositionInLine();

	AccessModifier access = visit(ctx->accessModifier());
	ance::Type* return_type = visit(ctx->type());

	std::vector<ance::Parameter*> parameters = visit(ctx->parameters());

	auto* function = new ance::DefinedFunction(
		access, ctx->IDENTIFIER()->getText(), return_type, parameters,
		application_.globalScope(), line, column
	);

	application_.globalScope()->addFunction(function);

	for (auto statement_context : ctx->statement())
	{
		Statement* statement = visit(statement_context);
		function->pushStatement(statement);
	}

	return this->visitChildren(ctx);
}

antlrcpp::Any Visitor::visitParameters(anceParser::ParametersContext* ctx)
{
	std::vector<ance::Parameter*> params;

	for (auto* param : ctx->parameter())
	{
		params.push_back(visit(param));
	}

	return params;
}

antlrcpp::Any Visitor::visitParameter(anceParser::ParameterContext* ctx)
{
	ance::Type* type = visit(ctx->type());
	const std::string k_identifier = ctx->IDENTIFIER()->getText();

	return new ance::Parameter(type, k_identifier);
}

antlrcpp::Any Visitor::visitExpressionStatement(anceParser::ExpressionStatementContext* ctx)
{
	unsigned int line = ctx->getStart()->getLine();
	unsigned int column = ctx->getStart()->getCharPositionInLine();

	Expression* expression = visit(ctx->independentExpression());
	auto* buildable_expression = dynamic_cast<BuildableExpression*>(expression);

	auto* statement =
		new ExpressionStatement(buildable_expression, line, column);

	return static_cast<Statement*>(statement);
}

antlrcpp::Any Visitor::visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx)
{
	unsigned int line = ctx->getStart()->getLine();
	unsigned int column = ctx->getStart()->getCharPositionInLine();

	ance::Type* type = visit(ctx->type());
	std::string identifier = ctx->IDENTIFIER()->getText();

	Expression* assigned;

	if (ctx->expression())
	{
		Assigner assigner = visit(ctx->assigner());
		assert(assigner == Assigner::COPY_ASSIGNMENT && "Final declaration not yet supported.");

		assigned = visit(ctx->expression());
	}
	else
	{
		assigned = new DefaultValueExpression(type);
	}

	auto* statement =
		new LocalVariableDefinition(identifier, type, assigned, line, column);

	return static_cast<Statement*>(statement);
}

antlrcpp::Any Visitor::visitAssignment(anceParser::AssignmentContext* ctx)
{
	unsigned int line = ctx->getStart()->getLine();
	unsigned int column = ctx->getStart()->getCharPositionInLine();

	Assignable* assignable = visit(ctx->assignable());
	Expression* assigned = visit(ctx->expression());

	Assigner assigner = visit(ctx->assigner());
	assert(assigner == Assigner::COPY_ASSIGNMENT && "Assignment to already declared variable cannot be final.");

	auto* statement =
		new AssignmentStatement(assignable, assigned, line, column);

	return static_cast<Statement*>(statement);
}

antlrcpp::Any Visitor::visitPrintStatement(anceParser::PrintStatementContext* ctx)
{
	unsigned int line = ctx->getStart()->getLine();
	unsigned int column = ctx->getStart()->getCharPositionInLine();

	Expression* str = visit(ctx->str);
	Expression* len = visit(ctx->len);

	auto* statement = new PrintStatement(str, len, line, column);

	return static_cast<Statement*>(statement);
}

antlrcpp::Any Visitor::visitDeleteStatement(anceParser::DeleteStatementContext* ctx)
{
	unsigned int line = ctx->getStart()->getLine();
	unsigned int column = ctx->getStart()->getCharPositionInLine();

	Expression* expression = visit(ctx->expression());
	bool delete_buffer = ctx->BUFFER();

	return static_cast<Statement*>(new DeleteStatement(expression, delete_buffer, line, column));
}

antlrcpp::Any Visitor::visitReturnStatement(anceParser::ReturnStatementContext* ctx)
{
	unsigned int line = ctx->getStart()->getLine();
	unsigned int column = ctx->getStart()->getCharPositionInLine();

	Expression* return_value = nullptr;

	if (ctx->expression() != nullptr)
	{
		return_value = visit(ctx->expression());
	}

	auto* statement =
		new ReturnStatement(return_value, line, column);

	return static_cast<Statement*>(statement);
}

antlrcpp::Any Visitor::visitVariableAssignable(anceParser::VariableAssignableContext* ctx)
{
	std::string identifier = ctx->IDENTIFIER()->getText();

	return static_cast<Assignable*>(new VariableAssignable(identifier));
}

antlrcpp::Any Visitor::visitIndexerSet(anceParser::IndexerSetContext* ctx)
{
	Expression* indexed = visit(ctx->indexed);
	Expression* index = visit(ctx->index);

	return static_cast<Assignable*>(new IndexerSet(indexed, index));
}

antlrcpp::Any Visitor::visitDiscard(anceParser::DiscardContext*)
{
	return static_cast<Assignable*>(new Discard());
}

antlrcpp::Any Visitor::visitFunctionCall(anceParser::FunctionCallContext* ctx)
{
	std::string identifier = ctx->IDENTIFIER()->getText();
	std::vector<Expression*> arguments = visit(ctx->arguments());

	// Call to highest scope intentional, as actual scope of called function is not known.
	application_.globalScope()->addFunctionName(identifier);

	return static_cast<Expression*>(new FunctionCall(identifier, arguments));
}

antlrcpp::Any Visitor::visitArguments(anceParser::ArgumentsContext* ctx)
{
	std::vector<Expression*> arguments;

	for (auto* argument : ctx->expression())
	{
		arguments.push_back(visit(argument));
	}

	return arguments;
}

antlrcpp::Any Visitor::visitVariableAccess(anceParser::VariableAccessContext* ctx)
{
	std::string identifier = ctx->IDENTIFIER()->getText();
	Expression* expression = new VariableAccess(identifier);
	return expression;
}

antlrcpp::Any Visitor::visitAllocation(anceParser::AllocationContext* ctx)
{
	Runtime::Allocator allocator = visit(ctx->allocator());
	ance::Type* type = visit(ctx->type());
	Expression* count = nullptr;

	if (ctx->expression())
	{
		count = visit(ctx->expression());
	}

	return static_cast<Expression*>(new Allocation(allocator, type, count, application_));
}

antlrcpp::Any Visitor::visitRoughCast(anceParser::RoughCastContext* ctx)
{
	ance::Type* type = visit(ctx->type());
	Expression* expr = visit(ctx->expression());

	return static_cast<Expression*>(new RoughCast(type, expr));
}

antlrcpp::Any Visitor::visitSizeofType(anceParser::SizeofTypeContext* ctx)
{
	ance::Type* type = visit(ctx->type());

	return static_cast<Expression*>(new SizeofType(type));
}

antlrcpp::Any Visitor::visitSizeofExpression(anceParser::SizeofExpressionContext* ctx)
{
	Expression* expr = visit(ctx->expression());

	return static_cast<Expression*>(new SizeofExpression(expr));
}

antlrcpp::Any Visitor::visitIndexerGet(anceParser::IndexerGetContext* ctx)
{
	Expression* indexed = visit(ctx->indexed);
	Expression* index = visit(ctx->index);

	return static_cast<Expression*>(new IndexerGet(indexed, index));
}

antlrcpp::Any Visitor::visitStringLiteral(anceParser::StringLiteralContext* ctx)
{
	std::string prefix;

	if (ctx->STRING_PREFIX())
	{
		prefix = ctx->STRING_PREFIX()->getText();
	}

	std::string str = ance::StringConstant::parse(ctx->STRING()->getText());

	ance::Constant* string = new ance::StringConstant(prefix, str, application_);
	return static_cast<Expression*>(new ConstantLiteral(string));
}

antlrcpp::Any Visitor::visitByteLiteral(anceParser::ByteLiteralContext* ctx)
{
	uint8_t b = ance::ByteConstant::parse(ctx->BYTE()->getText());

	ance::Constant* byte = new ance::ByteConstant(b, application_);
	return static_cast<Expression*>(new ConstantLiteral(byte));
}

antlrcpp::Any Visitor::visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext* ctx)
{
	llvm::APFloat number = llvm::APFloat::getZero(llvm::APFloat::Bogus());
	ance::FloatingPointType* type = nullptr;

	if (ctx->HALF())
	{
		number = llvm::APFloat(llvm::APFloat::IEEEhalf(), ctx->getText().erase(ctx->getText().size() - 1));
		type = ance::HalfType::get();
	}

	if (ctx->SINGLE())
	{
		number = llvm::APFloat(llvm::APFloat::IEEEsingle(), ctx->getText().erase(ctx->getText().size() - 1));
		type = ance::SingleType::get();
	}

	if (ctx->DOUBLE())
	{
		number = llvm::APFloat(llvm::APFloat::IEEEdouble(), ctx->getText().erase(ctx->getText().size() - 1));
		type = ance::DoubleType::get();
	}

	if (ctx->QUAD())
	{
		number = llvm::APFloat(llvm::APFloat::IEEEquad(), ctx->getText().erase(ctx->getText().size() - 1));
		type = ance::QuadType::get();
	}

	auto* flt = new ance::FloatConstant(number, type);
	return static_cast<Expression*>(new ConstantLiteral(flt));
}

antlrcpp::Any Visitor::visitTrue(anceParser::TrueContext*)
{
	ance::Constant* constant = ance::BooleanConstant::createTrue(application_);
	return static_cast<Expression*>(new ConstantLiteral(constant));
}

antlrcpp::Any Visitor::visitFalse(anceParser::FalseContext*)
{
	ance::Constant* constant = ance::BooleanConstant::createFalse(application_);
	return static_cast<Expression*>(new ConstantLiteral(constant));
}

antlrcpp::Any Visitor::visitSizeLiteral(anceParser::SizeLiteralContext* ctx)
{
	std::string size = ctx->INTEGER()->getText();
	ance::Constant* constant = new ance::SizeConstant(size, application_);

	return static_cast<Expression*>(new ConstantLiteral(constant));
}

antlrcpp::Any Visitor::visitUnsignedInteger(anceParser::UnsignedIntegerContext* ctx)
{
	uint64_t size = 64;

	if (ctx->INTEGER(1))
	{
		size = std::stoi(ctx->INTEGER(1)->getText());
	}

	const llvm::APInt integer(size, ctx->INTEGER(0)->getText(), 10);
	auto* integer_constant = new ance::IntegerConstant(integer, false, application_);
	Expression* expression = new ConstantLiteral(integer_constant);
	return expression;
}

antlrcpp::Any Visitor::visitSignedInteger(anceParser::SignedIntegerContext* ctx)
{
	uint64_t size = 64;

	if (ctx->INTEGER())
	{
		size = std::stoi(ctx->INTEGER()->getText());
	}

	const llvm::APInt integer(size, ctx->SIGNED_INTEGER()->getText(), 10);
	auto* integer_constant = new ance::IntegerConstant(integer, true, application_);
	Expression* expression = new ConstantLiteral(integer_constant);
	return expression;
}

antlrcpp::Any Visitor::visitSpecialInteger(anceParser::SpecialIntegerContext* ctx)
{
	uint64_t size = 64;

	if (ctx->INTEGER())
	{
		size = std::stoi(ctx->INTEGER()->getText());
	}

	std::string integer_str;
	int radix;

	if (ctx->HEX_INTEGER())
	{
		integer_str = ctx->HEX_INTEGER()->getText();
		radix = 16;
	}

	if (ctx->BIN_INTEGER())
	{
		integer_str = ctx->BIN_INTEGER()->getText();
		radix = 2;
	}

	if (ctx->OCT_INTEGER())
	{
		integer_str = ctx->OCT_INTEGER()->getText();
		radix = 8;
	}

	integer_str.erase(0, 2);

	const llvm::APInt integer(size, integer_str, radix);
	auto* integer_constant = new ance::IntegerConstant(integer, false, application_);
	Expression* expression = new ConstantLiteral(integer_constant);
	return expression;
}

antlrcpp::Any Visitor::visitIntegerType(anceParser::IntegerTypeContext* ctx)
{
	ance::Type* type;

	std::string integer_type_str = ctx->NATIVE_INTEGER_TYPE()->getText();

	bool is_unsigned = integer_type_str[0] == 'u';
	uint64_t size = std::stoi(integer_type_str.substr(1 + integer_type_str.find('i')));

	type = ance::IntegerType::get(application_, size, !is_unsigned);

	return type;
}

antlrcpp::Any Visitor::visitArrayType(anceParser::ArrayTypeContext* ctx)
{
	ance::Type* type;

	ance::Type* element_type = visit(ctx->type());
	uint64_t size = std::stoi(ctx->INTEGER()->getText());
	type = ance::ArrayType::get(application_, element_type, size);

	return type;
}

antlrcpp::Any Visitor::visitKeywordType(anceParser::KeywordTypeContext* ctx)
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

antlrcpp::Any Visitor::visitPublic(anceParser::PublicContext*)
{
	return AccessModifier::PUBLIC_ACCESS;
}

antlrcpp::Any Visitor::visitPrivate(anceParser::PrivateContext*)
{
	return AccessModifier::PRIVATE_ACCESS;
}

antlrcpp::Any Visitor::visitAutomatic(anceParser::AutomaticContext*)
{
	return Runtime::Allocator::AUTOMATIC;
}

antlrcpp::Any Visitor::visitDynamic(anceParser::DynamicContext*)
{
	return Runtime::Allocator::DYNAMIC;
}

antlrcpp::Any Visitor::visitCopyAssignment(anceParser::CopyAssignmentContext*)
{
	return Assigner::COPY_ASSIGNMENT;
}

antlrcpp::Any Visitor::visitMoveAssignment(anceParser::MoveAssignmentContext*)
{
	assert(false && "Move assignment currently not supported.");
	// todo: move assignment

	return Assigner::MOVE_ASSIGNMENT;
}

antlrcpp::Any Visitor::visitFinalCopyAssignment(anceParser::FinalCopyAssignmentContext*)
{
	return Assigner::FINAL_COPY_ASSIGNMENT;
}


