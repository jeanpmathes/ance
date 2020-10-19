grammar ance;

file
	: ( statement )+
	;

statement
	: print_statement
	| return_statement
	;

print_statement
	: PRINT SEMICOLON
	;

return_statement
	: RETURN ( INTEGER )? SEMICOLON
	;

INTEGER : [0-9]+ ;

PRINT : 'print' ;
RETURN : 'return' ;

SEMICOLON : ';' ;

WHITESPACE : [ \t\r\n]+ -> skip ;