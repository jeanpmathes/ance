#ifndef ANCE_SRC_LANG_UTILITY_ERASED_H_
#define ANCE_SRC_LANG_UTILITY_ERASED_H_

#include <any>

#include "lang/utility/Optional.h"

/**
 * Dirty fix to allow passing value to any that has no non-const copy constructor.
 * @tparam Value The type of the value.
 */
template<Copyable Value>
struct Erased {
    alignas(Value) std::array<std::byte, sizeof(Value)> mutable data;

    explicit Erased(Value value) : data() { new (data.data()) Value(value); }
    Erased(Erased const& other) : data() { new (data.data()) Value(other.get()); }
    Erased(Erased&& other) noexcept : data() { new (data.data()) Value(other.get()); }
    Erased& operator=(Erased const& other)
    {
        get() = other.get();
        return *this;
    }
    Erased& operator=(Erased&& other) noexcept
    {
        get() = other.get();
        return *this;
    }

    Value& get() const { return *reinterpret_cast<Value*>(data.data()); }

    ~Erased() { std::destroy_at(std::launder(reinterpret_cast<Value*>(data.data()))); }
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-template"
template<Copyable Value>
static Value erasedCast(std::any any)
{
    Erased<Value> value = std::any_cast<Erased<Value>>(any);
    return value.get();
}

template<Copyable Value>
static Erased<Value> erase(Value value)
{
    Erased<Value> any(value);
    return any;
}
#pragma clang diagnostic pop

#endif
