
// Generated from ./src/management/grammar/data.g4 by ANTLR 4.10.1


#include "dataVisitor.h"

#include "dataParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct DataParserStaticData final {
  DataParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  DataParserStaticData(const DataParserStaticData&) = delete;
  DataParserStaticData(DataParserStaticData&&) = delete;
  DataParserStaticData& operator=(const DataParserStaticData&) = delete;
  DataParserStaticData& operator=(DataParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag dataParserOnceFlag;
DataParserStaticData *dataParserStaticData = nullptr;

void dataParserInitialize() {
  assert(dataParserStaticData == nullptr);
  auto staticData = std::make_unique<DataParserStaticData>(
    std::vector<std::string>{
      "element", "dictionary", "entry", "list", "string", "boolean"
    },
    std::vector<std::string>{
      "", "'{'", "','", "'}'", "':'", "'['", "']'", "'true'", "'false'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "KEY", "STRING", "WHITESPACE", 
      "LINE_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,12,55,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,1,0,1,0,1,0,
  	1,0,3,0,17,8,0,1,1,1,1,1,1,1,1,5,1,23,8,1,10,1,12,1,26,9,1,3,1,28,8,1,
  	1,1,1,1,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,5,3,40,8,3,10,3,12,3,43,9,3,3,
  	3,45,8,3,1,3,1,3,1,4,1,4,1,5,1,5,3,5,53,8,5,1,5,0,0,6,0,2,4,6,8,10,0,
  	0,56,0,16,1,0,0,0,2,18,1,0,0,0,4,31,1,0,0,0,6,35,1,0,0,0,8,48,1,0,0,0,
  	10,52,1,0,0,0,12,17,3,2,1,0,13,17,3,6,3,0,14,17,3,8,4,0,15,17,3,10,5,
  	0,16,12,1,0,0,0,16,13,1,0,0,0,16,14,1,0,0,0,16,15,1,0,0,0,17,1,1,0,0,
  	0,18,27,5,1,0,0,19,24,3,4,2,0,20,21,5,2,0,0,21,23,3,4,2,0,22,20,1,0,0,
  	0,23,26,1,0,0,0,24,22,1,0,0,0,24,25,1,0,0,0,25,28,1,0,0,0,26,24,1,0,0,
  	0,27,19,1,0,0,0,27,28,1,0,0,0,28,29,1,0,0,0,29,30,5,3,0,0,30,3,1,0,0,
  	0,31,32,5,9,0,0,32,33,5,4,0,0,33,34,3,0,0,0,34,5,1,0,0,0,35,44,5,5,0,
  	0,36,41,3,0,0,0,37,38,5,2,0,0,38,40,3,0,0,0,39,37,1,0,0,0,40,43,1,0,0,
  	0,41,39,1,0,0,0,41,42,1,0,0,0,42,45,1,0,0,0,43,41,1,0,0,0,44,36,1,0,0,
  	0,44,45,1,0,0,0,45,46,1,0,0,0,46,47,5,6,0,0,47,7,1,0,0,0,48,49,5,10,0,
  	0,49,9,1,0,0,0,50,53,5,7,0,0,51,53,5,8,0,0,52,50,1,0,0,0,52,51,1,0,0,
  	0,53,11,1,0,0,0,6,16,24,27,41,44,52
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  dataParserStaticData = staticData.release();
}

}

dataParser::dataParser(TokenStream *input) : dataParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

dataParser::dataParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  dataParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *dataParserStaticData->atn, dataParserStaticData->decisionToDFA, dataParserStaticData->sharedContextCache, options);
}

dataParser::~dataParser() {
  delete _interpreter;
}

const atn::ATN& dataParser::getATN() const {
  return *dataParserStaticData->atn;
}

std::string dataParser::getGrammarFileName() const {
  return "data.g4";
}

const std::vector<std::string>& dataParser::getRuleNames() const {
  return dataParserStaticData->ruleNames;
}

const dfa::Vocabulary& dataParser::getVocabulary() const {
  return dataParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView dataParser::getSerializedATN() const {
  return dataParserStaticData->serializedATN;
}


//----------------- ElementContext ------------------------------------------------------------------

dataParser::ElementContext::ElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

dataParser::DictionaryContext* dataParser::ElementContext::dictionary() {
  return getRuleContext<dataParser::DictionaryContext>(0);
}

dataParser::ListContext* dataParser::ElementContext::list() {
  return getRuleContext<dataParser::ListContext>(0);
}

dataParser::StringContext* dataParser::ElementContext::string() {
  return getRuleContext<dataParser::StringContext>(0);
}

dataParser::BooleanContext* dataParser::ElementContext::boolean() {
  return getRuleContext<dataParser::BooleanContext>(0);
}


size_t dataParser::ElementContext::getRuleIndex() const {
  return dataParser::RuleElement;
}


std::any dataParser::ElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
    return parserVisitor->visitElement(this);
  else
    return visitor->visitChildren(this);
}

