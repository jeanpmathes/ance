#include "TargetDescriptor.h"

#include <llvm/MC/TargetRegistry.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/TargetParser/Host.h>

TargetDescriptor TargetDescriptor::system()
{
    TargetDescriptor descriptor;

    descriptor.triple_ = llvm::Triple(llvm::sys::getDefaultTargetTriple());

    return descriptor;
}

TargetDescriptor::SupportedOS TargetDescriptor::getOS() const
{
    switch (triple_.getOS())
    {
        case llvm::Triple::Win32:
            return WINDOWS;
        default:
            throw std::logic_error("Not supported");
    }
}

bool TargetDescriptor::is64Bit() const
{
    return triple_.isArch64Bit();
}

size_t TargetDescriptor::getPointerSize() const
{
    assert(data_layout_.hasValue());

    return data_layout_.value().getPointerSizeInBits() / 8;
}

std::string TargetDescriptor::toString() const
{
    return triple_.getTriple();
}

void TargetDescriptor::createTargetMachine(llvm::CodeGenOptLevel opt_level)
{
    assert(target_machine_ == nullptr);

    std::string         error;
    llvm::Target const* target = llvm::TargetRegistry::lookupTarget(triple_.str(), error);

    Optional<llvm::Reloc::Model> relocation_model;
    relocation_model = llvm::Reloc::Static;

    Optional<llvm::CodeModel::Model> code_model;
    code_model = llvm::CodeModel::Large;

    llvm::TargetOptions const target_options;

    target_machine_ = target->createTargetMachine(triple_.str(),
                                                  "generic",
                                                  "",
                                                  target_options,
                                                  relocation_model,
                                                  code_model,
                                                  opt_level);

    data_layout_ = target_machine_->createDataLayout();
}

void TargetDescriptor::configureModule(llvm::Module& module) const
{
    assert(target_machine_ != nullptr);
    assert(data_layout_.hasValue());

    module.setDataLayout(data_layout_.value());
    module.setTargetTriple(triple_.str());
}
