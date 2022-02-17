#include "BasicBlock.h"

#include "compiler/CompileContext.h"

lang::BasicBlock* lang::BasicBlock::createEmpty()
{
    auto block         = new BasicBlock();
    block->definition_ = std::make_unique<Definition::Empty>();

    return block;
}

lang::BasicBlock* lang::BasicBlock::createSimple(std::unique_ptr<Statement> statement)
{
    auto block         = new BasicBlock();
    block->definition_ = std::make_unique<Definition::Simple>(std::move(statement));

    return block;
}

void lang::BasicBlock::link(lang::BasicBlock& next)
{
    assert(!finalized_);
    definition_->link(next);
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

    definition_->setIndex(index++);
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

void lang::BasicBlock::Definition::Base::setIndex(size_t index)
{
    index_ = index;
}

void lang::BasicBlock::Definition::Empty::link(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(next_ptr->definition_.get() != this);
    assert(next_ == nullptr);

    next_ = next_ptr;
}

void lang::BasicBlock::Definition::Empty::setContainingFunction(lang::Function*) {}

void lang::BasicBlock::Definition::Empty::validate(ValidationLogger&) {}

void lang::BasicBlock::Definition::Empty::prepareBuild(CompileContext* context, llvm::Function* native_function)
{
    std::string name = "b" + std::to_string(index_);
    native_block_    = llvm::BasicBlock::Create(*context->llvmContext(), name, native_function);

    if (next_) next_->prepareBuild(context, native_function);
}

void lang::BasicBlock::Definition::Empty::doBuild(CompileContext* context)
{
    context->ir()->CreateBr(native_block_);// Branch from prelude in function to this block
    context->ir()->SetInsertPoint(native_block_);

    if (next_ != nullptr)
    {
        context->ir()->CreateBr(next_->definition_->native_block_);
        next_->doBuild(context);
    }
}

lang::BasicBlock::Definition::Simple::Simple(std::unique_ptr<Statement> statement)
{
    statements_.push_back(std::move(statement));
}

void lang::BasicBlock::Definition::Simple::link(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(next_ptr->definition_.get() != this);
    assert(next_ == nullptr);

    next_ = next_ptr;
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
        context->ir()->CreateBr(next_->definition_->native_block_);
        next_->doBuild(context);
    }
}
