#include "CompileContext.h"

#include "lang/scope/Scope.h"

CompileContext::CompileContext(Application*         app,
                               Runtime*             runtime,
                               llvm::LLVMContext*   c,
                               llvm::Module*        m,
                               llvm::IRBuilder<>*   ir,
                               llvm::DIBuilder*     di,
                               llvm::DICompileUnit* unit,
                               llvm::DIFile*        src_file)
    : application_(app)
    , runtime_(runtime)
    , context_(c)
    , module_(m)
    , ir_builder_(ir)
    , di_builder_(di)
    , unit_(unit)
    , src_file_(src_file)
{}

Application* CompileContext::application()
{
    return application_;
}

Runtime* CompileContext::runtime()
{
    return runtime_;
}

llvm::LLVMContext* CompileContext::llvmContext()
{
    return context_;
}

llvm::Module* CompileContext::module()
{
    return module_;
}

llvm::IRBuilder<>* CompileContext::ir()
{
    return ir_builder_;
}

llvm::DIBuilder* CompileContext::di()
{
    return di_builder_;
}

llvm::DICompileUnit* CompileContext::unit()
{
    return unit_;
}

llvm::DIFile* CompileContext::sourceFile()
{
    return src_file_;
}

void CompileContext::setDebugLocation(lang::Location location, lang::Scope* scope)
{
    llvm::DebugLoc previous_location = ir()->getCurrentDebugLocation();
    ir()->SetCurrentDebugLocation(location.getDebugLoc(llvmContext(), scope->getDebugScope(*this)));

    debug_loc_stack_.push(previous_location);
}

void CompileContext::resetDebugLocation()
{
    llvm::DebugLoc previous_location = debug_loc_stack_.top();
    ir()->SetCurrentDebugLocation(previous_location);

    debug_loc_stack_.pop();
}

bool CompileContext::allDebugLocationsPopped()
{
    return debug_loc_stack_.empty();
}
