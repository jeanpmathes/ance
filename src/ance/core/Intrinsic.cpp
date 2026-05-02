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
    {ance::core::Intrinsic::NO_OPERATION, "nop"},      {ance::core::Intrinsic::DECLARE, "declare"},
    {ance::core::Intrinsic::RESOLVE, "resolve"},       {ance::core::Intrinsic::ERASE, "erase"},
    {ance::core::Intrinsic::GET_PARENT, "get_parent"}, {ance::core::Intrinsic::B_2_STR, "b_2_str"},
    {ance::core::Intrinsic::FH_2_STR, "fh_2_str"},     {ance::core::Intrinsic::FS_2_STR, "fs_2_str"},
    {ance::core::Intrinsic::FD_2_STR, "fd_2_str"},     {ance::core::Intrinsic::FQ_2_STR, "fq_2_str"},
    {ance::core::Intrinsic::BOOL_NOT, "b_not"},        {ance::core::Intrinsic::LOG, "log"},
    {ance::core::Intrinsic::INCLUDE, "include"},       {ance::core::Intrinsic::CALL_INTRINSIC, "call_intrinsic"},
    {ance::core::Intrinsic::SIZE_ADD, "s_add"},        {ance::core::Intrinsic::SIZE_SUB, "s_sub"},
    {ance::core::Intrinsic::SIZE_MUL, "s_mul"},        {ance::core::Intrinsic::SIZE_DIV, "s_div"},
    {ance::core::Intrinsic::SIZE_REM, "s_rem"},        {ance::core::Intrinsic::SIZE_BITNOT, "s_bitnot"},
    {ance::core::Intrinsic::HALF_ADD, "fh_add"},       {ance::core::Intrinsic::HALF_SUB, "fh_sub"},
    {ance::core::Intrinsic::HALF_MUL, "fh_mul"},       {ance::core::Intrinsic::HALF_DIV, "fh_div"},
    {ance::core::Intrinsic::HALF_REM, "fh_rem"},       {ance::core::Intrinsic::HALF_NEG, "fh_neg"},
    {ance::core::Intrinsic::SINGLE_ADD, "fs_add"},     {ance::core::Intrinsic::SINGLE_SUB, "fs_sub"},
    {ance::core::Intrinsic::SINGLE_MUL, "fs_mul"},     {ance::core::Intrinsic::SINGLE_DIV, "fs_div"},
    {ance::core::Intrinsic::SINGLE_REM, "fs_rem"},     {ance::core::Intrinsic::SINGLE_NEG, "fs_neg"},
    {ance::core::Intrinsic::DOUBLE_ADD, "fd_add"},     {ance::core::Intrinsic::DOUBLE_SUB, "fd_sub"},
    {ance::core::Intrinsic::DOUBLE_MUL, "fd_mul"},     {ance::core::Intrinsic::DOUBLE_DIV, "fd_div"},
    {ance::core::Intrinsic::DOUBLE_REM, "fd_rem"},     {ance::core::Intrinsic::DOUBLE_NEG, "fd_neg"},
    {ance::core::Intrinsic::QUAD_ADD, "fq_add"},       {ance::core::Intrinsic::QUAD_SUB, "fq_sub"},
    {ance::core::Intrinsic::QUAD_MUL, "fq_mul"},       {ance::core::Intrinsic::QUAD_DIV, "fq_div"},
    {ance::core::Intrinsic::QUAD_REM, "fq_rem"},       {ance::core::Intrinsic::QUAD_NEG, "fq_neg"},
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
