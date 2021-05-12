
// Generated from ./src/grammar/ance.g4 by ANTLR 4.8

#pragma once

#include "antlr4-runtime.h"

class anceParser : public antlr4::Parser
{
	public:
		enum
		{
				T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7,
				T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14,
				T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20,
				T__20 = 21, NATIVE_INTEGER_TYPE = 22, HALF_TYPE = 23, SINGLE_TYPE = 24,
				DOUBLE_TYPE = 25, QUAD_TYPE = 26, SIGNED_INTEGER = 27, HEX_INTEGER = 28,
				BIN_INTEGER = 29, OCT_INTEGER = 30, HALF = 31, SINGLE = 32, DOUBLE = 33,
				QUAD = 34, DECIMAL = 35, STRING = 36, BYTE = 37, INTEGER = 38, DYNAMIC = 39,
				AUTOMATIC = 40, TRUE = 41, FALSE = 42, PUBLIC = 43, PRIVATE = 44, IDENTIFIER = 45,
				WHITESPACE = 46, BLOCK_COMMENT = 47, LINE_COMMENT = 48
		};

		enum
		{
				RuleFile = 0, RuleData = 1, RuleConstantDeclaration = 2, RuleVariableDeclaration = 3,
				RuleCode = 4, RuleFunction = 5, RuleParameters = 6, RuleParameter = 7,
				RuleAccessModifier = 8, RuleStatement = 9, RuleExpressionStatement = 10,
				RuleLocalVariableDefinition = 11, RuleVariableAssignment = 12, RulePrintStatement = 13,
				RuleDeleteStatement = 14, RuleReturnStatement = 15, RuleExpression = 16,
				RuleIndependentExpression = 17, RuleFunctionCall = 18, RuleArguments = 19,
				RuleVariableAccess = 20, RuleAllocation = 21, RuleAllocator = 22, RuleRoughCast = 23,
				RuleSizeofType = 24, RuleSizeofExpression = 25, RuleLiteralExpression = 26,
				RuleStringLiteral = 27, RuleByteLiteral = 28, RuleIntegerLiteral = 29,
				RuleUnsignedInteger = 30, RuleSignedInteger = 31, RuleSpecialInteger = 32,
				RuleFloatingPointLiteral = 33, RuleBooleanLiteral = 34, RuleType = 35,
				RuleIntegerType = 36, RuleArrayType = 37, RuleKeywordType = 38, RuleFloatingPointType = 39,
				RuleSizeType = 40, RuleUnsignedIntegerPointerType = 41, RuleVoidType = 42
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

		class ConstantDeclarationContext;

		class VariableDeclarationContext;

		class CodeContext;

		class FunctionContext;

		class ParametersContext;

		class ParameterContext;

		class AccessModifierContext;

		class StatementContext;

		class ExpressionStatementContext;

		class LocalVariableDefinitionContext;

		class VariableAssignmentContext;

		class PrintStatementContext;

		class DeleteStatementContext;

		class ReturnStatementContext;

		class ExpressionContext;

		class IndependentExpressionContext;

		class FunctionCallContext;

		class ArgumentsContext;

		class VariableAccessContext;

		class AllocationContext;

		class AllocatorContext;

		class RoughCastContext;

		class SizeofTypeContext;

		class SizeofExpressionContext;

		class LiteralExpressionContext;

		class StringLiteralContext;

		class ByteLiteralContext;

		class IntegerLiteralContext;

		class UnsignedIntegerContext;

		class SignedIntegerContext;

		class SpecialIntegerContext;

		class FloatingPointLiteralContext;

		class BooleanLiteralContext;

		class TypeContext;

		class IntegerTypeContext;

		class ArrayTypeContext;

		class KeywordTypeContext;

		class FloatingPointTypeContext;

		class SizeTypeContext;

		class UnsignedIntegerPointerTypeContext;

		class VoidTypeContext;

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

				ConstantDeclarationContext* constantDeclaration();

				VariableDeclarationContext* variableDeclaration();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		DataContext* data();

		class ConstantDeclarationContext : public antlr4::ParserRuleContext
		{
			public:
				ConstantDeclarationContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				AccessModifierContext* accessModifier();

				TypeContext* type();

				antlr4::tree::TerminalNode* IDENTIFIER();

				LiteralExpressionContext* literalExpression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		ConstantDeclarationContext* constantDeclaration();

		class VariableDeclarationContext : public antlr4::ParserRuleContext
		{
			public:
				VariableDeclarationContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				AccessModifierContext* accessModifier();

				TypeContext* type();

				antlr4::tree::TerminalNode* IDENTIFIER();

				LiteralExpressionContext* literalExpression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		VariableDeclarationContext* variableDeclaration();

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

				AccessModifierContext* accessModifier();

				TypeContext* type();

				antlr4::tree::TerminalNode* IDENTIFIER();

				ParametersContext* parameters();

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

