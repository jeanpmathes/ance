#ifndef ANCE_LOCALSCOPE_H
#define ANCE_LOCALSCOPE_H

#include "LocalVariable.h"
#include "Scope.h"

class Expression;

namespace ance
{
	class LocalScope : public Scope
	{
	public:
		explicit LocalScope(ance::Scope* parent);

		ance::GlobalScope* get_global_scope() override;

		bool validate() override;

		ance::LocalVariable* define_local_variable(const std::string& identifier, ance::Type* type, Expression* expression);
		ance::Variable* get_variable(std::string identifier) override;

	private:
		ance::Scope* parent_;

		std::map<std::string, ance::LocalVariable*> local_variables;
	};
}
#endif
