#ifndef ANCE_SRC_LANG_CONSTRUCT_BASICBLOCK_H_
#define ANCE_SRC_LANG_CONSTRUCT_BASICBLOCK_H_

#include "lang/Element.h"
#include "lang/construct/Value.h"
#include "lang/statement/Statement.h"

namespace lang
{
    /**
     * A basic block is a sequence of instructions that are executed sequentially.
     * No branching is possible in a basic block, only on exit.
     */
    class BasicBlock : public virtual lang::Visitable<ANCE_CONSTRUCTS>
    {
      public:
        /**
         * Create an empty basic block. The block can only link to one other block.
         * The empty block is meant as the initial block of a function.
         * @return The created basic block.
         */
        static Owned<BasicBlock> createEmpty();

        /**
         * Create a finalizing scope that is used to finalize a scope.
         * @param scope The scope to finalize.
         * @param info Information about the scope.
         * @return The finalizing block.
         */
        static Owned<BasicBlock> createFinalizing(lang::Scope& scope, std::string info);

        /**
         * Create a simple basic block that contains a single or no statement, and no links.
         * @param statement The statement to add to the basic block, or nullptr if no statement should be added.
         * @return The created basic block.
         */
        static Owned<BasicBlock> createSimple(Statement* statement = nullptr);

        /**
         * Create a basic block that returns from the function.
         * @param scope The scope to return from.
         * @param expression The expression providing the return value.
         * @param function The function that contains the basic block.
         * @return The created basic block.
         */
        static Owned<BasicBlock> createReturning(lang::Scope& scope, Expression& expression, Function& function);

        /**
         * Create a basic block that branches depending on the value of an expression.
         * @param condition The expression providing the condition.
         * @param true_block The block to execute if the condition is true.
         * @param false_block The block to execute if the condition is false.
         * @param function The function containing the basic block.
         * @return The created basic blocks.
         */
        static std::vector<Owned<BasicBlock>> createBranching(Expression& condition,
                                                              Statement&  true_block,
                                                              Statement*  false_block,
                                                              Function&   function);

        /**
         * Create a basic block that loops forever.
         * @param code_block The block to execute as long as the condition is true.
         * @param loop_parts The loop parts to set that are used by loop control statements.
         * @param function The function containing the basic block.
         * @return The created basic blocks.
         */
        static std::vector<Owned<BasicBlock>> createLooping(Statement&                                       code_block,
                                                            std::pair<lang::BasicBlock*, lang::BasicBlock*>* loop_parts,
                                                            Function&                                        function);

        /**
         * Create basis blocks that match a case for a given value.
         * @param match The match statement.
         * @param cases The cases to match. These are pairs of (value, block), where multiple values can use the same block. For the default case, the condition is null.
         * @param function The function containing the basic block.
         * @return The created basic blocks.
         */
        static std::vector<Owned<BasicBlock>> createMatching(
            Match&                                                        match,
            std::vector<std::pair<LiteralExpression*, Statement*>> const& cases,
            Function&                                                     function);

        /**
         * Create a jump to a basic block.
         * @param from The block to jump from.
         * @param to The block to jump to.
         * @param scopes The scopes to jump over. These scopes will be finalized.
         * @return The created basic block.
         */
        static std::vector<Owned<BasicBlock>> createJump(lang::BasicBlock&                from,
                                                         lang::BasicBlock&                to,
                                                         std::vector<lang::Scope*> const& scopes);

      public:
        /**
         * Link this block to unconditionally jump to the given block.
         * This is only possible if this is a simple block, and no link is already present.
         * @param next The next block to jump to.
         */
        void link(BasicBlock& next);

        /**
         * Simplify this basic block and all that follow it.
         */
        void simplify();

        /**
         * Set the containing function of this basic block.
         * @param function The function that contains this basic block.
         */
        void setContainingFunction(Function& function);

        /**
         * Get the containing function of this basic block.
         * @return The function that contains this basic block.
         */
        lang::Function const* getContainingFunction() const;

        /**
         * Complete the basic block.
         * @param index A reference to an index, initialized to 0, that is incremented for each block finalization.
         */
        void complete(size_t& index);

        /**
         * Whether this basic block is actually usable, i.e. it contains statements and was not simplified away.
         * This does not mean that the block is reachable.
         * @return True if this basic block is usable.
         */
        [[nodiscard]] bool isUsable() const;

