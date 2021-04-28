#pragma once

#include "anceBaseVisitor.h"

#include "ReturnStatement.h"

class Visitor : public anceBaseVisitor
{
	public:
		explicit Visitor(Application& application);

		// Declarations

		antlrcpp::Any visitConstant_declaration(anceParser::Constant_declarationContext* context) override;

		antlrcpp::Any visitVariable_declaration(anceParser::Variable_declarationContext* context) override;

		// Functions

		antlrcpp::Any visitFunction(anceParser::FunctionContext* context) override;

		antlrcpp::Any visitParameters(anceParser::ParametersContext* context) override;

		antlrcpp::Any visitParameter(anceParser::ParameterContext* context) override;

		// Statements

		antlrcpp::Any visitExpression_statement(anceParser::Expression_statementContext* context) override;

		antlrcpp::Any visitLocal_variable_definition(anceParser::Local_variable_definitionContext* context) override;

		antlrcpp::Any visitVariable_assignment(anceParser::Variable_assignmentContext* context) override;

		antlrcpp::Any visitPrint_statement(anceParser::Print_statementContext* context) override;

		antlrcpp::Any visitReturn_statement(anceParser::Return_statementContext* context) override;

		// Expressions

		antlrcpp::Any visitFunction_call(anceParser::Function_callContext* context) override;

		antlrcpp::Any visitArguments(anceParser::ArgumentsContext* context) override;

		antlrcpp::Any visitVariable_expression(anceParser::Variable_expressionContext* context) override;

		antlrcpp::Any visitSizeof_type_expression(anceParser::Sizeof_type_expressionContext* context) override;

		antlrcpp::Any visitSizeof_exp_expression(anceParser::Sizeof_exp_expressionContext* context) override;

		antlrcpp::Any visitLiteral_expression(anceParser::Literal_expressionContext* context) override;

		antlrcpp::Any visitFloating_point_expression(anceParser::Floating_point_expressionContext* context) override;

		// Literals and Types

		antlrcpp::Any visitUnsigned_integer(anceParser::Unsigned_integerContext* context) override;

		antlrcpp::Any visitSigned_integer(anceParser::Signed_integerContext* context) override;

		antlrcpp::Any visitSpecial_integer(anceParser::Special_integerContext* context) override;

		antlrcpp::Any visitInteger_type(anceParser::Integer_typeContext* context) override;

		antlrcpp::Any visitArray_type(anceParser::Array_typeContext* context) override;

		antlrcpp::Any visitKeyword_type(anceParser::Keyword_typeContext *ctx) override;

		antlrcpp::Any visitAccess_modifier(anceParser::Access_modifierContext* context) override;

	private:
		Application application_;
};