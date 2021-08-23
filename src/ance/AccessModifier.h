#ifndef ANCE_SRC_ANCE_ACCESSMODIFIER_H_
#define ANCE_SRC_ANCE_ACCESSMODIFIER_H_

#include <llvm/IR/GlobalValue.h>

/**
 * Represents different access levels of named values.
 */
class AccessModifier
{
  public:
    enum Value
    {
        PUBLIC_ACCESS,
        PRIVATE_ACCESS
    };

    AccessModifier() = default;
    constexpr AccessModifier(Value val) : value_(val) {}// NOLINT(google-explicit-constructor)

             operator Value() const;// NOLINT(google-explicit-constructor)
    explicit operator bool() = delete;

    /**
     * Get the corresponding native linkage type.
     * @return The linkage type.
     */
    llvm::GlobalValue::LinkageTypes linkage();

  private:
    Value value_;
};

#endif