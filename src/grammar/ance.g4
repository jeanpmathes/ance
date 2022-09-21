grammar ance;

file
	: ( variableDeclaration | function | typeDefinition )* EOF
	;

variableDeclaration
	: accessModifier ( CONST )? IDENTIFIER ':' type ( assigner literalExpression )? ';'
	;

function
	: accessModifier IDENTIFIER '(' parameters ')' (':' type)? '{' ( code )* '}' # FunctionDefinition
	| 'extern' IDENTIFIER '(' parameters ')' (':' type)? ';' # ExternFunctionDeclaration
	;

parameters
	: (parameter (',' parameter)* )?
	;

parameter
	: IDENTIFIER ':' type
	;

typeDefinition
    : defineAlias
    | structDefinition
    ;

defineAlias
    : accessModifier 'define' IDENTIFIER 'alias' type ';'
    ;

structDefinition
    : accessModifier 'struct' IDENTIFIER '{' ( member )* '}'
    ;

member
    : accessModifier IDENTIFIER ':' type ( assigner literalExpression )? ';'
    ;

accessModifier
	: 'public' # Public
	| 'private' # Private
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
	| dropStatement
	| assignment
	| deleteStatement
	| returnStatement
	| assertStatement
	| ifStatement
    | whileStatement
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

dropStatement
    : 'drop' IDENTIFIER ';'
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
	| addressof # AdressOf
    | bindRef # Ref
    | sizeofType # SizeOf
    | sizeofExpression # SizeOf
	| independentExpression # Independent
	| '(' expression ')' # Parenthesis
    | 'not' expression # NotOperation
	| left=expression binaryOperatorMultiplicative right=expression # BinaryOperation
	| left=expression binaryOperatorAdditive right=expression # BinaryOperation
	| left=expression binaryOperatorRelational right=expression # BinaryOperation
	| left=expression binaryOperatorEquality right=expression # BinaryOperation
	| left=expression 'and' right=expression # LogicalAnd
    | left=expression 'or' right=expression # LogicalOr
    | 'if' condition=expression 'then' thenBlock=expression 'else' elseBlock=expression # IfExpression
    | matchExpression # Match
    | '<' ( type '|' ) ? expression ( ',' expression )* '>' # VectorDefinition
    | '[' ( type '|' ) ? expression ( ',' expression )* ']' # ArrayDefinition
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

binaryOperatorRelational
    : '<' # LessThan
    | '<=' # LessThanOrEqual
    | '>' # GreaterThan
    | '>=' # GreaterThanOrEqual
    ;

binaryOperatorEquality
    : '==' # Equal
    | '!=' # NotEqual
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
	| byteLiteral
	| integerLiteral
	| floatingPointLiteral
	| booleanLiteral
	| sizeLiteral
	| diffLiteral
	| uiptrLiteral
	;

stringLiteral
	: ( prefix=IDENTIFIER )? STRING
	;

byteLiteral
    : BYTE
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

sizeLiteral
    : INTEGER ':' 'size'
    ;

diffLiteral
    : SIGNED_INTEGER ':' 'diff'
    ;

uiptrLiteral
    : HEX_INTEGER ':' 'uiptr'
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
    | voidType
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
    ;

booleanType
	: 'bool'
	;

voidType
	: 'void'
	;

customType
    : IDENTIFIER
    ;

NATIVE_INTEGER_TYPE : 'u'? 'i' INTEGER ;

SIGNED_INTEGER : ( '+' | '-' ) INTEGER ;
HEX_INTEGER : '0' [xX] [0-9a-fA-F]+ ;
BIN_INTEGER : '0' [bB] [01]+ ;
OCT_INTEGER : '0' [oO] [0-7]+ ;

HALF : DECIMAL 'h' ;
SINGLE : DECIMAL 's' ;
DOUBLE : DECIMAL 'd' ;
QUAD : DECIMAL 'q' ;

DECIMAL : ( '+' | '-' )? ( [0-9]* '.' [0-9]+ ) ;

STRING : '"' ('\\'. | .)*? '"' ;
BYTE : '\'' ( . | '\\' . ) '\'' ;
INTEGER : [0-9]+ ;

BUFFER : '[]' ;
CONST : 'const' ;

IDENTIFIER : [_]* [a-zA-Z] [_a-zA-Z0-9]* ;

SEMICOLON : ';' ;

WHITESPACE : [ \t\r\n]+ -> skip ;

BLOCK_COMMENT : '/*' .*? '*/' -> skip;
LINE_COMMENT : '//' ~[\r\n]* -> skip;
