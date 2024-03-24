#include "BasicBlock.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/CodeBlock.h"

Owned<lang::BasicBlock> lang::BasicBlock::createEmpty()
{
    return makeOwned<BasicBlock>(makeOwned<lang::bb::def::Empty>());
}

Owned<lang::BasicBlock> lang::BasicBlock::createFinalizing(lang::Scope& scope, std::string info)
{
    return makeOwned<BasicBlock>(makeOwned<lang::bb::def::Finalizing>(scope, std::move(info)));
}

Owned<lang::BasicBlock> lang::BasicBlock::createSimple(Statement* statement)
{
    if (statement == nullptr) { return makeOwned<BasicBlock>(makeOwned<lang::bb::def::Simple>()); }
    else { return makeOwned<BasicBlock>(makeOwned<lang::bb::def::Simple>(*statement)); }
}

Owned<lang::BasicBlock> lang::BasicBlock::createReturning(lang::Scope& scope,
                                                          Expression&  expression,
                                                          Function&    function)
{

    auto block = makeOwned<BasicBlock>(makeOwned<lang::bb::def::Returning>(scope, expression));

    block->setContainingFunction(function);

    return block;
}

std::vector<Owned<lang::BasicBlock>> lang::BasicBlock::createBranching(Expression& condition,
                                                                       Statement&  true_block,
                                                                       Statement*  false_block,
                                                                       Function&   function)
{
    std::vector<Owned<BasicBlock>> blocks;

    blocks.push_back(makeOwned<BasicBlock>(makeOwned<lang::bb::def::Branching>(condition)));
    auto& branch = *blocks.back();

    Owned<lang::BasicBlock> end_block = lang::BasicBlock::createSimple();

    auto append_code_block = [&](Statement* code_block) {
        auto new_basic_blocks = code_block->createBasicBlocks(branch, function);
        assert(!new_basic_blocks.empty());

        blocks.insert(blocks.end(),
                      std::make_move_iterator(new_basic_blocks.begin()),
                      std::make_move_iterator(new_basic_blocks.end()));

        blocks.back()->link(*end_block);
    };

    append_code_block(&true_block);

    if (false_block) append_code_block(false_block);
    else branch.link(*end_block);

    blocks.push_back(std::move(end_block));

    for (auto& new_block : blocks) new_block->setContainingFunction(function);

    return blocks;
}

std::vector<Owned<lang::BasicBlock>> lang::BasicBlock::createLooping(
    Statement&                                       code_block,
    std::pair<lang::BasicBlock*, lang::BasicBlock*>* loop_parts,
    Function&                                        function)
{
    std::vector<Owned<BasicBlock>> blocks;

    blocks.push_back(lang::BasicBlock::createSimple());
    auto& first_block = *blocks.back();

    Owned<lang::BasicBlock> end_block = lang::BasicBlock::createSimple();

    *loop_parts = std::make_pair(&first_block, end_block.get());

    auto append_code_block = [&](Statement* new_block, lang::BasicBlock& next) {
        auto new_basic_blocks = new_block->createBasicBlocks(first_block, function);
        assert(!new_basic_blocks.empty());

        blocks.insert(blocks.end(),
                      std::make_move_iterator(new_basic_blocks.begin()),
                      std::make_move_iterator(new_basic_blocks.end()));

        blocks.back()->link(next);
    };

    append_code_block(&code_block, first_block);
    blocks.push_back(std::move(end_block));

    for (auto& new_block : blocks) new_block->setContainingFunction(function);

    return blocks;
}

std::vector<Owned<lang::BasicBlock>> lang::BasicBlock::createJump(lang::BasicBlock&                from,
                                                                  lang::BasicBlock&                to,
                                                                  std::vector<lang::Scope*> const& scopes)
{
    std::vector<Owned<BasicBlock>> blocks;
    lang::BasicBlock*              current_block = &from;

    for (auto scope : scopes)
    {
        blocks.push_back(createFinalizing(*scope, "jump"));

        current_block->link(*blocks.back());
        current_block = blocks.back().get();
    }

    current_block->link(to);

    // Blocks after the jump might be unreachable, but still need a block to link to.
    blocks.push_back(createSimple());

    return blocks;
}

