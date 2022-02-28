#ifndef ANCE_SRC_LANG_CONSTRUCTS_H_
#define ANCE_SRC_LANG_CONSTRUCTS_H_

class Application;

namespace lang
{
    class FunctionGroup;

    class Function;
    class CustomFunction;
    class ExternFunction;

    class Variable;
    class GlobalVariable;
    class LocalVariable;
}

class Addressof;
class Allocation;
class BinaryOperation;
class BindRef;
class ConstantLiteral;
class DefaultValue;
class FunctionCall;
class SizeofExpression;
class SizeofType;
class Subscript;
class VariableAccess;

namespace lang
{
    class GlobalScope;
    class LocalScope;
};

class Assertion;
class AssignmentStatement;
class DeleteStatement;
class ExpressionStatement;
class LocalReferenceVariableDefinition;
class LocalVariableDefinition;
class ReturnStatement;

#define ANCE_CONSTRUCTS                                                                                                \
    Application, lang::FunctionGroup, lang::Function, lang::CustomFunction, lang::ExternFunction, lang::Variable,      \
        lang::GlobalVariable, lang::LocalVariable, Addressof, Allocation, BinaryOperation, BindRef, ConstantLiteral,   \
        DefaultValue, FunctionCall, SizeofExpression, SizeofType, Subscript, VariableAccess, lang::GlobalScope,        \
        lang::LocalScope, Assertion, AssignmentStatement, DeleteStatement, ExpressionStatement,                        \
        LocalReferenceVariableDefinition, LocalVariableDefinition, ReturnStatement

#endif
