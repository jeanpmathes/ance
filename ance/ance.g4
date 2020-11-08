grammar ance;

file
	: ( type )+
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

statement
	: function_call
	| print_statement
	| return_statement
	;

function_call
	: IDENTIFIER PARANTHESE_OPEN PARANTHESE_CLOSED SEMICOLON
	;

print_statement
	: PRINT STRING SEMICOLON
	;

return_statement
	: RETURN ( INTEGER )? SEMICOLON
	;

STRING : '"' ('\\'. | .)*? '"';
INTEGER : [0-9]+ ;

MAIN : 'main' ;
PRINT : 'print' ;
RETURN : 'return' ;

IDENTIFIER : [_a-zA-Z] [_a-zA-Z0-9]* ;

PARANTHESE_OPEN : '(' ;
PARANTHESE_CLOSED : ')' ;

BRACE_OPEN : '{' ;
BRACE_CLOSED : '}' ;

SEMICOLON : ';' ;

WHITESPACE : [ \t\r\n]+ -> skip ;