
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1

#include "anceVisitor.h"

#include "anceParser.h"

using namespace antlrcpp;

using namespace antlr4;

namespace
{

    struct AnceParserStaticData final
    {
        AnceParserStaticData(std::vector<std::string> ruleNames, std::vector<std::string> literalNames, std::vector<std::string> symbolicNames)
            : ruleNames(std::move(ruleNames))
            , literalNames(std::move(literalNames))
            , symbolicNames(std::move(symbolicNames))
            , vocabulary(this->literalNames, this->symbolicNames)
        {}

        AnceParserStaticData(AnceParserStaticData const&)            = delete;
        AnceParserStaticData(AnceParserStaticData&&)                 = delete;
        AnceParserStaticData& operator=(AnceParserStaticData const&) = delete;
        AnceParserStaticData& operator=(AnceParserStaticData&&)      = delete;

        std::vector<antlr4::dfa::DFA>       decisionToDFA;
        antlr4::atn::PredictionContextCache sharedContextCache;
        std::vector<std::string> const      ruleNames;
        std::vector<std::string> const      literalNames;
        std::vector<std::string> const      symbolicNames;
        antlr4::dfa::Vocabulary const       vocabulary;
        antlr4::atn::SerializedATNView      serializedATN;
        std::unique_ptr<antlr4::atn::ATN>   atn;
    };

    std::once_flag        anceParserOnceFlag;
    AnceParserStaticData* anceParserStaticData = nullptr;

