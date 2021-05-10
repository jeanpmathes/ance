#pragma once

#include "anceBaseVisitor.h"

#include "ReturnStatement.h"

class Visitor : public anceBaseVisitor
{
	public:
		explicit Visitor(Application& application);

		// Declarations

		antlrcpp::Any visitConstantDeclaration(anceParser::ConstantDeclarationContext* ctx) override;

		antlrcpp::Any visitVariableDeclaration(anceParser::VariableDeclarationContext* ctx) override;

		// Functions

		antlrcpp::Any visitFunction(anceParser::FunctionContext* ctx) override;

		antlrcpp::Any visitParameters(anceParser::ParametersContext* ctx) override;

		antlrcpp::Any visitParameter(anceParser::ParameterContext* ctx) override;

		// Statements

		antlrcpp::Any visitExpressionStatement(anceParser::ExpressionStatementContext* ctx) override;

		antlrcpp::Any visitLocalVariableDefinition(anceParser::LocalVariableDefinitionContext* ctx) override;

		antlrcpp::Any visitVariableAssignment(anceParser::VariableAssignmentContext* ctx) override;

		antlrcpp::Any visitPrintStatement(anceParser::PrintStatementContext* ctx) override;

		antlrcpp::Any visitDeleteStatement(anceParser::DeleteStatementContext* ctx) override;

		antlrcpp::Any visitReturnStatement(anceParser::ReturnStatementContext* ctx) override;

		// Expressions

		antlrcpp::Any visitFunctionCall(anceParser::FunctionCallContext* ctx) override;

		antlrcpp::Any visitArguments(anceParser::ArgumentsContext* ctx) override;

		antlrcpp::Any visitVariableExpression(anceParser::VariableExpressionContext* ctx) override;

		antlrcpp::Any visitAllocationExpression(anceParser::AllocationExpressionContext* ctx) override;

		antlrcpp::Any visitSizeofTypeExpression(anceParser::SizeofTypeExpressionContext* ctx) override;

		antlrcpp::Any visitSizeofExpExpression(anceParser::SizeofExpExpressionContext* ctx) override;

		// Literals and Types

		antlrcpp::Any visitStringLiteral(anceParser::StringLiteralContext* ctx) override;

		antlrcpp::Any visitByteLiteral(anceParser::ByteLiteralContext* ctx) override;

		antlrcpp::Any visitFloatingPointLiteral(anceParser::FloatingPointLiteralContext* ctx) override;

		antlrcpp::Any visitBooleanLiteral(anceParser::BooleanLiteralContext* ctx) override;

		antlrcpp::Any visitUnsignedInteger(anceParser::UnsignedIntegerContext* ctx) override;

		antlrcpp::Any visitSignedInteger(anceParser::SignedIntegerContext* ctx) override;

		antlrcpp::Any visitSpecialInteger(anceParser::SpecialIntegerContext* ctx) override;

		antlrcpp::Any visitIntegerType(anceParser::IntegerTypeContext* ctx) override;

		antlrcpp::Any visitArrayType(anceParser::ArrayTypeContext* ctx) override;

		antlrcpp::Any visitKeywordType(anceParser::KeywordTypeContext* ctx) override;

		antlrcpp::Any visitPointer(anceParser::PointerContext* ctx) override;

		// Other

		antlrcpp::Any visitAccessModifier(anceParser::AccessModifierContext* ctx) override;

		antlrcpp::Any visitAllocator(anceParser::AllocatorContext* ctx) override;

	private:
		Application application_;
};