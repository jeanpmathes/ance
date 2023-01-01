#include <utility>

#include "BasicBlock.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"

lang::BasicBlock::Definition::Returning::Returning(lang::LocalScope& scope,
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

std::list<lang::BasicBlock const*> lang::BasicBlock::Definition::Returning::getLeaves() const
{
    std::list<lang::BasicBlock const*> leaves;

    leaves.push_back(self());

    return leaves;
}

std::vector<lang::BasicBlock*> lang::BasicBlock::Definition::Returning::getSuccessors()
{
    return {};
}

Optional<std::pair<Optional<std::reference_wrapper<lang::Value const>>, lang::Location>> lang::BasicBlock::Definition::
    Returning::getReturnValue() const
{
    lang::Location const location = return_value_ ? return_value_->location() : return_location_;
    Optional<std::reference_wrapper<lang::Value const>> value =
        return_value_ ? makeOptional(std::cref(const_cast<Expression const*>(return_value_)->getValue()))
                      : std::nullopt;

    return std::make_pair(value, location);
}

lang::Location lang::BasicBlock::Definition::Returning::getStartLocation() const
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.back()->location();
}

lang::Location lang::BasicBlock::Definition::Returning::getEndLocation() const
{
    if (statements_.empty()) { return lang::Location::global(); }

    return statements_.back()->location();
}

void lang::BasicBlock::Definition::Returning::reach() const {}

void lang::BasicBlock::Definition::Returning::prepareBuild(CompileContext& context, llvm::Function* native_function)
{
    std::string const name = "b" + std::to_string(index_);
    native_block_          = llvm::BasicBlock::Create(context.llvmContext(), name, native_function);
}

void lang::BasicBlock::Definition::Returning::doBuild(CompileContext& context)
{
    context.ir().SetInsertPoint(native_block_);

    for (auto& statement : statements_) { statement->build(context); }

    if (return_value_) {}

    scope_.buildReturnFinalization(context);

    if (return_value_)
    {
        Shared<lang::Value> return_value = return_value_->getValue();

        return_value = lang::Type::makeMatching(self()->containing_function_->returnType(), return_value, context);
        return_value->buildContentValue(context);

        context.ir().CreateRet(return_value->getContentValue());
    }
    else { context.ir().CreateRetVoid(); }
}

std::string lang::BasicBlock::Definition::Returning::getExitRepresentation()
{
    return "// return";
}
