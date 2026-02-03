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
                /// This intrinsic does not take any parameters and returns the unit type.

                signature   = Signature::make(intrinsic.identifier());
                return_type = type_context.getUnit();

                break;
            }
            case core::Intrinsic::DECLARE:
            {
                /// This intrinsic takes the following parameters:
                /// - The scope to declare the variable in.
                /// - The identifier of the variable to declare.
                /// - Whether the declaration is final.
                /// - The type of the variable to declare.
                /// It returns a reference to the declared variable.

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
                /// This intrinsic takes the following parameters:
                /// - The scope to resolve the variable in.
                /// - The identifier of the variable to resolve.
                /// It returns a reference to the resolved variable.

                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getScopeRef(), type_context.getIdentifier());
                return_type = type_context.getVariableRef();

                break;
            }
            case core::Intrinsic::GET_PARENT:
            {
                /// This intrinsic takes the following parameters:
                /// - The scope to get the parent of.
                /// It returns the parent scope.

                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getScopeRef());
                return_type = type_context.getScopeRef();

                break;
            }
            case core::Intrinsic::LOG:
            {
                /// This intrinsic takes the following parameters:
                /// - The string message to log.
                /// - The location to log the message at.
                /// It returns the unit type.

                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getString(), type_context.getLocation());
                return_type = type_context.getUnit();

                break;
            }
            case core::Intrinsic::B_2_STR:
            {
                /// This intrinsic takes the following parameters:
                /// - The boolean to convert.
                /// It returns the string representation of the boolean.

                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getBool());
                return_type = type_context.getString();

                break;
            }
            case core::Intrinsic::INCLUDE:
            {
                /// This intrinsic takes the following parameters:
                /// - The path of the file to include.
                /// - The location of a file to use as base to resolve a relative path.
                /// It returns the unit type.

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
