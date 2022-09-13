#include "BasicBlock.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/CodeBlock.h"

std::unique_ptr<lang::BasicBlock> lang::BasicBlock::createEmpty()
{
    auto block = new BasicBlock();

    block->definition_ = std::make_unique<Definition::Empty>();
    block->definition_->setSelf(block);

    return std::unique_ptr<BasicBlock>(block);
}

std::unique_ptr<lang::BasicBlock> lang::BasicBlock::createFinalizing(lang::Scope* scope)
{
    auto block = new BasicBlock();

    block->definition_ = std::make_unique<Definition::Finalizing>(scope);
    block->definition_->setSelf(block);

    return std::unique_ptr<BasicBlock>(block);
}

std::unique_ptr<lang::BasicBlock> lang::BasicBlock::createSimple(Statement* statement)
{
    auto block = new BasicBlock();

    block->definition_ =
        statement ? std::make_unique<Definition::Simple>(statement) : std::make_unique<Definition::Simple>();
    block->definition_->setSelf(block);

    return std::unique_ptr<BasicBlock>(block);
}

std::unique_ptr<lang::BasicBlock> lang::BasicBlock::createReturning(lang::LocalScope* scope,
                                                                    Expression*       expression,
                                                                    lang::Location    return_location,
                                                                    Function&         function)
{
    auto block = new BasicBlock();

    block->definition_ = std::make_unique<Definition::Returning>(scope, expression, return_location);
    block->definition_->setSelf(block);

    block->setContainingFunction(function);

    return std::unique_ptr<BasicBlock>(block);
}

std::vector<std::unique_ptr<lang::BasicBlock>> lang::BasicBlock::createBranching(Expression* condition,
                                                                                 Statement*  true_block,
                                                                                 Statement*  false_block,
                                                                                 Function&   function)
{
    std::vector<std::unique_ptr<BasicBlock>> blocks;

    auto block = new BasicBlock();
    blocks.push_back(std::unique_ptr<BasicBlock>(block));

    block->definition_ = std::make_unique<Definition::Branching>(condition);
    block->definition_->setSelf(block);

    std::unique_ptr<lang::BasicBlock> end_block = lang::BasicBlock::createSimple();

    auto append_code_block = [&](Statement* code_block) {
        auto new_basic_blocks = code_block->createBasicBlocks(*block, function);
        assert(!new_basic_blocks.empty());

        blocks.insert(blocks.end(),
                      std::make_move_iterator(new_basic_blocks.begin()),
                      std::make_move_iterator(new_basic_blocks.end()));

        blocks.back()->link(*end_block);
    };

    append_code_block(true_block);

    if (false_block) append_code_block(false_block);
    else block->link(*end_block);

    blocks.push_back(std::move(end_block));

    for (auto& new_block : blocks) new_block->setContainingFunction(function);

    return blocks;
}

std::vector<std::unique_ptr<lang::BasicBlock>> lang::BasicBlock::createLooping(Expression* condition,
                                                                               Statement*  code_block,
                                                                               Function&   function)
{
    std::vector<std::unique_ptr<BasicBlock>> blocks;

    auto block = new BasicBlock();
    blocks.push_back(std::unique_ptr<BasicBlock>(block));

    block->definition_ = std::make_unique<Definition::Branching>(condition);
    block->definition_->setSelf(block);

    std::unique_ptr<lang::BasicBlock> end_block = lang::BasicBlock::createSimple();

    auto append_code_block = [&](Statement* new_block, lang::BasicBlock& next) {
        auto new_basic_blocks = new_block->createBasicBlocks(*block, function);
        assert(!new_basic_blocks.empty());

        blocks.insert(blocks.end(),
                      std::make_move_iterator(new_basic_blocks.begin()),
                      std::make_move_iterator(new_basic_blocks.end()));

        blocks.back()->link(next);
    };

    append_code_block(code_block, *block);
    block->link(*end_block);

    blocks.push_back(std::move(end_block));

    for (auto& new_block : blocks) new_block->setContainingFunction(function);

    return blocks;
}

std::vector<std::unique_ptr<lang::BasicBlock>> lang::BasicBlock::createMatching(
    Match*                                                  match,
    std::vector<std::pair<ConstantExpression*, Statement*>> cases,
    Function&                                               function)
{
    std::map<Statement*, std::vector<ConstantExpression*>> code_to_case;

    for (auto& [case_value, code_block] : cases)
    {
        if (!code_to_case.contains(code_block)) { code_to_case[code_block] = {}; }

        // Filter out default case, represented by null.
        if (case_value) code_to_case[code_block].push_back(case_value);
    }

    std::vector<std::vector<ConstantExpression*>> case_values;

    case_values.reserve(code_to_case.size());
    for (auto& [code_block, targeting_values] : code_to_case) { case_values.push_back(targeting_values); }

    std::vector<std::unique_ptr<BasicBlock>> blocks;

    auto block = new BasicBlock();
    blocks.push_back(std::unique_ptr<BasicBlock>(block));

    block->definition_ = std::make_unique<Definition::Matching>(match, case_values);
    block->definition_->setSelf(block);

    std::unique_ptr<lang::BasicBlock> end_block = lang::BasicBlock::createSimple();

    for (auto& [code_block, targeting_values] : code_to_case)
    {
        auto new_basic_blocks = code_block->createBasicBlocks(*block, function);
        assert(!new_basic_blocks.empty());

        blocks.insert(blocks.end(),
                      std::make_move_iterator(new_basic_blocks.begin()),
                      std::make_move_iterator(new_basic_blocks.end()));

        blocks.back()->link(*end_block);
    }

    blocks.push_back(std::move(end_block));

    for (auto& new_block : blocks) new_block->setContainingFunction(function);

    return blocks;
}

