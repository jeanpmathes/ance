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

    [[nodiscard]] bool isDescriptionAccepted(lang::Description const& description) const override;

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
    CompileTimeBuild& compile_time_build_;
};

#endif
