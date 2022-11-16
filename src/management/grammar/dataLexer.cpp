
// Generated from ./src/management/grammar/data.g4 by ANTLR 4.10.1

#include "dataLexer.h"

using namespace antlr4;

using namespace antlr4;

namespace
{

    struct DataLexerStaticData final {
        DataLexerStaticData(std::vector<std::string> ruleNames,
                            std::vector<std::string> channelNames,
                            std::vector<std::string> modeNames,
                            std::vector<std::string> literalNames,
                            std::vector<std::string> symbolicNames)
            : ruleNames(std::move(ruleNames))
            , channelNames(std::move(channelNames))
            , modeNames(std::move(modeNames))
            , literalNames(std::move(literalNames))
            , symbolicNames(std::move(symbolicNames))
            , vocabulary(this->literalNames, this->symbolicNames)
        {}

        DataLexerStaticData(DataLexerStaticData const&)            = delete;
        DataLexerStaticData(DataLexerStaticData&&)                 = delete;
        DataLexerStaticData& operator=(DataLexerStaticData const&) = delete;
        DataLexerStaticData& operator=(DataLexerStaticData&&)      = delete;

        std::vector<antlr4::dfa::DFA>       decisionToDFA;
        antlr4::atn::PredictionContextCache sharedContextCache;
        const std::vector<std::string>      ruleNames;
        const std::vector<std::string>      channelNames;
        const std::vector<std::string>      modeNames;
        const std::vector<std::string>      literalNames;
        const std::vector<std::string>      symbolicNames;
        const antlr4::dfa::Vocabulary       vocabulary;
        antlr4::atn::SerializedATNView      serializedATN;
        std::unique_ptr<antlr4::atn::ATN>   atn;
    };

    std::once_flag       datalexerLexerOnceFlag;
    DataLexerStaticData* datalexerLexerStaticData = nullptr;

