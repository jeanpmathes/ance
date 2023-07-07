#ifndef ANCE_SRC_LANG_CONSTRUCT_CODEBLOCK_H_
#define ANCE_SRC_LANG_CONSTRUCT_CODEBLOCK_H_

#include "lang/statement/Statement.h"

#include "lang/Element.h"
#include "lang/construct/BasicBlock.h"
#include "lang/scope/LocalScope.h"
#include "lang/scope/Scope.h"

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
        static Owned<CodeBlock> makeInitial(lang::Location location);

        /**
         * Make a block wrapping a statement. The block is not scoped.
         * @param statement The statement to wrap.
         * @return The block.
         */
        static Owned<CodeBlock> makeWithStatement(Owned<Statement> statement);

        /**
         * Create a code block wrapping multiple statements. The block is not scoped.
         * @param statements The statements to wrap.
         * @return The block.
         */
        static Owned<CodeBlock> wrapStatements(std::vector<Owned<Statement>> statements);

        /**
         * Make a scoped block.
         * @return The block.
         */
        static Owned<CodeBlock> makeScoped(lang::Location location);

        [[nodiscard]] std::vector<std::reference_wrapper<Statement const>> statements() const;

        /**
         * Append a block to this block.
         * @param block The block to append.
         */
        void append(Owned<CodeBlock> block);

        void setScope(Scope& scope) override;

        void walkDefinitions() override;
        void postResolve() override;

        std::vector<Owned<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry, Function& function) override;

        Scope*                           getBlockScope() override;
        [[nodiscard]] lang::Scope const* getBlockScope() const override;

        [[nodiscard]] bool isCompound() const override;

        void validate(ValidationLogger& validation_logger) const override;

        [[nodiscard]] Statements expandWith(Expressions    subexpressions,
                                            Statements     substatements,
                                            lang::Context& new_context) const override;

        void doBuild(CompileContext& context) override;

      private:
        bool                              scoped_;
        std::vector<Owned<Statement>>       subs_ {};
        Optional<Owned<lang::OrderedScope>> scope_ {};
    };

}

#endif