dataParser::ElementContext* dataParser::element() {
  ElementContext *_localctx = _tracker.createInstance<ElementContext>(_ctx, getState());
  enterRule(_localctx, 0, dataParser::RuleElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(16);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
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
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DictionaryContext ------------------------------------------------------------------

dataParser::DictionaryContext::DictionaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<dataParser::EntryContext *> dataParser::DictionaryContext::entry() {
  return getRuleContexts<dataParser::EntryContext>();
}

dataParser::EntryContext* dataParser::DictionaryContext::entry(size_t i) {
  return getRuleContext<dataParser::EntryContext>(i);
}


size_t dataParser::DictionaryContext::getRuleIndex() const {
  return dataParser::RuleDictionary;
}


std::any dataParser::DictionaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
    return parserVisitor->visitDictionary(this);
  else
    return visitor->visitChildren(this);
}

dataParser::DictionaryContext* dataParser::dictionary() {
  DictionaryContext *_localctx = _tracker.createInstance<DictionaryContext>(_ctx, getState());
  enterRule(_localctx, 2, dataParser::RuleDictionary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(18);
    match(dataParser::T__0);
    setState(27);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == dataParser::KEY) {
      setState(19);
      entry();
      setState(24);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == dataParser::T__1) {
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
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EntryContext ------------------------------------------------------------------

dataParser::EntryContext::EntryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* dataParser::EntryContext::KEY() {
  return getToken(dataParser::KEY, 0);
}

dataParser::ElementContext* dataParser::EntryContext::element() {
  return getRuleContext<dataParser::ElementContext>(0);
}


size_t dataParser::EntryContext::getRuleIndex() const {
  return dataParser::RuleEntry;
}


std::any dataParser::EntryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
    return parserVisitor->visitEntry(this);
  else
    return visitor->visitChildren(this);
}

dataParser::EntryContext* dataParser::entry() {
  EntryContext *_localctx = _tracker.createInstance<EntryContext>(_ctx, getState());
  enterRule(_localctx, 4, dataParser::RuleEntry);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(31);
    match(dataParser::KEY);
    setState(32);
    match(dataParser::T__3);
    setState(33);
    antlrcpp::downCast<EntryContext *>(_localctx)->value = element();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ListContext ------------------------------------------------------------------

dataParser::ListContext::ListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<dataParser::ElementContext *> dataParser::ListContext::element() {
  return getRuleContexts<dataParser::ElementContext>();
}

dataParser::ElementContext* dataParser::ListContext::element(size_t i) {
  return getRuleContext<dataParser::ElementContext>(i);
}


size_t dataParser::ListContext::getRuleIndex() const {
  return dataParser::RuleList;
}


std::any dataParser::ListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
    return parserVisitor->visitList(this);
  else
    return visitor->visitChildren(this);
}

dataParser::ListContext* dataParser::list() {
  ListContext *_localctx = _tracker.createInstance<ListContext>(_ctx, getState());
  enterRule(_localctx, 6, dataParser::RuleList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(35);
    match(dataParser::T__4);
    setState(44);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << dataParser::T__0)
      | (1ULL << dataParser::T__4)
      | (1ULL << dataParser::T__6)
      | (1ULL << dataParser::T__7)
      | (1ULL << dataParser::STRING))) != 0)) {
      setState(36);
      element();
      setState(41);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == dataParser::T__1) {
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
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringContext ------------------------------------------------------------------

dataParser::StringContext::StringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* dataParser::StringContext::STRING() {
  return getToken(dataParser::STRING, 0);
}


size_t dataParser::StringContext::getRuleIndex() const {
  return dataParser::RuleString;
}


std::any dataParser::StringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
    return parserVisitor->visitString(this);
  else
    return visitor->visitChildren(this);
}

dataParser::StringContext* dataParser::string() {
  StringContext *_localctx = _tracker.createInstance<StringContext>(_ctx, getState());
  enterRule(_localctx, 8, dataParser::RuleString);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(48);
    match(dataParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanContext ------------------------------------------------------------------

dataParser::BooleanContext::BooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t dataParser::BooleanContext::getRuleIndex() const {
  return dataParser::RuleBoolean;
}

void dataParser::BooleanContext::copyFrom(BooleanContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TrueContext ------------------------------------------------------------------

dataParser::TrueContext::TrueContext(BooleanContext *ctx) { copyFrom(ctx); }


std::any dataParser::TrueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
    return parserVisitor->visitTrue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FalseContext ------------------------------------------------------------------

dataParser::FalseContext::FalseContext(BooleanContext *ctx) { copyFrom(ctx); }


std::any dataParser::FalseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<dataVisitor*>(visitor))
    return parserVisitor->visitFalse(this);
  else
    return visitor->visitChildren(this);
}
dataParser::BooleanContext* dataParser::boolean() {
  BooleanContext *_localctx = _tracker.createInstance<BooleanContext>(_ctx, getState());
  enterRule(_localctx, 10, dataParser::RuleBoolean);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(52);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case dataParser::T__6: {
        _localctx = _tracker.createInstance<dataParser::TrueContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(50);
        match(dataParser::T__6);
        break;
      }

      case dataParser::T__7: {
        _localctx = _tracker.createInstance<dataParser::FalseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(51);
        match(dataParser::T__7);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void dataParser::initialize() {
  std::call_once(dataParserOnceFlag, dataParserInitialize);
}
