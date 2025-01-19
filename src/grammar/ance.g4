grammar ance;

file : statement EOF ;

statement
    : '{' ( statement )* '}' # BlockStatement
    | expression ';' # ExpressionStatement
    ;

expression
    : entity '(' arguments ')' # Call
    ;

arguments
    : (expression (',' expression)* )?
    ;

entity
    : IDENTIFIER
    ;

IDENTIFIER : ( [_]* [\p{Alpha}\p{General_Category=Other_Letter}] [_\p{Alnum}\p{General_Category=Other_Letter}]* )
           | [\p{Emoji}] ;

SEMICOLON : ';' ;

WHITESPACE : [\p{White_Space}] -> skip ;

BLOCK_COMMENT : '/*' .*? '*/' -> skip;
LINE_COMMENT : '//' ~[\r\n]* -> skip;

ERROR_CHAR : . ;
