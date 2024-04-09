
// Generated from ./src/grammar/ance.g4 by ANTLR 4.10.1


#include "anceVisitor.h"

#include "anceParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct AnceParserStaticData final {
  AnceParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  AnceParserStaticData(const AnceParserStaticData&) = delete;
  AnceParserStaticData(AnceParserStaticData&&) = delete;
  AnceParserStaticData& operator=(const AnceParserStaticData&) = delete;
  AnceParserStaticData& operator=(AnceParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag anceParserOnceFlag;
AnceParserStaticData *anceParserStaticData = nullptr;

void anceParserInitialize() {
  assert(anceParserStaticData == nullptr);
  auto staticData = std::make_unique<AnceParserStaticData>(
    std::vector<std::string>{
      "file", "projectFile", "global", "description", "variableDescription", 
      "functionDescription", "functionBlock", "parameters", "parameter", 
      "typeDescription", "aliasDescription", "structDescription", "member", 
      "accessModifier", "code", "block", "statement", "expressionStatement", 
      "localVariableDefinition", "localReferenceDefinition", "eraseStatement", 
      "assignment", "assigner", "deleteStatement", "breakStatement", "continueStatement", 
      "returnStatement", "assertStatement", "ifStatement", "whileStatement", 
      "loopStatement", "matchStatement", "matchCase", "expression", "unaryOperator", 
      "binaryOperatorMultiplicative", "binaryOperatorAdditive", "binaryOperatorBitwise", 
      "binaryOperatorShift", "binaryOperatorRelational", "binaryOperatorEquality", 
      "independentExpression", "functionCall", "arguments", "variableAccess", 
      "allocation", "allocator", "addressof", "bindRef", "sizeofType", "sizeofExpression", 
      "matchExpression", "matchExpressionCase", "literalExpression", "stringLiteral", 
      "charLiteral", "integerLiteral", "normalInteger", "specialInteger", 
      "floatingPointLiteral", "booleanLiteral", "nullLiteral", "sizeLiteral", 
      "diffLiteral", "uiptrLiteral", "unitLiteral", "type", "integerType", 
      "arrayType", "vectorType", "keywordType", "floatingPointType", "targetDependentType", 
      "booleanType", "charType", "nullPointerType", "unitType", "customType"
    },
    std::vector<std::string>{
      "", "':'", "'('", "')'", "'{'", "'}'", "','", "'define'", "'alias'", 
      "'struct'", "'public'", "'private'", "'extern'", "'let'", "'erase'", 
      "'<:'", "'<-'", "':='", "'delete'", "'break'", "'continue'", "'return'", 
      "'assert'", "'if'", "'then'", "'else'", "'while'", "'do'", "'loop'", 
      "'match'", "'with'", "'|'", "'=>'", "'default'", "'.'", "'['", "']'", 
      "'as'", "'and'", "'or'", "'<'", "'>'", "'<not>'", "'-'", "'*'", "'/'", 
      "'%'", "'+'", "'<and>'", "'<or>'", "'<xor>'", "'<sl>'", "'<sr>'", 
      "'<='", "'>='", "'=='", "'/='", "'new'", "'dynamic'", "'automatic'", 
      "'addressof'", "'ref'", "'to'", "'sizeof'", "'true'", "'false'", "'null'", 
      "'size'", "'diff'", "'uiptr'", "'&'", "'half'", "'single'", "'double'", 
      "'quad'", "'ptr'", "'bool'", "'char'", "'nullptr'", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "'[]'", "'const'", "'not'", "", 
      "';'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "NATIVE_INTEGER_TYPE", 
      "SIGNED_INTEGER", "HEX_INTEGER", "BIN_INTEGER", "OCT_INTEGER", "HALF", 
      "SINGLE", "DOUBLE", "QUAD", "DECIMAL", "STRING", "CHAR", "INTEGER", 
      "BUFFER", "CONST", "NOT", "IDENTIFIER", "SEMICOLON", "WHITESPACE", 
      "BLOCK_COMMENT", "LINE_COMMENT", "ERROR_CHAR"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,100,756,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,7,
  	70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,2,76,7,76,2,77,7,
  	77,1,0,1,0,1,0,1,1,5,1,161,8,1,10,1,12,1,164,9,1,1,1,1,1,1,2,5,2,169,
  	8,2,10,2,12,2,172,9,2,1,3,1,3,1,3,3,3,177,8,3,1,4,1,4,3,4,181,8,4,1,4,
  	1,4,1,4,3,4,186,8,4,1,4,1,4,1,4,3,4,191,8,4,1,4,1,4,1,5,1,5,1,5,1,5,1,
  	5,1,5,1,5,3,5,202,8,5,1,5,1,5,3,5,206,8,5,1,6,1,6,5,6,210,8,6,10,6,12,
  	6,213,9,6,1,6,1,6,1,7,1,7,1,7,5,7,220,8,7,10,7,12,7,223,9,7,3,7,225,8,
  	7,1,8,1,8,1,8,1,8,1,9,1,9,3,9,233,8,9,1,10,1,10,1,10,1,10,1,10,1,10,1,
  	10,1,11,1,11,1,11,1,11,1,11,5,11,247,8,11,10,11,12,11,250,9,11,1,11,1,
  	11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,3,12,261,8,12,1,12,1,12,1,13,1,
  	13,1,13,3,13,268,8,13,1,14,1,14,3,14,272,8,14,1,15,1,15,5,15,276,8,15,
  	10,15,12,15,279,9,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,
  	1,16,1,16,1,16,1,16,1,16,1,16,3,16,297,8,16,1,17,1,17,1,17,1,18,1,18,
  	1,18,1,18,3,18,306,8,18,1,18,1,18,1,18,3,18,311,8,18,1,18,1,18,1,19,1,
  	19,1,19,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,21,1,21,1,21,1,21,1,
  	21,1,22,1,22,1,22,3,22,334,8,22,1,23,1,23,3,23,338,8,23,1,23,1,23,1,23,
  	1,24,1,24,1,24,1,25,1,25,1,25,1,26,1,26,3,26,351,8,26,1,26,1,26,1,27,
  	1,27,1,27,1,27,1,28,1,28,1,28,1,28,1,28,1,28,3,28,365,8,28,1,29,1,29,
  	1,29,1,29,1,29,1,30,1,30,1,30,1,31,1,31,1,31,1,31,1,31,5,31,380,8,31,
  	10,31,12,31,383,9,31,1,31,1,31,1,32,1,32,1,32,5,32,390,8,32,10,32,12,
  	32,393,9,32,1,32,1,32,1,32,1,32,1,32,1,32,3,32,401,8,32,1,33,1,33,1,33,
  	1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,
  	1,33,1,33,1,33,1,33,1,33,3,33,425,8,33,1,33,1,33,1,33,1,33,1,33,3,33,
  	432,8,33,1,33,1,33,1,33,5,33,437,8,33,10,33,12,33,440,9,33,1,33,1,33,
  	1,33,1,33,1,33,1,33,3,33,448,8,33,1,33,1,33,1,33,5,33,453,8,33,10,33,
  	12,33,456,9,33,1,33,1,33,3,33,460,8,33,1,33,1,33,1,33,1,33,1,33,1,33,
  	1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,
  	1,33,1,33,1,33,1,33,1,33,1,33,3,33,488,8,33,1,33,1,33,1,33,1,33,3,33,
  	494,8,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,
  	1,33,1,33,5,33,510,8,33,10,33,12,33,513,9,33,1,34,1,34,1,34,3,34,518,
  	8,34,1,35,1,35,1,35,3,35,523,8,35,1,36,1,36,3,36,527,8,36,1,37,1,37,1,
  	37,3,37,532,8,37,1,38,1,38,3,38,536,8,38,1,39,1,39,1,39,1,39,3,39,542,
  	8,39,1,40,1,40,3,40,546,8,40,1,41,1,41,1,42,1,42,1,42,1,42,1,42,1,42,
  	1,42,1,42,1,42,1,42,3,42,560,8,42,1,43,1,43,1,43,5,43,565,8,43,10,43,
  	12,43,568,9,43,3,43,570,8,43,1,44,1,44,1,45,1,45,1,45,1,45,1,45,3,45,
  	579,8,45,1,45,1,45,1,45,1,46,1,46,3,46,586,8,46,1,47,1,47,1,47,1,48,1,
  	48,1,48,1,48,1,48,3,48,596,8,48,1,49,1,49,1,49,1,50,1,50,1,50,1,50,1,
  	50,1,51,1,51,1,51,1,51,1,51,1,51,1,51,5,51,613,8,51,10,51,12,51,616,9,
  	51,3,51,618,8,51,1,51,1,51,1,52,1,52,1,52,5,52,625,8,52,10,52,12,52,628,
  	9,52,1,52,1,52,1,52,1,52,1,52,1,52,3,52,636,8,52,1,53,1,53,1,53,1,53,
  	1,53,1,53,1,53,1,53,1,53,1,53,3,53,648,8,53,1,54,3,54,651,8,54,1,54,1,
  	54,1,55,3,55,656,8,55,1,55,1,55,1,56,1,56,3,56,662,8,56,1,57,1,57,3,57,
  	666,8,57,1,57,1,57,3,57,670,8,57,1,58,1,58,1,58,1,58,1,58,1,58,1,58,1,
  	58,1,58,3,58,681,8,58,1,59,1,59,1,60,1,60,3,60,687,8,60,1,61,1,61,1,62,
  	1,62,1,62,1,62,1,63,1,63,1,63,1,63,1,64,1,64,1,64,1,64,1,65,1,65,1,65,
  	1,66,1,66,1,66,1,66,1,66,1,66,1,66,1,66,1,66,1,66,1,66,3,66,717,8,66,
  	1,67,1,67,1,68,1,68,1,68,1,68,1,68,1,68,1,69,1,69,1,69,1,69,1,69,1,69,
  	1,70,1,70,1,70,1,70,1,70,1,70,3,70,739,8,70,1,71,1,71,1,72,1,72,1,73,
  	1,73,1,74,1,74,1,75,1,75,1,76,1,76,1,76,1,77,1,77,1,77,0,1,66,78,0,2,
  	4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,
  	52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,
  	98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,
  	134,136,138,140,142,144,146,148,150,152,154,0,4,2,0,91,91,95,95,1,0,84,
  	87,1,0,71,74,2,0,67,69,75,75,802,0,156,1,0,0,0,2,162,1,0,0,0,4,170,1,
  	0,0,0,6,176,1,0,0,0,8,178,1,0,0,0,10,194,1,0,0,0,12,207,1,0,0,0,14,224,
  	1,0,0,0,16,226,1,0,0,0,18,232,1,0,0,0,20,234,1,0,0,0,22,241,1,0,0,0,24,
  	253,1,0,0,0,26,267,1,0,0,0,28,271,1,0,0,0,30,273,1,0,0,0,32,296,1,0,0,
  	0,34,298,1,0,0,0,36,301,1,0,0,0,38,314,1,0,0,0,40,321,1,0,0,0,42,325,
  	1,0,0,0,44,333,1,0,0,0,46,335,1,0,0,0,48,342,1,0,0,0,50,345,1,0,0,0,52,
  	348,1,0,0,0,54,354,1,0,0,0,56,358,1,0,0,0,58,366,1,0,0,0,60,371,1,0,0,
  	0,62,374,1,0,0,0,64,400,1,0,0,0,66,459,1,0,0,0,68,517,1,0,0,0,70,522,
  	1,0,0,0,72,526,1,0,0,0,74,531,1,0,0,0,76,535,1,0,0,0,78,541,1,0,0,0,80,
  	545,1,0,0,0,82,547,1,0,0,0,84,559,1,0,0,0,86,569,1,0,0,0,88,571,1,0,0,
  	0,90,573,1,0,0,0,92,585,1,0,0,0,94,587,1,0,0,0,96,595,1,0,0,0,98,597,
  	1,0,0,0,100,600,1,0,0,0,102,605,1,0,0,0,104,635,1,0,0,0,106,647,1,0,0,
  	0,108,650,1,0,0,0,110,655,1,0,0,0,112,661,1,0,0,0,114,665,1,0,0,0,116,
  	680,1,0,0,0,118,682,1,0,0,0,120,686,1,0,0,0,122,688,1,0,0,0,124,690,1,
  	0,0,0,126,694,1,0,0,0,128,698,1,0,0,0,130,702,1,0,0,0,132,716,1,0,0,0,
  	134,718,1,0,0,0,136,720,1,0,0,0,138,726,1,0,0,0,140,738,1,0,0,0,142,740,
  	1,0,0,0,144,742,1,0,0,0,146,744,1,0,0,0,148,746,1,0,0,0,150,748,1,0,0,
  	0,152,750,1,0,0,0,154,753,1,0,0,0,156,157,3,4,2,0,157,158,5,0,0,1,158,
  	1,1,0,0,0,159,161,3,28,14,0,160,159,1,0,0,0,161,164,1,0,0,0,162,160,1,
  	0,0,0,162,163,1,0,0,0,163,165,1,0,0,0,164,162,1,0,0,0,165,166,5,0,0,1,
  	166,3,1,0,0,0,167,169,3,6,3,0,168,167,1,0,0,0,169,172,1,0,0,0,170,168,
  	1,0,0,0,170,171,1,0,0,0,171,5,1,0,0,0,172,170,1,0,0,0,173,177,3,8,4,0,
  	174,177,3,10,5,0,175,177,3,18,9,0,176,173,1,0,0,0,176,174,1,0,0,0,176,
  	175,1,0,0,0,177,7,1,0,0,0,178,180,3,26,13,0,179,181,5,93,0,0,180,179,
  	1,0,0,0,180,181,1,0,0,0,181,182,1,0,0,0,182,185,5,95,0,0,183,184,5,1,
  	0,0,184,186,3,132,66,0,185,183,1,0,0,0,185,186,1,0,0,0,186,190,1,0,0,
  	0,187,188,3,44,22,0,188,189,3,66,33,0,189,191,1,0,0,0,190,187,1,0,0,0,
  	190,191,1,0,0,0,191,192,1,0,0,0,192,193,5,96,0,0,193,9,1,0,0,0,194,195,
  	3,26,13,0,195,196,5,95,0,0,196,197,5,2,0,0,197,198,3,14,7,0,198,201,5,
  	3,0,0,199,200,5,1,0,0,200,202,3,132,66,0,201,199,1,0,0,0,201,202,1,0,
  	0,0,202,205,1,0,0,0,203,206,3,12,6,0,204,206,5,96,0,0,205,203,1,0,0,0,
  	205,204,1,0,0,0,206,11,1,0,0,0,207,211,5,4,0,0,208,210,3,28,14,0,209,
  	208,1,0,0,0,210,213,1,0,0,0,211,209,1,0,0,0,211,212,1,0,0,0,212,214,1,
  	0,0,0,213,211,1,0,0,0,214,215,5,5,0,0,215,13,1,0,0,0,216,221,3,16,8,0,
  	217,218,5,6,0,0,218,220,3,16,8,0,219,217,1,0,0,0,220,223,1,0,0,0,221,
  	219,1,0,0,0,221,222,1,0,0,0,222,225,1,0,0,0,223,221,1,0,0,0,224,216,1,
  	0,0,0,224,225,1,0,0,0,225,15,1,0,0,0,226,227,5,95,0,0,227,228,5,1,0,0,
  	228,229,3,132,66,0,229,17,1,0,0,0,230,233,3,20,10,0,231,233,3,22,11,0,
  	232,230,1,0,0,0,232,231,1,0,0,0,233,19,1,0,0,0,234,235,3,26,13,0,235,
  	236,5,7,0,0,236,237,5,95,0,0,237,238,5,8,0,0,238,239,3,132,66,0,239,240,
  	5,96,0,0,240,21,1,0,0,0,241,242,3,26,13,0,242,243,5,9,0,0,243,244,5,95,
  	0,0,244,248,5,4,0,0,245,247,3,24,12,0,246,245,1,0,0,0,247,250,1,0,0,0,
  	248,246,1,0,0,0,248,249,1,0,0,0,249,251,1,0,0,0,250,248,1,0,0,0,251,252,
  	5,5,0,0,252,23,1,0,0,0,253,254,3,26,13,0,254,255,5,95,0,0,255,256,5,1,
  	0,0,256,260,3,132,66,0,257,258,3,44,22,0,258,259,3,106,53,0,259,261,1,
  	0,0,0,260,257,1,0,0,0,260,261,1,0,0,0,261,262,1,0,0,0,262,263,5,96,0,
  	0,263,25,1,0,0,0,264,268,5,10,0,0,265,268,5,11,0,0,266,268,5,12,0,0,267,
  	264,1,0,0,0,267,265,1,0,0,0,267,266,1,0,0,0,268,27,1,0,0,0,269,272,3,
  	32,16,0,270,272,3,30,15,0,271,269,1,0,0,0,271,270,1,0,0,0,272,29,1,0,
  	0,0,273,277,5,4,0,0,274,276,3,28,14,0,275,274,1,0,0,0,276,279,1,0,0,0,
  	277,275,1,0,0,0,277,278,1,0,0,0,278,280,1,0,0,0,279,277,1,0,0,0,280,281, 5,   5,   0,   0,   281, 31,  1,   0,   0,   0,
      282, 297, 3,   34,  17,  0,   283, 297, 3,   56,  28,  0,   284, 297, 3,   36,  18,  0,   285, 297, 3,   38,  19,
      0,   286, 297, 3,   40,  20,  0,   287, 297, 3,   42,  21,  0,   288, 297, 3,   46,  23,  0,   289, 297, 3,   48,
      24,  0,   290, 297, 3,   50,  25,  0,   291, 297, 3,   52,  26,  0,   292, 297, 3,   54,  27,  0,   293, 297, 3,
      58,  29,  0,   294, 297, 3,   60,  30,  0,   295, 297, 3,   62,  31,  0,   296, 282, 1,0,0,0,296,283,1,0,0,0,296,284,1,0,0,0,296,285,1,0,0,0,296,286,1,0,0,
  	0,296,287,1,0,0,0,296,288,1,0,0,0,296,289,1,0,0,0,296,290,1,0,0,0,296,
  	291,1,0,0,0,296,292,1,0,0,0,296,293,1,0,0,0,296,294,1,0,0,0,296,295,1,
  	0,0,0,297,33,1,0,0,0,298,299,3,82,41,0,299,300,5,96,0,0,300,35,1,0,0,
  	0,301,302,5,13,0,0,302,305,5,95,0,0,303,304,5,1,0,0,304,306,3,132,66,
  	0,305,303,1,0,0,0,305,306,1,0,0,0,306,310,1,0,0,0,307,308,3,44,22,0,308,
  	309,3,66,33,0,309,311,1,0,0,0,310,307,1,0,0,0,310,311,1,0,0,0,311,312,
  	1,0,0,0,312,313,5,96,0,0,313,37,1,0,0,0,314,315,5,13,0,0,315,316,5,95,
  	0,0,316,317,5,1,0,0,317,318,3,132,66,0,318,319,3,96,48,0,319,320,5,96,
  	0,0,320,39,1,0,0,0,321,322,5,14,0,0,322,323,5,95,0,0,323,324,5,96,0,0,
  	324,41,1,0,0,0,325,326,3,66,33,0,326,327,3,44,22,0,327,328,3,66,33,0,
  	328,329,5,96,0,0,329,43,1,0,0,0,330,334,5,15,0,0,331,334,5,16,0,0,332,
  	334,5,17,0,0,333,330,1,0,0,0,333,331,1,0,0,0,333,332,1,0,0,0,334,45,1,
  	0,0,0,335,337,5,18,0,0,336,338,5,92,0,0,337,336,1,0,0,0,337,338,1,0,0,
  	0,338,339,1,0,0,0,339,340,3,66,33,0,340,341,5,96,0,0,341,47,1,0,0,0,342,
  	343,5,19,0,0,343,344,5,96,0,0,344,49,1,0,0,0,345,346,5,20,0,0,346,347,
  	5,96,0,0,347,51,1,0,0,0,348,350,5,21,0,0,349,351,3,66,33,0,350,349,1,
  	0,0,0,350,351,1,0,0,0,351,352,1,0,0,0,352,353,5,96,0,0,353,53,1,0,0,0,
  	354,355,5,22,0,0,355,356,3,66,33,0,356,357,5,96,0,0,357,55,1,0,0,0,358,
  	359,5,23,0,0,359,360,3,66,33,0,360,361,5,24,0,0,361,364,3,28,14,0,362,
  	363,5,25,0,0,363,365,3,28,14,0,364,362,1,0,0,0,364,365,1,0,0,0,365,57,
  	1,0,0,0,366,367,5,26,0,0,367,368,3,66,33,0,368,369,5,27,0,0,369,370,3,
  	28,14,0,370,59,1,0,0,0,371,372,5,28,0,0,372,373,3,28,14,0,373,61,1,0,
  	0,0,374,375,5,29,0,0,375,376,3,66,33,0,376,377,5,30,0,0,377,381,5,4,0,
  	0,378,380,3,64,32,0,379,378,1,0,0,0,380,383,1,0,0,0,381,379,1,0,0,0,381,
  	382,1,0,0,0,382,384,1,0,0,0,383,381,1,0,0,0,384,385,5,5,0,0,385,63,1,
  	0,0,0,386,391,3,106,53,0,387,388,5,31,0,0,388,390,3,106,53,0,389,387,
  	1,0,0,0,390,393,1,0,0,0,391,389,1,0,0,0,391,392,1,0,0,0,392,394,1,0,0,
  	0,393,391,1,0,0,0,394,395,5,32,0,0,395,396,3,28,14,0,396,401,1,0,0,0,
  	397,398,5,33,0,0,398,399,5,32,0,0,399,401,3,28,14,0,400,386,1,0,0,0,400,
  	397,1,0,0,0,401,65,1,0,0,0,402,403,6,33,-1,0,403,460,3,88,44,0,404,460,
  	3,90,45,0,405,460,3,106,53,0,406,460,3,94,47,0,407,460,3,96,48,0,408,
  	460,3,98,49,0,409,460,3,100,50,0,410,460,3,82,41,0,411,412,5,2,0,0,412,
  	413,3,66,33,0,413,414,5,3,0,0,414,460,1,0,0,0,415,416,3,68,34,0,416,417,
  	3,66,33,13,417,460,1,0,0,0,418,419,5,23,0,0,419,420,3,66,33,0,420,421,
  	5,24,0,0,421,424,3,66,33,0,422,423,5,25,0,0,423,425,3,66,33,0,424,422,
  	1,0,0,0,424,425,1,0,0,0,425,460,1,0,0,0,426,460,3,102,51,0,427,431,5,
  	40,0,0,428,429,3,132,66,0,429,430,5,31,0,0,430,432,1,0,0,0,431,428,1,
  	0,0,0,431,432,1,0,0,0,432,433,1,0,0,0,433,438,3,66,33,0,434,435,5,6,0,
  	0,435,437,3,66,33,0,436,434,1,0,0,0,437,440,1,0,0,0,438,436,1,0,0,0,438,
  	439,1,0,0,0,439,441,1,0,0,0,440,438,1,0,0,0,441,442,5,41,0,0,442,460,
  	1,0,0,0,443,447,5,35,0,0,444,445,3,132,66,0,445,446,5,31,0,0,446,448,
  	1,0,0,0,447,444,1,0,0,0,447,448,1,0,0,0,448,449,1,0,0,0,449,454,3,66,
  	33,0,450,451,5,6,0,0,451,453,3,66,33,0,452,450,1,0,0,0,453,456,1,0,0,
  	0,454,452,1,0,0,0,454,455,1,0,0,0,455,457,1,0,0,0,456,454,1,0,0,0,457,
  	458,5,36,0,0,458,460,1,0,0,0,459,402,1,0,0,0,459,404,1,0,0,0,459,405,
  	1,0,0,0,459,406,1,0,0,0,459,407,1,0,0,0,459,408,1,0,0,0,459,409,1,0,0,
  	0,459,410,1,0,0,0,459,411,1,0,0,0,459,415,1,0,0,0,459,418,1,0,0,0,459,
  	426,1,0,0,0,459,427,1,0,0,0,459,443,1,0,0,0,460,511,1,0,0,0,461,462,10,
  	12,0,0,462,463,3,70,35,0,463,464,3,66,33,13,464,510,1,0,0,0,465,466,10,
  	11,0,0,466,467,3,72,36,0,467,468,3,66,33,12,468,510,1,0,0,0,469,470,10,
  	10,0,0,470,471,3,74,37,0,471,472,3,66,33,11,472,510,1,0,0,0,473,474,10,
  	9,0,0,474,475,3,76,38,0,475,476,3,66,33,10,476,510,1,0,0,0,477,478,10,
  	8,0,0,478,479,3,78,39,0,479,480,3,66,33,9,480,510,1,0,0,0,481,482,10,
  	7,0,0,482,483,3,80,40,0,483,484,3,66,33,8,484,510,1,0,0,0,485,487,10,
  	6,0,0,486,488,5,94,0,0,487,486,1,0,0,0,487,488,1,0,0,0,488,489,1,0,0,
  	0,489,490,5,38,0,0,490,510,3,66,33,7,491,493,10,5,0,0,492,494,5,94,0,
  	0,493,492,1,0,0,0,493,494,1,0,0,0,494,495,1,0,0,0,495,496,5,39,0,0,496,
  	510,3,66,33,6,497,498,10,23,0,0,498,510,5,34,0,0,499,500,10,22,0,0,500,
  	501,5,35,0,0,501,502,3,66,33,0,502,503,5,36,0,0,503,510,1,0,0,0,504,505,
  	10,21,0,0,505,510,5,95,0,0,506,507,10,16,0,0,507,508,5,37,0,0,508,510,
  	3,132,66,0,509,461,1,0,0,0,509,465,1,0,0,0,509,469,1,0,0,0,509,473,1,
  	0,0,0,509,477,1,0,0,0,509,481,1,0,0,0,509,485,1,0,0,0,509,491,1,0,0,0,
  	509,497,1,0,0,0,509,499,1,0,0,0,509,504,1,0,0,0,509,506,1,0,0,0,510,513,
  	1,0,0,0,511,509,1,0,0,0,511,512,1,0,0,0,512,67,1,0,0,0,513,511,1,0,0,
  	0,514,518,5,94,0,0,515,518,5,42,0,0,516,518,5,43,0,0,517,514,1,0,0,0,
  	517,515,1,0,0,0,517,516,1,0,0,0,518,69,1,0,0,0,519,523,5,44,0,0,520,523,
  	5,45,0,0,521,523,5,46,0,0,522,519,1,0,0,0,522,520,1,0,0,0,522,521,1,0,
  	0,0,523,71,1,0,0,0,524,527,5,47,0,0,525,527,5,43,0,0,526,524,1,0,0,0,
  	526,525,1,0,0,0,527,73,1,0,0,0,528,532,5,48,0,0,529,532,5,49,0,0,530,
  	532,5,50,0,0,531,528,1,0,0,0,531,529,1,0,0,0,531,530,1,0,0,0,532,75,1,
  	0,0,0,533,536,5,51,0,0,534,536,5,52,0,0,535,533,1,0,0,0,535,534,1,0,0,
  	0,536,77,1,0,0,0,537,542,5,40,0,0,538,542,5,53,0,0,539,542,5,41,0,0,540,
  	542,5,54,0,0,541,537,1,0,0,0,541,538,1,0,0,0,541,539,1,0,0,0,541,540,
  	1,0,0,0,542,79,1,0,0,0,543,546,5,55,0,0,544,546,5,56,0,0,545,543,1,0,
  	0,0,545,544,1,0,0,0,546,81,1,0,0,0,547,548,3,84,42,0,548,83,1,0,0,0,549,
  	550,5,95,0,0,550,551,5,2,0,0,551,552,3,86,43,0,552,553,5,3,0,0,553,560,
  	1,0,0,0,554,555,3,132,66,0,555,556,5,2,0,0,556,557,3,86,43,0,557,558,
  	5,3,0,0,558,560,1,0,0,0,559,549,1,0,0,0,559,554,1,0,0,0,560,85,1,0,0,
  	0,561,566,3,66,33,0,562,563,5,6,0,0,563,565,3,66,33,0,564,562,1,0,0,0,
  	565,568,1,0,0,0,566,564,1,0,0,0,566,567,1,0,0,0,567,570,1,0,0,0,568,566,
  	1,0,0,0,569,561,1,0,0,0,569,570,1,0,0,0,570,87,1,0,0,0,571,572,5,95,0,
  	0,572,89,1,0,0,0,573,578,5,57,0,0,574,575,5,35,0,0,575,576,3,66,33,0,
  	576,577,5,36,0,0,577,579,1,0,0,0,578,574,1,0,0,0,578,579,1,0,0,0,579,
  	580,1,0,0,0,580,581,3,92,46,0,581,582,3,132,66,0,582,91,1,0,0,0,583,586,
  	5,58,0,0,584,586,5,59,0,0,585,583,1,0,0,0,585,584,1,0,0,0,586,93,1,0,
  	0,0,587,588,5,60,0,0,588,589,3,66,33,0,589,95,1,0,0,0,590,591,5,61,0,
  	0,591,596,3,66,33,0,592,593,5,61,0,0,593,594,5,62,0,0,594,596,3,66,33,
  	0,595,590,1,0,0,0,595,592,1,0,0,0,596,97,1,0,0,0,597,598,5,63,0,0,598,
  	599,3,132,66,0,599,99,1,0,0,0,600,601,5,63,0,0,601,602,5,2,0,0,602,603,
  	3,66,33,0,603,604,5,3,0,0,604,101,1,0,0,0,605,606,5,29,0,0,606,607,3,
  	66,33,0,607,608,5,30,0,0,608,617,5,4,0,0,609,614,3,104,52,0,610,611,5,
  	6,0,0,611,613,3,104,52,0,612,610,1,0,0,0,613,616,1,0,0,0,614,612,1,0,
  	0,0,614,615,1,0,0,0,615,618,1,0,0,0,616,614,1,0,0,0,617,609,1,0,0,0,617,
  	618,1,0,0,0,618,619,1,0,0,0,619,620,5,5,0,0,620,103,1,0,0,0,621,626,3,
  	106,53,0,622,623,5,31,0,0,623,625,3,106,53,0,624,622,1,0,0,0,625,628,
  	1,0,0,0,626,624,1,0,0,0,626,627,1,0,0,0,627,629,1,0,0,0,628,626,1,0,0,
  	0,629,630,5,32,0,0,630,631,3,66,33,0,631,636,1,0,0,0,632,633,5,33,0,0,
  	633,634,5,32,0,0,634,636,3,66,33,0,635,621,1,0,0,0,635,632,1,0,0,0,636,
  	105,1,0,0,0,637,648,3,108,54,0,638,648,3,110,55,0,639,648,3,112,56,0,
  	640,648,3,118,59,0,641,648,3,120,60,0,642,648,3,122,61,0,643,648,3,124,
  	62,0,644,648,3,126,63,0,645,648,3,128,64,0,646,648,3,130,65,0,647,637,
  	1,0,0,0,647,638,1,0,0,0,647,639,1,0,0,0,647,640,1,0,0,0,647,641,1,0,0,
  	0,647,642,1,0,0,0,647,643,1,0,0,0,647,644,1,0,0,0,647,645,1,0,0,0,647,
  	646,1,0,0,0,648,107,1,0,0,0,649,651,7,0,0,0,650,649,1,0,0,0,650,651,1,
  	0,0,0,651,652,1,0,0,0,652,653,5,89,0,0,653,109,1,0,0,0,654,656,7,0,0,
  	0,655,654,1,0,0,0,655,656,1,0,0,0,656,657,1,0,0,0,657,658,5,90,0,0,658,
  	111,1,0,0,0,659,662,3,114,57,0,660,662,3,116,58,0,661,659,1,0,0,0,661,
  	660,1,0,0,0,662,113,1,0,0,0,663,666,5,91,0,0,664,666,5,80,0,0,665,663,
  	1,0,0,0,665,664,1,0,0,0,666,669,1,0,0,0,667,668,5,1,0,0,668,670,5,91,
  	0,0,669,667,1,0,0,0,669,670,1,0,0,0,670,115,1,0,0,0,671,672,5,81,0,0,
  	672,673,5,1,0,0,673,681,5,91,0,0,674,675,5,82,0,0,675,676,5,1,0,0,676,
  	681,5,91,0,0,677,678,5,83,0,0,678,679,5,1,0,0,679,681,5,91,0,0,680,671,
  	1,0,0,0,680,674,1,0,0,0,680,677,1,0,0,0,681,117,1,0,0,0,682,683,7,1,0,
  	0,683,119,1,0,0,0,684,687,5,64,0,0,685,687,5,65,0,0,686,684,1,0,0,0,686,
  	685,1,0,0,0,687,121,1,0,0,0,688,689,5,66,0,0,689,123,1,0,0,0,690,691,
  	5,91,0,0,691,692,5,1,0,0,692,693,5,67,0,0,693,125,1,0,0,0,694,695,5,80,
  	0,0,695,696,5,1,0,0,696,697,5,68,0,0,697,127,1,0,0,0,698,699,5,81,0,0,
  	699,700,5,1,0,0,700,701,5,69,0,0,701,129,1,0,0,0,702,703,5,2,0,0,703,
  	704,5,3,0,0,704,131,1,0,0,0,705,717,3,134,67,0,706,717,3,136,68,0,707,
  	717,3,138,69,0,708,717,3,140,70,0,709,710,5,44,0,0,710,717,3,132,66,0,
  	711,712,5,92,0,0,712,717,3,132,66,0,713,714,5,70,0,0,714,717,3,132,66,
  	0,715,717,3,154,77,0,716,705,1,0,0,0,716,706,1,0,0,0,716,707,1,0,0,0,
  	716,708,1,0,0,0,716,709,1,0,0,0,716,711,1,0,0,0,716,713,1,0,0,0,716,715,
  	1,0,0,0,717,133,1,0,0,0,718,719,5,79,0,0,719,135,1,0,0,0,720,721,5,35,
  	0,0,721,722,3,132,66,0,722,723,5,96,0,0,723,724,5,91,0,0,724,725,5,36,
  	0,0,725,137,1,0,0,0,726,727,5,40,0,0,727,728,3,132,66,0,728,729,5,96,
  	0,0,729,730,5,91,0,0,730,731,5,41,0,0,731,139,1,0,0,0,732,739,3,142,71,
  	0,733,739,3,144,72,0,734,739,3,146,73,0,735,739,3,148,74,0,736,739,3,
  	150,75,0,737,739,3,152,76,0,738,732,1,0,0,0,738,733,1,0,0,0,738,734,1,
  	0,0,0,738,735,1,0,0,0,738,736,1,0,0,0,738,737,1,0,0,0,739,141,1,0,0,0,
  	740,741,7,2,0,0,741,143,1,0,0,0,742,743,7,3,0,0,743,145,1,0,0,0,744,745,
  	5,76,0,0,745,147,1,0,0,0,746,747,5,77,0,0,747,149,1,0,0,0,748,749,5,78,
  	0,0,749,151,1,0,0,0,750,751,5,2,0,0,751,752,5,3,0,0,752,153,1,0,0,0,753,
  	754,5,95,0,0,754,155,1,0,0,0,64,162,170,176,180,185,190,201,205,211,221,
  	224,232,248,260,267,271,277,296,305,310,333,337,350,364,381,391,400,424,
  	431,438,447,454,459,487,493,509,511,517,522,526,531,535,541,545,559,566,
  	569,578,585,595,614,617,626,635,647,650,655,661,665,669,680,686,716,738
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  anceParserStaticData = staticData.release();
}

}

anceParser::anceParser(TokenStream *input) : anceParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

anceParser::anceParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  anceParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *anceParserStaticData->atn, anceParserStaticData->decisionToDFA, anceParserStaticData->sharedContextCache, options);
}

