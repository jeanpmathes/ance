#ifndef ANCE_SRC_LANG_CONSTRUCT_BASICBLOCK_H_
#define ANCE_SRC_LANG_CONSTRUCT_BASICBLOCK_H_

#include "lang/statement/Statement.h"

namespace lang
{
    /**
     * A basic block is a sequence of instructions that are executed sequentially.
     * No branching is possible in a basic block, only on exit.
     */
    class BasicBlock
    {
      public:
        /**
         * Create an empty basic block. The block can only link to one other block.
         * The empty block is meant as the initial block of a function.
         * @return The created basic block.
         */
        static BasicBlock* createEmpty();

        /**
         * Create a simple basic block that contains a single statement, and no links.
         * @param statement The statement to add to the basic block.
         * @return The created basic block.
         */
        static BasicBlock* createSimple(std::unique_ptr<Statement> statement);

        /**
         * Link this block to unconditionally jump to the given block.
         * This is only possible if this is a simple block, and no link is already present.
         * @param next The next block to jump to.
         */
        void link(BasicBlock& next);

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
         * Validate this basic block.
         * @param validation_logger The validation logger to use.
         */
        void validate(ValidationLogger& validation_logger);

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
                void setIndex(size_t index);

                virtual void link(BasicBlock& next) = 0;

                virtual void setContainingFunction(lang::Function* function) = 0;

                virtual void validate(ValidationLogger& validation_logger) = 0;

                virtual void prepareBuild(CompileContext* context, llvm::Function* native_function) = 0;
                virtual void doBuild(CompileContext* context)                                       = 0;

              public:
                size_t            index_ {};
                llvm::BasicBlock* native_block_ {};
            };

            class Empty : public Base
            {
              public:
                ~Empty() override = default;

              public:
                void link(BasicBlock& next) override;

                void setContainingFunction(lang::Function* function) override;

                void validate(ValidationLogger& validation_logger) override;

                void prepareBuild(CompileContext* context, llvm::Function* native_function) override;
                void doBuild(CompileContext* context) override;

              private:
                lang::BasicBlock* next_ {nullptr};
            };

            class Simple : public Base
            {
              public:
                explicit Simple(std::unique_ptr<Statement> statement);
                ~Simple() override = default;

              public:
                void link(BasicBlock& next) override;

                void setContainingFunction(lang::Function* function) override;

                void validate(ValidationLogger& validation_logger) override;

                void prepareBuild(CompileContext* context, llvm::Function* native_function) override;
                void doBuild(CompileContext* context) override;

              private:
                std::vector<std::unique_ptr<Statement>> statements_ {};
                lang::BasicBlock*                       next_ {nullptr};
            };
        };

      private:
        std::unique_ptr<Definition::Base> definition_;
        bool                              finalized_ {false};
    };
}

#endif
