#ifndef ANCE_SRC_COMPILER_TARGETDESCRIPTOR_H_
#define ANCE_SRC_COMPILER_TARGETDESCRIPTOR_H_

#include <llvm/IR/DataLayout.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/TargetParser/Triple.h>

#include "lang/utility/Optional.h"

namespace llvm
{
    class TargetMachine;
}

/**
 * Describes a target machine for code generation.
 */
class TargetDescriptor
{
  public:
    enum SupportedOS
    {
        WINDOWS
    };

    /**
     * Get the target descriptor for the current system.
     * @return The target descriptor for the current system.
     */
    static TargetDescriptor system();

    /**
     * Get the targeted operating system.
     * @return The targeted operating system.
     */
    [[nodiscard]] SupportedOS getOS() const;

    /**
     * Whether the target OS is 64 bit.
     * @return True if the target OS is 64 bit, false if it is not.
     */
    [[nodiscard]] bool is64Bit() const;

    /**
     * Size of a pointer, in bytes.
     * @return The size of a pointer, in bytes.
     */
    [[nodiscard]] size_t getPointerSize() const;

    /**
     * Get the target as a string.
     * @return The target as a string.
     */
    [[nodiscard]] std::string toString() const;

    /**
     * Create the llvm target machine. Should only be called once.
     */
    void createTargetMachine(llvm::CodeGenOptLevel opt_level);

    /**
     * Configure an llvm module for this target.
     * @param module The module to configure.
     */
    void configureModule(llvm::Module& module) const;

    [[nodiscard]] llvm::Triple const& triple() const { return triple_; }

  private:
    llvm::Triple               triple_      = {};
    Optional<llvm::DataLayout> data_layout_ = std::nullopt;

    llvm::TargetMachine* target_machine_ = nullptr;
};

#endif
