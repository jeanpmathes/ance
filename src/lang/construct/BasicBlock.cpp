#include "BasicBlock.h"

#include "compiler/CompileContext.h"

std::unique_ptr<lang::BasicBlock> lang::BasicBlock::createEmpty()
{
    auto block = new BasicBlock();

    block->definition_ = std::make_unique<Definition::Empty>();
    block->definition_->setSelf(block);

    return std::unique_ptr<BasicBlock>(block);
}

std::unique_ptr<lang::BasicBlock> lang::BasicBlock::createSimple(Statement* statement)
{
    auto block = new BasicBlock();

    block->definition_ = std::make_unique<Definition::Simple>(statement);
    block->definition_->setSelf(block);

    return std::unique_ptr<BasicBlock>(block);
}

std::unique_ptr<lang::BasicBlock> lang::BasicBlock::createReturning(Expression*    expression,
                                                                    lang::Location return_location)
{
    auto block = new BasicBlock();

    block->definition_ = std::make_unique<Definition::Returning>(expression, return_location);
    block->definition_->setSelf(block);

    return std::unique_ptr<BasicBlock>(block);
}

void lang::BasicBlock::link(lang::BasicBlock& next)
{
    assert(!finalized_);
    definition_->setLink(next);
}

void lang::BasicBlock::simplify()
{
    assert(!finalized_);

    if (simplified_) return;
    simplified_ = true;

    definition_->simplify();
}

void lang::BasicBlock::setContainingFunction(lang::Function* function)
{
    assert(!finalized_);

    containing_function_ = function;
    definition_->setContainingFunction(function);
}

void lang::BasicBlock::finalize(size_t& index)
{
    if (finalized_) return;
    finalized_ = true;

    definition_->setIndex(index);
    definition_->finalize(index);
}

bool lang::BasicBlock::isUsable() const
{
    return !unused_;
}

void lang::BasicBlock::validate(ValidationLogger& validation_logger)
{
    assert(finalized_);

    if (validated_) return;
    validated_ = true;

    definition_->validate(validation_logger);
}

std::list<lang::BasicBlock*> lang::BasicBlock::getLeaves()
{
    assert(finalized_);
    assert(simplified_);

    if (!leaves_.has_value()) { leaves_ = definition_->getLeaves(); }

    return leaves_.value();
}

std::optional<std::pair<std::shared_ptr<lang::Value>, lang::Location>> lang::BasicBlock::getReturnValue()
{
    assert(finalized_);
    return definition_->getReturnValue();
}

lang::Location lang::BasicBlock::getStartLocation()
{
    assert(finalized_);
    return definition_->getStartLocation();
}

lang::Location lang::BasicBlock::getEndLocation()
{
    assert(finalized_);
    return definition_->getEndLocation();
}

void lang::BasicBlock::prepareBuild(CompileContext* context, llvm::Function* native_function)
{
    assert(finalized_);
    definition_->prepareBuild(context, native_function);
}

void lang::BasicBlock::doBuild(CompileContext* context)
{
    assert(finalized_);
    definition_->doBuild(context);
}

void lang::BasicBlock::registerIncomingLink(lang::BasicBlock& next)
{
    definition_->registerIncomingLink(next);
}

void lang::BasicBlock::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    definition_->updateLink(former, updated);
}

size_t lang::BasicBlock::getIncomingLinkCount() const
{
    return definition_->getIncomingLinkCount();
}

void lang::BasicBlock::transferStatements(std::list<Statement*>& statements)
{
    definition_->transferStatements(statements);
}

void lang::BasicBlock::reach()
{
    reached_ = true;
    definition_->reach();
}

bool lang::BasicBlock::isUnreached() const
{
    return !reached_ && !unused_;
}

void lang::BasicBlock::Definition::Base::setSelf(lang::BasicBlock* self)
{
    self_ = self;
}

lang::BasicBlock* lang::BasicBlock::Definition::Base::self()
{
    return self_;
}

void lang::BasicBlock::Definition::Base::setIndex(size_t& index)
{
    index_ = index;
    index++;
}

void lang::BasicBlock::Definition::Base::registerIncomingLink(lang::BasicBlock& block)
{
    incoming_links_.push_back(&block);
}

size_t lang::BasicBlock::Definition::Base::getIncomingLinkCount() const
{
    return incoming_links_.size();
}

void lang::BasicBlock::Definition::Base::updateIncomingLinks(lang::BasicBlock* updated)
{
    for (auto& link : incoming_links_) { link->updateLink(self(), updated); }

    incoming_links_.clear();
}

std::optional<std::pair<std::shared_ptr<lang::Value>, lang::Location>> lang::BasicBlock::Definition::Base::
    getReturnValue()
{
    return std::nullopt;
}

llvm::BasicBlock* lang::BasicBlock::Definition::Base::getNativeBlock()
{
    return native_block_;
}
