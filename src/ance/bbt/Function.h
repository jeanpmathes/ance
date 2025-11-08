#ifndef ANCE_BBT_FUNCTION_H
#define ANCE_BBT_FUNCTION_H

#include <string>

#include "ance/utility/Owners.h"

#include "ance/core/Identifier.h"
#include "ance/core/Signature.h"

#include "Node.h"
#include "Value.h"

namespace ance::core
{
    class Type;
}

namespace ance::bbt
{
    /// Represents a function.
    class Function final : public Value
    {
      public:
        Function(core::Signature signature, core::Type const& return_type, utility::Shared<Flow> body);
        Function(core::Signature signature, core::Type const& return_type, utility::Owned<Flow> body);
        ~Function() override = default;

        [[nodiscard]] core::Identifier const& name() const;
        [[nodiscard]] core::Signature const& signature() const;
        [[nodiscard]] core::Type const& returnType() const;

        [[nodiscard]] Flow const& body() const;

        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

      private:
        core::Signature signature_;
        core::Type const& return_type_;
        utility::Shared<Flow> body_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Function const& function);

#endif
