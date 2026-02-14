#include "CoreDefinitions.h"

#include "ance/utility/Containers.h"
#include "ance/utility/Owners.h"

#include "ance/core/Intrinsic.h"

#include "ance/bbt/FlowBuilder.h"
#include "ance/bbt/Function.h"
#include "ance/bbt/Type.h"

#include "ance/cet/Provider.h"
#include "ance/cet/Runner.h"

void ance::defineCoreLanguageFunctions(cet::Runner& runner)
{
    utility::List<utility::Shared<bbt::Function>> provider;// todo: remove / improve the functions
    bbt::FlowBuilder                              builder(core::Location::global(), runner.types());

    builder.setActiveBasicBlock(builder.createBasicBlock());
    {
        bbt::Temporary const& value = builder.pushVariableAccess(core::Identifier::make("value"));

        bbt::Temporary const& str_value = builder.pushTemporary("str_value");
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(value);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Intrinsic::B_2_STR, std::move(args), str_value, core::Location::global()));
        }

        bbt::Temporary const& location = builder.pushConstant(bbt::Location::make(core::Location::global(), runner.types()));

        bbt::Temporary const& result = builder.pushTemporary("result");
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(str_value);
            args.emplace_back(location);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Intrinsic::LOG, std::move(args), result, core::Location::global()));
        }
        (void) result;
    }
    provider.emplace_back(utility::makeShared<bbt::Function>(
        bbt::Signature::make("log1b", bbt::Signature::Parameter(core::Identifier::make("value"), runner.types().getBool())),
        runner.types().getUnit(),
        builder.build("main"),
        runner.types()));

    builder.setActiveBasicBlock(builder.createBasicBlock());
    {
        bbt::Temporary const& value    = builder.pushVariableAccess(core::Identifier::make("value"));
        bbt::Temporary const& location = builder.pushVariableAccess(core::Identifier::make("location"));

        bbt::Temporary const& str_value = builder.pushTemporary("str_value");
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(value);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Intrinsic::B_2_STR, std::move(args), str_value, core::Location::global()));
        }

        bbt::Temporary const& result = builder.pushTemporary("result");
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(str_value);
            args.emplace_back(location);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Intrinsic::LOG, std::move(args), result, core::Location::global()));
        }
        (void) result;
    }
    provider.emplace_back(
        utility::makeShared<bbt::Function>(bbt::Signature::make("log2b",
                                                                bbt::Signature::Parameter(core::Identifier::make("value"), runner.types().getBool()),
                                                                bbt::Signature::Parameter(core::Identifier::make("location"), runner.types().getLocation())),
                                           runner.types().getUnit(),
                                           builder.build("main"),
                                           runner.types()));

    builder.setActiveBasicBlock(builder.createBasicBlock());
    {
        bbt::Temporary const& value = builder.pushVariableAccess(core::Identifier::make("value"));

        bbt::Temporary const& location = builder.pushConstant(bbt::Location::make(core::Location::global(), runner.types()));

        bbt::Temporary const& result = builder.pushTemporary("result");
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(value);
            args.emplace_back(location);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Intrinsic::LOG, std::move(args), result, core::Location::global()));
        }
        (void) result;
    }
    provider.emplace_back(utility::makeShared<bbt::Function>(
        bbt::Signature::make("log1s", bbt::Signature::Parameter(core::Identifier::make("value"), runner.types().getString())),
        runner.types().getUnit(),
        builder.build("main"),
        runner.types()));

    builder.setActiveBasicBlock(builder.createBasicBlock());
    {
        bbt::Temporary const& value    = builder.pushVariableAccess(core::Identifier::make("value"));
        bbt::Temporary const& location = builder.pushVariableAccess(core::Identifier::make("location"));

        bbt::Temporary const& result = builder.pushTemporary("result");
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(value);
            args.emplace_back(location);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Intrinsic::LOG, std::move(args), result, core::Location::global()));
        }
        (void) result;
    }
    provider.emplace_back(
        utility::makeShared<bbt::Function>(bbt::Signature::make("log2s",
                                                                bbt::Signature::Parameter(core::Identifier::make("value"), runner.types().getString()),
                                                                bbt::Signature::Parameter(core::Identifier::make("location"), runner.types().getLocation())),
                                           runner.types().getUnit(),
                                           builder.build("main"),
                                           runner.types()));

    builder.setActiveBasicBlock(builder.createBasicBlock());
    {
        bbt::Temporary const& file     = builder.pushVariableAccess(core::Identifier::make("file"));
        bbt::Temporary const& location = builder.pushVariableAccess(core::Identifier::make("location"));

        bbt::Temporary const& result = builder.pushTemporary("result");
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(file);
            args.emplace_back(location);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Intrinsic::INCLUDE, std::move(args), result, core::Location::global()));
        }
        (void) result;
    }
    provider.emplace_back(
        utility::makeShared<bbt::Function>(bbt::Signature::make("include",
                                                                bbt::Signature::Parameter(core::Identifier::make("file"), runner.types().getString()),
                                                                bbt::Signature::Parameter(core::Identifier::make("location"), runner.types().getLocation())),
                                           runner.types().getUnit(),
                                           builder.build("main"),
                                           runner.types()));

    runner.add(cet::Provider::fromList(std::move(provider)));
}
