#ifndef ANCE_SRC_LANG_APPLICATIONVISITOR_H_
#define ANCE_SRC_LANG_APPLICATIONVISITOR_H_

#include "Element.h"

namespace lang
{
    template<bool is_const>
    class ApplicationVisitor : public lang::VisitorBase<ANCE_CONSTRUCTS>
    {
      public:
        using VisitorBase<ANCE_CONSTRUCTS>::visit;

        std::any defaultVisit(VisitableBase* ptr) override
        {
            assert(!is_const && "Non-const visitable passed to const visitor.");

            return lang::VisitorBase<ANCE_CONSTRUCTS>::defaultVisit(ptr);
        }
    };

    using ApplicationVisitorConst    = ApplicationVisitor<true>;
    using ApplicationVisitorNonConst = ApplicationVisitor<false>;
}

#include "compiler/Application.h"

#include "lang/construct/CustomFunction.h"
#include "lang/construct/ExternFunction.h"
#include "lang/construct/Function.h"
#include "lang/construct/InitializerFunction.h"
#include "lang/construct/PredefinedFunction.h"

#include "lang/construct/BasicBlock.h"
#include "lang/construct/CodeBlock.h"

#include "lang/construct/GlobalVariable.h"
#include "lang/construct/LocalVariable.h"
#include "lang/construct/Variable.h"

#include "lang/construct/descriptions/FunctionDescription.h"

#include "lang/expression/Addressof.h"
#include "lang/expression/Allocation.h"
#include "lang/expression/And.h"
#include "lang/expression/ArrayDefinition.h"
#include "lang/expression/BinaryOperation.h"
#include "lang/expression/BindRef.h"
#include "lang/expression/BindRefTo.h"
#include "lang/expression/ConstantLiteral.h"
#include "lang/expression/FunctionCall.h"
#include "lang/expression/IfSelect.h"
#include "lang/expression/Indirection.h"
#include "lang/expression/MatchSelect.h"
#include "lang/expression/MemberAccess.h"
#include "lang/expression/Or.h"
#include "lang/expression/Parenthesis.h"
#include "lang/expression/SizeofExpression.h"
#include "lang/expression/SizeofType.h"
#include "lang/expression/Subscript.h"
#include "lang/expression/UnaryOperation.h"
#include "lang/expression/VariableAccess.h"
#include "lang/expression/VectorDefinition.h"

#include "lang/scope/GlobalScope.h"
#include "lang/scope/LocalScope.h"

#include "lang/statement/Assertion.h"
#include "lang/statement/Assignment.h"
#include "lang/statement/Break.h"
#include "lang/statement/Continue.h"
#include "lang/statement/Delete.h"
#include "lang/statement/Drop.h"
#include "lang/statement/ExpressionStatement.h"
#include "lang/statement/If.h"
#include "lang/statement/LocalReferenceVariableDefinition.h"
#include "lang/statement/LocalVariableDefinition.h"
#include "lang/statement/Match.h"
#include "lang/statement/Return.h"
#include "lang/statement/While.h"

#endif
