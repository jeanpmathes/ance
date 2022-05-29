#ifndef ANCE_SRC_LANG_CONSTRUCT_CODEBLOCK_H_
#define ANCE_SRC_LANG_CONSTRUCT_CODEBLOCK_H_

#include "lang/statement/Statement.h"

#include "lang/construct/BasicBlock.h"
#include "lang/scope/LocalScope.h"
#include "lang/scope/Scope.h"
#include "lang/Element.h"

namespace lang
{
    /**
     * A code block is a sequence of statements, a compound statement.
     * In contrast to basic blocks, code blocks can be nested and contain branching statements.
     */
    class CodeBlock
        : public Statement
        , public lang::Element<CodeBlock, ANCE_CONSTRUCTS>
    {
      private:
        CodeBlock(bool scoped, lang::Location location);

      public:
        /**
         * Make an initial block. This block is scoped.
         * @return The initial block.
         */
        static std::unique_ptr<CodeBlock> makeInitial(lang::Location location);

        /**
         * Make a block wrapping a statement. The block is not scoped.
         * @param statement The statement to wrap.
         * @return The block.
         */
        static CodeBlock* wrapStatement(std::unique_ptr<Statement> statement);

        /**
         * Create a code block wrapping multiple statements.
         * @param statements The statements to wrap.
         * @return The block.
         */
        static std::unique_ptr<CodeBlock> wrapStatements(std::vector<std::unique_ptr<Statement>> statements);

        /**
         * Make a scoped block.
         * @return The block.
         */
        static CodeBlock* makeScoped(lang::Location location);

        [[nodiscard]] std::vector<std::reference_wrapper<Statement>> statements() const;

        /**
         * Append a block to this block.
         * @param block The block to append.
         */
        void append(std::unique_ptr<CodeBlock> block);

        void setScope(lang::Scope* scope) override;

        void walkDefinitions() override;

        std::vector<std::unique_ptr<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry,
                                                                         lang::Function*   function) override;

        lang::LocalScope* getBlockScope() const override;

        void validate(ValidationLogger& validation_logger) override;

        Statements expandWith(Expressions subexpressions, Statements substatements) const override;

        void doBuild(CompileContext* context) override;

      private:
        bool                                    scoped_;
        std::vector<std::unique_ptr<Statement>> subs_ {};
        std::unique_ptr<lang::LocalScope>       scope_ {};
    };

}

#endif
