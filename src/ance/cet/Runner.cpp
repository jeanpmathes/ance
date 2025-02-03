#include "Runner.h"

struct ance::cet::Runner::Implementation
{
};

ance::cet::Runner::Runner() : implementation_(utility::makeOwned<Implementation>()) {}

ance::cet::Runner::~Runner() = default;
