grammar ance;

file
	: ( value | code )+
	;

value
	: constant_declaration
	| variable_declaration
	;

constant_declaration
	: access_modifier CONST type IDENTIFIER ASSIGNMENT constant_expression SEMICOLON
	;

variable_declaration
	: access_modifier type IDENTIFIER ( ASSIGNMENT constant_expression )? SEMICOLON
	;

code
	: entry
	| function
	;

entry 
	: MAIN PARANTHESE_OPEN PARANTHESE_CLOSED BRACE_OPEN ( statement )+ BRACE_CLOSED
	;

function
	: IDENTIFIER PARANTHESE_OPEN PARANTHESE_CLOSED BRACE_OPEN ( statement )+ BRACE_CLOSED
	;

access_modifier
	: PUBLIC
	| PRIVATE
	;

statement
	: function_call
	| variable_assignment
	| print_statement
	| return_statement
	;

function_call
	: IDENTIFIER PARANTHESE_OPEN PARANTHESE_CLOSED SEMICOLON
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
	;

integer_type
	: NATIVE_INTEGER_TYPE
	;

array_type
	: BRACKET_OPEN type COLON INTEGER BRACKET_CLOSED
	;

NATIVE_INTEGER_TYPE : 'u'? 'i' INTEGER ;

SIGNED_INTEGER : ( '+' | '-' ) INTEGER ;
HEX_INTEGER : '0' [xX] [0-9a-fA-F]+ ;
BIN_INTEGER : '0' [bB] [01]+ ;
OCT_INTEGER : '0' [oO] [0-7]+ ;

STRING : '"' ('\\'. | .)*? '"';
INTEGER : [0-9]+ ;

MAIN : 'main' ;
PRINT : 'print' ;
RETURN : 'return' ;
CONST : 'const' ;
PUBLIC : 'public' ;
PRIVATE : 'private' ;

IDENTIFIER : [_a-zA-Z] [_a-zA-Z0-9]* ;

ASSIGNMENT : '=' ;

PARANTHESE_OPEN : '(' ;
PARANTHESE_CLOSED : ')' ;

BRACE_OPEN : '{' ;
BRACE_CLOSED : '}' ;

BRACKET_OPEN : '[' ;
BRACKET_CLOSED : ']' ;

COLON : ':' ;
SEMICOLON : ';' ;

WHITESPACE : [ \t\r\n]+ -> skip ;