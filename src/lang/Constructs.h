#ifndef ANCE_SRC_LANG_CONSTRUCTS_H
#define ANCE_SRC_LANG_CONSTRUCTS_H

#include <vector>

class Unit;

namespace lang
{
    class FunctionGroup;

    class Function;
    class CustomFunction;
    class ExternFunction;
    class PredefinedFunction;
    class InitializerFunction;

    class BasicBlock;
    class CodeBlock;

    class Variable;
    class GlobalVariable;
    class LocalVariable;

    class FunctionDescription;
}

class Addressof;
class Allocation;
class And;
class ArrayDefinition;
class BinaryOperation;
class BindRef;
class BindRefTo;
class ConstantLiteral;
class FunctionCall;
class IfSelect;
class Indirection;
class MatchSelect;
class MemberAccess;
class Or;
class Parenthesis;
class SizeofExpression;
class SizeofType;
class Subscript;
class UnaryOperation;
class VariableAccess;
class VectorDefinition;

namespace lang
{
    class GlobalScope;
    class LocalScope;
}

class Case;

class Assertion;
class Assignment;
class Break;
class Continue;
class Delete;
class Drop;
class ExpressionStatement;
class If;
class LocalReferenceVariableDefinition;
class LocalVariableDefinition;
class Match;
class Return;
class While;

#define ANCE_CONSTRUCTS                                                                                                \
    Unit, lang::FunctionGroup, lang::Function, lang::CustomFunction, lang::ExternFunction, lang::PredefinedFunction,   \
        lang::InitializerFunction, lang::BasicBlock, lang::CodeBlock, lang::Variable, lang::GlobalVariable,            \
        lang::LocalVariable, lang::FunctionDescription, Addressof, Allocation, BinaryOperation, UnaryOperation,        \
        BindRef, BindRefTo, ConstantLiteral, FunctionCall, Parenthesis, SizeofExpression, SizeofType, Subscript,       \
        VariableAccess, MemberAccess, Indirection, And, Or, IfSelect, MatchSelect, lang::GlobalScope,                  \
        lang::LocalScope, Assertion, Assignment, Break, Continue, Delete, ExpressionStatement,                         \
        LocalReferenceVariableDefinition, LocalVariableDefinition, Drop, Return, If, While, Match, Case,               \
        VectorDefinition, ArrayDefinition
#endif

template<typename T>
class Owned;

class Statement;
using Statements = std::vector<Owned<Statement>>;

class Expression;
using Expressions = std::vector<Owned<Expression>>;