void lang::BasicBlock::link(lang::BasicBlock& next)
{
    assert(!finalized_);
    definition_->setLink(next);
}

void lang::BasicBlock::simplify()
{
    assert(!finalized_);

    if (simplified_) return;
    simplified_ = true;

    definition_->simplify();
}

void lang::BasicBlock::setContainingFunction(Function& function)
{
    assert(!finalized_);

    containing_function_ = &function;
}

void lang::BasicBlock::complete(size_t& index)
{
    if (finalized_) return;
    finalized_ = true;

    definition_->setIndex(index);
    definition_->complete(index);
}

bool lang::BasicBlock::isUsable() const
{
    return !unused_;
}

size_t lang::BasicBlock::getId() const
{
    return definition_->getIndex();
}

std::list<lang::BasicBlock*> lang::BasicBlock::getLeaves()
{
    assert(finalized_);
    assert(simplified_);

    if (!leaves_.has_value())
    {
        leaves_ = std::make_optional(std::list<lang::BasicBlock*>());// Prevent infinite recursion.
        leaves_ = definition_->getLeaves();
    }

    return leaves_.value();
}

std::vector<lang::BasicBlock*> lang::BasicBlock::getSuccessors()
{
    assert(finalized_);
    assert(simplified_);

    return definition_->getSuccessors();
}

std::optional<std::pair<std::shared_ptr<lang::Value>, lang::Location>> lang::BasicBlock::getReturnValue()
{
    assert(finalized_);
    return definition_->getReturnValue();
}

lang::Location lang::BasicBlock::getStartLocation()
{
    assert(finalized_);
    return definition_->getStartLocation();
}

lang::Location lang::BasicBlock::getEndLocation()
{
    assert(finalized_);
    return definition_->getEndLocation();
}

void lang::BasicBlock::prepareBuild(CompileContext& context, llvm::Function* native_function)
{
    if (build_prepared_) return;
    build_prepared_ = true;

    assert(finalized_);
    definition_->prepareBuild(context, native_function);
}

void lang::BasicBlock::doBuild(CompileContext& context)
{
    if (build_done_) return;
    build_done_ = true;

    assert(finalized_);
    definition_->doBuild(context);
}

void lang::BasicBlock::registerIncomingLink(lang::BasicBlock& predecessor)
{
    definition_->registerIncomingLink(predecessor);
}

void lang::BasicBlock::updateLink(lang::BasicBlock* former, lang::BasicBlock* updated)
{
    definition_->updateLink(former, updated);
}

size_t lang::BasicBlock::getIncomingLinkCount() const
{
    return definition_->getIncomingLinkCount();
}

void lang::BasicBlock::transferStatements(std::list<Statement*>& statements)
{
    if (statements.empty()) return;
    definition_->transferStatements(statements);
}

void lang::BasicBlock::reach()
{
    if (reached_) return;
    reached_ = true;

    definition_->reach();
}

bool lang::BasicBlock::isUnreached() const
{
    return !reached_ && !unused_ && !isMeta();
}

std::string lang::BasicBlock::getExitRepresentation()
{
    return definition_->getExitRepresentation();
}

void lang::BasicBlock::Definition::Base::setSelf(lang::BasicBlock* self)
{
    self_ = self;
}

lang::BasicBlock* lang::BasicBlock::Definition::Base::self()
{
    return self_;
}

bool lang::BasicBlock::Definition::Base::isMeta() const
{
    return false;
}

void lang::BasicBlock::Definition::Base::setIndex(size_t& index)
{
    index_ = index;
    index++;
}

size_t lang::BasicBlock::Definition::Base::getIndex() const
{
    return index_;
}

bool lang::BasicBlock::isMeta() const
{
    return definition_->isMeta();
}

const std::vector<std::reference_wrapper<Statement>>& lang::BasicBlock::statements() const
{
    return statements_;
}

void lang::BasicBlock::addStatement(Statement& statement)
{
    statements_.emplace_back(statement);
    addChild(statement);
}

void lang::BasicBlock::Definition::Base::registerIncomingLink(lang::BasicBlock& block)
{
    incoming_links_.push_back(&block);
}

size_t lang::BasicBlock::Definition::Base::getIncomingLinkCount() const
{
    return incoming_links_.size();
}

void lang::BasicBlock::Definition::Base::updateIncomingLinks(lang::BasicBlock* updated)
{
    for (auto& link : incoming_links_) { link->updateLink(self(), updated); }

    incoming_links_.clear();
}

std::optional<std::pair<std::shared_ptr<lang::Value>, lang::Location>> lang::BasicBlock::Definition::Base::
    getReturnValue()
{
    return std::nullopt;
}

llvm::BasicBlock* lang::BasicBlock::Definition::Base::getNativeBlock()
{
    return native_block_;
}