anceParser::~anceParser() {
  delete _interpreter;
}

const atn::ATN& anceParser::getATN() const {
  return *anceParserStaticData->atn;
}

std::string anceParser::getGrammarFileName() const {
  return "ance.g4";
}

const std::vector<std::string>& anceParser::getRuleNames() const {
  return anceParserStaticData->ruleNames;
}

const dfa::Vocabulary& anceParser::getVocabulary() const {
  return anceParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView anceParser::getSerializedATN() const {
  return anceParserStaticData->serializedATN;
}


//----------------- FileContext ------------------------------------------------------------------

anceParser::FileContext::FileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::GlobalContext* anceParser::FileContext::global() {
  return getRuleContext<anceParser::GlobalContext>(0);
}

tree::TerminalNode* anceParser::FileContext::EOF() {
  return getToken(anceParser::EOF, 0);
}


size_t anceParser::FileContext::getRuleIndex() const {
  return anceParser::RuleFile;
}


std::any anceParser::FileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFile(this);
  else
    return visitor->visitChildren(this);
}

anceParser::FileContext* anceParser::file() {
  FileContext *_localctx = _tracker.createInstance<FileContext>(_ctx, getState());
  enterRule(_localctx, 0, anceParser::RuleFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(156);
    global();
    setState(157);
    match(anceParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProjectFileContext ------------------------------------------------------------------

anceParser::ProjectFileContext::ProjectFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::ProjectFileContext::EOF() {
  return getToken(anceParser::EOF, 0);
}

std::vector<anceParser::CodeContext *> anceParser::ProjectFileContext::code() {
  return getRuleContexts<anceParser::CodeContext>();
}

anceParser::CodeContext* anceParser::ProjectFileContext::code(size_t i) {
  return getRuleContext<anceParser::CodeContext>(i);
}


size_t anceParser::ProjectFileContext::getRuleIndex() const {
  return anceParser::RuleProjectFile;
}


std::any anceParser::ProjectFileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitProjectFile(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ProjectFileContext* anceParser::projectFile() {
  ProjectFileContext *_localctx = _tracker.createInstance<ProjectFileContext>(_ctx, getState());
  enterRule(_localctx, 2, anceParser::RuleProjectFile);
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
    setState(162);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__1)
      | (1ULL << anceParser::T__3)
      | (1ULL << anceParser::T__12)
      | (1ULL << anceParser::T__13)
      | (1ULL << anceParser::T__17)
      | (1ULL << anceParser::T__18)
      | (1ULL << anceParser::T__19)
      | (1ULL << anceParser::T__20)
      | (1ULL << anceParser::T__21)
      | (1ULL << anceParser::T__22)
      | (1ULL << anceParser::T__25)
      | (1ULL << anceParser::T__27)
      | (1ULL << anceParser::T__28)
      | (1ULL << anceParser::T__34)
      | (1ULL << anceParser::T__39)
      | (1ULL << anceParser::T__41)
      | (1ULL << anceParser::T__42)
      | (1ULL << anceParser::T__43)
      | (1ULL << anceParser::T__56)
      | (1ULL << anceParser::T__59)
      | (1ULL << anceParser::T__60)
      | (1ULL << anceParser::T__62))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (anceParser::T__63 - 64))
      | (1ULL << (anceParser::T__64 - 64))
      | (1ULL << (anceParser::T__65 - 64))
      | (1ULL << (anceParser::T__66 - 64))
      | (1ULL << (anceParser::T__67 - 64))
      | (1ULL << (anceParser::T__68 - 64))
      | (1ULL << (anceParser::T__69 - 64))
      | (1ULL << (anceParser::T__70 - 64))
      | (1ULL << (anceParser::T__71 - 64))
      | (1ULL << (anceParser::T__72 - 64))
      | (1ULL << (anceParser::T__73 - 64))
      | (1ULL << (anceParser::T__74 - 64))
      | (1ULL << (anceParser::T__75 - 64))
      | (1ULL << (anceParser::T__76 - 64))
      | (1ULL << (anceParser::T__77 - 64))
      | (1ULL << (anceParser::NATIVE_INTEGER_TYPE - 64))
      | (1ULL << (anceParser::SIGNED_INTEGER - 64))
      | (1ULL << (anceParser::HEX_INTEGER - 64))
      | (1ULL << (anceParser::BIN_INTEGER - 64))
      | (1ULL << (anceParser::OCT_INTEGER - 64))
      | (1ULL << (anceParser::HALF - 64))
      | (1ULL << (anceParser::SINGLE - 64))
      | (1ULL << (anceParser::DOUBLE - 64))
      | (1ULL << (anceParser::QUAD - 64))
      | (1ULL << (anceParser::STRING - 64))
      | (1ULL << (anceParser::CHAR - 64))
      | (1ULL << (anceParser::INTEGER - 64))
      | (1ULL << (anceParser::BUFFER - 64))
      | (1ULL << (anceParser::NOT - 64))
      | (1ULL << (anceParser::IDENTIFIER - 64)))) != 0)) {
      setState(159);
      code();
      setState(164);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(165);
    match(anceParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GlobalContext ------------------------------------------------------------------

anceParser::GlobalContext::GlobalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<anceParser::DescriptionContext *> anceParser::GlobalContext::description() {
  return getRuleContexts<anceParser::DescriptionContext>();
}

anceParser::DescriptionContext* anceParser::GlobalContext::description(size_t i) {
  return getRuleContext<anceParser::DescriptionContext>(i);
}


size_t anceParser::GlobalContext::getRuleIndex() const {
  return anceParser::RuleGlobal;
}


std::any anceParser::GlobalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitGlobal(this);
  else
    return visitor->visitChildren(this);
}

anceParser::GlobalContext* anceParser::global() {
  GlobalContext *_localctx = _tracker.createInstance<GlobalContext>(_ctx, getState());
  enterRule(_localctx, 4, anceParser::RuleGlobal);
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
    setState(170);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__9)
      | (1ULL << anceParser::T__10)
      | (1ULL << anceParser::T__11))) != 0)) {
      setState(167);
      description();
      setState(172);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DescriptionContext ------------------------------------------------------------------

anceParser::DescriptionContext::DescriptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::VariableDescriptionContext* anceParser::DescriptionContext::variableDescription() {
  return getRuleContext<anceParser::VariableDescriptionContext>(0);
}

anceParser::FunctionDescriptionContext* anceParser::DescriptionContext::functionDescription() {
  return getRuleContext<anceParser::FunctionDescriptionContext>(0);
}

anceParser::TypeDescriptionContext* anceParser::DescriptionContext::typeDescription() {
  return getRuleContext<anceParser::TypeDescriptionContext>(0);
}


size_t anceParser::DescriptionContext::getRuleIndex() const {
  return anceParser::RuleDescription;
}


std::any anceParser::DescriptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitDescription(this);
  else
    return visitor->visitChildren(this);
}

