#include "IndexerSet.h"

IndexerSet::IndexerSet(Expression* indexed, Expression* index)
	: indexed_(indexed), index_(index)
{

}

void IndexerSet::setScope(ance::Scope* scope)
{
	indexed_->setScope(scope);
	index_->setScope(scope);
}

void IndexerSet::assign(
	ance::Value* value,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileContext* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	ance::Type* indexed_type = indexed_->getType();
	assert(indexed_type->isIndexerDefined(Indexer::SET) && "Type does not support this indexer.");

	indexed_type->buildSetIndexer(indexed_->getValue(), index_->getValue(), value, c, m, state, ir, di);
}