		class AccessModifierContext : public antlr4::ParserRuleContext
		{
			public:
				AccessModifierContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* PUBLIC();

				antlr4::tree::TerminalNode* PRIVATE();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		AccessModifierContext* accessModifier();

		class StatementContext : public antlr4::ParserRuleContext
		{
			public:
				StatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				ExpressionStatementContext* expressionStatement();

				LocalVariableDefinitionContext* localVariableDefinition();

				VariableAssignmentContext* variableAssignment();

				PrintStatementContext* printStatement();

				DeleteStatementContext* deleteStatement();

				ReturnStatementContext* returnStatement();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		StatementContext* statement();

		class ExpressionStatementContext : public antlr4::ParserRuleContext
		{
			public:
				ExpressionStatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				IndependentExpressionContext* independentExpression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		ExpressionStatementContext* expressionStatement();

		class LocalVariableDefinitionContext : public antlr4::ParserRuleContext
		{
			public:
				LocalVariableDefinitionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				TypeContext* type();

				antlr4::tree::TerminalNode* IDENTIFIER();

				ExpressionContext* expression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		LocalVariableDefinitionContext* localVariableDefinition();

		class VariableAssignmentContext : public antlr4::ParserRuleContext
		{
			public:
				VariableAssignmentContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* IDENTIFIER();

				ExpressionContext* expression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		VariableAssignmentContext* variableAssignment();

		class PrintStatementContext : public antlr4::ParserRuleContext
		{
			public:
				PrintStatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				ExpressionContext* expression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		PrintStatementContext* printStatement();

		class DeleteStatementContext : public antlr4::ParserRuleContext
		{
			public:
				DeleteStatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				ExpressionContext* expression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		DeleteStatementContext* deleteStatement();

		class ReturnStatementContext : public antlr4::ParserRuleContext
		{
			public:
				ReturnStatementContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				ExpressionContext* expression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		ReturnStatementContext* returnStatement();

		class ExpressionContext : public antlr4::ParserRuleContext
		{
			public:
				ExpressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				VariableAccessContext* variableAccess();

				AllocationContext* allocation();

				RoughCastContext* roughCast();

				SizeofTypeContext* sizeofType();

				SizeofExpressionContext* sizeofExpression();

				LiteralExpressionContext* literalExpression();

				IndependentExpressionContext* independentExpression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		ExpressionContext* expression();

		class IndependentExpressionContext : public antlr4::ParserRuleContext
		{
			public:
				IndependentExpressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				FunctionCallContext* functionCall();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		IndependentExpressionContext* independentExpression();

		class FunctionCallContext : public antlr4::ParserRuleContext
		{
			public:
				FunctionCallContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* IDENTIFIER();

				ArgumentsContext* arguments();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		FunctionCallContext* functionCall();

		class ArgumentsContext : public antlr4::ParserRuleContext
		{
			public:
				ArgumentsContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				std::vector<ExpressionContext*> expression();

				ExpressionContext* expression(size_t i);

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		ArgumentsContext* arguments();

		class VariableAccessContext : public antlr4::ParserRuleContext
		{
			public:
				VariableAccessContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* IDENTIFIER();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		VariableAccessContext* variableAccess();

		class AllocationContext : public antlr4::ParserRuleContext
		{
			public:
				AllocationContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				AllocatorContext* allocator();

				TypeContext* type();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		AllocationContext* allocation();

		class AllocatorContext : public antlr4::ParserRuleContext
		{
			public:
				AllocatorContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* DYNAMIC();

				antlr4::tree::TerminalNode* AUTOMATIC();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		AllocatorContext* allocator();

		class RoughCastContext : public antlr4::ParserRuleContext
		{
			public:
				RoughCastContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				TypeContext* type();

				ExpressionContext* expression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		RoughCastContext* roughCast();

		class SizeofTypeContext : public antlr4::ParserRuleContext
		{
			public:
				SizeofTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				TypeContext* type();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		SizeofTypeContext* sizeofType();

		class SizeofExpressionContext : public antlr4::ParserRuleContext
		{
			public:
				SizeofExpressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				ExpressionContext* expression();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		SizeofExpressionContext* sizeofExpression();

		class LiteralExpressionContext : public antlr4::ParserRuleContext
		{
			public:
				LiteralExpressionContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				StringLiteralContext* stringLiteral();

				ByteLiteralContext* byteLiteral();

				IntegerLiteralContext* integerLiteral();

				FloatingPointLiteralContext* floatingPointLiteral();

				BooleanLiteralContext* booleanLiteral();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		LiteralExpressionContext* literalExpression();

		class StringLiteralContext : public antlr4::ParserRuleContext
		{
			public:
				StringLiteralContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* STRING();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		StringLiteralContext* stringLiteral();

		class ByteLiteralContext : public antlr4::ParserRuleContext
		{
			public:
				ByteLiteralContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* BYTE();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		ByteLiteralContext* byteLiteral();

