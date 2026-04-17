#include "Intrinsic.h"

#include <algorithm>
#include <utility>

ance::core::Intrinsic::Value ance::core::Intrinsic::value() const
{
    return value_;
}

ance::core::Identifier ance::core::Intrinsic::identifier() const
{
    return Identifier::make(toString(), Location::nowhere());
}

static std::pair<ance::core::Intrinsic::Value, char const*> const intrinsics[] = {
    {ance::core::Intrinsic::NO_OPERATION, "nop"},
    {ance::core::Intrinsic::DECLARE, "declare"},
    {ance::core::Intrinsic::RESOLVE, "resolve"},
    {ance::core::Intrinsic::ERASE, "erase"},
    {ance::core::Intrinsic::GET_PARENT, "get_parent"},
    {ance::core::Intrinsic::B_2_STR, "b_2_str"},
    {ance::core::Intrinsic::FH_2_STR, "fh_2_str"},
    {ance::core::Intrinsic::FS_2_STR, "fs_2_str"},
    {ance::core::Intrinsic::FD_2_STR, "fd_2_str"},
    {ance::core::Intrinsic::FQ_2_STR, "fq_2_str"},
    {ance::core::Intrinsic::LOG, "log"},
    {ance::core::Intrinsic::INCLUDE, "include"},
    {ance::core::Intrinsic::CALL_INTRINSIC, "call_intrinsic"},
    {ance::core::Intrinsic::SIZE_ADD, "size_add"},
    {ance::core::Intrinsic::SIZE_SUB, "size_sub"},
    {ance::core::Intrinsic::SIZE_MUL, "size_mul"},
    {ance::core::Intrinsic::SIZE_DIV, "size_div"},
    {ance::core::Intrinsic::HALF_ADD, "half_add"},
    {ance::core::Intrinsic::HALF_SUB, "half_sub"},
    {ance::core::Intrinsic::HALF_MUL, "half_mul"},
    {ance::core::Intrinsic::HALF_DIV, "half_div"},
    {ance::core::Intrinsic::SINGLE_ADD, "single_add"},
    {ance::core::Intrinsic::SINGLE_SUB, "single_sub"},
    {ance::core::Intrinsic::SINGLE_MUL, "single_mul"},
    {ance::core::Intrinsic::SINGLE_DIV, "single_div"},
    {ance::core::Intrinsic::DOUBLE_ADD, "double_add"},
    {ance::core::Intrinsic::DOUBLE_SUB, "double_sub"},
    {ance::core::Intrinsic::DOUBLE_MUL, "double_mul"},
    {ance::core::Intrinsic::DOUBLE_DIV, "double_div"},
    {ance::core::Intrinsic::QUAD_ADD, "quad_add"},
    {ance::core::Intrinsic::QUAD_SUB, "quad_sub"},
    {ance::core::Intrinsic::QUAD_MUL, "quad_mul"},
    {ance::core::Intrinsic::QUAD_DIV, "quad_div"},
};

std::string ance::core::Intrinsic::toString() const
{
    for (auto const& [value, name] : intrinsics)
    {
        if (value == value_) return name;
    }

    return "";
}

std::optional<ance::core::Intrinsic> ance::core::Intrinsic::fromString(std::string const& name)
{
    for (auto const& [value, intrinsic_name] : intrinsics)
    {
        if (name == intrinsic_name) return Intrinsic(value);
    }

    return std::nullopt;
}
