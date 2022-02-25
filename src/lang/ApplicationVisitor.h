#ifndef ANCE_SRC_LANG_APPLICATIONVISITOR_H_
#define ANCE_SRC_LANG_APPLICATIONVISITOR_H_

#include "Element.h"

namespace lang
{
    using ApplicationVisitor = lang::VisitorBase<ANCE_CONSTRUCTS>;
}

#include "compiler/Application.h"

#include "lang/construct/CustomFunction.h"
#include "lang/construct/ExternFunction.h"
#include "lang/construct/Function.h"

#include "lang/construct/GlobalVariable.h"
#include "lang/construct/LocalVariable.h"
#include "lang/construct/Variable.h"

#include "lang/expression/Addressof.h"
#include "lang/expression/Allocation.h"
#include "lang/expression/BinaryOperation.h"
#include "lang/expression/BindRef.h"
#include "lang/expression/ConstantLiteral.h"
#include "lang/expression/DefaultValue.h"
#include "lang/expression/FunctionCall.h"
#include "lang/expression/SizeofExpression.h"
#include "lang/expression/SizeofType.h"
#include "lang/expression/Subscript.h"
#include "lang/expression/VariableAccess.h"

#include "lang/scope/GlobalScope.h"
#include "lang/scope/LocalScope.h"

#include "lang/statement/Assertion.h"
#include "lang/statement/AssignmentStatement.h"
#include "lang/statement/DeleteStatement.h"
#include "lang/statement/ExpressionStatement.h"
#include "lang/statement/LocalReferenceVariableDefinition.h"
#include "lang/statement/LocalVariableDefinition.h"
#include "lang/statement/ReturnStatement.h"

#endif
