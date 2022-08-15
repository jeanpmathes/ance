#include "BasicBlock.h"

#include "compiler/CompileContext.h"
#include "lang/construct/constant/Constant.h"
#include "lang/construct/value/Value.h"
#include "lang/statement/Match.h"
#include "validation/ValidationLogger.h"

lang::BasicBlock::Definition::Matching::Matching(Match* match, std::vector<std::vector<ConstantExpression*>> cases)
    : match_(match)
    , cases_(std::move(cases))
{}

void lang::BasicBlock::Definition::Matching::complete(size_t& index)
{
    for (auto& statement : statements_) { self()->addChild(*statement); }
    for (auto& branch : branches_) { branch->complete(index); }
}

void lang::BasicBlock::Definition::Matching::setLink(lang::BasicBlock& next)
{
    branches_.push_back(&next);
    next.registerIncomingLink(*self());
}

void lang::BasicBlock::Definition::Matching::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    for (auto& branch : branches_)
    {
        if (branch == former)
        {
            branch = updated;
            updated->registerIncomingLink(*self());

            return;
        }
    }
}

void lang::BasicBlock::Definition::Matching::simplify()
{
    for (auto& branch : branches_) { branch->simplify(); }
}

void lang::BasicBlock::Definition::Matching::transferStatements(std::list<Statement*>& statements)
{
    statements_.splice(statements_.begin(), statements);
}

std::list<lang::BasicBlock*> lang::BasicBlock::Definition::Matching::getLeaves()
{
    std::list<lang::BasicBlock*> leaves;

    for (auto& branch : branches_)
    {
        for (auto& leaf : branch->getLeaves()) { leaves.push_back(leaf); }
    }

    return leaves;
}
std::vector<lang::BasicBlock*> lang::BasicBlock::Definition::Matching::getSuccessors()
{
    return branches_;
}

lang::Location lang::BasicBlock::Definition::Matching::getStartLocation()
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.back()->location();
}

lang::Location lang::BasicBlock::Definition::Matching::getEndLocation()
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.back()->location();
}

void lang::BasicBlock::Definition::Matching::reach()
{
    for (auto& branch : branches_) { branch->reach(); }
}

void lang::BasicBlock::Definition::Matching::prepareBuild(CompileContext* context, llvm::Function* native_function)
{
    std::string name = "b" + std::to_string(index_);
    native_block_    = llvm::BasicBlock::Create(*context->llvmContext(), name, native_function);

    for (auto& branch : branches_) { branch->prepareBuild(context, native_function); }
}

void lang::BasicBlock::Definition::Matching::doBuild(CompileContext* context)
{
    context->ir()->SetInsertPoint(native_block_);

    for (auto& statement : statements_) { statement->build(context); }

    std::shared_ptr<lang::Value> value = match_->expression().getValue();
    value->buildContentValue(context);

    llvm::BasicBlock* default_block = nullptr;

    for (const auto& [case_value, branch_block] : llvm::zip(cases_, branches_))
    {
        if (case_value.empty())
        {
            default_block = branch_block->definition_->getNativeBlock();
            break;
        }
    }

    if (!default_block) { default_block = branches_.front()->definition_->getNativeBlock(); }

    auto switch_instance = context->ir()->CreateSwitch(value->getContentValue(), default_block, cases_.size());

    for (const auto& [case_value, branch_block] : llvm::zip(cases_, branches_))
    {
        llvm::BasicBlock* branch_native_block = branch_block->definition_->getNativeBlock();

        if (case_value.empty() || branch_native_block == default_block) continue;

        for (auto& case_value_expression : case_value)
        {
            std::shared_ptr<lang::Constant> constant = case_value_expression->getConstantValue();
            constant->buildContentConstant(context->module());
            llvm::Constant* native_constant = constant->getContentConstant();

            auto native_integer_constant = llvm::cast<llvm::ConstantInt>(native_constant);
            switch_instance->addCase(native_integer_constant, branch_native_block);
        }
    }

    for (auto& branch : branches_) { branch->doBuild(context); }
}

std::string lang::BasicBlock::Definition::Matching::getExitRepresentation()
{
    return "// match";
}
