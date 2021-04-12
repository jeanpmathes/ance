#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

class CompileState;

namespace ance
{
	class Value;
	class Type;
}

class Expression
{
public:
	virtual ance::Type* get_type() = 0;
	virtual ance::Value* get_value() = 0;

	virtual ~Expression() = default;
};
#endif