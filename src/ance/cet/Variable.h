#ifndef ANCE_CET_VARIABLE_H
#define ANCE_CET_VARIABLE_H

#include "ance/core/Identifier.h"
#include "ance/core/Type.h"
#include "ance/core/Variable.h"

namespace ance::cet
{
    class Variable
    {
    public:
        Variable(core::Identifier const& identifier, core::Type const& type, bool is_final, core::Location const& location);

      [[nodiscard]] core::Identifier const& identifier() const;
        [[nodiscard]] core::Type const&       type() const;
      [[nodiscard]] core::Variable const&   variable() const;

      private:
        core::Identifier identifier_;
        core::Type const& type_;
        core::Variable variable_;
    };
}

#endif
