#ifndef ANCE_BBT_FUNCTION_H
#define ANCE_BBT_FUNCTION_H

#include <string>

#include "ance/utility/Owners.h"

#include "ance/core/Identifier.h"

#include "Node.h"
#include "Signature.h"
#include "Value.h"

namespace ance::bbt
{
    class Type;

    /// Represents a function.
    class Function final : public Value
    {
      public:
        Function(Signature signature, utility::Shared<Type> return_type, utility::Shared<Flow> body);
        Function(Signature signature, utility::Shared<Type> return_type, utility::Owned<Flow> body);
        ~Function() override = default;

        [[nodiscard]] core::Identifier const& name() const;
        [[nodiscard]] Signature        signature();
        [[nodiscard]] Signature const&        signature() const;
        [[nodiscard]] utility::Shared<Type>            returnType() ;
        [[nodiscard]] Type const&             returnType() const;

        [[nodiscard]] Flow const& body() const;

        [[nodiscard]] std::string            toString() const override;

      private:
        Signature             signature_;
        utility::Shared<Type> return_type_;
        utility::Shared<Flow> body_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Function const& function);

#endif
