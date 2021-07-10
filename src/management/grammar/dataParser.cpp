
// Generated from ./src/management/grammar/data.g4 by ANTLR 4.8

#include "dataVisitor.h"

#include "dataParser.h"

using namespace antlrcpp;
using namespace antlr4;

dataParser::dataParser(TokenStream* input)
    : Parser(input)
{
    _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

dataParser::~dataParser()
{
    delete _interpreter;
}

std::string dataParser::getGrammarFileName() const
{
    return "data.g4";
}

const std::vector<std::string>& dataParser::getRuleNames() const
{
    return _ruleNames;
}

dfa::Vocabulary& dataParser::getVocabulary() const
{
    return _vocabulary;
}

//----------------- ElementContext ------------------------------------------------------------------

dataParser::ElementContext::ElementContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

dataParser::DictionaryContext* dataParser::ElementContext::dictionary()
{
    return getRuleContext<dataParser::DictionaryContext>(0);
}

dataParser::ListContext* dataParser::ElementContext::list()
{
    return getRuleContext<dataParser::ListContext>(0);
}

dataParser::StringContext* dataParser::ElementContext::string()
{
    return getRuleContext<dataParser::StringContext>(0);
}

dataParser::BooleanContext* dataParser::ElementContext::boolean()
{
    return getRuleContext<dataParser::BooleanContext>(0);
}

size_t dataParser::ElementContext::getRuleIndex() const
{
    return dataParser::RuleElement;
}

antlrcpp::Any dataParser::ElementContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
        return parserVisitor->visitElement(this);
    else
        return visitor->visitChildren(this);
}

dataParser::ElementContext* dataParser::element()
{
    ElementContext* _localctx = _tracker.createInstance<ElementContext>(_ctx, getState());
    enterRule(_localctx, 0, dataParser::RuleElement);

    auto onExit = finally(
        [=] {
            exitRule();
        });
    try
    {
        setState(16);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case dataParser::T__0: {
                enterOuterAlt(_localctx, 1);
                setState(12);
                dictionary();
                break;
            }

            case dataParser::T__4: {
                enterOuterAlt(_localctx, 2);
                setState(13);
                list();
                break;
            }

            case dataParser::STRING: {
                enterOuterAlt(_localctx, 3);
                setState(14);
                string();
                break;
            }

            case dataParser::T__6:
            case dataParser::T__7: {
                enterOuterAlt(_localctx, 4);
                setState(15);
                boolean();
                break;
            }

            default:
                throw NoViableAltException(this);
        }

    } catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- DictionaryContext ------------------------------------------------------------------

dataParser::DictionaryContext::DictionaryContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

std::vector<dataParser::EntryContext*> dataParser::DictionaryContext::entry()
{
    return getRuleContexts<dataParser::EntryContext>();
}

dataParser::EntryContext* dataParser::DictionaryContext::entry(size_t i)
{
    return getRuleContext<dataParser::EntryContext>(i);
}

size_t dataParser::DictionaryContext::getRuleIndex() const
{
    return dataParser::RuleDictionary;
}

antlrcpp::Any dataParser::DictionaryContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
        return parserVisitor->visitDictionary(this);
    else
        return visitor->visitChildren(this);
}

dataParser::DictionaryContext* dataParser::dictionary()
{
    DictionaryContext* _localctx = _tracker.createInstance<DictionaryContext>(_ctx, getState());
    enterRule(_localctx, 2, dataParser::RuleDictionary);
    size_t _la = 0;

    auto onExit = finally(
        [=] {
            exitRule();
        });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(18);
        match(dataParser::T__0);
        setState(27);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == dataParser::KEY)
        {
            setState(19);
            entry();
            setState(24);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == dataParser::T__1)
            {
                setState(20);
                match(dataParser::T__1);
                setState(21);
                entry();
                setState(26);
                _errHandler->sync(this);
                _la = _input->LA(1);
            }
        }
        setState(29);
        match(dataParser::T__2);

    } catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- EntryContext ------------------------------------------------------------------

dataParser::EntryContext::EntryContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* dataParser::EntryContext::KEY()
{
    return getToken(dataParser::KEY, 0);
}

dataParser::ElementContext* dataParser::EntryContext::element()
{
    return getRuleContext<dataParser::ElementContext>(0);
}

size_t dataParser::EntryContext::getRuleIndex() const
{
    return dataParser::RuleEntry;
}

antlrcpp::Any dataParser::EntryContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
        return parserVisitor->visitEntry(this);
    else
        return visitor->visitChildren(this);
}