    void anceParserInitialize()
    {
        assert(anceParserStaticData == nullptr);
        auto staticData = std::make_unique<AnceParserStaticData>(
            std::vector<std::string> {"unorderedScopeFile",
                                      "orderedScopeFile",
                                      "declaration",
                                      "statement",
                                      "expression",
                                      "unary",
                                      "literal",
                                      "boolean",
                                      "entity",
                                      "parameter",
                                      "assigner",
                                      "accessModifier"},
            std::vector<std::string> {"",           "'do'",     "'cmp'",     "':'",      "'let'", "'if'",   "'then'", "'else'", "'loop'",  "'break'",
                                      "'continue'", "'return'", "'while'",   "','",      "'=>'",  "'here'", "'not'",  "'true'", "'false'", "'<:'",
                                      "':='",       "'public'", "'private'", "'extern'", "",      "",       "",       "'\\'",   "';'",     "",
                                      "",           "",         "'('",       "')'",      "'{'",   "'}'",    "'['",    "']'",    "'<'",     "'>'"},
            std::vector<std::string> {"",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "",
                                      "IDENTIFIER",
                                      "INTEGER",
                                      "STRING",
                                      "LAMBDA",
                                      "SEMICOLON",
                                      "WHITESPACE",
                                      "BLOCK_COMMENT",
                                      "LINE_COMMENT",
                                      "BRACKET_OPEN",
                                      "BRACKET_CLOSE",
                                      "CURLY_BRACKET_OPEN",
                                      "CURLY_BRACKET_CLOSE",
                                      "SQUARE_BRACKET_OPEN",
                                      "SQUARE_BRACKET_CLOSE",
                                      "POINTY_BRACKET_OPEN",
                                      "POINTY_BRACKET_CLOSE",
                                      "ERROR_CHAR"});
        static int32_t const serializedATNSegment[] = {
            4,   1,   40,  186, 2,   0,   7,   0,  2,  1,   7,  1,   2,   2,  7,  2,  2,   3,   7,   3,   2,  4,   7,  4,   2,   5,   7,   5,   2,   6,
            7,   6,   2,   7,   7,   7,   2,   8,  7,  8,   2,  9,   7,   9,  2,  10, 7,   10,  2,   11,  7,  11,  1,  0,   5,   0,   26,  8,   0,   10,
            0,   12,  0,   29,  9,   0,   1,   0,  1,  0,   1,  1,   1,   1,  1,  1,  1,   2,   1,   2,   1,  2,   1,  2,   1,   2,   1,   2,   1,   2,
            1,   2,   1,   2,   1,   2,   3,   2,  46, 8,   2,  1,   2,   1,  2,  3,  2,   50,  8,   2,   1,  3,   1,  3,   5,   3,   54,  8,   3,   10,
            3,   12,  3,   57,  9,   3,   1,   3,  1,  3,   1,  3,   1,   3,  1,  3,  1,   3,   1,   3,   1,  3,   1,  3,   1,   3,   1,   3,   3,   3,
            70,  8,   3,   1,   3,   1,   3,   1,  3,  1,   3,  1,   3,   1,  3,  1,  3,   1,   3,   1,   3,  1,   3,  1,   3,   1,   3,   1,   3,   3,
            3,   85,  8,   3,   1,   3,   1,   3,  1,  3,   1,  3,   1,   3,  1,  3,  1,   3,   1,   3,   3,  3,   95, 8,   3,   1,   3,   1,   3,   1,
            3,   1,   3,   1,   3,   1,   3,   3,  3,  103, 8,  3,   1,   4,  1,  4,  1,   4,   1,   4,   1,  4,   5,  4,   110, 8,   4,   10,  4,   12,
            4,   113, 9,   4,   3,   4,   115, 8,  4,  1,   4,  1,   4,   1,  4,  1,  4,   1,   4,   3,   4,  122, 8,  4,   1,   4,   1,   4,   1,   4,
            1,   4,   5,   4,   128, 8,   4,   10, 4,  12,  4,  131, 9,   4,  3,  4,  133, 8,   4,   1,   4,  1,   4,  1,   4,   1,   4,   1,   4,   1,
            4,   1,   4,   5,   4,   142, 8,   4,  10, 4,   12, 4,   145, 9,  4,  1,  4,   3,   4,   148, 8,  4,   1,  4,   1,   4,   1,   4,   1,   4,
            1,   4,   1,   4,   3,   4,   156, 8,  4,  1,   5,  1,   5,   1,  6,  1,  6,   1,   6,   1,   6,  1,   6,  3,   6,   165, 8,   6,   1,   7,
            1,   7,   3,   7,   169, 8,   7,   1,  8,  1,   8,  1,   9,   1,  9,  1,  9,   1,   9,   1,   10, 1,   10, 3,   10,  179, 8,   10,  1,   11,
            1,   11,  1,   11,  3,   11,  184, 8,  11, 1,   11, 0,   0,   12, 0,  2,  4,   6,   8,   10,  12, 14,  16, 18,  20,  22,  0,   0,   208, 0,
            27,  1,   0,   0,   0,   2,   32,  1,  0,  0,   0,  4,   49,  1,  0,  0,  0,   6,   102, 1,   0,  0,   0,  8,   155, 1,   0,   0,   0,   10,
            157, 1,   0,   0,   0,   12,  164, 1,  0,  0,   0,  14,  168, 1,  0,  0,  0,   16,  170, 1,   0,  0,   0,  18,  172, 1,   0,   0,   0,   20,
            178, 1,   0,   0,   0,   22,  183, 1,  0,  0,   0,  24,  26,  3,  4,  2,  0,   25,  24,  1,   0,  0,   0,  26,  29,  1,   0,   0,   0,   27,
            25,  1,   0,   0,   0,   27,  28,  1,  0,  0,   0,  28,  30,  1,  0,  0,  0,   29,  27,  1,   0,  0,   0,  30,  31,  5,   0,   0,   1,   31,
            1,   1,   0,   0,   0,   32,  33,  3,  6,  3,   0,  33,  34,  5,  0,  0,  1,   34,  3,   1,   0,  0,   0,  35,  36,  5,   1,   0,   0,   36,
            50,  3,   6,   3,   0,   37,  38,  3,  22, 11,  0,  38,  39,  5,  2,  0,  0,   39,  40,  5,   24, 0,   0,  40,  41,  5,   3,   0,   0,   41,
            45,  3,   8,   4,   0,   42,  43,  3,  20, 10,  0,  43,  44,  3,  8,  4,  0,   44,  46,  1,   0,  0,   0,  45,  42,  1,   0,   0,   0,   45,
            46,  1,   0,   0,   0,   46,  47,  1,  0,  0,   0,  47,  48,  5,  28, 0,  0,   48,  50,  1,   0,  0,   0,  49,  35,  1,   0,   0,   0,   49,
            37,  1,   0,   0,   0,   50,  5,   1,  0,  0,   0,  51,  55,  5,  34, 0,  0,   52,  54,  3,   6,  3,   0,  53,  52,  1,   0,   0,   0,   54,
            57,  1,   0,   0,   0,   55,  53,  1,  0,  0,   0,  55,  56,  1,  0,  0,  0,   56,  58,  1,   0,  0,   0,  57,  55,  1,   0,   0,   0,   58,
            103, 5,   35,  0,   0,   59,  60,  3,  8,  4,   0,  60,  61,  5,  28, 0,  0,   61,  103, 1,   0,  0,   0,  62,  63,  5,   4,   0,   0,   63,
            64,  5,   24,  0,   0,   64,  65,  5,  3,  0,   0,  65,  69,  3,  8,  4,  0,   66,  67,  3,   20, 10,  0,  67,  68,  3,   8,   4,   0,   68,
            70,  1,   0,   0,   0,   69,  66,  1,  0,  0,   0,  69,  70,  1,  0,  0,  0,   70,  71,  1,   0,  0,   0,  71,  72,  5,   28,  0,   0,   72,
            103, 1,   0,   0,   0,   73,  74,  3,  16, 8,   0,  74,  75,  3,  20, 10, 0,   75,  76,  3,   8,  4,   0,  76,  77,  5,   28,  0,   0,   77,
            103, 1,   0,   0,   0,   78,  79,  5,  5,  0,   0,  79,  80,  3,  8,  4,  0,   80,  81,  5,   6,  0,   0,  81,  84,  3,   6,   3,   0,   82,
            83,  5,   7,   0,   0,   83,  85,  3,  6,  3,   0,  84,  82,  1,  0,  0,  0,   84,  85,  1,   0,  0,   0,  85,  103, 1,   0,   0,   0,   86,
            87,  5,   8,   0,   0,   87,  103, 3,  6,  3,   0,  88,  89,  5,  9,  0,  0,   89,  103, 5,   28, 0,   0,  90,  91,  5,   10,  0,   0,   91,
            103, 5,   28,  0,   0,   92,  94,  5,  11, 0,   0,  93,  95,  3,  8,  4,  0,   94,  93,  1,   0,  0,   0,  94,  95,  1,   0,   0,   0,   95,
            96,  1,   0,   0,   0,   96,  103, 5,  28, 0,   0,  97,  98,  5,  12, 0,  0,   98,  99,  3,   8,  4,   0,  99,  100, 5,   1,   0,   0,   100,
            101, 3,   6,   3,   0,   101, 103, 1,  0,  0,   0,  102, 51,  1,  0,  0,  0,   102, 59,  1,   0,  0,   0,  102, 62,  1,   0,   0,   0,   102,
            73,  1,   0,   0,   0,   102, 78,  1,  0,  0,   0,  102, 86,  1,  0,  0,  0,   102, 88,  1,   0,  0,   0,  102, 90,  1,   0,   0,   0,   102,
            92,  1,   0,   0,   0,   102, 97,  1,  0,  0,   0,  103, 7,   1,  0,  0,  0,   104, 105, 3,   16, 8,   0,  105, 114, 5,   32,  0,   0,   106,
            111, 3,   8,   4,   0,   107, 108, 5,  13, 0,   0,  108, 110, 3,  8,  4,  0,   109, 107, 1,   0,  0,   0,  110, 113, 1,   0,   0,   0,   111,
            109, 1,   0,   0,   0,   111, 112, 1,  0,  0,   0,  112, 115, 1,  0,  0,  0,   113, 111, 1,   0,  0,   0,  114, 106, 1,   0,   0,   0,   114,
            115, 1,   0,   0,   0,   115, 116, 1,  0,  0,   0,  116, 117, 5,  33, 0,  0,   117, 156, 1,   0,  0,   0,  118, 121, 5,   27,  0,   0,   119,
            120, 5,   36,  0,   0,   120, 122, 5,  37, 0,   0,  121, 119, 1,  0,  0,  0,   121, 122, 1,   0,  0,   0,  122, 123, 1,   0,   0,   0,   123,
            132, 5,   32,  0,   0,   124, 129, 3,  18, 9,   0,  125, 126, 5,  13, 0,  0,   126, 128, 3,   18, 9,   0,  127, 125, 1,   0,   0,   0,   128,
            131, 1,   0,   0,   0,   129, 127, 1,  0,  0,   0,  129, 130, 1,  0,  0,  0,   130, 133, 1,   0,  0,   0,  131, 129, 1,   0,   0,   0,   132,
            124, 1,   0,   0,   0,   132, 133, 1,  0,  0,   0,  133, 134, 1,  0,  0,  0,   134, 135, 5,   33, 0,   0,  135, 136, 5,   3,   0,   0,   136,
            147, 3,   8,   4,   0,   137, 138, 5,  14, 0,   0,  138, 148, 3,  8,  4,  0,   139, 143, 5,   34, 0,   0,  140, 142, 3,   6,   3,   0,   141,
            140, 1,   0,   0,   0,   142, 145, 1,  0,  0,   0,  143, 141, 1,  0,  0,  0,   143, 144, 1,   0,  0,   0,  144, 146, 1,   0,   0,   0,   145,
            143, 1,   0,   0,   0,   146, 148, 5,  35, 0,   0,  147, 137, 1,  0,  0,  0,   147, 139, 1,   0,  0,   0,  148, 156, 1,   0,   0,   0,   149,
            156, 3,   16,  8,   0,   150, 156, 3,  12, 6,   0,  151, 152, 3,  10, 5,  0,   152, 153, 3,   8,  4,   0,  153, 156, 1,   0,   0,   0,   154,
            156, 5,   15,  0,   0,   155, 104, 1,  0,  0,   0,  155, 118, 1,  0,  0,  0,   155, 149, 1,   0,  0,   0,  155, 150, 1,   0,   0,   0,   155,
            151, 1,   0,   0,   0,   155, 154, 1,  0,  0,   0,  156, 9,   1,  0,  0,  0,   157, 158, 5,   16, 0,   0,  158, 11,  1,   0,   0,   0,   159,
            165, 3,   14,  7,   0,   160, 165, 5,  25, 0,   0,  161, 162, 5,  32, 0,  0,   162, 165, 5,   33, 0,   0,  163, 165, 5,   26,  0,   0,   164,
            159, 1,   0,   0,   0,   164, 160, 1,  0,  0,   0,  164, 161, 1,  0,  0,  0,   164, 163, 1,   0,  0,   0,  165, 13,  1,   0,   0,   0,   166,
            169, 5,   17,  0,   0,   167, 169, 5,  18, 0,   0,  168, 166, 1,  0,  0,  0,   168, 167, 1,   0,  0,   0,  169, 15,  1,   0,   0,   0,   170,
            171, 5,   24,  0,   0,   171, 17,  1,  0,  0,   0,  172, 173, 5,  24, 0,  0,   173, 174, 5,   3,  0,   0,  174, 175, 3,   8,   4,   0,   175,
            19,  1,   0,   0,   0,   176, 179, 5,  19, 0,   0,  177, 179, 5,  20, 0,  0,   178, 176, 1,   0,  0,   0,  178, 177, 1,   0,   0,   0,   179,
            21,  1,   0,   0,   0,   180, 184, 5,  21, 0,   0,  181, 184, 5,  22, 0,  0,   182, 184, 5,   23, 0,   0,  183, 180, 1,   0,   0,   0,   183,
            181, 1,   0,   0,   0,   183, 182, 1,  0,  0,   0,  184, 23,  1,  0,  0,  0,   20,  27,  45,  49, 55,  69, 84,  94,  102, 111, 114, 121, 129,
            132, 143, 147, 155, 164, 168, 178, 183};
        staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

        antlr4::atn::ATNDeserializer deserializer;
        staticData->atn = deserializer.deserialize(staticData->serializedATN);

        size_t const count = staticData->atn->getNumberOfDecisions();
        staticData->decisionToDFA.reserve(count);
        for (size_t i = 0; i < count; i++)
        {
            staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
        }
        anceParserStaticData = staticData.release();
    }

}