        /**
         * Get the ID of this basic block.
         * @return The ID of this basic block.
         */
        [[nodiscard]] size_t id() const;

        /**
         * Get all leaves of this basic block. A leaf is a basic block that is not followed by any other block.
         * @return The leaves of this basic block.
         */
        std::list<lang::BasicBlock const*> getLeaves() const;

        /**
         * Get the blocks that directly follow this block.
         * @return The blocks that directly follow this block.
         */
        virtual std::vector<lang::BasicBlock const*> getSuccessors() const = 0;

        /**
         * Get the return type of this basic block.
         * If this is not a return block, or a return block without return statement, an empty optional is returned.
         * @return The return type of this basic block.
         */
        virtual Optional<std::pair<std::reference_wrapper<lang::Type const>, lang::Location>> getReturnType() const;

        /**
         * Get the location of the first statement in this basic block.
         * @return The location, or a global location if no statements are present.
         */
        lang::Location getStartLocation() const;

        /**
         * Get the location of the last statement in this basic block.
         * @return The location, or a global location if no statements are present.
         */
        lang::Location getEndLocation() const;

        /**
         * Reach this block and all that follow it.
         */
        void reach();

        /**
         * Get whether this block is unreached. Call reach() first.
         * @return True if this block is unreached, false otherwise.
         */
        [[nodiscard]] bool isUnreached() const;

        /**
         * Get the exit type of this basic block represented as a string.
         * @return The exit representation.
         */
        [[nodiscard]] virtual std::string getExitRepresentation() const = 0;

        /**
         * Check if this is a meta-block. A meta-block is not part of actual code.
         * @return True if this is a meta-block, false otherwise.
         */
        [[nodiscard]] virtual bool isMeta() const;

        void                 registerIncomingLink(BasicBlock& predecessor);
        virtual void         updateLink(BasicBlock* former, BasicBlock* updated) = 0;
        [[nodiscard]] size_t getIncomingLinkCount() const;
        void                 transferStatements(std::list<Statement*>& statements);

        void markAsUnused();

        std::vector<Statement const*> statements() const;

      protected:
        void pushStatement(Statement& statement);

        virtual void setLink(BasicBlock& next) = 0;
        void         updateIncomingLinks(BasicBlock* updated);

        [[nodiscard]] virtual bool isSimplificationCandidate() const;

        [[nodiscard]] virtual std::vector<lang::BasicBlock*> getReachableNext() = 0;
        [[nodiscard]] virtual std::vector<lang::BasicBlock*> getUnreachableNext();

      private:
        lang::Function*                                      containing_function_ {nullptr};
        mutable Optional<std::list<lang::BasicBlock const*>> leaves_ {};

        bool         simplified_ {false};
        bool         unused_ {false};
        bool         finalized_ {false};
        bool         reached_ {false};

        std::vector<BasicBlock*> incoming_links_ {};
        size_t                   index_ {};
        std::list<Statement*>    statements_ {};
    };

    namespace bb::def
    {
        class Empty
            : public BasicBlock
            , public lang::Element<Empty, ANCE_CONSTRUCTS>
        {
          public:
            Empty()           = default;
            ~Empty() override = default;

            [[nodiscard]] lang::BasicBlock const* next() const;

          public:
            [[nodiscard]] bool isMeta() const override;

            void setLink(BasicBlock& next) override;
            void updateLink(BasicBlock* former, BasicBlock* updated) override;

            [[nodiscard]] std::vector<lang::BasicBlock const*> getSuccessors() const override;
            [[nodiscard]] std::string getExitRepresentation() const override;

          protected:
            std::vector<lang::BasicBlock*> getReachableNext() override;

          private:
            lang::BasicBlock* next_ {nullptr};
        };

        class Finalizing
            : public BasicBlock
            , public lang::Element<Finalizing, ANCE_CONSTRUCTS>
        {
          public:
            Finalizing(lang::Scope& scope, std::string info);
            ~Finalizing() override = default;

            [[nodiscard]] lang::BasicBlock const* next() const;
            [[nodiscard]] lang::Scope const&      scope() const;

          public:
            [[nodiscard]] bool isMeta() const override;

            void setLink(BasicBlock& next) override;
            void updateLink(BasicBlock* former, BasicBlock* updated) override;

            [[nodiscard]] std::vector<lang::BasicBlock const*> getSuccessors() const override;
            [[nodiscard]] std::string getExitRepresentation() const override;

          protected:
            std::vector<lang::BasicBlock*> getReachableNext() override;

          private:
            lang::BasicBlock* next_ {nullptr};
            lang::Scope&      scope_;
            std::string       info_ {};
        };

