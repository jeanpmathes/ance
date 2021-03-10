
// Generated from ./ance.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "anceParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by anceParser.
 */
class  anceVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by anceParser.
   */
    virtual antlrcpp::Any visitFile(anceParser::FileContext *context) = 0;

    virtual antlrcpp::Any visitData(anceParser::DataContext *context) = 0;

    virtual antlrcpp::Any visitConstant_declaration(anceParser::Constant_declarationContext *context) = 0;

    virtual antlrcpp::Any visitVariable_declaration(anceParser::Variable_declarationContext *context) = 0;

    virtual antlrcpp::Any visitCode(anceParser::CodeContext *context) = 0;

    virtual antlrcpp::Any visitFunction(anceParser::FunctionContext *context) = 0;

    virtual antlrcpp::Any visitParameters(anceParser::ParametersContext *context) = 0;

    virtual antlrcpp::Any visitParameter(anceParser::ParameterContext *context) = 0;

    virtual antlrcpp::Any visitAccess_modifier(anceParser::Access_modifierContext *context) = 0;

    virtual antlrcpp::Any visitStatement(anceParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitExpression_statement(anceParser::Expression_statementContext *context) = 0;

    virtual antlrcpp::Any visitLocal_variable_definition(anceParser::Local_variable_definitionContext *context) = 0;

    virtual antlrcpp::Any visitVariable_assignment(anceParser::Variable_assignmentContext *context) = 0;

    virtual antlrcpp::Any visitPrint_statement(anceParser::Print_statementContext *context) = 0;

    virtual antlrcpp::Any visitReturn_statement(anceParser::Return_statementContext *context) = 0;

    virtual antlrcpp::Any visitExpression(anceParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitIndependent_expression(anceParser::Independent_expressionContext *context) = 0;

    virtual antlrcpp::Any visitFunction_call(anceParser::Function_callContext *context) = 0;

    virtual antlrcpp::Any visitArguments(anceParser::ArgumentsContext *context) = 0;

    virtual antlrcpp::Any visitVariable_expression(anceParser::Variable_expressionContext *context) = 0;

    virtual antlrcpp::Any visitConstant_expression(anceParser::Constant_expressionContext *context) = 0;

    virtual antlrcpp::Any visitLiteral_expression(anceParser::Literal_expressionContext *context) = 0;

    virtual antlrcpp::Any visitInteger_expression(anceParser::Integer_expressionContext *context) = 0;

    virtual antlrcpp::Any visitUnsigned_integer(anceParser::Unsigned_integerContext *context) = 0;

    virtual antlrcpp::Any visitSigned_integer(anceParser::Signed_integerContext *context) = 0;

    virtual antlrcpp::Any visitSpecial_integer(anceParser::Special_integerContext *context) = 0;

    virtual antlrcpp::Any visitType(anceParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitInteger_type(anceParser::Integer_typeContext *context) = 0;

    virtual antlrcpp::Any visitArray_type(anceParser::Array_typeContext *context) = 0;

    virtual antlrcpp::Any visitVoid_type(anceParser::Void_typeContext *context) = 0;


};

