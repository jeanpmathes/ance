#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Entity;

    class FunctionGroup;
    class Function;
    class Type;
    class Variable;

    template<>
    struct HandleConfig<FunctionGroup> {
        using BaseType = Entity;
    };

    template<>
    struct HandleConfig<Function> {
        using BaseType = Entity;
    };

    template<>
    struct HandleConfig<Type> {
        using BaseType = Entity;
    };

    template<>
    struct HandleConfig<Variable> {
        using BaseType = Entity;
    };
}
