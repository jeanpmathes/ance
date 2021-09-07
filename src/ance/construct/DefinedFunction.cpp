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
                                       const std::string&            function_name,
                                       ance::Type*                   return_type,
                                       std::vector<ance::Parameter*> parameters,
                                       ance::Scope*                  scope,
                                       ance::Location                declaration_location,
                                       ance::Location                definition_location)
    : ance::Function(function_name, return_type, std::move(parameters), declaration_location)
    , access_(access)
    , definition_location_(definition_location)
    , containing_scope_(scope)
    , function_scope_(new ance::LocalScope(this))
{
    unsigned no = 1;
    for (auto* parameter : this->parameters())
    {
        ance::LocalVariable* arg = function_scope_->defineParameterVariable(parameter->name(),
                                                                            parameter->type(),
                                                                            Assigner::COPY_ASSIGNMENT,
                                                                            parameter,
                                                                            no++,
                                                                            parameter->location());
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
        createNativeFunction(access_.linkage(), *context->llvmContext(), context->module());

    std::vector<llvm::Metadata*> di_types;
    di_types.push_back(returnType()->getDebugType(context));

    for (const auto& pair : zip(parameters(), native_function_->args()))
    {
        const auto& [parameter, argument] = pair;
        parameter->wrap(&argument);

        di_types.push_back(parameter->type()->getDebugType(context));
    }

    llvm::DISubroutineType* debug_type =
        context->di()->createSubroutineType(context->di()->getOrCreateTypeArray(di_types));
    llvm::DISubprogram* subprogram =
        context->di()->createFunction(containing_scope_->getDebugScope(context),
                                      name(),
                                      llvm::StringRef(),
                                      context->sourceFile(),
                                      location().line(),
                                      debug_type,
                                      definition_location_.line(),
                                      llvm::DINode::DIFlags::FlagPrototyped,
                                      llvm::DISubprogram::toSPFlags(false, true, false, 0U, name() == "main"));

    native_function_->setSubprogram(subprogram);
}

void ance::DefinedFunction::build(CompileContext* context)
{
    llvm::BasicBlock* block = llvm::BasicBlock::Create(*context->llvmContext(), "entry", native_function_);

    context->ir()->SetInsertPoint(block);

    for (auto* arg : arguments_) { arg->build(context); }

    for (auto* statement : statements_)
    {
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
        if (returnType() == ance::VoidType::get()) { context->ir()->CreateRetVoid(); }
        else
        {
            // todo should actually be part of validation step
            assert(false && "Functions with return type that is not void require a return statement.");
        }
    }

    context->ir()->SetCurrentDebugLocation(llvm::DebugLoc());
    context->di()->finalizeSubprogram(native_function_->getSubprogram());
}

void ance::DefinedFunction::addReturn(ance::Value* value)
{
    if (value)
    {
        assert(value->type() == returnType());
        return_value_ = value;
        has_return_   = true;
    }
    else
    {
        assert(returnType() == ance::VoidType::get());
        return_value_ = nullptr;
        has_return_   = true;
    }
}

ance::Value* ance::DefinedFunction::buildCall(const std::vector<ance::Value*>& arguments, CompileContext* context) const
{
    llvm::Value* content_value = buildCall(arguments, native_type_, native_function_, context);

    if (returnType() == ance::VoidType::get()) { return nullptr; }

    llvm::Value* native_value = ance::Values::contentToNative(returnType(), content_value, context);
    return new ance::WrappedNativeValue(returnType(), native_value);
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

void ance::DefinedFunction::validate(ValidationLogger& validation_logger)
{
    function_scope_->validate(validation_logger);

    for (auto statement : statements_) { statement->validate(validation_logger); }
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
