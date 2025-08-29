grammar ance;

file : statement EOF ;

statement
    : '{' ( statement )* '}' # BlockStatement
    | expression ';' # ExpressionStatement
    | 'let' IDENTIFIER ':' varType=expression ( assigner assigned=expression )? ';' # LetStatement // todo: type inference - maybe before doing real type inference just do expansion to typeof(expression) if no type is set
    | entity assigner expression ';' # AssignmentStatement
    | 'if' expression 'then' trueBlock=statement ( 'else' falseBlock=statement )? # IfStatement
    | 'loop' statement # LoopStatement
    | 'break' ';' # BreakStatement
    | 'continue' ';' # ContinueStatement
    | 'while' expression 'do' statement # WhileStatement
    ;

expression
    : entity '(' (expression (',' expression)* )? ')' # CallExpression // todo: should become an operator
    | entity # AccessExpression
    | literal # LiteralExpression
    | unary expression # UnaryOperationExpression
    ;

unary
    : 'not' # UnaryNot
    ;

literal
    : boolean # BooleanLiteral
    | INTEGER # SizeLiteral
    | '(' ')' # UnitLiteral
    | type # TypeLiteral
    ;

type
    : 'Bool' # BoolType
    | 'Unit' # UnitType
    | 'Size' # SizeType
    | 'Type' # TypeType
    ;

boolean
    : 'true' # True
    | 'false' # False
    ;

entity
    : IDENTIFIER
    ;

assigner
    : '<:'
    ;

IDENTIFIER : ( [_]* [\p{Alpha}\p{General_Category=Other_Letter}] [_\p{Alnum}\p{General_Category=Other_Letter}]* )
           | [\p{Emoji}] ;

INTEGER : [0-9]+ ;

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
