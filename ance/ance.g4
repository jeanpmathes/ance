grammar ance;

file
	: ( statement )+
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

PRINT : 'print' ;
RETURN : 'return' ;

SEMICOLON : ';' ;

WHITESPACE : [ \t\r\n]+ -> skip ;