anceParser::DescriptionContext* anceParser::description() {
  DescriptionContext *_localctx = _tracker.createInstance<DescriptionContext>(_ctx, getState());
  enterRule(_localctx, 6, anceParser::RuleDescription);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(176);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(173);
      variableDescription();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(174);
      functionDescription();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(175);
      typeDescription();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDescriptionContext ------------------------------------------------------------------

anceParser::VariableDescriptionContext::VariableDescriptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AccessModifierContext* anceParser::VariableDescriptionContext::accessModifier() {
  return getRuleContext<anceParser::AccessModifierContext>(0);
}

tree::TerminalNode* anceParser::VariableDescriptionContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::VariableDescriptionContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

tree::TerminalNode* anceParser::VariableDescriptionContext::CONST() {
  return getToken(anceParser::CONST, 0);
}

anceParser::TypeContext* anceParser::VariableDescriptionContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::AssignerContext* anceParser::VariableDescriptionContext::assigner() {
  return getRuleContext<anceParser::AssignerContext>(0);
}

anceParser::ExpressionContext* anceParser::VariableDescriptionContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::VariableDescriptionContext::getRuleIndex() const {
  return anceParser::RuleVariableDescription;
}


std::any anceParser::VariableDescriptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVariableDescription(this);
  else
    return visitor->visitChildren(this);
}

anceParser::VariableDescriptionContext* anceParser::variableDescription() {
  VariableDescriptionContext *_localctx = _tracker.createInstance<VariableDescriptionContext>(_ctx, getState());
  enterRule(_localctx, 8, anceParser::RuleVariableDescription);
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
    setState(178);
    accessModifier();
    setState(180);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::CONST) {
      setState(179);
      match(anceParser::CONST);
    }
    setState(182);
    match(anceParser::IDENTIFIER);
    setState(185);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__0) {
      setState(183);
      match(anceParser::T__0);
      setState(184);
      type();
    }
    setState(190);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(187);
      assigner();
      setState(188);
      expression(0);
    }
    setState(192);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDescriptionContext ------------------------------------------------------------------

anceParser::FunctionDescriptionContext::FunctionDescriptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AccessModifierContext* anceParser::FunctionDescriptionContext::accessModifier() {
  return getRuleContext<anceParser::AccessModifierContext>(0);
}

tree::TerminalNode* anceParser::FunctionDescriptionContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ParametersContext* anceParser::FunctionDescriptionContext::parameters() {
  return getRuleContext<anceParser::ParametersContext>(0);
}

anceParser::FunctionBlockContext* anceParser::FunctionDescriptionContext::functionBlock() {
  return getRuleContext<anceParser::FunctionBlockContext>(0);
}

tree::TerminalNode* anceParser::FunctionDescriptionContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

anceParser::TypeContext* anceParser::FunctionDescriptionContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}


size_t anceParser::FunctionDescriptionContext::getRuleIndex() const {
  return anceParser::RuleFunctionDescription;
}


std::any anceParser::FunctionDescriptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFunctionDescription(this);
  else
    return visitor->visitChildren(this);
}

anceParser::FunctionDescriptionContext* anceParser::functionDescription() {
  FunctionDescriptionContext *_localctx = _tracker.createInstance<FunctionDescriptionContext>(_ctx, getState());
  enterRule(_localctx, 10, anceParser::RuleFunctionDescription);
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
    setState(194);
    accessModifier();
    setState(195);
    match(anceParser::IDENTIFIER);
    setState(196);
    match(anceParser::T__1);
    setState(197);
    parameters();
    setState(198);
    match(anceParser::T__2);
    setState(201);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__0) {
      setState(199);
      match(anceParser::T__0);
      setState(200);
      type();
    }
    setState(205);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__3: {
        setState(203);
        functionBlock();
        break;
      }

      case anceParser::SEMICOLON: {
        setState(204);
        match(anceParser::SEMICOLON);
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

//----------------- FunctionBlockContext ------------------------------------------------------------------

anceParser::FunctionBlockContext::FunctionBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<anceParser::CodeContext *> anceParser::FunctionBlockContext::code() {
  return getRuleContexts<anceParser::CodeContext>();
}

anceParser::CodeContext* anceParser::FunctionBlockContext::code(size_t i) {
  return getRuleContext<anceParser::CodeContext>(i);
}


size_t anceParser::FunctionBlockContext::getRuleIndex() const {
  return anceParser::RuleFunctionBlock;
}


std::any anceParser::FunctionBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFunctionBlock(this);
  else
    return visitor->visitChildren(this);
}

anceParser::FunctionBlockContext* anceParser::functionBlock() {
  FunctionBlockContext *_localctx = _tracker.createInstance<FunctionBlockContext>(_ctx, getState());
  enterRule(_localctx, 12, anceParser::RuleFunctionBlock);
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
    setState(207);
    match(anceParser::T__3);
    setState(211);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__1)
      | (1ULL << anceParser::T__3)
      | (1ULL << anceParser::T__12)
      | (1ULL << anceParser::T__13)
      | (1ULL << anceParser::T__17)
      | (1ULL << anceParser::T__18)
      | (1ULL << anceParser::T__19)
      | (1ULL << anceParser::T__20)
      | (1ULL << anceParser::T__21)
      | (1ULL << anceParser::T__22)
      | (1ULL << anceParser::T__25)
      | (1ULL << anceParser::T__27)
      | (1ULL << anceParser::T__28)
      | (1ULL << anceParser::T__34)
      | (1ULL << anceParser::T__39)
      | (1ULL << anceParser::T__41)
      | (1ULL << anceParser::T__42)
      | (1ULL << anceParser::T__43)
      | (1ULL << anceParser::T__56)
      | (1ULL << anceParser::T__59)
      | (1ULL << anceParser::T__60)
      | (1ULL << anceParser::T__62))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (anceParser::T__63 - 64))
      | (1ULL << (anceParser::T__64 - 64))
      | (1ULL << (anceParser::T__65 - 64))
      | (1ULL << (anceParser::T__66 - 64))
      | (1ULL << (anceParser::T__67 - 64))
      | (1ULL << (anceParser::T__68 - 64))
      | (1ULL << (anceParser::T__69 - 64))
      | (1ULL << (anceParser::T__70 - 64))
      | (1ULL << (anceParser::T__71 - 64))
      | (1ULL << (anceParser::T__72 - 64))
      | (1ULL << (anceParser::T__73 - 64))
      | (1ULL << (anceParser::T__74 - 64))
      | (1ULL << (anceParser::T__75 - 64))
      | (1ULL << (anceParser::T__76 - 64))
      | (1ULL << (anceParser::T__77 - 64))
      | (1ULL << (anceParser::NATIVE_INTEGER_TYPE - 64))
      | (1ULL << (anceParser::SIGNED_INTEGER - 64))
      | (1ULL << (anceParser::HEX_INTEGER - 64))
      | (1ULL << (anceParser::BIN_INTEGER - 64))
      | (1ULL << (anceParser::OCT_INTEGER - 64))
      | (1ULL << (anceParser::HALF - 64))
      | (1ULL << (anceParser::SINGLE - 64))
      | (1ULL << (anceParser::DOUBLE - 64))
      | (1ULL << (anceParser::QUAD - 64))
      | (1ULL << (anceParser::STRING - 64))
      | (1ULL << (anceParser::CHAR - 64))
      | (1ULL << (anceParser::INTEGER - 64))
      | (1ULL << (anceParser::BUFFER - 64))
      | (1ULL << (anceParser::NOT - 64))
      | (1ULL << (anceParser::IDENTIFIER - 64)))) != 0)) {
      setState(208);
      code();
      setState(213);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(214);
    match(anceParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParametersContext ------------------------------------------------------------------

anceParser::ParametersContext::ParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<anceParser::ParameterContext *> anceParser::ParametersContext::parameter() {
  return getRuleContexts<anceParser::ParameterContext>();
}

anceParser::ParameterContext* anceParser::ParametersContext::parameter(size_t i) {
  return getRuleContext<anceParser::ParameterContext>(i);
}


size_t anceParser::ParametersContext::getRuleIndex() const {
  return anceParser::RuleParameters;
}


std::any anceParser::ParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitParameters(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ParametersContext* anceParser::parameters() {
  ParametersContext *_localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
  enterRule(_localctx, 14, anceParser::RuleParameters);
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
    setState(224);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::IDENTIFIER) {
      setState(216);
      parameter();
      setState(221);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(217);
        match(anceParser::T__5);
        setState(218);
        parameter();
        setState(223);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterContext ------------------------------------------------------------------

anceParser::ParameterContext::ParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::ParameterContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::ParameterContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}


size_t anceParser::ParameterContext::getRuleIndex() const {
  return anceParser::RuleParameter;
}


std::any anceParser::ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ParameterContext* anceParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 16, anceParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(226);
    match(anceParser::IDENTIFIER);
    setState(227);
    match(anceParser::T__0);
    setState(228);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeDescriptionContext ------------------------------------------------------------------

anceParser::TypeDescriptionContext::TypeDescriptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AliasDescriptionContext* anceParser::TypeDescriptionContext::aliasDescription() {
  return getRuleContext<anceParser::AliasDescriptionContext>(0);
}

anceParser::StructDescriptionContext* anceParser::TypeDescriptionContext::structDescription() {
  return getRuleContext<anceParser::StructDescriptionContext>(0);
}


size_t anceParser::TypeDescriptionContext::getRuleIndex() const {
  return anceParser::RuleTypeDescription;
}


std::any anceParser::TypeDescriptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitTypeDescription(this);
  else
    return visitor->visitChildren(this);
}

anceParser::TypeDescriptionContext* anceParser::typeDescription() {
  TypeDescriptionContext *_localctx = _tracker.createInstance<TypeDescriptionContext>(_ctx, getState());
  enterRule(_localctx, 18, anceParser::RuleTypeDescription);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(232);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(230);
      aliasDescription();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(231);
      structDescription();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AliasDescriptionContext ------------------------------------------------------------------

anceParser::AliasDescriptionContext::AliasDescriptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AccessModifierContext* anceParser::AliasDescriptionContext::accessModifier() {
  return getRuleContext<anceParser::AccessModifierContext>(0);
}

tree::TerminalNode* anceParser::AliasDescriptionContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::AliasDescriptionContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::AliasDescriptionContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}


size_t anceParser::AliasDescriptionContext::getRuleIndex() const {
  return anceParser::RuleAliasDescription;
}


std::any anceParser::AliasDescriptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAliasDescription(this);
  else
    return visitor->visitChildren(this);
}

anceParser::AliasDescriptionContext* anceParser::aliasDescription() {
  AliasDescriptionContext *_localctx = _tracker.createInstance<AliasDescriptionContext>(_ctx, getState());
  enterRule(_localctx, 20, anceParser::RuleAliasDescription);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(234);
    accessModifier();
    setState(235);
    match(anceParser::T__6);
    setState(236);
    match(anceParser::IDENTIFIER);
    setState(237);
    match(anceParser::T__7);
    setState(238);
    type();
    setState(239);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDescriptionContext ------------------------------------------------------------------

anceParser::StructDescriptionContext::StructDescriptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AccessModifierContext* anceParser::StructDescriptionContext::accessModifier() {
  return getRuleContext<anceParser::AccessModifierContext>(0);
}

tree::TerminalNode* anceParser::StructDescriptionContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

std::vector<anceParser::MemberContext *> anceParser::StructDescriptionContext::member() {
  return getRuleContexts<anceParser::MemberContext>();
}

anceParser::MemberContext* anceParser::StructDescriptionContext::member(size_t i) {
  return getRuleContext<anceParser::MemberContext>(i);
}


size_t anceParser::StructDescriptionContext::getRuleIndex() const {
  return anceParser::RuleStructDescription;
}


std::any anceParser::StructDescriptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitStructDescription(this);
  else
    return visitor->visitChildren(this);
}

anceParser::StructDescriptionContext* anceParser::structDescription() {
  StructDescriptionContext *_localctx = _tracker.createInstance<StructDescriptionContext>(_ctx, getState());
  enterRule(_localctx, 22, anceParser::RuleStructDescription);
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
    setState(241);
    accessModifier();
    setState(242);
    match(anceParser::T__8);
    setState(243);
    match(anceParser::IDENTIFIER);
    setState(244);
    match(anceParser::T__3);
    setState(248);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__9)
      | (1ULL << anceParser::T__10)
      | (1ULL << anceParser::T__11))) != 0)) {
      setState(245);
      member();
      setState(250);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(251);
    match(anceParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MemberContext ------------------------------------------------------------------

anceParser::MemberContext::MemberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AccessModifierContext* anceParser::MemberContext::accessModifier() {
  return getRuleContext<anceParser::AccessModifierContext>(0);
}

tree::TerminalNode* anceParser::MemberContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::MemberContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::MemberContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

anceParser::AssignerContext* anceParser::MemberContext::assigner() {
  return getRuleContext<anceParser::AssignerContext>(0);
}

anceParser::LiteralExpressionContext* anceParser::MemberContext::literalExpression() {
  return getRuleContext<anceParser::LiteralExpressionContext>(0);
}


size_t anceParser::MemberContext::getRuleIndex() const {
  return anceParser::RuleMember;
}


std::any anceParser::MemberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitMember(this);
  else
    return visitor->visitChildren(this);
}

anceParser::MemberContext* anceParser::member() {
  MemberContext *_localctx = _tracker.createInstance<MemberContext>(_ctx, getState());
  enterRule(_localctx, 24, anceParser::RuleMember);
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
    setState(253);
    accessModifier();
    setState(254);
    match(anceParser::IDENTIFIER);
    setState(255);
    match(anceParser::T__0);
    setState(256);
    type();
    setState(260);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(257);
      assigner();
      setState(258);
      literalExpression();
    }
    setState(262);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AccessModifierContext ------------------------------------------------------------------

anceParser::AccessModifierContext::AccessModifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::AccessModifierContext::getRuleIndex() const {
  return anceParser::RuleAccessModifier;
}

void anceParser::AccessModifierContext::copyFrom(AccessModifierContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PrivateContext ------------------------------------------------------------------

anceParser::PrivateContext::PrivateContext(AccessModifierContext *ctx) { copyFrom(ctx); }


std::any anceParser::PrivateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitPrivate(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PublicContext ------------------------------------------------------------------

anceParser::PublicContext::PublicContext(AccessModifierContext *ctx) { copyFrom(ctx); }


std::any anceParser::PublicContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitPublic(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExternContext ------------------------------------------------------------------

anceParser::ExternContext::ExternContext(AccessModifierContext *ctx) { copyFrom(ctx); }


std::any anceParser::ExternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitExtern(this);
  else
    return visitor->visitChildren(this);
}
anceParser::AccessModifierContext* anceParser::accessModifier() {
  AccessModifierContext *_localctx = _tracker.createInstance<AccessModifierContext>(_ctx, getState());
  enterRule(_localctx, 26, anceParser::RuleAccessModifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(267);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__9: {
        _localctx = _tracker.createInstance<anceParser::PublicContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(264);
        match(anceParser::T__9);
        break;
      }

      case anceParser::T__10: {
        _localctx = _tracker.createInstance<anceParser::PrivateContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(265);
        match(anceParser::T__10);
        break;
      }

      case anceParser::T__11: {
        _localctx = _tracker.createInstance<anceParser::ExternContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(266);
        match(anceParser::T__11);
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

//----------------- CodeContext ------------------------------------------------------------------

anceParser::CodeContext::CodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::StatementContext* anceParser::CodeContext::statement() {
  return getRuleContext<anceParser::StatementContext>(0);
}

anceParser::BlockContext* anceParser::CodeContext::block() {
  return getRuleContext<anceParser::BlockContext>(0);
}


size_t anceParser::CodeContext::getRuleIndex() const {
  return anceParser::RuleCode;
}


std::any anceParser::CodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitCode(this);
  else
    return visitor->visitChildren(this);
}

anceParser::CodeContext* anceParser::code() {
  CodeContext *_localctx = _tracker.createInstance<CodeContext>(_ctx, getState());
  enterRule(_localctx, 28, anceParser::RuleCode);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(271);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__1:
      case anceParser::T__12:
      case anceParser::T__13:
      case anceParser::T__17:
      case anceParser::T__18:
      case anceParser::T__19:
      case anceParser::T__20:
      case anceParser::T__21:
      case anceParser::T__22:
      case anceParser::T__25:
      case anceParser::T__27:
      case anceParser::T__28:
      case anceParser::T__34:
      case anceParser::T__39:
      case anceParser::T__41:
      case anceParser::T__42:
      case anceParser::T__43:
      case anceParser::T__56:
      case anceParser::T__59:
      case anceParser::T__60:
      case anceParser::T__62:
      case anceParser::T__63:
      case anceParser::T__64:
      case anceParser::T__65:
      case anceParser::T__66:
      case anceParser::T__67:
      case anceParser::T__68:
      case anceParser::T__69:
      case anceParser::T__70:
      case anceParser::T__71:
      case anceParser::T__72:
      case anceParser::T__73:
      case anceParser::T__74:
      case anceParser::T__75:
      case anceParser::T__76:
      case anceParser::T__77:
      case anceParser::NATIVE_INTEGER_TYPE:
      case anceParser::SIGNED_INTEGER:
      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER:
      case anceParser::HALF:
      case anceParser::SINGLE:
      case anceParser::DOUBLE:
      case anceParser::QUAD:
      case anceParser::STRING:
      case anceParser::CHAR:
      case anceParser::INTEGER:
      case anceParser::BUFFER:
      case anceParser::NOT:
      case anceParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(269);
        statement();
        break;
      }

      case anceParser::T__3: {
        enterOuterAlt(_localctx, 2);
        setState(270);
        block();
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

//----------------- BlockContext ------------------------------------------------------------------

anceParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<anceParser::CodeContext *> anceParser::BlockContext::code() {
  return getRuleContexts<anceParser::CodeContext>();
}

anceParser::CodeContext* anceParser::BlockContext::code(size_t i) {
  return getRuleContext<anceParser::CodeContext>(i);
}


size_t anceParser::BlockContext::getRuleIndex() const {
  return anceParser::RuleBlock;
}


std::any anceParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

anceParser::BlockContext* anceParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 30, anceParser::RuleBlock);
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
    setState(273);
    match(anceParser::T__3);
    setState(277);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__1)
      | (1ULL << anceParser::T__3)
      | (1ULL << anceParser::T__12)
      | (1ULL << anceParser::T__13)
      | (1ULL << anceParser::T__17)
      | (1ULL << anceParser::T__18)
      | (1ULL << anceParser::T__19)
      | (1ULL << anceParser::T__20)
      | (1ULL << anceParser::T__21)
      | (1ULL << anceParser::T__22)
      | (1ULL << anceParser::T__25)
      | (1ULL << anceParser::T__27)
      | (1ULL << anceParser::T__28)
      | (1ULL << anceParser::T__34)
      | (1ULL << anceParser::T__39)
      | (1ULL << anceParser::T__41)
      | (1ULL << anceParser::T__42)
      | (1ULL << anceParser::T__43)
      | (1ULL << anceParser::T__56)
      | (1ULL << anceParser::T__59)
      | (1ULL << anceParser::T__60)
      | (1ULL << anceParser::T__62))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (anceParser::T__63 - 64))
      | (1ULL << (anceParser::T__64 - 64))
      | (1ULL << (anceParser::T__65 - 64))
      | (1ULL << (anceParser::T__66 - 64))
      | (1ULL << (anceParser::T__67 - 64))
      | (1ULL << (anceParser::T__68 - 64))
      | (1ULL << (anceParser::T__69 - 64))
      | (1ULL << (anceParser::T__70 - 64))
      | (1ULL << (anceParser::T__71 - 64))
      | (1ULL << (anceParser::T__72 - 64))
      | (1ULL << (anceParser::T__73 - 64))
      | (1ULL << (anceParser::T__74 - 64))
      | (1ULL << (anceParser::T__75 - 64))
      | (1ULL << (anceParser::T__76 - 64))
      | (1ULL << (anceParser::T__77 - 64))
      | (1ULL << (anceParser::NATIVE_INTEGER_TYPE - 64))
      | (1ULL << (anceParser::SIGNED_INTEGER - 64))
      | (1ULL << (anceParser::HEX_INTEGER - 64))
      | (1ULL << (anceParser::BIN_INTEGER - 64))
      | (1ULL << (anceParser::OCT_INTEGER - 64))
      | (1ULL << (anceParser::HALF - 64))
      | (1ULL << (anceParser::SINGLE - 64))
      | (1ULL << (anceParser::DOUBLE - 64))
      | (1ULL << (anceParser::QUAD - 64))
      | (1ULL << (anceParser::STRING - 64))
      | (1ULL << (anceParser::CHAR - 64))
      | (1ULL << (anceParser::INTEGER - 64))
      | (1ULL << (anceParser::BUFFER - 64))
      | (1ULL << (anceParser::NOT - 64))
      | (1ULL << (anceParser::IDENTIFIER - 64)))) != 0)) {
      setState(274);
      code();
      setState(279);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(280);
    match(anceParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

anceParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ExpressionStatementContext* anceParser::StatementContext::expressionStatement() {
  return getRuleContext<anceParser::ExpressionStatementContext>(0);
}

anceParser::IfStatementContext* anceParser::StatementContext::ifStatement()
{
    return getRuleContext<anceParser::IfStatementContext>(0);
}

anceParser::LocalVariableDefinitionContext* anceParser::StatementContext::localVariableDefinition() {
  return getRuleContext<anceParser::LocalVariableDefinitionContext>(0);
}

anceParser::LocalReferenceDefinitionContext* anceParser::StatementContext::localReferenceDefinition() {
  return getRuleContext<anceParser::LocalReferenceDefinitionContext>(0);
}

anceParser::EraseStatementContext* anceParser::StatementContext::eraseStatement() {
  return getRuleContext<anceParser::EraseStatementContext>(0);
}

anceParser::AssignmentContext* anceParser::StatementContext::assignment() {
  return getRuleContext<anceParser::AssignmentContext>(0);
}

anceParser::DeleteStatementContext* anceParser::StatementContext::deleteStatement() {
  return getRuleContext<anceParser::DeleteStatementContext>(0);
}

anceParser::BreakStatementContext* anceParser::StatementContext::breakStatement() {
  return getRuleContext<anceParser::BreakStatementContext>(0);
}

anceParser::ContinueStatementContext* anceParser::StatementContext::continueStatement() {
  return getRuleContext<anceParser::ContinueStatementContext>(0);
}

anceParser::ReturnStatementContext* anceParser::StatementContext::returnStatement() {
  return getRuleContext<anceParser::ReturnStatementContext>(0);
}

anceParser::AssertStatementContext* anceParser::StatementContext::assertStatement() {
  return getRuleContext<anceParser::AssertStatementContext>(0);
}

anceParser::WhileStatementContext* anceParser::StatementContext::whileStatement() {
  return getRuleContext<anceParser::WhileStatementContext>(0);
}

anceParser::LoopStatementContext* anceParser::StatementContext::loopStatement() {
  return getRuleContext<anceParser::LoopStatementContext>(0);
}

anceParser::MatchStatementContext* anceParser::StatementContext::matchStatement() {
  return getRuleContext<anceParser::MatchStatementContext>(0);
}


size_t anceParser::StatementContext::getRuleIndex() const {
  return anceParser::RuleStatement;
}


std::any anceParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::StatementContext* anceParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 32, anceParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(296);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(282);
      expressionStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(283);
      ifStatement();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(284);
      localVariableDefinition();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(285);
      localReferenceDefinition();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(286);
      eraseStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(287);
      assignment();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(288);
      deleteStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(289);
      breakStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(290);
      continueStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(291);
      returnStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(292);
      assertStatement();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(293);
      whileStatement();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(294);
      loopStatement();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(295);
      matchStatement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStatementContext ------------------------------------------------------------------

anceParser::ExpressionStatementContext::ExpressionStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::IndependentExpressionContext* anceParser::ExpressionStatementContext::independentExpression() {
  return getRuleContext<anceParser::IndependentExpressionContext>(0);
}

tree::TerminalNode* anceParser::ExpressionStatementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}


size_t anceParser::ExpressionStatementContext::getRuleIndex() const {
  return anceParser::RuleExpressionStatement;
}


std::any anceParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ExpressionStatementContext* anceParser::expressionStatement() {
  ExpressionStatementContext *_localctx = _tracker.createInstance<ExpressionStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, anceParser::RuleExpressionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(298);
    independentExpression();
    setState(299);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocalVariableDefinitionContext ------------------------------------------------------------------

anceParser::LocalVariableDefinitionContext::LocalVariableDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::LocalVariableDefinitionContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::LocalVariableDefinitionContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

anceParser::TypeContext* anceParser::LocalVariableDefinitionContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::AssignerContext* anceParser::LocalVariableDefinitionContext::assigner() {
  return getRuleContext<anceParser::AssignerContext>(0);
}

anceParser::ExpressionContext* anceParser::LocalVariableDefinitionContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::LocalVariableDefinitionContext::getRuleIndex() const {
  return anceParser::RuleLocalVariableDefinition;
}


std::any anceParser::LocalVariableDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLocalVariableDefinition(this);
  else
    return visitor->visitChildren(this);
}

anceParser::LocalVariableDefinitionContext* anceParser::localVariableDefinition() {
  LocalVariableDefinitionContext *_localctx = _tracker.createInstance<LocalVariableDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 36, anceParser::RuleLocalVariableDefinition);
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
    setState(301);
    match(anceParser::T__12);
    setState(302);
    match(anceParser::IDENTIFIER);
    setState(305);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__0) {
      setState(303);
      match(anceParser::T__0);
      setState(304);
      type();
    }
    setState(310);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(307);
      assigner();
      setState(308);
      expression(0);
    }
    setState(312);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LocalReferenceDefinitionContext ------------------------------------------------------------------