        class Simple
            : public BasicBlock
            , public lang::Element<Simple, ANCE_CONSTRUCTS>
        {
          public:
            Simple();
            explicit Simple(Statement& statement);
            ~Simple() override = default;

            [[nodiscard]] lang::BasicBlock const*      next() const;

          public:
            void setLink(BasicBlock& next) override;
            void updateLink(BasicBlock* former, BasicBlock* updated) override;
            [[nodiscard]] bool isSimplificationCandidate() const override;

            [[nodiscard]] std::vector<lang::BasicBlock const*> getSuccessors() const override;
            [[nodiscard]] std::string getExitRepresentation() const override;

          protected:
            std::vector<lang::BasicBlock*> getReachableNext() override;

          private:
            lang::BasicBlock*     next_ {nullptr};
        };

        class Returning
            : public BasicBlock
            , public lang::Element<Returning, ANCE_CONSTRUCTS>
        {
          public:
            explicit Returning(lang::Scope& scope, Expression& return_value);
            ~Returning() override = default;

            [[nodiscard]] lang::Scope const&           scope() const;
            [[nodiscard]] Expression const&            ret() const;

          public:
            void setLink(BasicBlock& next) override;
            void updateLink(BasicBlock* former, BasicBlock* updated) override;
            [[nodiscard]] std::vector<lang::BasicBlock const*> getSuccessors() const override;

            [[nodiscard]] Optional<std::pair<std::reference_wrapper<lang::Type const>, Location>> getReturnType()
                const override;

            [[nodiscard]] std::string getExitRepresentation() const override;

          protected:
            std::vector<lang::BasicBlock*> getReachableNext() override;
            std::vector<lang::BasicBlock*> getUnreachableNext() override;

          private:
            lang::BasicBlock*     unreachable_next_ {nullptr};
            Expression&           return_value_;
            lang::Scope&          scope_;
        };

        class Branching
            : public BasicBlock
            , public lang::Element<Branching, ANCE_CONSTRUCTS>
        {
          public:
            explicit Branching(Expression& condition);
            ~Branching() override = default;

            [[nodiscard]] Expression const&            condition() const;

            [[nodiscard]] lang::BasicBlock const* trueNext() const;
            [[nodiscard]] lang::BasicBlock const* falseNext() const;

          public:
            void setLink(BasicBlock& next) override;
            void updateLink(BasicBlock* former, BasicBlock* updated) override;

            [[nodiscard]] std::vector<lang::BasicBlock const*> getSuccessors() const override;
            [[nodiscard]] std::string getExitRepresentation() const override;

          protected:
            std::vector<lang::BasicBlock*> getReachableNext() override;

          private:
            lang::BasicBlock* true_next_ {nullptr};
            lang::BasicBlock* false_next_ {nullptr};

            Expression& condition_;
        };

        class Matching
            : public BasicBlock
            , public lang::Element<Matching, ANCE_CONSTRUCTS>
        {
          public:
            explicit Matching(Match& match, std::vector<std::vector<LiteralExpression*>> cases);
            ~Matching() override = default;

            [[nodiscard]] Expression const&            matched() const;

            [[nodiscard]] std::vector<std::vector<LiteralExpression*>> const& cases() const;
            [[nodiscard]] std::vector<lang::BasicBlock*> const&               branches() const;

          public:
            void setLink(BasicBlock& next) override;
            void updateLink(BasicBlock* former, BasicBlock* updated) override;

            [[nodiscard]] std::vector<lang::BasicBlock const*> getSuccessors() const override;
            [[nodiscard]] std::string getExitRepresentation() const override;

          protected:
            std::vector<lang::BasicBlock*> getReachableNext() override;

          private:
            std::vector<lang::BasicBlock*> branches_ {};

            Match&                                       match_;
            std::vector<std::vector<LiteralExpression*>> cases_;
        };
    }
}

#endif
