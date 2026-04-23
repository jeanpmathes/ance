#include "IntrinsicSignature.h"

#include "ance/utility/Optional.h"

#include "ance/bbt/Type.h"

namespace ance::bbt
{
    static std::tuple<Signature, utility::Shared<Type>> makeBinarySignature(core::Intrinsic const intrinsic, utility::Shared<Type> type)
    {
        Signature signature = Signature::makeAndNameParameters(intrinsic.identifier(), type, type);
        return {std::move(signature), type};
    }

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
            case core::Intrinsic::ERASE:
            {
                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getScopeRef(), type_context.getIdentifier());
                return_type = type_context.getUnit();

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
            case core::Intrinsic::FH_2_STR:
            {
                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getFloat(core::Precision::HALF));
                return_type = type_context.getString();

                break;
            }
            case core::Intrinsic::FS_2_STR:
            {
                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getFloat(core::Precision::SINGLE));
                return_type = type_context.getString();

                break;
            }
            case core::Intrinsic::FD_2_STR:
            {
                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getFloat(core::Precision::DOUBLE));
                return_type = type_context.getString();

                break;
            }
            case core::Intrinsic::FQ_2_STR:
            {
                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getFloat(core::Precision::QUAD));
                return_type = type_context.getString();

                break;
            }
            case core::Intrinsic::BOOL_NOT:
            {
                signature   = Signature::makeAndNameParameters(intrinsic.identifier(), type_context.getBool());
                return_type = type_context.getBool();

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
            case core::Intrinsic::CALL_INTRINSIC:
            {
                // todo: remove variadic parameters, instead take a string and a list of arguments
                utility::List<Signature::Parameter> parameters;
                parameters.emplace_back(Signature::Parameter {core::Identifier::make("arg0", core::Location::nowhere()), type_context.getString()});
                signature   = Signature(intrinsic.identifier(), std::move(parameters), true);
                return_type = type_context.getUnit();// Return type is determined dynamically by the called intrinsic.

                break;
            }

            case core::Intrinsic::SIZE_ADD:
            case core::Intrinsic::SIZE_SUB:
            case core::Intrinsic::SIZE_MUL:
            case core::Intrinsic::SIZE_DIV:
            case core::Intrinsic::SIZE_REM:
            {
                std::tie(signature, return_type) = makeBinarySignature(intrinsic, type_context.getSize());
                break;
            }

            case core::Intrinsic::HALF_ADD:
            case core::Intrinsic::HALF_SUB:
            case core::Intrinsic::HALF_MUL:
            case core::Intrinsic::HALF_DIV:
            case core::Intrinsic::HALF_REM:
            {
                std::tie(signature, return_type) = makeBinarySignature(intrinsic, type_context.getFloat(core::Precision::HALF));
                break;
            }

            case core::Intrinsic::SINGLE_ADD:
            case core::Intrinsic::SINGLE_SUB:
            case core::Intrinsic::SINGLE_MUL:
            case core::Intrinsic::SINGLE_DIV:
            case core::Intrinsic::SINGLE_REM:
            {
                std::tie(signature, return_type) = makeBinarySignature(intrinsic, type_context.getFloat(core::Precision::SINGLE));
                break;
            }

            case core::Intrinsic::DOUBLE_ADD:
            case core::Intrinsic::DOUBLE_SUB:
            case core::Intrinsic::DOUBLE_MUL:
            case core::Intrinsic::DOUBLE_DIV:
            case core::Intrinsic::DOUBLE_REM:
            {
                std::tie(signature, return_type) = makeBinarySignature(intrinsic, type_context.getFloat(core::Precision::DOUBLE));
                break;
            }

            case core::Intrinsic::QUAD_ADD:
            case core::Intrinsic::QUAD_SUB:
            case core::Intrinsic::QUAD_MUL:
            case core::Intrinsic::QUAD_DIV:
            case core::Intrinsic::QUAD_REM:
            {
                std::tie(signature, return_type) = makeBinarySignature(intrinsic, type_context.getFloat(core::Precision::QUAD));
                break;
            }
        }

        assert(signature.hasValue());
        assert(return_type.hasValue());

        return {signature.value(), return_type.value()};
    }
}
