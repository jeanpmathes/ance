#include "CompileTimeBuilder.h"

#include "compiler/cmp/CompileTimeBuild.h"

CompileTimeBuilder::CompileTimeBuilder(CompileTimeBuild& compile_time_build) : compile_time_build_(compile_time_build)
{
    compile_time_build_.setActiveVisitor(this);
}

Execution& CompileTimeBuilder::exec()
{
    return compile_time_build_;
}

void CompileTimeBuilder::visitFunctionDefinition(lang::Function const&)
{
    assert(false);// todo: implement
}

std::any CompileTimeBuilder::visit(lang::bb::def::Empty const&)
{
    assert(false);// todo: implement
    return {};
}

std::any CompileTimeBuilder::visit(lang::bb::def::Finalizing const&)
{
    assert(false);// todo: implement
    return {};
}

std::any CompileTimeBuilder::visit(lang::bb::def::Simple const&)
{
    assert(false);// todo: implement
    return {};
}

std::any CompileTimeBuilder::visit(lang::bb::def::Returning const&)
{
    assert(false);// todo: implement
    return {};
}

std::any CompileTimeBuilder::visit(lang::bb::def::Branching const&)
{
    assert(false);// todo: implement
    return {};
}

std::any CompileTimeBuilder::visit(lang::bb::def::Matching const&)
{
    assert(false);// todo: implement
    return {};
}
