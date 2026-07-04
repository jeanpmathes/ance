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
        auto declare_type = [&](ance::utility::Shared<ance::bbt::Type const> type) { runner.declareCoreVariable(type->name(), type); };

        declare_type(runner.types().Bool());
        declare_type(runner.types().Unit());
        declare_type(runner.types().Size());
        declare_type(runner.types().String());
        declare_type(runner.types().Identifier());
        declare_type(runner.types().Type());
        declare_type(runner.types().Location());
        declare_type(runner.types().Function());

        declare_type(runner.types().Float(ance::core::Precision::HALF));
        declare_type(runner.types().Float(ance::core::Precision::SINGLE));
        declare_type(runner.types().Float(ance::core::Precision::DOUBLE));
        declare_type(runner.types().Float(ance::core::Precision::QUAD));
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
    let string_value: String := intrinsic "b_2_str" args (value);
    intrinsic "log" args (string_value, nowhere);
}
)CODE", "log1b");

        runner.declareCore(R"CODE(
public log2b (value: Bool, location: Location)
{
    let string_value: String := intrinsic "b_2_str" args (value);
    intrinsic "log" args (string_value, location);
}
)CODE", "log2b");

        runner.declareCore(R"CODE(
public log1s (value: String)
{
    intrinsic "log" args (value, nowhere);
}
)CODE", "log1s");

        runner.declareCore(R"CODE(
public log2s (value: String, location: Location)
{
    intrinsic "log" args (value, location);
}
)CODE","log2s");

        runner.declareCore(R"CODE(
public log1fh (value: Half)
{
    let string_value: String := intrinsic "fh_2_str" args (value);
    intrinsic "log" args (string_value, nowhere);
}
)CODE",
                           "log1fh");

        runner.declareCore(R"CODE(
public log1fs (value: Single)
{
    let string_value: String := intrinsic "fs_2_str" args (value);
    intrinsic "log" args (string_value, nowhere);
}
)CODE",
                           "log1fs");

        runner.declareCore(R"CODE(
public log1fd (value: Double)
{
    let string_value: String := intrinsic "fd_2_str" args (value);
    intrinsic "log" args (string_value, nowhere);
}
)CODE",
                           "log1fd");

        runner.declareCore(R"CODE(
public log1fq (value: Quad)
{
    let string_value: String := intrinsic "fq_2_str" args (value);
    intrinsic "log" args (string_value, nowhere);
}
)CODE",
                           "log1fq");

        runner.declareCore(R"CODE(
public include (file: String, location: Location)
{
    intrinsic "include" args (file, location);
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
