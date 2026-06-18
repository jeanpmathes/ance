#include "Intrinsic.h"

#include <algorithm>
#include <ranges>
#include <utility>

ance::core::Intrinsic::Value ance::core::Intrinsic::value() const
{
    return value_;
}

ance::core::Identifier ance::core::Intrinsic::identifier() const
{
    return Identifier::make(toString(), Location::nowhere());
}

// todo: a bit ugly that these are essentially type prefix + operator shorthand and not defined based on their values, causing duplication
// todo: ideally the operators would be used directly to access the letters, and there would be a global constant file with the type prefix that is used by the types as well

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
    {ance::core::Intrinsic::SIZE_LT, "s_lt"},          {ance::core::Intrinsic::SIZE_LE, "s_le"},
    {ance::core::Intrinsic::SIZE_GT, "s_gt"},          {ance::core::Intrinsic::SIZE_GE, "s_ge"},
    {ance::core::Intrinsic::SIZE_EQ, "s_eq"},          {ance::core::Intrinsic::SIZE_NE, "s_ne"},
    {ance::core::Intrinsic::HALF_ADD, "fh_add"},       {ance::core::Intrinsic::HALF_SUB, "fh_sub"},
    {ance::core::Intrinsic::HALF_MUL, "fh_mul"},       {ance::core::Intrinsic::HALF_DIV, "fh_div"},
    {ance::core::Intrinsic::HALF_REM, "fh_rem"},       {ance::core::Intrinsic::HALF_NEG, "fh_neg"},
    {ance::core::Intrinsic::HALF_LT, "fh_lt"},         {ance::core::Intrinsic::HALF_LE, "fh_le"},
    {ance::core::Intrinsic::HALF_GT, "fh_gt"},         {ance::core::Intrinsic::HALF_GE, "fh_ge"},
    {ance::core::Intrinsic::HALF_EQ, "fh_eq"},         {ance::core::Intrinsic::HALF_NE, "fh_ne"},
    {ance::core::Intrinsic::SINGLE_ADD, "fs_add"},     {ance::core::Intrinsic::SINGLE_SUB, "fs_sub"},
    {ance::core::Intrinsic::SINGLE_MUL, "fs_mul"},     {ance::core::Intrinsic::SINGLE_DIV, "fs_div"},
    {ance::core::Intrinsic::SINGLE_REM, "fs_rem"},     {ance::core::Intrinsic::SINGLE_NEG, "fs_neg"},
    {ance::core::Intrinsic::SINGLE_LT, "fs_lt"},       {ance::core::Intrinsic::SINGLE_LE, "fs_le"},
    {ance::core::Intrinsic::SINGLE_GT, "fs_gt"},       {ance::core::Intrinsic::SINGLE_GE, "fs_ge"},
    {ance::core::Intrinsic::SINGLE_EQ, "fs_eq"},       {ance::core::Intrinsic::SINGLE_NE, "fs_ne"},
    {ance::core::Intrinsic::DOUBLE_ADD, "fd_add"},     {ance::core::Intrinsic::DOUBLE_SUB, "fd_sub"},
    {ance::core::Intrinsic::DOUBLE_MUL, "fd_mul"},     {ance::core::Intrinsic::DOUBLE_DIV, "fd_div"},
    {ance::core::Intrinsic::DOUBLE_REM, "fd_rem"},     {ance::core::Intrinsic::DOUBLE_NEG, "fd_neg"},
    {ance::core::Intrinsic::DOUBLE_LT, "fd_lt"},       {ance::core::Intrinsic::DOUBLE_LE, "fd_le"},
    {ance::core::Intrinsic::DOUBLE_GT, "fd_gt"},       {ance::core::Intrinsic::DOUBLE_GE, "fd_ge"},
    {ance::core::Intrinsic::DOUBLE_EQ, "fd_eq"},       {ance::core::Intrinsic::DOUBLE_NE, "fd_ne"},
    {ance::core::Intrinsic::QUAD_ADD, "fq_add"},       {ance::core::Intrinsic::QUAD_SUB, "fq_sub"},
    {ance::core::Intrinsic::QUAD_MUL, "fq_mul"},       {ance::core::Intrinsic::QUAD_DIV, "fq_div"},
    {ance::core::Intrinsic::QUAD_REM, "fq_rem"},       {ance::core::Intrinsic::QUAD_NEG, "fq_neg"},
    {ance::core::Intrinsic::QUAD_LT, "fq_lt"},         {ance::core::Intrinsic::QUAD_LE, "fq_le"},
    {ance::core::Intrinsic::QUAD_GT, "fq_gt"},         {ance::core::Intrinsic::QUAD_GE, "fq_ge"},
    {ance::core::Intrinsic::QUAD_EQ, "fq_eq"},         {ance::core::Intrinsic::QUAD_NE, "fq_ne"},
    {ance::core::Intrinsic::BOOL_EQ, "b_eq"},          {ance::core::Intrinsic::BOOL_NE, "b_ne"},
    {ance::core::Intrinsic::UNIT_EQ, "u_eq"},          {ance::core::Intrinsic::UNIT_NE, "u_ne"},
    {ance::core::Intrinsic::STRING_EQ, "str_eq"},      {ance::core::Intrinsic::STRING_NE, "str_ne"},
    {ance::core::Intrinsic::IDENTIFIER_EQ, "id_eq"},   {ance::core::Intrinsic::IDENTIFIER_NE, "id_ne"},
    {ance::core::Intrinsic::LOCATION_EQ, "loc_eq"},    {ance::core::Intrinsic::LOCATION_NE, "loc_ne"},
};

std::string ance::core::Intrinsic::toString() const
{
    auto const intrinsic = std::ranges::find_if(intrinsics, [this](auto const& entry) { return entry.first == value_; });
    if (intrinsic != std::ranges::end(intrinsics)) return intrinsic->second;

    return "";
}

std::optional<ance::core::Intrinsic> ance::core::Intrinsic::fromString(std::string const& name)
{
    auto const intrinsic = std::ranges::find_if(intrinsics, [&name](auto const& entry) { return name == entry.second; });
    if (intrinsic != std::ranges::end(intrinsics)) return Intrinsic(intrinsic->first);

    return std::nullopt;
}
