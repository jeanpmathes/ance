#ifndef ANCE_CORE_FUNCTION_H
#define ANCE_CORE_FUNCTION_H

#include <ostream>
#include <functional>

#include "ance/utility/Containers.h"
#include "ance/utility/Owners.h"

#include "ance/core/Identifier.h"
#include "ance/core/Signature.h"
#include "ance/core/Value.h"

namespace ance::core
{
    class Type;

    /// Represents a function.
    class Function // todo: should be merge with value at some point, call becomes just a special operator
    {
      public:
        Function(Signature const& signature, Type const& return_type, std::function<void(utility::List<utility::Shared<Value>> const&)> function);
        ~Function() = default;

        void run(utility::List<utility::Shared<Value>> const& arguments) const; // todo: remove this - should contain correct bbt tree or something and use intrinsics for special stuff internally - should no longer be in core if it references bbt

        [[nodiscard]] Identifier const& name() const;
        [[nodiscard]] Signature const& signature() const;
        [[nodiscard]] Type const& returnType() const;

      private:
        Signature signature_;
        Type const& return_type_;
        std::function<void(utility::List<utility::Shared<Value>> const&)> function_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::core::Function const& function);

#endif
