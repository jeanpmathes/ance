#ifndef ANCE_SRC_LANG_CONSTRUCT_BASICBLOCK_H_
#define ANCE_SRC_LANG_CONSTRUCT_BASICBLOCK_H_

#include "lang/Element.h"
#include "lang/construct/value/Value.h"
#include "lang/statement/Statement.h"

class ConstantExpression;

namespace lang
{
    /**
     * A basic block is a sequence of instructions that are executed sequentially.
     * No branching is possible in a basic block, only on exit.
     */
    class BasicBlock : public lang::Element<lang::BasicBlock, ANCE_CONSTRUCTS>
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
            Match&                                                         match,
            std::vector<std::pair<ConstantExpression*, Statement*>> const& cases,
            Function&                                                      function);

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
        [[nodiscard]] size_t getId() const;

        /**
         * Get all leaves of this basic block. A leaf is a basic block that is not followed by any other block.
         * @return The leaves of this basic block.
         */
        std::list<lang::BasicBlock const*> getLeaves() const;

        /**
         * Get the blocks that directly follow this block.
         * @return The blocks that directly follow this block.
         */
        std::vector<lang::BasicBlock const*> getSuccessors() const;

        /**
         * Get the return value of this basic block. If this is not a return block, an empty optional is returned.
         * If this is a return block, but no value is returned, the optional contains a nullptr.
         * @return The return value of this basic block.
         */
        Optional<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>> getReturnValue() const;

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
        void reach() const;

        /**
         * Get whether this block is unreached. Call reach() first.
         * @return True if this block is unreached, false otherwise.
         */
        [[nodiscard]] bool isUnreached() const;

        /**
         * Prepare building this basic block, and all following blocks.
         * @param context The current compilation context.
         * @param native_function The native function to build into.
         */
        void prepareBuild(CompileContext& context, llvm::Function* native_function);

        /**
         * Build this basic block, and all following blocks.
         * @param context The current compilation context.
         */
        void doBuild(CompileContext& context);

        /**
         * Get the exit type of this basic block represented as a string.
         * @return The exit type of this basic block.
         */
        std::string getExitRepresentation();

        /**
         * Check if this is a meta-block. A meta-block is not part of actual code.
         * @return True if this is a meta-block, false otherwise.
         */
        [[nodiscard]] bool isMeta() const;

        /**
         * Get all statements in this basic block.t
         * @return References to all statements in this basic block.
         */
        [[nodiscard]] std::vector<std::reference_wrapper<Statement>> const& statements() const;

      private:
        void                 registerIncomingLink(BasicBlock& predecessor);
        void                 updateLink(BasicBlock* former, BasicBlock* updated);
        [[nodiscard]] size_t getIncomingLinkCount() const;
        void                 transferStatements(std::list<Statement*>& statements);

        void addStatement(Statement& statement);

        std::vector<std::reference_wrapper<Statement>> statements_;

      private:
        class Definition
        {
          public:
            class Base
            {
              public:
                virtual ~Base() = default;

              public:
                void        setSelf(BasicBlock* self);
                BasicBlock*                     self();
                [[nodiscard]] BasicBlock const* self() const;

                [[nodiscard]] virtual bool isMeta() const;

                void                 setIndex(size_t& index);
                [[nodiscard]] size_t getIndex() const;
                virtual void         complete(size_t& index) = 0;

                virtual void setLink(BasicBlock& next)                             = 0;
                virtual void updateLink(BasicBlock* former, BasicBlock* updated)   = 0;
                virtual void transferStatements(std::list<Statement*>& statements) = 0;
                virtual void simplify()                                            = 0;

                void                 registerIncomingLink(BasicBlock& block);
                [[nodiscard]] size_t getIncomingLinkCount() const;
                void                 updateIncomingLinks(BasicBlock* updated);

                [[nodiscard]] virtual std::list<lang::BasicBlock const*> getLeaves() const     = 0;
                virtual std::vector<lang::BasicBlock const*>             getSuccessors() const = 0;
                [[nodiscard]] virtual Optional<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>>
                                                     getReturnValue() const;
                [[nodiscard]] virtual lang::Location getStartLocation() const = 0;
                [[nodiscard]] virtual lang::Location getEndLocation() const   = 0;

                virtual void reach() const = 0;

                virtual void prepareBuild(CompileContext& context, llvm::Function* native_function) = 0;
                virtual void doBuild(CompileContext& context)                                       = 0;

                llvm::BasicBlock* getNativeBlock();

                virtual std::string getExitRepresentation() = 0;

              protected:
                size_t            index_ {};
                llvm::BasicBlock* native_block_ {};

              private:
                BasicBlock*              self_ {};
                std::vector<BasicBlock*> incoming_links_ {};
            };

            class Empty : public Base
            {
              public:
                ~Empty() override = default;

              public:
                [[nodiscard]] bool isMeta() const override;

                void complete(size_t& index) override;

                void setLink(BasicBlock& next) override;
                void updateLink(BasicBlock* former, BasicBlock* updated) override;
                void simplify() override;

                void transferStatements(std::list<Statement*>& statements) override;

                [[nodiscard]] std::list<lang::BasicBlock const*> getLeaves() const override;
                std::vector<lang::BasicBlock const*>             getSuccessors() const override;
                [[nodiscard]] lang::Location                     getStartLocation() const override;
                [[nodiscard]] lang::Location                     getEndLocation() const override;

                void reach() const override;

                void prepareBuild(CompileContext& context, llvm::Function* native_function) override;
                void doBuild(CompileContext& context) override;

                std::string getExitRepresentation() override;

              private:
                lang::BasicBlock* next_ {nullptr};
            };

            class Finalizing : public Base
            {
              public:
                Finalizing(lang::Scope& scope, std::string info);
                ~Finalizing() override = default;

              public:
                [[nodiscard]] bool isMeta() const override;

                void complete(size_t& index) override;

                void setLink(BasicBlock& next) override;
                void updateLink(BasicBlock* former, BasicBlock* updated) override;
                void simplify() override;

                void transferStatements(std::list<Statement*>& statements) override;

                [[nodiscard]] std::list<lang::BasicBlock const*> getLeaves() const override;
                std::vector<lang::BasicBlock const*>             getSuccessors() const override;
                [[nodiscard]] lang::Location                     getStartLocation() const override;
                [[nodiscard]] lang::Location                     getEndLocation() const override;

                void reach() const override;

                void prepareBuild(CompileContext& context, llvm::Function* native_function) override;
                void doBuild(CompileContext& context) override;

                std::string getExitRepresentation() override;

              private:
                lang::BasicBlock* next_ {nullptr};
                lang::Scope&      scope_;
                std::string       info_ {};
            };

            class Simple : public Base
            {
              public:
                Simple();
                explicit Simple(Statement& statement);
                ~Simple() override = default;

              public:
                void complete(size_t& index) override;

                void setLink(BasicBlock& next) override;
                void updateLink(BasicBlock* former, BasicBlock* updated) override;
                void simplify() override;

                void transferStatements(std::list<Statement*>& statements) override;

                [[nodiscard]] std::list<lang::BasicBlock const*> getLeaves() const override;
                std::vector<lang::BasicBlock const*>             getSuccessors() const override;
                [[nodiscard]] lang::Location                     getStartLocation() const override;
                [[nodiscard]] lang::Location                     getEndLocation() const override;

                void reach() const override;

                void prepareBuild(CompileContext& context, llvm::Function* native_function) override;
                void doBuild(CompileContext& context) override;

                std::string getExitRepresentation() override;

              private:
                std::list<Statement*> statements_ {};
                lang::BasicBlock*     next_ {nullptr};
            };

            class Returning : public Base
            {
              public:
                explicit Returning(lang::Scope& scope, Expression& return_value);
                ~Returning() override = default;

              public:
                void complete(size_t& index) override;

                void setLink(BasicBlock& next) override;
                void updateLink(BasicBlock* former, BasicBlock* updated) override;
                void simplify() override;

                void transferStatements(std::list<Statement*>& statements) override;

                [[nodiscard]] std::list<lang::BasicBlock const*> getLeaves() const override;
                std::vector<lang::BasicBlock const*>             getSuccessors() const override;
                [[nodiscard]] Optional<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>>
                                             getReturnValue() const override;
                [[nodiscard]] lang::Location getStartLocation() const override;
                [[nodiscard]] lang::Location getEndLocation() const override;

                void reach() const override;

                void prepareBuild(CompileContext& context, llvm::Function* native_function) override;
                void doBuild(CompileContext& context) override;

                std::string getExitRepresentation() override;

              private:
                std::list<Statement*> statements_ {};
                lang::BasicBlock*     unreachable_next_ {nullptr};
                Expression&           return_value_;
                lang::Scope&          scope_;
            };

            class Branching : public Base
            {
              public:
                explicit Branching(Expression& condition);
                ~Branching() override = default;

              public:
                void complete(size_t& index) override;

                void setLink(BasicBlock& next) override;
                void updateLink(BasicBlock* former, BasicBlock* updated) override;
                void simplify() override;

                void transferStatements(std::list<Statement*>& statements) override;

                [[nodiscard]] std::list<lang::BasicBlock const*> getLeaves() const override;
                std::vector<lang::BasicBlock const*>             getSuccessors() const override;
                [[nodiscard]] lang::Location                     getStartLocation() const override;
                [[nodiscard]] lang::Location                     getEndLocation() const override;

                void reach() const override;

                void prepareBuild(CompileContext& context, llvm::Function* native_function) override;
                void doBuild(CompileContext& context) override;

                std::string getExitRepresentation() override;

              private:
                std::list<Statement*> statements_ {};

                lang::BasicBlock* true_next_ {nullptr};
                lang::BasicBlock* false_next_ {nullptr};

                Expression& condition_;
            };

            class Matching : public Base
            {
              public:
                explicit Matching(Match& match, std::vector<std::vector<ConstantExpression*>> cases);
                ~Matching() override = default;

              public:
                void complete(size_t& index) override;

                void setLink(BasicBlock& next) override;
                void updateLink(BasicBlock* former, BasicBlock* updated) override;
                void simplify() override;

                void transferStatements(std::list<Statement*>& statements) override;

                [[nodiscard]] std::list<lang::BasicBlock const*> getLeaves() const override;
                std::vector<lang::BasicBlock const*>             getSuccessors() const override;
                [[nodiscard]] lang::Location                     getStartLocation() const override;
                [[nodiscard]] lang::Location                     getEndLocation() const override;

                void reach() const override;

                void prepareBuild(CompileContext& context, llvm::Function* native_function) override;
                void doBuild(CompileContext& context) override;

                std::string getExitRepresentation() override;

              private:
                std::list<Statement*> statements_ {};

                std::vector<lang::BasicBlock*> branches_ {};

                Match&                                        match_;
                std::vector<std::vector<ConstantExpression*>> cases_;
            };
        };

      public:
        explicit BasicBlock(Owned<Definition::Base> definition);

      private:
        Owned<Definition::Base>                              definition_;
        lang::Function*                                      containing_function_ {nullptr};
        mutable Optional<std::list<lang::BasicBlock const*>> leaves_ {};

        bool         simplified_ {false};
        bool         unused_ {false};
        bool         finalized_ {false};
        mutable bool reached_ {false};

        bool build_prepared_ {false};
        bool build_done_ {false};
    };
}

#endif
