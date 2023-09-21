grammar ance;

file
    : global EOF
    ;

projectFile
    : ( code )* EOF
    ;

global
    : ( description )*
    ;

description
    : variableDescription
    | functionDescription
    | typeDescription
    ;

variableDescription
    : accessModifier ( CONST )? IDENTIFIER ( ':' type )? ( assigner expression )? ';'
    ;

functionDescription
    : accessModifier IDENTIFIER '(' parameters ')' (':' type)? ( functionBlock | ';' )
    ;

functionBlock
    : '{' ( code )* '}'
    ;

parameters
    : (parameter (',' parameter)* )?
    ;

parameter
    : IDENTIFIER ':' type
    ;

typeDescription
    : aliasDescription
    | structDescription
    ;

aliasDescription
    : accessModifier 'define' IDENTIFIER 'alias' type ';'
    ;

structDescription
    : accessModifier 'struct' IDENTIFIER '{' ( member )* '}'
    ;

member
    : accessModifier IDENTIFIER ':' type ( assigner literalExpression )? ';'
    ;

accessModifier
    : 'public' # Public
    | 'private' # Private
    | 'extern' # Extern
    ;

code
    : statement
    | block
    ;

block
    : '{' ( code )* '}'
    ;

statement
    : expressionStatement
    | localVariableDefinition
    | localReferenceDefinition
    | eraseStatement
    | assignment
    | deleteStatement
    | breakStatement
    | continueStatement
    | returnStatement
    | assertStatement
    | ifStatement
    | whileStatement
    | loopStatement
    | matchStatement
    ;

expressionStatement
    : independentExpression ';'
    ;

localVariableDefinition
    : 'let' IDENTIFIER (':' type )? ( assigner expression )? ';'
    ;

localReferenceDefinition
    : 'let' IDENTIFIER ':' type bindRef ';'
    ;

eraseStatement
    : 'erase' IDENTIFIER ';'
    ;

assignment
    : assignable=expression assigner assigned=expression ';'
    ;

assigner
    : '<:' # CopyAssignment
    | '<-' # MoveAssignment
    | ':=' # FinalCopyAssignment
    ;

deleteStatement
    : 'delete' ( BUFFER )? expression ';'
    ;

breakStatement
    : 'break' ';'
    ;

continueStatement
    : 'continue' ';'
    ;

returnStatement
    : 'return' ( expression )? ';'
    ;

assertStatement
    : 'assert' expression ';'
    ;

ifStatement
    : 'if' expression 'then' ifBlock=code ( 'else' elseBlock=code )?
    ;

whileStatement
    : 'while' expression 'do' code
    ;

loopStatement
    : 'loop' code
    ;

matchStatement
    : 'match' expression 'with' '{' ( matchCase )* '}'
    ;

matchCase
    : literalExpression ( '|' literalExpression )* '=>' code # LiteralCase
    | 'default' '=>' code # DefaultCase
    ;

expression
    : variableAccess # Variable
    | allocation # Alloc
    | literalExpression # Literal
    | value=expression '.' # Indirection
    | indexed=expression '[' index=expression ']' # Subscript
    | accessed=expression IDENTIFIER # MemberAccess
    | addressof # AddressOf
    | bindRef # Ref
    | sizeofType # SizeOf
    | sizeofExpression # SizeOf
    | independentExpression # Independent
    | '(' expression ')' # Parenthesis
    | unaryOperator expression # UnaryOperation
    | left=expression binaryOperatorMultiplicative right=expression # BinaryOperation
    | left=expression binaryOperatorAdditive right=expression # BinaryOperation
    | left=expression binaryOperatorBitwise right=expression # BinaryOperation
    | left=expression binaryOperatorShift right=expression # BinaryOperation
    | left=expression binaryOperatorRelational right=expression # BinaryOperation
    | left=expression binaryOperatorEquality right=expression # BinaryOperation
    | left=expression ( NOT )? 'and' right=expression # LogicalAnd
    | left=expression ( NOT )? 'or' right=expression # LogicalOr
    | 'if' condition=expression 'then' thenBlock=expression 'else' elseBlock=expression # IfExpression
    | matchExpression # Match
    | '<' ( type '|' )? expression ( ',' expression )* '>' # VectorDefinition
    | '[' ( type '|' )? expression ( ',' expression )* ']' # ArrayDefinition
    ;

unaryOperator
    : 'not' # Not
    | '<not>' # BitwiseNot
    | '-' # Negation
    ;

binaryOperatorMultiplicative
    : '*' # Multiplication
    | '/' # Division
    | '%' # Remainder
    ;

binaryOperatorAdditive
    : '+' # Addition
    | '-' # Subtraction
    ;

binaryOperatorBitwise
    : '<and>' # BitwiseAnd
    | '<or>' # BitwiseOr
    | '<xor>' # BitwiseXor
    ;

binaryOperatorShift
    : '<sl>' # LeftShift
    | '<sr>' # RightShift
    ;

binaryOperatorRelational
    : '<' # LessThan
    | '<=' # LessThanOrEqual
    | '>' # GreaterThan
    | '>=' # GreaterThanOrEqual
    ;

