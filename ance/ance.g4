grammar ance;

file
	: statement
	;

statement
	: return_statement
	;

return_statement
	: RETURN SEMICOLON
	;

RETURN : 'return' ;

SEMICOLON : ';' ;

WHITESPACE : [ \t\r\n]+ -> skip ;
