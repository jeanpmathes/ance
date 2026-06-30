#include "IntrinsicSignature.h"

#include "ance/utility/Optional.h"

#include "ance/bbt/Type.h"

namespace ance::bbt
{
    static std::tuple<Signature, utility::Shared<Type const>> makeBinarySignature(core::Intrinsic const intrinsic, utility::Shared<Type const> type)
    {
        Signature signature = Signature::makeAndNameParameters(intrinsic.identifier(), type, type);
        return {std::move(signature), type};
    }

    static std::tuple<Signature, utility::Shared<Type const>> makeUnarySignature(core::Intrinsic const intrinsic, utility::Shared<Type const> type)
    {
        Signature signature = Signature::makeAndNameParameters(intrinsic.identifier(), type);
        return {std::move(signature), type};
    }

    static std::tuple<Signature, utility::Shared<Type const>> makeComparisonSignature(core::Intrinsic const       intrinsic,
                                                                                      utility::Shared<Type const> type,
                                                                                      TypeContext&          type_context)
    {
        Signature signature = Signature::makeAndNameParameters(intrinsic.identifier(), type, type);
        return {std::move(signature), type_context.getBool()};
    }

    std::tuple<Signature, utility::Shared<Type const>> getIntrinsicSignature(core::Intrinsic intrinsic, TypeContext& type_context)
    {
        utility::Optional<Signature>             signature;
        utility::Optional<utility::Shared<Type const>> return_type;

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
            case core::Intrinsic::SIZE_LT:
            case core::Intrinsic::SIZE_LE:
            case core::Intrinsic::SIZE_GT:
            case core::Intrinsic::SIZE_GE:
            case core::Intrinsic::SIZE_EQ:
            case core::Intrinsic::SIZE_NE:
            {
                std::tie(signature, return_type) = makeComparisonSignature(intrinsic, type_context.getSize(), type_context);
                break;
            }
            case core::Intrinsic::SIZE_BITNOT:
            {
                std::tie(signature, return_type) = makeUnarySignature(intrinsic, type_context.getSize());
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
            case core::Intrinsic::HALF_LT:
            case core::Intrinsic::HALF_LE:
            case core::Intrinsic::HALF_GT:
            case core::Intrinsic::HALF_GE:
            case core::Intrinsic::HALF_EQ:
            case core::Intrinsic::HALF_NE:
            {
                std::tie(signature, return_type) = makeComparisonSignature(intrinsic, type_context.getFloat(core::Precision::HALF), type_context);
                break;
            }
            case core::Intrinsic::HALF_NEG:
            {
                std::tie(signature, return_type) = makeUnarySignature(intrinsic, type_context.getFloat(core::Precision::HALF));
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
            case core::Intrinsic::SINGLE_LT:
            case core::Intrinsic::SINGLE_LE:
            case core::Intrinsic::SINGLE_GT:
            case core::Intrinsic::SINGLE_GE:
            case core::Intrinsic::SINGLE_EQ:
            case core::Intrinsic::SINGLE_NE:
            {
                std::tie(signature, return_type) = makeComparisonSignature(intrinsic, type_context.getFloat(core::Precision::SINGLE), type_context);
                break;
            }
            case core::Intrinsic::SINGLE_NEG:
            {
                std::tie(signature, return_type) = makeUnarySignature(intrinsic, type_context.getFloat(core::Precision::SINGLE));
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
            case core::Intrinsic::DOUBLE_LT:
            case core::Intrinsic::DOUBLE_LE:
            case core::Intrinsic::DOUBLE_GT:
            case core::Intrinsic::DOUBLE_GE:
            case core::Intrinsic::DOUBLE_EQ:
            case core::Intrinsic::DOUBLE_NE:
            {
                std::tie(signature, return_type) = makeComparisonSignature(intrinsic, type_context.getFloat(core::Precision::DOUBLE), type_context);
                break;
            }
            case core::Intrinsic::DOUBLE_NEG:
            {
                std::tie(signature, return_type) = makeUnarySignature(intrinsic, type_context.getFloat(core::Precision::DOUBLE));
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
            case core::Intrinsic::QUAD_LT:
            case core::Intrinsic::QUAD_LE:
            case core::Intrinsic::QUAD_GT:
            case core::Intrinsic::QUAD_GE:
            case core::Intrinsic::QUAD_EQ:
            case core::Intrinsic::QUAD_NE:
            {
                std::tie(signature, return_type) = makeComparisonSignature(intrinsic, type_context.getFloat(core::Precision::QUAD), type_context);
                break;
            }
            case core::Intrinsic::QUAD_NEG:
            {
                std::tie(signature, return_type) = makeUnarySignature(intrinsic, type_context.getFloat(core::Precision::QUAD));
                break;
            }

            case core::Intrinsic::BOOL_EQ:
            case core::Intrinsic::BOOL_NE:
            {
                std::tie(signature, return_type) = makeComparisonSignature(intrinsic, type_context.getBool(), type_context);
                break;
            }
            case core::Intrinsic::UNIT_EQ:
            case core::Intrinsic::UNIT_NE:
            {
                std::tie(signature, return_type) = makeComparisonSignature(intrinsic, type_context.getUnit(), type_context);
                break;
            }
            case core::Intrinsic::STRING_EQ:
            case core::Intrinsic::STRING_NE:
            {
                std::tie(signature, return_type) = makeComparisonSignature(intrinsic, type_context.getString(), type_context);
                break;
            }
            case core::Intrinsic::IDENTIFIER_EQ:
            case core::Intrinsic::IDENTIFIER_NE:
            {
                std::tie(signature, return_type) = makeComparisonSignature(intrinsic, type_context.getIdentifier(), type_context);
                break;
            }
            case core::Intrinsic::LOCATION_EQ:
            case core::Intrinsic::LOCATION_NE:
            {
                std::tie(signature, return_type) = makeComparisonSignature(intrinsic, type_context.getLocation(), type_context);
                break;
            }
        }

        assert(signature.hasValue());
        assert(return_type.hasValue());

        return {signature.value(), return_type.value()};
    }
}