		class IntegerLiteralContext : public antlr4::ParserRuleContext
		{
			public:
				IntegerLiteralContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				UnsignedIntegerContext* unsignedInteger();

				SignedIntegerContext* signedInteger();

				SpecialIntegerContext* specialInteger();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		IntegerLiteralContext* integerLiteral();

		class UnsignedIntegerContext : public antlr4::ParserRuleContext
		{
			public:
				UnsignedIntegerContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				std::vector<antlr4::tree::TerminalNode*> INTEGER();

				antlr4::tree::TerminalNode* INTEGER(size_t i);

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		UnsignedIntegerContext* unsignedInteger();

		class SignedIntegerContext : public antlr4::ParserRuleContext
		{
			public:
				SignedIntegerContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* SIGNED_INTEGER();

				antlr4::tree::TerminalNode* INTEGER();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		SignedIntegerContext* signedInteger();

		class SpecialIntegerContext : public antlr4::ParserRuleContext
		{
			public:
				SpecialIntegerContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* HEX_INTEGER();

				antlr4::tree::TerminalNode* INTEGER();

				antlr4::tree::TerminalNode* BIN_INTEGER();

				antlr4::tree::TerminalNode* OCT_INTEGER();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		SpecialIntegerContext* specialInteger();

		class FloatingPointLiteralContext : public antlr4::ParserRuleContext
		{
			public:
				FloatingPointLiteralContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* HALF();

				antlr4::tree::TerminalNode* SINGLE();

				antlr4::tree::TerminalNode* DOUBLE();

				antlr4::tree::TerminalNode* QUAD();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		FloatingPointLiteralContext* floatingPointLiteral();

		class BooleanLiteralContext : public antlr4::ParserRuleContext
		{
			public:
				BooleanLiteralContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* TRUE();

				antlr4::tree::TerminalNode* FALSE();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		BooleanLiteralContext* booleanLiteral();

		class TypeContext : public antlr4::ParserRuleContext
		{
			public:
				TypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				TypeContext() = default;

				void copyFrom(TypeContext* context);

				using antlr4::ParserRuleContext::copyFrom;

				virtual size_t getRuleIndex() const override;

		};

		class IntegerContext : public TypeContext
		{
			public:
				IntegerContext(TypeContext* ctx);

				IntegerTypeContext* integerType();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
		};

		class ArrayContext : public TypeContext
		{
			public:
				ArrayContext(TypeContext* ctx);

				ArrayTypeContext* arrayType();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
		};

		class KeywordContext : public TypeContext
		{
			public:
				KeywordContext(TypeContext* ctx);

				KeywordTypeContext* keywordType();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
		};

		class PointerContext : public TypeContext
		{
			public:
				PointerContext(TypeContext* ctx);

				TypeContext* type();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;
		};

		TypeContext* type();

		TypeContext* type(int precedence);

		class IntegerTypeContext : public antlr4::ParserRuleContext
		{
			public:
				IntegerTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* NATIVE_INTEGER_TYPE();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		IntegerTypeContext* integerType();

		class ArrayTypeContext : public antlr4::ParserRuleContext
		{
			public:
				ArrayTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* INTEGER();

				TypeContext* type();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		ArrayTypeContext* arrayType();

		class KeywordTypeContext : public antlr4::ParserRuleContext
		{
			public:
				KeywordTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				FloatingPointTypeContext* floatingPointType();

				SizeTypeContext* sizeType();

				UnsignedIntegerPointerTypeContext* unsignedIntegerPointerType();

				VoidTypeContext* voidType();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		KeywordTypeContext* keywordType();

		class FloatingPointTypeContext : public antlr4::ParserRuleContext
		{
			public:
				FloatingPointTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				antlr4::tree::TerminalNode* HALF_TYPE();

				antlr4::tree::TerminalNode* SINGLE_TYPE();

				antlr4::tree::TerminalNode* DOUBLE_TYPE();

				antlr4::tree::TerminalNode* QUAD_TYPE();

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		FloatingPointTypeContext* floatingPointType();

		class SizeTypeContext : public antlr4::ParserRuleContext
		{
			public:
				SizeTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		SizeTypeContext* sizeType();

		class UnsignedIntegerPointerTypeContext : public antlr4::ParserRuleContext
		{
			public:
				UnsignedIntegerPointerTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		UnsignedIntegerPointerTypeContext* unsignedIntegerPointerType();

		class VoidTypeContext : public antlr4::ParserRuleContext
		{
			public:
				VoidTypeContext(antlr4::ParserRuleContext* parent, size_t invokingState);

				virtual size_t getRuleIndex() const override;

				virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor* visitor) override;

		};

		VoidTypeContext* voidType();

		virtual bool sempred(antlr4::RuleContext* _localctx, size_t ruleIndex, size_t predicateIndex) override;

		bool typeSempred(TypeContext* _localctx, size_t predicateIndex);

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

