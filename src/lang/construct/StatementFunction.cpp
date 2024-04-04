#include "StatementFunction.h"

#include <utility>

#include <llvm/ADT/SmallVector.h>// critical, missing include will cause linking error

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
{}

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

        auto parameter_variable = lang::LocalVariable::makeParameterVariable(*parameter, index++, function());

        parameter->argument(parameter_variable.handle());

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

    initial_block_->reach();
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

void lang::StatementFunction::registerDeclarationsFollowingOrder(Execution& exec) const
{
    lang::OrderedScope* ordered_scope = code_.getBlockScope();
    if (ordered_scope == nullptr) return;

    ordered_scope->registerEntityDeclarations(exec);
}

lang::BasicBlock const* lang::StatementFunction::getEntryBlock() const
{
    return initial_block_.get();
}

std::vector<lang::BasicBlock*> const& lang::StatementFunction::getBasicBlocks() const
{
    return used_blocks_;
}
