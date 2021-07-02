grammar data;

element
    : dictionary
    | list
    | string
    | boolean
    ;

dictionary
    : '{' (entry (',' entry)* )? '}'
    ;

entry
    : KEY ':' value=element
    ;

list
    : '[' (element (',' element)* )? ']'
    ;

string
    : STRING
    ;

boolean
    : 'true' # True
    | 'false' # False
    ;

KEY : [_a-zA-Z] [_a-zA-Z0-9]* ;
STRING : '"' ('\\'. | .)*? '"';

WHITESPACE : [ \t\r\n]+ -> skip ;

LINE_COMMENT : '#' ~[\r\n]* -> skip;