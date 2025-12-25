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
        bbt::Temporary const& value = builder.pushVariableRead(core::Identifier::like("value"));

        bbt::Temporary const& str_value = builder.pushTemporary();
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(value);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::B2Str::instance(), std::move(args), str_value, core::Location::global()));
        }

        bbt::Temporary const& location = builder.pushConstant(bbt::Location::make(core::Location::global(), runner.types()));

        bbt::Temporary const& result = builder.pushTemporary();
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(str_value);
            args.emplace_back(location);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Log::instance(), std::move(args), result, core::Location::global()));
        }
        (void) result;
    }
    provider.emplace_back(utility::makeShared<bbt::Function>(
        bbt::Signature::like("print1b", bbt::Signature::Parameter(core::Identifier::like("value"), runner.types().getBool())),
        runner.types().getUnit(),
        builder.build(),
        runner.types()));

    builder.setActiveBasicBlock(builder.createBasicBlock());
    {
        bbt::Temporary const& value    = builder.pushVariableRead(core::Identifier::like("value"));
        bbt::Temporary const& location = builder.pushVariableRead(core::Identifier::like("location"));

        bbt::Temporary const& str_value = builder.pushTemporary();
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(value);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::B2Str::instance(), std::move(args), str_value, core::Location::global()));
        }

        bbt::Temporary const& result = builder.pushTemporary();
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(str_value);
            args.emplace_back(location);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Log::instance(), std::move(args), result, core::Location::global()));
        }
        (void) result;
    }
    provider.emplace_back(
        utility::makeShared<bbt::Function>(bbt::Signature::like("print2b",
                                                                bbt::Signature::Parameter(core::Identifier::like("value"), runner.types().getBool()),
                                                                bbt::Signature::Parameter(core::Identifier::like("location"), runner.types().getLocation())),
                                           runner.types().getUnit(),
                                           builder.build(),
                                           runner.types()));

    builder.setActiveBasicBlock(builder.createBasicBlock());
    {
        bbt::Temporary const& value = builder.pushVariableRead(core::Identifier::like("value"));

        bbt::Temporary const& location = builder.pushConstant(bbt::Location::make(core::Location::global(), runner.types()));

        bbt::Temporary const& result = builder.pushTemporary();
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(value);
            args.emplace_back(location);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Log::instance(), std::move(args), result, core::Location::global()));
        }
        (void) result;
    }
    provider.emplace_back(utility::makeShared<bbt::Function>(
        bbt::Signature::like("print1s", bbt::Signature::Parameter(core::Identifier::like("value"), runner.types().getString())),
        runner.types().getUnit(),
        builder.build(),
        runner.types()));

    builder.setActiveBasicBlock(builder.createBasicBlock());
    {
        bbt::Temporary const& value    = builder.pushVariableRead(core::Identifier::like("value"));
        bbt::Temporary const& location = builder.pushVariableRead(core::Identifier::like("location"));

        bbt::Temporary const& result = builder.pushTemporary();
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(value);
            args.emplace_back(location);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Log::instance(), std::move(args), result, core::Location::global()));
        }
        (void) result;
    }
    provider.emplace_back(
        utility::makeShared<bbt::Function>(bbt::Signature::like("print2s",
                                                                bbt::Signature::Parameter(core::Identifier::like("value"), runner.types().getString()),
                                                                bbt::Signature::Parameter(core::Identifier::like("location"), runner.types().getLocation())),
                                           runner.types().getUnit(),
                                           builder.build(),
                                           runner.types()));

    builder.setActiveBasicBlock(builder.createBasicBlock());
    {
        bbt::Temporary const& file     = builder.pushVariableRead(core::Identifier::like("file"));
        bbt::Temporary const& location = builder.pushVariableRead(core::Identifier::like("location"));

        bbt::Temporary const& result = builder.pushTemporary();
        {
            utility::List<std::reference_wrapper<bbt::Temporary const>> args;
            args.emplace_back(file);
            args.emplace_back(location);
            builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Include::instance(), std::move(args), result, core::Location::global()));
        }
        (void) result;
    }
    provider.emplace_back(
        utility::makeShared<bbt::Function>(bbt::Signature::like("include",
                                                                bbt::Signature::Parameter(core::Identifier::like("file"), runner.types().getString()),
                                                                bbt::Signature::Parameter(core::Identifier::like("location"), runner.types().getLocation())),
                                           runner.types().getUnit(),
                                           builder.build(),
                                           runner.types()));

    runner.add(cet::Provider::fromList(std::move(provider)));
}
