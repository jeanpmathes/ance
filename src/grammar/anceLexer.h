
// Generated from ./src/grammar/ance.g4 by ANTLR 4.8

#pragma once

#include "antlr4-runtime.h"

class anceLexer : public antlr4::Lexer
{
	public:
		enum
		{
				T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7,
				T__7 = 8, T__8 = 9, NATIVE_INTEGER_TYPE = 10, HALF_TYPE = 11, SINGLE_TYPE = 12,
				DOUBLE_TYPE = 13, QUAD_TYPE = 14, SIGNED_INTEGER = 15, HEX_INTEGER = 16,
				BIN_INTEGER = 17, OCT_INTEGER = 18, HALF = 19, SINGLE = 20, DOUBLE = 21,
				QUAD = 22, DECIMAL = 23, STRING = 24, INTEGER = 25, SIZEOF = 26, SIZE = 27,
				UIPTR = 28, PRINT = 29, RETURN = 30, CONST = 31, PUBLIC = 32, PRIVATE = 33,
				VOID = 34, IDENTIFIER = 35, DEFINITION = 36, ASSIGNMENT = 37, WHITESPACE = 38
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

