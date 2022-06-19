#ifndef ANCE_SRC_LANG_CONSTRUCT_MEMBER_H_
#define ANCE_SRC_LANG_CONSTRUCT_MEMBER_H_

#include "lang/AccessModifier.h"
#include "lang/type/Type.h"

namespace lang
{
    /**
     * A member of a class or struct.
     */
    class Member
    {
      public:
        /**
         * Creates a new member.
         * @param access The access modifier of the member.
         * @param name The name of the member.
         * @param type The type of the member.
         * @param location The location of the member.
         */
        Member(lang::AccessModifier              access,
               lang::Identifier                  name,
               lang::ResolvingHandle<lang::Type> type,
               lang::Location                    location);

        [[nodiscard]] lang::AccessModifier              access() const;
        [[nodiscard]] const lang::Identifier&           name() const;
        [[nodiscard]] lang::ResolvingHandle<lang::Type> type() const;
        [[nodiscard]] lang::Location                    location() const;

      private:
        lang::AccessModifier              access_;
        lang::Identifier                  name_;
        lang::ResolvingHandle<lang::Type> type_;
        lang::Location                    location_;
    };
}

#endif
