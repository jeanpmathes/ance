grammar ance;

file
	: ( data | code )*
	;

data
	: constantDeclaration
	| variableDeclaration
	;

constantDeclaration
	: accessModifier CONST type IDENTIFIER DEFINITION literalExpression ';'
	;

variableDeclaration
	: accessModifier type IDENTIFIER ( ASSIGNMENT literalExpression )? ';'
	;

code
	: function
	;

function
	: accessModifier type IDENTIFIER '(' parameters ')' '{' ( statement )+ '}'
	;

parameters
	: (parameter (',' parameter)* )?
	;

parameter
	: type IDENTIFIER
	;

accessModifier
	: PUBLIC
	| PRIVATE
	;

statement
	: expressionStatement
	| localVariableDefinition
	| variableAssignment
	| printStatement
	| deleteStatement
	| returnStatement
	;

expressionStatement
	: independentExpression ';'
	;

localVariableDefinition
	: type IDENTIFIER ( ASSIGNMENT expression )? ';'
	;

variableAssignment
	: IDENTIFIER ASSIGNMENT expression ';'
	;

printStatement
	: PRINT expression ';'
	;

deleteStatement
    : DELETE expression ';'
    ;

returnStatement
	: RETURN ( expression )? ';'
	;

expression
	: variableExpression
	| allocationExpression
	| sizeofTypeExpression
	| sizeofExpExpression
	| literalExpression
	| independentExpression
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

variableExpression
	: IDENTIFIER
	;

allocationExpression
    : 'new' allocator type
    ;

allocator
    : DYNAMIC
    | AUTOMATIC
    ;

sizeofTypeExpression
	: SIZEOF type
	;

sizeofExpExpression
	: SIZEOF '(' expression ')'
	;

literalExpression
	: stringLiteral
	| byteLiteral
	| integerLiteral
	| floatingPointLiteral
	| booleanLiteral
	;

stringLiteral
	: STRING
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
    : TRUE
    | FALSE
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
	: '[' INTEGER ':' type ']'
	;

keywordType
    : floatingPointType
    | sizeType
    | unsignedIntegerPointerType
    | voidType
    ;

floatingPointType
	: HALF_TYPE
	| SINGLE_TYPE
	| DOUBLE_TYPE
	| QUAD_TYPE
	;

sizeType
	: SIZE
	;

unsignedIntegerPointerType
    : UIPTR
    ;

voidType
	: VOID
	;

NATIVE_INTEGER_TYPE : 'u'? 'i' INTEGER ;

HALF_TYPE: 'half' ;
SINGLE_TYPE: 'single' ;
DOUBLE_TYPE: 'double' ;
QUAD_TYPE: 'quad' ;

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

DYNAMIC : 'dynamic' ;
AUTOMATIC : 'automatic' ;

TRUE : 'true' ;
FALSE : 'false' ;

SIZEOF : 'sizeof' ;
SIZE : 'size' ;
UIPTR : 'uiptr' ;

PRINT : 'print' ;
RETURN : 'return' ;
DELETE : 'delete' ;
CONST : 'const' ;

PUBLIC : 'public' ;
PRIVATE : 'private' ;

VOID : 'void' ;

IDENTIFIER : [_a-zA-Z] [_a-zA-Z0-9]* ;

DEFINITION : ':=' ;
ASSIGNMENT : '<-' ;

WHITESPACE : [ \t\r\n]+ -> skip ;

BLOCK_COMMENT : '/*' .*? '*/' -> skip;
LINE_COMMENT : '//' ~[\r\n]* -> skip;