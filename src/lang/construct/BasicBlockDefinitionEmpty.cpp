#include "BasicBlock.h"

#include "compiler/CompileContext.h"

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
