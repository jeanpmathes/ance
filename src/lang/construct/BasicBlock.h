#ifndef ANCE_SRC_LANG_CONSTRUCT_BASICBLOCK_H_
#define ANCE_SRC_LANG_CONSTRUCT_BASICBLOCK_H_

#include "lang/statement/Statement.h"
#include "lang/construct/value/Value.h"
#include "lang/Element.h"

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
        static std::unique_ptr<BasicBlock> createEmpty();

        /**
         * Create a simple basic block that contains a single or no statement, and no links.
         * @param statement The statement to add to the basic block, or nullptr if no statement should be added.
         * @return The created basic block.
         */
        static std::unique_ptr<BasicBlock> createSimple(Statement* statement = nullptr);

        /**
         * Create a basic block that returns from the function.
         * @param expression The expression providing the return value, or nullptr if no value is returned.
         * @param return_location The location of the return statement.
         * @return The created basic block.
         */
        static std::unique_ptr<BasicBlock> createReturning(Expression* expression, lang::Location return_location);

        /**
         * Create a basic block that branches depending on the value of an expression.
         * @param condition The expression providing the condition.
         * @param true_block The block to execute if the condition is true.
         * @param false_block The block to execute if the condition is false.
         * @param function The function containing the basic block.
         * @return The created basic blocks.
         */
        static std::vector<std::unique_ptr<BasicBlock>> createBranching(Expression*      condition,
                                                                        lang::CodeBlock* true_block,
                                                                        lang::CodeBlock* false_block,
                                                                        lang::Function*  function);

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
        void setContainingFunction(lang::Function* function);

        /**
         * Finalize the basic block.
         * @param index A reference to an index, initialized to 0, that is incremented for each block finalization.
         */
        void finalize(size_t& index);

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
         * Validate this basic block.
         * @param validation_logger The validation logger to use.
         * @return Whether the basic block is valid.
         */
        bool validate(ValidationLogger& validation_logger);

        /**
         * Get all leaves of this basic block. A leave is a basic block that is not followed by any other block.
         * @return The leaves of this basic block.
         */
        std::list<lang::BasicBlock*> getLeaves();

        /**
         * Get the blocks that directly follow this block.
         * @return The blocks that directly follow this block.
         */
        std::vector<lang::BasicBlock*> getSuccessors();

        /**
         * Get the return value of this basic block. If this is not a return block, an empty optional is returned.
         * If this is a return block, but no value is returned, the optional contains a nullptr.
         * @return The return value of this basic block.
         */
        std::optional<std::pair<std::shared_ptr<lang::Value>, lang::Location>> getReturnValue();

        /**
         * Get the location of the first statement in this basic block.
         * @return The location, or a global location if no statements are present.
         */
        lang::Location getStartLocation();

        /**
         * Get the location of the last statement in this basic block.
         * @return The location, or a global location if no statements are present.
         */
        lang::Location getEndLocation();

        /**
         * Reach this block and all that follow it.
         */
        void reach();

        /**
         * Get whether this block is unreached.
         * @return True if this block is unreached, false otherwise.
         */
        [[nodiscard]] bool isUnreached() const;

        /**
         * Prepare building this basic block, and all following blocks.
         * @param context The current compilation context.
         * @param native_function The native function to build into.
         */
        void prepareBuild(CompileContext* context, llvm::Function* native_function);

        /**
         * Build this basic block, and all following blocks.
         * @param context The current compilation context.
         */
        void doBuild(CompileContext* context);

      private:
        void                 registerIncomingLink(BasicBlock& predecessor);
        void                 updateLink(BasicBlock* former, BasicBlock* updated);
        [[nodiscard]] size_t getIncomingLinkCount() const;
        void                 transferStatements(std::list<Statement*>& statements);

        BasicBlock() = default;

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
                BasicBlock* self();

                void                 setIndex(size_t& index);
                [[nodiscard]] size_t getIndex() const;
                virtual void         finalize(size_t& index) = 0;

                virtual void setLink(BasicBlock& next)                                             = 0;
                virtual void updateLink(BasicBlock* former, BasicBlock* updated)                   = 0;
                virtual void transferStatements(std::list<Statement*>& statements)                 = 0;
                virtual void simplify()                                                            = 0;

                void                 registerIncomingLink(BasicBlock& block);
                [[nodiscard]] size_t getIncomingLinkCount() const;
                void                 updateIncomingLinks(BasicBlock* updated);

                virtual bool                           validate(ValidationLogger& validation_logger) = 0;
                virtual std::list<lang::BasicBlock*>   getLeaves()                                   = 0;
                virtual std::vector<lang::BasicBlock*> getSuccessors()                               = 0;
                virtual std::optional<std::pair<std::shared_ptr<lang::Value>, lang::Location>> getReturnValue();
                virtual lang::Location                                                         getStartLocation() = 0;
                virtual lang::Location                                                         getEndLocation()   = 0;

                virtual void reach() = 0;

                virtual void prepareBuild(CompileContext* context, llvm::Function* native_function) = 0;
                virtual void doBuild(CompileContext* context)                                       = 0;

                llvm::BasicBlock* getNativeBlock();

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
                void finalize(size_t& index) override;

                void setLink(BasicBlock& next) override;
                void updateLink(BasicBlock* former, BasicBlock* updated) override;
                void simplify() override;

                void transferStatements(std::list<Statement*>& statements) override;

                bool                           validate(ValidationLogger& validation_logger) override;
                std::list<lang::BasicBlock*>   getLeaves() override;
                std::vector<lang::BasicBlock*> getSuccessors() override;
                lang::Location                 getStartLocation() override;
                lang::Location               getEndLocation() override;

                void reach() override;

                void prepareBuild(CompileContext* context, llvm::Function* native_function) override;
                void doBuild(CompileContext* context) override;

              private:
                lang::BasicBlock* next_ {nullptr};
            };

            class Simple : public Base
            {
              public:
                Simple();
                explicit Simple(Statement* statement);
                ~Simple() override = default;

              public:
                void finalize(size_t& index) override;

                void setLink(BasicBlock& next) override;
                void updateLink(BasicBlock* former, BasicBlock* updated) override;
                void simplify() override;

                void transferStatements(std::list<Statement*>& statements) override;

                bool                           validate(ValidationLogger& validation_logger) override;
                std::list<lang::BasicBlock*>   getLeaves() override;
                std::vector<lang::BasicBlock*> getSuccessors() override;
                lang::Location                 getStartLocation() override;
                lang::Location               getEndLocation() override;

                void reach() override;

                void prepareBuild(CompileContext* context, llvm::Function* native_function) override;
                void doBuild(CompileContext* context) override;

              private:
                std::list<Statement*> statements_ {};
                lang::BasicBlock*     next_ {nullptr};
            };

            class Returning : public Base
            {
              public:
                explicit Returning(Expression* return_value, lang::Location return_location);
                ~Returning() override = default;

              public:
                void finalize(size_t& index) override;

                void setLink(BasicBlock& next) override;
                void updateLink(BasicBlock* former, BasicBlock* updated) override;
                void simplify() override;

                void transferStatements(std::list<Statement*>& statements) override;

                bool                           validate(ValidationLogger& validation_logger) override;
                std::list<lang::BasicBlock*>   getLeaves() override;
                std::vector<lang::BasicBlock*> getSuccessors() override;
                std::optional<std::pair<std::shared_ptr<lang::Value>, lang::Location>> getReturnValue() override;
                lang::Location                                                         getStartLocation() override;
                lang::Location                                                         getEndLocation() override;

                void reach() override;

                void prepareBuild(CompileContext* context, llvm::Function* native_function) override;
                void doBuild(CompileContext* context) override;

              private:
                std::list<Statement*> statements_ {};
                lang::BasicBlock*     unreachable_next_ {nullptr};
                Expression*           return_value_;
                lang::Location        return_location_;
            };

            class Branching : public Base
            {
              public:
                explicit Branching(Expression* condition);
                ~Branching() override = default;

              public:
                void finalize(size_t& index) override;

                void setLink(BasicBlock& next) override;
                void updateLink(BasicBlock* former, BasicBlock* updated) override;
                void simplify() override;

                void transferStatements(std::list<Statement*>& statements) override;

                bool                           validate(ValidationLogger& validation_logger) override;
                std::list<lang::BasicBlock*>   getLeaves() override;
                std::vector<lang::BasicBlock*> getSuccessors() override;
                lang::Location                 getStartLocation() override;
                lang::Location                 getEndLocation() override;

                void reach() override;

                void prepareBuild(CompileContext* context, llvm::Function* native_function) override;
                void doBuild(CompileContext* context) override;

              private:
                std::list<Statement*> statements_ {};

                lang::BasicBlock* true_next_ {nullptr};
                lang::BasicBlock* false_next_ {nullptr};

                Expression* condition_;
            };
        };

      private:
        std::unique_ptr<Definition::Base>           definition_;
        lang::Function*                             containing_function_ {nullptr};
        std::optional<std::list<lang::BasicBlock*>> leaves_ {};

        bool simplified_ {false};
        bool unused_ {false};
        bool finalized_ {false};
        bool reached_ {false};

        bool build_prepared_ {false};
        bool build_done_ {false};

        std::optional<bool> validated_ {};
    };
}

#endif
