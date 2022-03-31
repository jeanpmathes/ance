#include "BasicBlock.h"

#include <set>

#include "compiler/CompileContext.h"
#include "lang/construct/value/Value.h"
#include "lang/expression/Expression.h"
#include "lang/type/IntegerType.h"

lang::BasicBlock::Definition::Branching::Branching(Expression* condition) : condition_(condition) {}

void lang::BasicBlock::Definition::Branching::finalize(size_t& index)
{
    for (auto& statement : statements_) { self()->addChild(*statement); }

    true_next_->finalize(index);
    false_next_->finalize(index);
}

void lang::BasicBlock::Definition::Branching::setLink(lang::BasicBlock& next)
{
    lang::BasicBlock* next_ptr = &next;

    assert(next_ptr->definition_.get() != this);
    assert(!true_next_ || !false_next_);

    if (!true_next_)
    {
        true_next_ = next_ptr;
        next.registerIncomingLink(*self());

        assert(true_next_ != false_next_);

        return;
    }

    if (!false_next_)
    {
        false_next_ = next_ptr;
        next.registerIncomingLink(*self());

        assert(true_next_ != false_next_);

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

        assert(true_next_ != false_next_);
    };

    if (true_next_ == former) { update(true_next_); }
    if (false_next_ == former) { update(false_next_); }
}

void lang::BasicBlock::Definition::Branching::simplify()
{
    true_next_->simplify();
    if (false_next_) false_next_->simplify();
}

void lang::BasicBlock::Definition::Branching::transferStatements(std::list<Statement*>& statements)
{
    statements_.splice(statements_.begin(), statements);
}

bool lang::BasicBlock::Definition::Branching::validate(ValidationLogger& validation_logger)
{
    bool valid = true;

    for (auto& statement : statements_) { statement->validate(validation_logger); }

    valid &= condition_->validate(validation_logger);
    valid &= valid
          && lang::Type::checkMismatch(lang::IntegerType::getBooleanType(),
                                       condition_->type(),
                                       condition_->location(),
                                       validation_logger);

    return valid;
}

std::list<lang::BasicBlock*> lang::BasicBlock::Definition::Branching::getLeaves()
{
    std::set<lang::BasicBlock*> leaves;

    for (auto leave : true_next_->getLeaves()) { leaves.insert(leave); }

    for (auto leave : false_next_->getLeaves()) { leaves.insert(leave); }

    return {leaves.begin(), leaves.end()};
}

std::vector<lang::BasicBlock*> lang::BasicBlock::Definition::Branching::getSuccessors()
{
    std::vector<lang::BasicBlock*> successors;

    successors.push_back(true_next_);
    successors.push_back(false_next_);

    return successors;
}

lang::Location lang::BasicBlock::Definition::Branching::getStartLocation()
{
    if (statements_.empty()) { return {0, 0, 0, 0}; }

    return statements_.back()->location();
}

lang::Location lang::BasicBlock::Definition::Branching::getEndLocation()
{
    if (statements_.empty()) { return {0, 0, 0, 0}; }

    return statements_.back()->location();
}

void lang::BasicBlock::Definition::Branching::reach()
{
    true_next_->reach();
    false_next_->reach();
}

void lang::BasicBlock::Definition::Branching::prepareBuild(CompileContext* context, llvm::Function* native_function)
{
    std::string name = "b" + std::to_string(index_);
    native_block_    = llvm::BasicBlock::Create(*context->llvmContext(), name, native_function);

    true_next_->prepareBuild(context, native_function);
    false_next_->prepareBuild(context, native_function);
}

void lang::BasicBlock::Definition::Branching::doBuild(CompileContext* context)
{
    context->ir()->SetInsertPoint(native_block_);

    for (auto& statement : statements_) { statement->build(context); }

    std::shared_ptr<lang::Value> truth = condition_->getValue();
    std::shared_ptr<lang::Value> boolean_truth =
        lang::Type::makeMatching(lang::IntegerType::getBooleanType(), truth, context);

    boolean_truth->buildContentValue(context);

    context->ir()->CreateCondBr(truth->getContentValue(),
                                true_next_->definition_->getNativeBlock(),
                                false_next_->definition_->getNativeBlock());

    true_next_->doBuild(context);
    false_next_->doBuild(context);
}

std::string lang::BasicBlock::Definition::Branching::getExitRepresentation()
{
    return "// branch";
}
