#include "LanguageCore.h"

#include "ance/utility/Owners.h"

#include "ance/core/Identifier.h"

#include "ance/bbt/Function.h"
#include "ance/bbt/Type.h"
#include "ance/bbt/Value.h"

#include "ance/cet/Runner.h"

namespace
{
    void defineLanguageCoreTypes(ance::cet::Runner& runner)
    {
        auto declare_type = [&](ance::utility::Shared<ance::bbt::Type> type) { runner.declareCoreVariable(type->name(), type); };

        declare_type(runner.types().getBool());
        declare_type(runner.types().getUnit());
        declare_type(runner.types().getSize());
        declare_type(runner.types().getString());
        declare_type(runner.types().getIdentifier());
        declare_type(runner.types().getType());
        declare_type(runner.types().getLocation());
        declare_type(runner.types().getFunction());
    }

    void defineLanguageCoreValues(ance::cet::Runner& runner)
    {
        // todo: maybe remove true and false literals and define them as variables here

        runner.declareCoreVariable(ance::core::Identifier::make("nowhere", ance::core::Location::nowhere()),
                                   ance::utility::makeShared<ance::bbt::Location>(ance::core::Location::project(), runner.types()));
    }

    void defineLanguageCoreFunctions(ance::cet::Runner& runner)
    {
        // todo: remove / improve the functions
        // todo: probably make them all compiletime only

        runner.declareCore(R"CODE(
public log1b (value: Bool)
{
    let string_value: String := intrinsic "b_2_str" (value);
    intrinsic "log" (string_value, nowhere);
}
)CODE", "log1b");

        runner.declareCore(R"CODE(
public log2b (value: Bool, location: Location)
{
    let string_value: String := intrinsic "b_2_str" (value);
    intrinsic "log" (string_value, location);
}
)CODE", "log2b");

        runner.declareCore(R"CODE(
public log1s (value: String)
{
    intrinsic "log" (value, nowhere);
}
)CODE", "log1s");

        runner.declareCore(R"CODE(
public log2s (value: String, location: Location)
{
    intrinsic "log" (value, location);
}
)CODE","log2s");

        runner.declareCore(R"CODE(
public include (file: String, location: Location)
{
    intrinsic "include" (file, location);
}
)CODE", "include");
    }
}

void ance::cet::defineLanguageCore(Runner& runner)
{
    defineLanguageCoreTypes(runner);
    defineLanguageCoreValues(runner);
    defineLanguageCoreFunctions(runner);
}
