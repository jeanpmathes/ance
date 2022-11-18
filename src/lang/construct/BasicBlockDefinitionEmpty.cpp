#include "BasicBlock.h"

#include "compiler/CompileContext.h"

bool lang::BasicBlock::Definition::Empty::isMeta() const
{
    return true;
}

void lang::BasicBlock::Definition::Empty::complete(size_t& index)
{
    if (next_) next_->complete(index);
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

std::list<lang::BasicBlock*> lang::BasicBlock::Definition::Empty::getLeaves()
{
    std::list<lang::BasicBlock*> leaves;

    if (next_) { leaves.splice(leaves.end(), next_->getLeaves()); }
    else { leaves.push_back(self()); }

    return leaves;
}

std::vector<lang::BasicBlock*> lang::BasicBlock::Definition::Empty::getSuccessors()
{
    std::vector<lang::BasicBlock*> successors;

    if (next_) { successors.push_back(next_); }

    return successors;
}

lang::Location lang::BasicBlock::Definition::Empty::getStartLocation()
{
    return lang::Location::global();
}

lang::Location lang::BasicBlock::Definition::Empty::getEndLocation()
{
    return lang::Location::global();
}

void lang::BasicBlock::Definition::Empty::reach()
{
    if (next_) next_->reach();
}

void lang::BasicBlock::Definition::Empty::prepareBuild(CompileContext& context, llvm::Function* native_function)
{
    std::string name = "b" + std::to_string(index_);
    native_block_    = llvm::BasicBlock::Create(*context.llvmContext(), name, native_function);

    if (next_) next_->prepareBuild(context, native_function);
}

void lang::BasicBlock::Definition::Empty::doBuild(CompileContext& context)
{
    context.ir()->CreateBr(native_block_);// Branch from prelude in function to this block
    context.ir()->SetInsertPoint(native_block_);

    if (next_ != nullptr)
    {
        context.ir()->CreateBr(next_->definition_->getNativeBlock());
        next_->doBuild(context);
    }
    else { context.ir()->CreateRetVoid(); }
}

std::string lang::BasicBlock::Definition::Empty::getExitRepresentation()
{
    return "// meta ";
}