anceParser::LocalReferenceDefinitionContext::LocalReferenceDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::LocalReferenceDefinitionContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::LocalReferenceDefinitionContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::BindRefContext* anceParser::LocalReferenceDefinitionContext::bindRef() {
  return getRuleContext<anceParser::BindRefContext>(0);
}

tree::TerminalNode* anceParser::LocalReferenceDefinitionContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}


size_t anceParser::LocalReferenceDefinitionContext::getRuleIndex() const {
  return anceParser::RuleLocalReferenceDefinition;
}


std::any anceParser::LocalReferenceDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLocalReferenceDefinition(this);
  else
    return visitor->visitChildren(this);
}

anceParser::LocalReferenceDefinitionContext* anceParser::localReferenceDefinition() {
  LocalReferenceDefinitionContext *_localctx = _tracker.createInstance<LocalReferenceDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 38, anceParser::RuleLocalReferenceDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(314);
    match(anceParser::T__12);
    setState(315);
    match(anceParser::IDENTIFIER);
    setState(316);
    match(anceParser::T__0);
    setState(317);
    type();
    setState(318);
    bindRef();
    setState(319);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EraseStatementContext ------------------------------------------------------------------

anceParser::EraseStatementContext::EraseStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::EraseStatementContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::EraseStatementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}


size_t anceParser::EraseStatementContext::getRuleIndex() const {
  return anceParser::RuleEraseStatement;
}


std::any anceParser::EraseStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitEraseStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::EraseStatementContext* anceParser::eraseStatement() {
  EraseStatementContext *_localctx = _tracker.createInstance<EraseStatementContext>(_ctx, getState());
  enterRule(_localctx, 40, anceParser::RuleEraseStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(321);
    match(anceParser::T__13);
    setState(322);
    match(anceParser::IDENTIFIER);
    setState(323);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

anceParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AssignerContext* anceParser::AssignmentContext::assigner() {
  return getRuleContext<anceParser::AssignerContext>(0);
}

tree::TerminalNode* anceParser::AssignmentContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

std::vector<anceParser::ExpressionContext *> anceParser::AssignmentContext::expression() {
  return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::AssignmentContext::expression(size_t i) {
  return getRuleContext<anceParser::ExpressionContext>(i);
}


size_t anceParser::AssignmentContext::getRuleIndex() const {
  return anceParser::RuleAssignment;
}


std::any anceParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

anceParser::AssignmentContext* anceParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 42, anceParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(325);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->assignable = expression(0);
    setState(326);
    assigner();
    setState(327);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->assigned = expression(0);
    setState(328);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignerContext ------------------------------------------------------------------

anceParser::AssignerContext::AssignerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::AssignerContext::getRuleIndex() const {
  return anceParser::RuleAssigner;
}

void anceParser::AssignerContext::copyFrom(AssignerContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MoveAssignmentContext ------------------------------------------------------------------

anceParser::MoveAssignmentContext::MoveAssignmentContext(AssignerContext *ctx) { copyFrom(ctx); }


std::any anceParser::MoveAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitMoveAssignment(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FinalCopyAssignmentContext ------------------------------------------------------------------

anceParser::FinalCopyAssignmentContext::FinalCopyAssignmentContext(AssignerContext *ctx) { copyFrom(ctx); }


std::any anceParser::FinalCopyAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFinalCopyAssignment(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CopyAssignmentContext ------------------------------------------------------------------

anceParser::CopyAssignmentContext::CopyAssignmentContext(AssignerContext *ctx) { copyFrom(ctx); }


std::any anceParser::CopyAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitCopyAssignment(this);
  else
    return visitor->visitChildren(this);
}
anceParser::AssignerContext* anceParser::assigner() {
  AssignerContext *_localctx = _tracker.createInstance<AssignerContext>(_ctx, getState());
  enterRule(_localctx, 44, anceParser::RuleAssigner);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(333);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__14: {
        _localctx = _tracker.createInstance<anceParser::CopyAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(330);
        match(anceParser::T__14);
        break;
      }

      case anceParser::T__15: {
        _localctx = _tracker.createInstance<anceParser::MoveAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(331);
        match(anceParser::T__15);
        break;
      }

      case anceParser::T__16: {
        _localctx = _tracker.createInstance<anceParser::FinalCopyAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(332);
        match(anceParser::T__16);
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

//----------------- DeleteStatementContext ------------------------------------------------------------------

anceParser::DeleteStatementContext::DeleteStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ExpressionContext* anceParser::DeleteStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

tree::TerminalNode* anceParser::DeleteStatementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

tree::TerminalNode* anceParser::DeleteStatementContext::BUFFER() {
  return getToken(anceParser::BUFFER, 0);
}


size_t anceParser::DeleteStatementContext::getRuleIndex() const {
  return anceParser::RuleDeleteStatement;
}


std::any anceParser::DeleteStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitDeleteStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::DeleteStatementContext* anceParser::deleteStatement() {
  DeleteStatementContext *_localctx = _tracker.createInstance<DeleteStatementContext>(_ctx, getState());
  enterRule(_localctx, 46, anceParser::RuleDeleteStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(335);
    match(anceParser::T__17);
    setState(337);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      setState(336);
      match(anceParser::BUFFER);
      break;
    }

    default:
      break;
    }
    setState(339);
    expression(0);
    setState(340);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStatementContext ------------------------------------------------------------------

anceParser::BreakStatementContext::BreakStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::BreakStatementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}


size_t anceParser::BreakStatementContext::getRuleIndex() const {
  return anceParser::RuleBreakStatement;
}


std::any anceParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::BreakStatementContext* anceParser::breakStatement() {
  BreakStatementContext *_localctx = _tracker.createInstance<BreakStatementContext>(_ctx, getState());
  enterRule(_localctx, 48, anceParser::RuleBreakStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(342);
    match(anceParser::T__18);
    setState(343);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueStatementContext ------------------------------------------------------------------

anceParser::ContinueStatementContext::ContinueStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::ContinueStatementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}


size_t anceParser::ContinueStatementContext::getRuleIndex() const {
  return anceParser::RuleContinueStatement;
}


std::any anceParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ContinueStatementContext* anceParser::continueStatement() {
  ContinueStatementContext *_localctx = _tracker.createInstance<ContinueStatementContext>(_ctx, getState());
  enterRule(_localctx, 50, anceParser::RuleContinueStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(345);
    match(anceParser::T__19);
    setState(346);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

anceParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::ReturnStatementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

anceParser::ExpressionContext* anceParser::ReturnStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::ReturnStatementContext::getRuleIndex() const {
  return anceParser::RuleReturnStatement;
}


std::any anceParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ReturnStatementContext* anceParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 52, anceParser::RuleReturnStatement);
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
    setState(348);
    match(anceParser::T__20);
    setState(350);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__1)
      | (1ULL << anceParser::T__22)
      | (1ULL << anceParser::T__28)
      | (1ULL << anceParser::T__34)
      | (1ULL << anceParser::T__39)
      | (1ULL << anceParser::T__41)
      | (1ULL << anceParser::T__42)
      | (1ULL << anceParser::T__43)
      | (1ULL << anceParser::T__56)
      | (1ULL << anceParser::T__59)
      | (1ULL << anceParser::T__60)
      | (1ULL << anceParser::T__62))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (anceParser::T__63 - 64))
      | (1ULL << (anceParser::T__64 - 64))
      | (1ULL << (anceParser::T__65 - 64))
      | (1ULL << (anceParser::T__66 - 64))
      | (1ULL << (anceParser::T__67 - 64))
      | (1ULL << (anceParser::T__68 - 64))
      | (1ULL << (anceParser::T__69 - 64))
      | (1ULL << (anceParser::T__70 - 64))
      | (1ULL << (anceParser::T__71 - 64))
      | (1ULL << (anceParser::T__72 - 64))
      | (1ULL << (anceParser::T__73 - 64))
      | (1ULL << (anceParser::T__74 - 64))
      | (1ULL << (anceParser::T__75 - 64))
      | (1ULL << (anceParser::T__76 - 64))
      | (1ULL << (anceParser::T__77 - 64))
      | (1ULL << (anceParser::NATIVE_INTEGER_TYPE - 64))
      | (1ULL << (anceParser::SIGNED_INTEGER - 64))
      | (1ULL << (anceParser::HEX_INTEGER - 64))
      | (1ULL << (anceParser::BIN_INTEGER - 64))
      | (1ULL << (anceParser::OCT_INTEGER - 64))
      | (1ULL << (anceParser::HALF - 64))
      | (1ULL << (anceParser::SINGLE - 64))
      | (1ULL << (anceParser::DOUBLE - 64))
      | (1ULL << (anceParser::QUAD - 64))
      | (1ULL << (anceParser::STRING - 64))
      | (1ULL << (anceParser::CHAR - 64))
      | (1ULL << (anceParser::INTEGER - 64))
      | (1ULL << (anceParser::BUFFER - 64))
      | (1ULL << (anceParser::NOT - 64))
      | (1ULL << (anceParser::IDENTIFIER - 64)))) != 0)) {
      setState(349);
      expression(0);
    }
    setState(352);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssertStatementContext ------------------------------------------------------------------

anceParser::AssertStatementContext::AssertStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ExpressionContext* anceParser::AssertStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

tree::TerminalNode* anceParser::AssertStatementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}


size_t anceParser::AssertStatementContext::getRuleIndex() const {
  return anceParser::RuleAssertStatement;
}