dataParser::EntryContext* dataParser::entry()
{
    EntryContext* _localctx = _tracker.createInstance<EntryContext>(_ctx, getState());
    enterRule(_localctx, 4, dataParser::RuleEntry);

    auto onExit = finally(
        [=] {
            exitRule();
        });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(31);
        match(dataParser::KEY);
        setState(32);
        match(dataParser::T__3);
        setState(33);
        dynamic_cast<EntryContext*>(_localctx)->value = element();

    } catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ListContext ------------------------------------------------------------------

dataParser::ListContext::ListContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

std::vector<dataParser::ElementContext*> dataParser::ListContext::element()
{
    return getRuleContexts<dataParser::ElementContext>();
}

dataParser::ElementContext* dataParser::ListContext::element(size_t i)
{
    return getRuleContext<dataParser::ElementContext>(i);
}

size_t dataParser::ListContext::getRuleIndex() const
{
    return dataParser::RuleList;
}

antlrcpp::Any dataParser::ListContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
        return parserVisitor->visitList(this);
    else
        return visitor->visitChildren(this);
}

dataParser::ListContext* dataParser::list()
{
    ListContext* _localctx = _tracker.createInstance<ListContext>(_ctx, getState());
    enterRule(_localctx, 6, dataParser::RuleList);
    size_t _la = 0;

    auto onExit = finally(
        [=] {
            exitRule();
        });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(35);
        match(dataParser::T__4);
        setState(44);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0) && ((1ULL << _la) & ((1ULL << dataParser::T__0) | (1ULL << dataParser::T__4) | (1ULL << dataParser::T__6) | (1ULL << dataParser::T__7) | (1ULL << dataParser::STRING))) != 0))
        {
            setState(36);
            element();
            setState(41);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == dataParser::T__1)
            {
                setState(37);
                match(dataParser::T__1);
                setState(38);
                element();
                setState(43);
                _errHandler->sync(this);
                _la = _input->LA(1);
            }
        }
        setState(46);
        match(dataParser::T__5);

    } catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- StringContext ------------------------------------------------------------------

dataParser::StringContext::StringContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

tree::TerminalNode* dataParser::StringContext::STRING()
{
    return getToken(dataParser::STRING, 0);
}

size_t dataParser::StringContext::getRuleIndex() const
{
    return dataParser::RuleString;
}

antlrcpp::Any dataParser::StringContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
        return parserVisitor->visitString(this);
    else
        return visitor->visitChildren(this);
}

