#include "CodeBlock.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/LocalScope.h"

lang::CodeBlock::CodeBlock(bool scoped, lang::Location location) : Statement(location), scoped_(scoped) {}

Owned<lang::CodeBlock> lang::CodeBlock::makeInitial(lang::Location location)
{
    return Owned<lang::CodeBlock>(*(new CodeBlock(true, location)));
}

Owned<lang::CodeBlock> lang::CodeBlock::makeWithStatement(Owned<Statement> statement)
{
    auto block = Owned<lang::CodeBlock>(*(new CodeBlock(false, statement->location())));

    block->addSubstatement(*statement);
    block->subs_.emplace_back(std::move(statement));

    return block;
}

Owned<lang::CodeBlock> lang::CodeBlock::wrapStatements(std::vector<Owned<Statement>> statements)
{
    lang::Location location = Location::global();

    for (auto& statement : statements) { location.extend(statement->location()); }

    auto block = Owned<lang::CodeBlock>(*(new CodeBlock(false, location)));

    for (auto& statement : statements)
    {
        block->addSubstatement(*statement);
        block->subs_.emplace_back(std::move(statement));
    }

    return block;
}

Owned<lang::CodeBlock> lang::CodeBlock::makeScoped(lang::Location location)
{
    return Owned<lang::CodeBlock>(*(new CodeBlock(true, location)));
}

std::vector<std::reference_wrapper<Statement const>> lang::CodeBlock::statements() const
{
    std::vector<std::reference_wrapper<Statement const>> s;
    s.reserve(subs_.size());

    for (auto const& statement : subs_) { s.emplace_back(*statement); }

    return s;
}

void lang::CodeBlock::append(Owned<CodeBlock> block)
{
    if (block->scoped_)
    {
        lang::CodeBlock* last_ptr = block.get();
        subs_.emplace_back(std::move(block));

        addSubstatement(*last_ptr);
    }
    else
    {
        for (auto& sub : block->subs_)
        {
            addSubstatement(*sub);
            subs_.push_back(std::move(sub));
        }

        block->subs_.clear();
    }
}

void lang::CodeBlock::setScope(Scope& scope)
{
    lang::Scope* created = nullptr;

    if (scoped_)
    {
        scope_  = scope.makeLocalScope(*this);
        created = scope_.value().get();
    }

    lang::Scope* local_parent = created ? created : &scope;

    for (auto& sub : subs_) { sub->setContainingScope(*local_parent); }
}

void lang::CodeBlock::walkDefinitions()
{
    for (auto& sub : subs_) { sub->walkDefinitions(); }
}

void lang::CodeBlock::postResolve()
{
    Statement::postResolve();

    if (scoped_) scope_.value()->postResolve();
}

std::vector<Owned<lang::BasicBlock>> lang::CodeBlock::createBasicBlocks(lang::BasicBlock& entry, Function& function)
{
    std::vector<Owned<lang::BasicBlock>> blocks;

    lang::BasicBlock* previous_block = &entry;

    auto append_blocks = [&](std::vector<Owned<BasicBlock>>&& new_blocks) {
        blocks.insert(blocks.end(),
                      std::make_move_iterator(new_blocks.begin()),
                      std::make_move_iterator(new_blocks.end()));

        assert(previous_block != blocks.back().get());
        previous_block = blocks.back().get();
    };

    for (auto& sub : subs_)
    {
        std::vector<Owned<BasicBlock>> new_blocks = sub->createBasicBlocks(*previous_block, function);
        append_blocks(std::move(new_blocks));
    }

    if (scoped_)
    {
        blocks.push_back(lang::BasicBlock::createFinalizing(**scope_, "block"));
        previous_block->link(*blocks.back());
    }

    return blocks;
}

lang::OrderedScope* lang::CodeBlock::getBlockScope()
{
    return getPtr(scope_);
}

lang::OrderedScope const* lang::CodeBlock::getBlockScope() const
{
    return getPtr(scope_);
}

bool lang::CodeBlock::isCompound() const
{
    // Compound blocks must be scoped, and unscoped blocks should have exactly one statement.
    assert(scoped_ || subs_.size() == 1);
    return scoped_;
}

bool lang::CodeBlock::validate(ValidationLogger& validation_logger) const
{
    bool valid = true;

    for (auto& sub : subs_) { valid &= sub->validate(validation_logger); }

    return valid;
}

Statements lang::CodeBlock::expandWith(Expressions, Statements substatements, lang::Context&) const
{
    Statements statements;

    auto& block = *(new CodeBlock(scoped_, location()));
    statements.emplace_back(block);

    for (auto& sub : substatements)
    {
        block.addSubstatement(*sub);
        block.subs_.push_back(std::move(sub));
    }

    return statements;
}
