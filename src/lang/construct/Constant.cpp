#include "Constant.h"

#include "lang/ApplicationVisitor.h"
#include "lang/type/Type.h"

lang::Constant::Constant(lang::Type const& type) : Value(type) {}
