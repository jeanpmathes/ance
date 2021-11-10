#include "CustomFunction.h"

#include <utility>

#include <llvm/ADT/SmallVector.h>// critical, missing include will cause linking error

#include "ance/construct/Function.h"
#include "ance/construct/Variable.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/LocalScope.h"
#include "ance/statement/Statement.h"
#include "ance/type/ReferenceType.h"
#include "ance/type/Type.h"
#include "ance/type/VoidType.h"
#include "ance/utility/Values.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::CustomFunction::CustomFunction(ance::Function*                               function,
                                     AccessModifier                                access,
                                     ance::ResolvingHandle<ance::Type>             return_type,
                                     std::vector<std::shared_ptr<ance::Parameter>> parameters,
                                     ance::Scope*                                  containing_scope,

                                     ance::Location declaration_location,
                                     ance::Location definition_location)
    : ance::FunctionDefinition(function, containing_scope, return_type, std::move(parameters), declaration_location)
    , access_(access)
    , definition_location_(definition_location)
    , inside_scope_(std::make_unique<ance::LocalScope>(this->function()))
{
    containing_scope->addType(return_type);

    unsigned no = 1;
    for (const auto& parameter : this->parameters())
    {
        containing_scope->addType(parameter->type());

        Assigner assigner = ance::ReferenceType::isReferenceType(parameter->type()) ? Assigner::REFERENCE_BINDING
                                                                                    : Assigner::COPY_ASSIGNMENT;

        auto arg = inside_scope_->defineParameterVariable(parameter->name(),
                                                          parameter->type(),
                                                          assigner,
                                                          parameter,
                                                          no++,
                                                          parameter->location());
        arguments_.push_back(arg);
    }
}

void ance::CustomFunction::pushStatement(Statement* statement)
{
    statements_.push_back(statement);
    statement->setContainingFunction(function());
}

void ance::CustomFunction::createNativeBacking(CompileContext* context)
{
    std::tie(native_type_, native_function_) =
        createNativeFunction(access_.linkage(), *context->llvmContext(), context->module());

    std::vector<llvm::Metadata*> di_types;
    di_types.push_back(returnType()->getDebugType(context));

    for (const auto& pair : llvm::zip(parameters(), native_function_->args()))
    {
        const auto& [parameter, argument] = pair;
        parameter->wrap(&argument);

        di_types.push_back(parameter->type()->getDebugType(context));
    }

    llvm::DISubroutineType* debug_type =
        context->di()->createSubroutineType(context->di()->getOrCreateTypeArray(di_types));
    llvm::DISubprogram* subprogram =
        context->di()->createFunction(scope()->getDebugScope(context),
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

void ance::CustomFunction::build(CompileContext* context)
{
    llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context->llvmContext(), "entry", native_function_);
    llvm::BasicBlock* code  = llvm::BasicBlock::Create(*context->llvmContext(), "code", native_function_);

    context->ir()->SetInsertPoint(entry);

    inside_scope_->buildDeclarations(context);// Arguments are also local variables in the function scope.

    context->ir()->CreateBr(code);
    context->ir()->SetInsertPoint(code);

    for (auto& arg : arguments_) { (*arg)->buildDefinition(context); }

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

void ance::CustomFunction::addReturn(const std::shared_ptr<ance::Value>& value)
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

std::shared_ptr<ance::Value> ance::CustomFunction::buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
                                                             CompileContext* context) const
{
    llvm::Value* content_value = buildCall(arguments, native_type_, native_function_, context);

    if (returnType() == ance::VoidType::get()) { return nullptr; }

    llvm::Value* native_value = ance::Values::contentToNative(returnType(), content_value, context);
    return std::make_shared<ance::WrappedNativeValue>(returnType(), native_value);
}

llvm::DISubprogram* ance::CustomFunction::debugSubprogram()
{
    return native_function_->getSubprogram();
}

ance::LocalScope* ance::CustomFunction::getInsideScope()
{
    return inside_scope_.get();
}

void ance::CustomFunction::validate(ValidationLogger& validation_logger)
{
    returnType()->validate(validation_logger, location());

    for (const auto& [parameter, argument] : llvm::zip(parameters(), arguments_))
    {
        if (!argument)
        {
            validation_logger.logError("Name '" + parameter->name() + "' already defined in the current context",
                                       parameter->location());
        }

        parameter->type()->validate(validation_logger, parameter->location());

        if (parameter->type() == ance::VoidType::get())
        {
            validation_logger.logError("Parameter cannot have 'void' type", parameter->location());
        }
    }

    inside_scope_->validate(validation_logger);

    for (auto statement : statements_) { statement->validate(validation_logger); }
}

llvm::DIScope* ance::CustomFunction::getDebugScope(CompileContext*)
{
    return debugSubprogram();
}
