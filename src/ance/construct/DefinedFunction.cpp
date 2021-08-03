#include "DefinedFunction.h"

#include <llvm/ADT/SmallVector.h>// critical, missing include will cause linking error
#include <utility>

#include "ance/AccessModifier.h"
#include "ance/construct/value/Value.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/LocalScope.h"
#include "ance/type/VoidType.h"
#include "ance/utility/Values.h"

ance::DefinedFunction::DefinedFunction(AccessModifier                access,
                                       std::string                   function_name,
                                       ance::Type*                   return_type,
                                       std::vector<ance::Parameter*> parameters,
                                       ance::Scope*                  scope,
                                       unsigned int                  line,
                                       unsigned int                  column)
    : ance::Function(std::move(function_name), return_type, line, column)
    , access_(access)
    , parameters_(std::move(parameters))
    , containing_scope_(scope)
    , function_scope_(new ance::LocalScope(this))
{
    for (auto* parameter : parameters_)
    {
        ance::LocalVariable* arg = function_scope_->defineParameterVariable(parameter->name(),
                                                                     parameter->type(),
                                                                     Assigner::COPY_ASSIGNMENT,
                                                                     parameter);
        arguments_.push_back(arg);
    }
}

void ance::DefinedFunction::pushStatement(Statement* statement)
{
    statements_.push_back(statement);
    statement->setContainingFunction(this);
}

void ance::DefinedFunction::buildName(CompileContext* context)
{
    std::tie(native_type_, native_function_) =
        createNativeFunction(parameters_, access_.linkage(), *context->llvmContext(), context->module());

    std::vector<llvm::Metadata*> di_types;

    for (const auto& pair : zip(parameters_, native_function_->args()))
    {
        const auto& [parameter, argument] = pair;
        parameter->wrap(&argument);

        di_types.push_back(parameter->type()->getDebugType(context));
    }

    llvm::DISubroutineType* debug_type =
        context->di()->createSubroutineType(context->di()->getOrCreateTypeArray(di_types));
    llvm::DISubprogram* debug =
        context->di()->createFunction(context->unit(),
                                      getName(),
                                      getName(),
                                      context->codeFile(),
                                      line(),
                                      debug_type,
                                      0,
                                      llvm::DINode::DIFlags::FlagZero,
                                      llvm::DISubprogram::toSPFlags(true, true, false, 0U, getName() == "main"));

    native_function_->setSubprogram(debug);

    unsigned no = 1;
    for (auto parameter : parameters_)
    {
        context->di()->createParameterVariable(debug,
                                               parameter->name(),
                                               no++,
                                               context->codeFile(),
                                               line(),
                                               parameter->type()->getDebugType(context),
                                               true);
    }
}

void ance::DefinedFunction::build(CompileContext* context)
{
    llvm::BasicBlock* block = llvm::BasicBlock::Create(*context->llvmContext(), "entry", native_function_);

    context->ir()->SetInsertPoint(block);

    for (auto* arg : arguments_) { arg->build(context); }

    for (auto* statement : statements_)
    {
        context->ir()->SetCurrentDebugLocation(llvm::DILocation::get(*context->llvmContext(),
                                                                     statement->line(),
                                                                     statement->column(),
                                                                     native_function_->getSubprogram()));

        statement->build(context);

        if (has_return_)
        {
            if (return_value_)
            {
                return_value_->buildContentValue(context);
                context->ir()->CreateRet(return_value_->getContentValue());
            }
            else
            {
                context->ir()->CreateRetVoid();
            }

            break;
        }
    }

    if (!has_return_)
    {
        if (getReturnType() == ance::VoidType::get()) { context->ir()->CreateRetVoid(); }
        else
        {
            assert(true && "Functions with return type that is not void require a return statement.");
        }
    }

    context->ir()->SetCurrentDebugLocation(nullptr);
}

void ance::DefinedFunction::addReturn(ance::Value* value)
{
    if (value)
    {
        assert(value->type() == getReturnType());
        return_value_ = value;
        has_return_   = true;
    }
    else
    {
        assert(getReturnType() == ance::VoidType::get());
        return_value_ = nullptr;
        has_return_   = true;
    }
}

ance::Value* ance::DefinedFunction::buildCall(const std::vector<ance::Value*>& arguments, CompileContext* context) const
{
    assert(arguments.size() == native_type_->getNumParams());

    for (auto pair : llvm::zip(parameters_, arguments))
    {
        assert(std::get<0>(pair)->type() == std::get<1>(pair)->type() && "Input parameter types must match.");
    }

    llvm::Value* content_value = buildCall(arguments, native_type_, native_function_, context);

    if (getReturnType() == ance::VoidType::get()) { return nullptr; }

    llvm::Value* native_value = ance::Values::contentToNative(getReturnType(), content_value, context);
    return new ance::WrappedNativeValue(getReturnType(), native_value);
}

llvm::DISubprogram* ance::DefinedFunction::debugSubprogram()
{
    return native_function_->getSubprogram();
}

ance::GlobalScope* ance::DefinedFunction::getGlobalScope()
{
    return containing_scope_->getGlobalScope();
}

ance::LocalScope* ance::DefinedFunction::getFunctionScope()
{
    return function_scope_;
}

llvm::DIScope* ance::DefinedFunction::getDebugScope(CompileContext*)
{
    return debugSubprogram();
}

bool ance::DefinedFunction::validate()
{
    return function_scope_->validate();
}

ance::Variable* ance::DefinedFunction::getVariable(std::string identifier)
{
    return function_scope_->getVariable(identifier);
}

bool ance::DefinedFunction::isTypeRegistered(const std::string& type_name)
{
    return function_scope_->isTypeRegistered(type_name);
}

ance::Type* ance::DefinedFunction::getType(const std::string& type_name)
{
    return function_scope_->getType(type_name);
}

void ance::DefinedFunction::registerType(ance::Type* type)
{
    function_scope_->registerType(type);
}
