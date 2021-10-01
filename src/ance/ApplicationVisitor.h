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
class Addressof;
class BindRef;
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
class LocalReferenceVariableDefinition;
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
        /**
         * Visit a given element.
         * @param element The element to visit.
         * @return The result.
         */
        bool visit(ance::Element& element);
        /**
         * Visit all children of a given element.
         * @param element The element to visit the children of. The element itself is not visited.
         * @return The result.
         */
        bool visitChildren(ance::Element& element);

      protected:
        /**
         * Called before an element is visited.
         * @param element The element that will be visited.
         */
        virtual void preVisit(ance::Element& element);
        /**
         * Called after an element was visited.
         * @param element The element that was visited.
         */
        virtual void postVisit(ance::Element& element);

      public:
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
        virtual bool visitAddressof(Addressof& addressof);
        virtual bool visitBindRef(BindRef& bind_ref);
        virtual bool visitSizeofExpression(SizeofExpression& sizeof_expression);
        virtual bool visitSizeofType(SizeofType& sizeof_type);
        virtual bool visitVariableAccess(VariableAccess& variable_access);

        virtual bool visitGlobalScope(ance::GlobalScope& global_scope);
        virtual bool visitLocalScope(ance::LocalScope& local_scope);

        virtual bool visitAssignmentStatement(AssignmentStatement& assignment_statement);
        virtual bool visitDeleteStatement(DeleteStatement& delete_statement);
        virtual bool visitExpressionStatement(ExpressionStatement& expression_statement);
        virtual bool visitLocalVariableDefinition(LocalVariableDefinition& local_variable_definition);
        virtual bool visitLocalReferenceVariableDefinition(LocalReferenceVariableDefinition& reference_definition);
        virtual bool visitReturnStatement(ReturnStatement& return_statement);
    };
}

#endif
