#ifndef ANCE_BBT_FUNCTION_H
#define ANCE_BBT_FUNCTION_H

#include "ance/utility/Owners.h"

#include "ance/core/Identifier.h"
#include "ance/core/Signature.h"
#include "ance/core/Entity.h"

#include "Node.h"

namespace ance::core
{
    class Type;
}

namespace ance::bbt
{
    /// Represents a function.
    class Function final : public core::Entity // todo: should be merge with value (NOT variable like it is now) at some point, call becomes just a special operator
    {
      public:
        Function(core::Signature signature, core::Type const& return_type, utility::Owned<Flow> body);
        ~Function() override = default;

        [[nodiscard]] core::Identifier const& name() const override;
        [[nodiscard]] core::Signature const& signature() const;
        [[nodiscard]] core::Type const& returnType() const;

        [[nodiscard]] Flow const& body() const;

        void* asFunction() override;
        [[nodiscard]] void const* asFunction() const override;

      private:
        core::Signature signature_;
        core::Type const& return_type_;
        utility::Owned<Flow> body_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Function const& function);

#endif
