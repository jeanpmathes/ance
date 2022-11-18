
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
      "file", "variableDeclaration", "function", "parameters", "parameter", 
      "typeDefinition", "defineAlias", "structDefinition", "member", "accessModifier", 
      "code", "block", "statement", "expressionStatement", "localVariableDefinition", 
      "localReferenceDefinition", "dropStatement", "assignment", "assigner", 
      "deleteStatement", "breakStatement", "continueStatement", "returnStatement", 
      "assertStatement", "ifStatement", "whileStatement", "matchStatement", 
      "matchCase", "expression", "unaryOperator", "binaryOperatorMultiplicative", 
      "binaryOperatorAdditive", "binaryOperatorBitwise", "binaryOperatorShift", 
      "binaryOperatorRelational", "binaryOperatorEquality", "independentExpression", 
      "functionCall", "arguments", "variableAccess", "allocation", "allocator", 
      "addressof", "bindRef", "sizeofType", "sizeofExpression", "matchExpression", 
      "matchExpressionCase", "literalExpression", "stringLiteral", "charLiteral", 
      "integerLiteral", "normalInteger", "specialInteger", "floatingPointLiteral", 
      "booleanLiteral", "nullLiteral", "sizeLiteral", "diffLiteral", "uiptrLiteral", 
      "type", "integerType", "arrayType", "vectorType", "keywordType", "floatingPointType", 
      "targetDependentType", "booleanType", "charType", "nullPointerType", 
      "voidType", "customType"
    },
    std::vector<std::string>{
      "", "':'", "'('", "')'", "'{'", "'}'", "'extern'", "','", "'define'", 
      "'alias'", "'struct'", "'public'", "'private'", "'let'", "'drop'", 
      "'<:'", "'<-'", "':='", "'delete'", "'break'", "'continue'", "'return'", 
      "'assert'", "'if'", "'then'", "'else'", "'while'", "'do'", "'match'", 
      "'with'", "'|'", "'=>'", "'default'", "'.'", "'['", "']'", "'and'", 
      "'or'", "'<'", "'>'", "'<not>'", "'-'", "'*'", "'/'", "'%'", "'+'", 
      "'<and>'", "'<or>'", "'<xor>'", "'<sl>'", "'<sr>'", "'<='", "'>='", 
      "'=='", "'/='", "'new'", "'dynamic'", "'automatic'", "'addressof'", 
      "'ref'", "'to'", "'sizeof'", "'true'", "'false'", "'null'", "'size'", 
      "'diff'", "'uiptr'", "'&'", "'half'", "'single'", "'double'", "'quad'", 
      "'ptr'", "'bool'", "'char'", "'nullptr'", "'void'", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "'[]'", "'const'", "'not'", "", 
      "';'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "NATIVE_INTEGER_TYPE", "SIGNED_INTEGER", 
      "HEX_INTEGER", "BIN_INTEGER", "OCT_INTEGER", "HALF", "SINGLE", "DOUBLE", 
      "QUAD", "DECIMAL", "STRING", "CHAR", "INTEGER", "BUFFER", "CONST", 
      "NOT", "IDENTIFIER", "SEMICOLON", "WHITESPACE", "BLOCK_COMMENT", "LINE_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,98,727,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,7,
  	70,2,71,7,71,1,0,1,0,1,0,5,0,148,8,0,10,0,12,0,151,9,0,1,0,1,0,1,1,1,
  	1,3,1,157,8,1,1,1,1,1,1,1,3,1,162,8,1,1,1,1,1,1,1,3,1,167,8,1,1,1,1,1,
  	1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,178,8,2,1,2,1,2,5,2,182,8,2,10,2,12,2,
  	185,9,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,196,8,2,1,2,1,2,3,2,200,
  	8,2,1,3,1,3,1,3,5,3,205,8,3,10,3,12,3,208,9,3,3,3,210,8,3,1,4,1,4,1,4,
  	1,4,1,5,1,5,3,5,218,8,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,
  	7,5,7,232,8,7,10,7,12,7,235,9,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,
  	8,246,8,8,1,8,1,8,1,9,1,9,3,9,252,8,9,1,10,1,10,3,10,256,8,10,1,11,1,
  	11,5,11,260,8,11,10,11,12,11,263,9,11,1,11,1,11,1,12,1,12,1,12,1,12,1,
  	12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,3,12,280,8,12,1,13,1,13,1,
  	13,1,14,1,14,1,14,1,14,3,14,289,8,14,1,14,1,14,1,14,3,14,294,8,14,1,14,
  	1,14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,17,1,17,
  	1,17,1,17,1,17,1,18,1,18,1,18,3,18,317,8,18,1,19,1,19,3,19,321,8,19,1,
  	19,1,19,1,19,1,20,1,20,1,20,1,21,1,21,1,21,1,22,1,22,3,22,334,8,22,1,
  	22,1,22,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,24,3,24,348,8,
  	24,1,25,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,1,26,5,26,360,8,26,10,
  	26,12,26,363,9,26,1,26,1,26,1,27,1,27,1,27,5,27,370,8,27,10,27,12,27,
  	373,9,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,381,8,27,1,28,1,28,1,28,1,
  	28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,
  	28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,3,28,411,8,28,1,
  	28,1,28,1,28,5,28,416,8,28,10,28,12,28,419,9,28,1,28,1,28,1,28,1,28,1,
  	28,1,28,3,28,427,8,28,1,28,1,28,1,28,5,28,432,8,28,10,28,12,28,435,9,
  	28,1,28,1,28,3,28,439,8,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,
  	28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,
  	28,1,28,1,28,1,28,3,28,467,8,28,1,28,1,28,1,28,1,28,3,28,473,8,28,1,28,
  	1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,5,28,486,8,28,10,28,
  	12,28,489,9,28,1,29,1,29,1,29,3,29,494,8,29,1,30,1,30,1,30,3,30,499,8,
  	30,1,31,1,31,3,31,503,8,31,1,32,1,32,1,32,3,32,508,8,32,1,33,1,33,3,33,
  	512,8,33,1,34,1,34,1,34,1,34,3,34,518,8,34,1,35,1,35,3,35,522,8,35,1,
  	36,1,36,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,3,37,536,8,
  	37,1,38,1,38,1,38,5,38,541,8,38,10,38,12,38,544,9,38,3,38,546,8,38,1,
  	39,1,39,1,40,1,40,1,40,1,40,1,40,3,40,555,8,40,1,40,1,40,1,40,1,41,1,
  	41,3,41,562,8,41,1,42,1,42,1,42,1,43,1,43,1,43,1,43,1,43,3,43,572,8,43,
  	1,44,1,44,1,44,1,45,1,45,1,45,1,45,1,45,1,46,1,46,1,46,1,46,1,46,1,46,
  	1,46,5,46,589,8,46,10,46,12,46,592,9,46,3,46,594,8,46,1,46,1,46,1,47,
  	1,47,1,47,5,47,601,8,47,10,47,12,47,604,9,47,1,47,1,47,1,47,1,47,1,47,
  	1,47,3,47,612,8,47,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,3,48,
  	623,8,48,1,49,3,49,626,8,49,1,49,1,49,1,50,3,50,631,8,50,1,50,1,50,1,
  	51,1,51,3,51,637,8,51,1,52,1,52,3,52,641,8,52,1,52,1,52,3,52,645,8,52,
  	1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,3,53,656,8,53,1,54,1,54,
  	1,55,1,55,3,55,662,8,55,1,56,1,56,1,57,1,57,1,57,1,57,1,58,1,58,1,58,
  	1,58,1,59,1,59,1,59,1,59,1,60,1,60,1,60,1,60,1,60,1,60,1,60,1,60,1,60,
  	1,60,1,60,3,60,689,8,60,1,61,1,61,1,62,1,62,1,62,1,62,1,62,1,62,1,63,
  	1,63,1,63,1,63,1,63,1,63,1,64,1,64,1,64,1,64,1,64,1,64,3,64,711,8,64,
  	1,65,1,65,1,66,1,66,1,67,1,67,1,68,1,68,1,69,1,69,1,70,1,70,1,71,1,71,
  	1,71,0,1,56,72,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,
  	40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,
  	86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,
  	124,126,128,130,132,134,136,138,140,142,0,4,2,0,90,90,94,94,1,0,83,86,
  	1,0,69,72,2,0,65,67,73,73,774,0,149,1,0,0,0,2,154,1,0,0,0,4,199,1,0,0,
  	0,6,209,1,0,0,0,8,211,1,0,0,0,10,217,1,0,0,0,12,219,1,0,0,0,14,226,1,
  	0,0,0,16,238,1,0,0,0,18,251,1,0,0,0,20,255,1,0,0,0,22,257,1,0,0,0,24,
  	279,1,0,0,0,26,281,1,0,0,0,28,284,1,0,0,0,30,297,1,0,0,0,32,304,1,0,0,
  	0,34,308,1,0,0,0,36,316,1,0,0,0,38,318,1,0,0,0,40,325,1,0,0,0,42,328,
  	1,0,0,0,44,331,1,0,0,0,46,337,1,0,0,0,48,341,1,0,0,0,50,349,1,0,0,0,52,
  	354,1,0,0,0,54,380,1,0,0,0,56,438,1,0,0,0,58,493,1,0,0,0,60,498,1,0,0,
  	0,62,502,1,0,0,0,64,507,1,0,0,0,66,511,1,0,0,0,68,517,1,0,0,0,70,521,
  	1,0,0,0,72,523,1,0,0,0,74,535,1,0,0,0,76,545,1,0,0,0,78,547,1,0,0,0,80,
  	549,1,0,0,0,82,561,1,0,0,0,84,563,1,0,0,0,86,571,1,0,0,0,88,573,1,0,0,
  	0,90,576,1,0,0,0,92,581,1,0,0,0,94,611,1,0,0,0,96,622,1,0,0,0,98,625,
  	1,0,0,0,100,630,1,0,0,0,102,636,1,0,0,0,104,640,1,0,0,0,106,655,1,0,0,
  	0,108,657,1,0,0,0,110,661,1,0,0,0,112,663,1,0,0,0,114,665,1,0,0,0,116,
  	669,1,0,0,0,118,673,1,0,0,0,120,688,1,0,0,0,122,690,1,0,0,0,124,692,1,
  	0,0,0,126,698,1,0,0,0,128,710,1,0,0,0,130,712,1,0,0,0,132,714,1,0,0,0,
  	134,716,1,0,0,0,136,718,1,0,0,0,138,720,1,0,0,0,140,722,1,0,0,0,142,724,
  	1,0,0,0,144,148,3,2,1,0,145,148,3,4,2,0,146,148,3,10,5,0,147,144,1,0,
  	0,0,147,145,1,0,0,0,147,146,1,0,0,0,148,151,1,0,0,0,149,147,1,0,0,0,149,
  	150,1,0,0,0,150,152,1,0,0,0,151,149,1,0,0,0,152,153,5,0,0,1,153,1,1,0,
  	0,0,154,156,3,18,9,0,155,157,5,92,0,0,156,155,1,0,0,0,156,157,1,0,0,0,
  	157,158,1,0,0,0,158,161,5,94,0,0,159,160,5,1,0,0,160,162,3,120,60,0,161,
  	159,1,0,0,0,161,162,1,0,0,0,162,166,1,0,0,0,163,164,3,36,18,0,164,165,
  	3,56,28,0,165,167,1,0,0,0,166,163,1,0,0,0,166,167,1,0,0,0,167,168,1,0,
  	0,0,168,169,5,95,0,0,169,3,1,0,0,0,170,171,3,18,9,0,171,172,5,94,0,0,
  	172,173,5,2,0,0,173,174,3,6,3,0,174,177,5,3,0,0,175,176,5,1,0,0,176,178,
  	3,120,60,0,177,175,1,0,0,0,177,178,1,0,0,0,178,179,1,0,0,0,179,183,5,
  	4,0,0,180,182,3,20,10,0,181,180,1,0,0,0,182,185,1,0,0,0,183,181,1,0,0,
  	0,183,184,1,0,0,0,184,186,1,0,0,0,185,183,1,0,0,0,186,187,5,5,0,0,187,
  	200,1,0,0,0,188,189,5,6,0,0,189,190,5,94,0,0,190,191,5,2,0,0,191,192,
  	3,6,3,0,192,195,5,3,0,0,193,194,5,1,0,0,194,196,3,120,60,0,195,193,1,
  	0,0,0,195,196,1,0,0,0,196,197,1,0,0,0,197,198,5,95,0,0,198,200,1,0,0,
  	0,199,170,1,0,0,0,199,188,1,0,0,0,200,5,1,0,0,0,201,206,3,8,4,0,202,203,
  	5,7,0,0,203,205,3,8,4,0,204,202,1,0,0,0,205,208,1,0,0,0,206,204,1,0,0,
  	0,206,207,1,0,0,0,207,210,1,0,0,0,208,206,1,0,0,0,209,201,1,0,0,0,209,
  	210,1,0,0,0,210,7,1,0,0,0,211,212,5,94,0,0,212,213,5,1,0,0,213,214,3,
  	120,60,0,214,9,1,0,0,0,215,218,3,12,6,0,216,218,3,14,7,0,217,215,1,0,
  	0,0,217,216,1,0,0,0,218,11,1,0,0,0,219,220,3,18,9,0,220,221,5,8,0,0,221,
  	222,5,94,0,0,222,223,5,9,0,0,223,224,3,120,60,0,224,225,5,95,0,0,225,
  	13,1,0,0,0,226,227,3,18,9,0,227,228,5,10,0,0,228,229,5,94,0,0,229,233,
  	5,4,0,0,230,232,3,16,8,0,231,230,1,0,0,0,232,235,1,0,0,0,233,231,1,0,
  	0,0,233,234,1,0,0,0,234,236,1,0,0,0,235,233,1,0,0,0,236,237,5,5,0,0,237,
  	15,1,0,0,0,238,239,3,18,9,0,239,240,5,94,0,0,240,241,5,1,0,0,241,245,
  	3,120,60,0,242,243,3,36,18,0,243,244,3,96,48,0,244,246,1,0,0,0,245,242,
  	1,0,0,0,245,246,1,0,0,0,246,247,1,0,0,0,247,248,5,95,0,0,248,17,1,0,0,
  	0,249,252,5,11,0,0,250,252,5,12,0,0,251,249,1,0,0,0,251,250,1,0,0,0,252,
  	19,1,0,0,0,253,256,3,24,12,0,254,256,3,22,11,0,255,253,1,0,0,0,255,254,
  	1,0,0,0,256,21,1,0,0,0,257,261,5,4,0,0,258,260,3,20,10,0,259,258,1,0,
  	0,0,260,263,1,0,0,0,261,259,1,0,0,0,261,262,1,0,0,0,262,264,1,0,0,0,263,
  	261,1,0,0,0,264,265,5,5,0,0,265,23,1,0,0,0,266,280,3,26,13,0,267,280,
  	3,28,14,0,268,280,3,30,15,0,269,280,3,32,16,0,270,280,3,34,17,0,271,280,
  	3,38,19,0,272,280,3,40,20,0,273,280,3,42,21,0,274,280,3,44,22,0,275,280,
  	3,46,23,0,276,280,3,48,24,0,277,280,3,50,25,0,278,280,3,52,26,0,279,266,
  	1,0,0,0,279,267,1,0,0,0,279,268,1,0,0,0,279,269,1,0,0,0,279,270,1,0,0,
  	0,279,271,1,0,0,0,279,272,1,0,0,0,279,273,1,0,0,0,279,274,1,0,0,0,279,
  	275,1,0,0,0,279,276,1,0,0,0,279,277,1,0,0,0,279,278,1,0,0,0,280,25,1,
  	0,0,0,281,282,3,72,36,0,282,283,5,95,0,0,283,27,1,0,0,0,284,285,5,13,
  	0,0,285,288,5,94,0,0,286,287,5,1,0,0,287,289,3,120,60,0,288,286,1,0,0,
  	0,288,289,1,0,0,0,289,293,1,0,0,0,290,291,3,36,18,0,291,292,3,56,28,0,
  	292,294,1,0,0,0,293,290,1,0,0,0,293,294,1,0,0,0,294,295,1,0,0,0,295,296,
  	5,95,0,0,296,29,1,0,0,0,297,298,5,13,0,0,298,299,5,94,0,0,299,300,5,1,
  	0,0,300,301,3,120,60,0,301,302,3,86,43,0,302,303,5,95,0,0,303,31,1,0,
  	0,0,304,305,5,14,0,0,305,306,5,94,0,0,306,307,5,95,0,0,307,33,1,0,0,0,
  	308,309,3,56,28,0,309,310,3,36,18,0,310,311,3,56,28,0,311,312,5,95,0,
  	0,312,35,1,0,0,0,313,317,5,15,0,0,314,317,5,16,0,0,315,317,5,17,0,0,316,
  	313,1,0,0,0,316,314,1,0,0,0,316,315,1,0,0,0,317,37,1,0,0,0,318,320,5,
  	18,0,0,319,321,5,91,0,0,320,319,1,0,0,0,320,321,1,0,0,0,321,322,1,0,0,
  	0,322,323,3,56,28,0,323,324,5,95,0,0,324,39,1,0,0,0,325,326,5,19,0,0,
  	326,327,5,95,0,0,327,41,1,0,0,0,328,329,5,20,0,0,329,330,5,95,0,0,330,
  	43,1,0,0,0,331,333,5,21,0,0,332,334,3,56,28,0,333,332,1,0,0,0,333,334,
  	1,0,0,0,334,335,1,0,0,0,335,336,5,95,0,0,336,45,1,0,0,0,337,338,5,22,
  	0,0,338,339,3,56,28,0,339,340,5,95,0,0,340,47,1,0,0,0,341,342,5,23,0,
  	0,342,343,3,56,28,0,343,344,5,24,0,0,344,347,3,20,10,0,345,346,5,25,0,
  	0,346,348,3,20,10,0,347,345,1,0,0,0,347,348,1,0,0,0,348,49,1,0,0,0,349,
  	350,5,26,0,0,350,351,3,56,28,0,351,352,5,27,0,0,352,353,3,20,10,0,353,
  	51,1,0,0,0,354,355,5,28,0,0,355,356,3,56,28,0,356,357,5,29,0,0,357,361,
  	5,4,0,0,358,360,3,54,27,0,359,358,1,0,0,0,360,363,1,0,0,0,361,359,1,0,
  	0,0,361,362,1,0,0,0,362,364,1,0,0,0,363,361,1,0,0,0,364,365,5,5,0,0,365,
  	53,1,0,0,0,366,371,3,96,48,0,367,368,5,30,0,0,368,370,3,96,48,0,369,367,
  	1,0,0,0,370,373,1,0,0,0,371,369,1,0,0,0,371,372,1,0,0,0,372,374,1,0,0,
  	0,373,371,1,0,0,0,374,375,5,31,0,0,375,376,3,20,10,0,376,381,1,0,0,0,
  	377,378,5,32,0,0,378,379,5,31,0,0,379,381,3,20,10,0,380,366,1,0,0,0,380,
  	377,1,0,0,0,381,55,1,0,0,0,382,383,6,28,-1,0,383,439,3,78,39,0,384,439,
  	3,80,40,0,385,439,3,96,48,0,386,439,3,84,42,0,387,439,3,86,43,0,388,439,
  	3,88,44,0,389,439,3,90,45,0,390,439,3,72,36,0,391,392,5,2,0,0,392,393,
  	3,56,28,0,393,394,5,3,0,0,394,439,1,0,0,0,395,396,3,58,29,0,396,397,3,
  	56,28,13,397,439,1,0,0,0,398,399,5,23,0,0,399,400,3,56,28,0,400,401,5,
  	24,0,0,401,402,3,56,28,0,402,403,5,25,0,0,403,404,3,56,28,4,404,439,1,
  	0,0,0,405,439,3,92,46,0,406,410,5,38,0,0,407,408,3,120,60,0,408,409,5,
  	30,0,0,409,411,1,0,0,0,410,407,1,0,0,0,410,411,1,0,0,0,411,412,1,0,0,
  	0,412,417,3,56,28,0,413,414,5,7,0,0,414,416,3,56,28,0,415,413,1,0,0,0,
  	416,419,1,0,0,0,417,415,1,0,0,0,417,418,1,0,0,0,418,420,1,0,0,0,419,417,
  	1,0,0,0,420,421,5,39,0,0,421,439,1,0,0,0,422,426,5,34,0,0,423,424,3,120,
  	60,0,424,425,5,30,0,0,425,427,1,0,0,0,426,423,1,0,0,0,426,427,1,0,0,0,
  	427,428,1,0,0,0,428,433,3,56,28,0,429,430,5,7,0,0,430,432,3,56,28,0,431,
  	429,1,0,0,0,432,435,1,0,0,0,433,431,1,0,0,0,433,434,1,0,0,0,434,436,1,
  	0,0,0,435,433,1,0,0,0,436,437,5,35,0,0,437,439,1,0,0,0,438,382,1,0,0,
  	0,438,384,1,0,0,0,438,385,1,0,0,0,438,386,1,0,0,0,438,387,1,0,0,0,438,
  	388,1,0,0,0,438,389,1,0,0,0,438,390,1,0,0,0,438,391,1,0,0,0,438,395,1,
  	0,0,0,438,398,1,0,0,0,438,405,1,0,0,0,438,406,1,0,0,0,438,422,1,0,0,0,
  	439,487,1,0,0,0,440,441,10,12,0,0,441,442,3,60,30,0,442,443,3,56,28,13,
  	443,486,1,0,0,0,444,445,10,11,0,0,445,446,3,62,31,0,446,447,3,56,28,12,
  	447,486,1,0,0,0,448,449,10,10,0,0,449,450,3,64,32,0,450,451,3,56,28,11,
  	451,486,1,0,0,0,452,453,10,9,0,0,453,454,3,66,33,0,454,455,3,56,28,10,
  	455,486,1,0,0,0,456,457,10,8,0,0,457,458,3,68,34,0,458,459,3,56,28,9,
  	459,486,1,0,0,0,460,461,10,7,0,0,461,462,3,70,35,0,462,463,3,56,28,8,
  	463,486,1,0,0,0,464,466,10,6,0,0,465,467,5,93,0,0,466,465,1,0,0,0,466,
  	467,1,0,0,0,467,468,1,0,0,0,468,469,5,36,0,0,469,486,3,56,28,7,470,472,
  	10,5,0,0,471,473,5,93,0,0,472,471,1,0,0,0,472,473,1,0,0,0,473,474,1,0,
  	0,0,474,475,5,37,0,0,475,486,3,56,28,6,476,477,10,22,0,0,477,486,5,33,
  	0,0,478,479,10,21,0,0,479,480,5,34,0,0,480,481,3,56,28,0,481,482,5,35,
  	0,0,482,486,1,0,0,0,483,484,10,20,0,0,484,486,5,94,0,0,485,440,1,0,0,
  	0,485,444,1,0,0,0,485,448,1,0,0,0,485,452,1,0,0,0,485,456,1,0,0,0,485,
  	460,1,0,0,0,485,464,1,0,0,0,485,470,1,0,0,0,485,476,1,0,0,0,485,478,1,
  	0,0,0,485,483,1,0,0,0,486,489,1,0,0,0,487,485,1,0,0,0,487,488,1,0,0,0,
  	488,57,1,0,0,0,489,487,1,0,0,0,490,494,5,93,0,0,491,494,5,40,0,0,492,
  	494,5,41,0,0,493,490,1,0,0,0,493,491,1,0,0,0,493,492,1,0,0,0,494,59,1,
  	0,0,0,495,499,5,42,0,0,496,499,5,43,0,0,497,499,5,44,0,0,498,495,1,0,
  	0,0,498,496,1,0,0,0,498,497,1,0,0,0,499,61,1,0,0,0,500,503,5,45,0,0,501,
  	503,5,41,0,0,502,500,1,0,0,0,502,501,1,0,0,0,503,63,1,0,0,0,504,508,5,
  	46,0,0,505,508,5,47,0,0,506,508,5,48,0,0,507,504,1,0,0,0,507,505,1,0,
  	0,0,507,506,1,0,0,0,508,65,1,0,0,0,509,512,5,49,0,0,510,512,5,50,0,0,
  	511,509,1,0,0,0,511,510,1,0,0,0,512,67,1,0,0,0,513,518,5,38,0,0,514,518,
  	5,51,0,0,515,518,5,39,0,0,516,518,5,52,0,0,517,513,1,0,0,0,517,514,1,
  	0,0,0,517,515,1,0,0,0,517,516,1,0,0,0,518,69,1,0,0,0,519,522,5,53,0,0,
  	520,522,5,54,0,0,521,519,1,0,0,0,521,520,1,0,0,0,522,71,1,0,0,0,523,524,
  	3,74,37,0,524,73,1,0,0,0,525,526,5,94,0,0,526,527,5,2,0,0,527,528,3,76,
  	38,0,528,529,5,3,0,0,529,536,1,0,0,0,530,531,3,120,60,0,531,532,5,2,0,
  	0,532,533,3,76,38,0,533,534,5,3,0,0,534,536,1,0,0,0,535,525,1,0,0,0,535,
  	530,1,0,0,0,536,75,1,0,0,0,537,542,3,56,28,0,538,539,5,7,0,0,539,541,
  	3,56,28,0,540,538,1,0,0,0,541,544,1,0,0,0,542,540,1,0,0,0,542,543,1,0,
  	0,0,543,546,1,0,0,0,544,542,1,0,0,0,545,537,1,0,0,0,545,546,1,0,0,0,546,
  	77,1,0,0,0,547,548,5,94,0,0,548,79,1,0,0,0,549,554,5,55,0,0,550,551,5,
  	34,0,0,551,552,3,56,28,0,552,553,5,35,0,0,553,555,1,0,0,0,554,550,1,0,
  	0,0,554,555,1,0,0,0,555,556,1,0,0,0,556,557,3,82,41,0,557,558,3,120,60,
  	0,558,81,1,0,0,0,559,562,5,56,0,0,560,562,5,57,0,0,561,559,1,0,0,0,561,
  	560,1,0,0,0,562,83,1,0,0,0,563,564,5,58,0,0,564,565,3,56,28,0,565,85,
  	1,0,0,0,566,567,5,59,0,0,567,572,3,56,28,0,568,569,5,59,0,0,569,570,5,
  	60,0,0,570,572,3,56,28,0,571,566,1,0,0,0,571,568,1,0,0,0,572,87,1,0,0,
  	0,573,574,5,61,0,0,574,575,3,120,60,0,575,89,1,0,0,0,576,577,5,61,0,0,
  	577,578,5,2,0,0,578,579,3,56,28,0,579,580,5,3,0,0,580,91,1,0,0,0,581,
  	582,5,28,0,0,582,583,3,56,28,0,583,584,5,29,0,0,584,593,5,4,0,0,585,590,
  	3,94,47,0,586,587,5,7,0,0,587,589,3,94,47,0,588,586,1,0,0,0,589,592,1,
  	0,0,0,590,588,1,0,0,0,590,591,1,0,0,0,591,594,1,0,0,0,592,590,1,0,0,0,
  	593,585,1,0,0,0,593,594,1,0,0,0,594,595,1,0,0,0,595,596,5,5,0,0,596,93,
  	1,0,0,0,597,602,3,96,48,0,598,599,5,30,0,0,599,601,3,96,48,0,600,598,
  	1,0,0,0,601,604,1,0,0,0,602,600,1,0,0,0,602,603,1,0,0,0,603,605,1,0,0,
  	0,604,602,1,0,0,0,605,606,5,31,0,0,606,607,3,56,28,0,607,612,1,0,0,0,
  	608,609,5,32,0,0,609,610,5,31,0,0,610,612,3,56,28,0,611,597,1,0,0,0,611,
  	608,1,0,0,0,612,95,1,0,0,0,613,623,3,98,49,0,614,623,3,100,50,0,615,623,
  	3,102,51,0,616,623,3,108,54,0,617,623,3,110,55,0,618,623,3,112,56,0,619,
  	623,3,114,57,0,620,623,3,116,58,0,621,623,3,118,59,0,622,613,1,0,0,0,
  	622,614,1,0,0,0,622,615,1,0,0,0,622,616,1,0,0,0,622,617,1,0,0,0,622,618,
  	1,0,0,0,622,619,1,0,0,0,622,620,1,0,0,0,622,621,1,0,0,0,623,97,1,0,0,
  	0,624,626,7,0,0,0,625,624,1,0,0,0,625,626,1,0,0,0,626,627,1,0,0,0,627,
  	628,5,88,0,0,628,99,1,0,0,0,629,631,7,0,0,0,630,629,1,0,0,0,630,631,1,
  	0,0,0,631,632,1,0,0,0,632,633,5,89,0,0,633,101,1,0,0,0,634,637,3,104,
  	52,0,635,637,3,106,53,0,636,634,1,0,0,0,636,635,1,0,0,0,637,103,1,0,0,
  	0,638,641,5,90,0,0,639,641,5,79,0,0,640,638,1,0,0,0,640,639,1,0,0,0,641,
  	644,1,0,0,0,642,643,5,1,0,0,643,645,5,90,0,0,644,642,1,0,0,0,644,645,
  	1,0,0,0,645,105,1,0,0,0,646,647,5,80,0,0,647,648,5,1,0,0,648,656,5,90,
  	0,0,649,650,5,81,0,0,650,651,5,1,0,0,651,656,5,90,0,0,652,653,5,82,0,
  	0,653,654,5,1,0,0,654,656,5,90,0,0,655,646,1,0,0,0,655,649,1,0,0,0,655,
  	652,1,0,0,0,656,107,1,0,0,0,657,658,7,1,0,0,658,109,1,0,0,0,659,662,5,
  	62,0,0,660,662,5,63,0,0,661,659,1,0,0,0,661,660,1,0,0,0,662,111,1,0,0,
  	0,663,664,5,64,0,0,664,113,1,0,0,0,665,666,5,90,0,0,666,667,5,1,0,0,667,
  	668,5,65,0,0,668,115,1,0,0,0,669,670,5,79,0,0,670,671,5,1,0,0,671,672,
  	5,66,0,0,672,117,1,0,0,0,673,674,5,80,0,0,674,675,5,1,0,0,675,676,5,67,
  	0,0,676,119,1,0,0,0,677,689,3,122,61,0,678,689,3,124,62,0,679,689,3,126,
  	63,0,680,689,3,128,64,0,681,682,5,42,0,0,682,689,3,120,60,0,683,684,5,
  	91,0,0,684,689,3,120,60,0,685,686,5,68,0,0,686,689,3,120,60,0,687,689,
  	3,142,71,0,688,677,1,0,0,0,688,678,1,0,0,0,688,679,1,0,0,0,688,680,1,
  	0,0,0,688,681,1,0,0,0,688,683,1,0,0,0,688,685,1,0,0,0,688,687,1,0,0,0,
  	689,121,1,0,0,0,690,691,5,78,0,0,691,123,1,0,0,0,692,693,5,34,0,0,693,
  	694,3,120,60,0,694,695,5,95,0,0,695,696,5,90,0,0,696,697,5,35,0,0,697,
  	125,1,0,0,0,698,699,5,38,0,0,699,700,3,120,60,0,700,701,5,95,0,0,701,
  	702,5,90,0,0,702,703,5,39,0,0,703,127,1,0,0,0,704,711,3,130,65,0,705,
  	711,3,132,66,0,706,711,3,134,67,0,707,711,3,136,68,0,708,711,3,138,69,
  	0,709,711,3,140,70,0,710,704,1,0,0,0,710,705,1,0,0,0,710,706,1,0,0,0,
  	710,707,1,0,0,0,710,708,1,0,0,0,710,709,1,0,0,0,711,129,1,0,0,0,712,713,
  	7,2,0,0,713,131,1,0,0,0,714,715,7,3,0,0,715,133,1,0,0,0,716,717,5,74,
  	0,0,717,135,1,0,0,0,718,719,5,75,0,0,719,137,1,0,0,0,720,721,5,76,0,0,
  	721,139,1,0,0,0,722,723,5,77,0,0,723,141,1,0,0,0,724,725,5,94,0,0,725,
  	143,1,0,0,0,63,147,149,156,161,166,177,183,195,199,206,209,217,233,245,
  	251,255,261,279,288,293,316,320,333,347,361,371,380,410,417,426,433,438,
  	466,472,485,487,493,498,502,507,511,517,521,535,542,545,554,561,571,590,
  	593,602,611,622,625,630,636,640,644,655,661,688,710
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

tree::TerminalNode* anceParser::FileContext::EOF() {
  return getToken(anceParser::EOF, 0);
}

std::vector<anceParser::VariableDeclarationContext *> anceParser::FileContext::variableDeclaration() {
  return getRuleContexts<anceParser::VariableDeclarationContext>();
}

anceParser::VariableDeclarationContext* anceParser::FileContext::variableDeclaration(size_t i) {
  return getRuleContext<anceParser::VariableDeclarationContext>(i);
}

std::vector<anceParser::FunctionContext *> anceParser::FileContext::function() {
  return getRuleContexts<anceParser::FunctionContext>();
}

anceParser::FunctionContext* anceParser::FileContext::function(size_t i) {
  return getRuleContext<anceParser::FunctionContext>(i);
}

std::vector<anceParser::TypeDefinitionContext *> anceParser::FileContext::typeDefinition() {
  return getRuleContexts<anceParser::TypeDefinitionContext>();
}

anceParser::TypeDefinitionContext* anceParser::FileContext::typeDefinition(size_t i) {
  return getRuleContext<anceParser::TypeDefinitionContext>(i);
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
    setState(149);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__5)
      | (1ULL << anceParser::T__10)
      | (1ULL << anceParser::T__11))) != 0)) {
      setState(147);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(144);
        variableDeclaration();
        break;
      }

      case 2: {
        setState(145);
        function();
        break;
      }

      case 3: {
        setState(146);
        typeDefinition();
        break;
      }

      default:
        break;
      }
      setState(151);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(152);
    match(anceParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

anceParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AccessModifierContext* anceParser::VariableDeclarationContext::accessModifier() {
  return getRuleContext<anceParser::AccessModifierContext>(0);
}

tree::TerminalNode* anceParser::VariableDeclarationContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::VariableDeclarationContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

tree::TerminalNode* anceParser::VariableDeclarationContext::CONST() {
  return getToken(anceParser::CONST, 0);
}

anceParser::TypeContext* anceParser::VariableDeclarationContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::AssignerContext* anceParser::VariableDeclarationContext::assigner() {
  return getRuleContext<anceParser::AssignerContext>(0);
}

anceParser::ExpressionContext* anceParser::VariableDeclarationContext::expression() {
  return getRuleContext<anceParser::ExpressionContext>(0);
}


size_t anceParser::VariableDeclarationContext::getRuleIndex() const {
  return anceParser::RuleVariableDeclaration;
}


std::any anceParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

anceParser::VariableDeclarationContext* anceParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 2, anceParser::RuleVariableDeclaration);
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
    setState(154);
    accessModifier();
    setState(156);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::CONST) {
      setState(155);
      match(anceParser::CONST);
    }
    setState(158);
    match(anceParser::IDENTIFIER);
    setState(161);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__0) {
      setState(159);
      match(anceParser::T__0);
      setState(160);
      type();
    }
    setState(166);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(163);
      assigner();
      setState(164);
      expression(0);
    }
    setState(168);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

