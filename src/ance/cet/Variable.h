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
        /// \param is_variable Whether the variable is variable (the value can be changed).
        /// \param location The location where the variable was defined.
        /// \param type_context The type context.
        Variable(core::Identifier const&    identifier,
                 utility::Shared<bbt::Type const> type,
                 bool                       is_variable,
                 core::Location const&      location,
                 bbt::TypeContext&          type_context);

        ~Variable() override = default;

        [[nodiscard]] core::Identifier const&    name() const;
        [[nodiscard]] utility::Shared<bbt::Type const> type() const override;
        [[nodiscard]] bool                       isVariable() const;
        [[nodiscard]] bool                       isConstant() const;
        [[nodiscard]] core::Location const&      location() const;

        [[nodiscard]] utility::Shared<bbt::Value const> access() override;

        utility::Shared<bbt::Value const> read(std::span<size_t const> indices) override;
        void                              write(utility::Shared<bbt::Value const> value, std::span<size_t const> indices) override;

        utility::Shared<bbt::Value const> read();
        void                              write(utility::Shared<bbt::Value const> value);

        [[nodiscard]] bool isDefined() const override;

      private:
        core::Identifier           identifier_;
        utility::Shared<bbt::Type const> type_;
        bool                       is_variable_;
        core::Location             location_;

        bbt::TypeContext& type_context_;

        utility::Optional<utility::Shared<bbt::Value const>> value_;
    };
}

#endif
