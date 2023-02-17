
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
      "localVariableDefinition", "localReferenceDefinition", "dropStatement", 
      "assignment", "assigner", "deleteStatement", "breakStatement", "continueStatement", 
      "returnStatement", "assertStatement", "ifStatement", "whileStatement", 
      "matchStatement", "matchCase", "expression", "unaryOperator", "binaryOperatorMultiplicative", 
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
      "", "':'", "'('", "')'", "'{'", "'}'", "','", "'define'", "'alias'", 
      "'struct'", "'public'", "'private'", "'extern'", "'let'", "'drop'", 
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
      "NOT", "IDENTIFIER", "SEMICOLON", "WHITESPACE", "BLOCK_COMMENT", "LINE_COMMENT", 
      "ERROR_CHAR"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,99,739,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,7,
  	70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,1,0,1,0,1,0,1,1,
  	5,1,157,8,1,10,1,12,1,160,9,1,1,1,1,1,1,2,5,2,165,8,2,10,2,12,2,168,9,
  	2,1,3,1,3,1,3,3,3,173,8,3,1,4,1,4,3,4,177,8,4,1,4,1,4,1,4,3,4,182,8,4,
  	1,4,1,4,1,4,3,4,187,8,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,198,8,
  	5,1,5,1,5,3,5,202,8,5,1,6,1,6,5,6,206,8,6,10,6,12,6,209,9,6,1,6,1,6,1,
  	7,1,7,1,7,5,7,216,8,7,10,7,12,7,219,9,7,3,7,221,8,7,1,8,1,8,1,8,1,8,1,
  	9,1,9,3,9,229,8,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,
  	11,1,11,5,11,243,8,11,10,11,12,11,246,9,11,1,11,1,11,1,12,1,12,1,12,1,
  	12,1,12,1,12,1,12,3,12,257,8,12,1,12,1,12,1,13,1,13,1,13,3,13,264,8,13,
  	1,14,1,14,3,14,268,8,14,1,15,1,15,5,15,272,8,15,10,15,12,15,275,9,15,
  	1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,
  	1,16,3,16,292,8,16,1,17,1,17,1,17,1,18,1,18,1,18,1,18,3,18,301,8,18,1,
  	18,1,18,1,18,3,18,306,8,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,1,
  	19,1,20,1,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,22,1,22,1,22,3,22,329,
  	8,22,1,23,1,23,3,23,333,8,23,1,23,1,23,1,23,1,24,1,24,1,24,1,25,1,25,
  	1,25,1,26,1,26,3,26,346,8,26,1,26,1,26,1,27,1,27,1,27,1,27,1,28,1,28,
  	1,28,1,28,1,28,1,28,3,28,360,8,28,1,29,1,29,1,29,1,29,1,29,1,30,1,30,
  	1,30,1,30,1,30,5,30,372,8,30,10,30,12,30,375,9,30,1,30,1,30,1,31,1,31,
  	1,31,5,31,382,8,31,10,31,12,31,385,9,31,1,31,1,31,1,31,1,31,1,31,1,31,
  	3,31,393,8,31,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,
  	1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,
  	1,32,1,32,1,32,3,32,423,8,32,1,32,1,32,1,32,5,32,428,8,32,10,32,12,32,
  	431,9,32,1,32,1,32,1,32,1,32,1,32,1,32,3,32,439,8,32,1,32,1,32,1,32,5,
  	32,444,8,32,10,32,12,32,447,9,32,1,32,1,32,3,32,451,8,32,1,32,1,32,1,
  	32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,
  	32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,3,32,479,8,32,1,32,1,
  	32,1,32,1,32,3,32,485,8,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,
  	32,1,32,1,32,5,32,498,8,32,10,32,12,32,501,9,32,1,33,1,33,1,33,3,33,506,
  	8,33,1,34,1,34,1,34,3,34,511,8,34,1,35,1,35,3,35,515,8,35,1,36,1,36,1,
  	36,3,36,520,8,36,1,37,1,37,3,37,524,8,37,1,38,1,38,1,38,1,38,3,38,530,
  	8,38,1,39,1,39,3,39,534,8,39,1,40,1,40,1,41,1,41,1,41,1,41,1,41,1,41,
  	1,41,1,41,1,41,1,41,3,41,548,8,41,1,42,1,42,1,42,5,42,553,8,42,10,42,
  	12,42,556,9,42,3,42,558,8,42,1,43,1,43,1,44,1,44,1,44,1,44,1,44,3,44,
  	567,8,44,1,44,1,44,1,44,1,45,1,45,3,45,574,8,45,1,46,1,46,1,46,1,47,1,
  	47,1,47,1,47,1,47,3,47,584,8,47,1,48,1,48,1,48,1,49,1,49,1,49,1,49,1,
  	49,1,50,1,50,1,50,1,50,1,50,1,50,1,50,5,50,601,8,50,10,50,12,50,604,9,
  	50,3,50,606,8,50,1,50,1,50,1,51,1,51,1,51,5,51,613,8,51,10,51,12,51,616,
  	9,51,1,51,1,51,1,51,1,51,1,51,1,51,3,51,624,8,51,1,52,1,52,1,52,1,52,
  	1,52,1,52,1,52,1,52,1,52,3,52,635,8,52,1,53,3,53,638,8,53,1,53,1,53,1,
  	54,3,54,643,8,54,1,54,1,54,1,55,1,55,3,55,649,8,55,1,56,1,56,3,56,653,
  	8,56,1,56,1,56,3,56,657,8,56,1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,
  	1,57,3,57,668,8,57,1,58,1,58,1,59,1,59,3,59,674,8,59,1,60,1,60,1,61,1,
  	61,1,61,1,61,1,62,1,62,1,62,1,62,1,63,1,63,1,63,1,63,1,64,1,64,1,64,1,
  	64,1,64,1,64,1,64,1,64,1,64,1,64,1,64,3,64,701,8,64,1,65,1,65,1,66,1,
  	66,1,66,1,66,1,66,1,66,1,67,1,67,1,67,1,67,1,67,1,67,1,68,1,68,1,68,1,
  	68,1,68,1,68,3,68,723,8,68,1,69,1,69,1,70,1,70,1,71,1,71,1,72,1,72,1,
  	73,1,73,1,74,1,74,1,75,1,75,1,75,0,1,64,76,0,2,4,6,8,10,12,14,16,18,20,
  	22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,
  	68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,
  	112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,
  	148,150,0,4,2,0,90,90,94,94,1,0,83,86,1,0,69,72,2,0,65,67,73,73,783,0,
  	152,1,0,0,0,2,158,1,0,0,0,4,166,1,0,0,0,6,172,1,0,0,0,8,174,1,0,0,0,10,
  	190,1,0,0,0,12,203,1,0,0,0,14,220,1,0,0,0,16,222,1,0,0,0,18,228,1,0,0,
  	0,20,230,1,0,0,0,22,237,1,0,0,0,24,249,1,0,0,0,26,263,1,0,0,0,28,267,
  	1,0,0,0,30,269,1,0,0,0,32,291,1,0,0,0,34,293,1,0,0,0,36,296,1,0,0,0,38,
  	309,1,0,0,0,40,316,1,0,0,0,42,320,1,0,0,0,44,328,1,0,0,0,46,330,1,0,0,
  	0,48,337,1,0,0,0,50,340,1,0,0,0,52,343,1,0,0,0,54,349,1,0,0,0,56,353,
  	1,0,0,0,58,361,1,0,0,0,60,366,1,0,0,0,62,392,1,0,0,0,64,450,1,0,0,0,66,
  	505,1,0,0,0,68,510,1,0,0,0,70,514,1,0,0,0,72,519,1,0,0,0,74,523,1,0,0,
  	0,76,529,1,0,0,0,78,533,1,0,0,0,80,535,1,0,0,0,82,547,1,0,0,0,84,557,
  	1,0,0,0,86,559,1,0,0,0,88,561,1,0,0,0,90,573,1,0,0,0,92,575,1,0,0,0,94,
  	583,1,0,0,0,96,585,1,0,0,0,98,588,1,0,0,0,100,593,1,0,0,0,102,623,1,0,
  	0,0,104,634,1,0,0,0,106,637,1,0,0,0,108,642,1,0,0,0,110,648,1,0,0,0,112,
  	652,1,0,0,0,114,667,1,0,0,0,116,669,1,0,0,0,118,673,1,0,0,0,120,675,1,
  	0,0,0,122,677,1,0,0,0,124,681,1,0,0,0,126,685,1,0,0,0,128,700,1,0,0,0,
  	130,702,1,0,0,0,132,704,1,0,0,0,134,710,1,0,0,0,136,722,1,0,0,0,138,724,
  	1,0,0,0,140,726,1,0,0,0,142,728,1,0,0,0,144,730,1,0,0,0,146,732,1,0,0,
  	0,148,734,1,0,0,0,150,736,1,0,0,0,152,153,3,4,2,0,153,154,5,0,0,1,154,
  	1,1,0,0,0,155,157,3,28,14,0,156,155,1,0,0,0,157,160,1,0,0,0,158,156,1,
  	0,0,0,158,159,1,0,0,0,159,161,1,0,0,0,160,158,1,0,0,0,161,162,5,0,0,1,
  	162,3,1,0,0,0,163,165,3,6,3,0,164,163,1,0,0,0,165,168,1,0,0,0,166,164,
  	1,0,0,0,166,167,1,0,0,0,167,5,1,0,0,0,168,166,1,0,0,0,169,173,3,8,4,0,
  	170,173,3,10,5,0,171,173,3,18,9,0,172,169,1,0,0,0,172,170,1,0,0,0,172,
  	171,1,0,0,0,173,7,1,0,0,0,174,176,3,26,13,0,175,177,5,92,0,0,176,175,
  	1,0,0,0,176,177,1,0,0,0,177,178,1,0,0,0,178,181,5,94,0,0,179,180,5,1,
  	0,0,180,182,3,128,64,0,181,179,1,0,0,0,181,182,1,0,0,0,182,186,1,0,0,
  	0,183,184,3,44,22,0,184,185,3,64,32,0,185,187,1,0,0,0,186,183,1,0,0,0,
  	186,187,1,0,0,0,187,188,1,0,0,0,188,189,5,95,0,0,189,9,1,0,0,0,190,191,
  	3,26,13,0,191,192,5,94,0,0,192,193,5,2,0,0,193,194,3,14,7,0,194,197,5,
  	3,0,0,195,196,5,1,0,0,196,198,3,128,64,0,197,195,1,0,0,0,197,198,1,0,
  	0,0,198,201,1,0,0,0,199,202,3,12,6,0,200,202,5,95,0,0,201,199,1,0,0,0,
  	201,200,1,0,0,0,202,11,1,0,0,0,203,207,5,4,0,0,204,206,3,28,14,0,205,
  	204,1,0,0,0,206,209,1,0,0,0,207,205,1,0,0,0,207,208,1,0,0,0,208,210,1,
  	0,0,0,209,207,1,0,0,0,210,211,5,5,0,0,211,13,1,0,0,0,212,217,3,16,8,0,
  	213,214,5,6,0,0,214,216,3,16,8,0,215,213,1,0,0,0,216,219,1,0,0,0,217,
  	215,1,0,0,0,217,218,1,0,0,0,218,221,1,0,0,0,219,217,1,0,0,0,220,212,1,
  	0,0,0,220,221,1,0,0,0,221,15,1,0,0,0,222,223,5,94,0,0,223,224,5,1,0,0,
  	224,225,3,128,64,0,225,17,1,0,0,0,226,229,3,20,10,0,227,229,3,22,11,0,
  	228,226,1,0,0,0,228,227,1,0,0,0,229,19,1,0,0,0,230,231,3,26,13,0,231,
  	232,5,7,0,0,232,233,5,94,0,0,233,234,5,8,0,0,234,235,3,128,64,0,235,236,
  	5,95,0,0,236,21,1,0,0,0,237,238,3,26,13,0,238,239,5,9,0,0,239,240,5,94,
  	0,0,240,244,5,4,0,0,241,243,3,24,12,0,242,241,1,0,0,0,243,246,1,0,0,0,
  	244,242,1,0,0,0,244,245,1,0,0,0,245,247,1,0,0,0,246,244,1,0,0,0,247,248,
  	5,5,0,0,248,23,1,0,0,0,249,250,3,26,13,0,250,251,5,94,0,0,251,252,5,1,
  	0,0,252,256,3,128,64,0,253,254,3,44,22,0,254,255,3,104,52,0,255,257,1,
  	0,0,0,256,253,1,0,0,0,256,257,1,0,0,0,257,258,1,0,0,0,258,259,5,95,0,
  	0,259,25,1,0,0,0,260,264,5,10,0,0,261,264,5,11,0,0,262,264,5,12,0,0,263,
  	260,1,0,0,0,263,261,1,0,0,0,263,262,1,0,0,0,264,27,1,0,0,0,265,268,3,
  	32,16,0,266,268,3,30,15,0,267,265,1,0,0,0,267,266,1,0,0,0,268,29,1,0,
  	0,0,269,273,5,4,0,0,270,272,3,28,14,0,271,270,1,0,0,0,272,275,1,0,0,0,
  	273,271,1,0,0,0,273,274,1,0,0,0,274,276,1,0,0,0,275,273,1,0,0,0,276,277,
  	5,5,0,0,277,31,1,0,0,0,278,292,3,34,17,0,279,292,3,36,18,0,280,292,3,
  	38,19,0,281,292,3,40,20,0,282,292,3,42,21,0,283,292,3,46,23,0,284,292,
  	3,48,24,0,285,292,3,50,25,0,286,292,3,52,26,0,287,292,3,54,27,0,288,292,
  	3,56,28,0,289,292,3,58,29,0,290,292,3,60,30,0,291,278,1,0,0,0,291,279,
  	1,0,0,0,291,280,1,0,0,0,291,281,1,0,0,0,291,282,1,0,0,0,291,283,1,0,0,
  	0,291,284,1,0,0,0,291,285,1,0,0,0,291,286,1,0,0,0,291,287,1,0,0,0,291,
  	288,1,0,0,0,291,289,1,0,0,0,291,290,1,0,0,0,292,33,1,0,0,0,293,294,3,
  	80,40,0,294,295,5,95,0,0,295,35,1,0,0,0,296,297,5,13,0,0,297,300,5,94,
  	0,0,298,299,5,1,0,0,299,301,3,128,64,0,300,298,1,0,0,0,300,301,1,0,0,
  	0,301,305,1,0,0,0,302,303,3,44,22,0,303,304,3,64,32,0,304,306,1,0,0,0,
  	305,302,1,0,0,0,305,306,1,0,0,0,306,307,1,0,0,0,307,308,5,95,0,0,308,
  	37,1,0,0,0,309,310,5,13,0,0,310,311,5,94,0,0,311,312,5,1,0,0,312,313,
  	3,128,64,0,313,314,3,94,47,0,314,315,5,95,0,0,315,39,1,0,0,0,316,317,
  	5,14,0,0,317,318,5,94,0,0,318,319,5,95,0,0,319,41,1,0,0,0,320,321,3,64,
  	32,0,321,322,3,44,22,0,322,323,3,64,32,0,323,324,5,95,0,0,324,43,1,0,
  	0,0,325,329,5,15,0,0,326,329,5,16,0,0,327,329,5,17,0,0,328,325,1,0,0,
  	0,328,326,1,0,0,0,328,327,1,0,0,0,329,45,1,0,0,0,330,332,5,18,0,0,331,
  	333,5,91,0,0,332,331,1,0,0,0,332,333,1,0,0,0,333,334,1,0,0,0,334,335,
  	3,64,32,0,335,336,5,95,0,0,336,47,1,0,0,0,337,338,5,19,0,0,338,339,5,
  	95,0,0,339,49,1,0,0,0,340,341,5,20,0,0,341,342,5,95,0,0,342,51,1,0,0,
  	0,343,345,5,21,0,0,344,346,3,64,32,0,345,344,1,0,0,0,345,346,1,0,0,0,
  	346,347,1,0,0,0,347,348,5,95,0,0,348,53,1,0,0,0,349,350,5,22,0,0,350,
  	351,3,64,32,0,351,352,5,95,0,0,352,55,1,0,0,0,353,354,5,23,0,0,354,355,
  	3,64,32,0,355,356,5,24,0,0,356,359,3,28,14,0,357,358,5,25,0,0,358,360,
  	3,28,14,0,359,357,1,0,0,0,359,360,1,0,0,0,360,57,1,0,0,0,361,362,5,26,
  	0,0,362,363,3,64,32,0,363,364,5,27,0,0,364,365,3,28,14,0,365,59,1,0,0,
  	0,366,367,5,28,0,0,367,368,3,64,32,0,368,369,5,29,0,0,369,373,5,4,0,0,
  	370,372,3,62,31,0,371,370,1,0,0,0,372,375,1,0,0,0,373,371,1,0,0,0,373,
  	374,1,0,0,0,374,376,1,0,0,0,375,373,1,0,0,0,376,377,5,5,0,0,377,61,1,
  	0,0,0,378,383,3,104,52,0,379,380,5,30,0,0,380,382,3,104,52,0,381,379,
  	1,0,0,0,382,385,1,0,0,0,383,381,1,0,0,0,383,384,1,0,0,0,384,386,1,0,0,
  	0,385,383,1,0,0,0,386,387,5,31,0,0,387,388,3,28,14,0,388,393,1,0,0,0,
  	389,390,5,32,0,0,390,391,5,31,0,0,391,393,3,28,14,0,392,378,1,0,0,0,392,
  	389,1,0,0,0,393,63,1,0,0,0,394,395,6,32,-1,0,395,451,3,86,43,0,396,451,
  	3,88,44,0,397,451,3,104,52,0,398,451,3,92,46,0,399,451,3,94,47,0,400,
  	451,3,96,48,0,401,451,3,98,49,0,402,451,3,80,40,0,403,404,5,2,0,0,404,
  	405,3,64,32,0,405,406,5,3,0,0,406,451,1,0,0,0,407,408,3,66,33,0,408,409,
  	3,64,32,13,409,451,1,0,0,0,410,411,5,23,0,0,411,412,3,64,32,0,412,413,
  	5,24,0,0,413,414,3,64,32,0,414,415,5,25,0,0,415,416,3,64,32,4,416,451,
  	1,0,0,0,417,451,3,100,50,0,418,422,5,38,0,0,419,420,3,128,64,0,420,421,
  	5,30,0,0,421,423,1,0,0,0,422,419,1,0,0,0,422,423,1,0,0,0,423,424,1,0,
  	0,0,424,429,3,64,32,0,425,426,5,6,0,0,426,428,3,64,32,0,427,425,1,0,0,
  	0,428,431,1,0,0,0,429,427,1,0,0,0,429,430,1,0,0,0,430,432,1,0,0,0,431,
  	429,1,0,0,0,432,433,5,39,0,0,433,451,1,0,0,0,434,438,5,34,0,0,435,436,
  	3,128,64,0,436,437,5,30,0,0,437,439,1,0,0,0,438,435,1,0,0,0,438,439,1,
  	0,0,0,439,440,1,0,0,0,440,445,3,64,32,0,441,442,5,6,0,0,442,444,3,64,
  	32,0,443,441,1,0,0,0,444,447,1,0,0,0,445,443,1,0,0,0,445,446,1,0,0,0,
  	446,448,1,0,0,0,447,445,1,0,0,0,448,449,5,35,0,0,449,451,1,0,0,0,450,
  	394,1,0,0,0,450,396,1,0,0,0,450,397,1,0,0,0,450,398,1,0,0,0,450,399,1,
  	0,0,0,450,400,1,0,0,0,450,401,1,0,0,0,450,402,1,0,0,0,450,403,1,0,0,0,
  	450,407,1,0,0,0,450,410,1,0,0,0,450,417,1,0,0,0,450,418,1,0,0,0,450,434,
  	1,0,0,0,451,499,1,0,0,0,452,453,10,12,0,0,453,454,3,68,34,0,454,455,3,
  	64,32,13,455,498,1,0,0,0,456,457,10,11,0,0,457,458,3,70,35,0,458,459,
  	3,64,32,12,459,498,1,0,0,0,460,461,10,10,0,0,461,462,3,72,36,0,462,463,
  	3,64,32,11,463,498,1,0,0,0,464,465,10,9,0,0,465,466,3,74,37,0,466,467,
  	3,64,32,10,467,498,1,0,0,0,468,469,10,8,0,0,469,470,3,76,38,0,470,471,
  	3,64,32,9,471,498,1,0,0,0,472,473,10,7,0,0,473,474,3,78,39,0,474,475,
  	3,64,32,8,475,498,1,0,0,0,476,478,10,6,0,0,477,479,5,93,0,0,478,477,1,
  	0,0,0,478,479,1,0,0,0,479,480,1,0,0,0,480,481,5,36,0,0,481,498,3,64,32,
  	7,482,484,10,5,0,0,483,485,5,93,0,0,484,483,1,0,0,0,484,485,1,0,0,0,485,
  	486,1,0,0,0,486,487,5,37,0,0,487,498,3,64,32,6,488,489,10,22,0,0,489,
  	498,5,33,0,0,490,491,10,21,0,0,491,492,5,34,0,0,492,493,3,64,32,0,493,
  	494,5,35,0,0,494,498,1,0,0,0,495,496,10,20,0,0,496,498,5,94,0,0,497,452,
  	1,0,0,0,497,456,1,0,0,0,497,460,1,0,0,0,497,464,1,0,0,0,497,468,1,0,0,
  	0,497,472,1,0,0,0,497,476,1,0,0,0,497,482,1,0,0,0,497,488,1,0,0,0,497,
  	490,1,0,0,0,497,495,1,0,0,0,498,501,1,0,0,0,499,497,1,0,0,0,499,500,1,
  	0,0,0,500,65,1,0,0,0,501,499,1,0,0,0,502,506,5,93,0,0,503,506,5,40,0,
  	0,504,506,5,41,0,0,505,502,1,0,0,0,505,503,1,0,0,0,505,504,1,0,0,0,506,
  	67,1,0,0,0,507,511,5,42,0,0,508,511,5,43,0,0,509,511,5,44,0,0,510,507,
  	1,0,0,0,510,508,1,0,0,0,510,509,1,0,0,0,511,69,1,0,0,0,512,515,5,45,0,
  	0,513,515,5,41,0,0,514,512,1,0,0,0,514,513,1,0,0,0,515,71,1,0,0,0,516,
  	520,5,46,0,0,517,520,5,47,0,0,518,520,5,48,0,0,519,516,1,0,0,0,519,517,
  	1,0,0,0,519,518,1,0,0,0,520,73,1,0,0,0,521,524,5,49,0,0,522,524,5,50,
  	0,0,523,521,1,0,0,0,523,522,1,0,0,0,524,75,1,0,0,0,525,530,5,38,0,0,526,
  	530,5,51,0,0,527,530,5,39,0,0,528,530,5,52,0,0,529,525,1,0,0,0,529,526,
  	1,0,0,0,529,527,1,0,0,0,529,528,1,0,0,0,530,77,1,0,0,0,531,534,5,53,0,
  	0,532,534,5,54,0,0,533,531,1,0,0,0,533,532,1,0,0,0,534,79,1,0,0,0,535,
  	536,3,82,41,0,536,81,1,0,0,0,537,538,5,94,0,0,538,539,5,2,0,0,539,540,
  	3,84,42,0,540,541,5,3,0,0,541,548,1,0,0,0,542,543,3,128,64,0,543,544,
  	5,2,0,0,544,545,3,84,42,0,545,546,5,3,0,0,546,548,1,0,0,0,547,537,1,0,
  	0,0,547,542,1,0,0,0,548,83,1,0,0,0,549,554,3,64,32,0,550,551,5,6,0,0,
  	551,553,3,64,32,0,552,550,1,0,0,0,553,556,1,0,0,0,554,552,1,0,0,0,554,
  	555,1,0,0,0,555,558,1,0,0,0,556,554,1,0,0,0,557,549,1,0,0,0,557,558,1,
  	0,0,0,558,85,1,0,0,0,559,560,5,94,0,0,560,87,1,0,0,0,561,566,5,55,0,0,
  	562,563,5,34,0,0,563,564,3,64,32,0,564,565,5,35,0,0,565,567,1,0,0,0,566,
  	562,1,0,0,0,566,567,1,0,0,0,567,568,1,0,0,0,568,569,3,90,45,0,569,570,
  	3,128,64,0,570,89,1,0,0,0,571,574,5,56,0,0,572,574,5,57,0,0,573,571,1,
  	0,0,0,573,572,1,0,0,0,574,91,1,0,0,0,575,576,5,58,0,0,576,577,3,64,32,
  	0,577,93,1,0,0,0,578,579,5,59,0,0,579,584,3,64,32,0,580,581,5,59,0,0,
  	581,582,5,60,0,0,582,584,3,64,32,0,583,578,1,0,0,0,583,580,1,0,0,0,584,
  	95,1,0,0,0,585,586,5,61,0,0,586,587,3,128,64,0,587,97,1,0,0,0,588,589,
  	5,61,0,0,589,590,5,2,0,0,590,591,3,64,32,0,591,592,5,3,0,0,592,99,1,0,
  	0,0,593,594,5,28,0,0,594,595,3,64,32,0,595,596,5,29,0,0,596,605,5,4,0,
  	0,597,602,3,102,51,0,598,599,5,6,0,0,599,601,3,102,51,0,600,598,1,0,0,
  	0,601,604,1,0,0,0,602,600,1,0,0,0,602,603,1,0,0,0,603,606,1,0,0,0,604,
  	602,1,0,0,0,605,597,1,0,0,0,605,606,1,0,0,0,606,607,1,0,0,0,607,608,5,
  	5,0,0,608,101,1,0,0,0,609,614,3,104,52,0,610,611,5,30,0,0,611,613,3,104,
  	52,0,612,610,1,0,0,0,613,616,1,0,0,0,614,612,1,0,0,0,614,615,1,0,0,0,
  	615,617,1,0,0,0,616,614,1,0,0,0,617,618,5,31,0,0,618,619,3,64,32,0,619,
  	624,1,0,0,0,620,621,5,32,0,0,621,622,5,31,0,0,622,624,3,64,32,0,623,609,
  	1,0,0,0,623,620,1,0,0,0,624,103,1,0,0,0,625,635,3,106,53,0,626,635,3,
  	108,54,0,627,635,3,110,55,0,628,635,3,116,58,0,629,635,3,118,59,0,630,
  	635,3,120,60,0,631,635,3,122,61,0,632,635,3,124,62,0,633,635,3,126,63,
  	0,634,625,1,0,0,0,634,626,1,0,0,0,634,627,1,0,0,0,634,628,1,0,0,0,634,
  	629,1,0,0,0,634,630,1,0,0,0,634,631,1,0,0,0,634,632,1,0,0,0,634,633,1,
  	0,0,0,635,105,1,0,0,0,636,638,7,0,0,0,637,636,1,0,0,0,637,638,1,0,0,0,
  	638,639,1,0,0,0,639,640,5,88,0,0,640,107,1,0,0,0,641,643,7,0,0,0,642,
  	641,1,0,0,0,642,643,1,0,0,0,643,644,1,0,0,0,644,645,5,89,0,0,645,109,
  	1,0,0,0,646,649,3,112,56,0,647,649,3,114,57,0,648,646,1,0,0,0,648,647,
  	1,0,0,0,649,111,1,0,0,0,650,653,5,90,0,0,651,653,5,79,0,0,652,650,1,0,
  	0,0,652,651,1,0,0,0,653,656,1,0,0,0,654,655,5,1,0,0,655,657,5,90,0,0,
  	656,654,1,0,0,0,656,657,1,0,0,0,657,113,1,0,0,0,658,659,5,80,0,0,659,
  	660,5,1,0,0,660,668,5,90,0,0,661,662,5,81,0,0,662,663,5,1,0,0,663,668,
  	5,90,0,0,664,665,5,82,0,0,665,666,5,1,0,0,666,668,5,90,0,0,667,658,1,
  	0,0,0,667,661,1,0,0,0,667,664,1,0,0,0,668,115,1,0,0,0,669,670,7,1,0,0,
  	670,117,1,0,0,0,671,674,5,62,0,0,672,674,5,63,0,0,673,671,1,0,0,0,673,
  	672,1,0,0,0,674,119,1,0,0,0,675,676,5,64,0,0,676,121,1,0,0,0,677,678,
  	5,90,0,0,678,679,5,1,0,0,679,680,5,65,0,0,680,123,1,0,0,0,681,682,5,79,
  	0,0,682,683,5,1,0,0,683,684,5,66,0,0,684,125,1,0,0,0,685,686,5,80,0,0,
  	686,687,5,1,0,0,687,688,5,67,0,0,688,127,1,0,0,0,689,701,3,130,65,0,690,
  	701,3,132,66,0,691,701,3,134,67,0,692,701,3,136,68,0,693,694,5,42,0,0,
  	694,701,3,128,64,0,695,696,5,91,0,0,696,701,3,128,64,0,697,698,5,68,0,
  	0,698,701,3,128,64,0,699,701,3,150,75,0,700,689,1,0,0,0,700,690,1,0,0,
  	0,700,691,1,0,0,0,700,692,1,0,0,0,700,693,1,0,0,0,700,695,1,0,0,0,700,
  	697,1,0,0,0,700,699,1,0,0,0,701,129,1,0,0,0,702,703,5,78,0,0,703,131,
  	1,0,0,0,704,705,5,34,0,0,705,706,3,128,64,0,706,707,5,95,0,0,707,708,
  	5,90,0,0,708,709,5,35,0,0,709,133,1,0,0,0,710,711,5,38,0,0,711,712,3,
  	128,64,0,712,713,5,95,0,0,713,714,5,90,0,0,714,715,5,39,0,0,715,135,1,
  	0,0,0,716,723,3,138,69,0,717,723,3,140,70,0,718,723,3,142,71,0,719,723,
  	3,144,72,0,720,723,3,146,73,0,721,723,3,148,74,0,722,716,1,0,0,0,722,
  	717,1,0,0,0,722,718,1,0,0,0,722,719,1,0,0,0,722,720,1,0,0,0,722,721,1,
  	0,0,0,723,137,1,0,0,0,724,725,7,2,0,0,725,139,1,0,0,0,726,727,7,3,0,0,
  	727,141,1,0,0,0,728,729,5,74,0,0,729,143,1,0,0,0,730,731,5,75,0,0,731,
  	145,1,0,0,0,732,733,5,76,0,0,733,147,1,0,0,0,734,735,5,77,0,0,735,149,
  	1,0,0,0,736,737,5,94,0,0,737,151,1,0,0,0,63,158,166,172,176,181,186,197,
  	201,207,217,220,228,244,256,263,267,273,291,300,305,328,332,345,359,373,
  	383,392,422,429,438,445,450,478,484,497,499,505,510,514,519,523,529,533,
  	547,554,557,566,573,583,602,605,614,623,634,637,642,648,652,656,667,673,
  	700,722
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
    setState(152);
    global();
    setState(153);
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
    setState(158);
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
      setState(155);
      code();
      setState(160);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(161);
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
    setState(166);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__9)
      | (1ULL << anceParser::T__10)
      | (1ULL << anceParser::T__11))) != 0)) {
      setState(163);
      description();
      setState(168);
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
    setState(172);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(169);
      variableDescription();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(170);
      functionDescription();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(171);
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
    setState(174);
    accessModifier();
    setState(176);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::CONST) {
      setState(175);
      match(anceParser::CONST);
    }
    setState(178);
    match(anceParser::IDENTIFIER);
    setState(181);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__0) {
      setState(179);
      match(anceParser::T__0);
      setState(180);
      type();
    }
    setState(186);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(183);
      assigner();
      setState(184);
      expression(0);
    }
    setState(188);
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
    setState(190);
    accessModifier();
    setState(191);
    match(anceParser::IDENTIFIER);
    setState(192);
    match(anceParser::T__1);
    setState(193);
    parameters();
    setState(194);
    match(anceParser::T__2);
    setState(197);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__0) {
      setState(195);
      match(anceParser::T__0);
      setState(196);
      type();
    }
    setState(201);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__3: {
        setState(199);
        functionBlock();
        break;
      }

      case anceParser::SEMICOLON: {
        setState(200);
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
    setState(203);
    match(anceParser::T__3);
    setState(207);
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
      setState(204);
      code();
      setState(209);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(210);
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
    setState(220);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::IDENTIFIER) {
      setState(212);
      parameter();
      setState(217);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(213);
        match(anceParser::T__5);
        setState(214);
        parameter();
        setState(219);
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
    setState(222);
    match(anceParser::IDENTIFIER);
    setState(223);
    match(anceParser::T__0);
    setState(224);
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
    setState(228);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(226);
      aliasDescription();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(227);
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
    setState(230);
    accessModifier();
    setState(231);
    match(anceParser::T__6);
    setState(232);
    match(anceParser::IDENTIFIER);
    setState(233);
    match(anceParser::T__7);
    setState(234);
    type();
    setState(235);
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
    setState(237);
    accessModifier();
    setState(238);
    match(anceParser::T__8);
    setState(239);
    match(anceParser::IDENTIFIER);
    setState(240);
    match(anceParser::T__3);
    setState(244);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__9)
      | (1ULL << anceParser::T__10)
      | (1ULL << anceParser::T__11))) != 0)) {
      setState(241);
      member();
      setState(246);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(247);
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
    setState(249);
    accessModifier();
    setState(250);
    match(anceParser::IDENTIFIER);
    setState(251);
    match(anceParser::T__0);
    setState(252);
    type();
    setState(256);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(253);
      assigner();
      setState(254);
      literalExpression();
    }
    setState(258);
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
    setState(263);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__9: {
        _localctx = _tracker.createInstance<anceParser::PublicContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(260);
        match(anceParser::T__9);
        break;
      }

      case anceParser::T__10: {
        _localctx = _tracker.createInstance<anceParser::PrivateContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(261);
        match(anceParser::T__10);
        break;
      }

      case anceParser::T__11: {
        _localctx = _tracker.createInstance<anceParser::ExternContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(262);
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
    setState(267);
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
        setState(265);
        statement();
        break;
      }

      case anceParser::T__3: {
        enterOuterAlt(_localctx, 2);
        setState(266);
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
    setState(269);
    match(anceParser::T__3);
    setState(273);
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
      setState(270);
      code();
      setState(275);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(276);
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
  enterRule(_localctx, 32, anceParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(291);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(278);
      expressionStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(279);
      localVariableDefinition();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(280);
      localReferenceDefinition();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(281);
      dropStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(282);
      assignment();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(283);
      deleteStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(284);
      breakStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(285);
      continueStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(286);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(287);
      assertStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(288);
      ifStatement();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(289);
      whileStatement();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(290);
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
    setState(293);
    independentExpression();
    setState(294);
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
    setState(296);
    match(anceParser::T__12);
    setState(297);
    match(anceParser::IDENTIFIER);
    setState(300);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__0) {
      setState(298);
      match(anceParser::T__0);
      setState(299);
      type();
    }
    setState(305);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(302);
      assigner();
      setState(303);
      expression(0);
    }
    setState(307);
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
    setState(309);
    match(anceParser::T__12);
    setState(310);
    match(anceParser::IDENTIFIER);
    setState(311);
    match(anceParser::T__0);
    setState(312);
    type();
    setState(313);
    bindRef();
    setState(314);
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
  enterRule(_localctx, 40, anceParser::RuleDropStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(316);
    match(anceParser::T__13);
    setState(317);
    match(anceParser::IDENTIFIER);
    setState(318);
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
    setState(320);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->assignable = expression(0);
    setState(321);
    assigner();
    setState(322);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->assigned = expression(0);
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
    setState(328);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__14: {
        _localctx = _tracker.createInstance<anceParser::CopyAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(325);
        match(anceParser::T__14);
        break;
      }

      case anceParser::T__15: {
        _localctx = _tracker.createInstance<anceParser::MoveAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(326);
        match(anceParser::T__15);
        break;
      }

      case anceParser::T__16: {
        _localctx = _tracker.createInstance<anceParser::FinalCopyAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(327);
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
    setState(330);
    match(anceParser::T__17);
    setState(332);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      setState(331);
      match(anceParser::BUFFER);
      break;
    }

    default:
      break;
    }
    setState(334);
    expression(0);
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
    setState(337);
    match(anceParser::T__18);
    setState(338);
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
    setState(340);
    match(anceParser::T__19);
    setState(341);
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
    setState(343);
    match(anceParser::T__20);
    setState(345);
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
      setState(344);
      expression(0);
    }
    setState(347);
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
    setState(349);
    match(anceParser::T__21);
    setState(350);
    expression(0);
    setState(351);
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
    setState(353);
    match(anceParser::T__22);
    setState(354);
    expression(0);
    setState(355);
    match(anceParser::T__23);
    setState(356);
    antlrcpp::downCast<IfStatementContext *>(_localctx)->ifBlock = code();
    setState(359);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(357);
      match(anceParser::T__24);
      setState(358);
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
    setState(361);
    match(anceParser::T__25);
    setState(362);
    expression(0);
    setState(363);
    match(anceParser::T__26);
    setState(364);
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
  enterRule(_localctx, 60, anceParser::RuleMatchStatement);
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
    setState(366);
    match(anceParser::T__27);
    setState(367);
    expression(0);
    setState(368);
    match(anceParser::T__28);
    setState(369);
    match(anceParser::T__3);
    setState(373);
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
      setState(370);
      matchCase();
      setState(375);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(376);
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
  enterRule(_localctx, 62, anceParser::RuleMatchCase);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(392);
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
        setState(378);
        literalExpression();
        setState(383);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__29) {
          setState(379);
          match(anceParser::T__29);
          setState(380);
          literalExpression();
          setState(385);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(386);
        match(anceParser::T__30);
        setState(387);
        code();
        break;
      }

      case anceParser::T__31: {
        _localctx = _tracker.createInstance<anceParser::DefaultCaseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(389);
        match(anceParser::T__31);
        setState(390);
        match(anceParser::T__30);
        setState(391);
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
  size_t startState = 64;
  enterRecursionRule(_localctx, 64, anceParser::RuleExpression, precedence);

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
    setState(450);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<VariableContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(395);
      variableAccess();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<AllocContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(396);
      allocation();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<LiteralContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(397);
      literalExpression();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<AddressOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(398);
      addressof();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<RefContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(399);
      bindRef();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SizeOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(400);
      sizeofType();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SizeOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(401);
      sizeofExpression();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<IndependentContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(402);
      independentExpression();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ParenthesisContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(403);
      match(anceParser::T__1);
      setState(404);
      expression(0);
      setState(405);
      match(anceParser::T__2);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<UnaryOperationContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(407);
      unaryOperator();
      setState(408);
      expression(13);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<IfExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(410);
      match(anceParser::T__22);
      setState(411);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->condition = expression(0);
      setState(412);
      match(anceParser::T__23);
      setState(413);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->thenBlock = expression(0);
      setState(414);
      match(anceParser::T__24);
      setState(415);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->elseBlock = expression(4);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<MatchContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(417);
      matchExpression();
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<VectorDefinitionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(418);
      match(anceParser::T__37);
      setState(422);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
      case 1: {
        setState(419);
        type();
        setState(420);
        match(anceParser::T__29);
        break;
      }

      default:
        break;
      }
      setState(424);
      expression(0);
      setState(429);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(425);
        match(anceParser::T__5);
        setState(426);
        expression(0);
        setState(431);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(432);
      match(anceParser::T__38);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<ArrayDefinitionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(434);
      match(anceParser::T__33);
      setState(438);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
      case 1: {
        setState(435);
        type();
        setState(436);
        match(anceParser::T__29);
        break;
      }

      default:
        break;
      }
      setState(440);
      expression(0);
      setState(445);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(441);
        match(anceParser::T__5);
        setState(442);
        expression(0);
        setState(447);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(448);
      match(anceParser::T__34);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(499);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(497);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(452);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(453);
          binaryOperatorMultiplicative();
          setState(454);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(13);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(456);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(457);
          binaryOperatorAdditive();
          setState(458);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(12);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(460);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(461);
          binaryOperatorBitwise();
          setState(462);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(11);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(464);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(465);
          binaryOperatorShift();
          setState(466);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(10);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(468);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(469);
          binaryOperatorRelational();
          setState(470);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(9);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(472);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(473);
          binaryOperatorEquality();
          setState(474);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(8);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<LogicalAndContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(476);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(478);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == anceParser::NOT) {
            setState(477);
            match(anceParser::NOT);
          }
          setState(480);
          match(anceParser::T__35);
          setState(481);
          antlrcpp::downCast<LogicalAndContext *>(_localctx)->right = expression(7);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<LogicalOrContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(482);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(484);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == anceParser::NOT) {
            setState(483);
            match(anceParser::NOT);
          }
          setState(486);
          match(anceParser::T__36);
          setState(487);
          antlrcpp::downCast<LogicalOrContext *>(_localctx)->right = expression(6);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<IndirectionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(488);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(489);
          match(anceParser::T__32);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<SubscriptContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->indexed = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(490);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(491);
          match(anceParser::T__33);
          setState(492);
          antlrcpp::downCast<SubscriptContext *>(_localctx)->index = expression(0);
          setState(493);
          match(anceParser::T__34);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->accessed = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(495);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(496);
          match(anceParser::IDENTIFIER);
          break;
        }

        default:
          break;
        } 
      }
      setState(501);
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
  enterRule(_localctx, 66, anceParser::RuleUnaryOperator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(505);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::NOT: {
        _localctx = _tracker.createInstance<anceParser::NotContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(502);
        match(anceParser::NOT);
        break;
      }

      case anceParser::T__39: {
        _localctx = _tracker.createInstance<anceParser::BitwiseNotContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(503);
        match(anceParser::T__39);
        break;
      }

      case anceParser::T__40: {
        _localctx = _tracker.createInstance<anceParser::NegationContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(504);
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
  enterRule(_localctx, 68, anceParser::RuleBinaryOperatorMultiplicative);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(510);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__41: {
        _localctx = _tracker.createInstance<anceParser::MultiplicationContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(507);
        match(anceParser::T__41);
        break;
      }

      case anceParser::T__42: {
        _localctx = _tracker.createInstance<anceParser::DivisionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(508);
        match(anceParser::T__42);
        break;
      }

      case anceParser::T__43: {
        _localctx = _tracker.createInstance<anceParser::RemainderContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(509);
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
  enterRule(_localctx, 70, anceParser::RuleBinaryOperatorAdditive);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(514);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__44: {
        _localctx = _tracker.createInstance<anceParser::AdditionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(512);
        match(anceParser::T__44);
        break;
      }

      case anceParser::T__40: {
        _localctx = _tracker.createInstance<anceParser::SubtractionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(513);
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
  enterRule(_localctx, 72, anceParser::RuleBinaryOperatorBitwise);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(519);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__45: {
        _localctx = _tracker.createInstance<anceParser::BitwiseAndContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(516);
        match(anceParser::T__45);
        break;
      }

      case anceParser::T__46: {
        _localctx = _tracker.createInstance<anceParser::BitwiseOrContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(517);
        match(anceParser::T__46);
        break;
      }

      case anceParser::T__47: {
        _localctx = _tracker.createInstance<anceParser::BitwiseXorContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(518);
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
  enterRule(_localctx, 74, anceParser::RuleBinaryOperatorShift);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(523);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__48: {
        _localctx = _tracker.createInstance<anceParser::LeftShiftContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(521);
        match(anceParser::T__48);
        break;
      }

      case anceParser::T__49: {
        _localctx = _tracker.createInstance<anceParser::RightShiftContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(522);
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
  enterRule(_localctx, 76, anceParser::RuleBinaryOperatorRelational);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(529);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__37: {
        _localctx = _tracker.createInstance<anceParser::LessThanContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(525);
        match(anceParser::T__37);
        break;
      }

      case anceParser::T__50: {
        _localctx = _tracker.createInstance<anceParser::LessThanOrEqualContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(526);
        match(anceParser::T__50);
        break;
      }

      case anceParser::T__38: {
        _localctx = _tracker.createInstance<anceParser::GreaterThanContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(527);
        match(anceParser::T__38);
        break;
      }

      case anceParser::T__51: {
        _localctx = _tracker.createInstance<anceParser::GreaterThanOrEqualContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(528);
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
  enterRule(_localctx, 78, anceParser::RuleBinaryOperatorEquality);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(533);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__52: {
        _localctx = _tracker.createInstance<anceParser::EqualContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(531);
        match(anceParser::T__52);
        break;
      }

      case anceParser::T__53: {
        _localctx = _tracker.createInstance<anceParser::NotEqualContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(532);
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
  enterRule(_localctx, 80, anceParser::RuleIndependentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(535);
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
  enterRule(_localctx, 82, anceParser::RuleFunctionCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(547);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(537);
      match(anceParser::IDENTIFIER);
      setState(538);
      match(anceParser::T__1);
      setState(539);
      arguments();
      setState(540);
      match(anceParser::T__2);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(542);
      type();
      setState(543);
      match(anceParser::T__1);
      setState(544);
      arguments();
      setState(545);
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
  enterRule(_localctx, 84, anceParser::RuleArguments);
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
    setState(557);
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
      setState(549);
      expression(0);
      setState(554);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(550);
        match(anceParser::T__5);
        setState(551);
        expression(0);
        setState(556);
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
  enterRule(_localctx, 86, anceParser::RuleVariableAccess);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(559);
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
  enterRule(_localctx, 88, anceParser::RuleAllocation);
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
    setState(561);
    match(anceParser::T__54);
    setState(566);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__33) {
      setState(562);
      match(anceParser::T__33);
      setState(563);
      expression(0);
      setState(564);
      match(anceParser::T__34);
    }
    setState(568);
    allocator();
    setState(569);
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
  enterRule(_localctx, 90, anceParser::RuleAllocator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(573);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__55: {
        _localctx = _tracker.createInstance<anceParser::DynamicContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(571);
        match(anceParser::T__55);
        break;
      }

      case anceParser::T__56: {
        _localctx = _tracker.createInstance<anceParser::AutomaticContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(572);
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
  enterRule(_localctx, 92, anceParser::RuleAddressof);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(575);
    match(anceParser::T__57);
    setState(576);
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
  enterRule(_localctx, 94, anceParser::RuleBindRef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(583);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::BindReferenceContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(578);
      match(anceParser::T__58);
      setState(579);
      expression(0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::BindReferenceToAddressContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(580);
      match(anceParser::T__58);
      setState(581);
      match(anceParser::T__59);
      setState(582);
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
  enterRule(_localctx, 96, anceParser::RuleSizeofType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(585);
    match(anceParser::T__60);
    setState(586);
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
  enterRule(_localctx, 98, anceParser::RuleSizeofExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(588);
    match(anceParser::T__60);
    setState(589);
    match(anceParser::T__1);
    setState(590);
    expression(0);
    setState(591);
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
  enterRule(_localctx, 100, anceParser::RuleMatchExpression);
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
    setState(593);
    match(anceParser::T__27);
    setState(594);
    antlrcpp::downCast<MatchExpressionContext *>(_localctx)->condition = expression(0);
    setState(595);
    match(anceParser::T__28);
    setState(596);
    match(anceParser::T__3);
    setState(605);
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
      setState(597);
      matchExpressionCase();
      setState(602);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(598);
        match(anceParser::T__5);
        setState(599);
        matchExpressionCase();
        setState(604);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(607);
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
  enterRule(_localctx, 102, anceParser::RuleMatchExpressionCase);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(623);
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
        setState(609);
        literalExpression();
        setState(614);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__29) {
          setState(610);
          match(anceParser::T__29);
          setState(611);
          literalExpression();
          setState(616);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(617);
        match(anceParser::T__30);
        setState(618);
        expression(0);
        break;
      }

      case anceParser::T__31: {
        _localctx = _tracker.createInstance<anceParser::DefaultExpressionCaseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(620);
        match(anceParser::T__31);
        setState(621);
        match(anceParser::T__30);
        setState(622);
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
  enterRule(_localctx, 104, anceParser::RuleLiteralExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(634);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(625);
      stringLiteral();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(626);
      charLiteral();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(627);
      integerLiteral();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(628);
      floatingPointLiteral();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(629);
      booleanLiteral();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(630);
      nullLiteral();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(631);
      sizeLiteral();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(632);
      diffLiteral();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(633);
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
  enterRule(_localctx, 106, anceParser::RuleStringLiteral);
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
    setState(637);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER

    || _la == anceParser::IDENTIFIER) {
      setState(636);
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
    setState(639);
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
  enterRule(_localctx, 108, anceParser::RuleCharLiteral);
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
    setState(642);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER

    || _la == anceParser::IDENTIFIER) {
      setState(641);
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
    setState(644);
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
  enterRule(_localctx, 110, anceParser::RuleIntegerLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(648);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::SIGNED_INTEGER:
      case anceParser::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(646);
        normalInteger();
        break;
      }

      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(647);
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
  enterRule(_localctx, 112, anceParser::RuleNormalInteger);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(652);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::INTEGER: {
        setState(650);
        antlrcpp::downCast<NormalIntegerContext *>(_localctx)->uvalue = match(anceParser::INTEGER);
        break;
      }

      case anceParser::SIGNED_INTEGER: {
        setState(651);
        antlrcpp::downCast<NormalIntegerContext *>(_localctx)->svalue = match(anceParser::SIGNED_INTEGER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(656);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      setState(654);
      match(anceParser::T__0);
      setState(655);
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
  enterRule(_localctx, 114, anceParser::RuleSpecialInteger);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(667);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::HEX_INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(658);
        match(anceParser::HEX_INTEGER);
        setState(659);
        match(anceParser::T__0);
        setState(660);
        antlrcpp::downCast<SpecialIntegerContext *>(_localctx)->width = match(anceParser::INTEGER);
        break;
      }

      case anceParser::BIN_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(661);
        match(anceParser::BIN_INTEGER);
        setState(662);
        match(anceParser::T__0);
        setState(663);
        antlrcpp::downCast<SpecialIntegerContext *>(_localctx)->width = match(anceParser::INTEGER);
        break;
      }

      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(664);
        match(anceParser::OCT_INTEGER);
        setState(665);
        match(anceParser::T__0);
        setState(666);
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
  enterRule(_localctx, 116, anceParser::RuleFloatingPointLiteral);
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
    setState(669);
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
  enterRule(_localctx, 118, anceParser::RuleBooleanLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(673);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__61: {
        _localctx = _tracker.createInstance<anceParser::TrueContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(671);
        match(anceParser::T__61);
        break;
      }

      case anceParser::T__62: {
        _localctx = _tracker.createInstance<anceParser::FalseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(672);
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
  enterRule(_localctx, 120, anceParser::RuleNullLiteral);

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
    setState(675);
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
  enterRule(_localctx, 122, anceParser::RuleSizeLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(677);
    match(anceParser::INTEGER);
    setState(678);
    match(anceParser::T__0);
    setState(679);
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
  enterRule(_localctx, 124, anceParser::RuleDiffLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(681);
    match(anceParser::SIGNED_INTEGER);
    setState(682);
    match(anceParser::T__0);
    setState(683);
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
  enterRule(_localctx, 126, anceParser::RuleUiptrLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(685);
    match(anceParser::HEX_INTEGER);
    setState(686);
    match(anceParser::T__0);
    setState(687);
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
  enterRule(_localctx, 128, anceParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(700);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::NATIVE_INTEGER_TYPE: {
        _localctx = _tracker.createInstance<anceParser::IntegerContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(689);
        integerType();
        break;
      }

      case anceParser::T__33: {
        _localctx = _tracker.createInstance<anceParser::ArrayContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(690);
        arrayType();
        break;
      }

      case anceParser::T__37: {
        _localctx = _tracker.createInstance<anceParser::VectorContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(691);
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
        setState(692);
        keywordType();
        break;
      }

      case anceParser::T__41: {
        _localctx = _tracker.createInstance<anceParser::PointerContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(693);
        match(anceParser::T__41);
        setState(694);
        type();
        break;
      }

      case anceParser::BUFFER: {
        _localctx = _tracker.createInstance<anceParser::BufferContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(695);
        match(anceParser::BUFFER);
        setState(696);
        type();
        break;
      }

      case anceParser::T__67: {
        _localctx = _tracker.createInstance<anceParser::ReferenceContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(697);
        match(anceParser::T__67);
        setState(698);
        type();
        break;
      }

      case anceParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<anceParser::CustomContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(699);
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
  enterRule(_localctx, 130, anceParser::RuleIntegerType);

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
  enterRule(_localctx, 132, anceParser::RuleArrayType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(704);
    match(anceParser::T__33);
    setState(705);
    type();
    setState(706);
    match(anceParser::SEMICOLON);
    setState(707);
    match(anceParser::INTEGER);
    setState(708);
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
  enterRule(_localctx, 134, anceParser::RuleVectorType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(710);
    match(anceParser::T__37);
    setState(711);
    type();
    setState(712);
    match(anceParser::SEMICOLON);
    setState(713);
    match(anceParser::INTEGER);
    setState(714);
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
  enterRule(_localctx, 136, anceParser::RuleKeywordType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(722);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__68:
      case anceParser::T__69:
      case anceParser::T__70:
      case anceParser::T__71: {
        enterOuterAlt(_localctx, 1);
        setState(716);
        floatingPointType();
        break;
      }

      case anceParser::T__64:
      case anceParser::T__65:
      case anceParser::T__66:
      case anceParser::T__72: {
        enterOuterAlt(_localctx, 2);
        setState(717);
        targetDependentType();
        break;
      }

      case anceParser::T__73: {
        enterOuterAlt(_localctx, 3);
        setState(718);
        booleanType();
        break;
      }

      case anceParser::T__74: {
        enterOuterAlt(_localctx, 4);
        setState(719);
        charType();
        break;
      }

      case anceParser::T__75: {
        enterOuterAlt(_localctx, 5);
        setState(720);
        nullPointerType();
        break;
      }

      case anceParser::T__76: {
        enterOuterAlt(_localctx, 6);
        setState(721);
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
  enterRule(_localctx, 138, anceParser::RuleFloatingPointType);
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
    setState(724);
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
  enterRule(_localctx, 140, anceParser::RuleTargetDependentType);
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
    setState(726);
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
  enterRule(_localctx, 142, anceParser::RuleBooleanType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(728);
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
  enterRule(_localctx, 144, anceParser::RuleCharType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(730);
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
  enterRule(_localctx, 146, anceParser::RuleNullPointerType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(732);
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
  enterRule(_localctx, 148, anceParser::RuleVoidType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(734);
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
  enterRule(_localctx, 150, anceParser::RuleCustomType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(736);
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
    case 32: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

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
