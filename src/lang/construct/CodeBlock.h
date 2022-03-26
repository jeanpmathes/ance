#ifndef ANCE_SRC_LANG_CONSTRUCT_CODEBLOCK_H_
#define ANCE_SRC_LANG_CONSTRUCT_CODEBLOCK_H_

#include <variant>

#include "lang/construct/BasicBlock.h"
#include "lang/scope/LocalScope.h"
#include "lang/scope/Scope.h"
#include "lang/statement/Statement.h"
#include "lang/Element.h"

namespace lang
{
    /**
     * A code block is a sequence of statements.
     * In contrast to basic blocks, code blocks can be nested and contain branching statements.
     */
    class CodeBlock : public lang::Element<CodeBlock, ANCE_CONSTRUCTS>
    {
      private:
        explicit CodeBlock(bool scoped);

      public:
        /**
         * Make an initial block. This block is scoped.
         * @return The initial block.
         */
        static std::unique_ptr<CodeBlock> makeInitial();

        /**
         * Make a block wrapping a statement. The block is not scoped.
         * @param statement The statement to wrap.
         * @return The block.
         */
        static CodeBlock* wrapStatement(std::unique_ptr<Statement> statement);

        /**
         * Make a scoped block.
         * @return The block.
         */
        static CodeBlock* makeScoped();

        /**
         * Append a block to this block.
         * @param block The block to append.
         */
        void append(std::unique_ptr<CodeBlock> block);

        /**
         * Create the scopes for this block and all sub-blocks.
         * @param parent The parent scope.
         * @return The created scope, or nullptr if the block is not scoped.
         */
        lang::LocalScope* createScopes(lang::Scope* parent);

        /**
         * Walk all definitions and declarations in this block.
         * This will not do any resolving, but will consider blockers.
         */
        void walkDefinitions();

        /**
         * Create basic blocks from the statements in this block.
         * @param entry The entry basic block.
         * @param function The function this block belongs to.
         * @return The created basic blocks.
         */
        std::vector<std::unique_ptr<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry,
                                                                         lang::Function*   function);

      private:
        bool                                                                              scoped_;
        std::vector<std::variant<std::unique_ptr<Statement>, std::unique_ptr<CodeBlock>>> subs_ {};
        std::unique_ptr<lang::LocalScope>                                                 scope_ {};
    };

}

#endif
