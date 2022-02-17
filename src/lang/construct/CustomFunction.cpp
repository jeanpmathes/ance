#include "CustomFunction.h"

#include <utility>

#include <llvm/ADT/SmallVector.h>// critical, missing include will cause linking error

#include "lang/construct/Function.h"
#include "lang/construct/Variable.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/LocalScope.h"
#include "lang/statement/Statement.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/Type.h"
#include "lang/type/VoidType.h"
#include "lang/utility/Values.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"
#include "lang/AccessModifier.h"

lang::CustomFunction::CustomFunction(lang::Function*                               function,
                                     lang::AccessModifier                          access,
                                     lang::ResolvingHandle<lang::Type>             return_type,
                                     lang::Location                                return_type_location,
                                     std::vector<std::shared_ptr<lang::Parameter>> parameters,
                                     lang::Scope*                                  containing_scope,
                                     lang::Location                                declaration_location,
                                     lang::Location                                definition_location)
    : lang::FunctionDefinition(function,
                               containing_scope,
                               return_type,
                               return_type_location,
                               std::move(parameters),
                               declaration_location)
    , access_(access)
    , definition_location_(definition_location)
    , inside_scope_(std::make_unique<lang::LocalScope>(this->function()))
{
    containing_scope->addType(return_type);

    unsigned no = 1;
    for (const auto& parameter : this->parameters())
    {
        containing_scope->addType(parameter->type());

        auto arg = inside_scope_->defineParameterVariable(parameter->name(),
                                                          parameter->type(),
                                                          parameter->typeLocation(),
                                                          parameter,
                                                          no++,
                                                          parameter->location());
        arguments_.push_back(arg);
    }
}

bool lang::CustomFunction::isMangled() const
{
    return true;
}

void lang::CustomFunction::pushStatement(std::unique_ptr<Statement> statement)
{
    Statement* stmt = statement.get();
    statements_.push_back(std::move(statement));
    stmt->setContainingFunction(function());
}

void lang::CustomFunction::createNativeBacking(CompileContext* context)
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
                                      signature_.getMangledName(),
                                      context->sourceFile(),
                                      location().line(),
                                      debug_type,
                                      definition_location_.line(),
                                      llvm::DINode::DIFlags::FlagPrototyped,
                                      llvm::DISubprogram::toSPFlags(false, true, false, 0U, name() == "main"));

    native_function_->setSubprogram(subprogram);
}

void lang::CustomFunction::build(CompileContext* context)
{
    llvm::BasicBlock* entry = llvm::BasicBlock::Create(*context->llvmContext(), "entry", native_function_);
    llvm::BasicBlock* code  = llvm::BasicBlock::Create(*context->llvmContext(), "code", native_function_);

    context->ir()->SetInsertPoint(entry);

    inside_scope_->buildDeclarations(context);// Arguments are also local variables in the function scope.

    context->ir()->CreateBr(code);
    context->ir()->SetInsertPoint(code);

    for (auto& arg : arguments_) { (*arg)->buildDefinition(context); }

    for (auto& statement : statements_)
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
        if (returnType()->isVoidType()) { context->ir()->CreateRetVoid(); }
        else {
            // todo should actually be part of validation step
            assert(false && "Functions with return type that is not void require a return statement.");
        }
    }

    context->ir()->SetCurrentDebugLocation(llvm::DebugLoc());
    context->di()->finalizeSubprogram(native_function_->getSubprogram());
}

void lang::CustomFunction::addReturn(const std::shared_ptr<lang::Value>& value)
{
    if (value)
    {
        assert(lang::Type::areSame(value->type(), returnType()));
        return_value_ = lang::Type::makeActual(value);
        has_return_   = true;
    }
    else {
        assert(returnType()->isVoidType());
        return_value_ = nullptr;
        has_return_   = true;
    }
}

std::shared_ptr<lang::Value> lang::CustomFunction::buildCall(const std::vector<std::shared_ptr<lang::Value>>& arguments,
                                                             CompileContext* context) const
{
    llvm::Value* content_value = buildCall(arguments, native_type_, native_function_, context);

    if (returnType()->isVoidType()) { return nullptr; }

    llvm::Value* native_value = lang::Values::contentToNative(returnType(), content_value, context);
    return std::make_shared<lang::WrappedNativeValue>(returnType(), native_value);
}

llvm::DISubprogram* lang::CustomFunction::debugSubprogram()
{
    return native_function_->getSubprogram();
}

lang::LocalScope* lang::CustomFunction::getInsideScope()
{
    return inside_scope_.get();
}

void lang::CustomFunction::validate(ValidationLogger& validation_logger)
{
    if (!returnType()->isDefined())
    {
        validation_logger.logError("Return type " + returnType()->getAnnotatedName() + " not defined.",
                                   returnTypeLocation());
        return;
    }

    returnType()->validate(validation_logger, returnTypeLocation());

    for (const auto& [parameter, argument] : llvm::zip(parameters(), arguments_))
    {
        if (!argument)
        {
            validation_logger.logError("Name '" + parameter->name() + "' already defined in the current context",
                                       parameter->location());
        }

        if (!parameter->type()->isDefined())
        {
            validation_logger.logError("Parameter type " + parameter->type()->getAnnotatedName() + " not defined.",
                                       parameter->typeLocation());

            return;
        }

        parameter->type()->validate(validation_logger, parameter->typeLocation());

        if (parameter->type() == lang::VoidType::get())
        {
            validation_logger.logError("Parameter cannot have 'void' type", parameter->location());
        }
    }

    inside_scope_->validate(validation_logger);

    for (auto& statement : statements_) { statement->validate(validation_logger); }
}

llvm::DIScope* lang::CustomFunction::getDebugScope(CompileContext*)
{
    return debugSubprogram();
}