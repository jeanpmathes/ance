#ifndef ANCE_BBT_INTRINSICSIGNATURE_H
#define ANCE_BBT_INTRINSICSIGNATURE_H

#include <tuple>

#include "ance/core/Intrinsic.h"

#include "ance/bbt/Signature.h"

namespace ance::bbt
{
    class TypeContext;

    /// Provides the signatures of the intrinsics.
    class IntrinsicSignature
    {
      public:
        static std::tuple<Signature, utility::Shared<Type>> get(core::Intrinsic const& intrinsic, TypeContext& type_context);
    };
}

#endif
