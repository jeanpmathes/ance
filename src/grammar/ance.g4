grammar ance;

unorderedScopeFile : ( declaration )* EOF ;

orderedScopeFile : statement EOF ;

// todo: plan to re-think all syntax, streamline it, simplify it, make it more consistent and logical
// todo: also make sure that EST is perfectly valid AST as well, needs things like the code expression

declaration
    : 'do' statement # RunnableDeclaration
    | accessModifier ( executionMode )? IDENTIFIER ':' varType=expression ( assigner assigned=expression )? ';' # VariableDeclaration
    | accessModifier ( executionMode )? IDENTIFIER '(' ( parameter (',' parameter)* )? ')' ( ':' type=expression )? '{' ( statement )* '}' # FunctionDeclaration
    ;

statement
    : '{' ( statement )* '}' # BlockStatement
    | expression ';' # ExpressionStatement
    | ('let' | VARIABLE) IDENTIFIER ':' varType=expression ( assigner assigned=expression )? ';' # BindStatement // todo: type inference - maybe before doing real type inference just do expansion to typeof(expression) if no type is set
    | assignee=expression assigner assgined=expression ';' # AssignmentStatement
    | 'if' expression 'then' trueBlock=statement ( 'else' falseBlock=statement )? # IfStatement
    | 'loop' statement # LoopStatement
    | 'break' ';' # BreakStatement
    | 'continue' ';' # ContinueStatement
    | 'return' ( expression )? ';' # ReturnStatement
    | 'while' expression 'do' statement # WhileStatement
    | 'match' expression 'with' '{' ( matchCase )* '}' # MatchStatement
    | 'erase' IDENTIFIER ';' # EraseStatement
    | 'assert' expression ';' # AssertStatement
    ;

matchCase
    : expression ( '|' expression )* '=>' statement # ExpressionMatchCase
    | DEFAULT '=>' statement # DefaultMatchCase
    ;

expression
    : orExpression
    ;

orExpression
    : andExpression ( orOperator andExpression )*
    ;

orOperator
    : (NOT)? 'or'
    ;

andExpression
    : equalityExpression ( andOperator equalityExpression )*
    ;

andOperator
    : ( NOT )? 'and'
    ;

equalityExpression
    : relationalExpression ( binaryOperatorEquality relationalExpression )*
    ;

relationalExpression
    : additiveExpression ( binaryOperatorRelational additiveExpression )*
    ;

additiveExpression
    : multiplicativeExpression ( binaryOperatorAdditive multiplicativeExpression )*
    ;

multiplicativeExpression
    : unaryExpression ( binaryOperatorMultiplicative unaryExpression )*
    ;

unaryExpression
    : unaryOperator target=unaryExpression # UnaryOperationExpression
    | postfixExpression # PostfixExpressionExpression
    ;

postfixExpression
    : callee=postfixExpression '(' (expression (',' expression)* )? ')' # CallExpression
    | indexed=postfixExpression '[' index=expression ']' # SubscriptExpression // todo: should become an operator
    | primaryExpression # PrimaryExpressionExpression
    ;

primaryExpression
    : '\\' ( '[' ']' )? '(' ( parameter (',' parameter)* )? ')' ( ':' type=expression )? ( ( '=>' body=expression ) | ( '{' ( statement )* '}' ) ) # LambdaExpression
    | 'intrinsic' name=expression 'args' '(' (expression (',' expression)* )? ')' # IntrinsicExpression
    | 'typeof' '(' expression (',' expression)* ')' # TypeOfExpression // todo: looks like a function, which is not ideal, but one might be able to make it a core function especially with inference, maybe it could then be typeof(#expr)
    | '[' type=expression ';' length=expression ']' # ArrayTypeExpression
    | '[' ( type=expression '|' )? expression ( ',' expression )* ']' # ArrayConstructorExpression
    | 'if' condition=expression 'then' trueBlock=expression ( 'else' falseBlock=expression )? # IfExpression
    | 'match' condition=expression 'with' '{' ( matchExpressionCase ( ',' matchExpressionCase )* )? '}' # MatchExpression
    | '({' ( statement )* ( '=>' expression )? '})' # BlockExpression
    | '(' expression ')' # ParenthesisExpression
    | IDENTIFIER # AccessExpression
    | literal # LiteralExpression
    | 'here' # HereExpression
    ;

matchExpressionCase
    : expression ( '|' expression )* '=>' expression # ExpressionMatchExpressionCase
    | DEFAULT '=>' expression # DefaultMatchExpressionCase
    ;

literal
    : boolean # BooleanLiteral
    | INTEGER # SizeLiteral
    | HALF # HalfLiteral
    | SINGLE # SingleLiteral
    | DOUBLE # DoubleLiteral
    | QUAD # QuadLiteral
    | '(' ')' # UnitLiteral
    | STRING # StringLiteral
    ;

boolean
    : 'true' # True
    | 'false' # False
    ;

parameter
    : IDENTIFIER ':' expression
    ;

unaryOperator
    : NOT # UnaryNot
    | '<not>' # UnaryBitwiseNot
    | '-' # UnaryNegation
    ;

binaryOperatorMultiplicative
    : '*' # Multiplication
    | '/' # Division
    | '%' # Remainder
    ;

binaryOperatorAdditive
    : '+' # Addition
    | '-' # Subtraction
    ;

assigner
    : ':=' # CopyAssigner
    ;

binaryOperatorRelational
    : '<' # LessThan
    | '<=' # LessThanOrEqual
    | '>' # GreaterThan
    | '>=' # GreaterThanOrEqual
    ;

binaryOperatorEquality
    : '==' # Equal
    | '/=' # NotEqual
    ;

accessModifier
    : 'public' # Public
    | 'private' # Private
    | 'extern' # Extern
    ;

executionMode
    : 'compiletime' # CompileTime
    | 'runtime' # Runtime
    ;

NOT : 'not' ;
VARIABLE : 'var' ;
DEFAULT : 'default' ;

INTEGER : [0-9]+ ;

IDENTIFIER : ( [_]* [\p{Alpha}\p{General_Category=Other_Letter}] [_\p{Alnum}\p{General_Category=Other_Letter}]* )
           | [\p{Emoji}] ;

STRING : '"' .*? '"' ; // todo: handle escape sequences (see old grammar) - needs code changes to preserve printing and do correct escaping

HALF : DECIMAL 'h' ;
SINGLE : DECIMAL 's' ;
DOUBLE : DECIMAL 'd' ;
QUAD : DECIMAL 'q' ;

DECIMAL : ( '+' | '-' )? ( [0-9]* '.' [0-9]+ ) ( [eE] ( '+' | '-' )? [0-9]+ )? ;

LAMBDA : '\\' ;
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
