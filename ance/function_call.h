 
#include "Statement.h"
class function_call :
	public Statement
{
public:
	function_call(unsigned int l, unsigned int c, std::string ident);
	void build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
	~function_call();

private:
	std::string identifier;
};
