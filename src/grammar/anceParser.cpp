
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
      "file", "projectFile", "variableDeclaration", "function", "parameters", 
      "parameter", "typeDefinition", "defineAlias", "structDefinition", 
      "member", "accessModifier", "code", "block", "statement", "expressionStatement", 
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
      "NOT", "IDENTIFIER", "SEMICOLON", "WHITESPACE", "BLOCK_COMMENT", "LINE_COMMENT", 
      "ERROR_CHAR"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,99,738,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,7,
  	70,2,71,7,71,2,72,7,72,1,0,1,0,1,0,5,0,150,8,0,10,0,12,0,153,9,0,1,0,
  	1,0,1,1,5,1,158,8,1,10,1,12,1,161,9,1,1,1,1,1,1,2,1,2,3,2,167,8,2,1,2,
  	1,2,1,2,3,2,172,8,2,1,2,1,2,1,2,3,2,177,8,2,1,2,1,2,1,3,1,3,1,3,1,3,1,
  	3,1,3,1,3,3,3,188,8,3,1,3,1,3,5,3,192,8,3,10,3,12,3,195,9,3,1,3,1,3,1,
  	3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,206,8,3,1,3,1,3,3,3,210,8,3,1,4,1,4,1,4,
  	5,4,215,8,4,10,4,12,4,218,9,4,3,4,220,8,4,1,5,1,5,1,5,1,5,1,6,1,6,3,6,
  	228,8,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,5,8,242,8,8,10,
  	8,12,8,245,9,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,256,8,9,1,9,1,
  	9,1,10,1,10,1,10,3,10,263,8,10,1,11,1,11,3,11,267,8,11,1,12,1,12,5,12,
  	271,8,12,10,12,12,12,274,9,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,
  	1,13,1,13,1,13,1,13,1,13,1,13,1,13,3,13,291,8,13,1,14,1,14,1,14,1,15,
  	1,15,1,15,1,15,3,15,300,8,15,1,15,1,15,1,15,3,15,305,8,15,1,15,1,15,1,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,
  	18,1,18,1,19,1,19,1,19,3,19,328,8,19,1,20,1,20,3,20,332,8,20,1,20,1,20,
  	1,20,1,21,1,21,1,21,1,22,1,22,1,22,1,23,1,23,3,23,345,8,23,1,23,1,23,
  	1,24,1,24,1,24,1,24,1,25,1,25,1,25,1,25,1,25,1,25,3,25,359,8,25,1,26,
  	1,26,1,26,1,26,1,26,1,27,1,27,1,27,1,27,1,27,5,27,371,8,27,10,27,12,27,
  	374,9,27,1,27,1,27,1,28,1,28,1,28,5,28,381,8,28,10,28,12,28,384,9,28,
  	1,28,1,28,1,28,1,28,1,28,1,28,3,28,392,8,28,1,29,1,29,1,29,1,29,1,29,
  	1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,
  	1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,3,29,422,8,29,1,29,1,29,
  	1,29,5,29,427,8,29,10,29,12,29,430,9,29,1,29,1,29,1,29,1,29,1,29,1,29,
  	3,29,438,8,29,1,29,1,29,1,29,5,29,443,8,29,10,29,12,29,446,9,29,1,29,
  	1,29,3,29,450,8,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,
  	1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,
  	1,29,1,29,3,29,478,8,29,1,29,1,29,1,29,1,29,3,29,484,8,29,1,29,1,29,1,
  	29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,1,29,5,29,497,8,29,10,29,12,29,
  	500,9,29,1,30,1,30,1,30,3,30,505,8,30,1,31,1,31,1,31,3,31,510,8,31,1,
  	32,1,32,3,32,514,8,32,1,33,1,33,1,33,3,33,519,8,33,1,34,1,34,3,34,523,
  	8,34,1,35,1,35,1,35,1,35,3,35,529,8,35,1,36,1,36,3,36,533,8,36,1,37,1,
  	37,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,1,38,3,38,547,8,38,1,
  	39,1,39,1,39,5,39,552,8,39,10,39,12,39,555,9,39,3,39,557,8,39,1,40,1,
  	40,1,41,1,41,1,41,1,41,1,41,3,41,566,8,41,1,41,1,41,1,41,1,42,1,42,3,
  	42,573,8,42,1,43,1,43,1,43,1,44,1,44,1,44,1,44,1,44,3,44,583,8,44,1,45,
  	1,45,1,45,1,46,1,46,1,46,1,46,1,46,1,47,1,47,1,47,1,47,1,47,1,47,1,47,
  	5,47,600,8,47,10,47,12,47,603,9,47,3,47,605,8,47,1,47,1,47,1,48,1,48,
  	1,48,5,48,612,8,48,10,48,12,48,615,9,48,1,48,1,48,1,48,1,48,1,48,1,48,
  	3,48,623,8,48,1,49,1,49,1,49,1,49,1,49,1,49,1,49,1,49,1,49,3,49,634,8,
  	49,1,50,3,50,637,8,50,1,50,1,50,1,51,3,51,642,8,51,1,51,1,51,1,52,1,52,
  	3,52,648,8,52,1,53,1,53,3,53,652,8,53,1,53,1,53,3,53,656,8,53,1,54,1,
  	54,1,54,1,54,1,54,1,54,1,54,1,54,1,54,3,54,667,8,54,1,55,1,55,1,56,1,
  	56,3,56,673,8,56,1,57,1,57,1,58,1,58,1,58,1,58,1,59,1,59,1,59,1,59,1,
  	60,1,60,1,60,1,60,1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,
  	61,3,61,700,8,61,1,62,1,62,1,63,1,63,1,63,1,63,1,63,1,63,1,64,1,64,1,
  	64,1,64,1,64,1,64,1,65,1,65,1,65,1,65,1,65,1,65,3,65,722,8,65,1,66,1,
  	66,1,67,1,67,1,68,1,68,1,69,1,69,1,70,1,70,1,71,1,71,1,72,1,72,1,72,0,
  	1,58,73,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,
  	44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,
  	90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,
  	128,130,132,134,136,138,140,142,144,0,4,2,0,90,90,94,94,1,0,83,86,1,0,
  	69,72,2,0,65,67,73,73,786,0,151,1,0,0,0,2,159,1,0,0,0,4,164,1,0,0,0,6,
  	209,1,0,0,0,8,219,1,0,0,0,10,221,1,0,0,0,12,227,1,0,0,0,14,229,1,0,0,
  	0,16,236,1,0,0,0,18,248,1,0,0,0,20,262,1,0,0,0,22,266,1,0,0,0,24,268,
  	1,0,0,0,26,290,1,0,0,0,28,292,1,0,0,0,30,295,1,0,0,0,32,308,1,0,0,0,34,
  	315,1,0,0,0,36,319,1,0,0,0,38,327,1,0,0,0,40,329,1,0,0,0,42,336,1,0,0,
  	0,44,339,1,0,0,0,46,342,1,0,0,0,48,348,1,0,0,0,50,352,1,0,0,0,52,360,
  	1,0,0,0,54,365,1,0,0,0,56,391,1,0,0,0,58,449,1,0,0,0,60,504,1,0,0,0,62,
  	509,1,0,0,0,64,513,1,0,0,0,66,518,1,0,0,0,68,522,1,0,0,0,70,528,1,0,0,
  	0,72,532,1,0,0,0,74,534,1,0,0,0,76,546,1,0,0,0,78,556,1,0,0,0,80,558,
  	1,0,0,0,82,560,1,0,0,0,84,572,1,0,0,0,86,574,1,0,0,0,88,582,1,0,0,0,90,
  	584,1,0,0,0,92,587,1,0,0,0,94,592,1,0,0,0,96,622,1,0,0,0,98,633,1,0,0,
  	0,100,636,1,0,0,0,102,641,1,0,0,0,104,647,1,0,0,0,106,651,1,0,0,0,108,
  	666,1,0,0,0,110,668,1,0,0,0,112,672,1,0,0,0,114,674,1,0,0,0,116,676,1,
  	0,0,0,118,680,1,0,0,0,120,684,1,0,0,0,122,699,1,0,0,0,124,701,1,0,0,0,
  	126,703,1,0,0,0,128,709,1,0,0,0,130,721,1,0,0,0,132,723,1,0,0,0,134,725,
  	1,0,0,0,136,727,1,0,0,0,138,729,1,0,0,0,140,731,1,0,0,0,142,733,1,0,0,
  	0,144,735,1,0,0,0,146,150,3,4,2,0,147,150,3,6,3,0,148,150,3,12,6,0,149,
  	146,1,0,0,0,149,147,1,0,0,0,149,148,1,0,0,0,150,153,1,0,0,0,151,149,1,
  	0,0,0,151,152,1,0,0,0,152,154,1,0,0,0,153,151,1,0,0,0,154,155,5,0,0,1,
  	155,1,1,0,0,0,156,158,3,22,11,0,157,156,1,0,0,0,158,161,1,0,0,0,159,157,
  	1,0,0,0,159,160,1,0,0,0,160,162,1,0,0,0,161,159,1,0,0,0,162,163,5,0,0,
  	1,163,3,1,0,0,0,164,166,3,20,10,0,165,167,5,92,0,0,166,165,1,0,0,0,166,
  	167,1,0,0,0,167,168,1,0,0,0,168,171,5,94,0,0,169,170,5,1,0,0,170,172,
  	3,122,61,0,171,169,1,0,0,0,171,172,1,0,0,0,172,176,1,0,0,0,173,174,3,
  	38,19,0,174,175,3,58,29,0,175,177,1,0,0,0,176,173,1,0,0,0,176,177,1,0,
  	0,0,177,178,1,0,0,0,178,179,5,95,0,0,179,5,1,0,0,0,180,181,3,20,10,0,
  	181,182,5,94,0,0,182,183,5,2,0,0,183,184,3,8,4,0,184,187,5,3,0,0,185,
  	186,5,1,0,0,186,188,3,122,61,0,187,185,1,0,0,0,187,188,1,0,0,0,188,189,
  	1,0,0,0,189,193,5,4,0,0,190,192,3,22,11,0,191,190,1,0,0,0,192,195,1,0,
  	0,0,193,191,1,0,0,0,193,194,1,0,0,0,194,196,1,0,0,0,195,193,1,0,0,0,196,
  	197,5,5,0,0,197,210,1,0,0,0,198,199,5,6,0,0,199,200,5,94,0,0,200,201,
  	5,2,0,0,201,202,3,8,4,0,202,205,5,3,0,0,203,204,5,1,0,0,204,206,3,122,
  	61,0,205,203,1,0,0,0,205,206,1,0,0,0,206,207,1,0,0,0,207,208,5,95,0,0,
  	208,210,1,0,0,0,209,180,1,0,0,0,209,198,1,0,0,0,210,7,1,0,0,0,211,216,
  	3,10,5,0,212,213,5,7,0,0,213,215,3,10,5,0,214,212,1,0,0,0,215,218,1,0,
  	0,0,216,214,1,0,0,0,216,217,1,0,0,0,217,220,1,0,0,0,218,216,1,0,0,0,219,
  	211,1,0,0,0,219,220,1,0,0,0,220,9,1,0,0,0,221,222,5,94,0,0,222,223,5,
  	1,0,0,223,224,3,122,61,0,224,11,1,0,0,0,225,228,3,14,7,0,226,228,3,16,
  	8,0,227,225,1,0,0,0,227,226,1,0,0,0,228,13,1,0,0,0,229,230,3,20,10,0,
  	230,231,5,8,0,0,231,232,5,94,0,0,232,233,5,9,0,0,233,234,3,122,61,0,234,
  	235,5,95,0,0,235,15,1,0,0,0,236,237,3,20,10,0,237,238,5,10,0,0,238,239,
  	5,94,0,0,239,243,5,4,0,0,240,242,3,18,9,0,241,240,1,0,0,0,242,245,1,0,
  	0,0,243,241,1,0,0,0,243,244,1,0,0,0,244,246,1,0,0,0,245,243,1,0,0,0,246,
  	247,5,5,0,0,247,17,1,0,0,0,248,249,3,20,10,0,249,250,5,94,0,0,250,251,
  	5,1,0,0,251,255,3,122,61,0,252,253,3,38,19,0,253,254,3,98,49,0,254,256,
  	1,0,0,0,255,252,1,0,0,0,255,256,1,0,0,0,256,257,1,0,0,0,257,258,5,95,
  	0,0,258,19,1,0,0,0,259,263,5,11,0,0,260,263,5,12,0,0,261,263,5,6,0,0,
  	262,259,1,0,0,0,262,260,1,0,0,0,262,261,1,0,0,0,263,21,1,0,0,0,264,267,
  	3,26,13,0,265,267,3,24,12,0,266,264,1,0,0,0,266,265,1,0,0,0,267,23,1,
  	0,0,0,268,272,5,4,0,0,269,271,3,22,11,0,270,269,1,0,0,0,271,274,1,0,0,
  	0,272,270,1,0,0,0,272,273,1,0,0,0,273,275,1,0,0,0,274,272,1,0,0,0,275,
  	276,5,5,0,0,276,25,1,0,0,0,277,291,3,28,14,0,278,291,3,30,15,0,279,291,
  	3,32,16,0,280,291,3,34,17,0,281,291,3,36,18,0,282,291,3,40,20,0,283,291,
  	3,42,21,0,284,291,3,44,22,0,285,291,3,46,23,0,286,291,3,48,24,0,287,291,
  	3,50,25,0,288,291,3,52,26,0,289,291,3,54,27,0,290,277,1,0,0,0,290,278,
  	1,0,0,0,290,279,1,0,0,0,290,280,1,0,0,0,290,281,1,0,0,0,290,282,1,0,0,
  	0,290,283,1,0,0,0,290,284,1,0,0,0,290,285,1,0,0,0,290,286,1,0,0,0,290,
  	287,1,0,0,0,290,288,1,0,0,0,290,289,1,0,0,0,291,27,1,0,0,0,292,293,3,
  	74,37,0,293,294,5,95,0,0,294,29,1,0,0,0,295,296,5,13,0,0,296,299,5,94,
  	0,0,297,298,5,1,0,0,298,300,3,122,61,0,299,297,1,0,0,0,299,300,1,0,0,
  	0,300,304,1,0,0,0,301,302,3,38,19,0,302,303,3,58,29,0,303,305,1,0,0,0,
  	304,301,1,0,0,0,304,305,1,0,0,0,305,306,1,0,0,0,306,307,5,95,0,0,307,
  	31,1,0,0,0,308,309,5,13,0,0,309,310,5,94,0,0,310,311,5,1,0,0,311,312,
  	3,122,61,0,312,313,3,88,44,0,313,314,5,95,0,0,314,33,1,0,0,0,315,316,
  	5,14,0,0,316,317,5,94,0,0,317,318,5,95,0,0,318,35,1,0,0,0,319,320,3,58,
  	29,0,320,321,3,38,19,0,321,322,3,58,29,0,322,323,5,95,0,0,323,37,1,0,
  	0,0,324,328,5,15,0,0,325,328,5,16,0,0,326,328,5,17,0,0,327,324,1,0,0,
  	0,327,325,1,0,0,0,327,326,1,0,0,0,328,39,1,0,0,0,329,331,5,18,0,0,330,
  	332,5,91,0,0,331,330,1,0,0,0,331,332,1,0,0,0,332,333,1,0,0,0,333,334,
  	3,58,29,0,334,335,5,95,0,0,335,41,1,0,0,0,336,337,5,19,0,0,337,338,5,
  	95,0,0,338,43,1,0,0,0,339,340,5,20,0,0,340,341,5,95,0,0,341,45,1,0,0,
  	0,342,344,5,21,0,0,343,345,3,58,29,0,344,343,1,0,0,0,344,345,1,0,0,0,
  	345,346,1,0,0,0,346,347,5,95,0,0,347,47,1,0,0,0,348,349,5,22,0,0,349,
  	350,3,58,29,0,350,351,5,95,0,0,351,49,1,0,0,0,352,353,5,23,0,0,353,354,
  	3,58,29,0,354,355,5,24,0,0,355,358,3,22,11,0,356,357,5,25,0,0,357,359,
  	3,22,11,0,358,356,1,0,0,0,358,359,1,0,0,0,359,51,1,0,0,0,360,361,5,26,
  	0,0,361,362,3,58,29,0,362,363,5,27,0,0,363,364,3,22,11,0,364,53,1,0,0,
  	0,365,366,5,28,0,0,366,367,3,58,29,0,367,368,5,29,0,0,368,372,5,4,0,0,
  	369,371,3,56,28,0,370,369,1,0,0,0,371,374,1,0,0,0,372,370,1,0,0,0,372,
  	373,1,0,0,0,373,375,1,0,0,0,374,372,1,0,0,0,375,376,5,5,0,0,376,55,1,
  	0,0,0,377,382,3,98,49,0,378,379,5,30,0,0,379,381,3,98,49,0,380,378,1,
  	0,0,0,381,384,1,0,0,0,382,380,1,0,0,0,382,383,1,0,0,0,383,385,1,0,0,0,
  	384,382,1,0,0,0,385,386,5,31,0,0,386,387,3,22,11,0,387,392,1,0,0,0,388,
  	389,5,32,0,0,389,390,5,31,0,0,390,392,3,22,11,0,391,377,1,0,0,0,391,388,
  	1,0,0,0,392,57,1,0,0,0,393,394,6,29,-1,0,394,450,3,80,40,0,395,450,3,
  	82,41,0,396,450,3,98,49,0,397,450,3,86,43,0,398,450,3,88,44,0,399,450,
  	3,90,45,0,400,450,3,92,46,0,401,450,3,74,37,0,402,403,5,2,0,0,403,404,
  	3,58,29,0,404,405,5,3,0,0,405,450,1,0,0,0,406,407,3,60,30,0,407,408,3,
  	58,29,13,408,450,1,0,0,0,409,410,5,23,0,0,410,411,3,58,29,0,411,412,5,
  	24,0,0,412,413,3,58,29,0,413,414,5,25,0,0,414,415,3,58,29,4,415,450,1,
  	0,0,0,416,450,3,94,47,0,417,421,5,38,0,0,418,419,3,122,61,0,419,420,5,
  	30,0,0,420,422,1,0,0,0,421,418,1,0,0,0,421,422,1,0,0,0,422,423,1,0,0,
  	0,423,428,3,58,29,0,424,425,5,7,0,0,425,427,3,58,29,0,426,424,1,0,0,0,
  	427,430,1,0,0,0,428,426,1,0,0,0,428,429,1,0,0,0,429,431,1,0,0,0,430,428,
  	1,0,0,0,431,432,5,39,0,0,432,450,1,0,0,0,433,437,5,34,0,0,434,435,3,122,
  	61,0,435,436,5,30,0,0,436,438,1,0,0,0,437,434,1,0,0,0,437,438,1,0,0,0,
  	438,439,1,0,0,0,439,444,3,58,29,0,440,441,5,7,0,0,441,443,3,58,29,0,442,
  	440,1,0,0,0,443,446,1,0,0,0,444,442,1,0,0,0,444,445,1,0,0,0,445,447,1,
  	0,0,0,446,444,1,0,0,0,447,448,5,35,0,0,448,450,1,0,0,0,449,393,1,0,0,
  	0,449,395,1,0,0,0,449,396,1,0,0,0,449,397,1,0,0,0,449,398,1,0,0,0,449,
  	399,1,0,0,0,449,400,1,0,0,0,449,401,1,0,0,0,449,402,1,0,0,0,449,406,1,
  	0,0,0,449,409,1,0,0,0,449,416,1,0,0,0,449,417,1,0,0,0,449,433,1,0,0,0,
  	450,498,1,0,0,0,451,452,10,12,0,0,452,453,3,62,31,0,453,454,3,58,29,13,
  	454,497,1,0,0,0,455,456,10,11,0,0,456,457,3,64,32,0,457,458,3,58,29,12,
  	458,497,1,0,0,0,459,460,10,10,0,0,460,461,3,66,33,0,461,462,3,58,29,11,
  	462,497,1,0,0,0,463,464,10,9,0,0,464,465,3,68,34,0,465,466,3,58,29,10,
  	466,497,1,0,0,0,467,468,10,8,0,0,468,469,3,70,35,0,469,470,3,58,29,9,
  	470,497,1,0,0,0,471,472,10,7,0,0,472,473,3,72,36,0,473,474,3,58,29,8,
  	474,497,1,0,0,0,475,477,10,6,0,0,476,478,5,93,0,0,477,476,1,0,0,0,477,
  	478,1,0,0,0,478,479,1,0,0,0,479,480,5,36,0,0,480,497,3,58,29,7,481,483,
  	10,5,0,0,482,484,5,93,0,0,483,482,1,0,0,0,483,484,1,0,0,0,484,485,1,0,
  	0,0,485,486,5,37,0,0,486,497,3,58,29,6,487,488,10,22,0,0,488,497,5,33,
  	0,0,489,490,10,21,0,0,490,491,5,34,0,0,491,492,3,58,29,0,492,493,5,35,
  	0,0,493,497,1,0,0,0,494,495,10,20,0,0,495,497,5,94,0,0,496,451,1,0,0,
  	0,496,455,1,0,0,0,496,459,1,0,0,0,496,463,1,0,0,0,496,467,1,0,0,0,496,
  	471,1,0,0,0,496,475,1,0,0,0,496,481,1,0,0,0,496,487,1,0,0,0,496,489,1,
  	0,0,0,496,494,1,0,0,0,497,500,1,0,0,0,498,496,1,0,0,0,498,499,1,0,0,0,
  	499,59,1,0,0,0,500,498,1,0,0,0,501,505,5,93,0,0,502,505,5,40,0,0,503,
  	505,5,41,0,0,504,501,1,0,0,0,504,502,1,0,0,0,504,503,1,0,0,0,505,61,1,
  	0,0,0,506,510,5,42,0,0,507,510,5,43,0,0,508,510,5,44,0,0,509,506,1,0,
  	0,0,509,507,1,0,0,0,509,508,1,0,0,0,510,63,1,0,0,0,511,514,5,45,0,0,512,
  	514,5,41,0,0,513,511,1,0,0,0,513,512,1,0,0,0,514,65,1,0,0,0,515,519,5,
  	46,0,0,516,519,5,47,0,0,517,519,5,48,0,0,518,515,1,0,0,0,518,516,1,0,
  	0,0,518,517,1,0,0,0,519,67,1,0,0,0,520,523,5,49,0,0,521,523,5,50,0,0,
  	522,520,1,0,0,0,522,521,1,0,0,0,523,69,1,0,0,0,524,529,5,38,0,0,525,529,
  	5,51,0,0,526,529,5,39,0,0,527,529,5,52,0,0,528,524,1,0,0,0,528,525,1,
  	0,0,0,528,526,1,0,0,0,528,527,1,0,0,0,529,71,1,0,0,0,530,533,5,53,0,0,
  	531,533,5,54,0,0,532,530,1,0,0,0,532,531,1,0,0,0,533,73,1,0,0,0,534,535,
  	3,76,38,0,535,75,1,0,0,0,536,537,5,94,0,0,537,538,5,2,0,0,538,539,3,78,
  	39,0,539,540,5,3,0,0,540,547,1,0,0,0,541,542,3,122,61,0,542,543,5,2,0,
  	0,543,544,3,78,39,0,544,545,5,3,0,0,545,547,1,0,0,0,546,536,1,0,0,0,546,
  	541,1,0,0,0,547,77,1,0,0,0,548,553,3,58,29,0,549,550,5,7,0,0,550,552,
  	3,58,29,0,551,549,1,0,0,0,552,555,1,0,0,0,553,551,1,0,0,0,553,554,1,0,
  	0,0,554,557,1,0,0,0,555,553,1,0,0,0,556,548,1,0,0,0,556,557,1,0,0,0,557,
  	79,1,0,0,0,558,559,5,94,0,0,559,81,1,0,0,0,560,565,5,55,0,0,561,562,5,
  	34,0,0,562,563,3,58,29,0,563,564,5,35,0,0,564,566,1,0,0,0,565,561,1,0,
  	0,0,565,566,1,0,0,0,566,567,1,0,0,0,567,568,3,84,42,0,568,569,3,122,61,
  	0,569,83,1,0,0,0,570,573,5,56,0,0,571,573,5,57,0,0,572,570,1,0,0,0,572,
  	571,1,0,0,0,573,85,1,0,0,0,574,575,5,58,0,0,575,576,3,58,29,0,576,87,
  	1,0,0,0,577,578,5,59,0,0,578,583,3,58,29,0,579,580,5,59,0,0,580,581,5,
  	60,0,0,581,583,3,58,29,0,582,577,1,0,0,0,582,579,1,0,0,0,583,89,1,0,0,
  	0,584,585,5,61,0,0,585,586,3,122,61,0,586,91,1,0,0,0,587,588,5,61,0,0,
  	588,589,5,2,0,0,589,590,3,58,29,0,590,591,5,3,0,0,591,93,1,0,0,0,592,
  	593,5,28,0,0,593,594,3,58,29,0,594,595,5,29,0,0,595,604,5,4,0,0,596,601,
  	3,96,48,0,597,598,5,7,0,0,598,600,3,96,48,0,599,597,1,0,0,0,600,603,1,
  	0,0,0,601,599,1,0,0,0,601,602,1,0,0,0,602,605,1,0,0,0,603,601,1,0,0,0,
  	604,596,1,0,0,0,604,605,1,0,0,0,605,606,1,0,0,0,606,607,5,5,0,0,607,95,
  	1,0,0,0,608,613,3,98,49,0,609,610,5,30,0,0,610,612,3,98,49,0,611,609,
  	1,0,0,0,612,615,1,0,0,0,613,611,1,0,0,0,613,614,1,0,0,0,614,616,1,0,0,
  	0,615,613,1,0,0,0,616,617,5,31,0,0,617,618,3,58,29,0,618,623,1,0,0,0,
  	619,620,5,32,0,0,620,621,5,31,0,0,621,623,3,58,29,0,622,608,1,0,0,0,622,
  	619,1,0,0,0,623,97,1,0,0,0,624,634,3,100,50,0,625,634,3,102,51,0,626,
  	634,3,104,52,0,627,634,3,110,55,0,628,634,3,112,56,0,629,634,3,114,57,
  	0,630,634,3,116,58,0,631,634,3,118,59,0,632,634,3,120,60,0,633,624,1,
  	0,0,0,633,625,1,0,0,0,633,626,1,0,0,0,633,627,1,0,0,0,633,628,1,0,0,0,
  	633,629,1,0,0,0,633,630,1,0,0,0,633,631,1,0,0,0,633,632,1,0,0,0,634,99,
  	1,0,0,0,635,637,7,0,0,0,636,635,1,0,0,0,636,637,1,0,0,0,637,638,1,0,0,
  	0,638,639,5,88,0,0,639,101,1,0,0,0,640,642,7,0,0,0,641,640,1,0,0,0,641,
  	642,1,0,0,0,642,643,1,0,0,0,643,644,5,89,0,0,644,103,1,0,0,0,645,648,
  	3,106,53,0,646,648,3,108,54,0,647,645,1,0,0,0,647,646,1,0,0,0,648,105,
  	1,0,0,0,649,652,5,90,0,0,650,652,5,79,0,0,651,649,1,0,0,0,651,650,1,0,
  	0,0,652,655,1,0,0,0,653,654,5,1,0,0,654,656,5,90,0,0,655,653,1,0,0,0,
  	655,656,1,0,0,0,656,107,1,0,0,0,657,658,5,80,0,0,658,659,5,1,0,0,659,
  	667,5,90,0,0,660,661,5,81,0,0,661,662,5,1,0,0,662,667,5,90,0,0,663,664,
  	5,82,0,0,664,665,5,1,0,0,665,667,5,90,0,0,666,657,1,0,0,0,666,660,1,0,
  	0,0,666,663,1,0,0,0,667,109,1,0,0,0,668,669,7,1,0,0,669,111,1,0,0,0,670,
  	673,5,62,0,0,671,673,5,63,0,0,672,670,1,0,0,0,672,671,1,0,0,0,673,113,
  	1,0,0,0,674,675,5,64,0,0,675,115,1,0,0,0,676,677,5,90,0,0,677,678,5,1,
  	0,0,678,679,5,65,0,0,679,117,1,0,0,0,680,681,5,79,0,0,681,682,5,1,0,0,
  	682,683,5,66,0,0,683,119,1,0,0,0,684,685,5,80,0,0,685,686,5,1,0,0,686,
  	687,5,67,0,0,687,121,1,0,0,0,688,700,3,124,62,0,689,700,3,126,63,0,690,
  	700,3,128,64,0,691,700,3,130,65,0,692,693,5,42,0,0,693,700,3,122,61,0,
  	694,695,5,91,0,0,695,700,3,122,61,0,696,697,5,68,0,0,697,700,3,122,61,
  	0,698,700,3,144,72,0,699,688,1,0,0,0,699,689,1,0,0,0,699,690,1,0,0,0,
  	699,691,1,0,0,0,699,692,1,0,0,0,699,694,1,0,0,0,699,696,1,0,0,0,699,698,
  	1,0,0,0,700,123,1,0,0,0,701,702,5,78,0,0,702,125,1,0,0,0,703,704,5,34,
  	0,0,704,705,3,122,61,0,705,706,5,95,0,0,706,707,5,90,0,0,707,708,5,35,
  	0,0,708,127,1,0,0,0,709,710,5,38,0,0,710,711,3,122,61,0,711,712,5,95,
  	0,0,712,713,5,90,0,0,713,714,5,39,0,0,714,129,1,0,0,0,715,722,3,132,66,
  	0,716,722,3,134,67,0,717,722,3,136,68,0,718,722,3,138,69,0,719,722,3,
  	140,70,0,720,722,3,142,71,0,721,715,1,0,0,0,721,716,1,0,0,0,721,717,1,
  	0,0,0,721,718,1,0,0,0,721,719,1,0,0,0,721,720,1,0,0,0,722,131,1,0,0,0,
  	723,724,7,2,0,0,724,133,1,0,0,0,725,726,7,3,0,0,726,135,1,0,0,0,727,728,
  	5,74,0,0,728,137,1,0,0,0,729,730,5,75,0,0,730,139,1,0,0,0,731,732,5,76,
  	0,0,732,141,1,0,0,0,733,734,5,77,0,0,734,143,1,0,0,0,735,736,5,94,0,0,
  	736,145,1,0,0,0,64,149,151,159,166,171,176,187,193,205,209,216,219,227,
  	243,255,262,266,272,290,299,304,327,331,344,358,372,382,391,421,428,437,
  	444,449,477,483,496,498,504,509,513,518,522,528,532,546,553,556,565,572,
  	582,601,604,613,622,633,636,641,647,651,655,666,672,699,721
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
    setState(151);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__5)
      | (1ULL << anceParser::T__10)
      | (1ULL << anceParser::T__11))) != 0)) {
      setState(149);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(146);
        variableDeclaration();
        break;
      }

      case 2: {
        setState(147);
        function();
        break;
      }

      case 3: {
        setState(148);
        typeDefinition();
        break;
      }

      default:
        break;
      }
      setState(153);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(154);
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
    setState(159);
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
      setState(156);
      code();
      setState(161);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(162);
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
  enterRule(_localctx, 4, anceParser::RuleVariableDeclaration);
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
    setState(164);
    accessModifier();
    setState(166);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::CONST) {
      setState(165);
      match(anceParser::CONST);
    }
    setState(168);
    match(anceParser::IDENTIFIER);
    setState(171);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__0) {
      setState(169);
      match(anceParser::T__0);
      setState(170);
      type();
    }
    setState(176);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(173);
      assigner();
      setState(174);
      expression(0);
    }
    setState(178);
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
  enterRule(_localctx, 6, anceParser::RuleFunction);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(209);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::FunctionDefinitionContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(180);
      accessModifier();
      setState(181);
      match(anceParser::IDENTIFIER);
      setState(182);
      match(anceParser::T__1);
      setState(183);
      parameters();
      setState(184);
      match(anceParser::T__2);
      setState(187);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == anceParser::T__0) {
        setState(185);
        match(anceParser::T__0);
        setState(186);
        type();
      }
      setState(189);
      match(anceParser::T__3);
      setState(193);
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
        setState(190);
        code();
        setState(195);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(196);
      match(anceParser::T__4);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::ExternFunctionDeclarationContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(198);
      match(anceParser::T__5);
      setState(199);
      match(anceParser::IDENTIFIER);
      setState(200);
      match(anceParser::T__1);
      setState(201);
      parameters();
      setState(202);
      match(anceParser::T__2);
      setState(205);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == anceParser::T__0) {
        setState(203);
        match(anceParser::T__0);
        setState(204);
        type();
      }
      setState(207);
      match(anceParser::SEMICOLON);
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
  enterRule(_localctx, 8, anceParser::RuleParameters);
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
    setState(219);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::IDENTIFIER) {
      setState(211);
      parameter();
      setState(216);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__6) {
        setState(212);
        match(anceParser::T__6);
        setState(213);
        parameter();
        setState(218);
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
  enterRule(_localctx, 10, anceParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(221);
    match(anceParser::IDENTIFIER);
    setState(222);
    match(anceParser::T__0);
    setState(223);
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
  enterRule(_localctx, 12, anceParser::RuleTypeDefinition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(227);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(225);
      defineAlias();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(226);
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
  enterRule(_localctx, 14, anceParser::RuleDefineAlias);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(229);
    accessModifier();
    setState(230);
    match(anceParser::T__7);
    setState(231);
    match(anceParser::IDENTIFIER);
    setState(232);
    match(anceParser::T__8);
    setState(233);
    type();
    setState(234);
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
  enterRule(_localctx, 16, anceParser::RuleStructDefinition);
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
    setState(236);
    accessModifier();
    setState(237);
    match(anceParser::T__9);
    setState(238);
    match(anceParser::IDENTIFIER);
    setState(239);
    match(anceParser::T__3);
    setState(243);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__5)
      | (1ULL << anceParser::T__10)
      | (1ULL << anceParser::T__11))) != 0)) {
      setState(240);
      member();
      setState(245);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(246);
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
  enterRule(_localctx, 18, anceParser::RuleMember);
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
    setState(248);
    accessModifier();
    setState(249);
    match(anceParser::IDENTIFIER);
    setState(250);
    match(anceParser::T__0);
    setState(251);
    type();
    setState(255);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(252);
      assigner();
      setState(253);
      literalExpression();
    }
    setState(257);
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
  enterRule(_localctx, 20, anceParser::RuleAccessModifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(262);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__10: {
        _localctx = _tracker.createInstance<anceParser::PublicContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(259);
        match(anceParser::T__10);
        break;
      }

      case anceParser::T__11: {
        _localctx = _tracker.createInstance<anceParser::PrivateContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(260);
        match(anceParser::T__11);
        break;
      }

      case anceParser::T__5: {
        _localctx = _tracker.createInstance<anceParser::ExternContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(261);
        match(anceParser::T__5);
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
  enterRule(_localctx, 22, anceParser::RuleCode);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(266);
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
        setState(264);
        statement();
        break;
      }

      case anceParser::T__3: {
        enterOuterAlt(_localctx, 2);
        setState(265);
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
  enterRule(_localctx, 24, anceParser::RuleBlock);
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
    setState(268);
    match(anceParser::T__3);
    setState(272);
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
      setState(269);
      code();
      setState(274);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(275);
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
  enterRule(_localctx, 26, anceParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(290);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(277);
      expressionStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(278);
      localVariableDefinition();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(279);
      localReferenceDefinition();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(280);
      dropStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(281);
      assignment();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(282);
      deleteStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(283);
      breakStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(284);
      continueStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(285);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(286);
      assertStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(287);
      ifStatement();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(288);
      whileStatement();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(289);
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
  enterRule(_localctx, 28, anceParser::RuleExpressionStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(292);
    independentExpression();
    setState(293);
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
  enterRule(_localctx, 30, anceParser::RuleLocalVariableDefinition);
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
    setState(295);
    match(anceParser::T__12);
    setState(296);
    match(anceParser::IDENTIFIER);
    setState(299);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__0) {
      setState(297);
      match(anceParser::T__0);
      setState(298);
      type();
    }
    setState(304);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(301);
      assigner();
      setState(302);
      expression(0);
    }
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
  enterRule(_localctx, 32, anceParser::RuleLocalReferenceDefinition);

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
    match(anceParser::T__12);
    setState(309);
    match(anceParser::IDENTIFIER);
    setState(310);
    match(anceParser::T__0);
    setState(311);
    type();
    setState(312);
    bindRef();
    setState(313);
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
  enterRule(_localctx, 34, anceParser::RuleDropStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(315);
    match(anceParser::T__13);
    setState(316);
    match(anceParser::IDENTIFIER);
    setState(317);
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
  enterRule(_localctx, 36, anceParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(319);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->assignable = expression(0);
    setState(320);
    assigner();
    setState(321);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->assigned = expression(0);
    setState(322);
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
  enterRule(_localctx, 38, anceParser::RuleAssigner);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(327);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__14: {
        _localctx = _tracker.createInstance<anceParser::CopyAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(324);
        match(anceParser::T__14);
        break;
      }

      case anceParser::T__15: {
        _localctx = _tracker.createInstance<anceParser::MoveAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(325);
        match(anceParser::T__15);
        break;
      }

      case anceParser::T__16: {
        _localctx = _tracker.createInstance<anceParser::FinalCopyAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(326);
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
  enterRule(_localctx, 40, anceParser::RuleDeleteStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(329);
    match(anceParser::T__17);
    setState(331);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      setState(330);
      match(anceParser::BUFFER);
      break;
    }

    default:
      break;
    }
    setState(333);
    expression(0);
    setState(334);
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
  enterRule(_localctx, 42, anceParser::RuleBreakStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(336);
    match(anceParser::T__18);
    setState(337);
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
  enterRule(_localctx, 44, anceParser::RuleContinueStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(339);
    match(anceParser::T__19);
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
  enterRule(_localctx, 46, anceParser::RuleReturnStatement);
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
    setState(342);
    match(anceParser::T__20);
    setState(344);
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
      setState(343);
      expression(0);
    }
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
  enterRule(_localctx, 48, anceParser::RuleAssertStatement);

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
    match(anceParser::T__21);
    setState(349);
    expression(0);
    setState(350);
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
  enterRule(_localctx, 50, anceParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(352);
    match(anceParser::T__22);
    setState(353);
    expression(0);
    setState(354);
    match(anceParser::T__23);
    setState(355);
    antlrcpp::downCast<IfStatementContext *>(_localctx)->ifBlock = code();
    setState(358);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      setState(356);
      match(anceParser::T__24);
      setState(357);
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
  enterRule(_localctx, 52, anceParser::RuleWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(360);
    match(anceParser::T__25);
    setState(361);
    expression(0);
    setState(362);
    match(anceParser::T__26);
    setState(363);
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
  enterRule(_localctx, 54, anceParser::RuleMatchStatement);
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
    setState(365);
    match(anceParser::T__27);
    setState(366);
    expression(0);
    setState(367);
    match(anceParser::T__28);
    setState(368);
    match(anceParser::T__3);
    setState(372);
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
      setState(369);
      matchCase();
      setState(374);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(375);
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
  enterRule(_localctx, 56, anceParser::RuleMatchCase);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(391);
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
        setState(377);
        literalExpression();
        setState(382);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__29) {
          setState(378);
          match(anceParser::T__29);
          setState(379);
          literalExpression();
          setState(384);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(385);
        match(anceParser::T__30);
        setState(386);
        code();
        break;
      }

      case anceParser::T__31: {
        _localctx = _tracker.createInstance<anceParser::DefaultCaseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(388);
        match(anceParser::T__31);
        setState(389);
        match(anceParser::T__30);
        setState(390);
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
  size_t startState = 58;
  enterRecursionRule(_localctx, 58, anceParser::RuleExpression, precedence);

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
    setState(449);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<VariableContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(394);
      variableAccess();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<AllocContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(395);
      allocation();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<LiteralContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(396);
      literalExpression();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<AddressOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(397);
      addressof();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<RefContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(398);
      bindRef();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SizeOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(399);
      sizeofType();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SizeOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(400);
      sizeofExpression();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<IndependentContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(401);
      independentExpression();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ParenthesisContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(402);
      match(anceParser::T__1);
      setState(403);
      expression(0);
      setState(404);
      match(anceParser::T__2);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<UnaryOperationContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(406);
      unaryOperator();
      setState(407);
      expression(13);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<IfExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(409);
      match(anceParser::T__22);
      setState(410);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->condition = expression(0);
      setState(411);
      match(anceParser::T__23);
      setState(412);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->thenBlock = expression(0);
      setState(413);
      match(anceParser::T__24);
      setState(414);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->elseBlock = expression(4);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<MatchContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(416);
      matchExpression();
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<VectorDefinitionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(417);
      match(anceParser::T__37);
      setState(421);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
      case 1: {
        setState(418);
        type();
        setState(419);
        match(anceParser::T__29);
        break;
      }

      default:
        break;
      }
      setState(423);
      expression(0);
      setState(428);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__6) {
        setState(424);
        match(anceParser::T__6);
        setState(425);
        expression(0);
        setState(430);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(431);
      match(anceParser::T__38);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<ArrayDefinitionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(433);
      match(anceParser::T__33);
      setState(437);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
      case 1: {
        setState(434);
        type();
        setState(435);
        match(anceParser::T__29);
        break;
      }

      default:
        break;
      }
      setState(439);
      expression(0);
      setState(444);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__6) {
        setState(440);
        match(anceParser::T__6);
        setState(441);
        expression(0);
        setState(446);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(447);
      match(anceParser::T__34);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(498);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(496);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(451);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(452);
          binaryOperatorMultiplicative();
          setState(453);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(13);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(455);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(456);
          binaryOperatorAdditive();
          setState(457);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(12);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(459);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(460);
          binaryOperatorBitwise();
          setState(461);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(11);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(463);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(464);
          binaryOperatorShift();
          setState(465);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(10);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(467);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(468);
          binaryOperatorRelational();
          setState(469);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(9);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(471);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(472);
          binaryOperatorEquality();
          setState(473);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(8);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<LogicalAndContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(475);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(477);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == anceParser::NOT) {
            setState(476);
            match(anceParser::NOT);
          }
          setState(479);
          match(anceParser::T__35);
          setState(480);
          antlrcpp::downCast<LogicalAndContext *>(_localctx)->right = expression(7);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<LogicalOrContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(481);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(483);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == anceParser::NOT) {
            setState(482);
            match(anceParser::NOT);
          }
          setState(485);
          match(anceParser::T__36);
          setState(486);
          antlrcpp::downCast<LogicalOrContext *>(_localctx)->right = expression(6);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<IndirectionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(487);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(488);
          match(anceParser::T__32);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<SubscriptContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->indexed = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(489);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(490);
          match(anceParser::T__33);
          setState(491);
          antlrcpp::downCast<SubscriptContext *>(_localctx)->index = expression(0);
          setState(492);
          match(anceParser::T__34);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->accessed = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(494);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(495);
          match(anceParser::IDENTIFIER);
          break;
        }

        default:
          break;
        } 
      }
      setState(500);
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
  enterRule(_localctx, 60, anceParser::RuleUnaryOperator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(504);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::NOT: {
        _localctx = _tracker.createInstance<anceParser::NotContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(501);
        match(anceParser::NOT);
        break;
      }

      case anceParser::T__39: {
        _localctx = _tracker.createInstance<anceParser::BitwiseNotContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(502);
        match(anceParser::T__39);
        break;
      }

      case anceParser::T__40: {
        _localctx = _tracker.createInstance<anceParser::NegationContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(503);
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
  enterRule(_localctx, 62, anceParser::RuleBinaryOperatorMultiplicative);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(509);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__41: {
        _localctx = _tracker.createInstance<anceParser::MultiplicationContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(506);
        match(anceParser::T__41);
        break;
      }

      case anceParser::T__42: {
        _localctx = _tracker.createInstance<anceParser::DivisionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(507);
        match(anceParser::T__42);
        break;
      }

      case anceParser::T__43: {
        _localctx = _tracker.createInstance<anceParser::RemainderContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(508);
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
  enterRule(_localctx, 64, anceParser::RuleBinaryOperatorAdditive);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(513);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__44: {
        _localctx = _tracker.createInstance<anceParser::AdditionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(511);
        match(anceParser::T__44);
        break;
      }

      case anceParser::T__40: {
        _localctx = _tracker.createInstance<anceParser::SubtractionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(512);
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
  enterRule(_localctx, 66, anceParser::RuleBinaryOperatorBitwise);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(518);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__45: {
        _localctx = _tracker.createInstance<anceParser::BitwiseAndContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(515);
        match(anceParser::T__45);
        break;
      }

      case anceParser::T__46: {
        _localctx = _tracker.createInstance<anceParser::BitwiseOrContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(516);
        match(anceParser::T__46);
        break;
      }

      case anceParser::T__47: {
        _localctx = _tracker.createInstance<anceParser::BitwiseXorContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(517);
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
  enterRule(_localctx, 68, anceParser::RuleBinaryOperatorShift);

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
      case anceParser::T__48: {
        _localctx = _tracker.createInstance<anceParser::LeftShiftContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(520);
        match(anceParser::T__48);
        break;
      }

      case anceParser::T__49: {
        _localctx = _tracker.createInstance<anceParser::RightShiftContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(521);
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
  enterRule(_localctx, 70, anceParser::RuleBinaryOperatorRelational);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(528);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__37: {
        _localctx = _tracker.createInstance<anceParser::LessThanContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(524);
        match(anceParser::T__37);
        break;
      }

      case anceParser::T__50: {
        _localctx = _tracker.createInstance<anceParser::LessThanOrEqualContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(525);
        match(anceParser::T__50);
        break;
      }

      case anceParser::T__38: {
        _localctx = _tracker.createInstance<anceParser::GreaterThanContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(526);
        match(anceParser::T__38);
        break;
      }

      case anceParser::T__51: {
        _localctx = _tracker.createInstance<anceParser::GreaterThanOrEqualContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(527);
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
  enterRule(_localctx, 72, anceParser::RuleBinaryOperatorEquality);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(532);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__52: {
        _localctx = _tracker.createInstance<anceParser::EqualContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(530);
        match(anceParser::T__52);
        break;
      }

      case anceParser::T__53: {
        _localctx = _tracker.createInstance<anceParser::NotEqualContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(531);
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
  enterRule(_localctx, 74, anceParser::RuleIndependentExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(534);
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
  enterRule(_localctx, 76, anceParser::RuleFunctionCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(546);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(536);
      match(anceParser::IDENTIFIER);
      setState(537);
      match(anceParser::T__1);
      setState(538);
      arguments();
      setState(539);
      match(anceParser::T__2);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(541);
      type();
      setState(542);
      match(anceParser::T__1);
      setState(543);
      arguments();
      setState(544);
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
  enterRule(_localctx, 78, anceParser::RuleArguments);
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
    setState(556);
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
      setState(548);
      expression(0);
      setState(553);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__6) {
        setState(549);
        match(anceParser::T__6);
        setState(550);
        expression(0);
        setState(555);
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
  enterRule(_localctx, 80, anceParser::RuleVariableAccess);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(558);
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
  enterRule(_localctx, 82, anceParser::RuleAllocation);
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
    setState(560);
    match(anceParser::T__54);
    setState(565);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__33) {
      setState(561);
      match(anceParser::T__33);
      setState(562);
      expression(0);
      setState(563);
      match(anceParser::T__34);
    }
    setState(567);
    allocator();
    setState(568);
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
  enterRule(_localctx, 84, anceParser::RuleAllocator);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(572);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__55: {
        _localctx = _tracker.createInstance<anceParser::DynamicContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(570);
        match(anceParser::T__55);
        break;
      }

      case anceParser::T__56: {
        _localctx = _tracker.createInstance<anceParser::AutomaticContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(571);
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
  enterRule(_localctx, 86, anceParser::RuleAddressof);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(574);
    match(anceParser::T__57);
    setState(575);
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
  enterRule(_localctx, 88, anceParser::RuleBindRef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(582);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::BindReferenceContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(577);
      match(anceParser::T__58);
      setState(578);
      expression(0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::BindReferenceToAddressContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(579);
      match(anceParser::T__58);
      setState(580);
      match(anceParser::T__59);
      setState(581);
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
  enterRule(_localctx, 90, anceParser::RuleSizeofType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(584);
    match(anceParser::T__60);
    setState(585);
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
  enterRule(_localctx, 92, anceParser::RuleSizeofExpression);

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
    match(anceParser::T__60);
    setState(588);
    match(anceParser::T__1);
    setState(589);
    expression(0);
    setState(590);
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
  enterRule(_localctx, 94, anceParser::RuleMatchExpression);
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
    setState(592);
    match(anceParser::T__27);
    setState(593);
    antlrcpp::downCast<MatchExpressionContext *>(_localctx)->condition = expression(0);
    setState(594);
    match(anceParser::T__28);
    setState(595);
    match(anceParser::T__3);
    setState(604);
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
      setState(596);
      matchExpressionCase();
      setState(601);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__6) {
        setState(597);
        match(anceParser::T__6);
        setState(598);
        matchExpressionCase();
        setState(603);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(606);
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
  enterRule(_localctx, 96, anceParser::RuleMatchExpressionCase);
  size_t _la = 0;

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
        setState(608);
        literalExpression();
        setState(613);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__29) {
          setState(609);
          match(anceParser::T__29);
          setState(610);
          literalExpression();
          setState(615);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(616);
        match(anceParser::T__30);
        setState(617);
        expression(0);
        break;
      }

      case anceParser::T__31: {
        _localctx = _tracker.createInstance<anceParser::DefaultExpressionCaseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(619);
        match(anceParser::T__31);
        setState(620);
        match(anceParser::T__30);
        setState(621);
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
  enterRule(_localctx, 98, anceParser::RuleLiteralExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(633);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(624);
      stringLiteral();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(625);
      charLiteral();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(626);
      integerLiteral();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(627);
      floatingPointLiteral();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(628);
      booleanLiteral();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(629);
      nullLiteral();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(630);
      sizeLiteral();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(631);
      diffLiteral();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(632);
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
  enterRule(_localctx, 100, anceParser::RuleStringLiteral);
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
    setState(636);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER

    || _la == anceParser::IDENTIFIER) {
      setState(635);
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
    setState(638);
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
  enterRule(_localctx, 102, anceParser::RuleCharLiteral);
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
    setState(641);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER

    || _la == anceParser::IDENTIFIER) {
      setState(640);
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
    setState(643);
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
  enterRule(_localctx, 104, anceParser::RuleIntegerLiteral);

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
    switch (_input->LA(1)) {
      case anceParser::SIGNED_INTEGER:
      case anceParser::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(645);
        normalInteger();
        break;
      }

      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(646);
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
  enterRule(_localctx, 106, anceParser::RuleNormalInteger);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(651);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::INTEGER: {
        setState(649);
        antlrcpp::downCast<NormalIntegerContext *>(_localctx)->uvalue = match(anceParser::INTEGER);
        break;
      }

      case anceParser::SIGNED_INTEGER: {
        setState(650);
        antlrcpp::downCast<NormalIntegerContext *>(_localctx)->svalue = match(anceParser::SIGNED_INTEGER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(655);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
    case 1: {
      setState(653);
      match(anceParser::T__0);
      setState(654);
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
  enterRule(_localctx, 108, anceParser::RuleSpecialInteger);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(666);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::HEX_INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(657);
        match(anceParser::HEX_INTEGER);
        setState(658);
        match(anceParser::T__0);
        setState(659);
        antlrcpp::downCast<SpecialIntegerContext *>(_localctx)->width = match(anceParser::INTEGER);
        break;
      }

      case anceParser::BIN_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(660);
        match(anceParser::BIN_INTEGER);
        setState(661);
        match(anceParser::T__0);
        setState(662);
        antlrcpp::downCast<SpecialIntegerContext *>(_localctx)->width = match(anceParser::INTEGER);
        break;
      }

      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(663);
        match(anceParser::OCT_INTEGER);
        setState(664);
        match(anceParser::T__0);
        setState(665);
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
  enterRule(_localctx, 110, anceParser::RuleFloatingPointLiteral);
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
    setState(668);
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
  enterRule(_localctx, 112, anceParser::RuleBooleanLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(672);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__61: {
        _localctx = _tracker.createInstance<anceParser::TrueContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(670);
        match(anceParser::T__61);
        break;
      }

      case anceParser::T__62: {
        _localctx = _tracker.createInstance<anceParser::FalseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(671);
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
  enterRule(_localctx, 114, anceParser::RuleNullLiteral);

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
    setState(674);
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
  enterRule(_localctx, 116, anceParser::RuleSizeLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(676);
    match(anceParser::INTEGER);
    setState(677);
    match(anceParser::T__0);
    setState(678);
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
  enterRule(_localctx, 118, anceParser::RuleDiffLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(680);
    match(anceParser::SIGNED_INTEGER);
    setState(681);
    match(anceParser::T__0);
    setState(682);
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
  enterRule(_localctx, 120, anceParser::RuleUiptrLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(684);
    match(anceParser::HEX_INTEGER);
    setState(685);
    match(anceParser::T__0);
    setState(686);
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
  enterRule(_localctx, 122, anceParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(699);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::NATIVE_INTEGER_TYPE: {
        _localctx = _tracker.createInstance<anceParser::IntegerContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(688);
        integerType();
        break;
      }

      case anceParser::T__33: {
        _localctx = _tracker.createInstance<anceParser::ArrayContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(689);
        arrayType();
        break;
      }

      case anceParser::T__37: {
        _localctx = _tracker.createInstance<anceParser::VectorContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(690);
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
        setState(691);
        keywordType();
        break;
      }

      case anceParser::T__41: {
        _localctx = _tracker.createInstance<anceParser::PointerContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(692);
        match(anceParser::T__41);
        setState(693);
        type();
        break;
      }

      case anceParser::BUFFER: {
        _localctx = _tracker.createInstance<anceParser::BufferContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(694);
        match(anceParser::BUFFER);
        setState(695);
        type();
        break;
      }

      case anceParser::T__67: {
        _localctx = _tracker.createInstance<anceParser::ReferenceContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(696);
        match(anceParser::T__67);
        setState(697);
        type();
        break;
      }

      case anceParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<anceParser::CustomContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(698);
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
  enterRule(_localctx, 124, anceParser::RuleIntegerType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(701);
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
  enterRule(_localctx, 126, anceParser::RuleArrayType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(703);
    match(anceParser::T__33);
    setState(704);
    type();
    setState(705);
    match(anceParser::SEMICOLON);
    setState(706);
    match(anceParser::INTEGER);
    setState(707);
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
  enterRule(_localctx, 128, anceParser::RuleVectorType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(709);
    match(anceParser::T__37);
    setState(710);
    type();
    setState(711);
    match(anceParser::SEMICOLON);
    setState(712);
    match(anceParser::INTEGER);
    setState(713);
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
  enterRule(_localctx, 130, anceParser::RuleKeywordType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(721);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__68:
      case anceParser::T__69:
      case anceParser::T__70:
      case anceParser::T__71: {
        enterOuterAlt(_localctx, 1);
        setState(715);
        floatingPointType();
        break;
      }

      case anceParser::T__64:
      case anceParser::T__65:
      case anceParser::T__66:
      case anceParser::T__72: {
        enterOuterAlt(_localctx, 2);
        setState(716);
        targetDependentType();
        break;
      }

      case anceParser::T__73: {
        enterOuterAlt(_localctx, 3);
        setState(717);
        booleanType();
        break;
      }

      case anceParser::T__74: {
        enterOuterAlt(_localctx, 4);
        setState(718);
        charType();
        break;
      }

      case anceParser::T__75: {
        enterOuterAlt(_localctx, 5);
        setState(719);
        nullPointerType();
        break;
      }

      case anceParser::T__76: {
        enterOuterAlt(_localctx, 6);
        setState(720);
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
  enterRule(_localctx, 132, anceParser::RuleFloatingPointType);
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
    setState(723);
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
  enterRule(_localctx, 134, anceParser::RuleTargetDependentType);
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
    setState(725);
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
  enterRule(_localctx, 136, anceParser::RuleBooleanType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(727);
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
  enterRule(_localctx, 138, anceParser::RuleCharType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(729);
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
  enterRule(_localctx, 140, anceParser::RuleNullPointerType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(731);
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
  enterRule(_localctx, 142, anceParser::RuleVoidType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(733);
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
  enterRule(_localctx, 144, anceParser::RuleCustomType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(735);
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
    case 29: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

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
