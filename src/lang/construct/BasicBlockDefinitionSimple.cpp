#include "BasicBlock.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"

lang::BasicBlock::Definition::Simple::Simple() = default;

lang::BasicBlock::Definition::Simple::Simple(Statement* statement)
{
    statements_.push_back(statement);
}

void lang::BasicBlock::Definition::Simple::complete(size_t& index)
{
    for (auto& statement : statements_) { self()->addStatement(*statement); }

    if (next_) next_->complete(index);
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

void lang::BasicBlock::Definition::Simple::simplify()
{
    if (!next_) { return; }

    // This block is the only block entering the next (real) block, or this block is unnecessary.
    bool can_simplify = (next_->getIncomingLinkCount() == 1 && !next_->isMeta()) || statements_.empty();

    if (can_simplify)
    {
        next_->transferStatements(statements_);
        this->updateIncomingLinks(next_);

        self()->unused_ = true;
    }

    next_->simplify();
}

void lang::BasicBlock::Definition::Simple::transferStatements(std::list<Statement*>& statements)
{
    statements_.splice(statements_.begin(), statements);
}

std::list<lang::BasicBlock*> lang::BasicBlock::Definition::Simple::getLeaves()
{
    std::list<lang::BasicBlock*> leaves;

    if (next_) { leaves.splice(leaves.end(), next_->getLeaves()); }
    else {
        leaves.push_back(self());
    }

    return leaves;
}

std::vector<lang::BasicBlock*> lang::BasicBlock::Definition::Simple::getSuccessors()
{
    std::vector<lang::BasicBlock*> successors;

    if (next_) { successors.push_back(next_); }

    return successors;
}

lang::Location lang::BasicBlock::Definition::Simple::getStartLocation()
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.front()->location();
}

lang::Location lang::BasicBlock::Definition::Simple::getEndLocation()
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.back()->location();
}

void lang::BasicBlock::Definition::Simple::reach()
{
    if (next_) { next_->reach(); }
}

void lang::BasicBlock::Definition::Simple::prepareBuild(CompileContext& context, llvm::Function* native_function)
{
    std::string name = "b" + std::to_string(index_);
    native_block_    = llvm::BasicBlock::Create(*context.llvmContext(), name, native_function);

    if (next_) next_->prepareBuild(context, native_function);
}

void lang::BasicBlock::Definition::Simple::doBuild(CompileContext& context)
{
    context.ir()->SetInsertPoint(native_block_);

    for (auto& statement : statements_) { statement->build(context); }

    if (next_ != nullptr)
    {
        context.ir()->CreateBr(next_->definition_->getNativeBlock());
        next_->doBuild(context);
    }
    else { context.ir()->CreateRetVoid(); }
}

std::string lang::BasicBlock::Definition::Simple::getExitRepresentation()
{
    return "// ---";
}