    void datalexerLexerInitialize()
    {
        assert(datalexerLexerStaticData == nullptr);
        auto staticData = std::make_unique<DataLexerStaticData>(
            std::vector<std::string> {"T__0",
                                      "T__1",
                                      "T__2",
                                      "T__3",
                                      "T__4",
                                      "T__5",
                                      "T__6",
                                      "T__7",
                                      "KEY",
                                      "STRING",
                                      "WHITESPACE",
                                      "LINE_COMMENT"},
            std::vector<std::string> {"DEFAULT_TOKEN_CHANNEL", "HIDDEN"},
            std::vector<std::string> {"DEFAULT_MODE"},
            std::vector<std::string> {"", "'{'", "','", "'}'", "':'", "'['", "']'", "'true'", "'false'"},
            std::vector<
                std::string> {"", "", "", "", "", "", "", "", "", "KEY", "STRING", "WHITESPACE", "LINE_COMMENT"});
        static const int32_t serializedATNSegment[] = {
            4,  0,  12, 82,  6,  -1, 2,  0,  7,   0,   2,  1,  7,  1,  2,  2,   7,  2,  2,  3,  7,  3,   2,   4,
            7,  4,  2,  5,   7,  5,  2,  6,  7,   6,   2,  7,  7,  7,  2,  8,   7,  8,  2,  9,  7,  9,   2,   10,
            7,  10, 2,  11,  7,  11, 1,  0,  1,   0,   1,  1,  1,  1,  1,  2,   1,  2,  1,  3,  1,  3,   1,   4,
            1,  4,  1,  5,   1,  5,  1,  6,  1,   6,   1,  6,  1,  6,  1,  6,   1,  7,  1,  7,  1,  7,   1,   7,
            1,  7,  1,  7,   1,  8,  1,  8,  5,   8,   51, 8,  8,  10, 8,  12,  8,  54, 9,  8,  1,  9,   1,   9,
            1,  9,  1,  9,   5,  9,  60, 8,  9,   10,  9,  12, 9,  63, 9,  9,   1,  9,  1,  9,  1,  10,  4,   10,
            68, 8,  10, 11,  10, 12, 10, 69, 1,   10,  1,  10, 1,  11, 1,  11,  5,  11, 76, 8,  11, 10,  11,  12,
            11, 79, 9,  11,  1,  11, 1,  11, 1,   61,  0,  12, 1,  1,  3,  2,   5,  3,  7,  4,  9,  5,   11,  6,
            13, 7,  15, 8,   17, 9,  19, 10, 21,  11,  23, 12, 1,  0,  4,  3,   0,  65, 90, 95, 95, 97,  122, 4,
            0,  48, 57, 65,  90, 95, 95, 97, 122, 3,   0,  9,  10, 13, 13, 32,  32, 2,  0,  10, 10, 13,  13,  86,
            0,  1,  1,  0,   0,  0,  0,  3,  1,   0,   0,  0,  0,  5,  1,  0,   0,  0,  0,  7,  1,  0,   0,   0,
            0,  9,  1,  0,   0,  0,  0,  11, 1,   0,   0,  0,  0,  13, 1,  0,   0,  0,  0,  15, 1,  0,   0,   0,
            0,  17, 1,  0,   0,  0,  0,  19, 1,   0,   0,  0,  0,  21, 1,  0,   0,  0,  0,  23, 1,  0,   0,   0,
            1,  25, 1,  0,   0,  0,  3,  27, 1,   0,   0,  0,  5,  29, 1,  0,   0,  0,  7,  31, 1,  0,   0,   0,
            9,  33, 1,  0,   0,  0,  11, 35, 1,   0,   0,  0,  13, 37, 1,  0,   0,  0,  15, 42, 1,  0,   0,   0,
            17, 48, 1,  0,   0,  0,  19, 55, 1,   0,   0,  0,  21, 67, 1,  0,   0,  0,  23, 73, 1,  0,   0,   0,
            25, 26, 5,  123, 0,  0,  26, 2,  1,   0,   0,  0,  27, 28, 5,  44,  0,  0,  28, 4,  1,  0,   0,   0,
            29, 30, 5,  125, 0,  0,  30, 6,  1,   0,   0,  0,  31, 32, 5,  58,  0,  0,  32, 8,  1,  0,   0,   0,
            33, 34, 5,  91,  0,  0,  34, 10, 1,   0,   0,  0,  35, 36, 5,  93,  0,  0,  36, 12, 1,  0,   0,   0,
            37, 38, 5,  116, 0,  0,  38, 39, 5,   114, 0,  0,  39, 40, 5,  117, 0,  0,  40, 41, 5,  101, 0,   0,
            41, 14, 1,  0,   0,  0,  42, 43, 5,   102, 0,  0,  43, 44, 5,  97,  0,  0,  44, 45, 5,  108, 0,   0,
            45, 46, 5,  115, 0,  0,  46, 47, 5,   101, 0,  0,  47, 16, 1,  0,   0,  0,  48, 52, 7,  0,   0,   0,
            49, 51, 7,  1,   0,  0,  50, 49, 1,   0,   0,  0,  51, 54, 1,  0,   0,  0,  52, 50, 1,  0,   0,   0,
            52, 53, 1,  0,   0,  0,  53, 18, 1,   0,   0,  0,  54, 52, 1,  0,   0,  0,  55, 61, 5,  34,  0,   0,
            56, 57, 5,  92,  0,  0,  57, 60, 9,   0,   0,  0,  58, 60, 9,  0,   0,  0,  59, 56, 1,  0,   0,   0,
            59, 58, 1,  0,   0,  0,  60, 63, 1,   0,   0,  0,  61, 62, 1,  0,   0,  0,  61, 59, 1,  0,   0,   0,
            62, 64, 1,  0,   0,  0,  63, 61, 1,   0,   0,  0,  64, 65, 5,  34,  0,  0,  65, 20, 1,  0,   0,   0,
            66, 68, 7,  2,   0,  0,  67, 66, 1,   0,   0,  0,  68, 69, 1,  0,   0,  0,  69, 67, 1,  0,   0,   0,
            69, 70, 1,  0,   0,  0,  70, 71, 1,   0,   0,  0,  71, 72, 6,  10,  0,  0,  72, 22, 1,  0,   0,   0,
            73, 77, 5,  35,  0,  0,  74, 76, 8,   3,   0,  0,  75, 74, 1,  0,   0,  0,  76, 79, 1,  0,   0,   0,
            77, 75, 1,  0,   0,  0,  77, 78, 1,   0,   0,  0,  78, 80, 1,  0,   0,  0,  79, 77, 1,  0,   0,   0,
            80, 81, 6,  11,  0,  0,  81, 24, 1,   0,   0,  0,  6,  0,  52, 59,  61, 69, 77, 1,  6,  0,   0};
        staticData->serializedATN =
            antlr4::atn::SerializedATNView(serializedATNSegment,
                                           sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

        antlr4::atn::ATNDeserializer deserializer;
        staticData->atn = deserializer.deserialize(staticData->serializedATN);

        const size_t count = staticData->atn->getNumberOfDecisions();
        staticData->decisionToDFA.reserve(count);
        for (size_t i = 0; i < count; i++)
        {
            staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
        }
        datalexerLexerStaticData = staticData.release();
    }

}

dataLexer::dataLexer(CharStream* input) : Lexer(input)
{
    dataLexer::initialize();
    _interpreter = new atn::LexerATNSimulator(this,
                                              *datalexerLexerStaticData->atn,
                                              datalexerLexerStaticData->decisionToDFA,
                                              datalexerLexerStaticData->sharedContextCache);
}

dataLexer::~dataLexer()
{
    delete _interpreter;
}

std::string dataLexer::getGrammarFileName() const
{
    return "data.g4";
}

std::vector<std::string>& dataLexer::getRuleNames() const {
  return datalexerLexerStaticData->ruleNames;
}

std::vector<std::string> const& dataLexer::getChannelNames() const
{
    return datalexerLexerStaticData->channelNames;
}

std::vector<std::string>& dataLexer::getModeNames() const {
  return datalexerLexerStaticData->modeNames;
}

dfa::Vocabulary const& dataLexer::getVocabulary() const
{
    return datalexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView dataLexer::getSerializedATN() const
{
    return datalexerLexerStaticData->serializedATN;
}

atn::ATN const& dataLexer::getATN() const
{
    return *datalexerLexerStaticData->atn;
}

void dataLexer::initialize()
{
    std::call_once(datalexerLexerOnceFlag, datalexerLexerInitialize);
}
