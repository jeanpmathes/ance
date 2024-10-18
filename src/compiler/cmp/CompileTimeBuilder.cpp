#include "CompileTimeBuilder.h"

#include "compiler/cmp/CompileTimeValue.h"
#include "compiler/cmp/CompileTimeBuild.h"

CompileTimeBuilder::CompileTimeBuilder(CompileTimeBuild& compile_time_build) : compile_time_build_(compile_time_build)
{
    compile_time_build_.setActiveVisitor(this);
}

bool CompileTimeBuilder::isDescriptionAccepted(lang::Description const& description) const
{
    return description.isCMP();
}

Execution& CompileTimeBuilder::exec()
{
    return compile_time_build_;
}

void CompileTimeBuilder::visitFunctionDefinition(lang::Function const& function)
{
    exec().defineFunctionBody(function, [this](Execution::FnCtx& ctx) {
        ctx.function().registerEntityDeclarations(ctx.exec());

        for (size_t parameter = 0; parameter < ctx.function().parameterCount(); parameter++)
        {
            ctx.function().parameter(parameter).argument().performInitialization(ctx.exec());
        }

        visitTree(*ctx.function().getEntryBlock());
    });
}

void CompileTimeBuilder::branchToNextOrReturnVoid(lang::BasicBlock const* next)
{
    if (next != nullptr) visitTree(*next);
    else exec().performReturn(std::nullopt);
}

void CompileTimeBuilder::branchConditional(lang::bb::def::Branching const& branching_bb, Shared<lang::Value> boolean_truth)
{
    bool const is_true = getB(boolean_truth);

    if (is_true) visitTree(*branching_bb.trueNext());
    else visitTree(*branching_bb.falseNext());
}

void CompileTimeBuilder::branchMatching(lang::bb::def::Matching const& matching_bb, Shared<lang::Value> value)
{
    auto const& cases    = matching_bb.cases();
    auto const& branches = matching_bb.branches();

    lang::BasicBlock const* target_block = nullptr;

    for (auto const [case_values, branch_block] : llvm::zip(cases, branches))
    {
        if (case_values.empty())
        {
            target_block = branch_block;
            continue;
        }

        for (auto& case_value : case_values)
        {
            Shared<lang::Constant> constant = getC(*case_value);

            Shared<lang::Value> is_equal = exec().performOperator(lang::BinaryOperator::EQUAL, value, constant);
            if (getB(is_equal))
            {
                target_block = branch_block;
                break;
            }
        }

        if (target_block != nullptr) break;
    }

    visitTree(*target_block);
}

bool CompileTimeBuilder::getB(Shared<lang::Value> value)
{
    return compile_time_build_.cmpContentOf(value).cast<cmp::BooleanValue>()->value();
}
