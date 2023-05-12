
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
      "loopStatement", "matchStatement", "matchCase", "expression", "unaryOperator", 
      "binaryOperatorMultiplicative", "binaryOperatorAdditive", "binaryOperatorBitwise", 
      "binaryOperatorShift", "binaryOperatorRelational", "binaryOperatorEquality", 
      "independentExpression", "functionCall", "arguments", "variableAccess", 
      "allocation", "allocator", "addressof", "bindRef", "sizeofType", "sizeofExpression", 
      "matchExpression", "matchExpressionCase", "literalExpression", "stringLiteral", 
      "charLiteral", "integerLiteral", "normalInteger", "specialInteger", 
      "floatingPointLiteral", "booleanLiteral", "nullLiteral", "sizeLiteral", 
      "diffLiteral", "uiptrLiteral", "type", "integerType", "arrayType", 
      "vectorType", "keywordType", "floatingPointType", "targetDependentType", 
      "booleanType", "charType", "nullPointerType", "voidType", "customType"
    },
    std::vector<std::string>{
      "", "':'", "'('", "')'", "'{'", "'}'", "','", "'define'", "'alias'", 
      "'struct'", "'public'", "'private'", "'extern'", "'let'", "'drop'", 
      "'<:'", "'<-'", "':='", "'delete'", "'break'", "'continue'", "'return'", 
      "'assert'", "'if'", "'then'", "'else'", "'while'", "'do'", "'loop'", 
      "'match'", "'with'", "'|'", "'=>'", "'default'", "'.'", "'['", "']'", 
      "'and'", "'or'", "'<'", "'>'", "'<not>'", "'-'", "'*'", "'/'", "'%'", 
      "'+'", "'<and>'", "'<or>'", "'<xor>'", "'<sl>'", "'<sr>'", "'<='", 
      "'>='", "'=='", "'/='", "'new'", "'dynamic'", "'automatic'", "'addressof'", 
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
      "", "", "", "", "", "", "", "", "", "", "", "NATIVE_INTEGER_TYPE", 
      "SIGNED_INTEGER", "HEX_INTEGER", "BIN_INTEGER", "OCT_INTEGER", "HALF", 
      "SINGLE", "DOUBLE", "QUAD", "DECIMAL", "STRING", "CHAR", "INTEGER", 
      "BUFFER", "CONST", "NOT", "IDENTIFIER", "SEMICOLON", "WHITESPACE", 
      "BLOCK_COMMENT", "LINE_COMMENT", "ERROR_CHAR"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,100,745,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,7,
  	70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,2,76,7,76,1,0,1,
  	0,1,0,1,1,5,1,159,8,1,10,1,12,1,162,9,1,1,1,1,1,1,2,5,2,167,8,2,10,2,
  	12,2,170,9,2,1,3,1,3,1,3,3,3,175,8,3,1,4,1,4,3,4,179,8,4,1,4,1,4,1,4,
  	3,4,184,8,4,1,4,1,4,1,4,3,4,189,8,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,
  	5,3,5,200,8,5,1,5,1,5,3,5,204,8,5,1,6,1,6,5,6,208,8,6,10,6,12,6,211,9,
  	6,1,6,1,6,1,7,1,7,1,7,5,7,218,8,7,10,7,12,7,221,9,7,3,7,223,8,7,1,8,1,
  	8,1,8,1,8,1,9,1,9,3,9,231,8,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,11,
  	1,11,1,11,1,11,1,11,5,11,245,8,11,10,11,12,11,248,9,11,1,11,1,11,1,12,
  	1,12,1,12,1,12,1,12,1,12,1,12,3,12,259,8,12,1,12,1,12,1,13,1,13,1,13,
  	3,13,266,8,13,1,14,1,14,3,14,270,8,14,1,15,1,15,5,15,274,8,15,10,15,12,
  	15,277,9,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,1,16,3,16,295,8,16,1,17,1,17,1,17,1,18,1,18,1,18,1,
  	18,3,18,304,8,18,1,18,1,18,1,18,3,18,309,8,18,1,18,1,18,1,19,1,19,1,19,
  	1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,22,
  	1,22,1,22,3,22,332,8,22,1,23,1,23,3,23,336,8,23,1,23,1,23,1,23,1,24,1,
  	24,1,24,1,25,1,25,1,25,1,26,1,26,3,26,349,8,26,1,26,1,26,1,27,1,27,1,
  	27,1,27,1,28,1,28,1,28,1,28,1,28,1,28,3,28,363,8,28,1,29,1,29,1,29,1,
  	29,1,29,1,30,1,30,1,30,1,31,1,31,1,31,1,31,1,31,5,31,378,8,31,10,31,12,
  	31,381,9,31,1,31,1,31,1,32,1,32,1,32,5,32,388,8,32,10,32,12,32,391,9,
  	32,1,32,1,32,1,32,1,32,1,32,1,32,3,32,399,8,32,1,33,1,33,1,33,1,33,1,
  	33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,
  	33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,3,33,429,8,33,1,33,1,
  	33,1,33,5,33,434,8,33,10,33,12,33,437,9,33,1,33,1,33,1,33,1,33,1,33,1,
  	33,3,33,445,8,33,1,33,1,33,1,33,5,33,450,8,33,10,33,12,33,453,9,33,1,
  	33,1,33,3,33,457,8,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,
  	33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,
  	33,1,33,1,33,3,33,485,8,33,1,33,1,33,1,33,1,33,3,33,491,8,33,1,33,1,33,
  	1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,1,33,5,33,504,8,33,10,33,12,33,
  	507,9,33,1,34,1,34,1,34,3,34,512,8,34,1,35,1,35,1,35,3,35,517,8,35,1,
  	36,1,36,3,36,521,8,36,1,37,1,37,1,37,3,37,526,8,37,1,38,1,38,3,38,530,
  	8,38,1,39,1,39,1,39,1,39,3,39,536,8,39,1,40,1,40,3,40,540,8,40,1,41,1,
  	41,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,3,42,554,8,42,1,
  	43,1,43,1,43,5,43,559,8,43,10,43,12,43,562,9,43,3,43,564,8,43,1,44,1,
  	44,1,45,1,45,1,45,1,45,1,45,3,45,573,8,45,1,45,1,45,1,45,1,46,1,46,3,
  	46,580,8,46,1,47,1,47,1,47,1,48,1,48,1,48,1,48,1,48,3,48,590,8,48,1,49,
  	1,49,1,49,1,50,1,50,1,50,1,50,1,50,1,51,1,51,1,51,1,51,1,51,1,51,1,51,
  	5,51,607,8,51,10,51,12,51,610,9,51,3,51,612,8,51,1,51,1,51,1,52,1,52,
  	1,52,5,52,619,8,52,10,52,12,52,622,9,52,1,52,1,52,1,52,1,52,1,52,1,52,
  	3,52,630,8,52,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,3,53,641,8,
  	53,1,54,3,54,644,8,54,1,54,1,54,1,55,3,55,649,8,55,1,55,1,55,1,56,1,56,
  	3,56,655,8,56,1,57,1,57,3,57,659,8,57,1,57,1,57,3,57,663,8,57,1,58,1,
  	58,1,58,1,58,1,58,1,58,1,58,1,58,1,58,3,58,674,8,58,1,59,1,59,1,60,1,
  	60,3,60,680,8,60,1,61,1,61,1,62,1,62,1,62,1,62,1,63,1,63,1,63,1,63,1,
  	64,1,64,1,64,1,64,1,65,1,65,1,65,1,65,1,65,1,65,1,65,1,65,1,65,1,65,1,
  	65,3,65,707,8,65,1,66,1,66,1,67,1,67,1,67,1,67,1,67,1,67,1,68,1,68,1,
  	68,1,68,1,68,1,68,1,69,1,69,1,69,1,69,1,69,1,69,3,69,729,8,69,1,70,1,
  	70,1,71,1,71,1,72,1,72,1,73,1,73,1,74,1,74,1,75,1,75,1,76,1,76,1,76,0,
  	1,66,77,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,
  	44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,
  	90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,
  	128,130,132,134,136,138,140,142,144,146,148,150,152,0,4,2,0,91,91,95,
  	95,1,0,84,87,1,0,70,73,2,0,66,68,74,74,789,0,154,1,0,0,0,2,160,1,0,0,
  	0,4,168,1,0,0,0,6,174,1,0,0,0,8,176,1,0,0,0,10,192,1,0,0,0,12,205,1,0,
  	0,0,14,222,1,0,0,0,16,224,1,0,0,0,18,230,1,0,0,0,20,232,1,0,0,0,22,239,
  	1,0,0,0,24,251,1,0,0,0,26,265,1,0,0,0,28,269,1,0,0,0,30,271,1,0,0,0,32,
  	294,1,0,0,0,34,296,1,0,0,0,36,299,1,0,0,0,38,312,1,0,0,0,40,319,1,0,0,
  	0,42,323,1,0,0,0,44,331,1,0,0,0,46,333,1,0,0,0,48,340,1,0,0,0,50,343,
  	1,0,0,0,52,346,1,0,0,0,54,352,1,0,0,0,56,356,1,0,0,0,58,364,1,0,0,0,60,
  	369,1,0,0,0,62,372,1,0,0,0,64,398,1,0,0,0,66,456,1,0,0,0,68,511,1,0,0,
  	0,70,516,1,0,0,0,72,520,1,0,0,0,74,525,1,0,0,0,76,529,1,0,0,0,78,535,
  	1,0,0,0,80,539,1,0,0,0,82,541,1,0,0,0,84,553,1,0,0,0,86,563,1,0,0,0,88,
  	565,1,0,0,0,90,567,1,0,0,0,92,579,1,0,0,0,94,581,1,0,0,0,96,589,1,0,0,
  	0,98,591,1,0,0,0,100,594,1,0,0,0,102,599,1,0,0,0,104,629,1,0,0,0,106,
  	640,1,0,0,0,108,643,1,0,0,0,110,648,1,0,0,0,112,654,1,0,0,0,114,658,1,
  	0,0,0,116,673,1,0,0,0,118,675,1,0,0,0,120,679,1,0,0,0,122,681,1,0,0,0,
  	124,683,1,0,0,0,126,687,1,0,0,0,128,691,1,0,0,0,130,706,1,0,0,0,132,708,
  	1,0,0,0,134,710,1,0,0,0,136,716,1,0,0,0,138,728,1,0,0,0,140,730,1,0,0,
  	0,142,732,1,0,0,0,144,734,1,0,0,0,146,736,1,0,0,0,148,738,1,0,0,0,150,
  	740,1,0,0,0,152,742,1,0,0,0,154,155,3,4,2,0,155,156,5,0,0,1,156,1,1,0,
  	0,0,157,159,3,28,14,0,158,157,1,0,0,0,159,162,1,0,0,0,160,158,1,0,0,0,
  	160,161,1,0,0,0,161,163,1,0,0,0,162,160,1,0,0,0,163,164,5,0,0,1,164,3,
  	1,0,0,0,165,167,3,6,3,0,166,165,1,0,0,0,167,170,1,0,0,0,168,166,1,0,0,
  	0,168,169,1,0,0,0,169,5,1,0,0,0,170,168,1,0,0,0,171,175,3,8,4,0,172,175,
  	3,10,5,0,173,175,3,18,9,0,174,171,1,0,0,0,174,172,1,0,0,0,174,173,1,0,
  	0,0,175,7,1,0,0,0,176,178,3,26,13,0,177,179,5,93,0,0,178,177,1,0,0,0,
  	178,179,1,0,0,0,179,180,1,0,0,0,180,183,5,95,0,0,181,182,5,1,0,0,182,
  	184,3,130,65,0,183,181,1,0,0,0,183,184,1,0,0,0,184,188,1,0,0,0,185,186,
  	3,44,22,0,186,187,3,66,33,0,187,189,1,0,0,0,188,185,1,0,0,0,188,189,1,
  	0,0,0,189,190,1,0,0,0,190,191,5,96,0,0,191,9,1,0,0,0,192,193,3,26,13,
  	0,193,194,5,95,0,0,194,195,5,2,0,0,195,196,3,14,7,0,196,199,5,3,0,0,197,
  	198,5,1,0,0,198,200,3,130,65,0,199,197,1,0,0,0,199,200,1,0,0,0,200,203,
  	1,0,0,0,201,204,3,12,6,0,202,204,5,96,0,0,203,201,1,0,0,0,203,202,1,0,
  	0,0,204,11,1,0,0,0,205,209,5,4,0,0,206,208,3,28,14,0,207,206,1,0,0,0,
  	208,211,1,0,0,0,209,207,1,0,0,0,209,210,1,0,0,0,210,212,1,0,0,0,211,209,
  	1,0,0,0,212,213,5,5,0,0,213,13,1,0,0,0,214,219,3,16,8,0,215,216,5,6,0,
  	0,216,218,3,16,8,0,217,215,1,0,0,0,218,221,1,0,0,0,219,217,1,0,0,0,219,
  	220,1,0,0,0,220,223,1,0,0,0,221,219,1,0,0,0,222,214,1,0,0,0,222,223,1,
  	0,0,0,223,15,1,0,0,0,224,225,5,95,0,0,225,226,5,1,0,0,226,227,3,130,65,
  	0,227,17,1,0,0,0,228,231,3,20,10,0,229,231,3,22,11,0,230,228,1,0,0,0,
  	230,229,1,0,0,0,231,19,1,0,0,0,232,233,3,26,13,0,233,234,5,7,0,0,234,
  	235,5,95,0,0,235,236,5,8,0,0,236,237,3,130,65,0,237,238,5,96,0,0,238,
  	21,1,0,0,0,239,240,3,26,13,0,240,241,5,9,0,0,241,242,5,95,0,0,242,246,
  	5,4,0,0,243,245,3,24,12,0,244,243,1,0,0,0,245,248,1,0,0,0,246,244,1,0,
  	0,0,246,247,1,0,0,0,247,249,1,0,0,0,248,246,1,0,0,0,249,250,5,5,0,0,250,
  	23,1,0,0,0,251,252,3,26,13,0,252,253,5,95,0,0,253,254,5,1,0,0,254,258,
  	3,130,65,0,255,256,3,44,22,0,256,257,3,106,53,0,257,259,1,0,0,0,258,255,
  	1,0,0,0,258,259,1,0,0,0,259,260,1,0,0,0,260,261,5,96,0,0,261,25,1,0,0,
  	0,262,266,5,10,0,0,263,266,5,11,0,0,264,266,5,12,0,0,265,262,1,0,0,0,
  	265,263,1,0,0,0,265,264,1,0,0,0,266,27,1,0,0,0,267,270,3,32,16,0,268,
  	270,3,30,15,0,269,267,1,0,0,0,269,268,1,0,0,0,270,29,1,0,0,0,271,275,
  	5,4,0,0,272,274,3,28,14,0,273,272,1,0,0,0,274,277,1,0,0,0,275,273,1,0,
  	0,0,275,276,1,0,0,0,276,278,1,0,0,0,277,275,1,0,0,0,278,279,5,5,0,0,279,
  	31,1,0,0,0,280,295,3,34,17,0,281,295,3,36,18,0,282,295,3,38,19,0,283,
  	295,3,40,20,0,284,295,3,42,21,0,285,295,3,46,23,0,286,295,3,48,24,0,287,
  	295,3,50,25,0,288,295,3,52,26,0,289,295,3,54,27,0,290,295,3,56,28,0,291,
  	295,3,58,29,0,292,295,3,60,30,0,293,295,3,62,31,0,294,280,1,0,0,0,294,
  	281,1,0,0,0,294,282,1,0,0,0,294,283,1,0,0,0,294,284,1,0,0,0,294,285,1,
  	0,0,0,294,286,1,0,0,0,294,287,1,0,0,0,294,288,1,0,0,0,294,289,1,0,0,0,
  	294,290,1,0,0,0,294,291,1,0,0,0,294,292,1,0,0,0,294,293,1,0,0,0,295,33,
  	1,0,0,0,296,297,3,82,41,0,297,298,5,96,0,0,298,35,1,0,0,0,299,300,5,13,
  	0,0,300,303,5,95,0,0,301,302,5,1,0,0,302,304,3,130,65,0,303,301,1,0,0,
  	0,303,304,1,0,0,0,304,308,1,0,0,0,305,306,3,44,22,0,306,307,3,66,33,0,
  	307,309,1,0,0,0,308,305,1,0,0,0,308,309,1,0,0,0,309,310,1,0,0,0,310,311,
  	5,96,0,0,311,37,1,0,0,0,312,313,5,13,0,0,313,314,5,95,0,0,314,315,5,1,
  	0,0,315,316,3,130,65,0,316,317,3,96,48,0,317,318,5,96,0,0,318,39,1,0,
  	0,0,319,320,5,14,0,0,320,321,5,95,0,0,321,322,5,96,0,0,322,41,1,0,0,0,
  	323,324,3,66,33,0,324,325,3,44,22,0,325,326,3,66,33,0,326,327,5,96,0,
  	0,327,43,1,0,0,0,328,332,5,15,0,0,329,332,5,16,0,0,330,332,5,17,0,0,331,
  	328,1,0,0,0,331,329,1,0,0,0,331,330,1,0,0,0,332,45,1,0,0,0,333,335,5,
  	18,0,0,334,336,5,92,0,0,335,334,1,0,0,0,335,336,1,0,0,0,336,337,1,0,0,
  	0,337,338,3,66,33,0,338,339,5,96,0,0,339,47,1,0,0,0,340,341,5,19,0,0,
  	341,342,5,96,0,0,342,49,1,0,0,0,343,344,5,20,0,0,344,345,5,96,0,0,345,
  	51,1,0,0,0,346,348,5,21,0,0,347,349,3,66,33,0,348,347,1,0,0,0,348,349,
  	1,0,0,0,349,350,1,0,0,0,350,351,5,96,0,0,351,53,1,0,0,0,352,353,5,22,
  	0,0,353,354,3,66,33,0,354,355,5,96,0,0,355,55,1,0,0,0,356,357,5,23,0,
  	0,357,358,3,66,33,0,358,359,5,24,0,0,359,362,3,28,14,0,360,361,5,25,0,
  	0,361,363,3,28,14,0,362,360,1,0,0,0,362,363,1,0,0,0,363,57,1,0,0,0,364,
  	365,5,26,0,0,365,366,3,66,33,0,366,367,5,27,0,0,367,368,3,28,14,0,368,
  	59,1,0,0,0,369,370,5,28,0,0,370,371,3,28,14,0,371,61,1,0,0,0,372,373,
  	5,29,0,0,373,374,3,66,33,0,374,375,5,30,0,0,375,379,5,4,0,0,376,378,3,
  	64,32,0,377,376,1,0,0,0,378,381,1,0,0,0,379,377,1,0,0,0,379,380,1,0,0,
  	0,380,382,1,0,0,0,381,379,1,0,0,0,382,383,5,5,0,0,383,63,1,0,0,0,384,
  	389,3,106,53,0,385,386,5,31,0,0,386,388,3,106,53,0,387,385,1,0,0,0,388,
  	391,1,0,0,0,389,387,1,0,0,0,389,390,1,0,0,0,390,392,1,0,0,0,391,389,1,
  	0,0,0,392,393,5,32,0,0,393,394,3,28,14,0,394,399,1,0,0,0,395,396,5,33,
  	0,0,396,397,5,32,0,0,397,399,3,28,14,0,398,384,1,0,0,0,398,395,1,0,0,
  	0,399,65,1,0,0,0,400,401,6,33,-1,0,401,457,3,88,44,0,402,457,3,90,45,
  	0,403,457,3,106,53,0,404,457,3,94,47,0,405,457,3,96,48,0,406,457,3,98,
  	49,0,407,457,3,100,50,0,408,457,3,82,41,0,409,410,5,2,0,0,410,411,3,66,
  	33,0,411,412,5,3,0,0,412,457,1,0,0,0,413,414,3,68,34,0,414,415,3,66,33,
  	13,415,457,1,0,0,0,416,417,5,23,0,0,417,418,3,66,33,0,418,419,5,24,0,
  	0,419,420,3,66,33,0,420,421,5,25,0,0,421,422,3,66,33,4,422,457,1,0,0,
  	0,423,457,3,102,51,0,424,428,5,39,0,0,425,426,3,130,65,0,426,427,5,31,
  	0,0,427,429,1,0,0,0,428,425,1,0,0,0,428,429,1,0,0,0,429,430,1,0,0,0,430,
  	435,3,66,33,0,431,432,5,6,0,0,432,434,3,66,33,0,433,431,1,0,0,0,434,437,
  	1,0,0,0,435,433,1,0,0,0,435,436,1,0,0,0,436,438,1,0,0,0,437,435,1,0,0,
  	0,438,439,5,40,0,0,439,457,1,0,0,0,440,444,5,35,0,0,441,442,3,130,65,
  	0,442,443,5,31,0,0,443,445,1,0,0,0,444,441,1,0,0,0,444,445,1,0,0,0,445,
  	446,1,0,0,0,446,451,3,66,33,0,447,448,5,6,0,0,448,450,3,66,33,0,449,447,
  	1,0,0,0,450,453,1,0,0,0,451,449,1,0,0,0,451,452,1,0,0,0,452,454,1,0,0,
  	0,453,451,1,0,0,0,454,455,5,36,0,0,455,457,1,0,0,0,456,400,1,0,0,0,456,
  	402,1,0,0,0,456,403,1,0,0,0,456,404,1,0,0,0,456,405,1,0,0,0,456,406,1,
  	0,0,0,456,407,1,0,0,0,456,408,1,0,0,0,456,409,1,0,0,0,456,413,1,0,0,0,
  	456,416,1,0,0,0,456,423,1,0,0,0,456,424,1,0,0,0,456,440,1,0,0,0,457,505,
  	1,0,0,0,458,459,10,12,0,0,459,460,3,70,35,0,460,461,3,66,33,13,461,504,
  	1,0,0,0,462,463,10,11,0,0,463,464,3,72,36,0,464,465,3,66,33,12,465,504,
  	1,0,0,0,466,467,10,10,0,0,467,468,3,74,37,0,468,469,3,66,33,11,469,504,
  	1,0,0,0,470,471,10,9,0,0,471,472,3,76,38,0,472,473,3,66,33,10,473,504,
  	1,0,0,0,474,475,10,8,0,0,475,476,3,78,39,0,476,477,3,66,33,9,477,504,
  	1,0,0,0,478,479,10,7,0,0,479,480,3,80,40,0,480,481,3,66,33,8,481,504,
  	1,0,0,0,482,484,10,6,0,0,483,485,5,94,0,0,484,483,1,0,0,0,484,485,1,0,
  	0,0,485,486,1,0,0,0,486,487,5,37,0,0,487,504,3,66,33,7,488,490,10,5,0,
  	0,489,491,5,94,0,0,490,489,1,0,0,0,490,491,1,0,0,0,491,492,1,0,0,0,492,
  	493,5,38,0,0,493,504,3,66,33,6,494,495,10,22,0,0,495,504,5,34,0,0,496,
  	497,10,21,0,0,497,498,5,35,0,0,498,499,3,66,33,0,499,500,5,36,0,0,500,
  	504,1,0,0,0,501,502,10,20,0,0,502,504,5,95,0,0,503,458,1,0,0,0,503,462,
  	1,0,0,0,503,466,1,0,0,0,503,470,1,0,0,0,503,474,1,0,0,0,503,478,1,0,0,
  	0,503,482,1,0,0,0,503,488,1,0,0,0,503,494,1,0,0,0,503,496,1,0,0,0,503,
  	501,1,0,0,0,504,507,1,0,0,0,505,503,1,0,0,0,505,506,1,0,0,0,506,67,1,
  	0,0,0,507,505,1,0,0,0,508,512,5,94,0,0,509,512,5,41,0,0,510,512,5,42,
  	0,0,511,508,1,0,0,0,511,509,1,0,0,0,511,510,1,0,0,0,512,69,1,0,0,0,513,
  	517,5,43,0,0,514,517,5,44,0,0,515,517,5,45,0,0,516,513,1,0,0,0,516,514,
  	1,0,0,0,516,515,1,0,0,0,517,71,1,0,0,0,518,521,5,46,0,0,519,521,5,42,
  	0,0,520,518,1,0,0,0,520,519,1,0,0,0,521,73,1,0,0,0,522,526,5,47,0,0,523,
  	526,5,48,0,0,524,526,5,49,0,0,525,522,1,0,0,0,525,523,1,0,0,0,525,524,
  	1,0,0,0,526,75,1,0,0,0,527,530,5,50,0,0,528,530,5,51,0,0,529,527,1,0,
  	0,0,529,528,1,0,0,0,530,77,1,0,0,0,531,536,5,39,0,0,532,536,5,52,0,0,
  	533,536,5,40,0,0,534,536,5,53,0,0,535,531,1,0,0,0,535,532,1,0,0,0,535,
  	533,1,0,0,0,535,534,1,0,0,0,536,79,1,0,0,0,537,540,5,54,0,0,538,540,5,
  	55,0,0,539,537,1,0,0,0,539,538,1,0,0,0,540,81,1,0,0,0,541,542,3,84,42,
  	0,542,83,1,0,0,0,543,544,5,95,0,0,544,545,5,2,0,0,545,546,3,86,43,0,546,
  	547,5,3,0,0,547,554,1,0,0,0,548,549,3,130,65,0,549,550,5,2,0,0,550,551,
  	3,86,43,0,551,552,5,3,0,0,552,554,1,0,0,0,553,543,1,0,0,0,553,548,1,0,
  	0,0,554,85,1,0,0,0,555,560,3,66,33,0,556,557,5,6,0,0,557,559,3,66,33,
  	0,558,556,1,0,0,0,559,562,1,0,0,0,560,558,1,0,0,0,560,561,1,0,0,0,561,
  	564,1,0,0,0,562,560,1,0,0,0,563,555,1,0,0,0,563,564,1,0,0,0,564,87,1,
  	0,0,0,565,566,5,95,0,0,566,89,1,0,0,0,567,572,5,56,0,0,568,569,5,35,0,
  	0,569,570,3,66,33,0,570,571,5,36,0,0,571,573,1,0,0,0,572,568,1,0,0,0,
  	572,573,1,0,0,0,573,574,1,0,0,0,574,575,3,92,46,0,575,576,3,130,65,0,
  	576,91,1,0,0,0,577,580,5,57,0,0,578,580,5,58,0,0,579,577,1,0,0,0,579,
  	578,1,0,0,0,580,93,1,0,0,0,581,582,5,59,0,0,582,583,3,66,33,0,583,95,
  	1,0,0,0,584,585,5,60,0,0,585,590,3,66,33,0,586,587,5,60,0,0,587,588,5,
  	61,0,0,588,590,3,66,33,0,589,584,1,0,0,0,589,586,1,0,0,0,590,97,1,0,0,
  	0,591,592,5,62,0,0,592,593,3,130,65,0,593,99,1,0,0,0,594,595,5,62,0,0,
  	595,596,5,2,0,0,596,597,3,66,33,0,597,598,5,3,0,0,598,101,1,0,0,0,599,
  	600,5,29,0,0,600,601,3,66,33,0,601,602,5,30,0,0,602,611,5,4,0,0,603,608,
  	3,104,52,0,604,605,5,6,0,0,605,607,3,104,52,0,606,604,1,0,0,0,607,610,
  	1,0,0,0,608,606,1,0,0,0,608,609,1,0,0,0,609,612,1,0,0,0,610,608,1,0,0,
  	0,611,603,1,0,0,0,611,612,1,0,0,0,612,613,1,0,0,0,613,614,5,5,0,0,614,
  	103,1,0,0,0,615,620,3,106,53,0,616,617,5,31,0,0,617,619,3,106,53,0,618,
  	616,1,0,0,0,619,622,1,0,0,0,620,618,1,0,0,0,620,621,1,0,0,0,621,623,1,
  	0,0,0,622,620,1,0,0,0,623,624,5,32,0,0,624,625,3,66,33,0,625,630,1,0,
  	0,0,626,627,5,33,0,0,627,628,5,32,0,0,628,630,3,66,33,0,629,615,1,0,0,
  	0,629,626,1,0,0,0,630,105,1,0,0,0,631,641,3,108,54,0,632,641,3,110,55,
  	0,633,641,3,112,56,0,634,641,3,118,59,0,635,641,3,120,60,0,636,641,3,
  	122,61,0,637,641,3,124,62,0,638,641,3,126,63,0,639,641,3,128,64,0,640,
  	631,1,0,0,0,640,632,1,0,0,0,640,633,1,0,0,0,640,634,1,0,0,0,640,635,1,
  	0,0,0,640,636,1,0,0,0,640,637,1,0,0,0,640,638,1,0,0,0,640,639,1,0,0,0,
  	641,107,1,0,0,0,642,644,7,0,0,0,643,642,1,0,0,0,643,644,1,0,0,0,644,645,
  	1,0,0,0,645,646,5,89,0,0,646,109,1,0,0,0,647,649,7,0,0,0,648,647,1,0,
  	0,0,648,649,1,0,0,0,649,650,1,0,0,0,650,651,5,90,0,0,651,111,1,0,0,0,
  	652,655,3,114,57,0,653,655,3,116,58,0,654,652,1,0,0,0,654,653,1,0,0,0,
  	655,113,1,0,0,0,656,659,5,91,0,0,657,659,5,80,0,0,658,656,1,0,0,0,658,
  	657,1,0,0,0,659,662,1,0,0,0,660,661,5,1,0,0,661,663,5,91,0,0,662,660,
  	1,0,0,0,662,663,1,0,0,0,663,115,1,0,0,0,664,665,5,81,0,0,665,666,5,1,
  	0,0,666,674,5,91,0,0,667,668,5,82,0,0,668,669,5,1,0,0,669,674,5,91,0,
  	0,670,671,5,83,0,0,671,672,5,1,0,0,672,674,5,91,0,0,673,664,1,0,0,0,673,
  	667,1,0,0,0,673,670,1,0,0,0,674,117,1,0,0,0,675,676,7,1,0,0,676,119,1,
  	0,0,0,677,680,5,63,0,0,678,680,5,64,0,0,679,677,1,0,0,0,679,678,1,0,0,
  	0,680,121,1,0,0,0,681,682,5,65,0,0,682,123,1,0,0,0,683,684,5,91,0,0,684,
  	685,5,1,0,0,685,686,5,66,0,0,686,125,1,0,0,0,687,688,5,80,0,0,688,689,
  	5,1,0,0,689,690,5,67,0,0,690,127,1,0,0,0,691,692,5,81,0,0,692,693,5,1,
  	0,0,693,694,5,68,0,0,694,129,1,0,0,0,695,707,3,132,66,0,696,707,3,134,
  	67,0,697,707,3,136,68,0,698,707,3,138,69,0,699,700,5,43,0,0,700,707,3,
  	130,65,0,701,702,5,92,0,0,702,707,3,130,65,0,703,704,5,69,0,0,704,707,
  	3,130,65,0,705,707,3,152,76,0,706,695,1,0,0,0,706,696,1,0,0,0,706,697,
  	1,0,0,0,706,698,1,0,0,0,706,699,1,0,0,0,706,701,1,0,0,0,706,703,1,0,0,
  	0,706,705,1,0,0,0,707,131,1,0,0,0,708,709,5,79,0,0,709,133,1,0,0,0,710,
  	711,5,35,0,0,711,712,3,130,65,0,712,713,5,96,0,0,713,714,5,91,0,0,714,
  	715,5,36,0,0,715,135,1,0,0,0,716,717,5,39,0,0,717,718,3,130,65,0,718,
  	719,5,96,0,0,719,720,5,91,0,0,720,721,5,40,0,0,721,137,1,0,0,0,722,729,
  	3,140,70,0,723,729,3,142,71,0,724,729,3,144,72,0,725,729,3,146,73,0,726,
  	729,3,148,74,0,727,729,3,150,75,0,728,722,1,0,0,0,728,723,1,0,0,0,728,
  	724,1,0,0,0,728,725,1,0,0,0,728,726,1,0,0,0,728,727,1,0,0,0,729,139,1,
  	0,0,0,730,731,7,2,0,0,731,141,1,0,0,0,732,733,7,3,0,0,733,143,1,0,0,0,
  	734,735,5,75,0,0,735,145,1,0,0,0,736,737,5,76,0,0,737,147,1,0,0,0,738,
  	739,5,77,0,0,739,149,1,0,0,0,740,741,5,78,0,0,741,151,1,0,0,0,742,743,
  	5,95,0,0,743,153,1,0,0,0,63,160,168,174,178,183,188,199,203,209,219,222,
  	230,246,258,265,269,275,294,303,308,331,335,348,362,379,389,398,428,435,
  	444,451,456,484,490,503,505,511,516,520,525,529,535,539,553,560,563,572,
  	579,589,608,611,620,629,640,643,648,654,658,662,673,679,706,728
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
    setState(154);
    global();
    setState(155);
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
    setState(160);
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
      | (1ULL << anceParser::T__38)
      | (1ULL << anceParser::T__40)
      | (1ULL << anceParser::T__41)
      | (1ULL << anceParser::T__42)
      | (1ULL << anceParser::T__55)
      | (1ULL << anceParser::T__58)
      | (1ULL << anceParser::T__59)
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
      setState(157);
      code();
      setState(162);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(163);
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
    setState(168);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__9)
      | (1ULL << anceParser::T__10)
      | (1ULL << anceParser::T__11))) != 0)) {
      setState(165);
      description();
      setState(170);
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
    setState(174);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(171);
      variableDescription();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(172);
      functionDescription();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(173);
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
    setState(176);
    accessModifier();
    setState(178);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::CONST) {
      setState(177);
      match(anceParser::CONST);
    }
    setState(180);
    match(anceParser::IDENTIFIER);
    setState(183);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__0) {
      setState(181);
      match(anceParser::T__0);
      setState(182);
      type();
    }
    setState(188);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(185);
      assigner();
      setState(186);
      expression(0);
    }
    setState(190);
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
    setState(192);
    accessModifier();
    setState(193);
    match(anceParser::IDENTIFIER);
    setState(194);
    match(anceParser::T__1);
    setState(195);
    parameters();
    setState(196);
    match(anceParser::T__2);
    setState(199);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__0) {
      setState(197);
      match(anceParser::T__0);
      setState(198);
      type();
    }
    setState(203);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__3: {
        setState(201);
        functionBlock();
        break;
      }

      case anceParser::SEMICOLON: {
        setState(202);
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
    setState(205);
    match(anceParser::T__3);
    setState(209);
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
      | (1ULL << anceParser::T__38)
      | (1ULL << anceParser::T__40)
      | (1ULL << anceParser::T__41)
      | (1ULL << anceParser::T__42)
      | (1ULL << anceParser::T__55)
      | (1ULL << anceParser::T__58)
      | (1ULL << anceParser::T__59)
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
      setState(206);
      code();
      setState(211);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(212);
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
    setState(222);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::IDENTIFIER) {
      setState(214);
      parameter();
      setState(219);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(215);
        match(anceParser::T__5);
        setState(216);
        parameter();
        setState(221);
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
    setState(224);
    match(anceParser::IDENTIFIER);
    setState(225);
    match(anceParser::T__0);
    setState(226);
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
    setState(230);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(228);
      aliasDescription();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(229);
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
    setState(232);
    accessModifier();
    setState(233);
    match(anceParser::T__6);
    setState(234);
    match(anceParser::IDENTIFIER);
    setState(235);
    match(anceParser::T__7);
    setState(236);
    type();
    setState(237);
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
    setState(239);
    accessModifier();
    setState(240);
    match(anceParser::T__8);
    setState(241);
    match(anceParser::IDENTIFIER);
    setState(242);
    match(anceParser::T__3);
    setState(246);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__9)
      | (1ULL << anceParser::T__10)
      | (1ULL << anceParser::T__11))) != 0)) {
      setState(243);
      member();
      setState(248);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(249);
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
    setState(251);
    accessModifier();
    setState(252);
    match(anceParser::IDENTIFIER);
    setState(253);
    match(anceParser::T__0);
    setState(254);
    type();
    setState(258);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(255);
      assigner();
      setState(256);
      literalExpression();
    }
    setState(260);
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
    setState(265);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__9: {
        _localctx = _tracker.createInstance<anceParser::PublicContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(262);
        match(anceParser::T__9);
        break;
      }

      case anceParser::T__10: {
        _localctx = _tracker.createInstance<anceParser::PrivateContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(263);
        match(anceParser::T__10);
        break;
      }

      case anceParser::T__11: {
        _localctx = _tracker.createInstance<anceParser::ExternContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(264);
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
    setState(269);
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
      case anceParser::T__38:
      case anceParser::T__40:
      case anceParser::T__41:
      case anceParser::T__42:
      case anceParser::T__55:
      case anceParser::T__58:
      case anceParser::T__59:
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
        setState(267);
        statement();
        break;
      }

      case anceParser::T__3: {
        enterOuterAlt(_localctx, 2);
        setState(268);
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
    setState(271);
    match(anceParser::T__3);
    setState(275);
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
      | (1ULL << anceParser::T__38)
      | (1ULL << anceParser::T__40)
      | (1ULL << anceParser::T__41)
      | (1ULL << anceParser::T__42)
      | (1ULL << anceParser::T__55)
      | (1ULL << anceParser::T__58)
      | (1ULL << anceParser::T__59)
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
      setState(272);
      code();
      setState(277);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(278);
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
    setState(294);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(280);
      expressionStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(281);
      localVariableDefinition();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(282);
      localReferenceDefinition();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(283);
      dropStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(284);
      assignment();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(285);
      deleteStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(286);
      breakStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(287);
      continueStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(288);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(289);
      assertStatement();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(290);
      ifStatement();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(291);
      whileStatement();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(292);
      loopStatement();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(293);
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
    setState(296);
    independentExpression();
    setState(297);
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
    setState(299);
    match(anceParser::T__12);
    setState(300);
    match(anceParser::IDENTIFIER);
    setState(303);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__0) {
      setState(301);
      match(anceParser::T__0);
      setState(302);
      type();
    }
    setState(308);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__14)
      | (1ULL << anceParser::T__15)
      | (1ULL << anceParser::T__16))) != 0)) {
      setState(305);
      assigner();
      setState(306);
      expression(0);
    }
    setState(310);
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
    setState(312);
    match(anceParser::T__12);
    setState(313);
    match(anceParser::IDENTIFIER);
    setState(314);
    match(anceParser::T__0);
    setState(315);
    type();
    setState(316);
    bindRef();
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
    setState(319);
    match(anceParser::T__13);
    setState(320);
    match(anceParser::IDENTIFIER);
    setState(321);
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
    setState(323);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->assignable = expression(0);
    setState(324);
    assigner();
    setState(325);
    antlrcpp::downCast<AssignmentContext *>(_localctx)->assigned = expression(0);
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
    setState(331);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__14: {
        _localctx = _tracker.createInstance<anceParser::CopyAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(328);
        match(anceParser::T__14);
        break;
      }

      case anceParser::T__15: {
        _localctx = _tracker.createInstance<anceParser::MoveAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(329);
        match(anceParser::T__15);
        break;
      }

      case anceParser::T__16: {
        _localctx = _tracker.createInstance<anceParser::FinalCopyAssignmentContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(330);
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
    setState(333);
    match(anceParser::T__17);
    setState(335);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      setState(334);
      match(anceParser::BUFFER);
      break;
    }

    default:
      break;
    }
    setState(337);
    expression(0);
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
    setState(340);
    match(anceParser::T__18);
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
    setState(343);
    match(anceParser::T__19);
    setState(344);
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
    setState(346);
    match(anceParser::T__20);
    setState(348);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__1)
      | (1ULL << anceParser::T__22)
      | (1ULL << anceParser::T__28)
      | (1ULL << anceParser::T__34)
      | (1ULL << anceParser::T__38)
      | (1ULL << anceParser::T__40)
      | (1ULL << anceParser::T__41)
      | (1ULL << anceParser::T__42)
      | (1ULL << anceParser::T__55)
      | (1ULL << anceParser::T__58)
      | (1ULL << anceParser::T__59)
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
      setState(347);
      expression(0);
    }
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
    setState(352);
    match(anceParser::T__21);
    setState(353);
    expression(0);
    setState(354);
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
    setState(356);
    match(anceParser::T__22);
    setState(357);
    expression(0);
    setState(358);
    match(anceParser::T__23);
    setState(359);
    antlrcpp::downCast<IfStatementContext *>(_localctx)->ifBlock = code();
    setState(362);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      setState(360);
      match(anceParser::T__24);
      setState(361);
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
    setState(364);
    match(anceParser::T__25);
    setState(365);
    expression(0);
    setState(366);
    match(anceParser::T__26);
    setState(367);
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
    setState(369);
    match(anceParser::T__27);
    setState(370);
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
    setState(372);
    match(anceParser::T__28);
    setState(373);
    expression(0);
    setState(374);
    match(anceParser::T__29);
    setState(375);
    match(anceParser::T__3);
    setState(379);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 33) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 33)) & ((1ULL << (anceParser::T__32 - 33))
      | (1ULL << (anceParser::T__62 - 33))
      | (1ULL << (anceParser::T__63 - 33))
      | (1ULL << (anceParser::T__64 - 33))
      | (1ULL << (anceParser::SIGNED_INTEGER - 33))
      | (1ULL << (anceParser::HEX_INTEGER - 33))
      | (1ULL << (anceParser::BIN_INTEGER - 33))
      | (1ULL << (anceParser::OCT_INTEGER - 33))
      | (1ULL << (anceParser::HALF - 33))
      | (1ULL << (anceParser::SINGLE - 33))
      | (1ULL << (anceParser::DOUBLE - 33))
      | (1ULL << (anceParser::QUAD - 33))
      | (1ULL << (anceParser::STRING - 33))
      | (1ULL << (anceParser::CHAR - 33))
      | (1ULL << (anceParser::INTEGER - 33))
      | (1ULL << (anceParser::IDENTIFIER - 33)))) != 0)) {
      setState(376);
      matchCase();
      setState(381);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(382);
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
    setState(398);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__62:
      case anceParser::T__63:
      case anceParser::T__64:
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
        setState(384);
        literalExpression();
        setState(389);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__30) {
          setState(385);
          match(anceParser::T__30);
          setState(386);
          literalExpression();
          setState(391);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(392);
        match(anceParser::T__31);
        setState(393);
        code();
        break;
      }

      case anceParser::T__32: {
        _localctx = _tracker.createInstance<anceParser::DefaultCaseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(395);
        match(anceParser::T__32);
        setState(396);
        match(anceParser::T__31);
        setState(397);
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
    setState(456);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<VariableContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(401);
      variableAccess();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<AllocContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(402);
      allocation();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<LiteralContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(403);
      literalExpression();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<AddressOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(404);
      addressof();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<RefContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(405);
      bindRef();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SizeOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(406);
      sizeofType();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SizeOfContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(407);
      sizeofExpression();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<IndependentContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(408);
      independentExpression();
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<ParenthesisContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(409);
      match(anceParser::T__1);
      setState(410);
      expression(0);
      setState(411);
      match(anceParser::T__2);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<UnaryOperationContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(413);
      unaryOperator();
      setState(414);
      expression(13);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<IfExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(416);
      match(anceParser::T__22);
      setState(417);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->condition = expression(0);
      setState(418);
      match(anceParser::T__23);
      setState(419);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->thenBlock = expression(0);
      setState(420);
      match(anceParser::T__24);
      setState(421);
      antlrcpp::downCast<IfExpressionContext *>(_localctx)->elseBlock = expression(4);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<MatchContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(423);
      matchExpression();
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<VectorDefinitionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(424);
      match(anceParser::T__38);
      setState(428);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
      case 1: {
        setState(425);
        type();
        setState(426);
        match(anceParser::T__30);
        break;
      }

      default:
        break;
      }
      setState(430);
      expression(0);
      setState(435);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(431);
        match(anceParser::T__5);
        setState(432);
        expression(0);
        setState(437);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(438);
      match(anceParser::T__39);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<ArrayDefinitionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(440);
      match(anceParser::T__34);
      setState(444);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
      case 1: {
        setState(441);
        type();
        setState(442);
        match(anceParser::T__30);
        break;
      }

      default:
        break;
      }
      setState(446);
      expression(0);
      setState(451);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(447);
        match(anceParser::T__5);
        setState(448);
        expression(0);
        setState(453);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(454);
      match(anceParser::T__35);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(505);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(503);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(458);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(459);
          binaryOperatorMultiplicative();
          setState(460);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(13);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(462);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(463);
          binaryOperatorAdditive();
          setState(464);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(12);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(466);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(467);
          binaryOperatorBitwise();
          setState(468);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(11);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(470);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(471);
          binaryOperatorShift();
          setState(472);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(10);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(474);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(475);
          binaryOperatorRelational();
          setState(476);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(9);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<BinaryOperationContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(478);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(479);
          binaryOperatorEquality();
          setState(480);
          antlrcpp::downCast<BinaryOperationContext *>(_localctx)->right = expression(8);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<LogicalAndContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(482);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
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
          antlrcpp::downCast<LogicalAndContext *>(_localctx)->right = expression(7);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<LogicalOrContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(488);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(490);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == anceParser::NOT) {
            setState(489);
            match(anceParser::NOT);
          }
          setState(492);
          match(anceParser::T__37);
          setState(493);
          antlrcpp::downCast<LogicalOrContext *>(_localctx)->right = expression(6);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<IndirectionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->value = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(494);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(495);
          match(anceParser::T__33);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<SubscriptContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->indexed = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(496);

          if (!(precpred(_ctx, 21))) throw FailedPredicateException(this, "precpred(_ctx, 21)");
          setState(497);
          match(anceParser::T__34);
          setState(498);
          antlrcpp::downCast<SubscriptContext *>(_localctx)->index = expression(0);
          setState(499);
          match(anceParser::T__35);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<MemberAccessContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->accessed = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(501);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(502);
          match(anceParser::IDENTIFIER);
          break;
        }

        default:
          break;
        } 
      }
      setState(507);
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
  enterRule(_localctx, 68, anceParser::RuleUnaryOperator);

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
      case anceParser::NOT: {
        _localctx = _tracker.createInstance<anceParser::NotContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(508);
        match(anceParser::NOT);
        break;
      }

      case anceParser::T__40: {
        _localctx = _tracker.createInstance<anceParser::BitwiseNotContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(509);
        match(anceParser::T__40);
        break;
      }

      case anceParser::T__41: {
        _localctx = _tracker.createInstance<anceParser::NegationContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(510);
        match(anceParser::T__41);
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
    setState(516);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__42: {
        _localctx = _tracker.createInstance<anceParser::MultiplicationContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(513);
        match(anceParser::T__42);
        break;
      }

      case anceParser::T__43: {
        _localctx = _tracker.createInstance<anceParser::DivisionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(514);
        match(anceParser::T__43);
        break;
      }

      case anceParser::T__44: {
        _localctx = _tracker.createInstance<anceParser::RemainderContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(515);
        match(anceParser::T__44);
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
    setState(520);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__45: {
        _localctx = _tracker.createInstance<anceParser::AdditionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(518);
        match(anceParser::T__45);
        break;
      }

      case anceParser::T__41: {
        _localctx = _tracker.createInstance<anceParser::SubtractionContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(519);
        match(anceParser::T__41);
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
    setState(525);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__46: {
        _localctx = _tracker.createInstance<anceParser::BitwiseAndContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(522);
        match(anceParser::T__46);
        break;
      }

      case anceParser::T__47: {
        _localctx = _tracker.createInstance<anceParser::BitwiseOrContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(523);
        match(anceParser::T__47);
        break;
      }

      case anceParser::T__48: {
        _localctx = _tracker.createInstance<anceParser::BitwiseXorContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(524);
        match(anceParser::T__48);
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
    setState(529);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__49: {
        _localctx = _tracker.createInstance<anceParser::LeftShiftContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(527);
        match(anceParser::T__49);
        break;
      }

      case anceParser::T__50: {
        _localctx = _tracker.createInstance<anceParser::RightShiftContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(528);
        match(anceParser::T__50);
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
    setState(535);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__38: {
        _localctx = _tracker.createInstance<anceParser::LessThanContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(531);
        match(anceParser::T__38);
        break;
      }

      case anceParser::T__51: {
        _localctx = _tracker.createInstance<anceParser::LessThanOrEqualContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(532);
        match(anceParser::T__51);
        break;
      }

      case anceParser::T__39: {
        _localctx = _tracker.createInstance<anceParser::GreaterThanContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(533);
        match(anceParser::T__39);
        break;
      }

      case anceParser::T__52: {
        _localctx = _tracker.createInstance<anceParser::GreaterThanOrEqualContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(534);
        match(anceParser::T__52);
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
    setState(539);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__53: {
        _localctx = _tracker.createInstance<anceParser::EqualContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(537);
        match(anceParser::T__53);
        break;
      }

      case anceParser::T__54: {
        _localctx = _tracker.createInstance<anceParser::NotEqualContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(538);
        match(anceParser::T__54);
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
    setState(541);
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
    setState(553);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(543);
      match(anceParser::IDENTIFIER);
      setState(544);
      match(anceParser::T__1);
      setState(545);
      arguments();
      setState(546);
      match(anceParser::T__2);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(548);
      type();
      setState(549);
      match(anceParser::T__1);
      setState(550);
      arguments();
      setState(551);
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
    setState(563);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << anceParser::T__1)
      | (1ULL << anceParser::T__22)
      | (1ULL << anceParser::T__28)
      | (1ULL << anceParser::T__34)
      | (1ULL << anceParser::T__38)
      | (1ULL << anceParser::T__40)
      | (1ULL << anceParser::T__41)
      | (1ULL << anceParser::T__42)
      | (1ULL << anceParser::T__55)
      | (1ULL << anceParser::T__58)
      | (1ULL << anceParser::T__59)
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
      setState(555);
      expression(0);
      setState(560);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(556);
        match(anceParser::T__5);
        setState(557);
        expression(0);
        setState(562);
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
    setState(565);
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
    setState(567);
    match(anceParser::T__55);
    setState(572);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::T__34) {
      setState(568);
      match(anceParser::T__34);
      setState(569);
      expression(0);
      setState(570);
      match(anceParser::T__35);
    }
    setState(574);
    allocator();
    setState(575);
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
    setState(579);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__56: {
        _localctx = _tracker.createInstance<anceParser::DynamicContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(577);
        match(anceParser::T__56);
        break;
      }

      case anceParser::T__57: {
        _localctx = _tracker.createInstance<anceParser::AutomaticContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(578);
        match(anceParser::T__57);
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
    setState(581);
    match(anceParser::T__58);
    setState(582);
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
    setState(589);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<anceParser::BindReferenceContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(584);
      match(anceParser::T__59);
      setState(585);
      expression(0);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<anceParser::BindReferenceToAddressContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(586);
      match(anceParser::T__59);
      setState(587);
      match(anceParser::T__60);
      setState(588);
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
    setState(591);
    match(anceParser::T__61);
    setState(592);
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
    setState(594);
    match(anceParser::T__61);
    setState(595);
    match(anceParser::T__1);
    setState(596);
    expression(0);
    setState(597);
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
    setState(599);
    match(anceParser::T__28);
    setState(600);
    antlrcpp::downCast<MatchExpressionContext *>(_localctx)->condition = expression(0);
    setState(601);
    match(anceParser::T__29);
    setState(602);
    match(anceParser::T__3);
    setState(611);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 33) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 33)) & ((1ULL << (anceParser::T__32 - 33))
      | (1ULL << (anceParser::T__62 - 33))
      | (1ULL << (anceParser::T__63 - 33))
      | (1ULL << (anceParser::T__64 - 33))
      | (1ULL << (anceParser::SIGNED_INTEGER - 33))
      | (1ULL << (anceParser::HEX_INTEGER - 33))
      | (1ULL << (anceParser::BIN_INTEGER - 33))
      | (1ULL << (anceParser::OCT_INTEGER - 33))
      | (1ULL << (anceParser::HALF - 33))
      | (1ULL << (anceParser::SINGLE - 33))
      | (1ULL << (anceParser::DOUBLE - 33))
      | (1ULL << (anceParser::QUAD - 33))
      | (1ULL << (anceParser::STRING - 33))
      | (1ULL << (anceParser::CHAR - 33))
      | (1ULL << (anceParser::INTEGER - 33))
      | (1ULL << (anceParser::IDENTIFIER - 33)))) != 0)) {
      setState(603);
      matchExpressionCase();
      setState(608);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == anceParser::T__5) {
        setState(604);
        match(anceParser::T__5);
        setState(605);
        matchExpressionCase();
        setState(610);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(613);
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
    setState(629);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__62:
      case anceParser::T__63:
      case anceParser::T__64:
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
        setState(615);
        literalExpression();
        setState(620);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == anceParser::T__30) {
          setState(616);
          match(anceParser::T__30);
          setState(617);
          literalExpression();
          setState(622);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(623);
        match(anceParser::T__31);
        setState(624);
        expression(0);
        break;
      }

      case anceParser::T__32: {
        _localctx = _tracker.createInstance<anceParser::DefaultExpressionCaseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(626);
        match(anceParser::T__32);
        setState(627);
        match(anceParser::T__31);
        setState(628);
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
  enterRule(_localctx, 106, anceParser::RuleLiteralExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(640);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(631);
      stringLiteral();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(632);
      charLiteral();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(633);
      integerLiteral();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(634);
      floatingPointLiteral();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(635);
      booleanLiteral();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(636);
      nullLiteral();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(637);
      sizeLiteral();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(638);
      diffLiteral();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(639);
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
    setState(643);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER

    || _la == anceParser::IDENTIFIER) {
      setState(642);
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
    setState(645);
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
    setState(648);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == anceParser::INTEGER

    || _la == anceParser::IDENTIFIER) {
      setState(647);
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
    setState(650);
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
    setState(654);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::SIGNED_INTEGER:
      case anceParser::INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(652);
        normalInteger();
        break;
      }

      case anceParser::HEX_INTEGER:
      case anceParser::BIN_INTEGER:
      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(653);
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
    setState(658);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::INTEGER: {
        setState(656);
        antlrcpp::downCast<NormalIntegerContext *>(_localctx)->uvalue = match(anceParser::INTEGER);
        break;
      }

      case anceParser::SIGNED_INTEGER: {
        setState(657);
        antlrcpp::downCast<NormalIntegerContext *>(_localctx)->svalue = match(anceParser::SIGNED_INTEGER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(662);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      setState(660);
      match(anceParser::T__0);
      setState(661);
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
    setState(673);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::HEX_INTEGER: {
        enterOuterAlt(_localctx, 1);
        setState(664);
        match(anceParser::HEX_INTEGER);
        setState(665);
        match(anceParser::T__0);
        setState(666);
        antlrcpp::downCast<SpecialIntegerContext *>(_localctx)->width = match(anceParser::INTEGER);
        break;
      }

      case anceParser::BIN_INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(667);
        match(anceParser::BIN_INTEGER);
        setState(668);
        match(anceParser::T__0);
        setState(669);
        antlrcpp::downCast<SpecialIntegerContext *>(_localctx)->width = match(anceParser::INTEGER);
        break;
      }

      case anceParser::OCT_INTEGER: {
        enterOuterAlt(_localctx, 3);
        setState(670);
        match(anceParser::OCT_INTEGER);
        setState(671);
        match(anceParser::T__0);
        setState(672);
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
    setState(675);
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
    setState(679);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__62: {
        _localctx = _tracker.createInstance<anceParser::TrueContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(677);
        match(anceParser::T__62);
        break;
      }

      case anceParser::T__63: {
        _localctx = _tracker.createInstance<anceParser::FalseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(678);
        match(anceParser::T__63);
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
    setState(681);
    match(anceParser::T__64);
   
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
    setState(683);
    match(anceParser::INTEGER);
    setState(684);
    match(anceParser::T__0);
    setState(685);
    match(anceParser::T__65);
   
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
    setState(687);
    match(anceParser::SIGNED_INTEGER);
    setState(688);
    match(anceParser::T__0);
    setState(689);
    match(anceParser::T__66);
   
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
    setState(691);
    match(anceParser::HEX_INTEGER);
    setState(692);
    match(anceParser::T__0);
    setState(693);
    match(anceParser::T__67);
   
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
  enterRule(_localctx, 130, anceParser::RuleType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(706);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::NATIVE_INTEGER_TYPE: {
        _localctx = _tracker.createInstance<anceParser::IntegerContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(695);
        integerType();
        break;
      }

      case anceParser::T__34: {
        _localctx = _tracker.createInstance<anceParser::ArrayContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(696);
        arrayType();
        break;
      }

      case anceParser::T__38: {
        _localctx = _tracker.createInstance<anceParser::VectorContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(697);
        vectorType();
        break;
      }

      case anceParser::T__65:
      case anceParser::T__66:
      case anceParser::T__67:
      case anceParser::T__69:
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
        setState(698);
        keywordType();
        break;
      }

      case anceParser::T__42: {
        _localctx = _tracker.createInstance<anceParser::PointerContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(699);
        match(anceParser::T__42);
        setState(700);
        type();
        break;
      }

      case anceParser::BUFFER: {
        _localctx = _tracker.createInstance<anceParser::BufferContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(701);
        match(anceParser::BUFFER);
        setState(702);
        type();
        break;
      }

      case anceParser::T__68: {
        _localctx = _tracker.createInstance<anceParser::ReferenceContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(703);
        match(anceParser::T__68);
        setState(704);
        type();
        break;
      }

      case anceParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<anceParser::CustomContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(705);
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
  enterRule(_localctx, 132, anceParser::RuleIntegerType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(708);
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
  enterRule(_localctx, 134, anceParser::RuleArrayType);

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
    match(anceParser::T__34);
    setState(711);
    type();
    setState(712);
    match(anceParser::SEMICOLON);
    setState(713);
    match(anceParser::INTEGER);
    setState(714);
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
  enterRule(_localctx, 136, anceParser::RuleVectorType);

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
    match(anceParser::T__38);
    setState(717);
    type();
    setState(718);
    match(anceParser::SEMICOLON);
    setState(719);
    match(anceParser::INTEGER);
    setState(720);
    match(anceParser::T__39);
   
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
  enterRule(_localctx, 138, anceParser::RuleKeywordType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(728);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case anceParser::T__69:
      case anceParser::T__70:
      case anceParser::T__71:
      case anceParser::T__72: {
        enterOuterAlt(_localctx, 1);
        setState(722);
        floatingPointType();
        break;
      }

      case anceParser::T__65:
      case anceParser::T__66:
      case anceParser::T__67:
      case anceParser::T__73: {
        enterOuterAlt(_localctx, 2);
        setState(723);
        targetDependentType();
        break;
      }

      case anceParser::T__74: {
        enterOuterAlt(_localctx, 3);
        setState(724);
        booleanType();
        break;
      }

      case anceParser::T__75: {
        enterOuterAlt(_localctx, 4);
        setState(725);
        charType();
        break;
      }

      case anceParser::T__76: {
        enterOuterAlt(_localctx, 5);
        setState(726);
        nullPointerType();
        break;
      }

      case anceParser::T__77: {
        enterOuterAlt(_localctx, 6);
        setState(727);
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
  enterRule(_localctx, 140, anceParser::RuleFloatingPointType);
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
    setState(730);
    _la = _input->LA(1);
    if (!(((((_la - 70) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 70)) & ((1ULL << (anceParser::T__69 - 70))
      | (1ULL << (anceParser::T__70 - 70))
      | (1ULL << (anceParser::T__71 - 70))
      | (1ULL << (anceParser::T__72 - 70)))) != 0))) {
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
  enterRule(_localctx, 142, anceParser::RuleTargetDependentType);
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
    setState(732);
    _la = _input->LA(1);
    if (!(((((_la - 66) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 66)) & ((1ULL << (anceParser::T__65 - 66))
      | (1ULL << (anceParser::T__66 - 66))
      | (1ULL << (anceParser::T__67 - 66))
      | (1ULL << (anceParser::T__73 - 66)))) != 0))) {
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
  enterRule(_localctx, 144, anceParser::RuleBooleanType);

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
    match(anceParser::T__74);
   
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
  enterRule(_localctx, 146, anceParser::RuleCharType);

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
    match(anceParser::T__75);
   
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
  enterRule(_localctx, 148, anceParser::RuleNullPointerType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(738);
    match(anceParser::T__76);
   
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
  enterRule(_localctx, 150, anceParser::RuleVoidType);

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
    match(anceParser::T__77);
   
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
  enterRule(_localctx, 152, anceParser::RuleCustomType);

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
