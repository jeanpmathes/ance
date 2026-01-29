
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
                                      "assigner",
                                      "accessModifier"},
            std::vector<std::string> {"",           "'do'",      "'cmp'",    "':'", "'let'",  "'if'",  "'then'", "'else'",  "'loop'", "'break'",
                                      "'continue'", "'return'",  "'while'",  "','", "'here'", "'not'", "'true'", "'false'", "'<:'",   "':='",
                                      "'public'",   "'private'", "'extern'", "",    "",       "",      "';'",    "",        "",       "",
                                      "'('",        "')'",       "'{'",      "'}'", "'['",    "']'",   "'<'",    "'>'"},
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
                                      "IDENTIFIER",
                                      "INTEGER",
                                      "STRING",
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
            4,  1,   38,  149, 2,   0,   7,   0,   2,   1, 7,  1,  2,   2,   7,   2,   2,  3,  7,  3,   2,   4,   7,   4,   2,   5,   7,   5,   2,  6,
            7,  6,   2,   7,   7,   7,   2,   8,   7,   8, 2,  9,  7,   9,   2,   10,  7,  10, 1,  0,   5,   0,   24,  8,   0,   10,  0,   12,  0,  27,
            9,  0,   1,   0,   1,   0,   1,   1,   1,   1, 1,  1,  1,   2,   1,   2,   1,  2,  1,  2,   1,   2,   1,   2,   1,   2,   1,   2,   1,  2,
            1,  2,   3,   2,   44,  8,   2,   1,   2,   1, 2,  3,  2,   48,  8,   2,   1,  3,  1,  3,   5,   3,   52,  8,   3,   10,  3,   12,  3,  55,
            9,  3,   1,   3,   1,   3,   1,   3,   1,   3, 1,  3,  1,   3,   1,   3,   1,  3,  1,  3,   1,   3,   1,   3,   3,   3,   68,  8,   3,  1,
            3,  1,   3,   1,   3,   1,   3,   1,   3,   1, 3,  1,  3,   1,   3,   1,   3,  1,  3,  1,   3,   1,   3,   1,   3,   3,   3,   83,  8,  3,
            1,  3,   1,   3,   1,   3,   1,   3,   1,   3, 1,  3,  1,   3,   1,   3,   3,  3,  93, 8,   3,   1,   3,   1,   3,   1,   3,   1,   3,  1,
            3,  1,   3,   3,   3,   101, 8,   3,   1,   4, 1,  4,  1,   4,   1,   4,   1,  4,  5,  4,   108, 8,   4,   10,  4,   12,  4,   111, 9,  4,
            3,  4,   113, 8,   4,   1,   4,   1,   4,   1, 4,  1,  4,   1,   4,   1,   4,  1,  4,  1,   4,   3,   4,   123, 8,   4,   1,   5,   1,  5,
            1,  6,   1,   6,   1,   6,   1,   6,   1,   6, 3,  6,  132, 8,   6,   1,   7,  1,  7,  3,   7,   136, 8,   7,   1,   8,   1,   8,   1,  9,
            1,  9,   3,   9,   142, 8,   9,   1,   10,  1, 10, 1,  10,  3,   10,  147, 8,  10, 1,  10,  0,   0,   11,  0,   2,   4,   6,   8,   10, 12,
            14, 16,  18,  20,  0,   0,   166, 0,   25,  1, 0,  0,  0,   2,   30,  1,   0,  0,  0,  4,   47,  1,   0,   0,   0,   6,   100, 1,   0,  0,
            0,  8,   122, 1,   0,   0,   0,   10,  124, 1, 0,  0,  0,   12,  131, 1,   0,  0,  0,  14,  135, 1,   0,   0,   0,   16,  137, 1,   0,  0,
            0,  18,  141, 1,   0,   0,   0,   20,  146, 1, 0,  0,  0,   22,  24,  3,   4,  2,  0,  23,  22,  1,   0,   0,   0,   24,  27,  1,   0,  0,
            0,  25,  23,  1,   0,   0,   0,   25,  26,  1, 0,  0,  0,   26,  28,  1,   0,  0,  0,  27,  25,  1,   0,   0,   0,   28,  29,  5,   0,  0,
            1,  29,  1,   1,   0,   0,   0,   30,  31,  3, 6,  3,  0,   31,  32,  5,   0,  0,  1,  32,  3,   1,   0,   0,   0,   33,  34,  5,   1,  0,
            0,  34,  48,  3,   6,   3,   0,   35,  36,  3, 20, 10, 0,   36,  37,  5,   2,  0,  0,  37,  38,  5,   23,  0,   0,   38,  39,  5,   3,  0,
            0,  39,  43,  3,   8,   4,   0,   40,  41,  3, 18, 9,  0,   41,  42,  3,   8,  4,  0,  42,  44,  1,   0,   0,   0,   43,  40,  1,   0,  0,
            0,  43,  44,  1,   0,   0,   0,   44,  45,  1, 0,  0,  0,   45,  46,  5,   26, 0,  0,  46,  48,  1,   0,   0,   0,   47,  33,  1,   0,  0,
            0,  47,  35,  1,   0,   0,   0,   48,  5,   1, 0,  0,  0,   49,  53,  5,   32, 0,  0,  50,  52,  3,   6,   3,   0,   51,  50,  1,   0,  0,
            0,  52,  55,  1,   0,   0,   0,   53,  51,  1, 0,  0,  0,   53,  54,  1,   0,  0,  0,  54,  56,  1,   0,   0,   0,   55,  53,  1,   0,  0,
            0,  56,  101, 5,   33,  0,   0,   57,  58,  3, 8,  4,  0,   58,  59,  5,   26, 0,  0,  59,  101, 1,   0,   0,   0,   60,  61,  5,   4,  0,
            0,  61,  62,  5,   23,  0,   0,   62,  63,  5, 3,  0,  0,   63,  67,  3,   8,  4,  0,  64,  65,  3,   18,  9,   0,   65,  66,  3,   8,  4,
            0,  66,  68,  1,   0,   0,   0,   67,  64,  1, 0,  0,  0,   67,  68,  1,   0,  0,  0,  68,  69,  1,   0,   0,   0,   69,  70,  5,   26, 0,
            0,  70,  101, 1,   0,   0,   0,   71,  72,  3, 16, 8,  0,   72,  73,  3,   18, 9,  0,  73,  74,  3,   8,   4,   0,   74,  75,  5,   26, 0,
            0,  75,  101, 1,   0,   0,   0,   76,  77,  5, 5,  0,  0,   77,  78,  3,   8,  4,  0,  78,  79,  5,   6,   0,   0,   79,  82,  3,   6,  3,
            0,  80,  81,  5,   7,   0,   0,   81,  83,  3, 6,  3,  0,   82,  80,  1,   0,  0,  0,  82,  83,  1,   0,   0,   0,   83,  101, 1,   0,  0,
            0,  84,  85,  5,   8,   0,   0,   85,  101, 3, 6,  3,  0,   86,  87,  5,   9,  0,  0,  87,  101, 5,   26,  0,   0,   88,  89,  5,   10, 0,
            0,  89,  101, 5,   26,  0,   0,   90,  92,  5, 11, 0,  0,   91,  93,  3,   8,  4,  0,  92,  91,  1,   0,   0,   0,   92,  93,  1,   0,  0,
            0,  93,  94,  1,   0,   0,   0,   94,  101, 5, 26, 0,  0,   95,  96,  5,   12, 0,  0,  96,  97,  3,   8,   4,   0,   97,  98,  5,   1,  0,
            0,  98,  99,  3,   6,   3,   0,   99,  101, 1, 0,  0,  0,   100, 49,  1,   0,  0,  0,  100, 57,  1,   0,   0,   0,   100, 60,  1,   0,  0,
            0,  100, 71,  1,   0,   0,   0,   100, 76,  1, 0,  0,  0,   100, 84,  1,   0,  0,  0,  100, 86,  1,   0,   0,   0,   100, 88,  1,   0,  0,
            0,  100, 90,  1,   0,   0,   0,   100, 95,  1, 0,  0,  0,   101, 7,   1,   0,  0,  0,  102, 103, 3,   16,  8,   0,   103, 112, 5,   30, 0,
            0,  104, 109, 3,   8,   4,   0,   105, 106, 5, 13, 0,  0,   106, 108, 3,   8,  4,  0,  107, 105, 1,   0,   0,   0,   108, 111, 1,   0,  0,
            0,  109, 107, 1,   0,   0,   0,   109, 110, 1, 0,  0,  0,   110, 113, 1,   0,  0,  0,  111, 109, 1,   0,   0,   0,   112, 104, 1,   0,  0,
            0,  112, 113, 1,   0,   0,   0,   113, 114, 1, 0,  0,  0,   114, 115, 5,   31, 0,  0,  115, 123, 1,   0,   0,   0,   116, 123, 3,   16, 8,
            0,  117, 123, 3,   12,  6,   0,   118, 119, 3, 10, 5,  0,   119, 120, 3,   8,  4,  0,  120, 123, 1,   0,   0,   0,   121, 123, 5,   14, 0,
            0,  122, 102, 1,   0,   0,   0,   122, 116, 1, 0,  0,  0,   122, 117, 1,   0,  0,  0,  122, 118, 1,   0,   0,   0,   122, 121, 1,   0,  0,
            0,  123, 9,   1,   0,   0,   0,   124, 125, 5, 15, 0,  0,   125, 11,  1,   0,  0,  0,  126, 132, 3,   14,  7,   0,   127, 132, 5,   24, 0,
            0,  128, 129, 5,   30,  0,   0,   129, 132, 5, 31, 0,  0,   130, 132, 5,   25, 0,  0,  131, 126, 1,   0,   0,   0,   131, 127, 1,   0,  0,
            0,  131, 128, 1,   0,   0,   0,   131, 130, 1, 0,  0,  0,   132, 13,  1,   0,  0,  0,  133, 136, 5,   16,  0,   0,   134, 136, 5,   17, 0,
            0,  135, 133, 1,   0,   0,   0,   135, 134, 1, 0,  0,  0,   136, 15,  1,   0,  0,  0,  137, 138, 5,   23,  0,   0,   138, 17,  1,   0,  0,
            0,  139, 142, 5,   18,  0,   0,   140, 142, 5, 19, 0,  0,   141, 139, 1,   0,  0,  0,  141, 140, 1,   0,   0,   0,   142, 19,  1,   0,  0,
            0,  143, 147, 5,   20,  0,   0,   144, 147, 5, 21, 0,  0,   145, 147, 5,   22, 0,  0,  146, 143, 1,   0,   0,   0,   146, 144, 1,   0,  0,
            0,  146, 145, 1,   0,   0,   0,   147, 21,  1, 0,  0,  0,   15,  25,  43,  47, 53, 67, 82,  92,  100, 109, 112, 122, 131, 135, 141, 146};
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
        setState(25);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (
            (((_la & ~0x3fULL) == 0)
             && ((1ULL << _la) & ((1ULL << anceParser::T__0) | (1ULL << anceParser::T__19) | (1ULL << anceParser::T__20) | (1ULL << anceParser::T__21))) != 0))
        {
            setState(22);
            declaration();
            setState(27);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(28);
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
        setState(30);
        statement();
        setState(31);
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
        setState(47);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__0:
            {
                _localctx = _tracker.createInstance<anceParser::RunnableDeclarationContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(33);
                match(anceParser::T__0);
                setState(34);
                statement();
                break;
            }

            case anceParser::T__19:
            case anceParser::T__20:
            case anceParser::T__21:
            {
                _localctx = _tracker.createInstance<anceParser::VariableDeclarationContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(35);
                accessModifier();
                setState(36);
                match(anceParser::T__1);
                setState(37);
                match(anceParser::IDENTIFIER);
                setState(38);
                match(anceParser::T__2);
                setState(39);
                antlrcpp::downCast<VariableDeclarationContext*>(_localctx)->varType = expression();
                setState(43);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == anceParser::T__17

                    || _la == anceParser::T__18)
                {
                    setState(40);
                    assigner();
                    setState(41);
                    antlrcpp::downCast<VariableDeclarationContext*>(_localctx)->assigned = expression();
                }
                setState(45);
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
        setState(100);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx))
        {
            case 1:
            {
                _localctx = _tracker.createInstance<anceParser::BlockStatementContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(49);
                match(anceParser::CURLY_BRACKET_OPEN);
                setState(53);
                _errHandler->sync(this);
                _la = _input->LA(1);
                while ((((_la & ~0x3fULL) == 0)
                        && ((1ULL << _la)
                            & ((1ULL << anceParser::T__3) | (1ULL << anceParser::T__4) | (1ULL << anceParser::T__7) | (1ULL << anceParser::T__8)
                               | (1ULL << anceParser::T__9) | (1ULL << anceParser::T__10) | (1ULL << anceParser::T__11) | (1ULL << anceParser::T__13)
                               | (1ULL << anceParser::T__14) | (1ULL << anceParser::T__15) | (1ULL << anceParser::T__16) | (1ULL << anceParser::IDENTIFIER)
                               | (1ULL << anceParser::INTEGER) | (1ULL << anceParser::STRING) | (1ULL << anceParser::BRACKET_OPEN)
                               | (1ULL << anceParser::CURLY_BRACKET_OPEN)))
                               != 0))
                {
                    setState(50);
                    statement();
                    setState(55);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                }
                setState(56);
                match(anceParser::CURLY_BRACKET_CLOSE);
                break;
            }

            case 2:
            {
                _localctx = _tracker.createInstance<anceParser::ExpressionStatementContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(57);
                expression();
                setState(58);
                match(anceParser::SEMICOLON);
                break;
            }

            case 3:
            {
                _localctx = _tracker.createInstance<anceParser::LetStatementContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(60);
                match(anceParser::T__3);
                setState(61);
                match(anceParser::IDENTIFIER);
                setState(62);
                match(anceParser::T__2);
                setState(63);
                antlrcpp::downCast<LetStatementContext*>(_localctx)->varType = expression();
                setState(67);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == anceParser::T__17

                    || _la == anceParser::T__18)
                {
                    setState(64);
                    assigner();
                    setState(65);
                    antlrcpp::downCast<LetStatementContext*>(_localctx)->assigned = expression();
                }
                setState(69);
                match(anceParser::SEMICOLON);
                break;
            }

            case 4:
            {
                _localctx = _tracker.createInstance<anceParser::AssignmentStatementContext>(_localctx);
                enterOuterAlt(_localctx, 4);
                setState(71);
                entity();
                setState(72);
                assigner();
                setState(73);
                expression();
                setState(74);
                match(anceParser::SEMICOLON);
                break;
            }

            case 5:
            {
                _localctx = _tracker.createInstance<anceParser::IfStatementContext>(_localctx);
                enterOuterAlt(_localctx, 5);
                setState(76);
                match(anceParser::T__4);
                setState(77);
                expression();
                setState(78);
                match(anceParser::T__5);
                setState(79);
                antlrcpp::downCast<IfStatementContext*>(_localctx)->trueBlock = statement();
                setState(82);
                _errHandler->sync(this);

                switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx))
                {
                    case 1:
                    {
                        setState(80);
                        match(anceParser::T__6);
                        setState(81);
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
                setState(84);
                match(anceParser::T__7);
                setState(85);
                statement();
                break;
            }

            case 7:
            {
                _localctx = _tracker.createInstance<anceParser::BreakStatementContext>(_localctx);
                enterOuterAlt(_localctx, 7);
                setState(86);
                match(anceParser::T__8);
                setState(87);
                match(anceParser::SEMICOLON);
                break;
            }

            case 8:
            {
                _localctx = _tracker.createInstance<anceParser::ContinueStatementContext>(_localctx);
                enterOuterAlt(_localctx, 8);
                setState(88);
                match(anceParser::T__9);
                setState(89);
                match(anceParser::SEMICOLON);
                break;
            }

            case 9:
            {
                _localctx = _tracker.createInstance<anceParser::ReturnStatementContext>(_localctx);
                enterOuterAlt(_localctx, 9);
                setState(90);
                match(anceParser::T__10);
                setState(92);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if ((((_la & ~0x3fULL) == 0)
                     && ((1ULL << _la)
                         & ((1ULL << anceParser::T__13) | (1ULL << anceParser::T__14) | (1ULL << anceParser::T__15) | (1ULL << anceParser::T__16)
                            | (1ULL << anceParser::IDENTIFIER) | (1ULL << anceParser::INTEGER) | (1ULL << anceParser::STRING)
                            | (1ULL << anceParser::BRACKET_OPEN)))
                            != 0))
                {
                    setState(91);
                    expression();
                }
                setState(94);
                match(anceParser::SEMICOLON);
                break;
            }

            case 10:
            {
                _localctx = _tracker.createInstance<anceParser::WhileStatementContext>(_localctx);
                enterOuterAlt(_localctx, 10);
                setState(95);
                match(anceParser::T__11);
                setState(96);
                expression();
                setState(97);
                match(anceParser::T__0);
                setState(98);
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
        setState(122);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx))
        {
            case 1:
            {
                _localctx = _tracker.createInstance<anceParser::CallExpressionContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(102);
                entity();
                setState(103);
                match(anceParser::BRACKET_OPEN);
                setState(112);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if ((((_la & ~0x3fULL) == 0)
                     && ((1ULL << _la)
                         & ((1ULL << anceParser::T__13) | (1ULL << anceParser::T__14) | (1ULL << anceParser::T__15) | (1ULL << anceParser::T__16)
                            | (1ULL << anceParser::IDENTIFIER) | (1ULL << anceParser::INTEGER) | (1ULL << anceParser::STRING)
                            | (1ULL << anceParser::BRACKET_OPEN)))
                            != 0))
                {
                    setState(104);
                    expression();
                    setState(109);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                    while (_la == anceParser::T__12)
                    {
                        setState(105);
                        match(anceParser::T__12);
                        setState(106);
                        expression();
                        setState(111);
                        _errHandler->sync(this);
                        _la = _input->LA(1);
                    }
                }
                setState(114);
                match(anceParser::BRACKET_CLOSE);
                break;
            }

            case 2:
            {
                _localctx = _tracker.createInstance<anceParser::AccessExpressionContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(116);
                entity();
                break;
            }

            case 3:
            {
                _localctx = _tracker.createInstance<anceParser::LiteralExpressionContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(117);
                literal();
                break;
            }

            case 4:
            {
                _localctx = _tracker.createInstance<anceParser::UnaryOperationExpressionContext>(_localctx);
                enterOuterAlt(_localctx, 4);
                setState(118);
                unary();
                setState(119);
                expression();
                break;
            }

            case 5:
            {
                _localctx = _tracker.createInstance<anceParser::HereExpressionContext>(_localctx);
                enterOuterAlt(_localctx, 5);
                setState(121);
                match(anceParser::T__13);
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
        setState(124);
        match(anceParser::T__14);
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
        setState(131);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__15:
            case anceParser::T__16:
            {
                _localctx = _tracker.createInstance<anceParser::BooleanLiteralContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(126);
                boolean();
                break;
            }

            case anceParser::INTEGER:
            {
                _localctx = _tracker.createInstance<anceParser::SizeLiteralContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(127);
                match(anceParser::INTEGER);
                break;
            }

            case anceParser::BRACKET_OPEN:
            {
                _localctx = _tracker.createInstance<anceParser::UnitLiteralContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(128);
                match(anceParser::BRACKET_OPEN);
                setState(129);
                match(anceParser::BRACKET_CLOSE);
                break;
            }

            case anceParser::STRING:
            {
                _localctx = _tracker.createInstance<anceParser::StringLiteralContext>(_localctx);
                enterOuterAlt(_localctx, 4);
                setState(130);
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
        setState(135);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__15:
            {
                _localctx = _tracker.createInstance<anceParser::TrueContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(133);
                match(anceParser::T__15);
                break;
            }

            case anceParser::T__16:
            {
                _localctx = _tracker.createInstance<anceParser::FalseContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(134);
                match(anceParser::T__16);
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
        setState(137);
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
    enterRule(_localctx, 18, anceParser::RuleAssigner);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(141);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__17:
            {
                _localctx = _tracker.createInstance<anceParser::CopyAssignerContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(139);
                match(anceParser::T__17);
                break;
            }

            case anceParser::T__18:
            {
                _localctx = _tracker.createInstance<anceParser::FinalCopyAssignerContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(140);
                match(anceParser::T__18);
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
    enterRule(_localctx, 20, anceParser::RuleAccessModifier);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try
    {
        setState(146);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case anceParser::T__19:
            {
                _localctx = _tracker.createInstance<anceParser::PublicContext>(_localctx);
                enterOuterAlt(_localctx, 1);
                setState(143);
                match(anceParser::T__19);
                break;
            }

            case anceParser::T__20:
            {
                _localctx = _tracker.createInstance<anceParser::PrivateContext>(_localctx);
                enterOuterAlt(_localctx, 2);
                setState(144);
                match(anceParser::T__20);
                break;
            }

            case anceParser::T__21:
            {
                _localctx = _tracker.createInstance<anceParser::ExternContext>(_localctx);
                enterOuterAlt(_localctx, 3);
                setState(145);
                match(anceParser::T__21);
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
