#include "IntrinsicSignature.h"

#include "ance/utility/Optional.h"

#include "ance/bbt/Type.h"

namespace ance::bbt
{
    std::tuple<Signature, utility::Shared<Type>> getIntrinsicSignature(core::Intrinsic intrinsic, TypeContext& type_context)
    {
        utility::Optional<Signature>             signature;
        utility::Optional<utility::Shared<Type>> return_type;

        switch (intrinsic.value())
        {
            case core::Intrinsic::NO_OPERATION:
            {
                signature   = Signature::make(intrinsic.identifier());
                return_type = type_context.getUnit();

                break;
            }
            case core::Intrinsic::DECLARE:
            {
                signature   = Signature::makeAndNameParameters(intrinsic.identifier(),
                                                             type_context.getScopeRef(),
                                                             type_context.getIdentifier(),
                                                             type_context.getBool(),
                                                             type_context.getType());
                return_type = type_context.getVariableRef();

                break;
            }
            case core::Intrinsic::RESOLVE:
            {
                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getScopeRef(), type_context.getIdentifier());
                return_type = type_context.getVariableRef();

                break;
            }
            case core::Intrinsic::GET_PARENT:
            {
                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getScopeRef());
                return_type = type_context.getScopeRef();

                break;
            }
            case core::Intrinsic::LOG:
            {
                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getString(), type_context.getLocation());
                return_type = type_context.getUnit();

                break;
            }
            case core::Intrinsic::B_2_STR:
            {
                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getBool());
                return_type = type_context.getString();

                break;
            }
            case core::Intrinsic::INCLUDE:
            {
                signature   = Signature::makeAndNameParameters(intrinsic.identifier(),
                                                             type_context.getString(),// todo: path type
                                                             type_context.getLocation());
                return_type = type_context.getUnit();

                break;
            }
        }

        assert(signature.hasValue());
        assert(return_type.hasValue());

        return {signature.value(), return_type.value()};
    }
}