std::any anceParser::AssertStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAssertStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::AssertStatementContext* anceParser::assertStatement() {
  AssertStatementContext *_localctx = _tracker.createInstance<AssertStatementContext>(_ctx, getState());
  enterRule(_localctx, 54, anceParser::RuleAssertStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(354);
    match(anceParser::T__21);
    setState(355);
    expression(0);
    setState(356);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

anceParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ExpressionContext* anceParser::IfStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

std::vector<anceParser::CodeContext *> anceParser::IfStatementContext::code() {
  return getRuleContexts<anceParser::CodeContext>();
}

anceParser::CodeContext* anceParser::IfStatementContext::code(size_t i) {
  return getRuleContext<anceParser::CodeContext>(i);
}


size_t anceParser::IfStatementContext::getRuleIndex() const {
  return anceParser::RuleIfStatement;
}


std::any anceParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::IfStatementContext* anceParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 56, anceParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(358);
    match(anceParser::T__22);
    setState(359);
    expression(0);
    setState(360);
    match(anceParser::T__23);
    setState(361);
    antlrcpp::downCast<IfStatementContext *>(_localctx)->ifBlock = code();
    setState(364);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(362);
      match(anceParser::T__24);
      setState(363);
      antlrcpp::downCast<IfStatementContext *>(_localctx)->elseBlock = code();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStatementContext ------------------------------------------------------------------

anceParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ExpressionContext* anceParser::WhileStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::CodeContext* anceParser::WhileStatementContext::code() {
  return getRuleContext<anceParser::CodeContext>(0);
}


size_t anceParser::WhileStatementContext::getRuleIndex() const {
  return anceParser::RuleWhileStatement;
}


std::any anceParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::WhileStatementContext* anceParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 58, anceParser::RuleWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(366);
    match(anceParser::T__25);
    setState(367);
    expression(0);
    setState(368);
    match(anceParser::T__26);
    setState(369);
    code();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LoopStatementContext ------------------------------------------------------------------

anceParser::LoopStatementContext::LoopStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::CodeContext* anceParser::LoopStatementContext::code() {
  return getRuleContext<anceParser::CodeContext>(0);
}


size_t anceParser::LoopStatementContext::getRuleIndex() const {
  return anceParser::RuleLoopStatement;
}


std::any anceParser::LoopStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLoopStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::LoopStatementContext* anceParser::loopStatement() {
  LoopStatementContext *_localctx = _tracker.createInstance<LoopStatementContext>(_ctx, getState());
  enterRule(_localctx, 60, anceParser::RuleLoopStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(371);
    match(anceParser::T__27);
    setState(372);
    code();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MatchStatementContext ------------------------------------------------------------------

anceParser::MatchStatementContext::MatchStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ExpressionContext* anceParser::MatchStatementContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

std::vector<anceParser::MatchCaseContext *> anceParser::MatchStatementContext::matchCase() {
  return getRuleContexts<anceParser::MatchCaseContext>();
}

anceParser::MatchCaseContext* anceParser::MatchStatementContext::matchCase(size_t i) {
  return getRuleContext<anceParser::MatchCaseContext>(i);
}


size_t anceParser::MatchStatementContext::getRuleIndex() const {
  return anceParser::RuleMatchStatement;
}


std::any anceParser::MatchStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitMatchStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::MatchStatementContext* anceParser::matchStatement() {
  MatchStatementContext *_localctx = _tracker.createInstance<MatchStatementContext>(_ctx, getState());
  enterRule(_localctx, 62, anceParser::RuleMatchStatement);
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
    setState(374);
    match(anceParser::T__28);
    setState(375);
    expression(0);
    setState(376);
    match(anceParser::T__29);
    setState(377);
    match(anceParser::T__3);
    setState(381);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == anceParser::T__1

    || _la == anceParser::T__32 || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (anceParser::T__63 - 64))
      | (1ULL << (anceParser::T__64 - 64))
      | (1ULL << (anceParser::T__65 - 64))
      | (1ULL << (anceParser::SIGNED_INTEGER - 64))
      | (1ULL << (anceParser::HEX_INTEGER - 64))
      | (1ULL << (anceParser::BIN_INTEGER - 64))
      | (1ULL << (anceParser::OCT_INTEGER - 64))
      | (1ULL << (anceParser::HALF - 64))
      | (1ULL << (anceParser::SINGLE - 64))
      | (1ULL << (anceParser::DOUBLE - 64))
      | (1ULL << (anceParser::QUAD - 64))
      | (1ULL << (anceParser::STRING - 64))
      | (1ULL << (anceParser::CHAR - 64))
      | (1ULL << (anceParser::INTEGER - 64))
      | (1ULL << (anceParser::IDENTIFIER - 64)))) != 0)) {
      setState(378);
      matchCase();
      setState(383);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(384);
    match(anceParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MatchCaseContext ------------------------------------------------------------------

anceParser::MatchCaseContext::MatchCaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::MatchCaseContext::getRuleIndex() const {
  return anceParser::RuleMatchCase;
}

void anceParser::MatchCaseContext::copyFrom(MatchCaseContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LiteralCaseContext ------------------------------------------------------------------

std::vector<anceParser::LiteralExpressionContext *> anceParser::LiteralCaseContext::literalExpression() {
  return getRuleContexts<anceParser::LiteralExpressionContext>();
}

anceParser::LiteralExpressionContext* anceParser::LiteralCaseContext::literalExpression(size_t i) {
  return getRuleContext<anceParser::LiteralExpressionContext>(i);
}

anceParser::CodeContext* anceParser::LiteralCaseContext::code() {
  return getRuleContext<anceParser::CodeContext>(0);
}

anceParser::LiteralCaseContext::LiteralCaseContext(MatchCaseContext *ctx) { copyFrom(ctx); }


std::any anceParser::LiteralCaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLiteralCase(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DefaultCaseContext ------------------------------------------------------------------

anceParser::CodeContext* anceParser::DefaultCaseContext::code() {
  return getRuleContext<anceParser::CodeContext>(0);
}

anceParser::DefaultCaseContext::DefaultCaseContext(MatchCaseContext *ctx) { copyFrom(ctx); }


std::any anceParser::DefaultCaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitDefaultCase(this);
  else
    return visitor->visitChildren(this);
}
anceParser::MatchCaseContext* anceParser::matchCase() {
  MatchCaseContext *_localctx = _tracker.createInstance<MatchCaseContext>(_ctx, getState());
  enterRule(_localctx, 64, anceParser::RuleMatchCase);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(400);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__1:
      case anceParser::T__63:
      case anceParser::T__64:
      case anceParser::T__65:
      case anceParser::SIGNED_INTEGER:
      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER:
      case anceParser::HALF:
      case anceParser::SINGLE:
      case anceParser::DOUBLE:
      case anceParser::QUAD:
      case anceParser::STRING:
      case anceParser::CHAR:
      case anceParser::INTEGER:
      case anceParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<anceParser::LiteralCaseContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(386);
        literalExpression();
        setState(391);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__30) {
          setState(387);
          match(anceParser::T__30);
          setState(388);
          literalExpression();
          setState(393);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(394);
        match(anceParser::T__31);
        setState(395);
        code();
        break;
      }

      case anceParser::T__32: {
        _localctx = _tracker.createInstance<anceParser::DefaultCaseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(397);
        match(anceParser::T__32);
        setState(398);
        match(anceParser::T__31);
        setState(399);
        code();
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

//----------------- ExpressionContext ------------------------------------------------------------------

anceParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::ExpressionContext::getRuleIndex() const {
  return anceParser::RuleExpression;
}

void anceParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CastContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::CastContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::TypeContext* anceParser::CastContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::CastContext::CastContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::CastContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitCast(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfExpressionContext ------------------------------------------------------------------

std::vector<anceParser::ExpressionContext *> anceParser::IfExpressionContext::expression() {
  return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::IfExpressionContext::expression(size_t i) {
  return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::IfExpressionContext::IfExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::IfExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitIfExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VariableContext ------------------------------------------------------------------

anceParser::VariableAccessContext* anceParser::VariableContext::variableAccess() {
  return getRuleContext<anceParser::VariableAccessContext>(0);
}

anceParser::VariableContext::VariableContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::VariableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVariable(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryOperationContext ------------------------------------------------------------------

anceParser::UnaryOperatorContext* anceParser::UnaryOperationContext::unaryOperator() {
  return getRuleContext<anceParser::UnaryOperatorContext>(0);
}

anceParser::ExpressionContext* anceParser::UnaryOperationContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::UnaryOperationContext::UnaryOperationContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::UnaryOperationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitUnaryOperation(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryOperationContext ------------------------------------------------------------------

anceParser::BinaryOperatorMultiplicativeContext* anceParser::BinaryOperationContext::binaryOperatorMultiplicative() {
  return getRuleContext<anceParser::BinaryOperatorMultiplicativeContext>(0);
}

std::vector<anceParser::ExpressionContext *> anceParser::BinaryOperationContext::expression() {
  return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::BinaryOperationContext::expression(size_t i) {
  return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::BinaryOperatorAdditiveContext* anceParser::BinaryOperationContext::binaryOperatorAdditive() {
  return getRuleContext<anceParser::BinaryOperatorAdditiveContext>(0);
}

anceParser::BinaryOperatorBitwiseContext* anceParser::BinaryOperationContext::binaryOperatorBitwise() {
  return getRuleContext<anceParser::BinaryOperatorBitwiseContext>(0);
}

anceParser::BinaryOperatorShiftContext* anceParser::BinaryOperationContext::binaryOperatorShift() {
  return getRuleContext<anceParser::BinaryOperatorShiftContext>(0);
}

anceParser::BinaryOperatorRelationalContext* anceParser::BinaryOperationContext::binaryOperatorRelational() {
  return getRuleContext<anceParser::BinaryOperatorRelationalContext>(0);
}

anceParser::BinaryOperatorEqualityContext* anceParser::BinaryOperationContext::binaryOperatorEquality() {
  return getRuleContext<anceParser::BinaryOperatorEqualityContext>(0);
}

anceParser::BinaryOperationContext::BinaryOperationContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::BinaryOperationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBinaryOperation(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SubscriptContext ------------------------------------------------------------------

std::vector<anceParser::ExpressionContext *> anceParser::SubscriptContext::expression() {
  return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::SubscriptContext::expression(size_t i) {
  return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::SubscriptContext::SubscriptContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::SubscriptContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSubscript(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalOrContext ------------------------------------------------------------------

std::vector<anceParser::ExpressionContext *> anceParser::LogicalOrContext::expression() {
  return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::LogicalOrContext::expression(size_t i) {
  return getRuleContext<anceParser::ExpressionContext>(i);
}

tree::TerminalNode* anceParser::LogicalOrContext::NOT() {
  return getToken(anceParser::NOT, 0);
}

anceParser::LogicalOrContext::LogicalOrContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::LogicalOrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLogicalOr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MatchContext ------------------------------------------------------------------

anceParser::MatchExpressionContext* anceParser::MatchContext::matchExpression() {
  return getRuleContext<anceParser::MatchExpressionContext>(0);
}

anceParser::MatchContext::MatchContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::MatchContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitMatch(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RefContext ------------------------------------------------------------------

anceParser::BindRefContext* anceParser::RefContext::bindRef() {
  return getRuleContext<anceParser::BindRefContext>(0);
}

anceParser::RefContext::RefContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::RefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitRef(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IndependentContext ------------------------------------------------------------------

anceParser::IndependentExpressionContext* anceParser::IndependentContext::independentExpression() {
  return getRuleContext<anceParser::IndependentExpressionContext>(0);
}

anceParser::IndependentContext::IndependentContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::IndependentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitIndependent(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenthesisContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::ParenthesisContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::ParenthesisContext::ParenthesisContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::ParenthesisContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitParenthesis(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AllocContext ------------------------------------------------------------------

anceParser::AllocationContext* anceParser::AllocContext::allocation() {
  return getRuleContext<anceParser::AllocationContext>(0);
}

anceParser::AllocContext::AllocContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::AllocContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAlloc(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MemberAccessContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::MemberAccessContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ExpressionContext* anceParser::MemberAccessContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::MemberAccessContext::MemberAccessContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::MemberAccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitMemberAccess(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LiteralContext ------------------------------------------------------------------

anceParser::LiteralExpressionContext* anceParser::LiteralContext::literalExpression() {
  return getRuleContext<anceParser::LiteralExpressionContext>(0);
}

anceParser::LiteralContext::LiteralContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalAndContext ------------------------------------------------------------------

std::vector<anceParser::ExpressionContext *> anceParser::LogicalAndContext::expression() {
  return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::LogicalAndContext::expression(size_t i) {
  return getRuleContext<anceParser::ExpressionContext>(i);
}

tree::TerminalNode* anceParser::LogicalAndContext::NOT() {
  return getToken(anceParser::NOT, 0);
}

anceParser::LogicalAndContext::LogicalAndContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::LogicalAndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLogicalAnd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VectorDefinitionContext ------------------------------------------------------------------

std::vector<anceParser::ExpressionContext *> anceParser::VectorDefinitionContext::expression() {
  return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::VectorDefinitionContext::expression(size_t i) {
  return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::TypeContext* anceParser::VectorDefinitionContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::VectorDefinitionContext::VectorDefinitionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::VectorDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVectorDefinition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddressOfContext ------------------------------------------------------------------

anceParser::AddressofContext* anceParser::AddressOfContext::addressof() {
  return getRuleContext<anceParser::AddressofContext>(0);
}

anceParser::AddressOfContext::AddressOfContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::AddressOfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAddressOf(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayDefinitionContext ------------------------------------------------------------------

std::vector<anceParser::ExpressionContext *> anceParser::ArrayDefinitionContext::expression() {
  return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::ArrayDefinitionContext::expression(size_t i) {
  return getRuleContext<anceParser::ExpressionContext>(i);
}

anceParser::TypeContext* anceParser::ArrayDefinitionContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::ArrayDefinitionContext::ArrayDefinitionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::ArrayDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitArrayDefinition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SizeOfContext ------------------------------------------------------------------

anceParser::SizeofTypeContext* anceParser::SizeOfContext::sizeofType() {
  return getRuleContext<anceParser::SizeofTypeContext>(0);
}

anceParser::SizeofExpressionContext* anceParser::SizeOfContext::sizeofExpression() {
  return getRuleContext<anceParser::SizeofExpressionContext>(0);
}

anceParser::SizeOfContext::SizeOfContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::SizeOfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSizeOf(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IndirectionContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::IndirectionContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::IndirectionContext::IndirectionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any anceParser::IndirectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitIndirection(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ExpressionContext* anceParser::expression() {
   return expression(0);
}

anceParser::ExpressionContext* anceParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  anceParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  anceParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 66;
  enterRecursionRule(_localctx, 66, anceParser::RuleExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(459);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<VariableContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(403);
      variableAccess();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<AllocContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(404);
      allocation();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<LiteralContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(405);
      literalExpression();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<AddressOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(406);
      addressof();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<RefContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(407);
      bindRef();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SizeOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(408);
      sizeofType();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SizeOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(409);
      sizeofExpression();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<IndependentContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(410);
      independentExpression();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ParenthesisContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(411);
      match(anceParser::T__1);
      setState(412);
      expression(0);
      setState(413);
      match(anceParser::T__2);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<UnaryOperationContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(415);
      unaryOperator();
      setState(416);
      expression(13);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<IfExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(418);
      match(anceParser::T__22);
      setState(419);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->condition = expression(0);
      setState(420);
      match(anceParser::T__23);
      setState(421);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->thenBlock = expression(0);
      setState(424);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
      case 1: {
        setState(422);
        match(anceParser::T__24);
        setState(423);
        antlrcpp::downCast<IfExpressionContext *>(_localctx)->elseBlock = expression(0);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<MatchContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(426);
      matchExpression();
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<VectorDefinitionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(427);
      match(anceParser::T__39);
      setState(431);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
      case 1: {
        setState(428);
        type();
        setState(429);
        match(anceParser::T__30);
        break;
      }

      default:
        break;
      }
      setState(433);
      expression(0);
      setState(438);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(434);
        match(anceParser::T__5);
        setState(435);
        expression(0);
        setState(440);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(441);
      match(anceParser::T__40);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<ArrayDefinitionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(443);
      match(anceParser::T__34);
      setState(447);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
      case 1: {
        setState(444);
        type();
        setState(445);
        match(anceParser::T__30);
        break;
      }

      default:
        break;
      }
      setState(449);
      expression(0);
      setState(454);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(450);
        match(anceParser::T__5);
        setState(451);
        expression(0);
        setState(456);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(457);
      match(anceParser::T__35);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(511);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(509);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(461);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(462);
          binaryOperatorMultiplicative();
          setState(463);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(13);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(465);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(466);
          binaryOperatorAdditive();
          setState(467);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(12);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(469);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(470);
          binaryOperatorBitwise();
          setState(471);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(11);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(473);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(474);
          binaryOperatorShift();
          setState(475);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(10);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(477);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(478);
          binaryOperatorRelational();
          setState(479);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(9);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(481);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(482);
          binaryOperatorEquality();
          setState(483);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(8);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<LogicalAndContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(485);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(487);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == anceParser::NOT) {
            setState(486);
            match(anceParser::NOT);
          }
          setState(489);
          match(anceParser::T__37);
          setState(490);
          antlrcpp::downCast<LogicalAndContext *>(_localctx)->right = expression(7);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<LogicalOrContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(491);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(493);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == anceParser::NOT) {
            setState(492);
            match(anceParser::NOT);
          }
          setState(495);
          match(anceParser::T__38);
          setState(496);
          antlrcpp::downCast<LogicalOrContext *>(_localctx)->right = expression(6);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<IndirectionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(497);

          if (!(precpred(_ctx, 23))) throw FailedPredicateException(this, "precpred(_ctx, 23)");
          setState(498);
          match(anceParser::T__33);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<SubscriptContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->indexed = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(499);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(500);
          match(anceParser::T__34);
          setState(501);
          antlrcpp::downCast<SubscriptContext *>(_localctx)->index = expression(0);
          setState(502);
          match(anceParser::T__35);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->accessed = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(504);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(505);
          match(anceParser::IDENTIFIER);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<CastContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(506);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(507);
          match(anceParser::T__36);
          setState(508);
          type();
          break;
        }

        default:
          break;
        } 
      }
      setState(513);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- UnaryOperatorContext ------------------------------------------------------------------

anceParser::UnaryOperatorContext::UnaryOperatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::UnaryOperatorContext::getRuleIndex() const {
  return anceParser::RuleUnaryOperator;
}

void anceParser::UnaryOperatorContext::copyFrom(UnaryOperatorContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NotContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::NotContext::NOT() {
  return getToken(anceParser::NOT, 0);
}

anceParser::NotContext::NotContext(UnaryOperatorContext *ctx) { copyFrom(ctx); }


std::any anceParser::NotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NegationContext ------------------------------------------------------------------

anceParser::NegationContext::NegationContext(UnaryOperatorContext *ctx) { copyFrom(ctx); }


std::any anceParser::NegationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitNegation(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitwiseNotContext ------------------------------------------------------------------

anceParser::BitwiseNotContext::BitwiseNotContext(UnaryOperatorContext *ctx) { copyFrom(ctx); }


std::any anceParser::BitwiseNotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBitwiseNot(this);
  else
    return visitor->visitChildren(this);
}
anceParser::UnaryOperatorContext* anceParser::unaryOperator() {
  UnaryOperatorContext *_localctx = _tracker.createInstance<UnaryOperatorContext>(_ctx, getState());
  enterRule(_localctx, 68, anceParser::RuleUnaryOperator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(517);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::NOT: {
        _localctx = _tracker.createInstance<anceParser::NotContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(514);
        match(anceParser::NOT);
        break;
      }

      case anceParser::T__41: {
        _localctx = _tracker.createInstance<anceParser::BitwiseNotContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(515);
        match(anceParser::T__41);
        break;
      }

      case anceParser::T__42: {
        _localctx = _tracker.createInstance<anceParser::NegationContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(516);
        match(anceParser::T__42);
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

//----------------- BinaryOperatorMultiplicativeContext ------------------------------------------------------------------

anceParser::BinaryOperatorMultiplicativeContext::BinaryOperatorMultiplicativeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::BinaryOperatorMultiplicativeContext::getRuleIndex() const {
  return anceParser::RuleBinaryOperatorMultiplicative;
}

void anceParser::BinaryOperatorMultiplicativeContext::copyFrom(BinaryOperatorMultiplicativeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MultiplicationContext ------------------------------------------------------------------

anceParser::MultiplicationContext::MultiplicationContext(BinaryOperatorMultiplicativeContext *ctx) { copyFrom(ctx); }


std::any anceParser::MultiplicationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitMultiplication(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DivisionContext ------------------------------------------------------------------

anceParser::DivisionContext::DivisionContext(BinaryOperatorMultiplicativeContext *ctx) { copyFrom(ctx); }


std::any anceParser::DivisionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitDivision(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RemainderContext ------------------------------------------------------------------

anceParser::RemainderContext::RemainderContext(BinaryOperatorMultiplicativeContext *ctx) { copyFrom(ctx); }


std::any anceParser::RemainderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitRemainder(this);
  else
    return visitor->visitChildren(this);
}
anceParser::BinaryOperatorMultiplicativeContext* anceParser::binaryOperatorMultiplicative() {
  BinaryOperatorMultiplicativeContext *_localctx = _tracker.createInstance<BinaryOperatorMultiplicativeContext>(_ctx, getState());
  enterRule(_localctx, 70, anceParser::RuleBinaryOperatorMultiplicative);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(522);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__43: {
        _localctx = _tracker.createInstance<anceParser::MultiplicationContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(519);
        match(anceParser::T__43);
        break;
      }

      case anceParser::T__44: {
        _localctx = _tracker.createInstance<anceParser::DivisionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(520);
        match(anceParser::T__44);
        break;
      }

      case anceParser::T__45: {
        _localctx = _tracker.createInstance<anceParser::RemainderContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(521);
        match(anceParser::T__45);
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

//----------------- BinaryOperatorAdditiveContext ------------------------------------------------------------------

anceParser::BinaryOperatorAdditiveContext::BinaryOperatorAdditiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::BinaryOperatorAdditiveContext::getRuleIndex() const {
  return anceParser::RuleBinaryOperatorAdditive;
}

void anceParser::BinaryOperatorAdditiveContext::copyFrom(BinaryOperatorAdditiveContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AdditionContext ------------------------------------------------------------------

anceParser::AdditionContext::AdditionContext(BinaryOperatorAdditiveContext *ctx) { copyFrom(ctx); }


std::any anceParser::AdditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAddition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SubtractionContext ------------------------------------------------------------------

anceParser::SubtractionContext::SubtractionContext(BinaryOperatorAdditiveContext *ctx) { copyFrom(ctx); }


std::any anceParser::SubtractionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSubtraction(this);
  else
    return visitor->visitChildren(this);
}
anceParser::BinaryOperatorAdditiveContext* anceParser::binaryOperatorAdditive() {
  BinaryOperatorAdditiveContext *_localctx = _tracker.createInstance<BinaryOperatorAdditiveContext>(_ctx, getState());
  enterRule(_localctx, 72, anceParser::RuleBinaryOperatorAdditive);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(526);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__46: {
        _localctx = _tracker.createInstance<anceParser::AdditionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(524);
        match(anceParser::T__46);
        break;
      }

      case anceParser::T__42: {
        _localctx = _tracker.createInstance<anceParser::SubtractionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(525);
        match(anceParser::T__42);
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

//----------------- BinaryOperatorBitwiseContext ------------------------------------------------------------------

anceParser::BinaryOperatorBitwiseContext::BinaryOperatorBitwiseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::BinaryOperatorBitwiseContext::getRuleIndex() const {
  return anceParser::RuleBinaryOperatorBitwise;
}

void anceParser::BinaryOperatorBitwiseContext::copyFrom(BinaryOperatorBitwiseContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BitwiseOrContext ------------------------------------------------------------------

anceParser::BitwiseOrContext::BitwiseOrContext(BinaryOperatorBitwiseContext *ctx) { copyFrom(ctx); }


std::any anceParser::BitwiseOrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBitwiseOr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitwiseXorContext ------------------------------------------------------------------

anceParser::BitwiseXorContext::BitwiseXorContext(BinaryOperatorBitwiseContext *ctx) { copyFrom(ctx); }


std::any anceParser::BitwiseXorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBitwiseXor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitwiseAndContext ------------------------------------------------------------------

anceParser::BitwiseAndContext::BitwiseAndContext(BinaryOperatorBitwiseContext *ctx) { copyFrom(ctx); }


std::any anceParser::BitwiseAndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBitwiseAnd(this);
  else
    return visitor->visitChildren(this);
}
anceParser::BinaryOperatorBitwiseContext* anceParser::binaryOperatorBitwise() {
  BinaryOperatorBitwiseContext *_localctx = _tracker.createInstance<BinaryOperatorBitwiseContext>(_ctx, getState());
  enterRule(_localctx, 74, anceParser::RuleBinaryOperatorBitwise);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(531);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__47: {
        _localctx = _tracker.createInstance<anceParser::BitwiseAndContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(528);
        match(anceParser::T__47);
        break;
      }

      case anceParser::T__48: {
        _localctx = _tracker.createInstance<anceParser::BitwiseOrContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(529);
        match(anceParser::T__48);
        break;
      }

      case anceParser::T__49: {
        _localctx = _tracker.createInstance<anceParser::BitwiseXorContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(530);
        match(anceParser::T__49);
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

//----------------- BinaryOperatorShiftContext ------------------------------------------------------------------

anceParser::BinaryOperatorShiftContext::BinaryOperatorShiftContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::BinaryOperatorShiftContext::getRuleIndex() const {
  return anceParser::RuleBinaryOperatorShift;
}

void anceParser::BinaryOperatorShiftContext::copyFrom(BinaryOperatorShiftContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- RightShiftContext ------------------------------------------------------------------

anceParser::RightShiftContext::RightShiftContext(BinaryOperatorShiftContext *ctx) { copyFrom(ctx); }


std::any anceParser::RightShiftContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitRightShift(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LeftShiftContext ------------------------------------------------------------------

anceParser::LeftShiftContext::LeftShiftContext(BinaryOperatorShiftContext *ctx) { copyFrom(ctx); }


std::any anceParser::LeftShiftContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLeftShift(this);
  else
    return visitor->visitChildren(this);
}
anceParser::BinaryOperatorShiftContext* anceParser::binaryOperatorShift() {
  BinaryOperatorShiftContext *_localctx = _tracker.createInstance<BinaryOperatorShiftContext>(_ctx, getState());
  enterRule(_localctx, 76, anceParser::RuleBinaryOperatorShift);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(535);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__50: {
        _localctx = _tracker.createInstance<anceParser::LeftShiftContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(533);
        match(anceParser::T__50);
        break;
      }

      case anceParser::T__51: {
        _localctx = _tracker.createInstance<anceParser::RightShiftContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(534);
        match(anceParser::T__51);
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

//----------------- BinaryOperatorRelationalContext ------------------------------------------------------------------

anceParser::BinaryOperatorRelationalContext::BinaryOperatorRelationalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::BinaryOperatorRelationalContext::getRuleIndex() const {
  return anceParser::RuleBinaryOperatorRelational;
}

void anceParser::BinaryOperatorRelationalContext::copyFrom(BinaryOperatorRelationalContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LessThanContext ------------------------------------------------------------------

anceParser::LessThanContext::LessThanContext(BinaryOperatorRelationalContext *ctx) { copyFrom(ctx); }


std::any anceParser::LessThanContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLessThan(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LessThanOrEqualContext ------------------------------------------------------------------

anceParser::LessThanOrEqualContext::LessThanOrEqualContext(BinaryOperatorRelationalContext *ctx) { copyFrom(ctx); }


std::any anceParser::LessThanOrEqualContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLessThanOrEqual(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GreaterThanContext ------------------------------------------------------------------

anceParser::GreaterThanContext::GreaterThanContext(BinaryOperatorRelationalContext *ctx) { copyFrom(ctx); }


std::any anceParser::GreaterThanContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitGreaterThan(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GreaterThanOrEqualContext ------------------------------------------------------------------

anceParser::GreaterThanOrEqualContext::GreaterThanOrEqualContext(BinaryOperatorRelationalContext *ctx) { copyFrom(ctx); }


std::any anceParser::GreaterThanOrEqualContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitGreaterThanOrEqual(this);
  else
    return visitor->visitChildren(this);
}
anceParser::BinaryOperatorRelationalContext* anceParser::binaryOperatorRelational() {
  BinaryOperatorRelationalContext *_localctx = _tracker.createInstance<BinaryOperatorRelationalContext>(_ctx, getState());
  enterRule(_localctx, 78, anceParser::RuleBinaryOperatorRelational);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(541);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__39: {
        _localctx = _tracker.createInstance<anceParser::LessThanContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(537);
        match(anceParser::T__39);
        break;
      }

      case anceParser::T__52: {
        _localctx = _tracker.createInstance<anceParser::LessThanOrEqualContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(538);
        match(anceParser::T__52);
        break;
      }

      case anceParser::T__40: {
        _localctx = _tracker.createInstance<anceParser::GreaterThanContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(539);
        match(anceParser::T__40);
        break;
      }

      case anceParser::T__53: {
        _localctx = _tracker.createInstance<anceParser::GreaterThanOrEqualContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(540);
        match(anceParser::T__53);
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

//----------------- BinaryOperatorEqualityContext ------------------------------------------------------------------

anceParser::BinaryOperatorEqualityContext::BinaryOperatorEqualityContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::BinaryOperatorEqualityContext::getRuleIndex() const {
  return anceParser::RuleBinaryOperatorEquality;
}

void anceParser::BinaryOperatorEqualityContext::copyFrom(BinaryOperatorEqualityContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NotEqualContext ------------------------------------------------------------------

anceParser::NotEqualContext::NotEqualContext(BinaryOperatorEqualityContext *ctx) { copyFrom(ctx); }


std::any anceParser::NotEqualContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitNotEqual(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EqualContext ------------------------------------------------------------------

anceParser::EqualContext::EqualContext(BinaryOperatorEqualityContext *ctx) { copyFrom(ctx); }


std::any anceParser::EqualContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitEqual(this);
  else
    return visitor->visitChildren(this);
}
anceParser::BinaryOperatorEqualityContext* anceParser::binaryOperatorEquality() {
  BinaryOperatorEqualityContext *_localctx = _tracker.createInstance<BinaryOperatorEqualityContext>(_ctx, getState());
  enterRule(_localctx, 80, anceParser::RuleBinaryOperatorEquality);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(545);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__54: {
        _localctx = _tracker.createInstance<anceParser::EqualContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(543);
        match(anceParser::T__54);
        break;
      }

      case anceParser::T__55: {
        _localctx = _tracker.createInstance<anceParser::NotEqualContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(544);
        match(anceParser::T__55);
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

//----------------- IndependentExpressionContext ------------------------------------------------------------------

anceParser::IndependentExpressionContext::IndependentExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::FunctionCallContext* anceParser::IndependentExpressionContext::functionCall() {
  return getRuleContext<anceParser::FunctionCallContext>(0);
}


size_t anceParser::IndependentExpressionContext::getRuleIndex() const {
  return anceParser::RuleIndependentExpression;
}


std::any anceParser::IndependentExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitIndependentExpression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::IndependentExpressionContext* anceParser::independentExpression() {
  IndependentExpressionContext *_localctx = _tracker.createInstance<IndependentExpressionContext>(_ctx, getState());
  enterRule(_localctx, 82, anceParser::RuleIndependentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(547);
    functionCall();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

anceParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::FunctionCallContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ArgumentsContext* anceParser::FunctionCallContext::arguments() {
  return getRuleContext<anceParser::ArgumentsContext>(0);
}

anceParser::TypeContext* anceParser::FunctionCallContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}


size_t anceParser::FunctionCallContext::getRuleIndex() const {
  return anceParser::RuleFunctionCall;
}


std::any anceParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

anceParser::FunctionCallContext* anceParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 84, anceParser::RuleFunctionCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(559);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(549);
      match(anceParser::IDENTIFIER);
      setState(550);
      match(anceParser::T__1);
      setState(551);
      arguments();
      setState(552);
      match(anceParser::T__2);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(554);
      type();
      setState(555);
      match(anceParser::T__1);
      setState(556);
      arguments();
      setState(557);
      match(anceParser::T__2);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

anceParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<anceParser::ExpressionContext *> anceParser::ArgumentsContext::expression() {
  return getRuleContexts<anceParser::ExpressionContext>();
}

anceParser::ExpressionContext* anceParser::ArgumentsContext::expression(size_t i) {
  return getRuleContext<anceParser::ExpressionContext>(i);
}


size_t anceParser::ArgumentsContext::getRuleIndex() const {
  return anceParser::RuleArguments;
}


std::any anceParser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ArgumentsContext* anceParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 86, anceParser::RuleArguments);
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
    setState(569);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__1)
      | (1ULL << anceParser::T__22)
      | (1ULL << anceParser::T__28)
      | (1ULL << anceParser::T__34)
      | (1ULL << anceParser::T__39)
      | (1ULL << anceParser::T__41)
      | (1ULL << anceParser::T__42)
      | (1ULL << anceParser::T__43)
      | (1ULL << anceParser::T__56)
      | (1ULL << anceParser::T__59)
      | (1ULL << anceParser::T__60)
      | (1ULL << anceParser::T__62))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (anceParser::T__63 - 64))
      | (1ULL << (anceParser::T__64 - 64))
      | (1ULL << (anceParser::T__65 - 64))
      | (1ULL << (anceParser::T__66 - 64))
      | (1ULL << (anceParser::T__67 - 64))
      | (1ULL << (anceParser::T__68 - 64))
      | (1ULL << (anceParser::T__69 - 64))
      | (1ULL << (anceParser::T__70 - 64))
      | (1ULL << (anceParser::T__71 - 64))
      | (1ULL << (anceParser::T__72 - 64))
      | (1ULL << (anceParser::T__73 - 64))
      | (1ULL << (anceParser::T__74 - 64))
      | (1ULL << (anceParser::T__75 - 64))
      | (1ULL << (anceParser::T__76 - 64))
      | (1ULL << (anceParser::T__77 - 64))
      | (1ULL << (anceParser::NATIVE_INTEGER_TYPE - 64))
      | (1ULL << (anceParser::SIGNED_INTEGER - 64))
      | (1ULL << (anceParser::HEX_INTEGER - 64))
      | (1ULL << (anceParser::BIN_INTEGER - 64))
      | (1ULL << (anceParser::OCT_INTEGER - 64))
      | (1ULL << (anceParser::HALF - 64))
      | (1ULL << (anceParser::SINGLE - 64))
      | (1ULL << (anceParser::DOUBLE - 64))
      | (1ULL << (anceParser::QUAD - 64))
      | (1ULL << (anceParser::STRING - 64))
      | (1ULL << (anceParser::CHAR - 64))
      | (1ULL << (anceParser::INTEGER - 64))
      | (1ULL << (anceParser::BUFFER - 64))
      | (1ULL << (anceParser::NOT - 64))
      | (1ULL << (anceParser::IDENTIFIER - 64)))) != 0)) {
      setState(561);
      expression(0);
      setState(566);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(562);
        match(anceParser::T__5);
        setState(563);
        expression(0);
        setState(568);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableAccessContext ------------------------------------------------------------------

anceParser::VariableAccessContext::VariableAccessContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::VariableAccessContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}


size_t anceParser::VariableAccessContext::getRuleIndex() const {
  return anceParser::RuleVariableAccess;
}


std::any anceParser::VariableAccessContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVariableAccess(this);
  else
    return visitor->visitChildren(this);
}

anceParser::VariableAccessContext* anceParser::variableAccess() {
  VariableAccessContext *_localctx = _tracker.createInstance<VariableAccessContext>(_ctx, getState());
  enterRule(_localctx, 88, anceParser::RuleVariableAccess);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(571);
    match(anceParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AllocationContext ------------------------------------------------------------------

anceParser::AllocationContext::AllocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AllocatorContext* anceParser::AllocationContext::allocator() {
  return getRuleContext<anceParser::AllocatorContext>(0);
}

anceParser::TypeContext* anceParser::AllocationContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::ExpressionContext* anceParser::AllocationContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::AllocationContext::getRuleIndex() const {
  return anceParser::RuleAllocation;
}


std::any anceParser::AllocationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAllocation(this);
  else
    return visitor->visitChildren(this);
}

anceParser::AllocationContext* anceParser::allocation() {
  AllocationContext *_localctx = _tracker.createInstance<AllocationContext>(_ctx, getState());
  enterRule(_localctx, 90, anceParser::RuleAllocation);
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
    setState(573);
    match(anceParser::T__56);
    setState(578);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__34) {
      setState(574);
      match(anceParser::T__34);
      setState(575);
      expression(0);
      setState(576);
      match(anceParser::T__35);
    }
    setState(580);
    allocator();
    setState(581);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AllocatorContext ------------------------------------------------------------------

anceParser::AllocatorContext::AllocatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::AllocatorContext::getRuleIndex() const {
  return anceParser::RuleAllocator;
}

void anceParser::AllocatorContext::copyFrom(AllocatorContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DynamicContext ------------------------------------------------------------------

anceParser::DynamicContext::DynamicContext(AllocatorContext *ctx) { copyFrom(ctx); }


std::any anceParser::DynamicContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitDynamic(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AutomaticContext ------------------------------------------------------------------

anceParser::AutomaticContext::AutomaticContext(AllocatorContext *ctx) { copyFrom(ctx); }


std::any anceParser::AutomaticContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAutomatic(this);
  else
    return visitor->visitChildren(this);
}
anceParser::AllocatorContext* anceParser::allocator() {
  AllocatorContext *_localctx = _tracker.createInstance<AllocatorContext>(_ctx, getState());
  enterRule(_localctx, 92, anceParser::RuleAllocator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(585);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__57: {
        _localctx = _tracker.createInstance<anceParser::DynamicContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(583);
        match(anceParser::T__57);
        break;
      }

      case anceParser::T__58: {
        _localctx = _tracker.createInstance<anceParser::AutomaticContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(584);
        match(anceParser::T__58);
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

//----------------- AddressofContext ------------------------------------------------------------------

anceParser::AddressofContext::AddressofContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ExpressionContext* anceParser::AddressofContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::AddressofContext::getRuleIndex() const {
  return anceParser::RuleAddressof;
}


std::any anceParser::AddressofContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitAddressof(this);
  else
    return visitor->visitChildren(this);
}

anceParser::AddressofContext* anceParser::addressof() {
  AddressofContext *_localctx = _tracker.createInstance<AddressofContext>(_ctx, getState());
  enterRule(_localctx, 94, anceParser::RuleAddressof);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(587);
    match(anceParser::T__59);
    setState(588);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BindRefContext ------------------------------------------------------------------

anceParser::BindRefContext::BindRefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::BindRefContext::getRuleIndex() const {
  return anceParser::RuleBindRef;
}

void anceParser::BindRefContext::copyFrom(BindRefContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BindReferenceToAddressContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::BindReferenceToAddressContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::BindReferenceToAddressContext::BindReferenceToAddressContext(BindRefContext *ctx) { copyFrom(ctx); }


std::any anceParser::BindReferenceToAddressContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBindReferenceToAddress(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BindReferenceContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::BindReferenceContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::BindReferenceContext::BindReferenceContext(BindRefContext *ctx) { copyFrom(ctx); }


std::any anceParser::BindReferenceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBindReference(this);
  else
    return visitor->visitChildren(this);
}
anceParser::BindRefContext* anceParser::bindRef() {
  BindRefContext *_localctx = _tracker.createInstance<BindRefContext>(_ctx, getState());
  enterRule(_localctx, 96, anceParser::RuleBindRef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(595);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::BindReferenceContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(590);
      match(anceParser::T__60);
      setState(591);
      expression(0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::BindReferenceToAddressContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(592);
      match(anceParser::T__60);
      setState(593);
      match(anceParser::T__61);
      setState(594);
      expression(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SizeofTypeContext ------------------------------------------------------------------

anceParser::SizeofTypeContext::SizeofTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::TypeContext* anceParser::SizeofTypeContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}


size_t anceParser::SizeofTypeContext::getRuleIndex() const {
  return anceParser::RuleSizeofType;
}


std::any anceParser::SizeofTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSizeofType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::SizeofTypeContext* anceParser::sizeofType() {
  SizeofTypeContext *_localctx = _tracker.createInstance<SizeofTypeContext>(_ctx, getState());
  enterRule(_localctx, 98, anceParser::RuleSizeofType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(597);
    match(anceParser::T__62);
    setState(598);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SizeofExpressionContext ------------------------------------------------------------------

anceParser::SizeofExpressionContext::SizeofExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ExpressionContext* anceParser::SizeofExpressionContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::SizeofExpressionContext::getRuleIndex() const {
  return anceParser::RuleSizeofExpression;
}


std::any anceParser::SizeofExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSizeofExpression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::SizeofExpressionContext* anceParser::sizeofExpression() {
  SizeofExpressionContext *_localctx = _tracker.createInstance<SizeofExpressionContext>(_ctx, getState());
  enterRule(_localctx, 100, anceParser::RuleSizeofExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(600);
    match(anceParser::T__62);
    setState(601);
    match(anceParser::T__1);
    setState(602);
    expression(0);
    setState(603);
    match(anceParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MatchExpressionContext ------------------------------------------------------------------

anceParser::MatchExpressionContext::MatchExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::ExpressionContext* anceParser::MatchExpressionContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

std::vector<anceParser::MatchExpressionCaseContext *> anceParser::MatchExpressionContext::matchExpressionCase() {
  return getRuleContexts<anceParser::MatchExpressionCaseContext>();
}

anceParser::MatchExpressionCaseContext* anceParser::MatchExpressionContext::matchExpressionCase(size_t i) {
  return getRuleContext<anceParser::MatchExpressionCaseContext>(i);
}


size_t anceParser::MatchExpressionContext::getRuleIndex() const {
  return anceParser::RuleMatchExpression;
}


std::any anceParser::MatchExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitMatchExpression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::MatchExpressionContext* anceParser::matchExpression() {
  MatchExpressionContext *_localctx = _tracker.createInstance<MatchExpressionContext>(_ctx, getState());
  enterRule(_localctx, 102, anceParser::RuleMatchExpression);
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
    setState(605);
    match(anceParser::T__28);
    setState(606);
    antlrcpp::downCast<MatchExpressionContext *>(_localctx)->condition = expression(0);
    setState(607);
    match(anceParser::T__29);
    setState(608);
    match(anceParser::T__3);
    setState(617);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__1

    || _la == anceParser::T__32 || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (anceParser::T__63 - 64))
      | (1ULL << (anceParser::T__64 - 64))
      | (1ULL << (anceParser::T__65 - 64))
      | (1ULL << (anceParser::SIGNED_INTEGER - 64))
      | (1ULL << (anceParser::HEX_INTEGER - 64))
      | (1ULL << (anceParser::BIN_INTEGER - 64))
      | (1ULL << (anceParser::OCT_INTEGER - 64))
      | (1ULL << (anceParser::HALF - 64))
      | (1ULL << (anceParser::SINGLE - 64))
      | (1ULL << (anceParser::DOUBLE - 64))
      | (1ULL << (anceParser::QUAD - 64))
      | (1ULL << (anceParser::STRING - 64))
      | (1ULL << (anceParser::CHAR - 64))
      | (1ULL << (anceParser::INTEGER - 64))
      | (1ULL << (anceParser::IDENTIFIER - 64)))) != 0)) {
      setState(609);
      matchExpressionCase();
      setState(614);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(610);
        match(anceParser::T__5);
        setState(611);
        matchExpressionCase();
        setState(616);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(619);
    match(anceParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MatchExpressionCaseContext ------------------------------------------------------------------

anceParser::MatchExpressionCaseContext::MatchExpressionCaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::MatchExpressionCaseContext::getRuleIndex() const {
  return anceParser::RuleMatchExpressionCase;
}

void anceParser::MatchExpressionCaseContext::copyFrom(MatchExpressionCaseContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LiteralExpressionCaseContext ------------------------------------------------------------------

std::vector<anceParser::LiteralExpressionContext *> anceParser::LiteralExpressionCaseContext::literalExpression() {
  return getRuleContexts<anceParser::LiteralExpressionContext>();
}

anceParser::LiteralExpressionContext* anceParser::LiteralExpressionCaseContext::literalExpression(size_t i) {
  return getRuleContext<anceParser::LiteralExpressionContext>(i);
}

anceParser::ExpressionContext* anceParser::LiteralExpressionCaseContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::LiteralExpressionCaseContext::LiteralExpressionCaseContext(MatchExpressionCaseContext *ctx) { copyFrom(ctx); }


std::any anceParser::LiteralExpressionCaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLiteralExpressionCase(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DefaultExpressionCaseContext ------------------------------------------------------------------

anceParser::ExpressionContext* anceParser::DefaultExpressionCaseContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}

anceParser::DefaultExpressionCaseContext::DefaultExpressionCaseContext(MatchExpressionCaseContext *ctx) { copyFrom(ctx); }


std::any anceParser::DefaultExpressionCaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitDefaultExpressionCase(this);
  else
    return visitor->visitChildren(this);
}
anceParser::MatchExpressionCaseContext* anceParser::matchExpressionCase() {
  MatchExpressionCaseContext *_localctx = _tracker.createInstance<MatchExpressionCaseContext>(_ctx, getState());
  enterRule(_localctx, 104, anceParser::RuleMatchExpressionCase);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(635);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__1:
      case anceParser::T__63:
      case anceParser::T__64:
      case anceParser::T__65:
      case anceParser::SIGNED_INTEGER:
      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER:
      case anceParser::HALF:
      case anceParser::SINGLE:
      case anceParser::DOUBLE:
      case anceParser::QUAD:
      case anceParser::STRING:
      case anceParser::CHAR:
      case anceParser::INTEGER:
      case anceParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<anceParser::LiteralExpressionCaseContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(621);
        literalExpression();
        setState(626);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__30) {
          setState(622);
          match(anceParser::T__30);
          setState(623);
          literalExpression();
          setState(628);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(629);
        match(anceParser::T__31);
        setState(630);
        expression(0);
        break;
      }

      case anceParser::T__32: {
        _localctx = _tracker.createInstance<anceParser::DefaultExpressionCaseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(632);
        match(anceParser::T__32);
        setState(633);
        match(anceParser::T__31);
        setState(634);
        expression(0);
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

//----------------- LiteralExpressionContext ------------------------------------------------------------------

anceParser::LiteralExpressionContext::LiteralExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::StringLiteralContext* anceParser::LiteralExpressionContext::stringLiteral() {
  return getRuleContext<anceParser::StringLiteralContext>(0);
}

anceParser::CharLiteralContext* anceParser::LiteralExpressionContext::charLiteral() {
  return getRuleContext<anceParser::CharLiteralContext>(0);
}

anceParser::IntegerLiteralContext* anceParser::LiteralExpressionContext::integerLiteral() {
  return getRuleContext<anceParser::IntegerLiteralContext>(0);
}

anceParser::FloatingPointLiteralContext* anceParser::LiteralExpressionContext::floatingPointLiteral() {
  return getRuleContext<anceParser::FloatingPointLiteralContext>(0);
}

anceParser::BooleanLiteralContext* anceParser::LiteralExpressionContext::booleanLiteral() {
  return getRuleContext<anceParser::BooleanLiteralContext>(0);
}

anceParser::NullLiteralContext* anceParser::LiteralExpressionContext::nullLiteral() {
  return getRuleContext<anceParser::NullLiteralContext>(0);
}

anceParser::SizeLiteralContext* anceParser::LiteralExpressionContext::sizeLiteral() {
  return getRuleContext<anceParser::SizeLiteralContext>(0);
}

anceParser::DiffLiteralContext* anceParser::LiteralExpressionContext::diffLiteral() {
  return getRuleContext<anceParser::DiffLiteralContext>(0);
}

anceParser::UiptrLiteralContext* anceParser::LiteralExpressionContext::uiptrLiteral() {
  return getRuleContext<anceParser::UiptrLiteralContext>(0);
}

anceParser::UnitLiteralContext* anceParser::LiteralExpressionContext::unitLiteral() {
  return getRuleContext<anceParser::UnitLiteralContext>(0);
}


size_t anceParser::LiteralExpressionContext::getRuleIndex() const {
  return anceParser::RuleLiteralExpression;
}


std::any anceParser::LiteralExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitLiteralExpression(this);
  else
    return visitor->visitChildren(this);
}

anceParser::LiteralExpressionContext* anceParser::literalExpression() {
  LiteralExpressionContext *_localctx = _tracker.createInstance<LiteralExpressionContext>(_ctx, getState());
  enterRule(_localctx, 106, anceParser::RuleLiteralExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(647);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(637);
      stringLiteral();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(638);
      charLiteral();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(639);
      integerLiteral();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(640);
      floatingPointLiteral();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(641);
      booleanLiteral();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(642);
      nullLiteral();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(643);
      sizeLiteral();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(644);
      diffLiteral();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(645);
      uiptrLiteral();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(646);
      unitLiteral();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringLiteralContext ------------------------------------------------------------------

anceParser::StringLiteralContext::StringLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::StringLiteralContext::STRING() {
  return getToken(anceParser::STRING, 0);
}

tree::TerminalNode* anceParser::StringLiteralContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::StringLiteralContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}


size_t anceParser::StringLiteralContext::getRuleIndex() const {
  return anceParser::RuleStringLiteral;
}


std::any anceParser::StringLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitStringLiteral(this);
  else
    return visitor->visitChildren(this);
}

anceParser::StringLiteralContext* anceParser::stringLiteral() {
  StringLiteralContext *_localctx = _tracker.createInstance<StringLiteralContext>(_ctx, getState());
  enterRule(_localctx, 108, anceParser::RuleStringLiteral);
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
    setState(650);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER

    || _la == anceParser::IDENTIFIER) {
      setState(649);
      antlrcpp::downCast<StringLiteralContext *>(_localctx)->prefix = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == anceParser::INTEGER

      || _la == anceParser::IDENTIFIER)) {
        antlrcpp::downCast<StringLiteralContext *>(_localctx)->prefix = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(652);
    match(anceParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CharLiteralContext ------------------------------------------------------------------

anceParser::CharLiteralContext::CharLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::CharLiteralContext::CHAR() {
  return getToken(anceParser::CHAR, 0);
}

tree::TerminalNode* anceParser::CharLiteralContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::CharLiteralContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}


size_t anceParser::CharLiteralContext::getRuleIndex() const {
  return anceParser::RuleCharLiteral;
}


std::any anceParser::CharLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitCharLiteral(this);
  else
    return visitor->visitChildren(this);
}

anceParser::CharLiteralContext* anceParser::charLiteral() {
  CharLiteralContext *_localctx = _tracker.createInstance<CharLiteralContext>(_ctx, getState());
  enterRule(_localctx, 110, anceParser::RuleCharLiteral);
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
    setState(655);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER

    || _la == anceParser::IDENTIFIER) {
      setState(654);
      antlrcpp::downCast<CharLiteralContext *>(_localctx)->prefix = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == anceParser::INTEGER

      || _la == anceParser::IDENTIFIER)) {
        antlrcpp::downCast<CharLiteralContext *>(_localctx)->prefix = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(657);
    match(anceParser::CHAR);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntegerLiteralContext ------------------------------------------------------------------

anceParser::IntegerLiteralContext::IntegerLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::NormalIntegerContext* anceParser::IntegerLiteralContext::normalInteger() {
  return getRuleContext<anceParser::NormalIntegerContext>(0);
}

anceParser::SpecialIntegerContext* anceParser::IntegerLiteralContext::specialInteger() {
  return getRuleContext<anceParser::SpecialIntegerContext>(0);
}


size_t anceParser::IntegerLiteralContext::getRuleIndex() const {
  return anceParser::RuleIntegerLiteral;
}


std::any anceParser::IntegerLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitIntegerLiteral(this);
  else
    return visitor->visitChildren(this);
}

anceParser::IntegerLiteralContext* anceParser::integerLiteral() {
  IntegerLiteralContext *_localctx = _tracker.createInstance<IntegerLiteralContext>(_ctx, getState());
  enterRule(_localctx, 112, anceParser::RuleIntegerLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(661);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::SIGNED_INTEGER:
      case anceParser::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(659);
        normalInteger();
        break;
      }

      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(660);
        specialInteger();
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

//----------------- NormalIntegerContext ------------------------------------------------------------------

anceParser::NormalIntegerContext::NormalIntegerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> anceParser::NormalIntegerContext::INTEGER() {
  return getTokens(anceParser::INTEGER);
}

tree::TerminalNode* anceParser::NormalIntegerContext::INTEGER(size_t i) {
  return getToken(anceParser::INTEGER, i);
}

tree::TerminalNode* anceParser::NormalIntegerContext::SIGNED_INTEGER() {
  return getToken(anceParser::SIGNED_INTEGER, 0);
}


size_t anceParser::NormalIntegerContext::getRuleIndex() const {
  return anceParser::RuleNormalInteger;
}


std::any anceParser::NormalIntegerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitNormalInteger(this);
  else
    return visitor->visitChildren(this);
}

anceParser::NormalIntegerContext* anceParser::normalInteger() {
  NormalIntegerContext *_localctx = _tracker.createInstance<NormalIntegerContext>(_ctx, getState());
  enterRule(_localctx, 114, anceParser::RuleNormalInteger);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(665);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::INTEGER: {
        setState(663);
        antlrcpp::downCast<NormalIntegerContext *>(_localctx)->uvalue = match(anceParser::INTEGER);
        break;
      }

      case anceParser::SIGNED_INTEGER: {
        setState(664);
        antlrcpp::downCast<NormalIntegerContext *>(_localctx)->svalue = match(anceParser::SIGNED_INTEGER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(669);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
    case 1: {
      setState(667);
      match(anceParser::T__0);
      setState(668);
      antlrcpp::downCast<NormalIntegerContext *>(_localctx)->width = match(anceParser::INTEGER);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SpecialIntegerContext ------------------------------------------------------------------

anceParser::SpecialIntegerContext::SpecialIntegerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::SpecialIntegerContext::HEX_INTEGER() {
  return getToken(anceParser::HEX_INTEGER, 0);
}

tree::TerminalNode* anceParser::SpecialIntegerContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}

tree::TerminalNode* anceParser::SpecialIntegerContext::BIN_INTEGER() {
  return getToken(anceParser::BIN_INTEGER, 0);
}

tree::TerminalNode* anceParser::SpecialIntegerContext::OCT_INTEGER() {
  return getToken(anceParser::OCT_INTEGER, 0);
}


size_t anceParser::SpecialIntegerContext::getRuleIndex() const {
  return anceParser::RuleSpecialInteger;
}


std::any anceParser::SpecialIntegerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSpecialInteger(this);
  else
    return visitor->visitChildren(this);
}

anceParser::SpecialIntegerContext* anceParser::specialInteger() {
  SpecialIntegerContext *_localctx = _tracker.createInstance<SpecialIntegerContext>(_ctx, getState());
  enterRule(_localctx, 116, anceParser::RuleSpecialInteger);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(680);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::HEX_INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(671);
        match(anceParser::HEX_INTEGER);
        setState(672);
        match(anceParser::T__0);
        setState(673);
        antlrcpp::downCast<SpecialIntegerContext *>(_localctx)->width = match(anceParser::INTEGER);
        break;
      }

      case anceParser::BIN_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(674);
        match(anceParser::BIN_INTEGER);
        setState(675);
        match(anceParser::T__0);
        setState(676);
        antlrcpp::downCast<SpecialIntegerContext *>(_localctx)->width = match(anceParser::INTEGER);
        break;
      }

      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(677);
        match(anceParser::OCT_INTEGER);
        setState(678);
        match(anceParser::T__0);
        setState(679);
        antlrcpp::downCast<SpecialIntegerContext *>(_localctx)->width = match(anceParser::INTEGER);
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

//----------------- FloatingPointLiteralContext ------------------------------------------------------------------

anceParser::FloatingPointLiteralContext::FloatingPointLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::FloatingPointLiteralContext::HALF() {
  return getToken(anceParser::HALF, 0);
}

tree::TerminalNode* anceParser::FloatingPointLiteralContext::SINGLE() {
  return getToken(anceParser::SINGLE, 0);
}

tree::TerminalNode* anceParser::FloatingPointLiteralContext::DOUBLE() {
  return getToken(anceParser::DOUBLE, 0);
}

tree::TerminalNode* anceParser::FloatingPointLiteralContext::QUAD() {
  return getToken(anceParser::QUAD, 0);
}


size_t anceParser::FloatingPointLiteralContext::getRuleIndex() const {
  return anceParser::RuleFloatingPointLiteral;
}


std::any anceParser::FloatingPointLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFloatingPointLiteral(this);
  else
    return visitor->visitChildren(this);
}

anceParser::FloatingPointLiteralContext* anceParser::floatingPointLiteral() {
  FloatingPointLiteralContext *_localctx = _tracker.createInstance<FloatingPointLiteralContext>(_ctx, getState());
  enterRule(_localctx, 118, anceParser::RuleFloatingPointLiteral);
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
    setState(682);
    _la = _input->LA(1);
    if (!(((((_la - 84) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 84)) & ((1ULL << (anceParser::HALF - 84))
      | (1ULL << (anceParser::SINGLE - 84))
      | (1ULL << (anceParser::DOUBLE - 84))
      | (1ULL << (anceParser::QUAD - 84)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanLiteralContext ------------------------------------------------------------------

anceParser::BooleanLiteralContext::BooleanLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::BooleanLiteralContext::getRuleIndex() const {
  return anceParser::RuleBooleanLiteral;
}

void anceParser::BooleanLiteralContext::copyFrom(BooleanLiteralContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TrueContext ------------------------------------------------------------------

anceParser::TrueContext::TrueContext(BooleanLiteralContext *ctx) { copyFrom(ctx); }


std::any anceParser::TrueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitTrue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FalseContext ------------------------------------------------------------------

anceParser::FalseContext::FalseContext(BooleanLiteralContext *ctx) { copyFrom(ctx); }


std::any anceParser::FalseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFalse(this);
  else
    return visitor->visitChildren(this);
}
anceParser::BooleanLiteralContext* anceParser::booleanLiteral() {
  BooleanLiteralContext *_localctx = _tracker.createInstance<BooleanLiteralContext>(_ctx, getState());
  enterRule(_localctx, 120, anceParser::RuleBooleanLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(686);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__63: {
        _localctx = _tracker.createInstance<anceParser::TrueContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(684);
        match(anceParser::T__63);
        break;
      }

      case anceParser::T__64: {
        _localctx = _tracker.createInstance<anceParser::FalseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(685);
        match(anceParser::T__64);
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

//----------------- NullLiteralContext ------------------------------------------------------------------

anceParser::NullLiteralContext::NullLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::NullLiteralContext::getRuleIndex() const {
  return anceParser::RuleNullLiteral;
}

void anceParser::NullLiteralContext::copyFrom(NullLiteralContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NullContext ------------------------------------------------------------------

anceParser::NullContext::NullContext(NullLiteralContext *ctx) { copyFrom(ctx); }


std::any anceParser::NullContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitNull(this);
  else
    return visitor->visitChildren(this);
}
anceParser::NullLiteralContext* anceParser::nullLiteral() {
  NullLiteralContext *_localctx = _tracker.createInstance<NullLiteralContext>(_ctx, getState());
  enterRule(_localctx, 122, anceParser::RuleNullLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<anceParser::NullContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(688);
    match(anceParser::T__65);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SizeLiteralContext ------------------------------------------------------------------

anceParser::SizeLiteralContext::SizeLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::SizeLiteralContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}


size_t anceParser::SizeLiteralContext::getRuleIndex() const {
  return anceParser::RuleSizeLiteral;
}


std::any anceParser::SizeLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitSizeLiteral(this);
  else
    return visitor->visitChildren(this);
}

anceParser::SizeLiteralContext* anceParser::sizeLiteral() {
  SizeLiteralContext *_localctx = _tracker.createInstance<SizeLiteralContext>(_ctx, getState());
  enterRule(_localctx, 124, anceParser::RuleSizeLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(690);
    match(anceParser::INTEGER);
    setState(691);
    match(anceParser::T__0);
    setState(692);
    match(anceParser::T__66);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DiffLiteralContext ------------------------------------------------------------------

anceParser::DiffLiteralContext::DiffLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::DiffLiteralContext::SIGNED_INTEGER() {
  return getToken(anceParser::SIGNED_INTEGER, 0);
}


size_t anceParser::DiffLiteralContext::getRuleIndex() const {
  return anceParser::RuleDiffLiteral;
}


std::any anceParser::DiffLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitDiffLiteral(this);
  else
    return visitor->visitChildren(this);
}

anceParser::DiffLiteralContext* anceParser::diffLiteral() {
  DiffLiteralContext *_localctx = _tracker.createInstance<DiffLiteralContext>(_ctx, getState());
  enterRule(_localctx, 126, anceParser::RuleDiffLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(694);
    match(anceParser::SIGNED_INTEGER);
    setState(695);
    match(anceParser::T__0);
    setState(696);
    match(anceParser::T__67);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UiptrLiteralContext ------------------------------------------------------------------

anceParser::UiptrLiteralContext::UiptrLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::UiptrLiteralContext::HEX_INTEGER() {
  return getToken(anceParser::HEX_INTEGER, 0);
}


size_t anceParser::UiptrLiteralContext::getRuleIndex() const {
  return anceParser::RuleUiptrLiteral;
}


std::any anceParser::UiptrLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitUiptrLiteral(this);
  else
    return visitor->visitChildren(this);
}

anceParser::UiptrLiteralContext* anceParser::uiptrLiteral() {
  UiptrLiteralContext *_localctx = _tracker.createInstance<UiptrLiteralContext>(_ctx, getState());
  enterRule(_localctx, 128, anceParser::RuleUiptrLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(698);
    match(anceParser::HEX_INTEGER);
    setState(699);
    match(anceParser::T__0);
    setState(700);
    match(anceParser::T__68);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnitLiteralContext ------------------------------------------------------------------

anceParser::UnitLiteralContext::UnitLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::UnitLiteralContext::getRuleIndex() const {
  return anceParser::RuleUnitLiteral;
}


std::any anceParser::UnitLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitUnitLiteral(this);
  else
    return visitor->visitChildren(this);
}

anceParser::UnitLiteralContext* anceParser::unitLiteral() {
  UnitLiteralContext *_localctx = _tracker.createInstance<UnitLiteralContext>(_ctx, getState());
  enterRule(_localctx, 130, anceParser::RuleUnitLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(702);
    match(anceParser::T__1);
    setState(703);
    match(anceParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

anceParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::TypeContext::getRuleIndex() const {
  return anceParser::RuleType;
}

void anceParser::TypeContext::copyFrom(TypeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IntegerContext ------------------------------------------------------------------

anceParser::IntegerTypeContext* anceParser::IntegerContext::integerType() {
  return getRuleContext<anceParser::IntegerTypeContext>(0);
}

anceParser::IntegerContext::IntegerContext(TypeContext *ctx) { copyFrom(ctx); }


std::any anceParser::IntegerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitInteger(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayContext ------------------------------------------------------------------

anceParser::ArrayTypeContext* anceParser::ArrayContext::arrayType() {
  return getRuleContext<anceParser::ArrayTypeContext>(0);
}

anceParser::ArrayContext::ArrayContext(TypeContext *ctx) { copyFrom(ctx); }


std::any anceParser::ArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitArray(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BufferContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::BufferContext::BUFFER() {
  return getToken(anceParser::BUFFER, 0);
}

anceParser::TypeContext* anceParser::BufferContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::BufferContext::BufferContext(TypeContext *ctx) { copyFrom(ctx); }


std::any anceParser::BufferContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBuffer(this);
  else
    return visitor->visitChildren(this);
}
//----------------- KeywordContext ------------------------------------------------------------------

anceParser::KeywordTypeContext* anceParser::KeywordContext::keywordType() {
  return getRuleContext<anceParser::KeywordTypeContext>(0);
}

anceParser::KeywordContext::KeywordContext(TypeContext *ctx) { copyFrom(ctx); }


std::any anceParser::KeywordContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitKeyword(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReferenceContext ------------------------------------------------------------------

anceParser::TypeContext* anceParser::ReferenceContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::ReferenceContext::ReferenceContext(TypeContext *ctx) { copyFrom(ctx); }


std::any anceParser::ReferenceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitReference(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PointerContext ------------------------------------------------------------------

anceParser::TypeContext* anceParser::PointerContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::PointerContext::PointerContext(TypeContext *ctx) { copyFrom(ctx); }


std::any anceParser::PointerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitPointer(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CustomContext ------------------------------------------------------------------

anceParser::CustomTypeContext* anceParser::CustomContext::customType() {
  return getRuleContext<anceParser::CustomTypeContext>(0);
}

anceParser::CustomContext::CustomContext(TypeContext *ctx) { copyFrom(ctx); }


std::any anceParser::CustomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitCustom(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VectorContext ------------------------------------------------------------------

anceParser::VectorTypeContext* anceParser::VectorContext::vectorType() {
  return getRuleContext<anceParser::VectorTypeContext>(0);
}

anceParser::VectorContext::VectorContext(TypeContext *ctx) { copyFrom(ctx); }


std::any anceParser::VectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVector(this);
  else
    return visitor->visitChildren(this);
}
anceParser::TypeContext* anceParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 132, anceParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(716);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::NATIVE_INTEGER_TYPE: {
        _localctx = _tracker.createInstance<anceParser::IntegerContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(705);
        integerType();
        break;
      }

      case anceParser::T__34: {
        _localctx = _tracker.createInstance<anceParser::ArrayContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(706);
        arrayType();
        break;
      }

      case anceParser::T__39: {
        _localctx = _tracker.createInstance<anceParser::VectorContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(707);
        vectorType();
        break;
      }

      case anceParser::T__1:
      case anceParser::T__66:
      case anceParser::T__67:
      case anceParser::T__68:
      case anceParser::T__70:
      case anceParser::T__71:
      case anceParser::T__72:
      case anceParser::T__73:
      case anceParser::T__74:
      case anceParser::T__75:
      case anceParser::T__76:
      case anceParser::T__77: {
        _localctx = _tracker.createInstance<anceParser::KeywordContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(708);
        keywordType();
        break;
      }

      case anceParser::T__43: {
        _localctx = _tracker.createInstance<anceParser::PointerContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(709);
        match(anceParser::T__43);
        setState(710);
        type();
        break;
      }

      case anceParser::BUFFER: {
        _localctx = _tracker.createInstance<anceParser::BufferContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(711);
        match(anceParser::BUFFER);
        setState(712);
        type();
        break;
      }

      case anceParser::T__69: {
        _localctx = _tracker.createInstance<anceParser::ReferenceContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(713);
        match(anceParser::T__69);
        setState(714);
        type();
        break;
      }

      case anceParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<anceParser::CustomContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(715);
        customType();
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

//----------------- IntegerTypeContext ------------------------------------------------------------------

anceParser::IntegerTypeContext::IntegerTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::IntegerTypeContext::NATIVE_INTEGER_TYPE() {
  return getToken(anceParser::NATIVE_INTEGER_TYPE, 0);
}


size_t anceParser::IntegerTypeContext::getRuleIndex() const {
  return anceParser::RuleIntegerType;
}


std::any anceParser::IntegerTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitIntegerType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::IntegerTypeContext* anceParser::integerType() {
  IntegerTypeContext *_localctx = _tracker.createInstance<IntegerTypeContext>(_ctx, getState());
  enterRule(_localctx, 134, anceParser::RuleIntegerType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(718);
    match(anceParser::NATIVE_INTEGER_TYPE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayTypeContext ------------------------------------------------------------------

anceParser::ArrayTypeContext::ArrayTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::TypeContext* anceParser::ArrayTypeContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::ArrayTypeContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

tree::TerminalNode* anceParser::ArrayTypeContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}


size_t anceParser::ArrayTypeContext::getRuleIndex() const {
  return anceParser::RuleArrayType;
}


std::any anceParser::ArrayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitArrayType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::ArrayTypeContext* anceParser::arrayType() {
  ArrayTypeContext *_localctx = _tracker.createInstance<ArrayTypeContext>(_ctx, getState());
  enterRule(_localctx, 136, anceParser::RuleArrayType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(720);
    match(anceParser::T__34);
    setState(721);
    type();
    setState(722);
    match(anceParser::SEMICOLON);
    setState(723);
    match(anceParser::INTEGER);
    setState(724);
    match(anceParser::T__35);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VectorTypeContext ------------------------------------------------------------------

anceParser::VectorTypeContext::VectorTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::TypeContext* anceParser::VectorTypeContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::VectorTypeContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

tree::TerminalNode* anceParser::VectorTypeContext::INTEGER() {
  return getToken(anceParser::INTEGER, 0);
}


size_t anceParser::VectorTypeContext::getRuleIndex() const {
  return anceParser::RuleVectorType;
}


std::any anceParser::VectorTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVectorType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::VectorTypeContext* anceParser::vectorType() {
  VectorTypeContext *_localctx = _tracker.createInstance<VectorTypeContext>(_ctx, getState());
  enterRule(_localctx, 138, anceParser::RuleVectorType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(726);
    match(anceParser::T__39);
    setState(727);
    type();
    setState(728);
    match(anceParser::SEMICOLON);
    setState(729);
    match(anceParser::INTEGER);
    setState(730);
    match(anceParser::T__40);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeywordTypeContext ------------------------------------------------------------------

anceParser::KeywordTypeContext::KeywordTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::FloatingPointTypeContext* anceParser::KeywordTypeContext::floatingPointType() {
  return getRuleContext<anceParser::FloatingPointTypeContext>(0);
}

anceParser::TargetDependentTypeContext* anceParser::KeywordTypeContext::targetDependentType() {
  return getRuleContext<anceParser::TargetDependentTypeContext>(0);
}

anceParser::BooleanTypeContext* anceParser::KeywordTypeContext::booleanType() {
  return getRuleContext<anceParser::BooleanTypeContext>(0);
}

anceParser::CharTypeContext* anceParser::KeywordTypeContext::charType() {
  return getRuleContext<anceParser::CharTypeContext>(0);
}

anceParser::NullPointerTypeContext* anceParser::KeywordTypeContext::nullPointerType() {
  return getRuleContext<anceParser::NullPointerTypeContext>(0);
}

anceParser::UnitTypeContext* anceParser::KeywordTypeContext::unitType() {
  return getRuleContext<anceParser::UnitTypeContext>(0);
}


size_t anceParser::KeywordTypeContext::getRuleIndex() const {
  return anceParser::RuleKeywordType;
}


std::any anceParser::KeywordTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitKeywordType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::KeywordTypeContext* anceParser::keywordType() {
  KeywordTypeContext *_localctx = _tracker.createInstance<KeywordTypeContext>(_ctx, getState());
  enterRule(_localctx, 140, anceParser::RuleKeywordType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(738);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__70:
      case anceParser::T__71:
      case anceParser::T__72:
      case anceParser::T__73: {
        enterOuterAlt(_localctx, 1);
        setState(732);
        floatingPointType();
        break;
      }

      case anceParser::T__66:
      case anceParser::T__67:
      case anceParser::T__68:
      case anceParser::T__74: {
        enterOuterAlt(_localctx, 2);
        setState(733);
        targetDependentType();
        break;
      }

      case anceParser::T__75: {
        enterOuterAlt(_localctx, 3);
        setState(734);
        booleanType();
        break;
      }

      case anceParser::T__76: {
        enterOuterAlt(_localctx, 4);
        setState(735);
        charType();
        break;
      }

      case anceParser::T__77: {
        enterOuterAlt(_localctx, 5);
        setState(736);
        nullPointerType();
        break;
      }

      case anceParser::T__1: {
        enterOuterAlt(_localctx, 6);
        setState(737);
        unitType();
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

//----------------- FloatingPointTypeContext ------------------------------------------------------------------

anceParser::FloatingPointTypeContext::FloatingPointTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::FloatingPointTypeContext::getRuleIndex() const {
  return anceParser::RuleFloatingPointType;
}


std::any anceParser::FloatingPointTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFloatingPointType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::FloatingPointTypeContext* anceParser::floatingPointType() {
  FloatingPointTypeContext *_localctx = _tracker.createInstance<FloatingPointTypeContext>(_ctx, getState());
  enterRule(_localctx, 142, anceParser::RuleFloatingPointType);
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
    setState(740);
    _la = _input->LA(1);
    if (!(((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & ((1ULL << (anceParser::T__70 - 71))
      | (1ULL << (anceParser::T__71 - 71))
      | (1ULL << (anceParser::T__72 - 71))
      | (1ULL << (anceParser::T__73 - 71)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TargetDependentTypeContext ------------------------------------------------------------------

anceParser::TargetDependentTypeContext::TargetDependentTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::TargetDependentTypeContext::getRuleIndex() const {
  return anceParser::RuleTargetDependentType;
}


std::any anceParser::TargetDependentTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitTargetDependentType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::TargetDependentTypeContext* anceParser::targetDependentType() {
  TargetDependentTypeContext *_localctx = _tracker.createInstance<TargetDependentTypeContext>(_ctx, getState());
  enterRule(_localctx, 144, anceParser::RuleTargetDependentType);
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
    setState(742);
    _la = _input->LA(1);
    if (!(((((_la - 67) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 67)) & ((1ULL << (anceParser::T__66 - 67))
      | (1ULL << (anceParser::T__67 - 67))
      | (1ULL << (anceParser::T__68 - 67))
      | (1ULL << (anceParser::T__74 - 67)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanTypeContext ------------------------------------------------------------------

anceParser::BooleanTypeContext::BooleanTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::BooleanTypeContext::getRuleIndex() const {
  return anceParser::RuleBooleanType;
}


std::any anceParser::BooleanTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitBooleanType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::BooleanTypeContext* anceParser::booleanType() {
  BooleanTypeContext *_localctx = _tracker.createInstance<BooleanTypeContext>(_ctx, getState());
  enterRule(_localctx, 146, anceParser::RuleBooleanType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(744);
    match(anceParser::T__75);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CharTypeContext ------------------------------------------------------------------

anceParser::CharTypeContext::CharTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::CharTypeContext::getRuleIndex() const {
  return anceParser::RuleCharType;
}


std::any anceParser::CharTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitCharType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::CharTypeContext* anceParser::charType() {
  CharTypeContext *_localctx = _tracker.createInstance<CharTypeContext>(_ctx, getState());
  enterRule(_localctx, 148, anceParser::RuleCharType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(746);
    match(anceParser::T__76);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NullPointerTypeContext ------------------------------------------------------------------

anceParser::NullPointerTypeContext::NullPointerTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::NullPointerTypeContext::getRuleIndex() const {
  return anceParser::RuleNullPointerType;
}


std::any anceParser::NullPointerTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitNullPointerType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::NullPointerTypeContext* anceParser::nullPointerType() {
  NullPointerTypeContext *_localctx = _tracker.createInstance<NullPointerTypeContext>(_ctx, getState());
  enterRule(_localctx, 150, anceParser::RuleNullPointerType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(748);
    match(anceParser::T__77);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnitTypeContext ------------------------------------------------------------------

anceParser::UnitTypeContext::UnitTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::UnitTypeContext::getRuleIndex() const {
  return anceParser::RuleUnitType;
}


std::any anceParser::UnitTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitUnitType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::UnitTypeContext* anceParser::unitType() {
  UnitTypeContext *_localctx = _tracker.createInstance<UnitTypeContext>(_ctx, getState());
  enterRule(_localctx, 152, anceParser::RuleUnitType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(750);
    match(anceParser::T__1);
    setState(751);
    match(anceParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CustomTypeContext ------------------------------------------------------------------

anceParser::CustomTypeContext::CustomTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::CustomTypeContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}


size_t anceParser::CustomTypeContext::getRuleIndex() const {
  return anceParser::RuleCustomType;
}


std::any anceParser::CustomTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitCustomType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::CustomTypeContext* anceParser::customType() {
  CustomTypeContext *_localctx = _tracker.createInstance<CustomTypeContext>(_ctx, getState());
  enterRule(_localctx, 154, anceParser::RuleCustomType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(753);
    match(anceParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool anceParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 33: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool anceParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 12);
    case 1: return precpred(_ctx, 11);
    case 2: return precpred(_ctx, 10);
    case 3: return precpred(_ctx, 9);
    case 4: return precpred(_ctx, 8);
    case 5: return precpred(_ctx, 7);
    case 6: return precpred(_ctx, 6);
    case 7: return precpred(_ctx, 5);
    case 8: return precpred(_ctx, 23);
    case 9: return precpred(_ctx, 22);
    case 10: return precpred(_ctx, 21);
    case 11: return precpred(_ctx, 16);

  default:
    break;
  }
  return true;
}

void anceParser::initialize() {
  std::call_once(anceParserOnceFlag, anceParserInitialize);
}
