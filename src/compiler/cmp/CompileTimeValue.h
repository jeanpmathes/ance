#ifndef ANCE_SRC_COMPILER_CMP_COMPILETIMEVALUE_H_
#define ANCE_SRC_COMPILER_CMP_COMPILETIMEVALUE_H_

#include "compiler/cmp/CompileTimeBuild.h"
#include "lang/construct/Constant.h"
#include "lang/utility/ResolvingHandle.h"

/**
 * A value that is used for compile-time evaluation.
 * While being called a value, this is technically a constant.
 * The reason is that the distinction between values and constants is made in relation to the runtime.
 * As such, a value during compile-time is a constant at run-time.
 */
class CompileTimeValue : public lang::Constant
{
  public:
    explicit CompileTimeValue(lang::Type const& type);
    ~CompileTimeValue() override = default;

    /**
     * Embed the constant in an execution context.
     * @param exec The context to embed the constant in. Should not be a compile-time context - that would be redundant.
     * @return The embedded constant.
     */
    virtual Shared<lang::Constant> embed(Execution& exec) const = 0;

    /**
     * Get a clone of this value with a different type.
     * Caller must ensure that the new type is compatible with the old one (e.g. alias types).
     * @param type The new type.
     * @param new_context The context to use for the new value.
     * @return The new value.
     */
    virtual Shared<CompileTimeValue> withType(lang::Type const& type, lang::Context& new_context) const = 0;

    [[nodiscard]] virtual Optional<CompileTimeBuild::Address> getHandle() const;

    /**
     * Access a value using an index, either loading the value or creating a value where the index is replaced.
     * @param index The index to access.
     * @param ok Whether the access was successful, i.e. the index is valid.
     * @param op Null to load the value, or a pointer to store the value at the index.
     * @param exec The execution context.
     * @return If loading, the loaded value. If storing, the new value.
     */
    virtual Shared<CompileTimeValue> access(size_t index, Shared<CompileTimeValue>* op, bool* ok, Execution& exec);
};

namespace cmp
{
    /**
     * Fulfills the role that 'native' values have in the native execution.
     * They are a value that is not used directly, but by it's address.
     * This is used to allow more lazy evaluation, e.g. an array load does not return the value, but a handle to it.
     */
    class HandledValue : public CompileTimeValue
    {
      public:
        HandledValue(CompileTimeBuild::Address handle, lang::Type const& type, CompileTimeBuild& exec);
        Shared<lang::Constant>   embed(Execution& exec) const override;
        Shared<CompileTimeValue> withType(lang::Type const& type, lang::Context& new_context) const override;

        [[nodiscard]] Optional<CompileTimeBuild::Address> getHandle() const override;

      private:
        CompileTimeBuild&         exec_;
        CompileTimeBuild::Address handle_;
    };

    class AddressValue : public CompileTimeValue
    {
      public:
        AddressValue(CompileTimeBuild::Address address, lang::Type const& type, lang::Context& context);
        Shared<lang::Constant>   embed(Execution& exec) const override;
        Shared<CompileTimeValue> withType(lang::Type const& type, lang::Context& new_context) const override;

        [[nodiscard]] CompileTimeBuild::Address const& address() const;

      private:
        CompileTimeBuild::Address address_;
    };

    class ArrayValue : public CompileTimeValue
    {
      public:
        ArrayValue(lang::Type const&                       element_type,
                   std::vector<Shared<CompileTimeValue>>&& values,
                   lang::Context&                          context);
        Shared<lang::Constant>   embed(Execution& exec) const override;
        Shared<CompileTimeValue> withType(lang::Type const& type, lang::Context& new_context) const override;

      private:
        std::vector<Shared<CompileTimeValue>> values_;
    };

    class BooleanValue : public CompileTimeValue
    {
      public:
        BooleanValue(bool value, lang::Context& context);
        Shared<lang::Constant>   embed(Execution& exec) const override;
        Shared<CompileTimeValue> withType(lang::Type const& type, lang::Context& new_context) const override;

        [[nodiscard]] bool value() const;

      private:
        bool value_;
    };

    class CharValue : public CompileTimeValue
    {
      public:
        CharValue(char32_t value, lang::Context& context);
        Shared<lang::Constant>   embed(Execution& exec) const override;
        Shared<CompileTimeValue> withType(lang::Type const& type, lang::Context& new_context) const override;

      private:
        char32_t value_;
    };

    class IntegerValue : public CompileTimeValue
    {
      public:
        IntegerValue(llvm::APInt value, lang::Type const& type, lang::Context& context);
        Shared<lang::Constant>   embed(Execution& exec) const override;
        Shared<CompileTimeValue> withType(lang::Type const& type, lang::Context& new_context) const override;

        [[nodiscard]] llvm::APInt const& value() const;

      private:
        llvm::APInt value_;
    };

    class FloatingPointValue : public CompileTimeValue
    {
      public:
        FloatingPointValue(llvm::APFloat value, lang::Type const& type, lang::Context& context);
        Shared<lang::Constant>   embed(Execution& exec) const override;
        Shared<CompileTimeValue> withType(lang::Type const& type, lang::Context& new_context) const override;

        [[nodiscard]] llvm::APFloat const& value() const;

      private:
        llvm::APFloat value_;
    };

    class UnitValue : public CompileTimeValue
    {
      public:
        UnitValue(lang::Type const& type, lang::Context& context);
        Shared<lang::Constant>   embed(Execution& exec) const override;
        Shared<CompileTimeValue> withType(lang::Type const& type, lang::Context& new_context) const override;
    };

    class StructValue : public CompileTimeValue
    {
      public:
        StructValue(lang::Type const& type, std::vector<Shared<CompileTimeValue>>&& values, lang::Context& context);
        Shared<lang::Constant>   embed(Execution& exec) const override;
        Shared<CompileTimeValue> withType(lang::Type const& type, lang::Context& new_context) const override;

      private:
        std::vector<Shared<CompileTimeValue>> values_;
    };

    class VectorValue : public CompileTimeValue
    {
      public:
        VectorValue(lang::Type const&                       element_type,
                    std::vector<Shared<CompileTimeValue>>&& values,
                    lang::Context&                          context);
        Shared<lang::Constant>   embed(Execution& exec) const override;
        Shared<CompileTimeValue> withType(lang::Type const& type, lang::Context& new_context) const override;

        [[nodiscard]] Shared<CompileTimeValue> get(size_t index);
        [[nodiscard]] size_t                   size() const;

      private:
        std::vector<Shared<CompileTimeValue>> values_;
    };
}

#endif
