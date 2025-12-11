#ifndef ANCE_CET_VARIABLE_H
#define ANCE_CET_VARIABLE_H

#include "ance/utility/Owners.h"

#include "ance/bbt/Type.h"
#include "ance/core/Identifier.h"

#include "ance/cet/Memory.h"

namespace ance::bbt
{
    class Value;
}

namespace ance::cet
{
    /// Represents a variable.
    class Variable : public Memory
    {
      public:
        /// Creates a new variable.
        /// \param identifier The identifier of the variable.
        /// \param type The type of the variable.
        /// \param is_final Whether the variable is final or not.
        /// \param location The location where the variable was defined.
        Variable(core::Identifier const&    identifier,
                 utility::Shared<bbt::Type> type,
                 bool                       is_final,
                 core::Location const&      location,
                 bbt::TypeContext&          type_context);

        [[nodiscard]] core::Identifier const&    name() const;
        [[nodiscard]] utility::Shared<bbt::Type> type();
        [[nodiscard]] bbt::Type const&           type() const;
        [[nodiscard]] bool                       isFinal() const;
        [[nodiscard]] core::Location const&      location() const;

        [[nodiscard]] utility::Shared<bbt::Value> access() override;

        utility::Shared<bbt::Value> read(std::vector<size_t> const& indices = {}) override;
        void                        write(utility::Shared<bbt::Value> value, std::vector<size_t> const& indices = {}) override;

        [[nodiscard]] bool isDefined() const override;

      private:
        core::Identifier           identifier_;
        utility::Shared<bbt::Type> type_;
        bool                       is_final_;
        core::Location             location_;

        bbt::TypeContext& type_context_;

        utility::Optional<utility::Shared<bbt::Value>> value_;
    };
}

#endif
