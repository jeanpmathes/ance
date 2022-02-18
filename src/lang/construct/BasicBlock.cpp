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
    definition_->setContainingFunction(function);
}

void lang::BasicBlock::finalize(size_t& index)
{
    if (finalized_) return;
    finalized_ = true;

    definition_->setIndex(index);
    definition_->finalize(index);
}

void lang::BasicBlock::validate(ValidationLogger& validation_logger)
{
    assert(finalized_);
    definition_->validate(validation_logger);
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

llvm::BasicBlock* lang::BasicBlock::Definition::Base::getNativeBlock()
{
    return native_block_;
}

void lang::BasicBlock::Definition::Empty::finalize(size_t& index)
{
    if (next_) next_->finalize(index);
}

void lang::BasicBlock::Definition::Empty::setLink(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(next_ptr->definition_.get() != this);
    assert(next_ == nullptr);

    next_ = next_ptr;
    next_->registerIncomingLink(*self());
}

void lang::BasicBlock::Definition::Empty::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    assert(next_ == former);
    assert(next_ != updated);

    next_ = updated;
    next_->registerIncomingLink(*self());
}

void lang::BasicBlock::Definition::Empty::transferStatements(std::list<Statement*>&)
{
    assert(false);
}

void lang::BasicBlock::Definition::Empty::simplify()
{
    if (next_) next_->simplify();
}

void lang::BasicBlock::Definition::Empty::setContainingFunction(lang::Function*) {}

void lang::BasicBlock::Definition::Empty::validate(ValidationLogger&) {}

void lang::BasicBlock::Definition::Empty::prepareBuild(CompileContext* context, llvm::Function* native_function)
{
    std::string name = "e" + std::to_string(index_);
    native_block_    = llvm::BasicBlock::Create(*context->llvmContext(), name, native_function);

    if (next_) next_->prepareBuild(context, native_function);
}

void lang::BasicBlock::Definition::Empty::doBuild(CompileContext* context)
{
    context->ir()->CreateBr(native_block_);// Branch from prelude in function to this block
    context->ir()->SetInsertPoint(native_block_);

    if (next_ != nullptr)
    {
        context->ir()->CreateBr(next_->definition_->getNativeBlock());
        next_->doBuild(context);
    }
}

lang::BasicBlock::Definition::Simple::Simple(Statement* statement)
{
    statements_.push_back(statement);
}

void lang::BasicBlock::Definition::Simple::finalize(size_t& index)
{
    if (next_) next_->finalize(index);
}

void lang::BasicBlock::Definition::Simple::setLink(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(next_ptr->definition_.get() != this);
    assert(next_ == nullptr);

    next_ = next_ptr;
    next_->registerIncomingLink(*self());
}

void lang::BasicBlock::Definition::Simple::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    assert(next_ == former);
    assert(next_ != updated);

    next_ = updated;
    next_->registerIncomingLink(*self());
}

void lang::BasicBlock::Definition::Simple::transferStatements(std::list<Statement*>& statements)
{
    statements_.splice(statements_.begin(), statements);
}

void lang::BasicBlock::Definition::Simple::simplify()
{
    if (!next_) { return; }

    bool can_simplify = next_->getIncomingLinkCount() == 1;// This block is the only block entering the next block.

    if (can_simplify)
    {
        next_->transferStatements(statements_);
        this->updateIncomingLinks(next_);
    }

    next_->simplify();
}

void lang::BasicBlock::Definition::Simple::setContainingFunction(lang::Function* function)
{
    for (auto& statement : statements_) { statement->setContainingFunction(function); }
}

void lang::BasicBlock::Definition::Simple::validate(ValidationLogger& validation_logger)
{
    for (auto& statement : statements_) { statement->validate(validation_logger); }
}

void lang::BasicBlock::Definition::Simple::prepareBuild(CompileContext* context, llvm::Function* native_function)
{
    std::string name = "b" + std::to_string(index_);
    native_block_    = llvm::BasicBlock::Create(*context->llvmContext(), name, native_function);

    if (next_) next_->prepareBuild(context, native_function);
}

void lang::BasicBlock::Definition::Simple::doBuild(CompileContext* context)
{
    context->ir()->SetInsertPoint(native_block_);

    for (auto& statement : statements_) { statement->build(context); }

    if (next_ != nullptr)
    {
        context->ir()->CreateBr(next_->definition_->getNativeBlock());
        next_->doBuild(context);
    }
}