dataParser::StringContext* dataParser::string()
{
    StringContext* _localctx = _tracker.createInstance<StringContext>(_ctx, getState());
    enterRule(_localctx, 8, dataParser::RuleString);

    auto onExit = finally(
        [=] {
            exitRule();
        });
    try
    {
        enterOuterAlt(_localctx, 1);
        setState(48);
        match(dataParser::STRING);

    } catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- BooleanContext ------------------------------------------------------------------

dataParser::BooleanContext::BooleanContext(ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState)
{
}

size_t dataParser::BooleanContext::getRuleIndex() const
{
    return dataParser::RuleBoolean;
}

void dataParser::BooleanContext::copyFrom(BooleanContext* ctx)
{
    ParserRuleContext::copyFrom(ctx);
}

//----------------- TrueContext ------------------------------------------------------------------

dataParser::TrueContext::TrueContext(BooleanContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any dataParser::TrueContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
        return parserVisitor->visitTrue(this);
    else
        return visitor->visitChildren(this);
}
//----------------- FalseContext ------------------------------------------------------------------

dataParser::FalseContext::FalseContext(BooleanContext* ctx)
{
    copyFrom(ctx);
}

antlrcpp::Any dataParser::FalseContext::accept(tree::ParseTreeVisitor* visitor)
{
    if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
        return parserVisitor->visitFalse(this);
    else
        return visitor->visitChildren(this);
}

dataParser::BooleanContext* dataParser::boolean()
{
    BooleanContext* _localctx = _tracker.createInstance<BooleanContext>(_ctx, getState());
    enterRule(_localctx, 10, dataParser::RuleBoolean);

    auto onExit = finally(
        [=] {
            exitRule();
        });
    try
    {
        setState(52);
        _errHandler->sync(this);
        switch (_input->LA(1))
        {
            case dataParser::T__6: {
                _localctx = dynamic_cast<BooleanContext*>(_tracker.createInstance<dataParser::TrueContext>(_localctx));
                enterOuterAlt(_localctx, 1);
                setState(50);
                match(dataParser::T__6);
                break;
            }

            case dataParser::T__7: {
                _localctx = dynamic_cast<BooleanContext*>(_tracker.createInstance<dataParser::FalseContext>(_localctx));
                enterOuterAlt(_localctx, 2);
                setState(51);
                match(dataParser::T__7);
                break;
            }

            default:
                throw NoViableAltException(this);
        }

    } catch (RecognitionException& e)
    {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA>       dataParser::_decisionToDFA;
atn::PredictionContextCache dataParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN              dataParser::_atn;
std::vector<uint16_t> dataParser::_serializedATN;

std::vector<std::string> dataParser::_ruleNames = {
    "element", "dictionary", "entry", "list", "string", "boolean"};

std::vector<std::string> dataParser::_literalNames = {
    "", "'{'", "','", "'}'", "':'", "'['", "']'", "'true'", "'false'"};

std::vector<std::string> dataParser::_symbolicNames = {
    "", "", "", "", "", "", "", "", "", "KEY", "STRING", "WHITESPACE", "LINE_COMMENT"};

dfa::Vocabulary dataParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> dataParser::_tokenNames;

dataParser::Initializer::Initializer()
{
    for (size_t i = 0; i < _symbolicNames.size(); ++i)
    {
        std::string name = _vocabulary.getLiteralName(i);
        if (name.empty())
        {
            name = _vocabulary.getSymbolicName(i);
        }

        if (name.empty())
        {
            _tokenNames.push_back("<INVALID>");
        }
        else
        {
            _tokenNames.push_back(name);
        }
    }

    _serializedATN = {
        0x3,
        0x608b,
        0xa72a,
        0x8133,
        0xb9ed,
        0x417c,
        0x3be7,
        0x7786,
        0x5964,
        0x3,
        0xe,
        0x39,
        0x4,
        0x2,
        0x9,
        0x2,
        0x4,
        0x3,
        0x9,
        0x3,
        0x4,
        0x4,
        0x9,
        0x4,
        0x4,
        0x5,
        0x9,
        0x5,
        0x4,
        0x6,
        0x9,
        0x6,
        0x4,
        0x7,
        0x9,
        0x7,
        0x3,
        0x2,
        0x3,
        0x2,
        0x3,
        0x2,
        0x3,
        0x2,
        0x5,
        0x2,
        0x13,
        0xa,
        0x2,
        0x3,
        0x3,
        0x3,
        0x3,
        0x3,
        0x3,
        0x3,
        0x3,
        0x7,
        0x3,
        0x19,
        0xa,
        0x3,
        0xc,
        0x3,
        0xe,
        0x3,
        0x1c,
        0xb,
        0x3,
        0x5,
        0x3,
        0x1e,
        0xa,
        0x3,
        0x3,
        0x3,
        0x3,
        0x3,
        0x3,
        0x4,
        0x3,
        0x4,
        0x3,
        0x4,
        0x3,
        0x4,
        0x3,
        0x5,
        0x3,
        0x5,
        0x3,
        0x5,
        0x3,
        0x5,
        0x7,
        0x5,
        0x2a,
        0xa,
        0x5,
        0xc,
        0x5,
        0xe,
        0x5,
        0x2d,
        0xb,
        0x5,
        0x5,
        0x5,
        0x2f,
        0xa,
        0x5,
        0x3,
        0x5,
        0x3,
        0x5,
        0x3,
        0x6,
        0x3,
        0x6,
        0x3,
        0x7,
        0x3,
        0x7,
        0x5,
        0x7,
        0x37,
        0xa,
        0x7,
        0x3,
        0x7,
        0x2,
        0x2,
        0x8,
        0x2,
        0x4,
        0x6,
        0x8,
        0xa,
        0xc,
        0x2,
        0x2,
        0x2,
        0x3a,
        0x2,
        0x12,
        0x3,
        0x2,
        0x2,
        0x2,
        0x4,
        0x14,
        0x3,
        0x2,
        0x2,
        0x2,
        0x6,
        0x21,
        0x3,
        0x2,
        0x2,
        0x2,
        0x8,
        0x25,
        0x3,
        0x2,
        0x2,
        0x2,
        0xa,
        0x32,
        0x3,
        0x2,
        0x2,
        0x2,
        0xc,
        0x36,
        0x3,
        0x2,
        0x2,
        0x2,
        0xe,
        0x13,
        0x5,
        0x4,
        0x3,
        0x2,
        0xf,
        0x13,
        0x5,
        0x8,
        0x5,
        0x2,
        0x10,
        0x13,
        0x5,
        0xa,
        0x6,
        0x2,
        0x11,
        0x13,
        0x5,
        0xc,
        0x7,
        0x2,
        0x12,
        0xe,
        0x3,
        0x2,
        0x2,
        0x2,
        0x12,
        0xf,
        0x3,
        0x2,
        0x2,
        0x2,
        0x12,
        0x10,
        0x3,
        0x2,
        0x2,
        0x2,
        0x12,
        0x11,
        0x3,
        0x2,
        0x2,
        0x2,
        0x13,
        0x3,
        0x3,
        0x2,
        0x2,
        0x2,
        0x14,
        0x1d,
        0x7,
        0x3,
        0x2,
        0x2,
        0x15,
        0x1a,
        0x5,
        0x6,
        0x4,
        0x2,
        0x16,
        0x17,
        0x7,
        0x4,
        0x2,
        0x2,
        0x17,
        0x19,
        0x5,
        0x6,
        0x4,
        0x2,
        0x18,
        0x16,
        0x3,
        0x2,
        0x2,
        0x2,
        0x19,
        0x1c,
        0x3,
        0x2,
        0x2,
        0x2,
        0x1a,
        0x18,
        0x3,
        0x2,
        0x2,
        0x2,
        0x1a,
        0x1b,
        0x3,
        0x2,
        0x2,
        0x2,
        0x1b,
        0x1e,
        0x3,
        0x2,
        0x2,
        0x2,
        0x1c,
        0x1a,
        0x3,
        0x2,
        0x2,
        0x2,
        0x1d,
        0x15,
        0x3,
        0x2,
        0x2,
        0x2,
        0x1d,
        0x1e,
        0x3,
        0x2,
        0x2,
        0x2,
        0x1e,
        0x1f,
        0x3,
        0x2,
        0x2,
        0x2,
        0x1f,
        0x20,
        0x7,
        0x5,
        0x2,
        0x2,
        0x20,
        0x5,
        0x3,
        0x2,
        0x2,
        0x2,
        0x21,
        0x22,
        0x7,
        0xb,
        0x2,
        0x2,
        0x22,
        0x23,
        0x7,
        0x6,
        0x2,
        0x2,
        0x23,
        0x24,
        0x5,
        0x2,
        0x2,
        0x2,
        0x24,
        0x7,
        0x3,
        0x2,
        0x2,
        0x2,
        0x25,
        0x2e,
        0x7,
        0x7,
        0x2,
        0x2,
        0x26,
        0x2b,
        0x5,
        0x2,
        0x2,
        0x2,
        0x27,
        0x28,
        0x7,
        0x4,
        0x2,
        0x2,
        0x28,
        0x2a,
        0x5,
        0x2,
        0x2,
        0x2,
        0x29,
        0x27,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2a,
        0x2d,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2b,
        0x29,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2b,
        0x2c,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2c,
        0x2f,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2d,
        0x2b,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2e,
        0x26,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2e,
        0x2f,
        0x3,
        0x2,
        0x2,
        0x2,
        0x2f,
        0x30,
        0x3,
        0x2,
        0x2,
        0x2,
        0x30,
        0x31,
        0x7,
        0x8,
        0x2,
        0x2,
        0x31,
        0x9,
        0x3,
        0x2,
        0x2,
        0x2,
        0x32,
        0x33,
        0x7,
        0xc,
        0x2,
        0x2,
        0x33,
        0xb,
        0x3,
        0x2,
        0x2,
        0x2,
        0x34,
        0x37,
        0x7,
        0x9,
        0x2,
        0x2,
        0x35,
        0x37,
        0x7,
        0xa,
        0x2,
        0x2,
        0x36,
        0x34,
        0x3,
        0x2,
        0x2,
        0x2,
        0x36,
        0x35,
        0x3,
        0x2,
        0x2,
        0x2,
        0x37,
        0xd,
        0x3,
        0x2,
        0x2,
        0x2,
        0x8,
        0x12,
        0x1a,
        0x1d,
        0x2b,
        0x2e,
        0x36,
    };

    atn::ATNDeserializer deserializer;
    _atn = deserializer.deserialize(_serializedATN);

    size_t count = _atn.getNumberOfDecisions();
    _decisionToDFA.reserve(count);
    for (size_t i = 0; i < count; i++)
    {
        _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
    }
}

dataParser::Initializer dataParser::_init;
