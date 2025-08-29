#ifndef ANCE_CORE_FUNCTION_H
#define ANCE_CORE_FUNCTION_H

#include <functional>

#include "ance/utility/Containers.h"
#include "ance/utility/Owners.h"

#include "ance/core/Identifier.h"
#include "ance/core/Signature.h"
#include "ance/core/Value.h"
#include "ance/core/Entity.h"

namespace ance::core
{
    class Type;

    /// Represents a function.
    class Function final : public Entity // todo: should be merge with value (NOT variable like it is now) at some point, call becomes just a special operator
    {
      public:
        Function(Signature signature, Type const& return_type, std::function<void(utility::List<utility::Shared<Value>> const&)> function);
        ~Function() override = default;

        void run(utility::List<utility::Shared<Value>> const& arguments) const; // todo: remove this - should contain correct bbt tree or something and use intrinsics for special stuff internally - should no longer be in core if it references bbt

        [[nodiscard]] Identifier const& name() const override;
        [[nodiscard]] Signature const& signature() const;
        [[nodiscard]] Type const&       returnType() const;

        Function* asFunction() override;
        [[nodiscard]] Function const* asFunction() const override;

      private:
        Signature signature_;
        Type const& return_type_;
        std::function<void(utility::List<utility::Shared<Value>> const&)> function_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::core::Function const& function);

#endif
