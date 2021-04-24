
// Generated from ./src/grammar/ance.g4 by ANTLR 4.8

#pragma once

#include "antlr4-runtime.h"

class anceParser : public antlr4::Parser
{
	public:
		enum
		{
				NATIVE_INTEGER_TYPE = 1, HALF_TYPE = 2, SINGLE_TYPE = 3, DOUBLE_TYPE = 4,
				QUAD_TYPE = 5, SIGNED_INTEGER = 6, HEX_INTEGER = 7, BIN_INTEGER = 8,
				OCT_INTEGER = 9, HALF = 10, SINGLE = 11, DOUBLE = 12, QUAD = 13, DECIMAL = 14,
				STRING = 15, INTEGER = 16, SIZEOF = 17, SIZE = 18, PRINT = 19, RETURN = 20,
				CONST = 21, PUBLIC = 22, PRIVATE = 23, VOID = 24, IDENTIFIER = 25, DEFINITION = 26,
				ASSIGNMENT = 27, PARENTHESES_OPEN = 28, PARENTHESES_CLOSED = 29, BRACE_OPEN = 30,
				BRACE_CLOSED = 31, BRACKET_OPEN = 32, BRACKET_CLOSED = 33, COMMA = 34,
				COLON = 35, SEMICOLON = 36, WHITESPACE = 37
		};

		enum
		{
				RuleFile = 0, RuleData = 1, RuleConstant_declaration = 2, RuleVariable_declaration = 3,
				RuleCode = 4, RuleFunction = 5, RuleParameters = 6, RuleParameter = 7,
				RuleAccess_modifier = 8, RuleStatement = 9, RuleExpression_statement = 10,
				RuleLocal_variable_definition = 11, RuleVariable_assignment = 12, RulePrint_statement = 13,
				RuleReturn_statement = 14, RuleExpression = 15, RuleIndependent_expression = 16,
				RuleFunction_call = 17, RuleArguments = 18, RuleVariable_expression = 19,
				RuleSizeof_type_expression = 20, RuleSizeof_exp_expression = 21, RuleConstant_expression = 22,
				RuleLiteral_expression = 23, RuleInteger_expression = 24, RuleUnsigned_integer = 25,
				RuleSigned_integer = 26, RuleSpecial_integer = 27, RuleFloating_point_expression = 28,
				RuleType = 29, RuleInteger_type = 30, RuleFloating_point_type = 31,
				RuleSize_type = 32, RuleArray_type = 33, RuleVoid_type = 34
		};

		anceParser(antlr4::TokenStream* input);

		~anceParser();

		virtual std::string getGrammarFileName() const override;

		virtual const antlr4::atn::ATN& getATN() const override
		{ return _atn; };

		virtual const std::vector<std::string>& getTokenNames() const override
		{ return _tokenNames; }; // deprecated: use vocabulary instead.
		virtual const std::vector<std::string>& getRuleNames() const override;

		virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

		class FileContext;

		class DataContext;

		class Constant_declarationContext;

		class Variable_declarationContext;

		class CodeContext;

		class FunctionContext;

		class ParametersContext;

		class ParameterContext;

		class Access_modifierContext;

		class StatementContext;

		class Expression_statementContext;

		class Local_variable_definitionContext;

		class Variable_assignmentContext;

		class Print_statementContext;

		class Return_statementContext;

		class ExpressionContext;

		class Independent_expressionContext;

		class Function_callContext;

		class ArgumentsContext;

		class Variable_expressionContext;

		class Sizeof_type_expressionContext;

		class Sizeof_exp_expressionContext;

		class Constant_expressionContext;

		class Literal_expressionContext;

		class Integer_expressionContext;

		class Unsigned_integerContext;

		class Signed_integerContext;

		class Special_integerContext;

		class Floating_point_expressionContext;

		class TypeContext;

		class Integer_typeContext;

		class Floating_point_typeContext;

		class Size_typeContext;

		class Array_typeContext;

		class Void_typeContext;

		class FileContext : public antlr4::ParserRuleContext
		{
			public:
				FileContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				std::vector<DataContext*> data();

				DataContext* data(size_t i);

				std::vector<CodeContext*> code();

				CodeContext* code(size_t i);

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		FileContext* file();

		class DataContext : public antlr4::ParserRuleContext
		{
			public:
				DataContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				Constant_declarationContext* constant_declaration();

				Variable_declarationContext* variable_declaration();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		DataContext* data();

		class Constant_declarationContext : public antlr4::ParserRuleContext
		{
			public:
				Constant_declarationContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				Access_modifierContext* access_modifier();

				antlr4::tree::TerminalNode* CONST();

				TypeContext* type();

				antlr4::tree::TerminalNode* IDENTIFIER();

				antlr4::tree::TerminalNode* DEFINITION();

				Constant_expressionContext* constant_expression();

				antlr4::tree::TerminalNode* SEMICOLON();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Constant_declarationContext* constant_declaration();

		class Variable_declarationContext : public antlr4::ParserRuleContext
		{
			public:
				Variable_declarationContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				Access_modifierContext* access_modifier();