binaryOperatorEquality
    : '==' # Equal
    | '/=' # NotEqual
    ;

independentExpression
    : functionCall
    ;

functionCall
    : IDENTIFIER '(' arguments ')'
    | type '(' arguments ')'
    ;

arguments
    : (expression (',' expression)* )?
    ;

variableAccess
    : IDENTIFIER
    ;

allocation
    : 'new' ( '[' expression ']' )? allocator type
    ;

allocator
    : 'dynamic' # Dynamic
    | 'automatic' # Automatic
    ;

addressof
    : 'addressof' expression
    ;

bindRef
    : 'ref' expression # BindReference
    | 'ref' 'to' expression # BindReferenceToAddress
    ;

sizeofType
    : 'sizeof' type
    ;

sizeofExpression
    : 'sizeof' '(' expression ')'
    ;

matchExpression
    : 'match' condition=expression 'with' '{' ( matchExpressionCase ( ',' matchExpressionCase )* )? '}'
    ;

matchExpressionCase
    : literalExpression ( '|' literalExpression )* '=>' expression # LiteralExpressionCase
    | 'default' '=>' expression # DefaultExpressionCase
    ;

literalExpression
    : stringLiteral
    | charLiteral
    | integerLiteral
    | floatingPointLiteral
    | booleanLiteral
    | nullLiteral
    | sizeLiteral
    | diffLiteral
    | uiptrLiteral
    | unitLiteral
    ;

stringLiteral
    : ( prefix=(IDENTIFIER | INTEGER) )? STRING
    ;

charLiteral
    : ( prefix=(IDENTIFIER | INTEGER) )? CHAR
    ;

integerLiteral
    : normalInteger
    | specialInteger
    ;

normalInteger
    : ( uvalue=INTEGER | svalue=SIGNED_INTEGER) ( ':' width=INTEGER )?
    ;

specialInteger
    : HEX_INTEGER ':' width=INTEGER
    | BIN_INTEGER ':' width=INTEGER
    | OCT_INTEGER ':' width=INTEGER
    ;

floatingPointLiteral
    : HALF
    | SINGLE
    | DOUBLE
    | QUAD
    ;

booleanLiteral
    : 'true' # True
    | 'false' # False
    ;

nullLiteral
    : 'null' # Null
    ;

sizeLiteral
    : INTEGER ':' 'size'
    ;

diffLiteral
    : SIGNED_INTEGER ':' 'diff'
    ;

uiptrLiteral
    : HEX_INTEGER ':' 'uiptr'
    ;

unitLiteral
    : '(' ')'
    ;

type
    : integerType # Integer
    | arrayType # Array
    | vectorType # Vector
    | keywordType # Keyword
    | '*' type # Pointer
    | '[]' type # Buffer
    | '&' type # Reference
    | customType # Custom
    ;

integerType
    : NATIVE_INTEGER_TYPE
    ;

arrayType
    : '[' type ';' INTEGER ']'
    ;

vectorType
    : '<' type ';' INTEGER '>'
    ;

keywordType
    : floatingPointType
    | targetDependentType
    | booleanType
    | charType
    | nullPointerType
    | unitType
    ;

floatingPointType
    : 'half'
    | 'single'
    | 'double'
    | 'quad'
    ;

targetDependentType
    : 'size'
    | 'diff'
    | 'uiptr'
    | 'ptr'
    ;

booleanType
    : 'bool'
    ;

charType
    : 'char'
    ;

nullPointerType
    : 'nullptr'
    ;

unitType
    : '(' ')'
    ;

customType
    : IDENTIFIER
    ;

NATIVE_INTEGER_TYPE : ( 'u' | 'i' ) INTEGER ;

SIGNED_INTEGER : ( '+' | '-' ) INTEGER ;
HEX_INTEGER : '0' [xX] [0-9a-fA-F]+ ;
BIN_INTEGER : '0' [bB] [01]+ ;
OCT_INTEGER : '0' [oO] [0-7]+ ;

HALF : DECIMAL 'h' ;
SINGLE : DECIMAL 's' ;
DOUBLE : DECIMAL 'd' ;
QUAD : DECIMAL 'q' ;

DECIMAL : ( '+' | '-' )? ( [0-9]* '.' [0-9]+ ) ( [eE] ( '+' | '-' )? [0-9]+ )? ;

STRING : '"' ('\\'~[\r\n] | ~[\r\n])*? '"' ;
CHAR : '\'' ( '\\' ~[\r\n] | ~[\r\n] )*? '\'' ;
INTEGER : [0-9]+ ;

BUFFER : '[]' ;
CONST : 'const' ;
NOT : 'not' ;

IDENTIFIER : ( [_]* [\p{Alpha}\p{General_Category=Other_Letter}] [_\p{Alnum}\p{General_Category=Other_Letter}]* )
           | [\p{Emoji}] ;

SEMICOLON : ';' ;

WHITESPACE : [\p{White_Space}] -> skip ;

BLOCK_COMMENT : '/*' .*? '*/' -> skip;
LINE_COMMENT : '//' ~[\r\n]* -> skip;

ERROR_CHAR : . ;
