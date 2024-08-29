#include "CompileTimeBuilder.h"

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

void CompileTimeBuilder::visitFunctionDefinition(lang::Function const&)
{
    // todo: implement
}

std::any CompileTimeBuilder::visit(lang::bb::def::Empty const&)
{
    // todo: implement

    return {};
}

std::any CompileTimeBuilder::visit(lang::bb::def::Finalizing const&)
{
    // todo: implement

    return {};
}

std::any CompileTimeBuilder::visit(lang::bb::def::Simple const&)
{
    // todo: implement

    return {};
}

std::any CompileTimeBuilder::visit(lang::bb::def::Returning const&)
{
    // todo: implement

    return {};
}

std::any CompileTimeBuilder::visit(lang::bb::def::Branching const&)
{
    // todo: implement

    return {};
}

std::any CompileTimeBuilder::visit(lang::bb::def::Matching const&)
{
    assert(false);// todo: implement
    return {};
}