				TypeContext* type();

				antlr4::tree::TerminalNode* IDENTIFIER();

				antlr4::tree::TerminalNode* SEMICOLON();

				antlr4::tree::TerminalNode* ASSIGNMENT();

				Constant_expressionContext* constant_expression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Variable_declarationContext* variable_declaration();

		class CodeContext : public antlr4::ParserRuleContext
		{
			public:
				CodeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				FunctionContext* function();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		CodeContext* code();

		class FunctionContext : public antlr4::ParserRuleContext
		{
			public:
				FunctionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				Access_modifierContext* access_modifier();

				TypeContext* type();

				antlr4::tree::TerminalNode* IDENTIFIER();

				antlr4::tree::TerminalNode* PARENTHESES_OPEN();

				ParametersContext* parameters();

				antlr4::tree::TerminalNode* PARENTHESES_CLOSED();

				antlr4::tree::TerminalNode* BRACE_OPEN();

				antlr4::tree::TerminalNode* BRACE_CLOSED();

				std::vector<StatementContext*> statement();

				StatementContext* statement(size_t i);

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		FunctionContext* function();

		class ParametersContext : public antlr4::ParserRuleContext
		{
			public:
				ParametersContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				std::vector<ParameterContext*> parameter();

				ParameterContext* parameter(size_t i);

				std::vector<antlr4::tree::TerminalNode*> COMMA();

				antlr4::tree::TerminalNode* COMMA(size_t i);

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		ParametersContext* parameters();

		class ParameterContext : public antlr4::ParserRuleContext
		{
			public:
				ParameterContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				TypeContext* type();

				antlr4::tree::TerminalNode* IDENTIFIER();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		ParameterContext* parameter();

		class Access_modifierContext : public antlr4::ParserRuleContext
		{
			public:
				Access_modifierContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* PUBLIC();

				antlr4::tree::TerminalNode* PRIVATE();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Access_modifierContext* access_modifier();

		class StatementContext : public antlr4::ParserRuleContext
		{
			public:
				StatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				Expression_statementContext* expression_statement();

				Local_variable_definitionContext* local_variable_definition();

				Variable_assignmentContext* variable_assignment();

				Print_statementContext* print_statement();

				Return_statementContext* return_statement();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		StatementContext* statement();

		class Expression_statementContext : public antlr4::ParserRuleContext
		{
			public:
				Expression_statementContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				Independent_expressionContext* independent_expression();

				antlr4::tree::TerminalNode* SEMICOLON();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Expression_statementContext* expression_statement();

		class Local_variable_definitionContext : public antlr4::ParserRuleContext
		{
			public:
				Local_variable_definitionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				TypeContext* type();

				antlr4::tree::TerminalNode* IDENTIFIER();

				antlr4::tree::TerminalNode* SEMICOLON();

				antlr4::tree::TerminalNode* ASSIGNMENT();

				ExpressionContext* expression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Local_variable_definitionContext* local_variable_definition();

		class Variable_assignmentContext : public antlr4::ParserRuleContext
		{
			public:
				Variable_assignmentContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* IDENTIFIER();

				antlr4::tree::TerminalNode* ASSIGNMENT();

				ExpressionContext* expression();

				antlr4::tree::TerminalNode* SEMICOLON();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Variable_assignmentContext* variable_assignment();

		class Print_statementContext : public antlr4::ParserRuleContext
		{
			public:
				Print_statementContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* PRINT();

				ExpressionContext* expression();

				antlr4::tree::TerminalNode* SEMICOLON();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Print_statementContext* print_statement();

		class Return_statementContext : public antlr4::ParserRuleContext
		{
			public:
				Return_statementContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* RETURN();

				antlr4::tree::TerminalNode* SEMICOLON();

				ExpressionContext* expression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Return_statementContext* return_statement();

		class ExpressionContext : public antlr4::ParserRuleContext
		{
			public:
				ExpressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				Variable_expressionContext* variable_expression();

				Sizeof_type_expressionContext* sizeof_type_expression();

				Sizeof_exp_expressionContext* sizeof_exp_expression();

				Constant_expressionContext* constant_expression();

				Independent_expressionContext* independent_expression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		ExpressionContext* expression();

		class Independent_expressionContext : public antlr4::ParserRuleContext
		{
			public:
				Independent_expressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				Function_callContext* function_call();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Independent_expressionContext* independent_expression();

		class Function_callContext : public antlr4::ParserRuleContext
		{
			public:
				Function_callContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* IDENTIFIER();

				antlr4::tree::TerminalNode* PARENTHESES_OPEN();

				ArgumentsContext* arguments();

				antlr4::tree::TerminalNode* PARENTHESES_CLOSED();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Function_callContext* function_call();

		class ArgumentsContext : public antlr4::ParserRuleContext
		{
			public:
				ArgumentsContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				std::vector<ExpressionContext*> expression();

				ExpressionContext* expression(size_t i);

				std::vector<antlr4::tree::TerminalNode*> COMMA();

				antlr4::tree::TerminalNode* COMMA(size_t i);

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		ArgumentsContext* arguments();

