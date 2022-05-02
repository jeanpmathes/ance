#include "CustomFunction.h"

#include <utility>

#include <llvm/ADT/SmallVector.h>// critical, missing include will cause linking error

#include "lang/construct/Function.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/LocalScope.h"
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
                                     std::unique_ptr<Statement>                    code,
                                     lang::Scope*                                  containing_scope,
                                     lang::Location                                declaration_location,
                                     lang::Location                                definition_location)
    : lang::FunctionDefinition(function,
                               containing_scope,
                               return_type,
                               return_type_location,
                               std::move(parameters),
                               declaration_location)
    , code_(std::move(code))
    , access_(access)
    , definition_location_(definition_location)
    , initial_block_(lang::BasicBlock::createEmpty())
{
    setupCode();

    containing_scope->addType(return_type);

    unsigned no = 1;
    for (const auto& parameter : this->parameters())
    {
        containing_scope->addType(parameter->type());

        auto arg = function->defineParameterVariable(parameter->name(),
                                                     parameter->type(),
                                                     parameter->typeLocation(),
                                                     parameter,
                                                     no++,
                                                     parameter->location());
        arguments_.push_back(arg);
    }
}

void lang::CustomFunction::setupCode()
{
    addChild(*code_);

    code_->setContainingScope(this->function());
    inside_scope_ = code_->getBlockScope();
    assert(inside_scope_);

    code_->walkDefinitions();
}

bool lang::CustomFunction::isMangled() const
{
    return true;
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
    code_->validate(validation_logger);
}

void lang::CustomFunction::expand()
{
    clearChildren();

    Statements expanded_statements = code_->expand();
    assert(expanded_statements.size() == 1);

    code_ = std::move(expanded_statements.front());

    setupCode();
}

void lang::CustomFunction::determineFlow()
{
    blocks_ = code_->createBasicBlocks(*initial_block_, function());

    initial_block_->setContainingFunction(function());

    for (auto& block : blocks_) { block->setContainingFunction(function()); }

    initial_block_->simplify();

    for (auto& block : blocks_) { block->simplify(); }

    size_t running_index = 0;
    initial_block_->finalize(running_index);
    used_blocks_.push_back(initial_block_.get());

    for (auto& block : blocks_)
    {
        block->finalize(running_index);
        if (block->isUsable()) { used_blocks_.push_back(block.get()); }
    }
}

bool lang::CustomFunction::validateFlow(ValidationLogger& validation_logger)
{
    validateReturn(validation_logger);
    validateUnreachable(validation_logger);

    return true;
}

void lang::CustomFunction::validateReturn(ValidationLogger& validation_logger)
{
    std::list<lang::BasicBlock*> final_blocks = initial_block_->getLeaves();

    std::optional<lang::Location> missing_return_location;

    for (auto* block : final_blocks)
    {
        std::optional<std::pair<std::shared_ptr<lang::Value>, lang::Location>> return_value = block->getReturnValue();

        if (return_value)
        {
            auto& [value, location] = *return_value;

            if (value)
            {
                if (returnType()->isVoidType())
                {
                    validation_logger.logError("Cannot return value in void function '" + name() + "'",
                                               this->location());
                }
                else {
                    lang::Type::checkMismatch(returnType(), value->type(), location, validation_logger);
                }
            }
            else if (!returnType()->isVoidType()) {
                validation_logger.logError("Missing return value in function '" + name() + "'", location);
            }
            else {
                // No value, but void return type -> OK
            }
        }
        else {
            if (!returnType()->isVoidType())
            {
                lang::Location end = block->getEndLocation();
                if (end.isGlobal()) end = this->location();
                missing_return_location = end;
            }
        }
    }

    if (missing_return_location)
    {
        validation_logger.logError("Not all code paths of '" + name() + "' return a value", *missing_return_location);
    }
}

void lang::CustomFunction::validateUnreachable(ValidationLogger& validation_logger)
{
    initial_block_->reach();

    std::optional<lang::Location> unreachable_code_location;

    for (auto& block : blocks_)
    {
        if (block->isUnreached()) { unreachable_code_location = block->getStartLocation(); }
    }

    if (unreachable_code_location)
    {
        validation_logger.logWarning("Unreachable code in function '" + name() + "'", *unreachable_code_location);
    }
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
    llvm::BasicBlock* decl = llvm::BasicBlock::Create(*context->llvmContext(), "decl", native_function_);

    context->ir()->SetInsertPoint(decl);
    function()->buildDeclarations(context);
    inside_scope_->buildDeclarations(context);

    llvm::BasicBlock* defs = llvm::BasicBlock::Create(*context->llvmContext(), "defs", native_function_);

    context->ir()->CreateBr(defs);
    context->ir()->SetInsertPoint(defs);
    for (auto& arg : arguments_) { (*arg)->buildDefinition(context); }

    initial_block_->prepareBuild(context, native_function_);
    initial_block_->doBuild(context);

    context->ir()->SetCurrentDebugLocation(llvm::DebugLoc());
    context->di()->finalizeSubprogram(native_function_->getSubprogram());
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
    return inside_scope_;
}

const std::vector<lang::BasicBlock*>& lang::CustomFunction::getBasicBlocks() const
{
    return used_blocks_;
}

llvm::DIScope* lang::CustomFunction::getDebugScope(CompileContext*)
{
    return debugSubprogram();
}