anceParser::FunctionContext::FunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::FunctionContext::getRuleIndex() const {
  return anceParser::RuleFunction;
}

void anceParser::FunctionContext::copyFrom(FunctionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExternFunctionDeclarationContext ------------------------------------------------------------------

tree::TerminalNode* anceParser::ExternFunctionDeclarationContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ParametersContext* anceParser::ExternFunctionDeclarationContext::parameters() {
  return getRuleContext<anceParser::ParametersContext>(0);
}

tree::TerminalNode* anceParser::ExternFunctionDeclarationContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}

anceParser::TypeContext* anceParser::ExternFunctionDeclarationContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

anceParser::ExternFunctionDeclarationContext::ExternFunctionDeclarationContext(FunctionContext *ctx) { copyFrom(ctx); }


std::any anceParser::ExternFunctionDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitExternFunctionDeclaration(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionDefinitionContext ------------------------------------------------------------------

anceParser::AccessModifierContext* anceParser::FunctionDefinitionContext::accessModifier() {
  return getRuleContext<anceParser::AccessModifierContext>(0);
}

tree::TerminalNode* anceParser::FunctionDefinitionContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::ParametersContext* anceParser::FunctionDefinitionContext::parameters() {
  return getRuleContext<anceParser::ParametersContext>(0);
}

anceParser::TypeContext* anceParser::FunctionDefinitionContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

std::vector<anceParser::CodeContext *> anceParser::FunctionDefinitionContext::code() {
  return getRuleContexts<anceParser::CodeContext>();
}

anceParser::CodeContext* anceParser::FunctionDefinitionContext::code(size_t i) {
  return getRuleContext<anceParser::CodeContext>(i);
}

anceParser::FunctionDefinitionContext::FunctionDefinitionContext(FunctionContext *ctx) { copyFrom(ctx); }


std::any anceParser::FunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}
anceParser::FunctionContext* anceParser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 4, anceParser::RuleFunction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(199);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__10:
      case anceParser::T__11: {
        _localctx = _tracker.createInstance<anceParser::FunctionDefinitionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(170);
        accessModifier();
        setState(171);
        match(anceParser::IDENTIFIER);
        setState(172);
        match(anceParser::T__1);
        setState(173);
        parameters();
        setState(174);
        match(anceParser::T__2);
        setState(177);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::T__0) {
          setState(175);
          match(anceParser::T__0);
          setState(176);
          type();
        }
        setState(179);
        match(anceParser::T__3);
        setState(183);
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
          | (1ULL << anceParser::T__33)
          | (1ULL << anceParser::T__37)
          | (1ULL << anceParser::T__39)
          | (1ULL << anceParser::T__40)
          | (1ULL << anceParser::T__41)
          | (1ULL << anceParser::T__54)
          | (1ULL << anceParser::T__57)
          | (1ULL << anceParser::T__58)
          | (1ULL << anceParser::T__60)
          | (1ULL << anceParser::T__61)
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
          setState(180);
          code();
          setState(185);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(186);
        match(anceParser::T__4);
        break;
      }

      case anceParser::T__5: {
        _localctx = _tracker.createInstance<anceParser::ExternFunctionDeclarationContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(188);
        match(anceParser::T__5);
        setState(189);
        match(anceParser::IDENTIFIER);
        setState(190);
        match(anceParser::T__1);
        setState(191);
        parameters();
        setState(192);
        match(anceParser::T__2);
        setState(195);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == anceParser::T__0) {
          setState(193);
          match(anceParser::T__0);
          setState(194);
          type();
        }
        setState(197);
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
  enterRule(_localctx, 6, anceParser::RuleParameters);
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
    setState(209);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::IDENTIFIER) {
      setState(201);
      parameter();
      setState(206);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__6) {
        setState(202);
        match(anceParser::T__6);
        setState(203);
        parameter();
        setState(208);
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
  enterRule(_localctx, 8, anceParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(211);
    match(anceParser::IDENTIFIER);
    setState(212);
    match(anceParser::T__0);
    setState(213);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeDefinitionContext ------------------------------------------------------------------

anceParser::TypeDefinitionContext::TypeDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::DefineAliasContext* anceParser::TypeDefinitionContext::defineAlias() {
  return getRuleContext<anceParser::DefineAliasContext>(0);
}

anceParser::StructDefinitionContext* anceParser::TypeDefinitionContext::structDefinition() {
  return getRuleContext<anceParser::StructDefinitionContext>(0);
}


size_t anceParser::TypeDefinitionContext::getRuleIndex() const {
  return anceParser::RuleTypeDefinition;
}


std::any anceParser::TypeDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitTypeDefinition(this);
  else
    return visitor->visitChildren(this);
}

anceParser::TypeDefinitionContext* anceParser::typeDefinition() {
  TypeDefinitionContext *_localctx = _tracker.createInstance<TypeDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 10, anceParser::RuleTypeDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(217);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(215);
      defineAlias();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(216);
      structDefinition();
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

//----------------- DefineAliasContext ------------------------------------------------------------------

anceParser::DefineAliasContext::DefineAliasContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AccessModifierContext* anceParser::DefineAliasContext::accessModifier() {
  return getRuleContext<anceParser::AccessModifierContext>(0);
}

tree::TerminalNode* anceParser::DefineAliasContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

anceParser::TypeContext* anceParser::DefineAliasContext::type() {
  return getRuleContext<anceParser::TypeContext>(0);
}

tree::TerminalNode* anceParser::DefineAliasContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}


size_t anceParser::DefineAliasContext::getRuleIndex() const {
  return anceParser::RuleDefineAlias;
}


std::any anceParser::DefineAliasContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitDefineAlias(this);
  else
    return visitor->visitChildren(this);
}

