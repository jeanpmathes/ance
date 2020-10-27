grammar ance;

file
	: entry
	;

entry 
	: MAIN PARANTHESE_OPEN PARANTHESE_CLOSED BRACE_OPEN ( statement )+ BRACE_CLOSED
	;

statement
	: print_statement
	| return_statement
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

PARANTHESE_OPEN : '(' ;
PARANTHESE_CLOSED : ')' ;

BRACE_OPEN : '{' ;
BRACE_CLOSED : '}' ;

SEMICOLON : ';' ;

WHITESPACE : [ \t\r\n]+ -> skip ;