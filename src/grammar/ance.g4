grammar ance;

file
	: ( data | code )*
	;

data
	: constant_declaration
	| variable_declaration
	;

constant_declaration
	: access_modifier CONST type IDENTIFIER DEFINITION constant_expression SEMICOLON
	;

variable_declaration
	: access_modifier type IDENTIFIER ( ASSIGNMENT constant_expression )? SEMICOLON
	;

code
	: function
	;

function
	: access_modifier type IDENTIFIER PARENTHESES_OPEN parameters PARENTHESES_CLOSED BRACE_OPEN ( statement )+ BRACE_CLOSED
	;

parameters
	: (parameter (COMMA parameter)* )?
	;

parameter
	: type IDENTIFIER
	;

access_modifier
	: PUBLIC
	| PRIVATE
	;

statement
	: expression_statement
	| local_variable_definition
	| variable_assignment
	| print_statement
	| return_statement
	;

expression_statement
	: independent_expression SEMICOLON 
	;

local_variable_definition
	: type IDENTIFIER ( ASSIGNMENT expression )? SEMICOLON
	;

variable_assignment
	: IDENTIFIER ASSIGNMENT expression SEMICOLON
	;

print_statement
	: PRINT expression SEMICOLON
	;

return_statement
	: RETURN ( expression )? SEMICOLON
	;

expression
	: variable_expression
	| sizeof_type_expression
	| sizeof_exp_expression
	| constant_expression
	| independent_expression
	;

independent_expression
	: function_call
	;

function_call
	: IDENTIFIER PARENTHESES_OPEN arguments PARENTHESES_CLOSED
	;

arguments
	: (expression (COMMA expression)* )?
	;

variable_expression
	: IDENTIFIER
	;

sizeof_type_expression
	: SIZEOF type
	;

sizeof_exp_expression
	: SIZEOF PARENTHESES_OPEN expression PARENTHESES_CLOSED
	;

constant_expression
	: literal_expression
	| integer_expression
	| floating_point_expression
	;

literal_expression
	: STRING
	;

integer_expression
	: unsigned_integer
	| signed_integer
	| special_integer
	;

unsigned_integer
	: INTEGER ( COLON INTEGER )?
	;

signed_integer
	: SIGNED_INTEGER ( COLON INTEGER )?
	;

special_integer
	: HEX_INTEGER ( COLON INTEGER )?
	| BIN_INTEGER ( COLON INTEGER )?
	| OCT_INTEGER ( COLON INTEGER )?
	;

floating_point_expression
	: HALF
	| SINGLE
	| DOUBLE
	| QUAD
	;

type
	: integer_type
	| floating_point_type
	| size_type
	| array_type
	| void_type
	;

integer_type
	: NATIVE_INTEGER_TYPE
	;

floating_point_type
	: HALF_TYPE
	| SINGLE_TYPE
	| DOUBLE_TYPE
	| QUAD_TYPE
	;

size_type
	: SIZE
	;

array_type
	: BRACKET_OPEN INTEGER COLON type BRACKET_CLOSED
	;

void_type
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

STRING : '"' ('\\'. | .)*? '"';
INTEGER : [0-9]+ ;

SIZEOF : 'sizeof' ;
SIZE : 'size' ;

PRINT : 'print' ;
RETURN : 'return' ;
CONST : 'const' ;
PUBLIC : 'public' ;
PRIVATE : 'private' ;
VOID : 'void' ;

IDENTIFIER : [_a-zA-Z] [_a-zA-Z0-9]* ;

DEFINITION : ':=' ;
ASSIGNMENT : '<-' ;

PARENTHESES_OPEN : '(' ;
PARENTHESES_CLOSED : ')' ;

BRACE_OPEN : '{' ;
BRACE_CLOSED : '}' ;

BRACKET_OPEN : '[' ;
BRACKET_CLOSED : ']' ;

COMMA : ',' ;
COLON : ':' ;
SEMICOLON : ';' ;

WHITESPACE : [ \t\r\n]+ -> skip ;