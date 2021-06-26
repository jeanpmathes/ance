#include "IndexerGet.h"

#include "Type.h"

IndexerGet::IndexerGet(Expression* indexed, Expression* index)
	: indexed_(indexed), index_(index)
{

}

void IndexerGet::setScope(ance::Scope* scope)
{
	indexed_->setScope(scope);
	index_->setScope(scope);
}

ance::Type* IndexerGet::getType()
{
	return indexed_->getType()->getIndexerReturnType();
}

void IndexerGet::buildValue(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	ance::Type* indexed_type = indexed_->getType();
	assert(indexed_type->isIndexerDefined(Indexer::GET) && "Type does not support this indexer.");

	ance::Value
		* return_value = indexed_type->buildGetIndexer(indexed_->getValue(), index_->getValue(), c, m, state, ir, di);
	setValue(return_value);
}

IndexerGet::~IndexerGet() = default;
