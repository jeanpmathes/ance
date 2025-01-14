#ifndef ANCE_SRC_LANG_ACCESSIBILITY_H_
#define ANCE_SRC_LANG_ACCESSIBILITY_H_

#include "lang/AccessModifier.h"

namespace lang
{
    /**
     * Describes the accessibility of the source providing a defined name.
     */
    enum class SourceAccessibility
    {
        /**
         * The current package is the source.
         */
        LOCAL,

        /**
         * The source is a public dependency.
         */
        PUBLIC,

        /**
         * The source is a private dependency.
         */
        PRIVATE,

        /**
         * The source is the language itself, meaning the name is built in.
         */
        BUILT_IN
    };

    /**
     * Describes the accessibility of a defined name, e.g. a type.
     */
    class Accessibility
    {
      public:
        Accessibility(lang::AccessModifier access_modifier, lang::SourceAccessibility source_accessibility);

        /**
         * Whether the type should be exported.
         */
        [[nodiscard]] bool isExported() const;

        /**
         * Whether the type was imported.
         */
        [[nodiscard]] bool isImported() const;

        /**
         * Whether the type can be exposed as part of an export.
         */
        [[nodiscard]] bool isExposable() const;

        [[nodiscard]] lang::AccessModifier      modifier() const;
        [[nodiscard]] lang::SourceAccessibility source() const;

        /**
         * Create an accessibility description for an imported name.
         * @param is_public Whether the name was imported from a public dependency.
         * @return The accessibility description. The access modifier is always public.
         */
        static lang::Accessibility imported(bool is_public);

        /**
         * Create an accessibility description for a local name.
         * @param access_modifier The access modifier of the name.
         * @return The accessibility description. The source accessibility is always local.
         */
        static lang::Accessibility local(lang::AccessModifier access_modifier);

      private:
        lang::AccessModifier      access_modifier_;
        lang::SourceAccessibility source_accessibility_;
    };
}

#endif
