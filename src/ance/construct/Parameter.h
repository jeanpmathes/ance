#ifndef ANCE_SRC_ANCE_CONSTRUCT_PARAMETER_H_
#define ANCE_SRC_ANCE_CONSTRUCT_PARAMETER_H_

#include <string>

#include "LocalVariable.h"

namespace ance
{
	class WrappedNativeValue;
	class Type;

	class Parameter
	{
	public:
		Parameter(ance::Type* type, std::string name);

		ance::Type* type();
		std::string name();

		ance::Value* getValue();

		void wrap(llvm::Argument* argument);
		llvm::Argument* getWrapped();

	private:
		ance::Type* type_;
		std::string name_;

		ance::WrappedNativeValue* wrapper_;

		llvm::Argument* argument_;
	};
}
#endif