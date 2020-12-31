#pragma once
#include "anceBaseVisitor.h"

#include "function_call.h"
#include "print_statement.h"
#include "return_statement.h"

class Visitor : public anceBaseVisitor
{
public:
	Visitor(Application& application);

	antlrcpp::Any visitConstant_declaration(anceParser::Constant_declarationContext* context) override;

	antlrcpp::Any visitEntry(anceParser::EntryContext* context) override;
	antlrcpp::Any visitFunction(anceParser::FunctionContext* context) override;

	antlrcpp::Any visitPrint_statement(anceParser::Print_statementContext* context) override;
	antlrcpp::Any visitReturn_statement(anceParser::Return_statementContext* context) override;
	antlrcpp::Any visitFunction_call(anceParser::Function_callContext* context) override;

	antlrcpp::Any visitVariable_expression(anceParser::Variable_expressionContext* context) override;
	antlrcpp::Any visitLiteral_expression(anceParser::Literal_expressionContext* context) override;

private:
	Application application_;
};