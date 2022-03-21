#include "CodeBlock.h"

#include "lang/scope/LocalScope.h"

lang::CodeBlock::CodeBlock(bool scoped) : scoped_(scoped) {}

std::unique_ptr<lang::CodeBlock> lang::CodeBlock::makeInitial()
{
    return std::unique_ptr<lang::CodeBlock>(new CodeBlock(true));
}

lang::CodeBlock* lang::CodeBlock::wrapStatement(std::unique_ptr<Statement> statement)
{
    auto* block = new CodeBlock(false);
    block->statements_.emplace_back(std::move(statement));

    return block;
}

lang::CodeBlock* lang::CodeBlock::makeScoped()
{
    return new CodeBlock(true);
}

void lang::CodeBlock::append(std::unique_ptr<CodeBlock> block)
{
    if (block->scoped_) { statements_.emplace_back(std::move(block)); }
    else {
        for (auto& statement : block->statements_) { statements_.push_back(std::move(statement)); }

        block->statements_.clear();
    }
}

lang::LocalScope* lang::CodeBlock::createScopes(lang::Scope* parent)
{
    lang::LocalScope* created = nullptr;

    if (scoped_)
    {
        scope_  = parent->makeLocalScope();
        created = scope_.get();
    }

    for (auto& sub : statements_)
    {
        auto* block = std::get_if<std::unique_ptr<CodeBlock>>(&sub);
        if (block)
        {
            lang::Scope* local_parent = created ? created : parent;
            block->get()->createScopes(local_parent);
        }

        auto* statement = std::get_if<std::unique_ptr<Statement>>(&sub);
        if (statement) { statement->get()->setContainingScope(created ? created : parent); }
    }

    return created;
}

void lang::CodeBlock::walkDefinitions()
{
    for (auto& sub : statements_)
    {
        auto* block = std::get_if<std::unique_ptr<CodeBlock>>(&sub);
        if (block) { block->get()->walkDefinitions(); }

        auto* statement = std::get_if<std::unique_ptr<Statement>>(&sub);
        if (statement) { statement->get()->walkDefinitions(); }
    }
}

std::vector<std::unique_ptr<lang::BasicBlock>> lang::CodeBlock::createBasicBlocks(lang::BasicBlock& entry,
                                                                                  lang::Function*   function)
{
    std::vector<std::unique_ptr<lang::BasicBlock>> blocks;

    lang::BasicBlock* previous_block = &entry;

    for (auto& sub : statements_)
    {
        auto* block = std::get_if<std::unique_ptr<CodeBlock>>(&sub);
        if (block)
        {
            auto sub_blocks = block->get()->createBasicBlocks(*previous_block, function);

            blocks.insert(blocks.end(),
                          std::make_move_iterator(sub_blocks.begin()),
                          std::make_move_iterator(sub_blocks.end()));
        }

        auto* statement = std::get_if<std::unique_ptr<Statement>>(&sub);
        if (statement)
        {
            auto bb = statement->get()->createBlock();
            previous_block->link(*bb);
            bb->setContainingFunction(function);

            blocks.push_back(std::move(bb));
        }

        previous_block = blocks.back().get();
    }

    return blocks;
}
