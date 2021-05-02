grammar ance;

file
	: ( data | code )*
	;

data
	: constant_declaration
	| variable_declaration
	;

constant_declaration
	: access_modifier CONST type IDENTIFIER DEFINITION constant_expression ';'
	;

variable_declaration
	: access_modifier type IDENTIFIER ( ASSIGNMENT constant_expression )? ';'
	;

code
	: function
	;

function
	: access_modifier type IDENTIFIER '(' parameters ')' '{' ( statement )+ '}'
	;

parameters
	: (parameter (',' parameter)* )?
	;

parameter
	: type IDENTIFIER
	;

access_modifier
	: PUBLIC
	| PRIVATE
	;

statement
	: expression_statement
	| local_variable_definition
	| variable_assignment
	| print_statement
	| return_statement
	;

expression_statement
	: independent_expression ';'
	;

local_variable_definition
	: type IDENTIFIER ( ASSIGNMENT expression )? ';'
	;

variable_assignment
	: IDENTIFIER ASSIGNMENT expression ';'
	;

print_statement
	: PRINT expression ';'
	;

return_statement
	: RETURN ( expression )? ';'
	;

expression
	: variable_expression
	| sizeof_type_expression
	| sizeof_exp_expression
	| constant_expression
	| independent_expression
	;

independent_expression
	: function_call
	;

function_call
	: IDENTIFIER '(' arguments ')'
	;

arguments
	: (expression (',' expression)* )?
	;

variable_expression
	: IDENTIFIER
	;

sizeof_type_expression
	: SIZEOF type
	;

sizeof_exp_expression
	: SIZEOF '(' expression ')'
	;

constant_expression
	: string_expression
	| byte_expression
	| integer_expression
	| floating_point_expression
	| boolean_expression
	;

string_expression
	: STRING
	;

byte_expression
    : BYTE
    ;

integer_expression
	: unsigned_integer
	| signed_integer
	| special_integer
	;

unsigned_integer
	: INTEGER ( ':' INTEGER )?
	;

signed_integer
	: SIGNED_INTEGER ( ':' INTEGER )?
	;

special_integer
	: HEX_INTEGER ( ':' INTEGER )?
	| BIN_INTEGER ( ':' INTEGER )?
	| OCT_INTEGER ( ':' INTEGER )?
	;

floating_point_expression
	: HALF
	| SINGLE
	| DOUBLE
	| QUAD
	;

boolean_expression
    : TRUE
    | FALSE
    ;

type
	: integer_type # Integer
	| array_type # Array
	| keyword_type # Keyword
	| type '*' # Pointer
	;

integer_type
	: NATIVE_INTEGER_TYPE
	;

array_type
	: '[' INTEGER ':' type ']'
	;

keyword_type
    : floating_point_type
    | size_type
    | unsigned_integer_pointer_type
    | void_type
    ;

floating_point_type
	: HALF_TYPE
	| SINGLE_TYPE
	| DOUBLE_TYPE
	| QUAD_TYPE
	;

size_type
	: SIZE
	;

unsigned_integer_pointer_type
    : UIPTR
    ;

void_type
	: VOID
	;

NATIVE_INTEGER_TYPE : 'u'? 'i' INTEGER ;

HALF_TYPE: 'half' ;
SINGLE_TYPE: 'single' ;
DOUBLE_TYPE: 'double' ;
QUAD_TYPE: 'quad' ;

SIGNED_INTEGER : ( '+' | '-' ) INTEGER ;
HEX_INTEGER : '0' [xX] [0-9a-fA-F]+ ;
BIN_INTEGER : '0' [bB] [01]+ ;
OCT_INTEGER : '0' [oO] [0-7]+ ;

HALF : DECIMAL 'h' ;
SINGLE : DECIMAL 's' ;
DOUBLE : DECIMAL 'd' ;
QUAD : DECIMAL 'q' ;

DECIMAL : ( '+' | '-' )? ( [0-9]* '.' [0-9]+ ) ;

STRING : '"' ('\\'. | .)*? '"' ;
BYTE : '\'' ( . | '\\' . ) '\'' ;
INTEGER : [0-9]+ ;

TRUE : 'true' ;
FALSE : 'false' ;

SIZEOF : 'sizeof' ;
SIZE : 'size' ;
UIPTR : 'uiptr' ;

PRINT : 'print' ;
RETURN : 'return' ;
CONST : 'const' ;
PUBLIC : 'public' ;
PRIVATE : 'private' ;
VOID : 'void' ;

IDENTIFIER : [_a-zA-Z] [_a-zA-Z0-9]* ;

DEFINITION : ':=' ;
ASSIGNMENT : '<-' ;

WHITESPACE : [ \t\r\n]+ -> skip ;

BLOCK_COMMENT : '/*' .*? '*/' -> skip;
LINE_COMMENT : '//' ~[\r\n]* -> skip;