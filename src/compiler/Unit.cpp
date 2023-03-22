#include "Unit.h"

#include <fstream>

#include "compiler/CodePrinter.h"
#include "compiler/Packages.h"
#include "lang/type/SizeType.h"
#include "lang/type/UnsignedIntegerPointerType.h"
#include "validation/ValidationLogger.h"

Unit::Unit(Owned<lang::GlobalScope> global_scope) : global_scope_(std::move(global_scope))
{
    addChild(*global_scope_);
}

Unit::Unit(bool is_containing_runtime) : Unit(makeOwned<lang::GlobalScope>(is_containing_runtime))
{
}

void Unit::setTargetInfo(llvm::Triple const& triple, llvm::DataLayout const& data_layout)
{
    pointer_size_  = data_layout.getPointerSize();
    target_triple_ = triple;

    lang::SizeType::init(*this);
    lang::UnsignedIntegerPointerType::init(data_layout);
}

unsigned Unit::getBitness() const
{
    return pointer_size_ * 8;
}

llvm::Triple const& Unit::getTargetTriple() const
{
    return target_triple_;
}

bool Unit::preparePackageDependencies(Packages const& packages)
{
    auto dependencies = getDependencies();
    bool valid        = true;

    for (auto const& dependency : dependencies)
    {
        auto package = packages.getPackage(dependency);
        if (!package.hasValue())
        {
            std::cout << "ance: packages: Could not find package '" << dependency << "'" << std::endl;
            valid = false;
        }
    }

    return valid;
}

void Unit::preValidate()
{
    global_scope_->resolve();
    global_scope_->postResolve();
}

void Unit::preBuild()
{
    clearChildren();
    global_scope_ = global_scope_->expand();
    addChild(*global_scope_);

    global_scope_->resolve();
    global_scope_->postResolve();
    global_scope_->determineFlow();
}

void Unit::emitAsSource(std::filesystem::path const& out)
{
    std::ofstream of;
    of.open(out);

    std::ostream o(of.rdbuf());

    CodePrinter printer(o);

    Unit const& self = *this;
    printer.visit(self);
}

void Unit::validateFlow(ValidationLogger& validation_logger)
{
    global_scope_->validateFlow(validation_logger);
}

lang::GlobalScope& Unit::globalScope()
{
    return *global_scope_;
}

lang::GlobalScope const& Unit::globalScope() const
{
    return *global_scope_;
}

std::vector<std::string> Unit::getExportedFunctions() const
{
    return global_scope_->getExportFunctions();
}