anceParser::anceParser(TokenStream* input) : anceParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

anceParser::anceParser(TokenStream* input, antlr4::atn::ParserATNSimulatorOptions const& options) : Parser(input)
{
    anceParser::initialize();
    _interpreter =
        new atn::ParserATNSimulator(this, *anceParserStaticData->atn, anceParserStaticData->decisionToDFA, anceParserStaticData->sharedContextCache, options);
}

anceParser::~anceParser()
{
    delete _interpreter;
}

atn::ATN const& anceParser::getATN() const
{
    return *anceParserStaticData->atn;
}

std::string anceParser::getGrammarFileName() const
{
    return "ance.g4";
}

std::vector<std::string> const& anceParser::getRuleNames() const
{
    return anceParserStaticData->ruleNames;
}

dfa::Vocabulary const& anceParser::getVocabulary() const
{
    return anceParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView anceParser::getSerializedATN() const
{
    return anceParserStaticData->serializedATN;
}

//----------------- UnorderedScopeFileContext ------------------------------------------------------------------

anceParser::UnorderedScopeFileContext::UnorderedScopeFileContext(ParserRuleContext* parent, size_t invokingState) : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* anceParser::UnorderedScopeFileContext::EOF()
{
    return getToken(anceParser::EOF, 0);
}

std::vector<anceParser::DeclarationContext*> anceParser::UnorderedScopeFileContext::declaration()
{
    return getRuleContexts<anceParser::DeclarationContext>();
}

anceParser::DeclarationContext* anceParser::UnorderedScopeFileContext::declaration(size_t i)
{
    return getRuleContext<anceParser::DeclarationContext>(i);
}

size_t anceParser::UnorderedScopeFileContext::getRuleIndex() const
{
    return anceParser::RuleUnorderedScopeFile;
}

std::any anceParser::UnorderedScopeFileContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitUnorderedScopeFile(this);
    else return visitor->visitChildren(this);
}

