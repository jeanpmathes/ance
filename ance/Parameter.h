#ifndef ANCE_PARAMETER_H
#define ANCE_PARAMETER_H

#include <string>

#include "LocalVariable.h"

namespace ance
{
	class ValueWrapper;
	class Type;

	class Parameter
	{
	public:
		Parameter(ance::Type* type, std::string name);

		ance::Type* type();
		std::string name();

		ance::Value* get_value();

		void wrap(llvm::Argument* argument);
		llvm::Argument* get_wrapped();

	private:
		ance::Type* type_;
		std::string name_;

		ance::ValueWrapper* wrapper_;

		llvm::Argument* argument_;
	};
}
#endif