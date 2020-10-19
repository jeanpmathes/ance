grammar ance;

file
	: statement
	;

statement
	: return_statement
	;

return_statement
	: RETURN ( INTEGER )? SEMICOLON
	;

INTEGER : [0-9]+ ;

RETURN : 'return' ;

SEMICOLON : ';' ;

WHITESPACE : [ \t\r\n]+ -> skip ;
