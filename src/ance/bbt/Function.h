#ifndef ANCE_BBT_FUNCTION_H
#define ANCE_BBT_FUNCTION_H

#include <string>

#include "ance/utility/Owners.h"

#include "ance/core/Identifier.h"

#include "ance/bbt/Node.h"

#include "Signature.h"
#include "Value.h"

namespace ance::bbt
{
    class Type;
    class TypeContext;

    /// Represents a function.
    class Function final : public ValueBase<Function>
    {
      public:
        Function(Signature signature, utility::Shared<Type const> return_type, Flow const& body, TypeContext& type_context);
        Function(Signature signature, utility::Shared<Type const> return_type, utility::Shared<Flow> body, TypeContext& type_context);
        Function(Signature signature, utility::Shared<Type const> return_type, utility::Owned<Flow> body, TypeContext& type_context);
        ~Function() override = default;

        [[nodiscard]] core::Identifier const&     name() const;
        [[nodiscard]] Signature                   signature();
        [[nodiscard]] Signature const&            signature() const;
        [[nodiscard]] utility::Shared<Type const> returnType() const;

        [[nodiscard]] Flow const& body() const;

        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] bool        equals(Function const& other) const override;

      private:
        Signature                   signature_;
        utility::Shared<Type const> return_type_;

        Flow const&                              body_;
        utility::Optional<utility::Shared<Flow>> owned_body_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Function const& function);

#endif
