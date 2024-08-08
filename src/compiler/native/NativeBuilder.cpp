#include "NativeBuilder.h"

#include "compiler/native/NativeBuild.h"
#include "compiler/native/RoughlyCastedValue.h"

NativeBuilder::NativeBuilder(NativeBuild& native_build) : native_build_(native_build)
{
    native_build_.setActiveVisitor(this);
}

void NativeBuilder::preVisit(lang::Visitable<ANCE_CONSTRUCTS> const& visitable)
{
    auto const* located = dynamic_cast<lang::Located const*>(&visitable);
    if (located != nullptr) { native_build_.setDebugLocation(located->location(), located->scope()); }
}

void NativeBuilder::postVisit(lang::Visitable<ANCE_CONSTRUCTS> const& visitable)
{
    auto const* located = dynamic_cast<lang::Located const*>(&visitable);
    if (located != nullptr) { native_build_.resetDebugLocation(); }
}

std::any NativeBuilder::visit(lang::bb::def::Empty const& empty_bb)
{
    branchToNextOrReturnVoid(empty_bb.next());

    return {};
}

std::any NativeBuilder::visit(lang::bb::def::Finalizing const& finalizing_bb)
{
    finalizing_bb.scope().performEntityFinalizations(native_build_);

    branchToNextOrReturnVoid(finalizing_bb.next());

    return {};
}

std::any NativeBuilder::visit(lang::bb::def::Simple const& simple_bb)
{
    for (Statement const* statement : simple_bb.statements()) visitTree(*statement);

    branchToNextOrReturnVoid(simple_bb.next());

    return {};
}

std::any NativeBuilder::visit(lang::bb::def::Returning const& returning_bb)
{
    for (Statement const* statement : returning_bb.statements()) visitTree(*statement);

    lang::Scope const* current = &returning_bb.scope();
    while (current->isPartOfFunction())
    {
        current->performEntityFinalizations(native_build_);
        current = &current->scope();
    }

    lang::Type const& return_type = returning_bb.getContainingFunction()->returnType();

    if (return_type.isUnitType()) { native_build_.performReturn(std::nullopt); }
    else
    {
        Shared<lang::Value> return_value = getV(returning_bb.ret());

        return_value = lang::Type::makeMatching(return_type, return_value, native_build_);

        native_build_.performReturn(return_value);
    }

    return {};
}

std::any NativeBuilder::visit(lang::bb::def::Branching const& branching_bb)
{
    for (Statement const* statement : branching_bb.statements()) visitTree(*statement);

    Shared<lang::Value> truth = getV(branching_bb.condition());
    Shared<lang::Value> boolean_truth =
        lang::Type::makeMatching(native_build_.ctx().getBooleanType(), truth, native_build_);

    native_build_.ir().CreateCondBr(native_build_.llvmContentValue(boolean_truth),
                                    bb_map_[branching_bb.trueNext()],
                                    bb_map_[branching_bb.falseNext()]);

    return {};
}

std::any NativeBuilder::visit(lang::bb::def::Matching const& matching_bb)
{
    auto const& cases    = matching_bb.cases();
    auto const& branches = matching_bb.branches();

    for (Statement const* statement : matching_bb.statements()) visitTree(*statement);

    llvm::BasicBlock* default_block = nullptr;

    for (auto const [case_values, branch_block] : llvm::zip(cases, branches))
    {
        if (case_values.empty())
        {
            default_block = bb_map_[branch_block];
            break;
        }
    }

    if (!default_block) { default_block = bb_map_[branches.front()]; }

    Shared<lang::Value> value = getV(matching_bb.matched());

    auto switch_instance = native_build_.ir().CreateSwitch(native_build_.llvmContentValue(value),
                                                           default_block,
                                                           static_cast<unsigned>(cases.size()));

    for (auto const [case_values, branch_block] : llvm::zip(cases, branches))
    {
        llvm::BasicBlock* branch_native_block = bb_map_[branch_block];

        if (case_values.empty() || branch_native_block == default_block) continue;

        for (auto& case_value : case_values)
        {
            Shared<lang::Constant> constant = getC(*case_value);

            auto native_integer_constant = llvm::cast<llvm::ConstantInt>(native_build_.llvmConstant(constant));
            switch_instance->addCase(native_integer_constant, branch_native_block);
        }
    }

    return {};
}

Execution& NativeBuilder::exec()
{
    return native_build_;
}

void NativeBuilder::visitFunctionDefinition(lang::Function const& function)
{
    if (function.getEntryBlock() == nullptr) return;

    native_build_.setCurrentFunction(&function);
    assert(native_build_.getCurrentFunction()->getSubprogram() != nullptr);

    llvm::BasicBlock* decl =
        llvm::BasicBlock::Create(native_build_.llvmContext(), "decl", native_build_.getCurrentFunction());

    native_build_.ir().SetInsertPoint(decl);
    function.registerEntityDeclarations(native_build_);

    llvm::BasicBlock* defs =
        llvm::BasicBlock::Create(native_build_.llvmContext(), "defs", native_build_.getCurrentFunction());

    native_build_.ir().CreateBr(defs);
    native_build_.ir().SetInsertPoint(defs);
    for (auto& parameter : function.parameters()) { parameter->argument().performInitialization(native_build_); }

    bb_map_                                      = {};
    std::vector<lang::BasicBlock const*> bb_list = {};

    {
        llvm::Function* current_function = native_build_.getCurrentFunction();

        std::vector<lang::BasicBlock const*> bb_queue = {function.getEntryBlock()};

        while (!bb_queue.empty())
        {
            lang::BasicBlock const* bb = bb_queue.back();
            bb_queue.pop_back();

            if (bb_map_.contains(bb)) continue;

            std::string const name = "b" + std::to_string(bb->id());

            bb_list.emplace_back(bb);
            bb_map_[bb] = llvm::BasicBlock::Create(native_build_.llvmContext(), name, current_function);

            for (lang::BasicBlock const* next : bb->getSuccessors()) { bb_queue.emplace_back(next); }
        }
    }

    {
        bool first = true;

        for (lang::BasicBlock const* bb : bb_list)
        {
            llvm::BasicBlock* llvm_bb = bb_map_[bb];

            if (first)
            {
                first = false;

                // Create the branch from 'defs' to the first block.
                native_build_.ir().CreateBr(llvm_bb);
            }

            native_build_.ir().SetInsertPoint(llvm_bb);

            visitTree(*bb);
        }
    }

    bb_map_.clear();

    native_build_.ir().SetCurrentDebugLocation(llvm::DebugLoc());
    native_build_.di().finalizeSubprogram(native_build_.getCurrentFunction()->getSubprogram());

    native_build_.setCurrentFunction(nullptr);
}

void NativeBuilder::branchToNextOrReturnVoid(lang::BasicBlock const* next)
{
    if (next != nullptr) native_build_.ir().CreateBr(bb_map_[next]);
    else native_build_.ir().CreateRetVoid();
}
