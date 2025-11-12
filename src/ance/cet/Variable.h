#ifndef ANCE_CET_VARIABLE_H
#define ANCE_CET_VARIABLE_H

#include "ance/utility/Owners.h"

#include "ance/core/Identifier.h"
#include "ance/core/Type.h"

namespace ance::bbt
{
    class Value;
}

namespace ance::cet
{
    /// Represents a variable.
    class Variable
    {
      public:
        /// Creates a new variable.
        /// \param identifier The identifier of the variable.
        /// \param type The type of the variable.
        /// \param is_final Whether the variable is final or not.
        /// \param location The location where the variable was defined.
        Variable(core::Identifier const& identifier, core::Type const& type, bool is_final, core::Location const& location);

        [[nodiscard]] core::Identifier const& name() const;
        [[nodiscard]] core::Type const&       type() const;
        [[nodiscard]] bool                    isFinal() const;
        [[nodiscard]] core::Location const&   location() const;

        [[nodiscard]] bool isDefined() const;

        utility::Shared<bbt::Value> getValue();
        void setValue(utility::Shared<bbt::Value> value);

      private:
        core::Identifier  identifier_;
        core::Type const& type_;
        bool              is_final_;
        core::Location    location_;

        utility::Optional<utility::Shared<bbt::Value>> value_;
    };
}

#endif
