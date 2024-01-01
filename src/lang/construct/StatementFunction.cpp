#include "StatementFunction.h"

#include <utility>

#include <llvm/ADT/SmallVector.h>// critical, missing include will cause linking error

#include "compiler/CompileContext.h"
#include "lang/AccessModifier.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/type/Type.h"
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

}

void lang::StatementFunction::setup()
{
    function().addChild(code_);

    for (auto& parameter : this->parameters()) { function().prepareDefinition(parameter->name()); }

    code_.setContainingScope(this->function());
    inside_scope_ = code_.getBlockScope();
    assert(inside_scope_);

    scope().registerUsage(returnType());

    unsigned index = 0;
    for (auto& parameter : this->parameters())
    {
        scope().registerUsage(parameter->type());

        auto parameter_variable = lang::LocalVariable::makeParameterVariable(parameter->name(),
                                                                             parameter->type(),
                                                                             parameter->typeLocation(),
                                                                             parameter,
                                                                             index++,
                                                                             function(),
                                                                             parameter->location());
        arguments_.emplace_back(parameter_variable.handle());

        function().addEntity(std::move(parameter_variable));
    }

    code_.walkDefinitions();
}

lang::AccessModifier lang::StatementFunction::access() const
{
    return access_;
}

Statement const* lang::StatementFunction::code() const
{
    return &code_;
}

void lang::StatementFunction::resolveFollowingOrder()
{
    code_.getBlockScope()->resolve();
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

    Optional<lang::Location> unreachable;

    for (auto& block : blocks_)
    {
        if (block->isUnreached())
        {
            unreachable =
                lang::Location::getFirst(unreachable.valueOr(lang::Location::global()), block->getStartLocation());
            std::cout << "Comparing " << unreachable.value() << " and " << block->getStartLocation() << std::endl;
        }
    }

    return unreachable;
}

void lang::StatementFunction::build(CompileContext& context)
{
    llvm::Function* native_function = context.exec().llvmFunction(function_handle_.value());
    assert(native_function->getSubprogram() != nullptr);

    llvm::BasicBlock* decl = llvm::BasicBlock::Create(context.exec().llvmContext(), "decl", native_function);

    context.exec().ir().SetInsertPoint(decl);
    function().buildDeclarations(context);

    llvm::BasicBlock* defs = llvm::BasicBlock::Create(context.exec().llvmContext(), "defs", native_function);

    context.exec().ir().CreateBr(defs);
    context.exec().ir().SetInsertPoint(defs);
    for (auto& arg : arguments_) { (*arg)->buildInitialization(context); }

    initial_block_->prepareBuild(context, native_function);
    initial_block_->doBuild(context);

    context.exec().ir().SetCurrentDebugLocation(llvm::DebugLoc());
    context.exec().di().finalizeSubprogram(native_function->getSubprogram());
}

void lang::StatementFunction::buildDeclarationsFollowingOrder(CompileContext& context)
{
    code_.getBlockScope()->buildDeclarations(context);
}

std::vector<lang::BasicBlock*> const& lang::StatementFunction::getBasicBlocks() const
{
    return used_blocks_;
}

std::vector<Optional<lang::ResolvingHandle<lang::Variable>>> const& lang::StatementFunction::arguments() const
{
    return arguments_;
}
