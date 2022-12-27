#include "BasicBlock.h"

#include <set>

#include "compiler/CompileContext.h"
#include "lang/construct/value/Value.h"
#include "lang/expression/Expression.h"
#include "lang/type/BooleanType.h"

lang::BasicBlock::Definition::Branching::Branching(Expression* condition) : condition_(condition) {}

void lang::BasicBlock::Definition::Branching::complete(size_t& index)
{
    for (auto& statement : statements_) { self()->addStatement(*statement); }

    true_next_->complete(index);
    false_next_->complete(index);
}

void lang::BasicBlock::Definition::Branching::setLink(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(!true_next_ || !false_next_);

    if (!true_next_)
    {
        true_next_ = next_ptr;
        next.registerIncomingLink(*self());

        return;
    }

    if (!false_next_)
    {
        false_next_ = next_ptr;
        next.registerIncomingLink(*self());

        return;
    }

    assert(false);
}

void lang::BasicBlock::Definition::Branching::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    auto update = [&](lang::BasicBlock*& target) {
        assert(target != updated);

        target = updated;
        updated->registerIncomingLink(*self());
    };

    if (true_next_ == former) { update(true_next_); }
    if (false_next_ == former) { update(false_next_); }
}

void lang::BasicBlock::Definition::Branching::simplify()
{
    true_next_->simplify();
    false_next_->simplify();
}

void lang::BasicBlock::Definition::Branching::transferStatements(std::list<Statement*>& statements)
{
    statements_.splice(statements_.begin(), statements);
}

std::list<lang::BasicBlock const*> lang::BasicBlock::Definition::Branching::getLeaves() const
{
    std::set<lang::BasicBlock const*> leaves;

    for (auto leaf : true_next_->getLeaves()) { leaves.insert(leaf); }

    for (auto leaf : false_next_->getLeaves()) { leaves.insert(leaf); }

    return {leaves.begin(), leaves.end()};
}

std::vector<lang::BasicBlock*> lang::BasicBlock::Definition::Branching::getSuccessors()
{
    std::vector<lang::BasicBlock*> successors;

    successors.push_back(true_next_);
    successors.push_back(false_next_);

    return successors;
}

lang::Location lang::BasicBlock::Definition::Branching::getStartLocation() const
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.back()->location();
}

lang::Location lang::BasicBlock::Definition::Branching::getEndLocation() const
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.back()->location();
}

void lang::BasicBlock::Definition::Branching::reach() const
{
    true_next_->reach();
    false_next_->reach();
}

void lang::BasicBlock::Definition::Branching::prepareBuild(CompileContext& context, llvm::Function* native_function)
{
    std::string name = "b" + std::to_string(index_);
    native_block_    = llvm::BasicBlock::Create(*context.llvmContext(), name, native_function);

    true_next_->prepareBuild(context, native_function);
    false_next_->prepareBuild(context, native_function);
}

void lang::BasicBlock::Definition::Branching::doBuild(CompileContext& context)
{
    context.ir()->SetInsertPoint(native_block_);

    for (auto& statement : statements_) { statement->build(context); }

    Shared<lang::Value> truth         = condition_->getValue();
    Shared<lang::Value> boolean_truth = lang::Type::makeMatching(lang::BooleanType::get(), truth, context);

    boolean_truth->buildContentValue(context);

    context.ir()->CreateCondBr(truth->getContentValue(),
                               true_next_->definition_->getNativeBlock(),
                               false_next_->definition_->getNativeBlock());

    true_next_->doBuild(context);
    false_next_->doBuild(context);
}

std::string lang::BasicBlock::Definition::Branching::getExitRepresentation()
{
    return "// branch";
}