anceParser::UnorderedScopeFileContext* anceParser::unorderedScopeFile()
{
    UnorderedScopeFileContext* _localctx = _tracker.createInstance<UnorderedScopeFileContext>(_ctx, getState());
    enterRule(_localctx, 0, anceParser::RuleUnorderedScopeFile);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(27);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (
            (((_la & ~0x3fULL) == 0)
             && ((1ULL << _la) & ((1ULL << anceParser::T__0) | (1ULL << anceParser::T__20) | (1ULL << anceParser::T__21) | (1ULL << anceParser::T__22))) != 0))
        {
            setState(24);
            declaration();
            setState(29);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(30);
        match(anceParser::EOF);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- OrderedScopeFileContext ------------------------------------------------------------------

anceParser::OrderedScopeFileContext::OrderedScopeFileContext(ParserRuleContext* parent, size_t invokingState) : ParserRuleContext(parent, invokingState) {}

anceParser::StatementContext* anceParser::OrderedScopeFileContext::statement()
{
    return getRuleContext<anceParser::StatementContext>(0);
}

tree::TerminalNode* anceParser::OrderedScopeFileContext::EOF()
{
    return getToken(anceParser::EOF, 0);
}

size_t anceParser::OrderedScopeFileContext::getRuleIndex() const
{
    return anceParser::RuleOrderedScopeFile;
}

std::any anceParser::OrderedScopeFileContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitOrderedScopeFile(this);
    else return visitor->visitChildren(this);
}

anceParser::OrderedScopeFileContext* anceParser::orderedScopeFile()
{
    OrderedScopeFileContext* _localctx = _tracker.createInstance<OrderedScopeFileContext>(_ctx, getState());
    enterRule(_localctx, 2, anceParser::RuleOrderedScopeFile);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(32);
        statement();
        setState(33);
        match(anceParser::EOF);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

anceParser::DeclarationContext::DeclarationContext(ParserRuleContext* parent, size_t invokingState) : ParserRuleContext(parent, invokingState) {}

size_t anceParser::DeclarationContext::getRuleIndex() const
{
    return anceParser::RuleDeclaration;
}

void anceParser::DeclarationContext::copyFrom(DeclarationContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

anceParser::AccessModifierContext* anceParser::VariableDeclarationContext::accessModifier()
{
    return getRuleContext<anceParser::AccessModifierContext>(0);
}

tree::TerminalNode* anceParser::VariableDeclarationContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::VariableDeclarationContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

std::vector<anceParser::ExpressionContext*> anceParser::VariableDeclarationContext::expression()
{
    return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::VariableDeclarationContext::expression(size_t i)
{
    return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::AssignerContext* anceParser::VariableDeclarationContext::assigner()
{
    return getRuleContext<anceParser::AssignerContext>(0);
}

anceParser::VariableDeclarationContext::VariableDeclarationContext(DeclarationContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitVariableDeclaration(this);
    else return visitor->visitChildren(this);
}
//----------------- RunnableDeclarationContext ------------------------------------------------------------------

anceParser::StatementContext* anceParser::RunnableDeclarationContext::statement()
{
    return getRuleContext<anceParser::StatementContext>(0);
}

anceParser::RunnableDeclarationContext::RunnableDeclarationContext(DeclarationContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::RunnableDeclarationContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitRunnableDeclaration(this);
    else return visitor->visitChildren(this);
}
anceParser::DeclarationContext* anceParser::declaration()
{
    DeclarationContext* _localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
    enterRule(_localctx, 4, anceParser::RuleDeclaration);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(49);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__0:
            {
                _localctx = _tracker.createInstance<anceParser::RunnableDeclarationContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(35);
                match(anceParser::T__0);
                setState(36);
                statement();
                break;
            }

            case anceParser::T__20:
            case anceParser::T__21:
            case anceParser::T__22:
            {
                _localctx = _tracker.createInstance<anceParser::VariableDeclarationContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(37);
                accessModifier();
                setState(38);
                match(anceParser::T__1);
                setState(39);
                match(anceParser::IDENTIFIER);
                setState(40);
                match(anceParser::T__2);
                setState(41);
                antlrcpp::downCast<VariableDeclarationContext*>(_localctx)->varType = expression();
                setState(45);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == anceParser::T__18

                    || _la == anceParser::T__19)
                {
                    setState(42);
                    assigner();
                    setState(43);
                    antlrcpp::downCast<VariableDeclarationContext*>(_localctx)->assigned = expression();
                }
                setState(47);
                match(anceParser::SEMICOLON);
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

anceParser::StatementContext::StatementContext(ParserRuleContext* parent, size_t invokingState) : ParserRuleContext(parent, invokingState) {}

size_t anceParser::StatementContext::getRuleIndex() const
{
    return anceParser::RuleStatement;
}

void anceParser::StatementContext::copyFrom(StatementContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- BreakStatementContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::BreakStatementContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

anceParser::BreakStatementContext::BreakStatementContext(StatementContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::BreakStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitBreakStatement(this);
    else return visitor->visitChildren(this);
}
//----------------- IfStatementContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::IfStatementContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

std::vector<anceParser::StatementContext*> anceParser::IfStatementContext::statement()
{
    return getRuleContexts<anceParser::StatementContext>();
}

anceParser::StatementContext* anceParser::IfStatementContext::statement(size_t i)
{
    return getRuleContext<anceParser::StatementContext>(i);
}

anceParser::IfStatementContext::IfStatementContext(StatementContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::IfStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitIfStatement(this);
    else return visitor->visitChildren(this);
}
//----------------- AssignmentStatementContext ------------------------------------------------------------------

anceParser::EntityContext* anceParser::AssignmentStatementContext::entity()
{
    return getRuleContext<anceParser::EntityContext>(0);
}

anceParser::AssignerContext* anceParser::AssignmentStatementContext::assigner()
{
    return getRuleContext<anceParser::AssignerContext>(0);
}

anceParser::ExpressionContext* anceParser::AssignmentStatementContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

tree::TerminalNode* anceParser::AssignmentStatementContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

anceParser::AssignmentStatementContext::AssignmentStatementContext(StatementContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::AssignmentStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitAssignmentStatement(this);
    else return visitor->visitChildren(this);
}
//----------------- ExpressionStatementContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::ExpressionStatementContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

tree::TerminalNode* anceParser::ExpressionStatementContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

anceParser::ExpressionStatementContext::ExpressionStatementContext(StatementContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitExpressionStatement(this);
    else return visitor->visitChildren(this);
}
//----------------- ReturnStatementContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::ReturnStatementContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

anceParser::ExpressionContext* anceParser::ReturnStatementContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::ReturnStatementContext::ReturnStatementContext(StatementContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::ReturnStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitReturnStatement(this);
    else return visitor->visitChildren(this);
}
//----------------- BlockStatementContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::BlockStatementContext::CURLY_BRACKET_OPEN()
{
    return getToken(anceParser::CURLY_BRACKET_OPEN, 0);
}

tree::TerminalNode* anceParser::BlockStatementContext::CURLY_BRACKET_CLOSE()
{
    return getToken(anceParser::CURLY_BRACKET_CLOSE, 0);
}

std::vector<anceParser::StatementContext*> anceParser::BlockStatementContext::statement()
{
    return getRuleContexts<anceParser::StatementContext>();
}

anceParser::StatementContext* anceParser::BlockStatementContext::statement(size_t i)
{
    return getRuleContext<anceParser::StatementContext>(i);
}

anceParser::BlockStatementContext::BlockStatementContext(StatementContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::BlockStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitBlockStatement(this);
    else return visitor->visitChildren(this);
}
//----------------- LoopStatementContext ------------------------------------------------------------------

anceParser::StatementContext* anceParser::LoopStatementContext::statement()
{
    return getRuleContext<anceParser::StatementContext>(0);
}

anceParser::LoopStatementContext::LoopStatementContext(StatementContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::LoopStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitLoopStatement(this);
    else return visitor->visitChildren(this);
}
//----------------- WhileStatementContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::WhileStatementContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::StatementContext* anceParser::WhileStatementContext::statement()
{
    return getRuleContext<anceParser::StatementContext>(0);
}

anceParser::WhileStatementContext::WhileStatementContext(StatementContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::WhileStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitWhileStatement(this);
    else return visitor->visitChildren(this);
}
//----------------- LetStatementContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::LetStatementContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::LetStatementContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

std::vector<anceParser::ExpressionContext*> anceParser::LetStatementContext::expression()
{
    return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::LetStatementContext::expression(size_t i)
{
    return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::AssignerContext* anceParser::LetStatementContext::assigner()
{
    return getRuleContext<anceParser::AssignerContext>(0);
}

anceParser::LetStatementContext::LetStatementContext(StatementContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::LetStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitLetStatement(this);
    else return visitor->visitChildren(this);
}
//----------------- ContinueStatementContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::ContinueStatementContext::SEMICOLON()
{
    return getToken(anceParser::SEMICOLON, 0);
}

anceParser::ContinueStatementContext::ContinueStatementContext(StatementContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::ContinueStatementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitContinueStatement(this);
    else return visitor->visitChildren(this);
}
anceParser::StatementContext* anceParser::statement()
{
    StatementContext* _localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
    enterRule(_localctx, 6, anceParser::RuleStatement);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(102);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx))
        {
            case 1:
            {
                _localctx = _tracker.createInstance<anceParser::BlockStatementContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(51);
                match(anceParser::CURLY_BRACKET_OPEN);
                setState(55);
                _errHandler->sync(this);
                _la = _input->LA(1);
                while ((((_la & ~0x3fULL) == 0)
                        && ((1ULL << _la)
                            & ((1ULL << anceParser::T__3) | (1ULL << anceParser::T__4) | (1ULL << anceParser::T__7) | (1ULL << anceParser::T__8)
                               | (1ULL << anceParser::T__9) | (1ULL << anceParser::T__10) | (1ULL << anceParser::T__11) | (1ULL << anceParser::T__14)
                               | (1ULL << anceParser::T__15) | (1ULL << anceParser::T__16) | (1ULL << anceParser::T__17) | (1ULL << anceParser::IDENTIFIER)
                               | (1ULL << anceParser::INTEGER) | (1ULL << anceParser::STRING) | (1ULL << anceParser::LAMBDA)
                               | (1ULL << anceParser::BRACKET_OPEN) | (1ULL << anceParser::CURLY_BRACKET_OPEN)))
                               != 0))
                {
                    setState(52);
                    statement();
                    setState(57);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                }
                setState(58);
                match(anceParser::CURLY_BRACKET_CLOSE);
                break;
            }

            case 2:
            {
                _localctx = _tracker.createInstance<anceParser::ExpressionStatementContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(59);
                expression();
                setState(60);
                match(anceParser::SEMICOLON);
                break;
            }

            case 3:
            {
                _localctx = _tracker.createInstance<anceParser::LetStatementContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(62);
                match(anceParser::T__3);
                setState(63);
                match(anceParser::IDENTIFIER);
                setState(64);
                match(anceParser::T__2);
                setState(65);
                antlrcpp::downCast<LetStatementContext*>(_localctx)->varType = expression();
                setState(69);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == anceParser::T__18

                    || _la == anceParser::T__19)
                {
                    setState(66);
                    assigner();
                    setState(67);
                    antlrcpp::downCast<LetStatementContext*>(_localctx)->assigned = expression();
                }
                setState(71);
                match(anceParser::SEMICOLON);
                break;
            }

            case 4:
            {
                _localctx = _tracker.createInstance<anceParser::AssignmentStatementContext>(_localctx);
                enterOuterAlt(_localctx, 4);
                setState(73);
                entity();
                setState(74);
                assigner();
                setState(75);
                expression();
                setState(76);
                match(anceParser::SEMICOLON);
                break;
            }

            case 5:
            {
                _localctx = _tracker.createInstance<anceParser::IfStatementContext>(_localctx);
                enterOuterAlt(_localctx, 5);
                setState(78);
                match(anceParser::T__4);
                setState(79);
                expression();
                setState(80);
                match(anceParser::T__5);
                setState(81);
                antlrcpp::downCast<IfStatementContext*>(_localctx)->trueBlock = statement();
                setState(84);
                _errHandler->sync(this);

                switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx))
                {
                    case 1:
                    {
                        setState(82);
                        match(anceParser::T__6);
                        setState(83);
                        antlrcpp::downCast<IfStatementContext*>(_localctx)->falseBlock = statement();
                        break;
                    }

                    default:
                        break;
                }
                break;
            }

            case 6:
            {
                _localctx = _tracker.createInstance<anceParser::LoopStatementContext>(_localctx);
                enterOuterAlt(_localctx, 6);
                setState(86);
                match(anceParser::T__7);
                setState(87);
                statement();
                break;
            }

            case 7:
            {
                _localctx = _tracker.createInstance<anceParser::BreakStatementContext>(_localctx);
                enterOuterAlt(_localctx, 7);
                setState(88);
                match(anceParser::T__8);
                setState(89);
                match(anceParser::SEMICOLON);
                break;
            }

            case 8:
            {
                _localctx = _tracker.createInstance<anceParser::ContinueStatementContext>(_localctx);
                enterOuterAlt(_localctx, 8);
                setState(90);
                match(anceParser::T__9);
                setState(91);
                match(anceParser::SEMICOLON);
                break;
            }

            case 9:
            {
                _localctx = _tracker.createInstance<anceParser::ReturnStatementContext>(_localctx);
                enterOuterAlt(_localctx, 9);
                setState(92);
                match(anceParser::T__10);
                setState(94);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if ((((_la & ~0x3fULL) == 0)
                     && ((1ULL << _la)
                         & ((1ULL << anceParser::T__14) | (1ULL << anceParser::T__15) | (1ULL << anceParser::T__16) | (1ULL << anceParser::T__17)
                            | (1ULL << anceParser::IDENTIFIER) | (1ULL << anceParser::INTEGER) | (1ULL << anceParser::STRING) | (1ULL << anceParser::LAMBDA)
                            | (1ULL << anceParser::BRACKET_OPEN)))
                            != 0))
                {
                    setState(93);
                    expression();
                }
                setState(96);
                match(anceParser::SEMICOLON);
                break;
            }

            case 10:
            {
                _localctx = _tracker.createInstance<anceParser::WhileStatementContext>(_localctx);
                enterOuterAlt(_localctx, 10);
                setState(97);
                match(anceParser::T__11);
                setState(98);
                expression();
                setState(99);
                match(anceParser::T__0);
                setState(100);
                statement();
                break;
            }

            default:
                break;
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

anceParser::ExpressionContext::ExpressionContext(ParserRuleContext* parent, size_t invokingState) : ParserRuleContext(parent, invokingState) {}

size_t anceParser::ExpressionContext::getRuleIndex() const
{
    return anceParser::RuleExpression;
}

void anceParser::ExpressionContext::copyFrom(ExpressionContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- UnaryOperationExpressionContext ------------------------------------------------------------------

anceParser::UnaryContext* anceParser::UnaryOperationExpressionContext::unary()
{
    return getRuleContext<anceParser::UnaryContext>(0);
}

anceParser::ExpressionContext* anceParser::UnaryOperationExpressionContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::UnaryOperationExpressionContext::UnaryOperationExpressionContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::UnaryOperationExpressionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitUnaryOperationExpression(this);
    else return visitor->visitChildren(this);
}
//----------------- LiteralExpressionContext ------------------------------------------------------------------

anceParser::LiteralContext* anceParser::LiteralExpressionContext::literal()
{
    return getRuleContext<anceParser::LiteralContext>(0);
}

anceParser::LiteralExpressionContext::LiteralExpressionContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::LiteralExpressionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitLiteralExpression(this);
    else return visitor->visitChildren(this);
}
//----------------- AccessExpressionContext ------------------------------------------------------------------

anceParser::EntityContext* anceParser::AccessExpressionContext::entity()
{
    return getRuleContext<anceParser::EntityContext>(0);
}

anceParser::AccessExpressionContext::AccessExpressionContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::AccessExpressionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitAccessExpression(this);
    else return visitor->visitChildren(this);
}
//----------------- CallExpressionContext ------------------------------------------------------------------

anceParser::EntityContext* anceParser::CallExpressionContext::entity()
{
    return getRuleContext<anceParser::EntityContext>(0);
}

tree::TerminalNode* anceParser::CallExpressionContext::BRACKET_OPEN()
{
    return getToken(anceParser::BRACKET_OPEN, 0);
}

tree::TerminalNode* anceParser::CallExpressionContext::BRACKET_CLOSE()
{
    return getToken(anceParser::BRACKET_CLOSE, 0);
}

std::vector<anceParser::ExpressionContext*> anceParser::CallExpressionContext::expression()
{
    return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::CallExpressionContext::expression(size_t i)
{
    return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::CallExpressionContext::CallExpressionContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::CallExpressionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitCallExpression(this);
    else return visitor->visitChildren(this);
}
//----------------- LambdaExpressionContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::LambdaExpressionContext::LAMBDA()
{
    return getToken(anceParser::LAMBDA, 0);
}

tree::TerminalNode* anceParser::LambdaExpressionContext::BRACKET_OPEN()
{
    return getToken(anceParser::BRACKET_OPEN, 0);
}

tree::TerminalNode* anceParser::LambdaExpressionContext::BRACKET_CLOSE()
{
    return getToken(anceParser::BRACKET_CLOSE, 0);
}

std::vector<anceParser::ExpressionContext*> anceParser::LambdaExpressionContext::expression()
{
    return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::LambdaExpressionContext::expression(size_t i)
{
    return getRuleContext<anceParser::ExpressionContext>(i);
}

tree::TerminalNode* anceParser::LambdaExpressionContext::SQUARE_BRACKET_OPEN()
{
    return getToken(anceParser::SQUARE_BRACKET_OPEN, 0);
}

tree::TerminalNode* anceParser::LambdaExpressionContext::SQUARE_BRACKET_CLOSE()
{
    return getToken(anceParser::SQUARE_BRACKET_CLOSE, 0);
}

std::vector<anceParser::ParameterContext*> anceParser::LambdaExpressionContext::parameter()
{
    return getRuleContexts<anceParser::ParameterContext>();
}

anceParser::ParameterContext* anceParser::LambdaExpressionContext::parameter(size_t i)
{
    return getRuleContext<anceParser::ParameterContext>(i);
}

tree::TerminalNode* anceParser::LambdaExpressionContext::CURLY_BRACKET_OPEN()
{
    return getToken(anceParser::CURLY_BRACKET_OPEN, 0);
}

tree::TerminalNode* anceParser::LambdaExpressionContext::CURLY_BRACKET_CLOSE()
{
    return getToken(anceParser::CURLY_BRACKET_CLOSE, 0);
}

std::vector<anceParser::StatementContext*> anceParser::LambdaExpressionContext::statement()
{
    return getRuleContexts<anceParser::StatementContext>();
}

anceParser::StatementContext* anceParser::LambdaExpressionContext::statement(size_t i)
{
    return getRuleContext<anceParser::StatementContext>(i);
}

anceParser::LambdaExpressionContext::LambdaExpressionContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::LambdaExpressionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitLambdaExpression(this);
    else return visitor->visitChildren(this);
}
//----------------- HereExpressionContext ------------------------------------------------------------------

anceParser::HereExpressionContext::HereExpressionContext(ExpressionContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::HereExpressionContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitHereExpression(this);
    else return visitor->visitChildren(this);
}
anceParser::ExpressionContext* anceParser::expression()
{
    ExpressionContext* _localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
    enterRule(_localctx, 8, anceParser::RuleExpression);
    size_t _la = 0;

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(155);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx))
        {
            case 1:
            {
                _localctx = _tracker.createInstance<anceParser::CallExpressionContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(104);
                entity();
                setState(105);
                match(anceParser::BRACKET_OPEN);
                setState(114);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if ((((_la & ~0x3fULL) == 0)
                     && ((1ULL << _la)
                         & ((1ULL << anceParser::T__14) | (1ULL << anceParser::T__15) | (1ULL << anceParser::T__16) | (1ULL << anceParser::T__17)
                            | (1ULL << anceParser::IDENTIFIER) | (1ULL << anceParser::INTEGER) | (1ULL << anceParser::STRING) | (1ULL << anceParser::LAMBDA)
                            | (1ULL << anceParser::BRACKET_OPEN)))
                            != 0))
                {
                    setState(106);
                    expression();
                    setState(111);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                    while (_la == anceParser::T__12)
                    {
                        setState(107);
                        match(anceParser::T__12);
                        setState(108);
                        expression();
                        setState(113);
                        _errHandler->sync(this);
                        _la = _input->LA(1);
                    }
                }
                setState(116);
                match(anceParser::BRACKET_CLOSE);
                break;
            }

            case 2:
            {
                _localctx = _tracker.createInstance<anceParser::LambdaExpressionContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(118);
                match(anceParser::LAMBDA);
                setState(121);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == anceParser::SQUARE_BRACKET_OPEN)
                {
                    setState(119);
                    match(anceParser::SQUARE_BRACKET_OPEN);
                    setState(120);
                    match(anceParser::SQUARE_BRACKET_CLOSE);
                }
                setState(123);
                match(anceParser::BRACKET_OPEN);
                setState(132);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == anceParser::IDENTIFIER)
                {
                    setState(124);
                    parameter();
                    setState(129);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                    while (_la == anceParser::T__12)
                    {
                        setState(125);
                        match(anceParser::T__12);
                        setState(126);
                        parameter();
                        setState(131);
                        _errHandler->sync(this);
                        _la = _input->LA(1);
                    }
                }
                setState(134);
                match(anceParser::BRACKET_CLOSE);
                setState(135);
                match(anceParser::T__2);
                setState(136);
                antlrcpp::downCast<LambdaExpressionContext*>(_localctx)->type = expression();
                setState(147);
                _errHandler->sync(this);
                switch (_input->LA(1))
                {
                    case anceParser::T__13:
                    {
                        setState(137);
                        match(anceParser::T__13);
                        setState(138);
                        antlrcpp::downCast<LambdaExpressionContext*>(_localctx)->body = expression();
                        break;
                    }

                    case anceParser::CURLY_BRACKET_OPEN:
                    {
                        setState(139);
                        match(anceParser::CURLY_BRACKET_OPEN);
                        setState(143);
                        _errHandler->sync(this);
                        _la = _input->LA(1);
                        while ((((_la & ~0x3fULL) == 0)
                                && ((1ULL << _la)
                                    & ((1ULL << anceParser::T__3) | (1ULL << anceParser::T__4) | (1ULL << anceParser::T__7) | (1ULL << anceParser::T__8)
                                       | (1ULL << anceParser::T__9) | (1ULL << anceParser::T__10) | (1ULL << anceParser::T__11) | (1ULL << anceParser::T__14)
                                       | (1ULL << anceParser::T__15) | (1ULL << anceParser::T__16) | (1ULL << anceParser::T__17)
                                       | (1ULL << anceParser::IDENTIFIER) | (1ULL << anceParser::INTEGER) | (1ULL << anceParser::STRING)
                                       | (1ULL << anceParser::LAMBDA) | (1ULL << anceParser::BRACKET_OPEN) | (1ULL << anceParser::CURLY_BRACKET_OPEN)))
                                       != 0))
                        {
                            setState(140);
                            statement();
                            setState(145);
                            _errHandler->sync(this);
                            _la = _input->LA(1);
                        }
                        setState(146);
                        match(anceParser::CURLY_BRACKET_CLOSE);
                        break;
                    }

                    default:
                        throw NoViableAltException(this);
                }
                break;
            }

            case 3:
            {
                _localctx = _tracker.createInstance<anceParser::AccessExpressionContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(149);
                entity();
                break;
            }

            case 4:
            {
                _localctx = _tracker.createInstance<anceParser::LiteralExpressionContext>(_localctx);
                enterOuterAlt(_localctx, 4);
                setState(150);
                literal();
                break;
            }

            case 5:
            {
                _localctx = _tracker.createInstance<anceParser::UnaryOperationExpressionContext>(_localctx);
                enterOuterAlt(_localctx, 5);
                setState(151);
                unary();
                setState(152);
                expression();
                break;
            }

            case 6:
            {
                _localctx = _tracker.createInstance<anceParser::HereExpressionContext>(_localctx);
                enterOuterAlt(_localctx, 6);
                setState(154);
                match(anceParser::T__14);
                break;
            }

            default:
                break;
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- UnaryContext ------------------------------------------------------------------

anceParser::UnaryContext::UnaryContext(ParserRuleContext* parent, size_t invokingState) : ParserRuleContext(parent, invokingState) {}

size_t anceParser::UnaryContext::getRuleIndex() const
{
    return anceParser::RuleUnary;
}

void anceParser::UnaryContext::copyFrom(UnaryContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- UnaryNotContext ------------------------------------------------------------------

anceParser::UnaryNotContext::UnaryNotContext(UnaryContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::UnaryNotContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitUnaryNot(this);
    else return visitor->visitChildren(this);
}
anceParser::UnaryContext* anceParser::unary()
{
    UnaryContext* _localctx = _tracker.createInstance<UnaryContext>(_ctx, getState());
    enterRule(_localctx, 10, anceParser::RuleUnary);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        _localctx = _tracker.createInstance<anceParser::UnaryNotContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(157);
        match(anceParser::T__15);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

anceParser::LiteralContext::LiteralContext(ParserRuleContext* parent, size_t invokingState) : ParserRuleContext(parent, invokingState) {}

size_t anceParser::LiteralContext::getRuleIndex() const
{
    return anceParser::RuleLiteral;
}

void anceParser::LiteralContext::copyFrom(LiteralContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- StringLiteralContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::StringLiteralContext::STRING()
{
    return getToken(anceParser::STRING, 0);
}

anceParser::StringLiteralContext::StringLiteralContext(LiteralContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::StringLiteralContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitStringLiteral(this);
    else return visitor->visitChildren(this);
}
//----------------- BooleanLiteralContext ------------------------------------------------------------------

anceParser::BooleanContext* anceParser::BooleanLiteralContext::boolean()
{
    return getRuleContext<anceParser::BooleanContext>(0);
}

anceParser::BooleanLiteralContext::BooleanLiteralContext(LiteralContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::BooleanLiteralContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitBooleanLiteral(this);
    else return visitor->visitChildren(this);
}
//----------------- UnitLiteralContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::UnitLiteralContext::BRACKET_OPEN()
{
    return getToken(anceParser::BRACKET_OPEN, 0);
}

tree::TerminalNode* anceParser::UnitLiteralContext::BRACKET_CLOSE()
{
    return getToken(anceParser::BRACKET_CLOSE, 0);
}

anceParser::UnitLiteralContext::UnitLiteralContext(LiteralContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::UnitLiteralContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitUnitLiteral(this);
    else return visitor->visitChildren(this);
}
//----------------- SizeLiteralContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::SizeLiteralContext::INTEGER()
{
    return getToken(anceParser::INTEGER, 0);
}

anceParser::SizeLiteralContext::SizeLiteralContext(LiteralContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::SizeLiteralContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitSizeLiteral(this);
    else return visitor->visitChildren(this);
}
anceParser::LiteralContext* anceParser::literal()
{
    LiteralContext* _localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
    enterRule(_localctx, 12, anceParser::RuleLiteral);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(164);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__16:
            case anceParser::T__17:
            {
                _localctx = _tracker.createInstance<anceParser::BooleanLiteralContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(159);
                boolean();
                break;
            }

            case anceParser::INTEGER:
            {
                _localctx = _tracker.createInstance<anceParser::SizeLiteralContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(160);
                match(anceParser::INTEGER);
                break;
            }

            case anceParser::BRACKET_OPEN:
            {
                _localctx = _tracker.createInstance<anceParser::UnitLiteralContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(161);
                match(anceParser::BRACKET_OPEN);
                setState(162);
                match(anceParser::BRACKET_CLOSE);
                break;
            }

            case anceParser::STRING:
            {
                _localctx = _tracker.createInstance<anceParser::StringLiteralContext>(_localctx);
                enterOuterAlt(_localctx, 4);
                setState(163);
                match(anceParser::STRING);
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- BooleanContext ------------------------------------------------------------------

anceParser::BooleanContext::BooleanContext(ParserRuleContext* parent, size_t invokingState) : ParserRuleContext(parent, invokingState) {}

size_t anceParser::BooleanContext::getRuleIndex() const
{
    return anceParser::RuleBoolean;
}

void anceParser::BooleanContext::copyFrom(BooleanContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- TrueContext ------------------------------------------------------------------

anceParser::TrueContext::TrueContext(BooleanContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::TrueContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitTrue(this);
    else return visitor->visitChildren(this);
}
//----------------- FalseContext ------------------------------------------------------------------

anceParser::FalseContext::FalseContext(BooleanContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::FalseContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitFalse(this);
    else return visitor->visitChildren(this);
}
anceParser::BooleanContext* anceParser::boolean()
{
    BooleanContext* _localctx = _tracker.createInstance<BooleanContext>(_ctx, getState());
    enterRule(_localctx, 14, anceParser::RuleBoolean);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(168);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__16:
            {
                _localctx = _tracker.createInstance<anceParser::TrueContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(166);
                match(anceParser::T__16);
                break;
            }

            case anceParser::T__17:
            {
                _localctx = _tracker.createInstance<anceParser::FalseContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(167);
                match(anceParser::T__17);
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- EntityContext ------------------------------------------------------------------

anceParser::EntityContext::EntityContext(ParserRuleContext* parent, size_t invokingState) : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* anceParser::EntityContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

size_t anceParser::EntityContext::getRuleIndex() const
{
    return anceParser::RuleEntity;
}

std::any anceParser::EntityContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitEntity(this);
    else return visitor->visitChildren(this);
}

anceParser::EntityContext* anceParser::entity()
{
    EntityContext* _localctx = _tracker.createInstance<EntityContext>(_ctx, getState());
    enterRule(_localctx, 16, anceParser::RuleEntity);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(170);
        match(anceParser::IDENTIFIER);
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ParameterContext ------------------------------------------------------------------

anceParser::ParameterContext::ParameterContext(ParserRuleContext* parent, size_t invokingState) : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* anceParser::ParameterContext::IDENTIFIER()
{
    return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ExpressionContext* anceParser::ParameterContext::expression()
{
    return getRuleContext<anceParser::ExpressionContext>(0);
}

size_t anceParser::ParameterContext::getRuleIndex() const
{
    return anceParser::RuleParameter;
}

std::any anceParser::ParameterContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitParameter(this);
    else return visitor->visitChildren(this);
}

anceParser::ParameterContext* anceParser::parameter()
{
    ParameterContext* _localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
    enterRule(_localctx, 18, anceParser::RuleParameter);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(172);
        match(anceParser::IDENTIFIER);
        setState(173);
        match(anceParser::T__2);
        setState(174);
        expression();
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- AssignerContext ------------------------------------------------------------------

anceParser::AssignerContext::AssignerContext(ParserRuleContext* parent, size_t invokingState) : ParserRuleContext(parent, invokingState) {}

size_t anceParser::AssignerContext::getRuleIndex() const
{
    return anceParser::RuleAssigner;
}

void anceParser::AssignerContext::copyFrom(AssignerContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- CopyAssignerContext ------------------------------------------------------------------

anceParser::CopyAssignerContext::CopyAssignerContext(AssignerContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::CopyAssignerContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitCopyAssigner(this);
    else return visitor->visitChildren(this);
}
//----------------- FinalCopyAssignerContext ------------------------------------------------------------------

anceParser::FinalCopyAssignerContext::FinalCopyAssignerContext(AssignerContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::FinalCopyAssignerContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitFinalCopyAssigner(this);
    else return visitor->visitChildren(this);
}
anceParser::AssignerContext* anceParser::assigner()
{
    AssignerContext* _localctx = _tracker.createInstance<AssignerContext>(_ctx, getState());
    enterRule(_localctx, 20, anceParser::RuleAssigner);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(178);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__18:
            {
                _localctx = _tracker.createInstance<anceParser::CopyAssignerContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(176);
                match(anceParser::T__18);
                break;
            }

            case anceParser::T__19:
            {
                _localctx = _tracker.createInstance<anceParser::FinalCopyAssignerContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(177);
                match(anceParser::T__19);
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- AccessModifierContext ------------------------------------------------------------------

anceParser::AccessModifierContext::AccessModifierContext(ParserRuleContext* parent, size_t invokingState) : ParserRuleContext(parent, invokingState) {}

size_t anceParser::AccessModifierContext::getRuleIndex() const
{
    return anceParser::RuleAccessModifier;
}

void anceParser::AccessModifierContext::copyFrom(AccessModifierContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- PrivateContext ------------------------------------------------------------------

anceParser::PrivateContext::PrivateContext(AccessModifierContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::PrivateContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitPrivate(this);
    else return visitor->visitChildren(this);
}
//----------------- PublicContext ------------------------------------------------------------------

anceParser::PublicContext::PublicContext(AccessModifierContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::PublicContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitPublic(this);
    else return visitor->visitChildren(this);
}
//----------------- ExternContext ------------------------------------------------------------------

anceParser::ExternContext::ExternContext(AccessModifierContext* ctx)
{
    copyFrom(ctx);
}

std::any anceParser::ExternContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor)) return parserVisitor->visitExtern(this);
    else return visitor->visitChildren(this);
}
anceParser::AccessModifierContext* anceParser::accessModifier()
{
    AccessModifierContext* _localctx = _tracker.createInstance<AccessModifierContext>(_ctx, getState());
    enterRule(_localctx, 22, anceParser::RuleAccessModifier);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(183);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__20:
            {
                _localctx = _tracker.createInstance<anceParser::PublicContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(180);
                match(anceParser::T__20);
                break;
            }

            case anceParser::T__21:
            {
                _localctx = _tracker.createInstance<anceParser::PrivateContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(181);
                match(anceParser::T__21);
                break;
            }

            case anceParser::T__22:
            {
                _localctx = _tracker.createInstance<anceParser::ExternContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(182);
                match(anceParser::T__22);
                break;
            }

            default:
                throw NoViableAltException(this);
        }
    }
    catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

void anceParser::initialize()
{
    std::call_once(anceParserOnceFlag, anceParserInitialize);
}
