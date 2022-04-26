#include "CodeBlock.h"

#include "lang/scope/LocalScope.h"

lang::CodeBlock::CodeBlock(bool scoped, lang::Location location) : Statement(location), scoped_(scoped) {}

std::unique_ptr<lang::CodeBlock> lang::CodeBlock::makeInitial(lang::Location location)
{
    return std::unique_ptr<lang::CodeBlock>(new CodeBlock(true, location));
}

lang::CodeBlock* lang::CodeBlock::wrapStatement(std::unique_ptr<Statement> statement)
{
    auto* block = new CodeBlock(false, statement->location());

    block->addSubstatement(*statement);

    block->subs_.emplace_back(std::move(statement));

    return block;
}

lang::CodeBlock* lang::CodeBlock::makeScoped(lang::Location location)
{
    return new CodeBlock(true, location);
}

void lang::CodeBlock::append(std::unique_ptr<CodeBlock> block)
{
    if (block->scoped_)
    {
        lang::CodeBlock* last_ptr = block.get();
        subs_.emplace_back(std::move(block));

        addSubstatement(*last_ptr);
    }
    else {
        for (auto& sub : block->subs_)
        {
            addSubstatement(*sub);

            subs_.push_back(std::move(sub));
        }

        block->subs_.clear();
    }
}

void lang::CodeBlock::setScope(lang::Scope* scope)
{
    lang::LocalScope* created = nullptr;

    if (scoped_)
    {
        scope_  = scope->makeLocalScope();
        created = scope_.get();
    }

    lang::Scope* local_parent = created ? created : scope;

    for (auto& sub : subs_) { sub->setContainingScope(local_parent); }
}

void lang::CodeBlock::walkDefinitions()
{
    for (auto& sub : subs_)
    { sub->walkDefinitions(); }
}

std::vector<std::unique_ptr<lang::BasicBlock>> lang::CodeBlock::createBasicBlocks(lang::BasicBlock& entry,
                                                                                  lang::Function*   function)
{
    std::vector<std::unique_ptr<lang::BasicBlock>> blocks;

    lang::BasicBlock* previous_block = &entry;

    for (auto& sub : subs_)
    {
        std::vector<std::unique_ptr<BasicBlock>> new_blocks = sub->createBasicBlocks(*previous_block, function);

        blocks.insert(blocks.end(),
                      std::make_move_iterator(new_blocks.begin()),
                      std::make_move_iterator(new_blocks.end()));

        assert(previous_block != blocks.back().get());
        previous_block = blocks.back().get();
    }

    return blocks;
}

lang::LocalScope* lang::CodeBlock::getBlockScope() const
{
    return scope_.get();
}

void lang::CodeBlock::validate(ValidationLogger& validation_logger)
{
    for (auto& sub : subs_) { sub->validate(validation_logger); }
}

Statements lang::CodeBlock::expandWith(Expressions, Statements substatements) const
{
    Statements statements;

    auto* block = new CodeBlock(scoped_, location());
    statements.push_back(std::unique_ptr<Statement>(block));

    for (auto& sub : substatements)
    {
        block->addSubstatement(*sub);

        block->subs_.push_back(std::move(sub));
    }

    return statements;
}

void lang::CodeBlock::doBuild(CompileContext*)
{
    assert(false && "Build step must use code-block free hierarchy.");// Building uses BBs.
}
