#include "Compiler.h"

struct ance::build::Compiler::Implementation
{

};

ance::build::Compiler::Compiler() : implementation_(utility::makeOwned<Implementation>()) {}

ance::build::Compiler::~Compiler() = default;
