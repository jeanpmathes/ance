#ifndef ANCE_SRC_COMPILER_CMP_COMPILETIMEBUILDER_H_
#define ANCE_SRC_COMPILER_CMP_COMPILETIMEBUILDER_H_

#include "compiler/Builder.h"

class CompileTimeBuild;

class CompileTimeBuilder : public Builder
{
  public:
    using Builder::visit;
    using lang::ApplicationVisitorConst::visit;

    /**
     * Create a new compile time builder.
     * @param compile_time_build The build context.
     */
    explicit CompileTimeBuilder(CompileTimeBuild& compile_time_build);

    void preVisit(lang::Visitable<ANCE_CONSTRUCTS> const& visitable) override;
    void postVisit(lang::Visitable<ANCE_CONSTRUCTS> const& visitable) override;

    [[nodiscard]] bool isDescriptionAccepted(lang::Description const& description) const override;
    [[nodiscard]] bool isEntityAccepted(lang::Entity const& entity) const override;

  protected:
    Execution& exec() override;

    void visitFunctionDefinition(lang::Function const& function) override;
    void branchToNextOrReturnVoid(lang::BasicBlock const* next) override;
    void branchConditional(lang::bb::def::Branching const& branching_bb, Shared<lang::Value> boolean_truth) override;
    void branchMatching(lang::bb::def::Matching const& matching_bb, Shared<lang::Value> value) override;

  private:
    bool getB(Shared<lang::Value> value);

    CompileTimeBuild& compile_time_build_;
};

#endif
