#include "tree/Definition.h"

[[maybe_unused]] static tree::Definition cet =
    tree::Definition::create().node("Unit", "A unit of compilation.", [](auto&) {});
