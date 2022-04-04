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
    : defineAs
    | defineAlias
    ;

defineAs
    : 'define' IDENTIFIER 'as' type ';'
    ;

defineAlias
    : 'define' IDENTIFIER 'alias' type ';'
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
	| assignment
	| deleteStatement
	| returnStatement
	| assertStatement
	| ifStatement
    | whileStatement
	;

expressionStatement
	: independentExpression ';'
	;

localVariableDefinition
	: 'let' IDENTIFIER ':' type ( assigner expression )? ';'
	;

localReferenceDefinition
    : 'let' IDENTIFIER ':' type 'ref' expression ';' # LocalReferenceToValueDefinition
    | 'let' IDENTIFIER ':' type 'ref' 'to' expression ';' # LocalReferenceToPointerDefinition
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

expression
	: variableAccess # Variable
	| allocation # Alloc
	| addressof # AdressOf
	| bindRef # Ref
	| sizeofType # SizeOf
	| sizeofExpression # SizeOf
	| literalExpression # Literal
	| indexed=expression '[' index=expression ']' # Subscript
	| independentExpression # Independent
	| '(' expression ')' # Parenthesis
	| left=expression binaryOperatorMultiplicative right=expression # BinaryOperation
	| left=expression binaryOperatorAdditive right=expression # BinaryOperation
	| left=expression binaryOperatorRelational right=expression # BinaryOperation
	| left=expression binaryOperatorEquality right=expression # BinaryOperation
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

literalExpression
	: stringLiteral
	| byteLiteral
	| integerLiteral
	| floatingPointLiteral
	| booleanLiteral
	| sizeLiteral
	| diffLiteral
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
	: value=INTEGER ':' width=INTEGER
	;

signedInteger
	: value=SIGNED_INTEGER ':' width=INTEGER
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
    : INTEGER ( ':' 'size' )?
    ;

diffLiteral
    : SIGNED_INTEGER ( ':' 'diff' )?
    ;

type
	: integerType # Integer
	| arrayType # Array
	| keywordType # Keyword
	| '*' type # Pointer
	| '&' type # Reference
	| customType # Custom
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