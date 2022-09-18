#ifndef ANCE_SRC_LANG_CONSTRUCTS_H
#define ANCE_SRC_LANG_CONSTRUCTS_H

class Application;

namespace lang
{
    class FunctionGroup;

    class Function;
    class CustomFunction;
    class ExternFunction;
    class PredefinedFunction;

    class BasicBlock;
    class CodeBlock;

    class Variable;
    class GlobalVariable;
    class LocalVariable;
}

class Addressof;
class Allocation;
class And;
class BinaryOperation;
class BindRef;
class BindRefTo;
class ConstantLiteral;
class FunctionCall;
class IfSelect;
class MatchSelect;
class Or;
class Parenthesis;
class SizeofExpression;
class SizeofType;
class Subscript;
class UnaryOperation;
class VariableAccess;
class MemberAccess;
class Indirection;

namespace lang
{
    class GlobalScope;
    class LocalScope;
}

class Assertion;
class Assignment;
class Case;
class Delete;
class Drop;
class ExpressionStatement;
class If;
class LocalReferenceVariableDefinition;
class LocalVariableDefinition;
class Match;
class Return;
class While;
class VectorDefinition;
class ArrayDefinition;

#define ANCE_CONSTRUCTS                                                                                                \
    Application, lang::FunctionGroup, lang::Function, lang::CustomFunction, lang::ExternFunction,                      \
        lang::PredefinedFunction, lang::BasicBlock, lang::CodeBlock, lang::Variable, lang::GlobalVariable,             \
        lang::LocalVariable, Addressof, Allocation, BinaryOperation, UnaryOperation, BindRef, BindRefTo,               \
        ConstantLiteral, FunctionCall, Parenthesis, SizeofExpression, SizeofType, Subscript, VariableAccess,           \
        MemberAccess, Indirection, And, Or, IfSelect, MatchSelect, lang::GlobalScope, lang::LocalScope, Assertion,     \
        Assignment, Delete, ExpressionStatement, LocalReferenceVariableDefinition, LocalVariableDefinition, Drop,      \
        Return, If, While, Match, Case, VectorDefinition, ArrayDefinition
#endif

class Statement;
using Statements = std::vector<std::unique_ptr<Statement>>;

class Expression;
using Expressions = std::vector<std::unique_ptr<Expression>>;
