#include "Resolver.h"

struct ance::ret::Resolver::Implementation
{

};

ance::ret::Resolver::Resolver() : implementation_(utility::makeOwned<Implementation>()) {}

ance::ret::Resolver::~Resolver() = default;