		class Variable_expressionContext : public antlr4::ParserRuleContext
		{
			public:
				Variable_expressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* IDENTIFIER();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Variable_expressionContext* variable_expression();

		class Sizeof_type_expressionContext : public antlr4::ParserRuleContext
		{
			public:
				Sizeof_type_expressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* SIZEOF();

				TypeContext* type();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Sizeof_type_expressionContext* sizeof_type_expression();

		class Sizeof_exp_expressionContext : public antlr4::ParserRuleContext
		{
			public:
				Sizeof_exp_expressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* SIZEOF();

				antlr4::tree::TerminalNode* PARENTHESES_OPEN();

				ExpressionContext* expression();

				antlr4::tree::TerminalNode* PARENTHESES_CLOSED();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Sizeof_exp_expressionContext* sizeof_exp_expression();

		class Constant_expressionContext : public antlr4::ParserRuleContext
		{
			public:
				Constant_expressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				Literal_expressionContext* literal_expression();

				Integer_expressionContext* integer_expression();

				Floating_point_expressionContext* floating_point_expression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Constant_expressionContext* constant_expression();

		class Literal_expressionContext : public antlr4::ParserRuleContext
		{
			public:
				Literal_expressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* STRING();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Literal_expressionContext* literal_expression();

		class Integer_expressionContext : public antlr4::ParserRuleContext
		{
			public:
				Integer_expressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				Unsigned_integerContext* unsigned_integer();

				Signed_integerContext* signed_integer();

				Special_integerContext* special_integer();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Integer_expressionContext* integer_expression();

		class Unsigned_integerContext : public antlr4::ParserRuleContext
		{
			public:
				Unsigned_integerContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				std::vector<antlr4::tree::TerminalNode*> INTEGER();

				antlr4::tree::TerminalNode* INTEGER(size_t i);

				antlr4::tree::TerminalNode* COLON();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Unsigned_integerContext* unsigned_integer();

		class Signed_integerContext : public antlr4::ParserRuleContext
		{
			public:
				Signed_integerContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* SIGNED_INTEGER();

				antlr4::tree::TerminalNode* COLON();

				antlr4::tree::TerminalNode* INTEGER();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Signed_integerContext* signed_integer();

		class Special_integerContext : public antlr4::ParserRuleContext
		{
			public:
				Special_integerContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* HEX_INTEGER();

				antlr4::tree::TerminalNode* COLON();

				antlr4::tree::TerminalNode* INTEGER();

				antlr4::tree::TerminalNode* BIN_INTEGER();

				antlr4::tree::TerminalNode* OCT_INTEGER();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Special_integerContext* special_integer();

		class Floating_point_expressionContext : public antlr4::ParserRuleContext
		{
			public:
				Floating_point_expressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* HALF();

				antlr4::tree::TerminalNode* SINGLE();

				antlr4::tree::TerminalNode* DOUBLE();

				antlr4::tree::TerminalNode* QUAD();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Floating_point_expressionContext* floating_point_expression();

		class TypeContext : public antlr4::ParserRuleContext
		{
			public:
				TypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				Integer_typeContext* integer_type();

				Floating_point_typeContext* floating_point_type();

				Size_typeContext* size_type();

				Array_typeContext* array_type();

				Void_typeContext* void_type();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		TypeContext* type();

		class Integer_typeContext : public antlr4::ParserRuleContext
		{
			public:
				Integer_typeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* NATIVE_INTEGER_TYPE();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Integer_typeContext* integer_type();

		class Floating_point_typeContext : public antlr4::ParserRuleContext
		{
			public:
				Floating_point_typeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* HALF_TYPE();

				antlr4::tree::TerminalNode* SINGLE_TYPE();

				antlr4::tree::TerminalNode* DOUBLE_TYPE();

				antlr4::tree::TerminalNode* QUAD_TYPE();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Floating_point_typeContext* floating_point_type();

		class Size_typeContext : public antlr4::ParserRuleContext
		{
			public:
				Size_typeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* SIZE();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Size_typeContext* size_type();

		class Array_typeContext : public antlr4::ParserRuleContext
		{
			public:
				Array_typeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* BRACKET_OPEN();

				antlr4::tree::TerminalNode* INTEGER();

				antlr4::tree::TerminalNode* COLON();

				TypeContext* type();

				antlr4::tree::TerminalNode* BRACKET_CLOSED();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Array_typeContext* array_type();

		class Void_typeContext : public antlr4::ParserRuleContext
		{
			public:
				Void_typeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* VOID();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		Void_typeContext* void_type();

	private:
		static std::vector<antlr4::dfa::DFA> _decisionToDFA;
		static antlr4::atn::PredictionContextCache _sharedContextCache;
		static std::vector<std::string> _ruleNames;
		static std::vector<std::string> _tokenNames;

		static std::vector<std::string> _literalNames;
		static std::vector<std::string> _symbolicNames;
		static antlr4::dfa::Vocabulary _vocabulary;
		static antlr4::atn::ATN _atn;
		static std::vector<uint16_t> _serializedATN;

		struct Initializer
		{
				Initializer();
		};

		static Initializer _init;
};

