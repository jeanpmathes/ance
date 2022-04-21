#ifndef ANCE_SRC_LANG_CONSTRUCTS_H_
#define ANCE_SRC_LANG_CONSTRUCTS_H_

class Application;

namespace lang
{
    class FunctionGroup;

    class Function;
    class CustomFunction;
    class ExternFunction;

    class BasicBlock;
    class CodeBlock;

    class Variable;
    class GlobalVariable;
    class LocalVariable;
}

class Addressof;
class Allocation;
class BinaryOperation;
class UnaryOperation;
class BindRef;
class ConstantLiteral;
class DefaultValue;
class FunctionCall;
class Parenthesis;
class SizeofExpression;
class SizeofType;
class Subscript;
class VariableAccess;

namespace lang
{
    class GlobalScope;
    class LocalScope;
}

class Assertion;
class Assignment;
class Delete;
class ExpressionStatement;
class LocalReferenceVariableDefinition;
class LocalVariableDefinition;
class Drop;
class Return;
class If;
class While;
class Match;
class Case;

#define ANCE_CONSTRUCTS                                                                                                \
    Application, lang::FunctionGroup, lang::Function, lang::CustomFunction, lang::ExternFunction, lang::BasicBlock,    \
        lang::CodeBlock, lang::Variable, lang::GlobalVariable, lang::LocalVariable, Addressof, Allocation,             \
        BinaryOperation, UnaryOperation, BindRef, ConstantLiteral, DefaultValue, FunctionCall, Parenthesis,            \
        SizeofExpression, SizeofType, Subscript, VariableAccess, lang::GlobalScope, lang::LocalScope, Assertion,       \
        Assignment, Delete, ExpressionStatement, LocalReferenceVariableDefinition, LocalVariableDefinition, Drop,      \
        Return, If, While, Match, Case
#endif
