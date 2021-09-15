#ifndef ANCE_SRC_ANCE_APPLICATIONVISITOR_H_
#define ANCE_SRC_ANCE_APPLICATIONVISITOR_H_

class Application;

class Discard;
class IndexerSet;
class VariableAssignable;

namespace ance
{
    class DefinedFunction;
    class ExternFunction;

    class GlobalVariable;
    class LocalVariable;
};

class Allocation;
class ConstantLiteral;
class DefaultValue;
class FunctionCall;
class IndexerGet;
class RoughCast;
class SizeofExpression;
class SizeofType;
class VariableAccess;

namespace ance
{
    class GlobalScope;
    class LocalScope;
};

class AssignmentStatement;
class DeleteStatement;
class ExpressionStatement;
class LocalVariableDefinition;
class ReturnStatement;

namespace ance
{
    class Element;

    /**
     * A visitor base class for the application element structure.
     */
    class ApplicationVisitor
    {
      public:
        bool visit(ance::Element& element);
        bool visitChildren(ance::Element& element);

        virtual bool visitApplication(Application& application);

        virtual bool visitDiscard(Discard& discard);
        virtual bool visitIndexerSet(IndexerSet& indexer_set);
        virtual bool visitVariableAssignable(VariableAssignable& variable_assignable);

        virtual bool visitDefinedFunction(ance::DefinedFunction& defined_function);
        virtual bool visitExternFunction(ance::ExternFunction& extern_function);

        virtual bool visitGlobalVariable(ance::GlobalVariable& global_variable);
        virtual bool visitLocalVariable(ance::LocalVariable& local_variable);

        virtual bool visitAllocation(Allocation& allocation);
        virtual bool visitConstantLiteral(ConstantLiteral& constant_literal);
        virtual bool visitDefaultValue(DefaultValue& default_value);
        virtual bool visitFunctionCall(FunctionCall& function_call);
        virtual bool visitIndexerGet(IndexerGet& indexer_get);
        virtual bool visitRoughCast(RoughCast& rough_cast);
        virtual bool visitSizeofExpression(SizeofExpression& sizeof_expression);
        virtual bool visitSizeofType(SizeofType& sizeof_type);
        virtual bool visitVariableAccess(VariableAccess& variable_access);

        virtual bool visitGlobalScope(ance::GlobalScope& global_scope);
        virtual bool visitLocalScope(ance::LocalScope& local_scope);

        virtual bool visitAssignmentStatement(AssignmentStatement& assignment_statement);
        virtual bool visitDeleteStatement(DeleteStatement& delete_statement);
        virtual bool visitExpressionStatement(ExpressionStatement& expression_statement);
        virtual bool visitLocalVariableDefinition(LocalVariableDefinition& local_variable_definition);
        virtual bool visitReturnStatement(ReturnStatement& return_statement);
    };
}

#endif