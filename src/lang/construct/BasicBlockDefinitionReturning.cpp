#include <utility>

#include "BasicBlock.h"

#include "compiler/CompileContext.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"

lang::BasicBlock::Definition::Returning::Returning(Expression* return_value) : return_value_(return_value) {}

void lang::BasicBlock::Definition::Returning::finalize(size_t& index)
{
    if (unreachable_next_) unreachable_next_->finalize(index);
}

void lang::BasicBlock::Definition::Returning::setLink(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(next_ptr->definition_.get() != this);
    assert(unreachable_next_ == nullptr);

    unreachable_next_ = next_ptr;
    unreachable_next_->registerIncomingLink(*self());
}

void lang::BasicBlock::Definition::Returning::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    assert(unreachable_next_ == former);
    assert(unreachable_next_ != updated);

    unreachable_next_ = updated;
    unreachable_next_->registerIncomingLink(*self());
}

void lang::BasicBlock::Definition::Returning::simplify()
{
    if (unreachable_next_) unreachable_next_->simplify();
}

void lang::BasicBlock::Definition::Returning::transferStatements(std::list<Statement*>& statements)
{
    statements_.splice(statements_.begin(), statements);
}

void lang::BasicBlock::Definition::Returning::setContainingFunction(lang::Function* function)
{
    for (auto& statement : statements_) { statement->setContainingFunction(function); }

    if (return_value_) return_value_->setContainingScope(function);
}

void lang::BasicBlock::Definition::Returning::validate(ValidationLogger& validation_logger)
{
    for (auto& statement : statements_) { statement->validate(validation_logger); }

    if (return_value_) { return_value_->validate(validation_logger); }

    if (unreachable_next_) { unreachable_next_->validate(validation_logger); }
}

void lang::BasicBlock::Definition::Returning::prepareBuild(CompileContext* context, llvm::Function* native_function)
{
    std::string name = "b" + std::to_string(index_);
    native_block_    = llvm::BasicBlock::Create(*context->llvmContext(), name, native_function);

    if (unreachable_next_) unreachable_next_->prepareBuild(context, native_function);
}

void lang::BasicBlock::Definition::Returning::doBuild(CompileContext* context)
{
    context->ir()->SetInsertPoint(native_block_);

    for (auto& statement : statements_) { statement->build(context); }

    if (return_value_)
    {
        std::shared_ptr<lang::Value> return_value = return_value_->getValue();
        return_value = lang::Type::makeMatching(self()->containing_function_->returnType(), return_value, context);

        return_value->buildContentValue(context);
        context->ir()->CreateRet(return_value->getContentValue());
    }
    else {
        context->ir()->CreateRetVoid();
    }
}
