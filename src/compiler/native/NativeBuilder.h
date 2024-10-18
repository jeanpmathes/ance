#ifndef ANCE_SRC_COMPILER_NATIVEBUILDER_H_
#define ANCE_SRC_COMPILER_NATIVEBUILDER_H_

#include "compiler/Builder.h"

class NativeBuild;

/**
 * Visitor to build the native IR representation.
 */
class NativeBuilder : public Builder
{
  public:
    using Builder::visit;
    using lang::ApplicationVisitorConst::visit;

    /**
     * Create a new native builder.
     * @param native_build The build context.
     */
    explicit NativeBuilder(NativeBuild& native_build);

    void preVisit(lang::Visitable<ANCE_CONSTRUCTS> const& visitable) override;
    void postVisit(lang::Visitable<ANCE_CONSTRUCTS> const& visitable) override;

  protected:
    Execution& exec() override;

    void visitFunctionDefinition(lang::Function const& function) override;
    void branchToNextOrReturnVoid(lang::BasicBlock const* next) override;
    void branchConditional(lang::bb::def::Branching const& branching_bb, Shared<lang::Value> boolean_truth) override;
    void branchMatching(lang::bb::def::Matching const& matching_bb, Shared<lang::Value> value) override;

  private:
    NativeBuild& native_build_;

    std::map<lang::BasicBlock const*, llvm::BasicBlock*> bb_map_;
};

#endif