std::vector<Owned<lang::BasicBlock>> lang::BasicBlock::createMatching(
    Match&                                                        match,
    std::vector<std::pair<LiteralExpression*, Statement*>> const& cases,
    Function&                                                     function)
{
    std::map<Statement*, std::vector<LiteralExpression*>> code_to_case;

    for (auto& [case_value, code_block] : cases)
    {
        if (!code_to_case.contains(code_block)) { code_to_case[code_block] = {}; }

        // Filter out default case, represented by null.
        if (case_value) code_to_case[code_block].push_back(case_value);
    }

    std::vector<std::vector<LiteralExpression*>> case_values;

    case_values.reserve(code_to_case.size());
    for (auto& [code_block, targeting_values] : code_to_case) { case_values.push_back(targeting_values); }

    std::vector<Owned<BasicBlock>> blocks;

    blocks.push_back(makeOwned<BasicBlock>(makeOwned<lang::bb::def::Matching>(match, case_values)));
    auto& branch = *blocks.back();

    Owned<lang::BasicBlock> end_block = lang::BasicBlock::createSimple();

    for (auto& [code_block, targeting_values] : code_to_case)
    {
        auto new_basic_blocks = code_block->createBasicBlocks(branch, function);
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

lang::Function const* lang::BasicBlock::getContainingFunction() const
{
    return containing_function_;
}

void lang::BasicBlock::complete(size_t& index)
{
    if (finalized_) return;
    finalized_ = true;

    definition_->index(index);
    definition_->complete(index);
}

bool lang::BasicBlock::isUsable() const
{
    return !unused_;
}

size_t lang::BasicBlock::getId() const
{
    return definition_->index();
}

std::list<lang::BasicBlock const*> lang::BasicBlock::getLeaves() const
{
    assert(finalized_);
    assert(simplified_);

    if (!leaves_.hasValue())
    {
        leaves_ = makeOptional<std::list<lang::BasicBlock const*>>(
            std::list<lang::BasicBlock const*>());// Prevent infinite recursion, as getLeaves() calls this function.
        leaves_ = definition_->getLeaves();
    }

    return leaves_.value();
}

std::vector<lang::BasicBlock const*> lang::BasicBlock::getSuccessors() const
{
    assert(finalized_);
    assert(simplified_);

    return definition_->getSuccessors();
}

Optional<std::pair<std::reference_wrapper<lang::Type const>, lang::Location>> lang::BasicBlock::getReturnType() const
{
    assert(finalized_);
    return definition_->getReturnType();
}

lang::Location lang::BasicBlock::getStartLocation() const
{
    assert(finalized_);
    return definition_->getStartLocation();
}

lang::Location lang::BasicBlock::getEndLocation() const
{
    assert(finalized_);
    return definition_->getEndLocation();
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

void lang::BasicBlock::reach() const
{
    if (reached_) return;
    reached_ = true;

    definition_->reach();
}

bool lang::BasicBlock::isUnreached() const
{
    return !reached_ && !unused_ && !isMeta();
}

std::string lang::BasicBlock::getExitRepresentation() const
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

lang::BasicBlock const* lang::BasicBlock::Definition::Base::self() const
{
    return self_;
}

bool lang::BasicBlock::Definition::Base::isMeta() const
{
    return false;
}

void lang::BasicBlock::Definition::Base::index(size_t& index)
{
    index_ = index;
    index++;
}

size_t lang::BasicBlock::Definition::Base::index() const
{
    return index_;
}

bool lang::BasicBlock::isMeta() const
{
    return definition_->isMeta();
}

std::vector<std::reference_wrapper<Statement>> const& lang::BasicBlock::statements() const
{
    return statements_;
}

void lang::BasicBlock::addStatement(Statement& statement)
{
    statements_.emplace_back(statement);
    addChild(statement);
}

lang::BasicBlock::BasicBlock(Owned<Definition::Base> definition) : definition_(std::move(definition))
{
    definition_->setSelf(this);
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

Optional<std::pair<std::reference_wrapper<lang::Type const>, lang::Location>> lang::BasicBlock::Definition::Base::
    getReturnType() const
{
    return std::nullopt;
}

lang::BasicBlock::Definition::Base& lang::BasicBlock::definition()
{
    return *definition_;
}

lang::BasicBlock::Definition::Base const& lang::BasicBlock::definition() const
{
    return *definition_;
}

void lang::BasicBlock::markAsUnused()
{
    unused_ = true;
}

bool lang::BasicBlock::isUnused() const
{
    return unused_;
}
