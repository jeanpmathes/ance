#include "BasicBlock.h"

#include "compiler/CompileContext.h"
#include "lang/scope/Scope.h"

lang::BasicBlock::Definition::Finalizing::Finalizing(lang::Scope* scope) : scope_(scope) {}

bool lang::BasicBlock::Definition::Finalizing::isMeta() const
{
    return true;
}

void lang::BasicBlock::Definition::Finalizing::complete(size_t& index)
{
    if (next_) next_->complete(index);
}

void lang::BasicBlock::Definition::Finalizing::setLink(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(next_ptr->definition_.get() != this);
    assert(next_ == nullptr);

    next_ = next_ptr;
    next_->registerIncomingLink(*self());
}

void lang::BasicBlock::Definition::Finalizing::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    assert(next_ == former);
    assert(next_ != updated);

    next_ = updated;
    next_->registerIncomingLink(*self());
}

void lang::BasicBlock::Definition::Finalizing::transferStatements(std::list<Statement*>& list)
{
    assert(list.empty());
}

void lang::BasicBlock::Definition::Finalizing::simplify()
{
    if (next_) next_->simplify();
}

std::list<lang::BasicBlock*> lang::BasicBlock::Definition::Finalizing::getLeaves()
{
    std::list<lang::BasicBlock*> leaves;

    if (next_) { leaves.splice(leaves.end(), next_->getLeaves()); }
    else { leaves.push_back(self()); }

    return leaves;
}

std::vector<lang::BasicBlock*> lang::BasicBlock::Definition::Finalizing::getSuccessors()
{
    std::vector<lang::BasicBlock*> successors;

    if (next_) { successors.push_back(next_); }

    return successors;
}

lang::Location lang::BasicBlock::Definition::Finalizing::getStartLocation()
{
    return lang::Location::global();
}

lang::Location lang::BasicBlock::Definition::Finalizing::getEndLocation()
{
    return lang::Location::global();
}

void lang::BasicBlock::Definition::Finalizing::reach()
{
    if (next_) next_->reach();
}

void lang::BasicBlock::Definition::Finalizing::prepareBuild(CompileContext* context, llvm::Function* native_function)
{
    std::string name = "b" + std::to_string(index_);
    native_block_    = llvm::BasicBlock::Create(*context->llvmContext(), name, native_function);

    if (next_) next_->prepareBuild(context, native_function);
}

void lang::BasicBlock::Definition::Finalizing::doBuild(CompileContext* context)
{
    context->ir()->SetInsertPoint(native_block_);

    scope_->buildFinalization(context);

    if (next_ != nullptr)
    {
        context->ir()->CreateBr(next_->definition_->getNativeBlock());
        next_->doBuild(context);
    }
    else { context->ir()->CreateRetVoid(); }
}

std::string lang::BasicBlock::Definition::Finalizing::getExitRepresentation()
{
    return "// finalize ";
}
