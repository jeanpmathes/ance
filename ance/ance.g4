grammar ance;

file
	: ( type | value )+
	;

value
	: constant_declaration
	| variable_declaration
	;

constant_declaration
	: access_modifier CONST IDENTIFIER ASSIGNMENT literal_expression SEMICOLON
	;

variable_declaration
	: access_modifier IDENTIFIER ( ASSIGNMENT literal_expression )? SEMICOLON
	;

type
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
	: RETURN ( INTEGER )? SEMICOLON
	;

expression
	: variable_expression
	| literal_expression
	;

variable_expression
	: IDENTIFIER
	;

literal_expression
	: STRING
	;

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

SEMICOLON : ';' ;

WHITESPACE : [ \t\r\n]+ -> skip ;