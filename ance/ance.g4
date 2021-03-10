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
	: access_modifier type IDENTIFIER PARANTHESE_OPEN parameters PARANTHESE_CLOSED BRACE_OPEN ( statement )+ BRACE_CLOSED
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
	| constant_expression
	| independent_expression
	;

independent_expression
	: function_call
	;

function_call
	: IDENTIFIER PARANTHESE_OPEN arguments PARANTHESE_CLOSED
	;

arguments
	: (expression (COMMA expression)* )?
	;

variable_expression
	: IDENTIFIER
	;

constant_expression
	: literal_expression
	| integer_expression
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

type
	: integer_type
	| array_type
	| void_type
	;

integer_type
	: NATIVE_INTEGER_TYPE
	;

array_type
	: BRACKET_OPEN type COLON INTEGER BRACKET_CLOSED
	;

void_type
	: VOID
	;

NATIVE_INTEGER_TYPE : 'u'? 'i' INTEGER ;

SIGNED_INTEGER : ( '+' | '-' ) INTEGER ;
HEX_INTEGER : '0' [xX] [0-9a-fA-F]+ ;
BIN_INTEGER : '0' [bB] [01]+ ;
OCT_INTEGER : '0' [oO] [0-7]+ ;

STRING : '"' ('\\'. | .)*? '"';
INTEGER : [0-9]+ ;

PRINT : 'print' ;
RETURN : 'return' ;
CONST : 'const' ;
PUBLIC : 'public' ;
PRIVATE : 'private' ;
VOID : 'void' ;

IDENTIFIER : [_a-zA-Z] [_a-zA-Z0-9]* ;

DEFINITION : ':=' ;
ASSIGNMENT : '<-' ;

PARANTHESE_OPEN : '(' ;
PARANTHESE_CLOSED : ')' ;

BRACE_OPEN : '{' ;
BRACE_CLOSED : '}' ;

BRACKET_OPEN : '[' ;
BRACKET_CLOSED : ']' ;

COMMA : ',' ;
COLON : ':' ;
SEMICOLON : ';' ;

WHITESPACE : [ \t\r\n]+ -> skip ;