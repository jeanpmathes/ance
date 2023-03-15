#include "StatementFunction.h"

#include <utility>

#include <llvm/ADT/SmallVector.h>// critical, missing include will cause linking error

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/scope/LocalScope.h"
#include "lang/type/Type.h"
#include "lang/type/VoidType.h"
#include "validation/ValidationLogger.h"

lang::StatementFunction::StatementFunction(Function&                            function,
                                           lang::AccessModifier                 access,
                                           lang::ResolvingHandle<lang::Type>    return_type,
                                           lang::Location                       return_type_location,
                                           std::vector<Shared<lang::Parameter>> parameters,
                                           Statement&                           code,
                                           Scope&                               containing_scope,
                                           lang::Location                       declaration_location)
    : lang::FunctionDefinition(function,
                               containing_scope,
                               return_type,
                               return_type_location,
                               std::move(parameters),
                               declaration_location)
    , code_(code)
    , access_(access)
    , initial_block_(lang::BasicBlock::createEmpty())
{
    setupCode();
}

std::pair<llvm::FunctionType*, llvm::Function*> lang::StatementFunction::getNativeRepresentation() const
{
    return std::make_pair(native_type_, native_function_);
}

void lang::StatementFunction::setupCode()
{
    function().addChild(code_);

    code_.setContainingScope(this->function());
    inside_scope_ = code_.getBlockScope();
    assert(inside_scope_);

    code_.walkDefinitions();

    scope().addType(returnType());

    unsigned no = 1;
    for (auto& parameter : this->parameters())
    {
        scope().addType(parameter->type());

        auto arg = function().defineParameterVariable(parameter->name(),
                                                      parameter->type(),
                                                      parameter->typeLocation(),
                                                      parameter,
                                                      no++,
                                                      parameter->location());
        arguments_.emplace_back(arg);
    }
}

lang::AccessModifier lang::StatementFunction::access() const
{
    return access_;
}

Statement const* lang::StatementFunction::code() const
{
    return &code_;
}

void lang::StatementFunction::postResolve()
{
    code_.postResolve();
}

void lang::StatementFunction::determineFlow()
{
    blocks_ = code_.createBasicBlocks(*initial_block_, function());

    lang::BasicBlock* last = blocks_.empty() ? initial_block_.get() : blocks_.back().get();
    blocks_.push_back(lang::BasicBlock::createFinalizing(function(), "function"));
    last->link(*blocks_.back());

    initial_block_->setContainingFunction(function());

    for (auto& block : blocks_) { block->setContainingFunction(function()); }

    initial_block_->simplify();

    for (auto& block : blocks_) { block->simplify(); }

    size_t running_index = 0;
    initial_block_->complete(running_index);
    used_blocks_.push_back(initial_block_.get());

    for (auto& block : blocks_)
    {
        block->complete(running_index);
        if (block->isUsable()) { used_blocks_.push_back(block.get()); }
    }
}

bool lang::StatementFunction::validateFlow(ValidationLogger&) const
{
    return true;
}

lang::BasicBlock const& lang::StatementFunction::getInitialBlock() const
{
    return *initial_block_;
}

Optional<lang::Location> lang::StatementFunction::findUnreachableCode() const
{
    initial_block_->reach();

    Optional<lang::Location> unreachable_code_location;

    for (auto& block : blocks_)
    {
        if (block->isUnreached()) { unreachable_code_location = block->getStartLocation(); }
    }

    return unreachable_code_location;
}

void lang::StatementFunction::createNativeBacking(CompileContext& context)
{
    std::tie(native_type_, native_function_) =
        createNativeFunction(access_.linkage(), context.llvmContext(), context.llvmModule());

    auto params = parameters();

    for (unsigned int i = 0; i < params.size(); ++i) { params[i]->wrap(native_function_->getArg(i)); }
}

void lang::StatementFunction::build(CompileContext& context)
{
    llvm::BasicBlock* decl = llvm::BasicBlock::Create(context.llvmContext(), "decl", native_function_);

    context.ir().SetInsertPoint(decl);
    function().buildDeclarations(context);
    inside_scope_->buildDeclarations(context);

    llvm::BasicBlock* defs = llvm::BasicBlock::Create(context.llvmContext(), "defs", native_function_);

    context.ir().CreateBr(defs);
    context.ir().SetInsertPoint(defs);
    for (auto& arg : arguments_) { (*arg)->buildDefinition(context); }

    initial_block_->prepareBuild(context, native_function_);
    initial_block_->doBuild(context);

    context.ir().SetCurrentDebugLocation(llvm::DebugLoc());
    context.di().finalizeSubprogram(native_function_->getSubprogram());
}

lang::LocalScope* lang::StatementFunction::getInsideScope()
{
    return inside_scope_;
}

std::vector<lang::BasicBlock*> const& lang::StatementFunction::getBasicBlocks() const
{
    return used_blocks_;
}

llvm::DIScope* lang::StatementFunction::getDebugScope(CompileContext&) const
{
    return native_function_->getSubprogram();
}

std::vector<Optional<lang::ResolvingHandle<lang::Variable>>> const& lang::StatementFunction::arguments() const
{
    return arguments_;
}
