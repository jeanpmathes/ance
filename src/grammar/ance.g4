grammar ance;

file
	: ( variableDeclaration | function )* EOF
	;

variableDeclaration
	: accessModifier ( CONST )? type IDENTIFIER ( assigner literalExpression )? ';'
	;

function
	: accessModifier type IDENTIFIER '(' parameters ')' '{' ( statement )* '}' # FunctionDefinition
	| 'extern' type IDENTIFIER '(' parameters ')' ';' # ExternFunctionDeclaration
	;

parameters
	: (parameter (',' parameter)* )?
	;

parameter
	: type IDENTIFIER
	;

accessModifier
	: 'public' # Public
	| 'private' # Private
	;

statement
	: expressionStatement
	| localVariableDefinition
	| assignment
	| deleteStatement
	| returnStatement
	;

expressionStatement
	: independentExpression ';'
	;

localVariableDefinition
	: type IDENTIFIER ( assigner expression )? ';'
	;

assignment
	: assignable assigner expression ';'
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

assignable
    : variableAssignable
    | indexerSet
    | discard
    ;

variableAssignable
    : IDENTIFIER
    ;

indexerSet
    : indexed=expression '[' index=expression ']'
    ;

discard
    : 'discard'
    ;

expression
	: variableAccess # Variable
	| allocation # Alloc
	| roughCast # Cast
	| sizeofType # SizeOf
	| sizeofExpression # SizeOf
	| literalExpression # Literal
	| indexed=expression '[' index=expression ']' # IndexerGet
	| independentExpression # Independent
	;

independentExpression
	: functionCall
	;

functionCall
	: IDENTIFIER '(' arguments ')'
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

roughCast
    : '{' type '}' expression
    ;

sizeofType
	: 'sizeof' type
	;

sizeofExpression
	: 'sizeof' '(' expression ')'
	;

literalExpression
	: stringLiteral
	| byteLiteral
	| integerLiteral
	| floatingPointLiteral
	| booleanLiteral
	| sizeLiteral
	;

stringLiteral
	: ( prefix=IDENTIFIER )? STRING
	;

byteLiteral
    : BYTE
    ;

integerLiteral
	: unsignedInteger
	| signedInteger
	| specialInteger
	;

unsignedInteger
	: INTEGER ( ':' INTEGER )?
	;

signedInteger
	: SIGNED_INTEGER ( ':' INTEGER )?
	;

specialInteger
	: HEX_INTEGER ( ':' INTEGER )?
	| BIN_INTEGER ( ':' INTEGER )?
	| OCT_INTEGER ( ':' INTEGER )?
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

type
	: integerType # Integer
	| arrayType # Array
	| keywordType # Keyword
	| type '*' # Pointer
	;

integerType
	: NATIVE_INTEGER_TYPE
	;

arrayType
	: '[' type ';' INTEGER ']'
	;

keywordType
    : floatingPointType
    | targetDependentType
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

voidType
	: 'void'
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