anceParser::DefineAliasContext* anceParser::defineAlias() {
  DefineAliasContext *_localctx = _tracker.createInstance<DefineAliasContext>(_ctx, getState());
  enterRule(_localctx, 12, anceParser::RuleDefineAlias);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(219);
    accessModifier();
    setState(220);
    match(anceParser::T__7);
    setState(221);
    match(anceParser::IDENTIFIER);
    setState(222);
    match(anceParser::T__8);
    setState(223);
    type();
    setState(224);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDefinitionContext ------------------------------------------------------------------

anceParser::StructDefinitionContext::StructDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

anceParser::AccessModifierContext* anceParser::StructDefinitionContext::accessModifier() {
  return getRuleContext<anceParser::AccessModifierContext>(0);
}

tree::TerminalNode* anceParser::StructDefinitionContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

std::vector<anceParser::MemberContext *> anceParser::StructDefinitionContext::member() {
  return getRuleContexts<anceParser::MemberContext>();
}

anceParser::MemberContext* anceParser::StructDefinitionContext::member(size_t i) {
  return getRuleContext<anceParser::MemberContext>(i);
}


size_t anceParser::StructDefinitionContext::getRuleIndex() const {
  return anceParser::RuleStructDefinition;
}


std::any anceParser::StructDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitStructDefinition(this);
  else
    return visitor->visitChildren(this);
}

