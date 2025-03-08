grammar ance;

file : statement EOF ;

statement
    : '{' ( statement )* '}' # BlockStatement
    | expression ';' # ExpressionStatement
    | 'let' IDENTIFIER ( '<:' expression )? ';' # LetStatement
    ;

expression
    : entity '(' arguments ')' # Call
    | entity # Access
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

BRACKET_OPEN : '(' ;
BRACKET_CLOSE : ')' ;

CURLY_BRACKET_OPEN : '{' ;
CURLY_BRACKET_CLOSE : '}' ;

SQUARE_BRACKET_OPEN : '[' ;
SQUARE_BRACKET_CLOSE : ']' ;

POINTY_BRACKET_OPEN : '<' ;
POINTY_BRACKET_CLOSE : '>' ;

ERROR_CHAR : . ;
