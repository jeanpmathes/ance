#ifndef ANCE_CORE_FUNCTION_H
#define ANCE_CORE_FUNCTION_H

#include <ostream>
#include <functional>

#include "ance/core/Identifier.h"

namespace ance::core
{
    /// Represents a function.
    class Function // todo: should be merge with value at some point, call becomes just a special operator
    {
      public:
        Function(Identifier const& name, std::function<void()> function);
        ~Function() = default;

        void run() const; // todo: remove this - should contain correct bbt tree or something and use intrinsics for special stuff internally

        [[nodiscard]] Identifier const& name() const;

      private:
        Identifier name_;
        std::function<void()> function_;
    };
}

std::ostream& operator<<(std::ostream& out, ance::core::Function const& function);

#endif
