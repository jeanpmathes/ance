#include "Address.h"

#include <utility>

namespace ance::cet
{
    Address::Address(Memory& memory, std::vector<size_t> indices)
        : memory_(memory), indices_(std::move(indices))
    {}

    Memory& Address::memory() const
    {
        return memory_.get();
    }

    std::span<size_t const> Address::indices() const
    {
        return indices_;
    }

    Address Address::subscript(size_t const index) const
    {
        std::vector<size_t> indices_copy = indices_;

        indices_copy.emplace_back(index);

        return Address(memory_.get(), std::move(indices_copy));
    }

    utility::Shared<bbt::Value> Address::read() const
    {
        return memory_.get().read(indices_);
    }

    void Address::write(utility::Shared<bbt::Value> value) const
    {
        memory_.get().write(std::move(value), indices_);
    }

    bool Address::isDefined() const
    {
        return memory_.get().isDefined();
    }
}
