#include "Accessibility.h"

lang::Accessibility::Accessibility(lang::AccessModifier access_modifier, lang::SourceAccessibility source_accessibility)
    : access_modifier_(access_modifier)
    , source_accessibility_(source_accessibility)
{}

bool lang::Accessibility::isExported() const
{
    return access_modifier_ == AccessModifier::PUBLIC_ACCESS && source_accessibility_ == SourceAccessibility::LOCAL;
}

bool lang::Accessibility::isImported() const
{
    return source_accessibility_ == SourceAccessibility::PUBLIC
        || source_accessibility_ == SourceAccessibility::PRIVATE;
}

bool lang::Accessibility::isExposable() const
{
    bool const is_local_public =
        access_modifier_ == AccessModifier::PUBLIC_ACCESS && source_accessibility_ == SourceAccessibility::LOCAL;
    bool const is_public_import =
        access_modifier_ == AccessModifier::PUBLIC_ACCESS && source_accessibility_ == SourceAccessibility::PUBLIC;
    bool const is_built_in = source_accessibility_ == SourceAccessibility::BUILT_IN;

    return is_local_public || is_public_import || is_built_in;
}

lang::AccessModifier lang::Accessibility::modifier() const
{
    return access_modifier_;
}

lang::SourceAccessibility lang::Accessibility::source() const
{
    return source_accessibility_;
}

lang::Accessibility lang::Accessibility::imported(bool is_public)
{
    return {AccessModifier::PUBLIC_ACCESS, is_public ? SourceAccessibility::PUBLIC : SourceAccessibility::PRIVATE};
}

lang::Accessibility lang::Accessibility::local(lang::AccessModifier access_modifier)
{
    return {access_modifier, SourceAccessibility::LOCAL};
}
