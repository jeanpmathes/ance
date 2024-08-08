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

    std::any visit(lang::bb::def::Empty const& emtpy_bb) override;
    std::any visit(lang::bb::def::Finalizing const& finalizing_bb) override;
    std::any visit(lang::bb::def::Simple const& simple_bb) override;
    std::any visit(lang::bb::def::Returning const& returning_bb) override;
    std::any visit(lang::bb::def::Branching const& branching_bb) override;
    std::any visit(lang::bb::def::Matching const& matching_bb) override;

  protected:
    Execution& exec() override;

    void visitFunctionDefinition(lang::Function const& function) override;

  private:
    void branchToNextOrReturnVoid(lang::BasicBlock const* next);

    NativeBuild& native_build_;

    std::map<lang::BasicBlock const*, llvm::BasicBlock*> bb_map_;
};

#endif
