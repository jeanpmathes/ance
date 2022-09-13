#include <utility>

#include "BasicBlock.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"

lang::BasicBlock::Definition::Returning::Returning(lang::LocalScope* scope,
                                                   Expression*       return_value,
                                                   lang::Location    return_location)
    : return_value_(return_value)
    , scope_(scope)
    , return_location_(return_location)
{}

void lang::BasicBlock::Definition::Returning::complete(size_t& index)
{
    for (auto& statement : statements_) { self()->addStatement(*statement); }

    if (unreachable_next_) unreachable_next_->complete(index);
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

std::list<lang::BasicBlock*> lang::BasicBlock::Definition::Returning::getLeaves()
{
    std::list<lang::BasicBlock*> leaves;

    leaves.push_back(self());

    return leaves;
}

std::vector<lang::BasicBlock*> lang::BasicBlock::Definition::Returning::getSuccessors()
{
    return {};
}

std::optional<std::pair<std::shared_ptr<lang::Value>, lang::Location>> lang::BasicBlock::Definition::Returning::
    getReturnValue()
{
    lang::Location               location = return_value_ ? return_value_->location() : return_location_;
    std::shared_ptr<lang::Value> value    = return_value_ ? return_value_->getValue() : nullptr;

    return std::make_pair(value, location);
}

lang::Location lang::BasicBlock::Definition::Returning::getStartLocation()
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.back()->location();
}

lang::Location lang::BasicBlock::Definition::Returning::getEndLocation()
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.back()->location();
}

void lang::BasicBlock::Definition::Returning::reach() {}

void lang::BasicBlock::Definition::Returning::prepareBuild(CompileContext& context, llvm::Function* native_function)
{
    std::string name = "b" + std::to_string(index_);
    native_block_    = llvm::BasicBlock::Create(*context.llvmContext(), name, native_function);
}

void lang::BasicBlock::Definition::Returning::doBuild(CompileContext& context)
{
    context.ir()->SetInsertPoint(native_block_);

    for (auto& statement : statements_) { statement->build(context); }

    std::shared_ptr<lang::Value> return_value;

    if (return_value_)
    {
        return_value = return_value_->getValue();
        return_value = lang::Type::makeMatching(self()->containing_function_->returnType(), return_value, context);

        return_value->buildContentValue(context);
    }

    scope_->buildReturnFinalization(context);

    if (return_value_) { context.ir()->CreateRet(return_value->getContentValue()); }
    else { context.ir()->CreateRetVoid(); }
}

std::string lang::BasicBlock::Definition::Returning::getExitRepresentation()
{
    return "// return";
}

