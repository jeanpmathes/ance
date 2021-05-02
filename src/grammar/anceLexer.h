
// Generated from ./src/grammar/ance.g4 by ANTLR 4.8

#pragma once

#include "antlr4-runtime.h"

class anceLexer : public antlr4::Lexer
{
	public:
		enum
		{
				T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7,
				T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, NATIVE_INTEGER_TYPE = 12,
				HALF_TYPE = 13, SINGLE_TYPE = 14, DOUBLE_TYPE = 15, QUAD_TYPE = 16,
				SIGNED_INTEGER = 17, HEX_INTEGER = 18, BIN_INTEGER = 19, OCT_INTEGER = 20,
				HALF = 21, SINGLE = 22, DOUBLE = 23, QUAD = 24, DECIMAL = 25, STRING = 26,
				BYTE = 27, INTEGER = 28, DYNAMIC = 29, AUTOMATIC = 30, TRUE = 31, FALSE = 32,
				SIZEOF = 33, SIZE = 34, UIPTR = 35, PRINT = 36, RETURN = 37, CONST = 38,
				PUBLIC = 39, PRIVATE = 40, VOID = 41, IDENTIFIER = 42, DEFINITION = 43,
				ASSIGNMENT = 44, WHITESPACE = 45, BLOCK_COMMENT = 46, LINE_COMMENT = 47
		};

		anceLexer(antlr4::CharStream* input);

		~anceLexer();

		virtual std::string getGrammarFileName() const override;

		virtual const std::vector<std::string>& getRuleNames() const override;

		virtual const std::vector<std::string>& getChannelNames() const override;

		virtual const std::vector<std::string>& getModeNames() const override;

		virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
		virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

		virtual const std::vector<uint16_t> getSerializedATN() const override;

		virtual const antlr4::atn::ATN& getATN() const override;

	private:
		static std::vector<antlr4::dfa::DFA> _decisionToDFA;
		static antlr4::atn::PredictionContextCache _sharedContextCache;
		static std::vector<std::string> _ruleNames;
		static std::vector<std::string> _tokenNames;
		static std::vector<std::string> _channelNames;
		static std::vector<std::string> _modeNames;

		static std::vector<std::string> _literalNames;
		static std::vector<std::string> _symbolicNames;
		static antlr4::dfa::Vocabulary _vocabulary;
		static antlr4::atn::ATN _atn;
		static std::vector<uint16_t> _serializedATN;


		// Individual action functions triggered by action() above.

		// Individual semantic predicate functions triggered by sempred() above.

		struct Initializer
		{
				Initializer();
		};

		static Initializer _init;
};