anceParser::StructDefinitionContext* anceParser::structDefinition() {
  StructDefinitionContext *_localctx = _tracker.createInstance<StructDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 14, anceParser::RuleStructDefinition);
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
    setState(226);
    accessModifier();
    setState(227);
    match(anceParser::T__9);
    setState(228);
    match(anceParser::IDENTIFIER);
    setState(229);
    match(anceParser::T__3);
    setState(233);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == anceParser::T__10

    || _la == anceParser::T__11) {
      setState(230);
      member();
      setState(235);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(236);
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
  enterRule(_localctx, 16, anceParser::RuleMember);
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
    setState(238);
    accessModifier();
    setState(239);
    match(anceParser::IDENTIFIER);
    setState(240);
    match(anceParser::T__0);
    setState(241);
    type();
    setState(245);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(242);
      assigner();
      setState(243);
      literalExpression();
    }
    setState(247);
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
anceParser::AccessModifierContext* anceParser::accessModifier() {
  AccessModifierContext *_localctx = _tracker.createInstance<AccessModifierContext>(_ctx, getState());
  enterRule(_localctx, 18, anceParser::RuleAccessModifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(251);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__10: {
        _localctx = _tracker.createInstance<anceParser::PublicContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(249);
        match(anceParser::T__10);
        break;
      }

      case anceParser::T__11: {
        _localctx = _tracker.createInstance<anceParser::PrivateContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(250);
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
  enterRule(_localctx, 20, anceParser::RuleCode);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(255);
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
      case anceParser::T__33:
      case anceParser::T__37:
      case anceParser::T__39:
      case anceParser::T__40:
      case anceParser::T__41:
      case anceParser::T__54:
      case anceParser::T__57:
      case anceParser::T__58:
      case anceParser::T__60:
      case anceParser::T__61:
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
        setState(253);
        statement();
        break;
      }

      case anceParser::T__3: {
        enterOuterAlt(_localctx, 2);
        setState(254);
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
  enterRule(_localctx, 22, anceParser::RuleBlock);
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
    setState(257);
    match(anceParser::T__3);
    setState(261);
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
      | (1ULL << anceParser::T__33)
      | (1ULL << anceParser::T__37)
      | (1ULL << anceParser::T__39)
      | (1ULL << anceParser::T__40)
      | (1ULL << anceParser::T__41)
      | (1ULL << anceParser::T__54)
      | (1ULL << anceParser::T__57)
      | (1ULL << anceParser::T__58)
      | (1ULL << anceParser::T__60)
      | (1ULL << anceParser::T__61)
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
      setState(258);
      code();
      setState(263);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(264);
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

anceParser::LocalVariableDefinitionContext* anceParser::StatementContext::localVariableDefinition() {
  return getRuleContext<anceParser::LocalVariableDefinitionContext>(0);
}

anceParser::LocalReferenceDefinitionContext* anceParser::StatementContext::localReferenceDefinition() {
  return getRuleContext<anceParser::LocalReferenceDefinitionContext>(0);
}

anceParser::DropStatementContext* anceParser::StatementContext::dropStatement() {
  return getRuleContext<anceParser::DropStatementContext>(0);
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

anceParser::IfStatementContext* anceParser::StatementContext::ifStatement() {
  return getRuleContext<anceParser::IfStatementContext>(0);
}

anceParser::WhileStatementContext* anceParser::StatementContext::whileStatement() {
  return getRuleContext<anceParser::WhileStatementContext>(0);
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
  enterRule(_localctx, 24, anceParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(279);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(266);
      expressionStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(267);
      localVariableDefinition();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(268);
      localReferenceDefinition();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(269);
      dropStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(270);
      assignment();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(271);
      deleteStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(272);
      breakStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(273);
      continueStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(274);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(275);
      assertStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(276);
      ifStatement();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(277);
      whileStatement();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(278);
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
  enterRule(_localctx, 26, anceParser::RuleExpressionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(281);
    independentExpression();
    setState(282);
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
  enterRule(_localctx, 28, anceParser::RuleLocalVariableDefinition);
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
    setState(284);
    match(anceParser::T__12);
    setState(285);
    match(anceParser::IDENTIFIER);
    setState(288);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__0) {
      setState(286);
      match(anceParser::T__0);
      setState(287);
      type();
    }
    setState(293);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(290);
      assigner();
      setState(291);
      expression(0);
    }
    setState(295);
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
  enterRule(_localctx, 30, anceParser::RuleLocalReferenceDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(297);
    match(anceParser::T__12);
    setState(298);
    match(anceParser::IDENTIFIER);
    setState(299);
    match(anceParser::T__0);
    setState(300);
    type();
    setState(301);
    bindRef();
    setState(302);
    match(anceParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DropStatementContext ------------------------------------------------------------------

anceParser::DropStatementContext::DropStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* anceParser::DropStatementContext::IDENTIFIER() {
  return getToken(anceParser::IDENTIFIER, 0);
}

tree::TerminalNode* anceParser::DropStatementContext::SEMICOLON() {
  return getToken(anceParser::SEMICOLON, 0);
}


size_t anceParser::DropStatementContext::getRuleIndex() const {
  return anceParser::RuleDropStatement;
}


std::any anceParser::DropStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitDropStatement(this);
  else
    return visitor->visitChildren(this);
}

anceParser::DropStatementContext* anceParser::dropStatement() {
  DropStatementContext *_localctx = _tracker.createInstance<DropStatementContext>(_ctx, getState());
  enterRule(_localctx, 32, anceParser::RuleDropStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(304);
    match(anceParser::T__13);
    setState(305);
    match(anceParser::IDENTIFIER);
    setState(306);
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
  enterRule(_localctx, 34, anceParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(308);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->assignable = expression(0);
    setState(309);
    assigner();
    setState(310);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->assigned = expression(0);
    setState(311);
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
  enterRule(_localctx, 36, anceParser::RuleAssigner);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(316);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__14: {
        _localctx = _tracker.createInstance<anceParser::CopyAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(313);
        match(anceParser::T__14);
        break;
      }

      case anceParser::T__15: {
        _localctx = _tracker.createInstance<anceParser::MoveAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(314);
        match(anceParser::T__15);
        break;
      }

      case anceParser::T__16: {
        _localctx = _tracker.createInstance<anceParser::FinalCopyAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(315);
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
  enterRule(_localctx, 38, anceParser::RuleDeleteStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(318);
    match(anceParser::T__17);
    setState(320);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      setState(319);
      match(anceParser::BUFFER);
      break;
    }

    default:
      break;
    }
    setState(322);
    expression(0);
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
  enterRule(_localctx, 40, anceParser::RuleBreakStatement);

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
    match(anceParser::T__18);
    setState(326);
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
  enterRule(_localctx, 42, anceParser::RuleContinueStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(328);
    match(anceParser::T__19);
    setState(329);
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
  enterRule(_localctx, 44, anceParser::RuleReturnStatement);
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
    setState(331);
    match(anceParser::T__20);
    setState(333);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__1)
      | (1ULL << anceParser::T__22)
      | (1ULL << anceParser::T__27)
      | (1ULL << anceParser::T__33)
      | (1ULL << anceParser::T__37)
      | (1ULL << anceParser::T__39)
      | (1ULL << anceParser::T__40)
      | (1ULL << anceParser::T__41)
      | (1ULL << anceParser::T__54)
      | (1ULL << anceParser::T__57)
      | (1ULL << anceParser::T__58)
      | (1ULL << anceParser::T__60)
      | (1ULL << anceParser::T__61)
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
      setState(332);
      expression(0);
    }
    setState(335);
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
  enterRule(_localctx, 46, anceParser::RuleAssertStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(337);
    match(anceParser::T__21);
    setState(338);
    expression(0);
    setState(339);
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
  enterRule(_localctx, 48, anceParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(341);
    match(anceParser::T__22);
    setState(342);
    expression(0);
    setState(343);
    match(anceParser::T__23);
    setState(344);
    antlrcpp::downCast<IfStatementContext *>(_localctx)->ifBlock = code();
    setState(347);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(345);
      match(anceParser::T__24);
      setState(346);
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
  enterRule(_localctx, 50, anceParser::RuleWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(349);
    match(anceParser::T__25);
    setState(350);
    expression(0);
    setState(351);
    match(anceParser::T__26);
    setState(352);
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
  enterRule(_localctx, 52, anceParser::RuleMatchStatement);
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
    setState(354);
    match(anceParser::T__27);
    setState(355);
    expression(0);
    setState(356);
    match(anceParser::T__28);
    setState(357);
    match(anceParser::T__3);
    setState(361);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 32) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 32)) & ((1ULL << (anceParser::T__31 - 32))
      | (1ULL << (anceParser::T__61 - 32))
      | (1ULL << (anceParser::T__62 - 32))
      | (1ULL << (anceParser::T__63 - 32))
      | (1ULL << (anceParser::SIGNED_INTEGER - 32))
      | (1ULL << (anceParser::HEX_INTEGER - 32))
      | (1ULL << (anceParser::BIN_INTEGER - 32))
      | (1ULL << (anceParser::OCT_INTEGER - 32))
      | (1ULL << (anceParser::HALF - 32))
      | (1ULL << (anceParser::SINGLE - 32))
      | (1ULL << (anceParser::DOUBLE - 32))
      | (1ULL << (anceParser::QUAD - 32))
      | (1ULL << (anceParser::STRING - 32))
      | (1ULL << (anceParser::CHAR - 32))
      | (1ULL << (anceParser::INTEGER - 32))
      | (1ULL << (anceParser::IDENTIFIER - 32)))) != 0)) {
      setState(358);
      matchCase();
      setState(363);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(364);
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
  enterRule(_localctx, 54, anceParser::RuleMatchCase);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(380);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__61:
      case anceParser::T__62:
      case anceParser::T__63:
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
        setState(366);
        literalExpression();
        setState(371);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__29) {
          setState(367);
          match(anceParser::T__29);
          setState(368);
          literalExpression();
          setState(373);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(374);
        match(anceParser::T__30);
        setState(375);
        code();
        break;
      }

      case anceParser::T__31: {
        _localctx = _tracker.createInstance<anceParser::DefaultCaseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(377);
        match(anceParser::T__31);
        setState(378);
        match(anceParser::T__30);
        setState(379);
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
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, anceParser::RuleExpression, precedence);

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
    setState(438);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<VariableContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(383);
      variableAccess();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<AllocContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(384);
      allocation();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<LiteralContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(385);
      literalExpression();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<AddressOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(386);
      addressof();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<RefContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(387);
      bindRef();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SizeOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(388);
      sizeofType();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SizeOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(389);
      sizeofExpression();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<IndependentContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(390);
      independentExpression();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ParenthesisContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(391);
      match(anceParser::T__1);
      setState(392);
      expression(0);
      setState(393);
      match(anceParser::T__2);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<UnaryOperationContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(395);
      unaryOperator();
      setState(396);
      expression(13);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<IfExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(398);
      match(anceParser::T__22);
      setState(399);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->condition = expression(0);
      setState(400);
      match(anceParser::T__23);
      setState(401);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->thenBlock = expression(0);
      setState(402);
      match(anceParser::T__24);
      setState(403);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->elseBlock = expression(4);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<MatchContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(405);
      matchExpression();
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<VectorDefinitionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(406);
      match(anceParser::T__37);
      setState(410);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
      case 1: {
        setState(407);
        type();
        setState(408);
        match(anceParser::T__29);
        break;
      }

      default:
        break;
      }
      setState(412);
      expression(0);
      setState(417);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__6) {
        setState(413);
        match(anceParser::T__6);
        setState(414);
        expression(0);
        setState(419);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(420);
      match(anceParser::T__38);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<ArrayDefinitionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(422);
      match(anceParser::T__33);
      setState(426);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
      case 1: {
        setState(423);
        type();
        setState(424);
        match(anceParser::T__29);
        break;
      }

      default:
        break;
      }
      setState(428);
      expression(0);
      setState(433);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__6) {
        setState(429);
        match(anceParser::T__6);
        setState(430);
        expression(0);
        setState(435);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(436);
      match(anceParser::T__34);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(487);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(485);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(440);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(441);
          binaryOperatorMultiplicative();
          setState(442);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(13);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(444);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(445);
          binaryOperatorAdditive();
          setState(446);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(12);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(448);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(449);
          binaryOperatorBitwise();
          setState(450);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(11);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(452);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(453);
          binaryOperatorShift();
          setState(454);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(10);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(456);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(457);
          binaryOperatorRelational();
          setState(458);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(9);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(460);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(461);
          binaryOperatorEquality();
          setState(462);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(8);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<LogicalAndContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(464);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(466);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == anceParser::NOT) {
            setState(465);
            match(anceParser::NOT);
          }
          setState(468);
          match(anceParser::T__35);
          setState(469);
          antlrcpp::downCast<LogicalAndContext *>(_localctx)->right = expression(7);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<LogicalOrContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(470);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(472);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == anceParser::NOT) {
            setState(471);
            match(anceParser::NOT);
          }
          setState(474);
          match(anceParser::T__36);
          setState(475);
          antlrcpp::downCast<LogicalOrContext *>(_localctx)->right = expression(6);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<IndirectionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(476);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(477);
          match(anceParser::T__32);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<SubscriptContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->indexed = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(478);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(479);
          match(anceParser::T__33);
          setState(480);
          antlrcpp::downCast<SubscriptContext *>(_localctx)->index = expression(0);
          setState(481);
          match(anceParser::T__34);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->accessed = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(483);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(484);
          match(anceParser::IDENTIFIER);
          break;
        }

        default:
          break;
        } 
      }
      setState(489);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
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
  enterRule(_localctx, 58, anceParser::RuleUnaryOperator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(493);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::NOT: {
        _localctx = _tracker.createInstance<anceParser::NotContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(490);
        match(anceParser::NOT);
        break;
      }

      case anceParser::T__39: {
        _localctx = _tracker.createInstance<anceParser::BitwiseNotContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(491);
        match(anceParser::T__39);
        break;
      }

      case anceParser::T__40: {
        _localctx = _tracker.createInstance<anceParser::NegationContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(492);
        match(anceParser::T__40);
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
  enterRule(_localctx, 60, anceParser::RuleBinaryOperatorMultiplicative);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(498);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__41: {
        _localctx = _tracker.createInstance<anceParser::MultiplicationContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(495);
        match(anceParser::T__41);
        break;
      }

      case anceParser::T__42: {
        _localctx = _tracker.createInstance<anceParser::DivisionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(496);
        match(anceParser::T__42);
        break;
      }

      case anceParser::T__43: {
        _localctx = _tracker.createInstance<anceParser::RemainderContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(497);
        match(anceParser::T__43);
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
  enterRule(_localctx, 62, anceParser::RuleBinaryOperatorAdditive);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(502);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__44: {
        _localctx = _tracker.createInstance<anceParser::AdditionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(500);
        match(anceParser::T__44);
        break;
      }

      case anceParser::T__40: {
        _localctx = _tracker.createInstance<anceParser::SubtractionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(501);
        match(anceParser::T__40);
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
  enterRule(_localctx, 64, anceParser::RuleBinaryOperatorBitwise);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(507);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__45: {
        _localctx = _tracker.createInstance<anceParser::BitwiseAndContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(504);
        match(anceParser::T__45);
        break;
      }

      case anceParser::T__46: {
        _localctx = _tracker.createInstance<anceParser::BitwiseOrContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(505);
        match(anceParser::T__46);
        break;
      }

      case anceParser::T__47: {
        _localctx = _tracker.createInstance<anceParser::BitwiseXorContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(506);
        match(anceParser::T__47);
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
  enterRule(_localctx, 66, anceParser::RuleBinaryOperatorShift);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(511);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__48: {
        _localctx = _tracker.createInstance<anceParser::LeftShiftContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(509);
        match(anceParser::T__48);
        break;
      }

      case anceParser::T__49: {
        _localctx = _tracker.createInstance<anceParser::RightShiftContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(510);
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
  enterRule(_localctx, 68, anceParser::RuleBinaryOperatorRelational);

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
      case anceParser::T__37: {
        _localctx = _tracker.createInstance<anceParser::LessThanContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(513);
        match(anceParser::T__37);
        break;
      }

      case anceParser::T__50: {
        _localctx = _tracker.createInstance<anceParser::LessThanOrEqualContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(514);
        match(anceParser::T__50);
        break;
      }

      case anceParser::T__38: {
        _localctx = _tracker.createInstance<anceParser::GreaterThanContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(515);
        match(anceParser::T__38);
        break;
      }

      case anceParser::T__51: {
        _localctx = _tracker.createInstance<anceParser::GreaterThanOrEqualContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(516);
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
  enterRule(_localctx, 70, anceParser::RuleBinaryOperatorEquality);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(521);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__52: {
        _localctx = _tracker.createInstance<anceParser::EqualContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(519);
        match(anceParser::T__52);
        break;
      }

      case anceParser::T__53: {
        _localctx = _tracker.createInstance<anceParser::NotEqualContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(520);
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
  enterRule(_localctx, 72, anceParser::RuleIndependentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(523);
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
  enterRule(_localctx, 74, anceParser::RuleFunctionCall);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(525);
      match(anceParser::IDENTIFIER);
      setState(526);
      match(anceParser::T__1);
      setState(527);
      arguments();
      setState(528);
      match(anceParser::T__2);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(530);
      type();
      setState(531);
      match(anceParser::T__1);
      setState(532);
      arguments();
      setState(533);
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
  enterRule(_localctx, 76, anceParser::RuleArguments);
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
    setState(545);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__1)
      | (1ULL << anceParser::T__22)
      | (1ULL << anceParser::T__27)
      | (1ULL << anceParser::T__33)
      | (1ULL << anceParser::T__37)
      | (1ULL << anceParser::T__39)
      | (1ULL << anceParser::T__40)
      | (1ULL << anceParser::T__41)
      | (1ULL << anceParser::T__54)
      | (1ULL << anceParser::T__57)
      | (1ULL << anceParser::T__58)
      | (1ULL << anceParser::T__60)
      | (1ULL << anceParser::T__61)
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
      setState(537);
      expression(0);
      setState(542);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__6) {
        setState(538);
        match(anceParser::T__6);
        setState(539);
        expression(0);
        setState(544);
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
  enterRule(_localctx, 78, anceParser::RuleVariableAccess);

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
  enterRule(_localctx, 80, anceParser::RuleAllocation);
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
    setState(549);
    match(anceParser::T__54);
    setState(554);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__33) {
      setState(550);
      match(anceParser::T__33);
      setState(551);
      expression(0);
      setState(552);
      match(anceParser::T__34);
    }
    setState(556);
    allocator();
    setState(557);
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
  enterRule(_localctx, 82, anceParser::RuleAllocator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(561);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__55: {
        _localctx = _tracker.createInstance<anceParser::DynamicContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(559);
        match(anceParser::T__55);
        break;
      }

      case anceParser::T__56: {
        _localctx = _tracker.createInstance<anceParser::AutomaticContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(560);
        match(anceParser::T__56);
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
  enterRule(_localctx, 84, anceParser::RuleAddressof);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(563);
    match(anceParser::T__57);
    setState(564);
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
  enterRule(_localctx, 86, anceParser::RuleBindRef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(571);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::BindReferenceContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(566);
      match(anceParser::T__58);
      setState(567);
      expression(0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::BindReferenceToAddressContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(568);
      match(anceParser::T__58);
      setState(569);
      match(anceParser::T__59);
      setState(570);
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
  enterRule(_localctx, 88, anceParser::RuleSizeofType);

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
    match(anceParser::T__60);
    setState(574);
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
  enterRule(_localctx, 90, anceParser::RuleSizeofExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(576);
    match(anceParser::T__60);
    setState(577);
    match(anceParser::T__1);
    setState(578);
    expression(0);
    setState(579);
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
  enterRule(_localctx, 92, anceParser::RuleMatchExpression);
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
    setState(581);
    match(anceParser::T__27);
    setState(582);
    antlrcpp::downCast<MatchExpressionContext *>(_localctx)->condition = expression(0);
    setState(583);
    match(anceParser::T__28);
    setState(584);
    match(anceParser::T__3);
    setState(593);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 32) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 32)) & ((1ULL << (anceParser::T__31 - 32))
      | (1ULL << (anceParser::T__61 - 32))
      | (1ULL << (anceParser::T__62 - 32))
      | (1ULL << (anceParser::T__63 - 32))
      | (1ULL << (anceParser::SIGNED_INTEGER - 32))
      | (1ULL << (anceParser::HEX_INTEGER - 32))
      | (1ULL << (anceParser::BIN_INTEGER - 32))
      | (1ULL << (anceParser::OCT_INTEGER - 32))
      | (1ULL << (anceParser::HALF - 32))
      | (1ULL << (anceParser::SINGLE - 32))
      | (1ULL << (anceParser::DOUBLE - 32))
      | (1ULL << (anceParser::QUAD - 32))
      | (1ULL << (anceParser::STRING - 32))
      | (1ULL << (anceParser::CHAR - 32))
      | (1ULL << (anceParser::INTEGER - 32))
      | (1ULL << (anceParser::IDENTIFIER - 32)))) != 0)) {
      setState(585);
      matchExpressionCase();
      setState(590);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__6) {
        setState(586);
        match(anceParser::T__6);
        setState(587);
        matchExpressionCase();
        setState(592);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(595);
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
  enterRule(_localctx, 94, anceParser::RuleMatchExpressionCase);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(611);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__61:
      case anceParser::T__62:
      case anceParser::T__63:
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
        setState(597);
        literalExpression();
        setState(602);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__29) {
          setState(598);
          match(anceParser::T__29);
          setState(599);
          literalExpression();
          setState(604);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(605);
        match(anceParser::T__30);
        setState(606);
        expression(0);
        break;
      }

      case anceParser::T__31: {
        _localctx = _tracker.createInstance<anceParser::DefaultExpressionCaseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(608);
        match(anceParser::T__31);
        setState(609);
        match(anceParser::T__30);
        setState(610);
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
  enterRule(_localctx, 96, anceParser::RuleLiteralExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(622);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(613);
      stringLiteral();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(614);
      charLiteral();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(615);
      integerLiteral();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(616);
      floatingPointLiteral();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(617);
      booleanLiteral();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(618);
      nullLiteral();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(619);
      sizeLiteral();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(620);
      diffLiteral();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(621);
      uiptrLiteral();
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
  enterRule(_localctx, 98, anceParser::RuleStringLiteral);
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
    setState(625);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER

    || _la == anceParser::IDENTIFIER) {
      setState(624);
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
    setState(627);
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
  enterRule(_localctx, 100, anceParser::RuleCharLiteral);
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
    setState(630);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER

    || _la == anceParser::IDENTIFIER) {
      setState(629);
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
    setState(632);
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
  enterRule(_localctx, 102, anceParser::RuleIntegerLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(636);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::SIGNED_INTEGER:
      case anceParser::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(634);
        normalInteger();
        break;
      }

      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(635);
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
  enterRule(_localctx, 104, anceParser::RuleNormalInteger);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(640);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::INTEGER: {
        setState(638);
        antlrcpp::downCast<NormalIntegerContext *>(_localctx)->uvalue = match(anceParser::INTEGER);
        break;
      }

      case anceParser::SIGNED_INTEGER: {
        setState(639);
        antlrcpp::downCast<NormalIntegerContext *>(_localctx)->svalue = match(anceParser::SIGNED_INTEGER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(644);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      setState(642);
      match(anceParser::T__0);
      setState(643);
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
  enterRule(_localctx, 106, anceParser::RuleSpecialInteger);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(655);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::HEX_INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(646);
        match(anceParser::HEX_INTEGER);
        setState(647);
        match(anceParser::T__0);
        setState(648);
        antlrcpp::downCast<SpecialIntegerContext *>(_localctx)->width = match(anceParser::INTEGER);
        break;
      }

      case anceParser::BIN_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(649);
        match(anceParser::BIN_INTEGER);
        setState(650);
        match(anceParser::T__0);
        setState(651);
        antlrcpp::downCast<SpecialIntegerContext *>(_localctx)->width = match(anceParser::INTEGER);
        break;
      }

      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(652);
        match(anceParser::OCT_INTEGER);
        setState(653);
        match(anceParser::T__0);
        setState(654);
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
  enterRule(_localctx, 108, anceParser::RuleFloatingPointLiteral);
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
    setState(657);
    _la = _input->LA(1);
    if (!(((((_la - 83) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 83)) & ((1ULL << (anceParser::HALF - 83))
      | (1ULL << (anceParser::SINGLE - 83))
      | (1ULL << (anceParser::DOUBLE - 83))
      | (1ULL << (anceParser::QUAD - 83)))) != 0))) {
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
  enterRule(_localctx, 110, anceParser::RuleBooleanLiteral);

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
      case anceParser::T__61: {
        _localctx = _tracker.createInstance<anceParser::TrueContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(659);
        match(anceParser::T__61);
        break;
      }

      case anceParser::T__62: {
        _localctx = _tracker.createInstance<anceParser::FalseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(660);
        match(anceParser::T__62);
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
  enterRule(_localctx, 112, anceParser::RuleNullLiteral);

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
    setState(663);
    match(anceParser::T__63);
   
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
  enterRule(_localctx, 114, anceParser::RuleSizeLiteral);

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
    match(anceParser::INTEGER);
    setState(666);
    match(anceParser::T__0);
    setState(667);
    match(anceParser::T__64);
   
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
  enterRule(_localctx, 116, anceParser::RuleDiffLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(669);
    match(anceParser::SIGNED_INTEGER);
    setState(670);
    match(anceParser::T__0);
    setState(671);
    match(anceParser::T__65);
   
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
  enterRule(_localctx, 118, anceParser::RuleUiptrLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(673);
    match(anceParser::HEX_INTEGER);
    setState(674);
    match(anceParser::T__0);
    setState(675);
    match(anceParser::T__66);
   
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
  enterRule(_localctx, 120, anceParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(688);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::NATIVE_INTEGER_TYPE: {
        _localctx = _tracker.createInstance<anceParser::IntegerContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(677);
        integerType();
        break;
      }

      case anceParser::T__33: {
        _localctx = _tracker.createInstance<anceParser::ArrayContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(678);
        arrayType();
        break;
      }

      case anceParser::T__37: {
        _localctx = _tracker.createInstance<anceParser::VectorContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(679);
        vectorType();
        break;
      }

      case anceParser::T__64:
      case anceParser::T__65:
      case anceParser::T__66:
      case anceParser::T__68:
      case anceParser::T__69:
      case anceParser::T__70:
      case anceParser::T__71:
      case anceParser::T__72:
      case anceParser::T__73:
      case anceParser::T__74:
      case anceParser::T__75:
      case anceParser::T__76: {
        _localctx = _tracker.createInstance<anceParser::KeywordContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(680);
        keywordType();
        break;
      }

      case anceParser::T__41: {
        _localctx = _tracker.createInstance<anceParser::PointerContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(681);
        match(anceParser::T__41);
        setState(682);
        type();
        break;
      }

      case anceParser::BUFFER: {
        _localctx = _tracker.createInstance<anceParser::BufferContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(683);
        match(anceParser::BUFFER);
        setState(684);
        type();
        break;
      }

      case anceParser::T__67: {
        _localctx = _tracker.createInstance<anceParser::ReferenceContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(685);
        match(anceParser::T__67);
        setState(686);
        type();
        break;
      }

      case anceParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<anceParser::CustomContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(687);
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
  enterRule(_localctx, 122, anceParser::RuleIntegerType);

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
  enterRule(_localctx, 124, anceParser::RuleArrayType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(692);
    match(anceParser::T__33);
    setState(693);
    type();
    setState(694);
    match(anceParser::SEMICOLON);
    setState(695);
    match(anceParser::INTEGER);
    setState(696);
    match(anceParser::T__34);
   
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
  enterRule(_localctx, 126, anceParser::RuleVectorType);

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
    match(anceParser::T__37);
    setState(699);
    type();
    setState(700);
    match(anceParser::SEMICOLON);
    setState(701);
    match(anceParser::INTEGER);
    setState(702);
    match(anceParser::T__38);
   
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

anceParser::VoidTypeContext* anceParser::KeywordTypeContext::voidType() {
  return getRuleContext<anceParser::VoidTypeContext>(0);
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
  enterRule(_localctx, 128, anceParser::RuleKeywordType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(710);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__68:
      case anceParser::T__69:
      case anceParser::T__70:
      case anceParser::T__71: {
        enterOuterAlt(_localctx, 1);
        setState(704);
        floatingPointType();
        break;
      }

      case anceParser::T__64:
      case anceParser::T__65:
      case anceParser::T__66:
      case anceParser::T__72: {
        enterOuterAlt(_localctx, 2);
        setState(705);
        targetDependentType();
        break;
      }

      case anceParser::T__73: {
        enterOuterAlt(_localctx, 3);
        setState(706);
        booleanType();
        break;
      }

      case anceParser::T__74: {
        enterOuterAlt(_localctx, 4);
        setState(707);
        charType();
        break;
      }

      case anceParser::T__75: {
        enterOuterAlt(_localctx, 5);
        setState(708);
        nullPointerType();
        break;
      }

      case anceParser::T__76: {
        enterOuterAlt(_localctx, 6);
        setState(709);
        voidType();
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
  enterRule(_localctx, 130, anceParser::RuleFloatingPointType);
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
    setState(712);
    _la = _input->LA(1);
    if (!(((((_la - 69) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 69)) & ((1ULL << (anceParser::T__68 - 69))
      | (1ULL << (anceParser::T__69 - 69))
      | (1ULL << (anceParser::T__70 - 69))
      | (1ULL << (anceParser::T__71 - 69)))) != 0))) {
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
  enterRule(_localctx, 132, anceParser::RuleTargetDependentType);
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
    setState(714);
    _la = _input->LA(1);
    if (!(((((_la - 65) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 65)) & ((1ULL << (anceParser::T__64 - 65))
      | (1ULL << (anceParser::T__65 - 65))
      | (1ULL << (anceParser::T__66 - 65))
      | (1ULL << (anceParser::T__72 - 65)))) != 0))) {
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
  enterRule(_localctx, 134, anceParser::RuleBooleanType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(716);
    match(anceParser::T__73);
   
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
  enterRule(_localctx, 136, anceParser::RuleCharType);

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
    match(anceParser::T__74);
   
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
  enterRule(_localctx, 138, anceParser::RuleNullPointerType);

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
    match(anceParser::T__75);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VoidTypeContext ------------------------------------------------------------------

anceParser::VoidTypeContext::VoidTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t anceParser::VoidTypeContext::getRuleIndex() const {
  return anceParser::RuleVoidType;
}


std::any anceParser::VoidTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<anceVisitor*>(visitor))
    return parserVisitor->visitVoidType(this);
  else
    return visitor->visitChildren(this);
}

anceParser::VoidTypeContext* anceParser::voidType() {
  VoidTypeContext *_localctx = _tracker.createInstance<VoidTypeContext>(_ctx, getState());
  enterRule(_localctx, 140, anceParser::RuleVoidType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(722);
    match(anceParser::T__76);
   
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
  enterRule(_localctx, 142, anceParser::RuleCustomType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(724);
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
    case 28: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

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
    case 8: return precpred(_ctx, 22);
    case 9: return precpred(_ctx, 21);
    case 10: return precpred(_ctx, 20);

  default:
    break;
  }
  return true;
}

void anceParser::initialize() {
  std::call_once(anceParserOnceFlag, anceParserInitialize);
}
